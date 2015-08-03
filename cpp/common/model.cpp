#ifndef PI
#define PI 3.14159265359f
#endif

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

#include <string>
#include <algorithm> // std::find

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp>
#endif

// Include matrix_transform.hpp .
#ifndef __GLM_GTC_MATRIX_TRANSFORM_HPP_INCLUDED
#define __GLM_GTC_MATRIX_TRANSFORM_HPP_INCLUDED
#include <glm/gtc/matrix_transform.hpp>
#endif

// Include gtc/quaternion.hpp .
#ifndef __GLM_GTC_QUATERNION_HPP_INCLUDED
#define __GLM_GTC_QUATERNION_HPP_INCLUDED
#include <glm/gtc/quaternion.hpp>
#endif

// Include gtx/quaternion.hpp .
#ifndef __GLM_GTX_QUATERNION_HPP_INCLUDED
#define __GLM_GTX_QUATERNION_HPP_INCLUDED
#include <glm/gtx/quaternion.hpp>
#endif

#include "model.hpp"
#include "globals.hpp"
#include "texture.hpp"
#include "heightmap_loader.hpp"
#include "objloader.hpp"
#include "vboindexer.hpp"

extern GLFWwindow* window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.

glm::vec3 camera_position;

namespace model
{
    GLfloat speed = 5.0f; // 5 units / second
#ifdef TESTING_SPHERICAL_WORLD_IN_USE
    GLfloat turbo_factor = 100.0f;
    GLfloat twin_turbo_factor = 50000.0f;
#else
    GLfloat turbo_factor = 5.0f;
    GLfloat twin_turbo_factor = 100.0f;
#endif
    GLfloat mouseSpeed = 0.005f;

    // `World`, `Shader`, `Texture`, `Species`, `Object`.
    // `World` must be created before any `Shader`. `parent_pointer` must be given to each `Shader`.
    // `Shader` must be created before any `Texture`. `parent_pointer` must be given to each `Texture`.
    // `Texture` must be created before any `Species`. `parent_pointer` must be given to each `Species`.
    // `Species` must be create before any `Object` of that `Species`. `parent_pointer` must be given to each `Object` of the `Species`.
    //
    //
    // Hierarchy for regular objects (including world species):
    //
    //     World
    //       ^
    //    Shader
    //       ^
    //    Texture
    //       ^
    //    Species
    //       ^
    //    Object
    //
    //
    // Hierarchy for glyph (character) objects:
    //
    //     World
    //       ^
    //    Shader
    //       ^
    //    Texture
    //       ^
    //     Font
    //       ^
    //     Glyph
    //       ^
    //    Object
    //
    //
    // Deleting a `World` also deletes all shaders, textures, species and objects that are binded to the same World.
    // Deleting a `Shader` also deletes all textures, species and objects that are binded to the same Shader.
    // Deleting a `Texture` also deletes all species and objects that are binded to the same Texture.
    // Deleting a `Species` also deletes all objects that are binded to the same Species.
    // Deleting an `Object` only deletes the object.

    // Characteristics of object type graphs:
    // 1. Each object must be an undirected graph.
    // 2. Each edge must be a link in the graph.
    // 3. The faces of each object must form a closed surface. The only exception is the terrain object, which may have borders.
    //
    // Modifying object type graphs:
    // 1. Translation of a vertex does not require changes in any other nodes of the graph.
    // 2. Adding a vertex always requires changes in some other nodes of the graph (unless the graph is empty before adding the vertex).
    // 3. Deleting a vertex always requires deletion of edges from some other nodes of the graph (unless the vertex is the only vertex of the graph).
    // 4. Deleting a vertex or vertices usually also requires appropriate vertex additions. These changes are called 'complex modifications'.
    //
    // Adding a vertex or several vertices:
    // 1. The new edges must be connected to the existing graph with appropriate links.
    // 2. Each new face must be a triangle.
    //
    // Deleting a vertex or several vertices:
    // 1. When a vertex or several vertices are deleted, their links must be deleted too (`Node` destructor handles this).
    // 2. If the vertex to be deleted is on the border of a [terrain] object, it can be deleted.
    // 3. If the vertices that are neighbors to the vertex to be deleted form only triangeles, the vertex can be deleted without vertex additions.
    // 4. Otherwise the vertex cannot be deleted without appropriate vertex and edge additions.
    //
    // Complex modifications:
    // 1. In complex modifications one or more vertices and edges are deleted and one or more vertices and edges are added.
    // 2. Complex modifications may also change the topology of the object (tunnels, arcs, etc.).
    // 3. If a complex modification causes splitting the object in two or more pieces, each piece becomes a separate object.
    // 4. If the splitted object is a terrain object, then the lowest vertex (any vertex with smallest y-coordinate) of each piece is searched and the
    //    y-coordinates of these are compared. The piece with the smallest y-coordinate (lowest altitude) remains terrain, other pieces become
    //    regular objects. The pieces that become regular objects will be subject to gravity the same way as any regular object.

    void set_child_pointer(GLuint childID, void* child_pointer, std::vector<void*> &child_pointer_vector, std::queue<GLuint> &free_childID_queue)
    {
        child_pointer_vector[childID] = child_pointer;

        if (child_pointer == NULL)
        {
            if (childID == child_pointer_vector.size() - 1)
            {
                // OK, this is the biggest childID of all childID's of this 'object'.
                // We can reduce the size of the child pointer vector at least by 1.
                while ((!child_pointer_vector.empty()) && (child_pointer_vector.back() == NULL))
                {
                    // Reduce the size of child pointer vector by 1.
                    child_pointer_vector.pop_back();
                }
            }
        }
    }

    GLuint get_childID(std::vector<void*> &child_pointer_vector, std::queue<GLuint> &free_childID_queue)
    {
        GLuint childID;

        while (!free_childID_queue.empty())
        {
            // return the first (oldest) free childID.
            childID = free_childID_queue.front();
            free_childID_queue.pop();

            // check that the child index does not exceed current child pointer vector.
            if (childID < child_pointer_vector.size())
            {
                // OK, it does not exceed current child pointer vector.
                return childID;
            }
        }
        // OK, the queue is empty.
        // A new child index must be created.
        childID = child_pointer_vector.size();

        // child pointer vector must also be extended with an appropriate NULL pointer.
        child_pointer_vector.push_back(NULL);

        return childID;
    }

    GLfloat get_ground_level(
            model::Species* world_species,
            glm::vec3 position)
    {
        if (!world_species->is_world)
        {
            // if the current species is not a world species, no collision detection to the ground will be performed.
            return NAN;
        }

        if ((position.x < 0.0f) || (position.x > world_species->image_width))
        {
            // if the x coordinate is out of range, no collision detection to the ground will be performed.
            return NAN;
        }

        if ((position.z < 0.0f) || (position.z > world_species->image_height))
        {
            // if the z coordinate is out of range, no collision detection to the ground will be performed.
            return NAN;
        }

        // compute the indices of closest vertices.
        GLuint southwest_i = (GLuint) floor(position.z) * world_species->image_width + floor(position.x);
        GLuint southeast_i = (GLuint) floor(position.z) * world_species->image_width + ceil(position.x);
        GLuint northwest_i = (GLuint) ceil(position.z) * world_species->image_width + floor(position.x);
        GLuint northeast_i = (GLuint) ceil(position.z) * world_species->image_width + ceil(position.x);

        // read closest the heights of closest integer coordinates to be used in bilinear interpolation.
        GLfloat southwest_height = world_species->vertices[southwest_i].y;
        GLfloat southeast_height = world_species->vertices[southeast_i].y;
        GLfloat northwest_height = world_species->vertices[northwest_i].y;
        GLfloat northeast_height = world_species->vertices[northeast_i].y;

        // these are not actually means but interpolations.
        // the result of the interpolation is mean if and only if (ceil(x) - x == 0.5) & (x - floor(x) == 0.5) , likewise for the z coordinate.
        GLfloat south_mean;
        GLfloat north_mean;
        GLfloat mean;

        if ((position.x - floor(position.x) < 0.01f) || (ceil(position.x) - position.x < 0.01f))
        {
            // if the x coordinate is too close to integer, the height of the closest vertex is used instead.
            south_mean = southwest_height;
            north_mean = northwest_height;
        }
        else
        {
            // the height is computed using bilinear interpolation.
            south_mean = (GLfloat) ((ceil(position.x) - position.x) * southwest_height) + ((position.x - floor(position.x)) * southeast_height);
            north_mean = (GLfloat) ((ceil(position.x) - position.x) * northwest_height) + ((position.x - floor(position.x)) * northeast_height);
        }

        if ((position.z - floor(position.z) < 0.01f) || (ceil(position.z) - position.z < 0.01f))
        {
            // if the z coordinate is too close to integer, the mean is used instead of bilinear interpolation.
            mean = (south_mean + north_mean) / 2.0f;
        }
        else
        {
            // the height is computed using bilinear interpolation.
            mean = (GLfloat) ((ceil(position.z) - position.z) * south_mean) + ((position.z - floor(position.z)) * north_mean);
        }

        return mean;
    }

    GLfloat get_floor_level(
            model::Species* world_species,
            glm::vec3 position)
    {
        if (!world_species->is_world)
        {
            // if the current species is not a world species, no collision detection to the ground will be performed.
            return NAN;
        }

#define CHARACTER_RADIUS 1.0f
        GLfloat current_ground_level = get_ground_level(world_species, position);

        // Get ground level at current location and +/- 1.0f.
        glm::vec3 south_position = position;
        south_position.z -= (GLfloat) CHARACTER_RADIUS;
        GLfloat south_ground_level = get_ground_level(world_species, south_position);

        glm::vec3 west_position = position;
        west_position.x -= (GLfloat) CHARACTER_RADIUS;
        GLfloat west_ground_level = get_ground_level(world_species, west_position);

        glm::vec3 north_position = position;
        north_position.z += (GLfloat) CHARACTER_RADIUS;
        GLfloat north_ground_level = get_ground_level(world_species, north_position);

        glm::vec3 east_position = position;
        east_position.x += (GLfloat) CHARACTER_RADIUS;
        GLfloat east_ground_level = get_ground_level(world_species, east_position);

        glm::vec3 southwest_position = south_position;
        southwest_position.x -= (GLfloat) CHARACTER_RADIUS;
        GLfloat southwest_ground_level = get_ground_level(world_species, southwest_position);

        glm::vec3 southeast_position = south_position;
        southeast_position.x += (GLfloat) CHARACTER_RADIUS;
        GLfloat southeast_ground_level = get_ground_level(world_species, southeast_position);

        glm::vec3 northwest_position = north_position;
        northwest_position.x -= (GLfloat) CHARACTER_RADIUS;
        GLfloat northwest_ground_level = get_ground_level(world_species, northwest_position);

        glm::vec3 northeast_position = north_position;
        northeast_position.x += (GLfloat) CHARACTER_RADIUS;
        GLfloat northeast_ground_level = get_ground_level(world_species, northeast_position);

        GLfloat temp_max_between_southwest_and_southeast = fmax(southwest_ground_level, southeast_ground_level);
        GLfloat temp_max_south = fmax(temp_max_between_southwest_and_southeast, south_ground_level);
        GLfloat temp_max_between_northwest_and_northeast = fmax(northwest_ground_level, northeast_ground_level);
        GLfloat temp_max_north = fmax(temp_max_between_northwest_and_northeast, north_ground_level);
        GLfloat temp_max_between_south_and_north = fmax(temp_max_south, temp_max_north);
        GLfloat temp_max_between_west_and_east = fmax(west_ground_level, east_ground_level);
        GLfloat temp_max_around_character = fmax(temp_max_between_south_and_north, temp_max_between_west_and_east);
        return fmax(temp_max_around_character, current_ground_level);
    }

    // template<typename T1>
    template<class T1>
        void bind_child_to_parent(T1 child_pointer, std::vector<void*> &child_pointer_vector, std::queue<GLuint> &free_childID_queue)
        {
            // get childID from the parent, because every child deserves a unique ID!
            child_pointer->childID = get_childID(child_pointer_vector, free_childID_queue);
            // set pointer to the child in parent's child pointer vector so that parent knows about children's whereabouts!
            set_child_pointer(child_pointer->childID, child_pointer, child_pointer_vector, free_childID_queue);
        }

    template <class T1, class T2>
        void bind_child_to_new_parent(
                T1 child_pointer,
                T2 new_parent_pointer,
                std::vector<void*> &old_child_pointer_vector,
                std::queue<GLuint> &old_free_childID_queue)
        {
            // set pointer to this child to NULL in the old parent.
            set_child_pointer(child_pointer->childID, NULL, old_child_pointer_vector, old_free_childID_queue);
            // set the new parent pointer.
            child_pointer->parent_pointer = new_parent_pointer;
            // bind to the new parent.
            child_pointer->bind_to_parent();
        }

    // template<typename T1>
    template<class T1>
        void delete_children(std::vector<void*> &child_pointer_vector)
        {
            for (GLuint child_i = 0; child_i < child_pointer_vector.size(); child_i++)
            {
                delete static_cast<T1>(child_pointer_vector[child_i]);
            }
        }

    // template<typename T1>
    template<class T1>
        void render_children(std::vector<void*> &child_pointer_vector)
        {
            for (GLuint child_i = 0; child_i < child_pointer_vector.size(); child_i++)
            {
                T1 child_pointer;
                child_pointer = static_cast<T1>(child_pointer_vector[child_i]);

                if (child_pointer != NULL)
                {
                    child_pointer->render();
                }
            }
        }

    World::World()
    {
        // constructor.
    }

    World::~World()
    {
        // destructor.
        std::cout << "This world will be destroyed.\n";

        // destroy all shaders of this world.
        std::cout << "All shaders of this world will be destroyed.\n";
        delete_children<model::Shader*>(this->shader_pointer_vector);
    }

    void World::render()
    {
        this->compute_matrices_from_inputs();

        // render World by calling `render()` function of each Shader.
        render_children<model::Shader*>(this->shader_pointer_vector);
    }

    void World::set_shader_pointer(GLuint childID, void* parent_pointer)
    {
        set_child_pointer(childID, parent_pointer, this->shader_pointer_vector, this->free_shaderID_queue);
    }

    void* World::get_shader_pointer(GLuint childID)
    {
        return this->shader_pointer_vector[childID];
    }

    void World::set_world_species_pointer(void* world_species_pointer)
    {
        this->world_species_pointer = world_species_pointer;
    }

    void World::compute_matrices_from_inputs()
    {
        // glfwGetTime is called only once, the first time this function is called
        static double lastTime = glfwGetTime();

        // Compute time difference between current and last frame
        double currentTime = glfwGetTime();
        float deltaTime = float(currentTime - lastTime);

        // Get mouse position
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        // Reset mouse position for next frame
        glfwSetCursorPos(window, WINDOW_WIDTH/2, WINDOW_HEIGHT/2);

        if (hasMouseEverMoved || (abs(xpos) > 0.0001) || (abs(ypos) > 0.0001))
        {
            hasMouseEverMoved = true;

            // Compute new orientation
            horizontalAngle += mouseSpeed * GLfloat(WINDOW_WIDTH/2 - xpos);
            horizontalAngle = remainder(horizontalAngle, (2.0f * PI));

            if (is_invert_mouse_in_use)
            {
                // invert mouse.
                verticalAngle   -= mouseSpeed * GLfloat(WINDOW_HEIGHT/2 - ypos);
            }
            else
            {
                // don't invert mouse.
                verticalAngle   += mouseSpeed * GLfloat(WINDOW_HEIGHT/2 - ypos);
            }
            verticalAngle = remainder(verticalAngle, (2.0f * PI));
        }

        // Direction : Spherical coordinates to Cartesian coordinates conversion
        glm::vec3 direction(
                cos(verticalAngle) * sin(horizontalAngle),
                sin(verticalAngle),
                cos(verticalAngle) * cos(horizontalAngle)
                );

        // Right vector
        glm::vec3 right = glm::vec3(
                sin(horizontalAngle - PI/2.0f),
                0,
                cos(horizontalAngle - PI/2.0f)
                );

        // Up vector
        glm::vec3 up = glm::cross(right, direction);

        GLfloat temp_speed;

        // Turbo.
        if ((glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) && (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS))
        {
            temp_speed = twin_turbo_factor * speed;
        }
        else if ((glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS))
        {
            temp_speed = turbo_factor * speed;
        }
        else
        {
            temp_speed = speed;
        }

        // Move forward
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            position += direction * deltaTime * temp_speed;
        }
        // Move backward
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            position -= direction * deltaTime * temp_speed;
        }
        // Strafe right
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            position += right * deltaTime * temp_speed;
        }
        // Strafe left
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            position -= right * deltaTime * temp_speed;
        }

        // Move up.
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            position.y += deltaTime * temp_speed;
        }

        // Move down.
        if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
        {
            position.y -= deltaTime * temp_speed;
        }

        // Move west.
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            position.x -= deltaTime * temp_speed;
        }

        // Move east.
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        {
            position.x += deltaTime * temp_speed;
        }

        // Move north.
        if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
        {
            position.z += deltaTime * temp_speed;
        }

        // Move south.
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            position.z -= deltaTime * temp_speed;
        }

        // Flight mode on.
        if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        {
            fallSpeed = 0.0f;
            inFlightmode = true;
        }

        // Run mode on.
        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        {
            fallSpeed = 0.0f;
            inFlightmode = false;
        }

        if (!inFlightmode)
        {
            fallSpeed += gravity;
            position.y -= fallSpeed;
        }

        GLfloat FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

        if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
        {
            if (is_key_I_released)
            {
                if (is_invert_mouse_in_use)
                {
                    is_invert_mouse_in_use = false;
                }
                else
                {
                    is_invert_mouse_in_use = true;
                }
            }
        }
        else
        {
            is_key_I_released = true;
        }

        // adjust position according to the ground.
        if (!inFlightmode)
        {
            if (this->world_species_pointer != NULL)
            {
                GLfloat ground_y = model::get_floor_level(static_cast<model::Species*>(this->world_species_pointer), position);

                if (!std::isnan(ground_y))
                {
                    if (position.y < ground_y)
                    {
                        position.y = ground_y;
                        fallSpeed = 0.0f;
                    }
                }
            }
        }

#ifdef TESTING_SPHERICAL_WORLD_IN_USE
        // compute spherical coordinates.
        spherical_position.rho = sqrt((position.x * position.x) + (position.y * position.y) + (position.z * position.z));
        spherical_position.theta = RADIANS_TO_DEGREES(atan2(sqrt((position.x * position.x) + (position.y * position.y)), position.z));
        spherical_position.phi = RADIANS_TO_DEGREES(atan2(position.y, position.x));
#endif

        earth_radius = EARTH_RADIUS;

        camera_position = position;
        camera_position.y += 2.0f;

        // Projection matrix : 45° Field of View, aspect ratio, display range : 0.1 unit <-> 100 units
        ProjectionMatrix = glm::perspective(FoV, ASPECT_RATIO, 0.001f, 5000.0f + 2.0f * (GLfloat) earth_radius);
        // Camera matrix
        ViewMatrix = glm::lookAt(
                camera_position,           // Camera is here
                camera_position+direction, // and looks here : at the same position, plus "direction"
                up                         // Head is up (set to 0,-1,0 to look upside-down)
                );

        // For the next frame, the "last time" will be "now"
        lastTime = currentTime;
    }

    void Shader::bind_to_parent()
    {
        model::bind_child_to_parent<model::Shader*>(this, this->parent_pointer->shader_pointer_vector, this->parent_pointer->free_shaderID_queue);
    }

    Shader::Shader(ShaderStruct shader_struct)
    {
        // constructor.

        this->vertex_shader        = shader_struct.vertex_shader;
        this->fragment_shader      = shader_struct.fragment_shader;

        this->char_vertex_shader   = this->vertex_shader.c_str();
        this->char_fragment_shader = this->fragment_shader.c_str();
        this->parent_pointer        = static_cast<model::World*>(shader_struct.parent_pointer);

        // get childID from the World and set pointer to this shader.
        this->bind_to_parent();

        // Create and compile our GLSL program from the shaders.
        this->programID = LoadShaders(this->char_vertex_shader, this->char_fragment_shader);

        // Get a handle for our "MVP" uniform.
        this->MatrixID = glGetUniformLocation(this->programID, "MVP");
        this->ViewMatrixID = glGetUniformLocation(this->programID, "V");
        this->ModelMatrixID = glGetUniformLocation(this->programID, "M");
    }

    Shader::~Shader()
    {
        // destructor.
        std::cout << "Shader with childID " << this->childID << " will be destroyed.\n";

        // destroy all textures of this shader.
        std::cout << "All textures of this shader will be destroyed.\n";
        delete_children<model::Texture*>(this->texture_pointer_vector);

        // set pointer to this shader to NULL.
        this->parent_pointer->set_shader_pointer(this->childID, NULL);

        glDeleteProgram(this->programID);
    }

    void Shader::render()
    {
        // [re]bind `programID` shader.
        glUseProgram(this->programID);

        glUniformMatrix4fv(this->ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]); // This one doesn't change between objects, so this can be done once for all objects that use "programID"

        // render Shader by calling `render()` function of each Texture.
        render_children<model::Texture*>(this->texture_pointer_vector);
    }

    void Shader::set_texture_pointer(GLuint childID, void* parent_pointer)
    {
        set_child_pointer(childID, parent_pointer, this->texture_pointer_vector, this->free_textureID_queue);
    }

    void* Shader::get_texture_pointer(GLuint childID)
    {
        return this->texture_pointer_vector[childID];
    }

    void Shader::bind_to_new_parent(model::World *new_world_pointer)
    {
        model::bind_child_to_new_parent<model::Shader*, model::World*>(this, new_world_pointer, this->parent_pointer->shader_pointer_vector, this->parent_pointer->free_shaderID_queue);
    }

    void Shader::set_world_species_pointer(void* world_species_pointer)
    {
        this->world_species_pointer = world_species_pointer;
        this->parent_pointer->set_world_species_pointer(this->world_species_pointer);
    }

    void Texture::bind_to_parent()
    {
        model::bind_child_to_parent<model::Texture*>(this, this->parent_pointer->texture_pointer_vector, this->parent_pointer->free_textureID_queue);
    }

    Texture::Texture(TextureStruct texture_struct)
    {
        // constructor.
        this->parent_pointer = static_cast<model::Shader*>(texture_struct.parent_pointer);

        this->texture_file_format = texture_struct.texture_file_format;
        this->texture_filename    = texture_struct.texture_filename;

        this->char_texture_file_format = this->texture_file_format.c_str();
        this->char_texture_filename    = this->texture_filename.c_str();

        // get childID from the Shader and set pointer to this texture.
        this->bind_to_parent();

        // Load the texture.
        if ((strcmp(this->char_texture_file_format, "bmp") == 0) || (strcmp(this->char_texture_file_format, "BMP") == 0))
        {
            this->texture = texture::load_BMP_texture(this->char_texture_filename);
        }
        else if ((strcmp(this->char_texture_file_format, "dds") == 0) || (strcmp(this->char_texture_file_format, "DDS") == 0))
        {
            this->texture = texture::load_DDS_texture(this->char_texture_filename);
        }
        else
        {
            std::cerr << "no texture was loaded!\n";
            std::cerr << "texture file format: " << this->texture_file_format << "\n";
        }

        // Get a handle for our "myTextureSampler" uniform.
        this->openGL_textureID = glGetUniformLocation(this->parent_pointer->programID, "myTextureSampler");
    }

    Texture::~Texture()
    {
        // destructor.
        std::cout << "Texture with childID " << this->childID << " will be destroyed.\n";

        // destroy all species of this texture.
        std::cout << "All species of this texture will be destroyed.\n";
        delete_children<model::Species*>(this->species_pointer_vector);

        glDeleteTextures(1, &this->texture);

        // set pointer to this texture to NULL.
        this->parent_pointer->set_texture_pointer(this->childID, NULL);
    }

    void Texture::render()
    {
        // Bind our texture in Texture Unit 0.
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->texture);
        // Set our "myTextureSampler" sampler to user Texture Unit 0.
        glUniform1i(this->openGL_textureID, 0);

        // render Texture by calling `render()` function of each Species and of each Font.
        render_children<model::Species*>(this->species_pointer_vector);
        render_children<model::Font*>(this->font_pointer_vector);
    }

    void Texture::set_species_pointer(GLuint childID, void* parent_pointer)
    {
        set_child_pointer(childID, parent_pointer, this->species_pointer_vector, this->free_speciesID_queue);
    }

    void* Texture::get_species_pointer(GLuint childID)
    {
        return this->species_pointer_vector[childID];
    }

    void Texture::bind_to_new_parent(model::Shader *new_shader_pointer)
    {
        model::bind_child_to_new_parent<model::Texture*, model::Shader*>(this, new_shader_pointer, this->parent_pointer->texture_pointer_vector, this->parent_pointer->free_textureID_queue);
    }

    void Texture::set_world_species_pointer(void* world_species_pointer)
    {
        this->world_species_pointer = world_species_pointer;
        this->parent_pointer->set_world_species_pointer(this->world_species_pointer);
    }

    Graph::Graph()
    {
        // constructor.
    }

    void Graph::set_node_pointer(GLuint childID, void* parent_pointer)
    {
        set_child_pointer(childID, parent_pointer, this->node_pointer_vector, this->free_nodeID_queue);
    }

    void* Graph::get_node_pointer(GLuint childID)
    {
        return this->node_pointer_vector[childID];
    }

    GLuint Graph::get_nodeID()
    {
        return get_childID(node_pointer_vector, free_nodeID_queue);
    }

    Graph::~Graph()
    {
        // destructor.
        std::cout << "This graph will be destroyed.\n";

        // destroy all nodes of this graph.
        std::cout << "All nodes of this graph will be destroyed.\n";
        delete_children<model::Node*>(this->node_pointer_vector);
    }

    void Node::bind_to_parent()
    {
        model::bind_child_to_parent<model::Node*>(this, this->parent_pointer->node_pointer_vector, this->parent_pointer->free_nodeID_queue);
    }

    Node::Node(NodeStruct node_struct)
    {
        // constructor.
        this->childID = node_struct.nodeID;
        this->coordinate_vector = node_struct.coordinate_vector;
        this->parent_pointer = static_cast<model::Graph*>(node_struct.parent_pointer);

        // set pointer to this node.
        this->parent_pointer->set_node_pointer(this->childID, this);

        // create all bidirectional links between this node and neighbor nodes.
        for (GLuint link_i = 0; link_i < this->neighbor_nodeIDs.size(); link_i++)
        {
            this->create_bidirectional_link(this->neighbor_nodeIDs[link_i]);
        }
    }

    Node::~Node()
    {
        // destructor.
        std::cout << "Node with childID " << this->childID << " will be destroyed.\n";

        // delete all bidirectional links.
        for (GLuint link_i = 0; link_i < this->neighbor_nodeIDs.size(); link_i++)
        {
            this->delete_bidirectional_link(this->neighbor_nodeIDs[link_i]);
        }

        // set pointer to this node to NULL.
        this->parent_pointer->set_node_pointer(this->childID, NULL);
    }

    void Node::create_unidirectional_link(GLuint nodeID)
    {
        // this method creates an unidirectional link.

        // check that a link not exist already.
        if (std::find(this->neighbor_nodeIDs.begin(), this->neighbor_nodeIDs.end(), nodeID) == this->neighbor_nodeIDs.end())
        {
            // OK, it does not exist yet,
            // so create a link from this node to destination node.
            this->neighbor_nodeIDs.push_back(nodeID);
        }
        // an alternative: create a link from this node to destination node without checking its prior existence.
        // this->neighbor_nodeIDs.push_back(nodeID);
    }

    void Node::create_bidirectional_link(GLuint nodeID)
    {
        // create a link from this node to destination node.
        this->create_unidirectional_link(nodeID);

        // create a link from destination node to this node.
        static_cast<model::Node*>(this->parent_pointer->get_node_pointer(childID))->create_unidirectional_link(this->childID);
    }

    void Node::delete_unidirectional_link(GLuint nodeID)
    {
        // this method deletes an unidirectional link.
        this->neighbor_nodeIDs.erase(std::remove(this->neighbor_nodeIDs.begin(), this->neighbor_nodeIDs.end(), nodeID), this->neighbor_nodeIDs.end());
    }

    void Node::delete_bidirectional_link(GLuint nodeID)
    {
        // this method deletes a bidirectional link.
        this->delete_unidirectional_link(nodeID);

        // delete a link from destination node to this node.
        static_cast<model::Node*>(this->parent_pointer->get_node_pointer(childID))->delete_unidirectional_link(this->childID);
    }

    // Transfering node to a new graph is similar to `bind_to_new_parent`, `bind_to_new_parent`, `bind_to_new_parent`,
    // but there is one important difference:
    // nodes have references (links) to other nodes, whereas shaders, species, and objects do not.
    // The easiest way would be to request new `nodeID` for each new node, and this will be probably be implemented first.
    // Another option would be to change only those `nodeID`'s for which there would be duplicate `nodeID`'s.
    // However, that may consume huge amounts of memory if a big object (eg. a terrain object) is split into several smaller objects.
    // Therefore a `nodeID_bias` needs to be defined for each graph, it will be used for reindexing.
    // If `Graph::get_nodeID` would cause overflow (2^32 = 4 294 967 295), it will instead give smallest current `nodeID` of the graph and decrement `nodeID_bias` by 1.

    void Node::bind_to_new_parent(model::Graph *new_graph_pointer)
    {
        model::bind_child_to_new_parent<model::Node*, model::Graph*>(this, new_graph_pointer, this->parent_pointer->node_pointer_vector, this->parent_pointer->free_nodeID_queue);
    }

    void Species::bind_to_parent()
    {
        model::bind_child_to_parent<model::Species*>(this, this->parent_pointer->species_pointer_vector, this->parent_pointer->free_speciesID_queue);
    }

    Species::Species(SpeciesStruct species_struct)
    {
        // constructor.
        this->is_world          = species_struct.is_world;
        this->model_file_format = species_struct.model_file_format;
        this->model_filename    = species_struct.model_filename;
        this->color_channel     = species_struct.color_channel;
        this->lightPos          = species_struct.lightPos;
        this->parent_pointer   = static_cast<model::Texture*>(species_struct.parent_pointer);

        this->char_model_file_format = this->model_file_format.c_str();
        this->char_model_filename    = this->model_filename.c_str();
        this->char_color_channel     = this->color_channel.c_str();

        // get childID from the Texture and set pointer to this species.
        this->bind_to_parent();

        // Get a handle for our buffers.
        this->vertexPosition_modelspaceID = glGetAttribLocation(this->parent_pointer->parent_pointer->programID, "vertexPosition_modelspace");
        this->vertexUVID = glGetAttribLocation(this->parent_pointer->parent_pointer->programID, "vertexUV");
        this->vertexNormal_modelspaceID = glGetAttribLocation(this->parent_pointer->parent_pointer->programID, "vertexNormal_modelspace");

        bool model_loading_result;

        if ((strcmp(this->char_model_file_format, "obj") == 0) || (strcmp(this->char_model_file_format, "OBJ") == 0))
        {
            model_loading_result = model::load_OBJ(this->char_model_filename, this->vertices, this->UVs, this->normals);
        }
        else if (strcmp(this->char_model_file_format, "SRTM") == 0)
        {
            double current_latitude_in_degrees;
            double current_longitude_in_degrees;
            current_latitude_in_degrees = -16.50f;
            current_longitude_in_degrees = -68.15f;

            model_loading_result = model::load_SRTM_world(
                    this->model_filename,
                    current_latitude_in_degrees,
                    current_longitude_in_degrees,
                    this->vertices,
                    this->UVs,
                    this->normals);
        }
        else if ((strcmp(this->char_model_file_format, "bmp") == 0) || (strcmp(this->char_model_file_format, "BMP") == 0))
        {
            model_loading_result = model::load_BMP_world(
                    this->model_filename,
                    this->vertices,
                    this->UVs,
                    this->normals,
                    this->image_width,
                    this->image_height,
                    this->color_channel);
        }
        else
        {
            std::cerr << "no model was loaded!\n";
            std::cerr << "model file format: " << this->model_file_format << "\n";
        }

        model::indexVBO(this->vertices, this->UVs, this->normals, this->indices, this->indexed_vertices, this->indexed_UVs, this->indexed_normals);

        // Load it into a VBO.
        glGenBuffers(1, &this->vertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, this->indexed_vertices.size() * sizeof(glm::vec3), &this->indexed_vertices[0], GL_STATIC_DRAW);

        glGenBuffers(1, &this->uvbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
        glBufferData(GL_ARRAY_BUFFER, this->indexed_UVs.size() * sizeof(glm::vec2), &this->indexed_UVs[0], GL_STATIC_DRAW);

        glGenBuffers(1, &this->normalbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, this->normalbuffer);
        glBufferData(GL_ARRAY_BUFFER, this->indexed_normals.size() * sizeof(glm::vec3), &this->indexed_normals[0], GL_STATIC_DRAW);

        glGenBuffers(1, &this->elementbuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->elementbuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0] , GL_STATIC_DRAW);

        // Get a handle for our "LightPosition" uniform.
        glUseProgram(this->parent_pointer->parent_pointer->programID);
        this->lightID = glGetUniformLocation(this->parent_pointer->parent_pointer->programID, "LightPosition_worldspace");

        if (this->is_world)
        {
            // set world species pointer so that it points to this species.
            // currently there can be only one world species (used in collision detection).
            this->parent_pointer->parent_pointer->parent_pointer->set_world_species_pointer(this);
        }

        // Compute the graph of this object type.
    }

    Species::~Species()
    {
        // destructor.
        std::cout << "Species with childID " << this->childID << " will be destroyed.\n";

        // destroy all objects of this species.
        std::cout << "All objects of this species will be destroyed.\n";
        delete_children<model::Object*>(this->object_pointer_vector);

        // Cleanup VBO, shader and texture.
        glDeleteBuffers(1, &this->vertexbuffer);
        glDeleteBuffers(1, &this->uvbuffer);
        glDeleteBuffers(1, &this->normalbuffer);
        glDeleteBuffers(1, &this->elementbuffer);

        // set pointer to this species to NULL.
        this->parent_pointer->set_species_pointer(this->childID, NULL);
    }

    void Species::render()
    {
        // Compute the MVP matrix from keyboard and mouse input.
        glUniform3f(this->lightID, this->lightPos.x, this->lightPos.y, this->lightPos.z);

        // 1st attribute buffer : vertices.
        glEnableVertexAttribArray(this->vertexPosition_modelspaceID);

        // 2nd attribute buffer : UVs.
        glEnableVertexAttribArray(this->vertexUVID);

        // 3rd attribute buffer : normals.
        glEnableVertexAttribArray(this->vertexNormal_modelspaceID);

        // render Species by calling `render()` function of each Object.
        render_children<model::Object*>(this->object_pointer_vector);

        glDisableVertexAttribArray(this->vertexPosition_modelspaceID);
        glDisableVertexAttribArray(this->vertexUVID);
        glDisableVertexAttribArray(this->vertexNormal_modelspaceID);
    }

    void Species::set_object_pointer(GLuint childID, void* parent_pointer)
    {
        set_child_pointer(childID, parent_pointer, this->object_pointer_vector, this->free_objectID_queue);
    }

    void* Species::get_object_pointer(GLuint childID)
    {
        return this->object_pointer_vector[childID];
    }

    void Species::bind_to_new_parent(model::Texture *new_texture_pointer)
    {
        model::bind_child_to_new_parent<model::Species*, model::Texture*>(this, new_texture_pointer, this->parent_pointer->species_pointer_vector, this->parent_pointer->free_speciesID_queue);
    }

    Font::Font(FontStruct font_struct)
    {
    }

    Font::~Font()
    {
    }

    void Font::render()
    {
    }

    void Object::bind_to_parent()
    {
        model::bind_child_to_parent<model::Object*>(this, this->parent_pointer->object_pointer_vector, this->parent_pointer->free_objectID_queue);
    }

    Object::Object(ObjectStruct object_struct)
    {
        // constructor.
        this->coordinate_vector     = object_struct.coordinate_vector;
        this->original_scale_vector = object_struct.original_scale_vector;
        this->rotate_angle          = object_struct.rotate_angle;
        this->rotate_vector         = object_struct.rotate_vector;
        this->translate_vector      = object_struct.translate_vector;
        this->has_entered           = false;
        this->parent_pointer       = static_cast<model::Species*>(object_struct.parent_pointer);

        // get childID from the Species and set pointer to this object.
        this->bind_to_parent();

        bool model_loading_result = false;
    }

    Object::~Object()
    {
        // destructor.
        std::cout << "Object with childID " << this->childID << " will be destroyed.\n";

        // set pointer to this object to NULL.
        this->parent_pointer->set_object_pointer(this->childID, NULL);
    }

    void Object::render()
    {
        if (!this->has_entered)
        {
            this->model_matrix = glm::translate(glm::mat4(1.0f), this->coordinate_vector);
            this->model_matrix = glm::scale(this->model_matrix, this->original_scale_vector);

            // store the new coordinates to be used in the next update.
            this->coordinate_vector = glm::vec3(model_matrix[0][0], model_matrix[1][1], model_matrix[2][2]);
            this->has_entered = true;
        }
        else
        {
            // create `rotation_matrix` using quaternions.
            glm::quat my_quaternion;
            my_quaternion = glm::quat(DEGREES_TO_RADIANS(this->rotate_vector));
            glm::mat4 rotation_matrix = glm::toMat4(my_quaternion);

            // rotate.
            // this->model_matrix = rotation_matrix * this->model_matrix;
            if (this->rotate_vector != glm::vec3(0.0f, 0.0f, 0.0f))
            {
                this->model_matrix = glm::rotate(this->model_matrix, this->rotate_angle, this->rotate_vector);
            }

            this->model_matrix = glm::translate(this->model_matrix, this->translate_vector);
            this->coordinate_vector = glm::vec3(model_matrix[0][0], model_matrix[1][1], model_matrix[2][2]);
        }

        this->MVP_matrix = ProjectionMatrix * ViewMatrix * this->model_matrix;

        // Send our transformation to the currently bound shader,
        // in the "MVP" uniform.
        glUniformMatrix4fv(this->parent_pointer->parent_pointer->parent_pointer->MatrixID, 1, GL_FALSE, &this->MVP_matrix[0][0]);
        glUniformMatrix4fv(this->parent_pointer->parent_pointer->parent_pointer->ModelMatrixID, 1, GL_FALSE, &this->model_matrix[0][0]);

        // 1st attribute buffer : vertices.
        glBindBuffer(GL_ARRAY_BUFFER, this->parent_pointer->vertexbuffer);
        glVertexAttribPointer(
                this->parent_pointer->vertexPosition_modelspaceID, // The attribute we want to configure
                3,                                                  // size
                GL_FLOAT,                                           // type
                GL_FALSE,                                           // normalized?
                0,                                                  // stride
                (void*) 0                                           // array buffer offset
                );

        // 2nd attribute buffer : UVs.
        glBindBuffer(GL_ARRAY_BUFFER, this->parent_pointer->uvbuffer);
        glVertexAttribPointer(
                this->parent_pointer->vertexUVID, // The attribute we want to configure
                2,                                 // size : U+V => 2
                GL_FLOAT,                          // type
                GL_FALSE,                          // normalized?
                0,                                 // stride
                (void*) 0                          // array buffer offset
                );

        // 3rd attribute buffer : normals.
        glBindBuffer(GL_ARRAY_BUFFER, this->parent_pointer->normalbuffer);
        glVertexAttribPointer(
                this->parent_pointer->vertexNormal_modelspaceID, // The attribute we want to configure
                3,                                                // size
                GL_FLOAT,                                         // type
                GL_FALSE,                                         // normalized?
                0,                                                // stride
                (void*) 0                                         // array buffer offset
                );

        // Index buffer.
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->parent_pointer->elementbuffer);

        // Draw the triangles!
        glDrawElements(
                GL_TRIANGLES,                          // mode
                this->parent_pointer->indices.size(), // count
                GL_UNSIGNED_INT,                       // type
                (void*) 0                              // element array buffer offset
                );
    }

    void Object::bind_to_new_parent(model::Species *new_species_pointer)
    {
        // set pointer to this object to NULL.
        this->parent_pointer->set_object_pointer(this->childID, NULL);

        this->parent_pointer = new_species_pointer;

        // get childID from the Species and set pointer to this object.
        this->bind_to_parent();
    }
}
