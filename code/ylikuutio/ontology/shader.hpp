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
#include "shader_struct.hpp"
#include "render_templates.hpp"
#include "entity_templates.hpp"
#include "code/ylikuutio/loaders/shader_loader.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/common/pi.hpp"

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
    class Symbiosis;

    class Shader: public ontology::Entity
    {
        public:
            // constructor.
            Shader(const ShaderStruct shader_struct);

            // destructor.
            virtual ~Shader();

            // this method sets pointer to this `Shader` to nullptr, sets `parent_pointer` according to the input, and requests a new `childID` from the new `Scene`.
            void bind_to_new_parent(ontology::Scene* const new_scene_pointer);

            void set_name(std::string name);

            friend class Scene;
            friend class Symbiosis;
            friend class Material;
            friend class Glyph;
            friend class Species;
            template<class T1>
                friend void render_children(std::vector<T1>& child_pointer_vector);
            template<class T1>
                friend void set_name(std::string name, T1 entity);
            template<class T1>
                friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<int32_t>& free_childID_queue, int32_t* number_of_children);
            template<class T1, class T2>
                friend void hierarchy::bind_child_to_new_parent(T1 child_pointer, T2 new_parent_pointer, std::vector<T1>& old_child_pointer_vector, std::queue<int32_t>& old_free_childID_queue, int32_t* old_number_of_children);
            template<class T1>
                friend void render_this_object(ontology::Object* object_pointer, ontology::Shader* shader_pointer);

        private:
            void bind_to_parent();

            // this method renders all materials using this `Shader`.
            void render();

            int32_t get_number_of_children() override;

            int32_t get_number_of_descendants() override;

            // this method sets a `Material` pointer.
            void set_material_pointer(const int32_t childID, ontology::Material* const child_pointer);

            // this method sets a `Symbiosis` pointer.
            void set_symbiosis_pointer(const int32_t childID, ontology::Symbiosis* const child_pointer);

            // this method sets a scene species pointer.
            void set_terrain_species_pointer(ontology::Species* terrain_species_pointer);

            ontology::Scene* parent_pointer;      // pointer to `Scene`.

            GLuint programID;                     // this `Shader`'s `programID`, returned by `load_shaders`.

            GLuint MatrixID;
            GLuint ViewMatrixID;
            GLuint ModelMatrixID;

            ontology::Species* terrain_species_pointer; // pointer to scene species (used in collision detection).

            std::string vertex_shader;            // filename of vertex shader.
            std::string fragment_shader;          // filename of fragment shader.

            std::vector<ontology::Material*> material_pointer_vector;
            std::vector<ontology::Symbiosis*> symbiosis_pointer_vector;
            std::queue<int32_t> free_materialID_queue;
            std::queue<int32_t> free_symbiosisID_queue;
            int32_t number_of_materials;
            int32_t number_of_symbioses;

            const char* char_vertex_shader;
            const char* char_fragment_shader;
    };
}

#endif
