#ifndef __SHADER_HPP_INCLUDED
#define __SHADER_HPP_INCLUDED

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

#include "cpp/ylikuutio/common/globals.hpp"
#include "shader_loader.hpp"
#include "render_templates.hpp"
#include "cpp/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include standard headers
#include <string>    // std::string
#include <vector>    // std::vector
#include <queue>     // std::queue

namespace model
{
    class World;
    class Object;

    class Shader
    {
        public:
            // constructor.
            Shader(ShaderStruct shader_struct);

            // destructor.
            ~Shader();

            // this method sets pointer to this shader to nullptr, sets `parent_pointer` according to the input, and requests a new `childID` from the new world.
            void bind_to_new_parent(model::World *new_scene_pointer);

            friend class World;
            friend class Material;
            friend class Glyph;
            friend class Species;
            template<class T1>
                friend void render_children(std::vector<void*> &child_pointer_vector);
            template<class T1>
                friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<void*> &child_pointer_vector, std::queue<uint32_t> &free_childID_queue);
            template<class T1, class T2>
                friend void hierarchy::bind_child_to_new_parent(T1 child_pointer, T2 new_parent_pointer, std::vector<void*> &old_child_pointer_vector, std::queue<uint32_t> &old_free_childID_queue);
            template<class T1>
                friend void render_this_object(model::Object* object_pointer, model::Shader* shader_pointer);

        private:
            // this method renders all textures using this shader.
            void render();

            // this method sets a texture pointer.
            void set_texture_pointer(uint32_t childID, void* parent_pointer);

            // this method sets a world species pointer.
            void set_terrain_species_pointer(model::Species* terrain_species_pointer);

            model::World *parent_pointer;         // pointer to the world.

            GLuint programID;                     // shaders' programID, returned by `LoadShaders`.

            GLuint MatrixID;
            GLuint ViewMatrixID;
            GLuint ModelMatrixID;

            void bind_to_parent();

            model::Species* terrain_species_pointer; // pointer to world species (used in collision detection).

            uint32_t childID;                     // shader ID, returned by `model::World->get_shaderID()`.

            std::string vertex_shader;            // filename of vertex shader.
            std::string fragment_shader;          // filename of fragment shader.

            std::vector<void*> texture_pointer_vector;
            std::queue<uint32_t> free_textureID_queue;

            const char* char_vertex_shader;
            const char* char_fragment_shader;
    };
}

#endif
