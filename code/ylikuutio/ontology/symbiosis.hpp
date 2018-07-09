#ifndef __SYMBIOSIS_HPP_INCLUDED
#define __SYMBIOSIS_HPP_INCLUDED
// `Symbiosis` consists usually of 2 or more different `SymbiontMaterial`s and 2 or more `SymbiontSpecies` bound to these `SymbiontMaterial`s.
// All `SymbiontSpecies` of the same `Symbiosis` use the same `Shader`.
//
// In the future, a new class `ShaderSymbiosis` may be created should need for such class arise.
// `ShaderSymbiosis` is like `Symbiosis`, but it contains also `SymbiontShader`s in addition to `SymbiontMaterial`s and `SymbiontSpecies`.

#include "entity.hpp"
#include "symbiosis_struct.hpp"
#include "material_struct.hpp"
#include "code/ylikuutio/loaders/symbiosis_loader.hpp"
#include "code/ylikuutio/loaders/symbiosis_loader_struct.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/file/file_loader.hpp"
#include <ofbx.h>

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

// OpenFBX wants `u8` == `unsigned char`.
typedef unsigned char u8;

// Include standard headers
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <unordered_map> // std::unordered_map
#include <vector>   // std::vector

namespace yli
{
    namespace ontology
    {
        class Shader;
        class SymbiontMaterial;
        class SymbiontSpecies;
        class Holobiont;

        class Symbiosis: public yli::ontology::Entity
        {
            public:
                void bind_symbiont_material(yli::ontology::SymbiontMaterial* const symbiont_material);
                void bind_holobiont(yli::ontology::Holobiont* const holobiont);

                void unbind_holobiont(const int32_t childID);

                // this method sets pointer to this `Symbiosis` to nullptr, sets `parent` according to the input, and requests a new `childID` from the new `Shader`.
                void bind_to_new_parent(yli::ontology::Shader* const new_shader_pointer);

                // constructor.
                Symbiosis(yli::ontology::Universe* universe, const SymbiosisStruct& symbiosis_struct)
                    : Entity(universe)
                {
                    // constructor.
                    this->parent = symbiosis_struct.parent;
                    this->model_filename = symbiosis_struct.model_filename;
                    this->model_file_format = symbiosis_struct.model_file_format;
                    this->triangulation_type = symbiosis_struct.triangulation_type;
                    this->light_position = symbiosis_struct.light_position;

                    this->number_of_symbiont_materials = 0;
                    this->number_of_holobionts = 0;
                    this->ofbx_mesh_count = 0;

                    // get `childID` from `Shader` and set pointer to this `Symbiosis`.
                    this->bind_to_parent();

                    this->child_vector_pointers_vector.push_back(&this->symbiont_material_pointer_vector);
                    this->child_vector_pointers_vector.push_back(&this->holobiont_pointer_vector);
                    this->type = "yli::ontology::Symbiosis*";

                    this->can_be_erased = true;
                }

                // destructor.
                virtual ~Symbiosis();

                void create_symbionts();

                // this method renders all `SymbiontMaterial`s belonging to this `Symbiosis`.
                void render();

                yli::ontology::Entity* get_parent() const override;

                int32_t get_number_of_children() const override;

                int32_t get_number_of_descendants() const override;

                const std::string& get_model_file_format();

                void set_symbiont_material_pointer(const int32_t childID, yli::ontology::SymbiontMaterial* const child_pointer);

                void set_holobiont_pointer(const int32_t childID, yli::ontology::Holobiont* const child_pointer);

                yli::ontology::SymbiontSpecies* get_symbiont_species(const int32_t biontID) const;
                GLuint get_vertex_position_modelspaceID(const int32_t biontID) const;
                GLuint get_vertexUVID(const int32_t biontID) const;
                GLuint get_vertex_normal_modelspaceID(const int32_t biontID) const;

                GLuint get_vertexbuffer(const int32_t biontID) const;
                GLuint get_uvbuffer(const int32_t biontID) const;
                GLuint get_normalbuffer(const int32_t biontID) const;
                GLuint get_elementbuffer(const int32_t biontID) const;

                std::vector<uint32_t> get_indices(const int32_t biontID) const;
                GLuint get_indices_size(const int32_t biontID) const;
                int32_t get_number_of_symbionts() const;
                bool has_texture(const int32_t biontID) const;
                GLuint get_texture(const int32_t biontID) const;
                GLuint get_openGL_textureID(const int32_t biontID) const;

                GLuint get_lightID(const int32_t biontID) const;
                glm::vec3 get_light_position(const int32_t biontID) const;

                template<class T1>
                    friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<int32_t>& free_childID_queue, int32_t* number_of_children);
                template<class T1, class T2>
                    friend void hierarchy::bind_child_to_new_parent(T1 child_pointer, T2 new_parent, std::vector<T1>& old_child_pointer_vector, std::queue<int32_t>& old_free_childID_queue, int32_t* old_number_of_children);

            private:
                void bind_to_parent();

                yli::ontology::Shader* parent; // pointer to `Shader`.

                std::string model_file_format;  // type of the model file, eg. `"fbx"`.
                std::string model_filename;     // filename of the model file.
                std::string triangulation_type;

                glm::vec3 light_position;       // light position.

                std::vector<yli::ontology::SymbiontMaterial*> symbiont_material_pointer_vector;
                std::vector<yli::ontology::Holobiont*> holobiont_pointer_vector;
                std::queue<int32_t> free_symbiont_materialID_queue;
                std::queue<int32_t> free_holobiontID_queue;
                int32_t number_of_symbiont_materials;
                int32_t number_of_holobionts;

                std::vector<std::vector<glm::vec3>> vertices;         // vertices of the object.
                std::vector<std::vector<glm::vec2>> uvs;              // UVs of the object.
                std::vector<std::vector<glm::vec3>> normals;          // normals of the object.

                std::vector<std::vector<uint32_t>> indices;           // the deleted vertices will be reused (though it is not required, if there's enough memory).
                std::vector<std::vector<glm::vec3>> indexed_vertices;
                std::vector<std::vector<glm::vec2>> indexed_uvs;
                std::vector<std::vector<glm::vec3>> indexed_normals;

                std::unordered_map<const ofbx::Texture*, std::vector<int32_t>> ofbx_diffuse_texture_mesh_map;
                std::vector<yli::ontology::SymbiontMaterial*> biontID_symbiont_material_vector;
                std::vector<yli::ontology::SymbiontSpecies*> biontID_symbiont_species_vector;
                std::vector<const ofbx::Mesh*> ofbx_meshes;
                std::vector<const ofbx::Texture*> ofbx_diffuse_texture_vector;
                std::vector<const ofbx::Texture*> ofbx_normal_texture_vector; // currently not in use.
                std::vector<const ofbx::Texture*> ofbx_count_texture_vector;  // currently not in use.
                int32_t ofbx_mesh_count;
        };
    }
}

#endif
