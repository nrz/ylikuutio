#ifndef __OBJECT_HPP_INCLUDED
#define __OBJECT_HPP_INCLUDED

#include "entity.hpp"
#include "shader.hpp"
#include "species.hpp"
#include "glyph.hpp"
#include "object_struct.hpp"
#include "render_templates.hpp"
#include "entity_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/common/globals.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

#ifndef __GLM_GTC_MATRIX_TRANSFORM_HPP_INCLUDED
#define __GLM_GTC_MATRIX_TRANSFORM_HPP_INCLUDED
#include <glm/gtc/matrix_transform.hpp>
#endif

#ifndef __GLM_GTC_QUATERNION_HPP_INCLUDED
#define __GLM_GTC_QUATERNION_HPP_INCLUDED
#include <glm/gtc/quaternion.hpp> // glm::quat
#endif

// Include standard headers
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace ontology
{
    class Species;
    class Glyph;

    class Object: public ontology::Entity
    {
        public:
            // constructor.
            Object(const ObjectStruct object_struct);

            // destructor.
            virtual ~Object();

            // this method sets pointer to this `Object` to nullptr, sets `parent_pointer` according to the input,
            // and requests a new `childID` from the new `Species` or from the new `Glyph`.
            void bind_to_new_parent(void* const new_parent_pointer);

            void set_name(const std::string& name);

            // Public callbacks (to be called from AI scripts written in
            // Chibi-Scheme). These are the functions that are available
            // for AI scripts. Ylikuutio will support scripting of game
            // agents using Chibi-Scheme. Ylikuutio does not predefine what
            // kind of games can be done with it. However, the callbacks
            // Ylikuutio provides mean these is more support for features
            // needing such callbacks. In particular, Ylikuutio supports
            // simulations of real-life phenomena.
            // TODO: implement public AI callbacks!

            // Command callbacks.

            // Set target towards which to move.
            static void set_dest(ontology::Object* const object, const float x, const float y, const float z);

            // Allied-object-centric-information callbacks.

            // Get x coordinate of `object`.
            static float get_x(const ontology::Object* const object);

            // Get y coordinate of `object`.
            static float get_y(const ontology::Object* const object);

            // Get z destination coordinate of `object`.
            static float get_z(const ontology::Object* const object);

            // Get x destination coordinate of `object`.
            static float get_dest_x(const ontology::Object* const object);

            // Get y destination coordinate of `object`.
            static float get_dest_y(const ontology::Object* const object);

            // Get z coordinate of `object`.
            static float get_dest_z(const ontology::Object* const object);

            // Allied-object-centric path and map information callbacks.

            // this method returns `true` if destination is visible, `false` otherwise.
            // destination may be visible directly (line of sight) or eg. by radar (without line of sight).
            static bool is_visible(const float x, const float y, const float z);

            // this method returns `true` if destination is visible with a line of sight for any own `Object`, `false` otherwise.
            static bool is_line_of_sight_for_any(const float x, const float y, const float z);

            // this method returns `true` if destination is visible with a line of sight for any own `Object`, `false` otherwise.
            static bool is_line_of_sight(const ontology::Object* const object, const float x, const float y, const float z);

            // this method returns `true` if there is any known ground path between `Object` and (x, y, z),  `false` otherwise.
            static bool is_ground_path_known(const ontology::Object* const object, const float x, const float y, const float z);

            // this method returns `true` if there is any known rail path between `Object` and (x, y, z),  `false` otherwise.
            static bool is_rail_path_known(const ontology::Object* const object, const float x, const float y, const float z);

            // this method returns `true` if there is known air path between objects, `false` otherwise.
            static bool is_air_path_known(const ontology::Object* const object, const float x, const float y, const float z);

            // this method returns `true` if there is known ballistic path between `Object` and (x, y, z), `false` otherwise.
            static bool is_ballistic_path_known(const ontology::Object* const object, const float x, const float y, const float z);

            // this method returns `true` if there may be ballistic path between objects, `false` otherwise.
            static bool may_have_ballistic_path(const ontology::Object* const object, const float x, const float y, const float z);

            // these functions return the coordinates of the farthest point
            static float get_closest_visible_ground_dest_x_towards(const ontology::Object* const object, const float x, const float y, const float z);
            static float get_closest_visible_ground_dest_y_towards(const ontology::Object* const object, const float x, const float y, const float z);
            static float get_closest_visible_ground_dest_z_towards(const ontology::Object* const object, const float x, const float y, const float z);

            // this method returns `true` if complete path is visible, `false` otherwise.
            static bool is_complete_ground_path_visible(const ontology::Object* const object, const float x, const float y, const float z);
            static bool is_complete_rail_path_visible(const ontology::Object* const object, const float x, const float y, const float z);
            static bool is_complete_air_path_visible(const ontology::Object* const object, const float x, const float y, const float z);
            static bool is_complete_ballistic_path_visible(const ontology::Object* const object, const float x, const float y, const float z);

            // these methods return the coordinates of the point closest to `object` from which there is known ballistic path to (x, y, z).
            static float get_nearest_known_ballistic_launch_site_x(const ontology::Object* const object, const float x, const float y, const float z);
            static float get_nearest_known_ballistic_launch_site_y(const ontology::Object* const object, const float x, const float y, const float z);
            static float get_nearest_known_ballistic_launch_site_z(const ontology::Object* const object, const float x, const float y, const float z);

            // these methods return the coordinates of the point closest to `object` from which there may be a ballistic path to (x, y, z).
            static float get_nearest_possible_ballistic_launch_site_x(const ontology::Object* const object, const float x, const float y, const float z);
            static float get_nearest_possible_ballistic_launch_site_y(const ontology::Object* const object, const float x, const float y, const float z);
            static float get_nearest_possible_ballistic_launch_site_z(const ontology::Object* const object, const float x, const float y, const float z);

            // this method returns `true` if there is known line of sight between (x1, y1, z1) and (x2, y2, z2).

            // Coordinate-centric path and map information callbacks.
            // The conditions for returning `true` match the conditions of the corresponding allied-object-centric callbacks.

            static bool is_line_of_sight_between_from(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
            static bool may_have_line_of_sight_between(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
            static bool is_ground_path_known_between(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
            static bool is_rail_path_known_between(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
            static bool is_air_path_known_between(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
            static bool is_ballistic_path_known(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
            static bool may_have_ballistic_path_between(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);

            static float get_nearest_known_ballistic_launch_site_x(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
            static float get_nearest_known_ballistic_launch_site_y(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
            static float get_nearest_known_ballistic_launch_site_z(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);

            static float get_nearest_possible_ballistic_launch_site_x(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
            static float get_nearest_possible_ballistic_launch_site_y(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
            static float get_nearest_possible_ballistic_launch_site_z(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);

            static float get_closest_visible_dest_x_towards(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
            static float get_closest_visible_dest_y_towards(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
            static float get_closest_visible_dest_z_towards(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);

            // Callbacks for looping through objects.
            static void* get_first_allied_object(ontology::Object* object);       // point `allied_iterator` to the first object, `nullptr` if N/A.
            static void* get_next_allied_object(ontology::Object* object);        // advance `allied_iterator`, `nullptr` if N/A.
            static void* get_first_other_allied_object(ontology::Object* object); // point `allied_other_iterator` to the first other object, `nullptr` if N/A.
            static void* get_next_other_allied_object(ontology::Object* object);  // advance `allied_other_iterator`, `nullptr` if N/A.
            static void* get_first_opponent_object(ontology::Object* object);     // point `opponent_iterator` to the first opponent, `nullptr` if N/A.
            static void* get_next_opponent_object(ontology::Object* object);      // advance `opponent_iterator`, `nullptr` if N/A.

            // Public callbacks end here.

            template<class T1>
                friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<int32_t>& free_childID_queue, int32_t* number_of_children);
            template<class T1, class T2>
                friend void hierarchy::bind_child_to_new_parent(T1 child_pointer, T2 new_parent_pointer, std::vector<T1>& old_child_pointer_vector, std::queue<int32_t>& old_free_childID_queue, int32_t* old_number_of_children);
            template<class T1>
                friend void render_children(std::vector<T1>& child_pointer_vector);
            template<class T1>
                friend void render_this_object(ontology::Object* object_pointer, ontology::Shader* shader_pointer);
            template<class T1>
                friend void set_name(std::string name, T1 entity);

        private:
            void bind_to_parent();

            // this method renders this `Object`.
            void render();

            int32_t get_number_of_children() override;

            int32_t get_number_of_descendants() override;

            // act according to this game/simulation object's programming.
            void act();

            ontology::Species* species_parent_pointer; // pointer to `Species`.
            ontology::Glyph* glyph_parent_pointer;     // pointer to `Glyph`.
            ontology::Text3D* text3D_parent_pointer;   // pointer to `Text3D`.
            bool is_character;
            bool quaternions_in_use;

            bool has_entered;
            bool should_ylikuutio_render_this_object;

            glm::vec3 coordinate_vector;           // coordinate vector.
            glm::vec3 original_scale_vector;       // original scale vector.
            GLfloat rotate_angle;                  // rotate angle.
            glm::vec3 rotate_vector;               // rotate vector.
            glm::vec3 translate_vector;            // translate vector.

            glm::vec3 dest_vector;                 // destination vector.

            // The rest fields are created in the constructor.
            glm::mat4 model_matrix;                // model matrix.
            glm::mat4 MVP_matrix;                  // model view projection matrix.
    };

    template<class T1>
        void render_this_object(ontology::Object* object_pointer, ontology::Shader* shader_pointer)
        {
            if (!object_pointer->has_entered)
            {
                object_pointer->model_matrix = glm::translate(glm::mat4(1.0f), object_pointer->coordinate_vector);
                object_pointer->model_matrix = glm::scale(object_pointer->model_matrix, object_pointer->original_scale_vector);

                // store the new coordinates to be used in the next update.
                object_pointer->coordinate_vector = glm::vec3(object_pointer->model_matrix[0][0], object_pointer->model_matrix[1][1], object_pointer->model_matrix[2][2]);
                object_pointer->has_entered = true;
            }
            else
            {
                // rotate.
                if (object_pointer->rotate_vector != glm::vec3(0.0f, 0.0f, 0.0f))
                {
                    if (object_pointer->quaternions_in_use)
                    {
                        // create `rotation_matrix` using quaternions.
                        glm::quat my_quaternion = glm::quat(DEGREES_TO_RADIANS(object_pointer->rotate_vector));
                        glm::mat4 rotation_matrix = glm::mat4_cast(my_quaternion);
                        object_pointer->model_matrix = rotation_matrix * object_pointer->model_matrix;
                    }
                    else
                    {
                        object_pointer->model_matrix = glm::rotate(object_pointer->model_matrix, object_pointer->rotate_angle, object_pointer->rotate_vector);
                    }
                }

                object_pointer->model_matrix = glm::translate(object_pointer->model_matrix, object_pointer->translate_vector);
                object_pointer->coordinate_vector = glm::vec3(object_pointer->model_matrix[0][0], object_pointer->model_matrix[1][1], object_pointer->model_matrix[2][2]);
            }

            object_pointer->MVP_matrix = object_pointer->universe_pointer->ProjectionMatrix * object_pointer->universe_pointer->ViewMatrix * object_pointer->model_matrix;

            // Send our transformation to the currently bound shader,
            // in the "MVP" uniform.
            glUniformMatrix4fv(shader_pointer->MatrixID, 1, GL_FALSE, &object_pointer->MVP_matrix[0][0]);
            glUniformMatrix4fv(shader_pointer->ModelMatrixID, 1, GL_FALSE, &object_pointer->model_matrix[0][0]);

            GLuint vertexbuffer;
            GLuint vertexPosition_modelspaceID;
            GLuint uvbuffer;
            GLuint vertexUVID;
            GLuint normalbuffer;
            GLuint vertexNormal_modelspaceID;
            GLuint elementbuffer;
            GLuint indices_size;

            if (object_pointer->is_character)
            {
                ontology::Glyph* parent_glyph = object_pointer->glyph_parent_pointer;
                vertexbuffer = parent_glyph->vertexbuffer;
                vertexPosition_modelspaceID = parent_glyph->vertexPosition_modelspaceID;
                uvbuffer = parent_glyph->uvbuffer;
                vertexUVID = parent_glyph->vertexUVID;
                normalbuffer = parent_glyph->normalbuffer;
                vertexNormal_modelspaceID = parent_glyph->vertexNormal_modelspaceID;
                elementbuffer = parent_glyph->elementbuffer;
                indices_size = parent_glyph->indices.size();
            }
            else
            {
                ontology::Species* parent_species = object_pointer->species_parent_pointer;
                vertexbuffer = parent_species->vertexbuffer;
                vertexPosition_modelspaceID = parent_species->vertexPosition_modelspaceID;
                uvbuffer = parent_species->uvbuffer;
                vertexUVID = parent_species->vertexUVID;
                normalbuffer = parent_species->normalbuffer;
                vertexNormal_modelspaceID = parent_species->vertexNormal_modelspaceID;
                elementbuffer = parent_species->elementbuffer;
                indices_size = parent_species->indices.size();
            }

            // 1st attribute buffer : vertices.
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glVertexAttribPointer(
                    vertexPosition_modelspaceID, // The attribute we want to configure
                    3,                           // size
                    GL_FLOAT,                    // type
                    GL_FALSE,                    // normalized?
                    0,                           // stride
                    (void*) 0                    // array buffer offset
                    );

            // 2nd attribute buffer : UVs.
            glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
            glVertexAttribPointer(
                    vertexUVID, // The attribute we want to configure
                    2,          // size : U+V => 2
                    GL_FLOAT,   // type
                    GL_FALSE,   // normalized?
                    0,          // stride
                    (void*) 0   // array buffer offset
                    );

            // 3rd attribute buffer : normals.
            glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
            glVertexAttribPointer(
                    vertexNormal_modelspaceID, // The attribute we want to configure
                    3,                         // size
                    GL_FLOAT,                  // type
                    GL_FALSE,                  // normalized?
                    0,                         // stride
                    (void*) 0                  // array buffer offset
                    );

            // Index buffer.
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

            // Draw the triangles!
            glDrawElements(
                    GL_TRIANGLES,    // mode
                    indices_size,    // count
                    GL_UNSIGNED_INT, // type
                    (void*) 0        // element array buffer offset
                    );
        }
}

#endif
