#ifndef __SHADER_HPP_INCLUDED
#define __SHADER_HPP_INCLUDED

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

#include "entity.hpp"
#include "shader_struct.hpp"
#include "render_templates.hpp"
#include "code/ylikuutio/loaders/shader_loader.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/common/global_variables.hpp"
#include "code/ylikuutio/common/globals.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include standard headers
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace ontology
{
    class Scene;
    class Material;
    class Object;

    class Shader: public Entity
    {
        public:
            // constructor.
            Shader(ShaderStruct shader_struct);

            // destructor.
            ~Shader();

            // this method sets pointer to this `Shader` to nullptr, sets `parent_pointer` according to the input, and requests a new `childID` from the new `Scene`.
            void bind_to_new_parent(ontology::Scene* new_scene_pointer);

            friend class Scene;
            friend class Material;
            friend class Glyph;
            friend class Species;
            template<class T1>
                friend void render_children(std::vector<T1>& child_pointer_vector);
            template<class T1>
                friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<uint32_t>& free_childID_queue);
            template<class T1, class T2>
                friend void hierarchy::bind_child_to_new_parent(T1 child_pointer, T2 new_parent_pointer, std::vector<T1>& old_child_pointer_vector, std::queue<uint32_t>& old_free_childID_queue);
            template<class T1>
                friend void render_this_object(ontology::Object* object_pointer, ontology::Shader* shader_pointer);

        private:
            // this method renders all materials using this `Shader`.
            void render();

            // this method sets a material pointer.
            void set_material_pointer(uint32_t childID, ontology::Material* child_pointer);

            // this method sets a scene species pointer.
            void set_terrain_species_pointer(ontology::Species* terrain_species_pointer);

            ontology::Scene* parent_pointer;         // pointer to `Scene`.

            GLuint programID;                     // this `Shader`'s `programID`, returned by `load_shaders`.

            GLuint MatrixID;
            GLuint ViewMatrixID;
            GLuint ModelMatrixID;

            void bind_to_parent();

            ontology::Species* terrain_species_pointer; // pointer to scene species (used in collision detection).

            uint32_t childID;                     // shader ID, returned by `ontology::Scene->get_shaderID()`.

            std::string vertex_shader;            // filename of vertex shader.
            std::string fragment_shader;          // filename of fragment shader.

            std::vector<ontology::Material*> material_pointer_vector;
            std::queue<uint32_t> free_materialID_queue;

            const char* char_vertex_shader;
            const char* char_fragment_shader;
    };
}

#endif
