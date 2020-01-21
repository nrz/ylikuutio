// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef __SYMBIOSIS_HPP_INCLUDED
#define __SYMBIOSIS_HPP_INCLUDED
// `Symbiosis` consists usually of 2 or more different `SymbiontMaterial`s and 2 or more `SymbiontSpecies` bound to these `SymbiontMaterial`s.
// All `SymbiontSpecies` of the same `Symbiosis` use the same `Shader`.
//
// In the future, a new class `ShaderSymbiosis` may be created should need for such class arise.
// `ShaderSymbiosis` is like `Symbiosis`, but it contains also `SymbiontShader`s in addition to `SymbiontMaterial`s and `SymbiontSpecies`.

#include "entity.hpp"
#include "family_templates.hpp"
#include "symbiosis_struct.hpp"
#include "material_struct.hpp"
#include "code/ylikuutio/load/symbiosis_loader.hpp"
#include "code/ylikuutio/load/symbiosis_loader_struct.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/file/file_loader.hpp"
#include <ofbx.h>

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// OpenFBX wants `u8` == `unsigned char`.
typedef unsigned char u8;

// Include standard headers
#include <cstddef>       // std::size_t
#include <queue>         // std::queue
#include <stdint.h>      // uint32_t etc.
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

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
                void bind_SymbiontMaterial(yli::ontology::SymbiontMaterial* const symbiont_material);
                void bind_Holobiont(yli::ontology::Holobiont* const holobiont);

                void unbind_SymbiontMaterial(const std::size_t childID);
                void unbind_Holobiont(const std::size_t childID);

                // this method sets pointer to this `Symbiosis` to `nullptr`, sets `parent` according to the input, and requests a new `childID` from the new `Shader`.
                void bind_to_new_parent(yli::ontology::Shader* const new_parent);
                void bind_to_new_parent(yli::ontology::Entity* const new_parent) override;

                // constructor.
                Symbiosis(yli::ontology::Universe* universe, const yli::ontology::SymbiosisStruct& symbiosis_struct)
                    : Entity(universe)
                {
                    // constructor.
                    this->parent                       = symbiosis_struct.parent;
                    this->model_filename               = symbiosis_struct.model_filename;
                    this->model_file_format            = symbiosis_struct.model_file_format;
                    this->triangulation_type           = symbiosis_struct.triangulation_type;
                    this->light_position               = symbiosis_struct.light_position;

                    this->number_of_symbiont_materials = 0;
                    this->number_of_holobionts         = 0;
                    this->ofbx_mesh_count              = 0;
                    this->opengl_in_use                = symbiosis_struct.opengl_in_use;

                    // get `childID` from `Shader` and set pointer to this `Symbiosis`.
                    this->bind_to_parent();

                    this->create_symbionts();

                    // `yli::ontology::Entity` member variables begin here.
                    this->type_string = "yli::ontology::Symbiosis*";
                    this->can_be_erased = true;
                }

                Symbiosis(const Symbiosis&) = delete;            // Delete copy constructor.
                Symbiosis &operator=(const Symbiosis&) = delete; // Delete copy assignment.

                // destructor.
                virtual ~Symbiosis();

                yli::ontology::Entity* get_parent() const override;
                std::size_t get_number_of_children() const override;
                std::size_t get_number_of_descendants() const override;

                std::size_t get_number_of_symbiont_materials() const;
                std::size_t get_number_of_symbiont_species() const;

                // this method renders all `SymbiontMaterial`s belonging to this `Symbiosis`.
                void render() override;

                const std::string& get_model_file_format() const;

                yli::ontology::SymbiontMaterial* get_symbiont_material(const std::size_t symbiont_material_i) const;
                yli::ontology::SymbiontSpecies* get_symbiont_species(const std::size_t biontID) const;
                GLint get_vertex_position_modelspaceID(const std::size_t biontID) const;
                GLint get_vertexUVID(const std::size_t biontID) const;
                GLint get_vertex_normal_modelspaceID(const std::size_t biontID) const;

                uint32_t get_vertexbuffer(const std::size_t biontID) const;
                uint32_t get_uvbuffer(const std::size_t biontID) const;
                uint32_t get_normalbuffer(const std::size_t biontID) const;
                uint32_t get_elementbuffer(const std::size_t biontID) const;

                std::vector<uint32_t> get_indices(const std::size_t biontID) const;
                std::size_t get_indices_size(const std::size_t biontID) const;
                std::size_t get_number_of_ofbx_meshes() const;
                bool has_texture(const std::size_t biontID) const;
                uint32_t get_texture(const std::size_t biontID) const;
                GLint get_openGL_textureID(const std::size_t biontID) const;

                GLint get_lightID(const std::size_t biontID) const;
                const glm::vec3& get_light_position(const std::size_t biontID) const;

                template<class T1>
                    friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);

            private:
                void bind_to_parent();

                void create_symbionts();

                yli::ontology::Shader* parent; // pointer to `Shader`.

                std::string model_file_format;  // type of the model file, eg. `"fbx"`.
                std::string model_filename;     // filename of the model file.
                std::string triangulation_type;

                glm::vec3 light_position;       // light position.

                std::vector<yli::ontology::SymbiontMaterial*> symbiont_material_pointer_vector;
                std::vector<yli::ontology::Holobiont*> holobiont_pointer_vector;
                std::queue<std::size_t> free_symbiont_materialID_queue;
                std::queue<std::size_t> free_holobiontID_queue;
                std::size_t number_of_symbiont_materials;
                std::size_t number_of_holobionts;

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
                std::vector<const ofbx::Texture*> ofbx_normal_texture_vector;  // currently not in use.
                std::vector<const ofbx::Texture*> ofbx_count_texture_vector;   // currently not in use.
                std::size_t ofbx_mesh_count;                                   // the value of `ofbx_mesh_count` comes from OpenFBX.

                bool opengl_in_use;
        };
    }
}

#endif
