// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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

#ifndef YLIKUUTIO_ONTOLOGY_SYMBIOSIS_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_SYMBIOSIS_HPP_INCLUDED
// `Symbiosis` consists usually of 2 or more different `SymbiontMaterial`s and 2 or more `SymbiontSpecies` bound to these `SymbiontMaterial`s.
// All `SymbiontSpecies` of the same `Symbiosis` use the same `Pipeline`.
//
// In the future, a new class `PipelineSymbiosis` may be created should need for such class arise.
// `PipelineSymbiosis` is like `Symbiosis`, but it contains also `SymbiontPipeline`s in addition to `SymbiontMaterial`s and `SymbiontSpecies`.

#include "entity.hpp"
#include "child_module.hpp"
#include "generic_parent_module.hpp"
#include "apprentice_module.hpp"
#include "generic_master_module.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.
#include <ofbx.h>

// Include GLM
#ifndef GLM_GLM_HPP_INCLUDED
#define GLM_GLM_HPP_INCLUDED
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

namespace yli::core
{
    class Application;
}

namespace yli::memory
{
    template<typename T1, std::size_t DataSize>
        class MemoryStorage;
}

namespace yli::ontology
{
    class GenericMasterModule;
    class Universe;
    class Ecosystem;
    class Scene;
    class Pipeline;
    class SymbiontMaterial;
    class SymbiontSpecies;
    class Holobiont;
    struct SymbiosisStruct;

    class Symbiosis final : public Entity
    {
        public:
            // Set pointer to `species` to `nullptr`, set parent according to the input,
            // and request a new childID from `new_parent`.
            static std::optional<yli::data::AnyValue> bind_to_new_ecosystem_parent(
                    Symbiosis& symbiosis,
                    Ecosystem& new_parent);

            // Set pointer to `symbiosis` to `nullptr`, set parent according to the input,
            // and request a new childID from `new_parent`.
            static std::optional<yli::data::AnyValue> bind_to_new_scene_parent(
                    Symbiosis& symbiosis,
                    Scene& new_parent);

            // Set pointer to `symbiosis` to `nullptr`, set pipeline according to the input,
            // and request a new apprenticeID from `new_pipeline`.
            static std::optional<yli::data::AnyValue> bind_to_new_pipeline(
                    Symbiosis& symbiosis,
                    Pipeline& new_pipeline) noexcept;

        private:
            Symbiosis(
                    yli::core::Application& application,
                    Universe& universe,
                    const SymbiosisStruct& symbiosis_struct,
                    GenericParentModule* const ecosystem_or_scene_parent_module,
                    GenericMasterModule* const pipeline_master_module);

            ~Symbiosis() = default;

        public:
            Symbiosis(const Symbiosis&) = delete;            // Delete copy constructor.
            Symbiosis& operator=(const Symbiosis&) = delete; // Delete copy assignment.

            Entity* get_parent() const override;

            Pipeline* get_pipeline() const;

            template<typename ChildType>
                GenericParentModule* get_generic_parent_module() = delete;

            template<typename ApprenticeType>
                GenericMasterModule* get_generic_master_module() = delete;

            std::size_t get_number_of_symbiont_materials() const;
            std::size_t get_number_of_symbiont_species() const;

            // this method renders all `SymbiontMaterial`s belonging to this `Symbiosis`.
            void render(const Scene* const target_scene);

            const std::string& get_model_file_format() const;

            SymbiontMaterial* get_symbiont_material(const std::size_t symbiont_material_i) const;
            SymbiontSpecies* get_symbiont_species(const std::size_t biontID) const;
            GLint get_vertex_position_modelspace_id(const std::size_t biontID) const;
            GLint get_vertex_uv_id(const std::size_t biontID) const;
            GLint get_vertex_normal_modelspace_id(const std::size_t biontID) const;

            uint32_t get_vertex_buffer(const std::size_t biontID) const;
            uint32_t get_uv_buffer(const std::size_t biontID) const;
            uint32_t get_normal_buffer(const std::size_t biontID) const;
            uint32_t get_element_buffer(const std::size_t biontID) const;

            std::vector<uint32_t> get_indices(const std::size_t biontID) const;
            std::size_t get_indices_size(const std::size_t biontID) const;
            std::size_t get_number_of_ofbx_meshes() const;
            bool has_texture(const std::size_t biontID) const;
            uint32_t get_texture(const std::size_t biontID) const;
            GLint get_openGL_textureID(const std::size_t biontID) const;

            template<typename T1, std::size_t DataSize>
                friend class yli::memory::MemoryStorage;

            ChildModule child_of_ecosystem_or_scene;
            GenericParentModule parent_of_symbiont_materials;
            ApprenticeModule apprentice_of_pipeline;
            GenericMasterModule master_of_holobionts;

            Scene* get_scene() const override;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            void create_symbionts();

            std::string model_filename;     // filename of the model file.
            std::string model_file_format;  // type of the model file, eg. `"fbx"`.

            std::vector<std::vector<glm::vec3>> vertices;         // vertices of the object.
            std::vector<std::vector<glm::vec2>> uvs;              // UVs of the object.
            std::vector<std::vector<glm::vec3>> normals;          // normals of the object.

            std::vector<std::vector<uint32_t>> indices;           // the deleted vertices will be reused (though it is not required, if there's enough memory).
            std::vector<std::vector<glm::vec3>> indexed_vertices;
            std::vector<std::vector<glm::vec2>> indexed_uvs;
            std::vector<std::vector<glm::vec3>> indexed_normals;

            std::unordered_map<const ofbx::Texture*, std::vector<int32_t>> ofbx_diffuse_texture_mesh_map;
            std::vector<SymbiontMaterial*> biontID_symbiont_material_vector;
            std::vector<SymbiontSpecies*> biontID_symbiont_species_vector;
            std::vector<const ofbx::Mesh*> ofbx_meshes;
            std::vector<const ofbx::Texture*> ofbx_diffuse_texture_vector;
            std::vector<const ofbx::Texture*> ofbx_normal_texture_vector;  // currently not in use.
            std::vector<const ofbx::Texture*> ofbx_count_texture_vector;   // currently not in use.
            std::size_t ofbx_mesh_count { 0 };                             // the value of `ofbx_mesh_count` comes from OpenFBX.
    };

    template<>
        inline GenericParentModule* Symbiosis::get_generic_parent_module<SymbiontMaterial>()
        {
            return &this->parent_of_symbiont_materials;
        }

    template<>
        inline GenericMasterModule* Symbiosis::get_generic_master_module<Holobiont>()
        {
            return &this->master_of_holobionts;
        }
}

#endif
