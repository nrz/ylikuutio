// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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

#include "symbiosis.hpp"
#include "universe.hpp"
#include "ecosystem.hpp"
#include "scene.hpp"
#include "pipeline.hpp"
#include "symbiont_material.hpp"
#include "symbiont_species.hpp"
#include "generic_entity_factory.hpp"
#include "material_struct.hpp"
#include "model_struct.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/core/application.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/data/datatype.hpp"
#include "code/ylikuutio/load/symbiosis_loader.hpp"
#include "code/ylikuutio/load/model_loader_struct.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.
#include "code/ylikuutio/render/render_system.hpp"
#include "code/ylikuutio/render/render_templates.hpp"
#include <ofbx.h>

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstdint>   // std::uintptr_t
#include <cstddef>   // std::size_t
#include <ios>       // std::hex
#include <iostream>  // std::cout, std::cerr
#include <optional>  // std::optional
#include <sstream>   // std::stringstream
#include <stdexcept> // std::runtime_error
#include <stdint.h>  // uint32_t etc.
#include <string>    // std::string
#include <vector>    // std::vector

namespace yli::ontology
{
    class Entity;

    std::optional<yli::data::AnyValue> Symbiosis::bind_to_new_ecosystem_parent(
            yli::ontology::Symbiosis& symbiosis,
            yli::ontology::Ecosystem& new_parent)
    {
        // Set pointer to `Symbiosis` to `nullptr`, set parent according to the input,
        // and request a new childID from `new_parent`.

        const yli::ontology::Entity* const old_ecosystem_or_scene_parent = symbiosis.get_parent();

        if (old_ecosystem_or_scene_parent == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Symbiosis::bind_to_new_ecosystem_parent`: `old_ecosystem_or_scene_parent` is `nullptr`!");
        }

        if (&new_parent == old_ecosystem_or_scene_parent)
        {
            // Setting current parent as the new parent. Nothing to do.
            return std::nullopt;
        }

        if (new_parent.has_child(symbiosis.local_name))
        {
            std::cerr << "ERROR: `Symbiosis::bind_to_new_ecosystem_parent`: local name is already in use!\n";
            return std::nullopt;
        }

        // `Ecosystem`s do not care in which `Ecosystem`s their apprentices reside,
        // so binding to an `Ecosystem` does not unbind any apprentices.
        symbiosis.child_of_ecosystem_or_scene.unbind_and_bind_to_new_parent(
                &new_parent.parent_of_symbioses);

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Symbiosis::bind_to_new_scene_parent(
            yli::ontology::Symbiosis& symbiosis,
            yli::ontology::Scene& new_parent)
    {
        // Set pointer to `symbiosis` to `nullptr`, set parent according to the input,
        // and request a new childID from `new_parent`.

        const yli::ontology::Entity* const old_ecosystem_or_scene_parent = symbiosis.get_parent();

        if (old_ecosystem_or_scene_parent == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Symbiosis::bind_to_new_scene_parent`: `old_ecosystem_or_scene_parent` is `nullptr`!");
        }

        if (&new_parent == old_ecosystem_or_scene_parent)
        {
            // Setting current parent as the new parent. Nothing to do.
            return std::nullopt;
        }

        if (new_parent.has_child(symbiosis.local_name))
        {
            std::cerr << "ERROR: `Symbiosis::bind_to_new_scene_parent`: local name is already in use!\n";
            return std::nullopt;
        }

        symbiosis.apprentice_of_pipeline.unbind_from_any_master_belonging_to_other_scene(new_parent);
        symbiosis.child_of_ecosystem_or_scene.unbind_and_bind_to_new_parent(
                &new_parent.parent_of_symbioses);

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Symbiosis::bind_to_new_pipeline(
            yli::ontology::Symbiosis& symbiosis,
            yli::ontology::Pipeline& new_pipeline) noexcept
    {
        // Set pointer to `symbiosis` to `nullptr`, set pipeline according to the input,
        // and request a new apprenticeID from `new_pipeline`.

        // All apprentices of a master must belong to the same `Scene`
        // as the master if the master belongs to some `Scene`.
        if (symbiosis.get_scene() == new_pipeline.get_scene() ||
                new_pipeline.get_scene() == nullptr)
        {
            symbiosis.apprentice_of_pipeline.unbind_and_bind_to_new_generic_master_module(
                    &new_pipeline.master_of_symbioses);
        }
        else
        {
            std::cerr << "ERROR: `Symbiosis::bind_to_new_pipeline`: master and apprentice can not belong to different `Scene`s!\n";
        }

        return std::nullopt;
    }

    Symbiosis::Symbiosis(
            yli::core::Application& application,
            yli::ontology::Universe& universe,
            const yli::ontology::ModelStruct& model_struct,
            yli::ontology::GenericParentModule* const ecosystem_or_scene_parent_module,
            yli::ontology::GenericMasterModule* const pipeline_master_module)
        : Entity(application, universe, model_struct),
        child_of_ecosystem_or_scene(ecosystem_or_scene_parent_module, *this),
        parent_of_symbiont_materials(
                *this,
                this->registry,
                application.get_memory_allocator(yli::data::Datatype::SYMBIONT_MATERIAL),
                "symbiont_materials"),
        apprentice_of_pipeline(pipeline_master_module, this),
        master_of_holobionts(this, &this->registry, "holobionts"),
        model_filename     { model_struct.model_filename },
        model_file_format  { model_struct.model_file_format }
    {
        // constructor.

        this->create_symbionts();

        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "yli::ontology::Symbiosis*";
        this->can_be_erased = true;
    }

    void Symbiosis::render(const yli::ontology::Scene* const target_scene)
    {
        if (!this->should_be_rendered)
        {
            return;
        }

        yli::ontology::Scene* const scene = this->get_scene();

        if (target_scene != nullptr && scene != nullptr && scene != target_scene)
        {
            // Different `Scene`s, do not render.
            return;
        }

        const yli::ontology::Scene* const new_target_scene = (target_scene != nullptr ? target_scene : scene);

        yli::render::RenderSystem* const render_system = this->universe.get_render_system();

        if (render_system == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Symbiosis::render`: `render_system` is `nullptr`!");
        }

        render_system->render_holobionts(this->master_of_holobionts, new_target_scene);
    }

    std::size_t Symbiosis::get_number_of_symbiont_materials() const
    {
        return this->parent_of_symbiont_materials.get_number_of_children();
    }

    std::size_t Symbiosis::get_number_of_symbiont_species() const
    {
        std::size_t number_of_symbiont_species = 0;

        for (const auto& symbiont_material : this->parent_of_symbiont_materials.child_pointer_vector)
        {
            number_of_symbiont_species += symbiont_material->get_number_of_all_children();
        }

        return number_of_symbiont_species;
    }

    yli::ontology::Entity* Symbiosis::get_parent() const
    {
        return this->child_of_ecosystem_or_scene.get_parent();
    }

    yli::ontology::Pipeline* Symbiosis::get_pipeline() const
    {
        return static_cast<yli::ontology::Pipeline*>(this->apprentice_of_pipeline.get_master());
    }

    yli::ontology::Scene* Symbiosis::get_scene() const
    {
        return this->child_of_ecosystem_or_scene.get_scene();
    }

    std::size_t Symbiosis::get_number_of_children() const
    {
        return this->parent_of_symbiont_materials.get_number_of_children();
    }

    std::size_t Symbiosis::get_number_of_descendants() const
    {
        return yli::ontology::get_number_of_descendants(this->parent_of_symbiont_materials.child_pointer_vector);
    }

    const std::string& Symbiosis::get_model_file_format() const
    {
        return this->model_file_format;
    }

    void Symbiosis::create_symbionts()
    {
        yli::load::ModelLoaderStruct model_loader_struct;
        model_loader_struct.model_struct.model_filename = this->model_filename;
        model_loader_struct.model_struct.model_file_format = this->model_file_format;

        const bool is_debug_mode = true;

        if (yli::load::load_symbiosis(
                    model_loader_struct,
                    this->vertices,
                    this->uvs,
                    this->normals,
                    this->ofbx_diffuse_texture_mesh_map,
                    this->ofbx_meshes,
                    this->ofbx_diffuse_texture_vector,
                    this->ofbx_normal_texture_vector,
                    this->ofbx_count_texture_vector,
                    this->ofbx_mesh_count,
                    is_debug_mode))
        {
            std::cout << "number of meshes: " << this->ofbx_mesh_count << "\n";

            std::vector<const ofbx::Texture*> ofbx_diffuse_texture_pointer_vector;
            ofbx_diffuse_texture_pointer_vector.reserve(this->ofbx_diffuse_texture_mesh_map.size());
            this->biontID_symbiont_material_vector.resize(this->ofbx_mesh_count);

            this->biontID_symbiont_species_vector.resize(this->ofbx_mesh_count);

            for (const auto& key_and_value : this->ofbx_diffuse_texture_mesh_map)
            {
                ofbx_diffuse_texture_pointer_vector.emplace_back(key_and_value.first); // key.
            }

            yli::ontology::Pipeline* const pipeline = this->get_pipeline();

            if (pipeline == nullptr) [[unlikely]]
            {
                throw std::runtime_error("ERROR: `Symbiosis::create_symbionts`: `pipeline` is `nullptr`!");
            }

            // Create `SymbiontMaterial`s.
            for (const ofbx::Texture* const ofbx_texture : ofbx_diffuse_texture_pointer_vector)
            {
                if (ofbx_texture == nullptr)
                {
                    continue;
                }

                const std::uintptr_t memory_address = reinterpret_cast<std::uintptr_t>(ofbx_texture);
                std::stringstream memory_address_stringstream;
                memory_address_stringstream << "0x" << std::hex << memory_address;

                std::cout << "Creating `SymbiontMaterial*` based on `ofbx::Texture*` at 0x" << memory_address_stringstream.str() << " ...\n";
                yli::ontology::MaterialStruct material_struct;
                material_struct.pipeline = pipeline;
                material_struct.parent = this;
                material_struct.ofbx_texture = ofbx_texture;

                yli::ontology::GenericEntityFactory& entity_factory = this->application.get_generic_entity_factory();
                auto symbiont_material = entity_factory.create_symbiont_material(material_struct);

                std::cout << "yli::ontology::SymbiontMaterial* successfully created.\n";

                // Create `SymbiontSpecies`s.
                // Care only about `ofbx::Texture*`s which are DIFFUSE textures.
                for (const std::size_t mesh_i : this->ofbx_diffuse_texture_mesh_map.at(ofbx_texture))
                {
                    yli::ontology::ModelStruct model_struct;
                    model_struct.model_filename = this->model_filename;
                    model_struct.model_file_format = this->model_file_format;
                    model_struct.pipeline = pipeline;
                    model_struct.symbiont_material = symbiont_material;
                    model_struct.vertex_count = mesh_i < this->vertices.size() ? this->vertices.at(mesh_i).size() : 0;
                    model_struct.vertices = mesh_i < this->vertices.size() ? this->vertices.at(mesh_i) : std::vector<glm::vec3>();
                    model_struct.uvs = mesh_i < this->uvs.size() ? this->uvs.at(mesh_i) : std::vector<glm::vec2>();
                    model_struct.normals = mesh_i < this->normals.size() ? this->normals.at(mesh_i) : std::vector<glm::vec3>();
                    model_struct.mesh_i = mesh_i;

                    std::cout << "Creating yli::ontology::SymbiontSpecies*, mesh index " << mesh_i << "...\n";

                    auto symbiont_species = entity_factory.create_symbiont_species(model_struct);

                    std::cout << "yli::ontology::SymbiontSpecies*, mesh index " << mesh_i << " successfully created.\n";

                    std::cout << "storing yli::ontology::SymbiontMaterial* symbiont_material into vector with mesh_i " << mesh_i << " ...\n";
                    this->biontID_symbiont_material_vector.at(mesh_i) = symbiont_material;
                    std::cout << "storing yli::ontology::SymbiontSpecies* symbiont_species into vector with mesh_i " << mesh_i << " ...\n";
                    this->biontID_symbiont_species_vector.at(mesh_i) = symbiont_species;

                    std::cout << "Success.\n";
                }
            }

            std::cout << "All symbionts successfully created.\n";
        }
    }

    yli::ontology::SymbiontMaterial* Symbiosis::get_symbiont_material(const std::size_t symbiont_material_i) const
    {
        if (symbiont_material_i >= this->parent_of_symbiont_materials.child_pointer_vector.size())
        {
            return nullptr;
        }

        return static_cast<yli::ontology::SymbiontMaterial*>(
                this->parent_of_symbiont_materials.child_pointer_vector.at(symbiont_material_i));
    }

    yli::ontology::SymbiontSpecies* Symbiosis::get_symbiont_species(const std::size_t biontID) const
    {
        if (biontID >= this->biontID_symbiont_species_vector.size())
        {
            return nullptr;
        }

        return this->biontID_symbiont_species_vector.at(biontID);
    }

    GLint Symbiosis::get_vertex_position_modelspace_id(const std::size_t biontID) const
    {
        return this->biontID_symbiont_species_vector.at(biontID)->mesh.get_vertex_position_modelspace_id();
    }

    GLint Symbiosis::get_vertex_uv_id(const std::size_t biontID) const
    {
        return this->biontID_symbiont_species_vector.at(biontID)->mesh.get_vertex_uv_id();
    }

    GLint Symbiosis::get_vertex_normal_modelspace_id(const std::size_t biontID) const
    {
        return this->biontID_symbiont_species_vector.at(biontID)->mesh.get_vertex_normal_modelspace_id();
    }

    uint32_t Symbiosis::get_vertexbuffer(const std::size_t biontID) const
    {
        return this->biontID_symbiont_species_vector.at(biontID)->mesh.get_vertexbuffer();
    }

    uint32_t Symbiosis::get_uvbuffer(const std::size_t biontID) const
    {
        return this->biontID_symbiont_species_vector.at(biontID)->mesh.get_uvbuffer();
    }

    uint32_t Symbiosis::get_normalbuffer(const std::size_t biontID) const
    {
        return this->biontID_symbiont_species_vector.at(biontID)->mesh.get_normalbuffer();
    }

    uint32_t Symbiosis::get_elementbuffer(const std::size_t biontID) const
    {
        return this->biontID_symbiont_species_vector.at(biontID)->mesh.get_elementbuffer();
    }

    std::vector<uint32_t> Symbiosis::get_indices(const std::size_t biontID) const
    {
        return this->biontID_symbiont_species_vector.at(biontID)->mesh.get_indices();
        // return this->indices.at(biontID);
    }

    std::size_t Symbiosis::get_indices_size(const std::size_t biontID) const
    {
        return this->biontID_symbiont_species_vector.at(biontID)->mesh.get_indices_size();
        // return this->indices.at(biontID).size();
    }

    std::size_t Symbiosis::get_number_of_ofbx_meshes() const
    {
        // the value of `ofbx_mesh_count` comes from OpenFBX.
        return this->ofbx_mesh_count;
    }

    bool Symbiosis::has_texture(const std::size_t biontID) const
    {
        if (biontID >= this->biontID_symbiont_material_vector.size())
        {
            return false;
        }

        if (this->biontID_symbiont_material_vector.at(biontID) == nullptr)
        {
            return false;
        }

        return true;
    }

    uint32_t Symbiosis::get_texture(const std::size_t biontID) const
    {
        yli::ontology::SymbiontMaterial* const symbiont_material = this->biontID_symbiont_material_vector.at(biontID);
        return symbiont_material->texture.get_texture();
    }

    GLint Symbiosis::get_openGL_textureID(const std::size_t biontID) const
    {
        yli::ontology::SymbiontMaterial* const symbiont_material = this->biontID_symbiont_material_vector.at(biontID);
        return symbiont_material->get_openGL_textureID();
    }
}
