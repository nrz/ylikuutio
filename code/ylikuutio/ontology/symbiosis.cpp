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

#include "symbiosis.hpp"
#include "universe.hpp"
#include "shader.hpp"
#include "symbiont_material.hpp"
#include "symbiont_species.hpp"
#include "material_struct.hpp"
#include "model_struct.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/load/symbiosis_loader.hpp"
#include "code/ylikuutio/load/model_loader_struct.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.
#include "code/ylikuutio/render/render_master.hpp"
#include "code/ylikuutio/render/render_templates.hpp"
#include <ofbx.h>

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstdint>  // std::uintptr_t
#include <cstddef>  // std::size_t
#include <ios>      // std::defaultfloat, std::dec, std::fixed, std::hex, std::ios
#include <iostream> // std::cout, std::cin, std::cerr
#include <sstream>  // std::istringstream, std::ostringstream, std::stringstream
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::ontology
{
    class Entity;
    class Scene;

    void Symbiosis::bind_to_new_scene_parent(yli::ontology::Scene* const new_parent)
    {
        // this method sets pointer to this `Symbiosis` to `nullptr`, sets `parent` according to the input,
        // and requests a new `childID` from the new `Scene`.
        //
        // requirements:
        // `this->parent` must not be `nullptr`.
        // `new_parent` must not be `nullptr`.

        yli::ontology::Entity* const scene = this->get_parent();

        if (scene == nullptr)
        {
            std::cerr << "ERROR: `Symbiosis::bind_to_new_scene_parent`: `scene` is `nullptr`!\n";
            return;
        }

        if (new_parent == scene)
        {
            // Setting current parent as the new parent. Nothing to do.
            return;
        }

        if (new_parent == nullptr)
        {
            std::cerr << "ERROR: `Symbiosis::bind_to_new_scene_parent`: `new_parent` is `nullptr`!\n";
            return;
        }

        if (new_parent->has_child(this->local_name))
        {
            std::cerr << "ERROR: `Symbiosis::bind_to_new_scene_parent`: local name is already in use!\n";
            return;
        }

        this->child_of_scene.unbind_and_bind_to_new_parent(&new_parent->parent_of_symbioses);
    }

    void Symbiosis::bind_to_new_parent(yli::ontology::Entity* const new_parent)
    {
        // this method sets pointer to this `Symbiosis` to `nullptr`, sets `scene_parent` according to the input,
        // and requests a new `childID` from the new `Scene`.
        //
        // requirements:
        // `this->scene_parent` must not be `nullptr`.
        // `new_parent` must not be `nullptr`.

        yli::ontology::Scene* const scene_parent = dynamic_cast<yli::ontology::Scene*>(new_parent);

        if (scene_parent == nullptr)
        {
            std::cerr << "ERROR: `Symbiosis::bind_to_new_parent`: `new_parent` is not `yli::ontology::Scene*`!\n";
            return;
        }

        this->bind_to_new_scene_parent(scene_parent);
    }

    void Symbiosis::bind_to_new_shader(yli::ontology::Shader* const new_shader)
    {
        if (new_shader != nullptr)
        {
            this->apprentice_of_shader.unbind_and_bind_to_new_generic_master_module(&new_shader->master_of_symbioses);
        }
        else
        {
            this->apprentice_of_shader.unbind_and_bind_to_new_generic_master_module(nullptr);
        }
    }

    Symbiosis::~Symbiosis()
    {
        // destructor.
        std::cout << "`Symbiosis` with childID " << std::dec << this->childID << " will be destroyed.\n";
    }

    void Symbiosis::render()
    {
        if (this->should_be_rendered)
        {
            yli::render::RenderMaster* const render_master = this->universe.get_render_master();

            if (render_master == nullptr)
            {
                std::cerr << "ERROR: `Symbiosis::render`: `render_master` is `nullptr`!\n";
                return;
            }

            render_master->render_holobionts(this->parent_of_holobionts.child_pointer_vector);
        }
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
        return this->child_of_scene.get_parent();
    }

    yli::ontology::Shader* Symbiosis::get_shader() const
    {
        return static_cast<yli::ontology::Shader*>(this->apprentice_of_shader.get_master());
    }

    yli::ontology::Scene* Symbiosis::get_scene() const
    {
        return static_cast<yli::ontology::Scene*>(this->child_of_scene.get_parent());
    }

    std::size_t Symbiosis::get_number_of_children() const
    {
        return this->parent_of_symbiont_materials.get_number_of_children() +
            this->parent_of_holobionts.get_number_of_children();
    }

    std::size_t Symbiosis::get_number_of_descendants() const
    {
        return yli::ontology::get_number_of_descendants(this->parent_of_symbiont_materials.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_holobionts.child_pointer_vector);
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
        model_loader_struct.model_struct.triangulation_type = this->triangulation_type;

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

            yli::ontology::Shader* const shader = this->get_shader();

            if (shader == nullptr)
            {
                std::cerr << "ERROR: `Symbiosis::create_symbionts`: `shader` is `nullptr`!\n";
                return;
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
                material_struct.shader = shader;
                material_struct.parent = this;
                material_struct.ofbx_texture = ofbx_texture;
                yli::ontology::SymbiontMaterial* const symbiont_material = new yli::ontology::SymbiontMaterial(
                        this->universe,
                        material_struct,
                        &this->parent_of_symbiont_materials);

                std::cout << "yli::ontology::SymbiontMaterial* successfully created.\n";

                // Create `SymbiontSpecies`s.
                // Care only about `ofbx::Texture*`s which are DIFFUSE textures.
                for (const std::size_t& mesh_i : this->ofbx_diffuse_texture_mesh_map.at(ofbx_texture))
                {
                    yli::ontology::ModelStruct model_struct;
                    model_struct.model_filename = this->model_filename;
                    model_struct.model_file_format = this->model_file_format;
                    model_struct.scene = static_cast<yli::ontology::Scene*>(shader->get_parent());
                    model_struct.shader = shader;
                    model_struct.symbiont_material = symbiont_material;
                    model_struct.vertex_count = mesh_i < this->vertices.size() ? this->vertices.at(mesh_i).size() : 0;
                    model_struct.vertices = mesh_i < this->vertices.size() ? this->vertices.at(mesh_i) : std::vector<glm::vec3>();
                    model_struct.uvs = mesh_i < this->uvs.size() ? this->uvs.at(mesh_i) : std::vector<glm::vec2>();
                    model_struct.normals = mesh_i < this->normals.size() ? this->normals.at(mesh_i) : std::vector<glm::vec3>();
                    model_struct.mesh_i = mesh_i;

                    std::cout << "Creating yli::ontology::SymbiontSpecies*, mesh index " << mesh_i << "...\n";

                    yli::ontology::SymbiontSpecies* symbiont_species = new yli::ontology::SymbiontSpecies(
                            this->universe,
                            model_struct,
                            &symbiont_material->parent_of_symbiont_species);

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

        return static_cast<yli::ontology::SymbiontMaterial*>(this->parent_of_symbiont_materials.child_pointer_vector[symbiont_material_i]);
    }

    yli::ontology::SymbiontSpecies* Symbiosis::get_symbiont_species(const std::size_t biontID) const
    {
        if (biontID >= this->biontID_symbiont_species_vector.size())
        {
            return nullptr;
        }

        return this->biontID_symbiont_species_vector[biontID];
    }

    GLint Symbiosis::get_vertex_position_modelspace_id(const std::size_t biontID) const
    {
        return this->biontID_symbiont_species_vector[biontID]->mesh.get_vertex_position_modelspace_id();
    }

    GLint Symbiosis::get_vertex_uv_id(const std::size_t biontID) const
    {
        return this->biontID_symbiont_species_vector[biontID]->mesh.get_vertex_uv_id();
    }

    GLint Symbiosis::get_vertex_normal_modelspace_id(const std::size_t biontID) const
    {
        return this->biontID_symbiont_species_vector[biontID]->mesh.get_vertex_normal_modelspace_id();
    }

    uint32_t Symbiosis::get_vertexbuffer(const std::size_t biontID) const
    {
        return this->biontID_symbiont_species_vector[biontID]->mesh.get_vertexbuffer();
    }

    uint32_t Symbiosis::get_uvbuffer(const std::size_t biontID) const
    {
        return this->biontID_symbiont_species_vector[biontID]->mesh.get_uvbuffer();
    }

    uint32_t Symbiosis::get_normalbuffer(const std::size_t biontID) const
    {
        return this->biontID_symbiont_species_vector[biontID]->mesh.get_normalbuffer();
    }

    uint32_t Symbiosis::get_elementbuffer(const std::size_t biontID) const
    {
        return this->biontID_symbiont_species_vector[biontID]->mesh.get_elementbuffer();
    }

    std::vector<uint32_t> Symbiosis::get_indices(const std::size_t biontID) const
    {
        return this->biontID_symbiont_species_vector[biontID]->mesh.get_indices();
        // return this->indices.at(biontID);
    }

    std::size_t Symbiosis::get_indices_size(const std::size_t biontID) const
    {
        return this->biontID_symbiont_species_vector[biontID]->mesh.get_indices_size();
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
