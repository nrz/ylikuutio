// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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

#ifndef __YLIKUUTIO_ONTOLOGY_SYMBIOSIS_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_SYMBIOSIS_HPP_INCLUDED
// `Symbiosis` consists usually of 2 or more different `SymbiontMaterial`s and 2 or more `SymbiontSpecies` bound to these `SymbiontMaterial`s.
// All `SymbiontSpecies` of the same `Symbiosis` use the same `Shader`.
//
// In the future, a new class `ShaderSymbiosis` may be created should need for such class arise.
// `ShaderSymbiosis` is like `Symbiosis`, but it contains also `SymbiontShader`s in addition to `SymbiontMaterial`s and `SymbiontSpecies`.

#include "entity.hpp"
#include "child_module.hpp"
#include "generic_parent_module.hpp"
#include "apprentice_module.hpp"
#include "generic_master_module.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.
#include <ofbx.h>

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// OpenFBX wants `u8` == `unsigned char`.
typedef unsigned char u8;

// Include standard headers
#include <cstddef>       // std::size_t
#include <optional>      // std::optional
#include <stdint.h>      // uint32_t etc.
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

namespace yli::ontology
{
    class GenericMasterModule;
    class Universe;
    class Ecosystem;
    class Scene;
    class Shader;
    class SymbiontMaterial;
    class SymbiontSpecies;
    struct ModelStruct;

    class Symbiosis final : public yli::ontology::Entity
    {
        public:
            // Set pointer to `species` to `nullptr`, set parent according to the input,
            // and request a new childID from `new_parent`.
            static std::optional<yli::data::AnyValue> bind_to_new_ecosystem_parent(yli::ontology::Symbiosis& symbiosis, yli::ontology::Ecosystem& new_parent);

            // Set pointer to `symbiosis` to `nullptr`, set parent according to the input,
            // and request a new childID from `new_parent`.
            static std::optional<yli::data::AnyValue> bind_to_new_scene_parent(yli::ontology::Symbiosis& symbiosis, yli::ontology::Scene& new_parent);

            // Set pointer to `symbiosis` to `nullptr`, set shader according to the input,
            // and request a new apprenticeID from `new_shader`.
            static std::optional<yli::data::AnyValue> bind_to_new_shader(yli::ontology::Symbiosis& symbiosis, yli::ontology::Shader& new_shader);

            Symbiosis(
                    yli::ontology::Universe& universe,
                    const yli::ontology::ModelStruct& model_struct,
                    yli::ontology::GenericParentModule* const scene_parent_module,
                    yli::ontology::GenericMasterModule* const shader_master);

            Symbiosis(const Symbiosis&) = delete;            // Delete copy constructor.
            Symbiosis& operator=(const Symbiosis&) = delete; // Delete copy assignment.

            // destructor.
            ~Symbiosis() = default;

            yli::ontology::Entity* get_parent() const override;

            yli::ontology::Shader* get_shader() const;

            std::size_t get_number_of_symbiont_materials() const;
            std::size_t get_number_of_symbiont_species() const;

            // this method renders all `SymbiontMaterial`s belonging to this `Symbiosis`.
            void render(const yli::ontology::Scene* const target_scene);

            const std::string& get_model_file_format() const;

            yli::ontology::SymbiontMaterial* get_symbiont_material(const std::size_t symbiont_material_i) const;
            yli::ontology::SymbiontSpecies* get_symbiont_species(const std::size_t biontID) const;
            GLint get_vertex_position_modelspace_id(const std::size_t biontID) const;
            GLint get_vertex_uv_id(const std::size_t biontID) const;
            GLint get_vertex_normal_modelspace_id(const std::size_t biontID) const;

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

            yli::ontology::ChildModule child_of_scene_or_ecosystem;
            yli::ontology::GenericParentModule parent_of_symbiont_materials;
            yli::ontology::ApprenticeModule apprentice_of_shader;
            yli::ontology::GenericMasterModule master_of_holobionts;

            yli::ontology::Scene* get_scene() const override;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            void create_symbionts();

            std::string model_filename;     // filename of the model file.
            std::string model_file_format;  // type of the model file, eg. `"fbx"`.
            std::string triangulation_type;

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
            std::size_t ofbx_mesh_count { 0 };                             // the value of `ofbx_mesh_count` comes from OpenFBX.
    };
}

#endif
