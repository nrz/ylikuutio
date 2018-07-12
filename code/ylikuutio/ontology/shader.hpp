#ifndef __SHADER_HPP_INCLUDED
#define __SHADER_HPP_INCLUDED

#ifndef PI
#define PI 3.14159265359f
#endif

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

#include "entity.hpp"
#include "glyph.hpp"
#include "shader_struct.hpp"
#include "render_templates.hpp"
#include "code/ylikuutio/loaders/shader_loader.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/common/pi.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include GLFW
#ifndef __GLFW3_H_INCLUDED
#define __GLFW3_H_INCLUDED
#include <GLFW/glfw3.h>
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace ontology
    {
        class Scene;
        class Material;
        class Symbiosis;

        class Shader: public yli::ontology::Entity
        {
            public:
                void bind_material(yli::ontology::Material* const material);
                void bind_symbiosis(yli::ontology::Symbiosis* const symbiosis);

                void unbind_material(const int32_t childID);
                void unbind_symbiosis(const int32_t childID);

                // this method sets pointer to this `Shader` to nullptr, sets `parent` according to the input, and requests a new `childID` from the new `Scene`.
                void bind_to_new_parent(yli::ontology::Scene* const new_scene_pointer);

                // constructor.
                Shader(yli::ontology::Universe* const universe, const ShaderStruct& shader_struct)
                    : Entity(universe)
                {
                    // constructor.

                    this->vertex_shader        = shader_struct.vertex_shader;
                    this->fragment_shader      = shader_struct.fragment_shader;

                    this->char_vertex_shader   = this->vertex_shader.c_str();
                    this->char_fragment_shader = this->fragment_shader.c_str();
                    this->parent               = shader_struct.parent;

                    this->terrain_species = nullptr;

                    this->number_of_materials = 0;
                    this->number_of_symbioses = 0;

                    // get `childID` from `Scene` and set pointer to this `Shader`.
                    this->bind_to_parent();

                    // Create and compile our GLSL program from the shaders.
                    this->programID = loaders::load_shaders(this->char_vertex_shader, this->char_fragment_shader);

                    // Get a handle for our "MVP" uniform.
                    this->MatrixID = glGetUniformLocation(this->programID, "MVP");
                    this->view_matrixID = glGetUniformLocation(this->programID, "V");
                    this->model_matrixID = glGetUniformLocation(this->programID, "M");

                    this->child_vector_pointers_vector.push_back(&this->material_pointer_vector);
                    this->child_vector_pointers_vector.push_back(&this->symbiosis_pointer_vector);
                    this->type = "yli::ontology::Shader*";

                    this->can_be_erased = true;
                }

                // destructor.
                virtual ~Shader();

                yli::ontology::Entity* get_parent() const override;

                // this method sets a `Material` pointer.
                void set_material_pointer(const int32_t childID, yli::ontology::Material* const child_pointer);

                // this method sets a `Symbiosis` pointer.
                void set_symbiosis_pointer(const int32_t childID, yli::ontology::Symbiosis* const child_pointer);

                // this method sets a scene species pointer.
                void set_terrain_species(yli::ontology::Species* const terrain_species);

                GLuint get_programID() const;
                GLuint get_matrixID() const;
                GLuint get_model_matrixID() const;

                template<class T1>
                    friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<int32_t>& free_childID_queue, std::size_t* number_of_children);
                template<class T1, class T2>
                    friend void hierarchy::bind_child_to_new_parent(T1 child_pointer, T2 new_parent, std::vector<T1>& old_child_pointer_vector, std::queue<int32_t>& old_free_childID_queue, std::size_t* old_number_of_children);
                template<class T1>
                    friend void render_children(const std::vector<T1>& child_pointer_vector);

            private:
                void bind_to_parent();

                // this method renders all materials using this `Shader`.
                void render();

                std::size_t get_number_of_children() const override;
                std::size_t get_number_of_descendants() const override;

                yli::ontology::Scene* parent;      // pointer to `Scene`.

                GLuint programID;                     // this `Shader`'s `programID`, returned by `load_shaders`.

                GLuint MatrixID;
                GLuint view_matrixID;
                GLuint model_matrixID;

                yli::ontology::Species* terrain_species;   // pointer to scene species (used in collision detection).

                std::string vertex_shader;            // filename of vertex shader.
                std::string fragment_shader;          // filename of fragment shader.

                std::vector<yli::ontology::Material*> material_pointer_vector;
                std::vector<yli::ontology::Symbiosis*> symbiosis_pointer_vector;
                std::queue<int32_t> free_materialID_queue;
                std::queue<int32_t> free_symbiosisID_queue;
                std::size_t number_of_materials;
                std::size_t number_of_symbioses;

                const char* char_vertex_shader;
                const char* char_fragment_shader;
        };
    }
}

#endif
