// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
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

#include "species.hpp"
#include "entity.hpp"
#include "mesh_module.hpp"
#include "scene.hpp"
#include "material.hpp"
#include "object.hpp"
#include "code/ylikuutio/render/render_model.hpp"

// Include standard headers
#include <ios>      // std::defaultfloat, std::dec, std::fixed, std::hex, std::ios
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

namespace yli::ontology
{
    class Shader;

    void Species::bind_to_new_scene_parent(yli::ontology::Scene* const new_parent)
    {
        // this method sets pointer to this `Species` to `nullptr`, sets `scene_parent` according to the input,
        // and requests a new `childID` from the new `Scene`.
        //
        // requirements:
        // `this->scene_parent` must not be `nullptr`.
        // `new_parent` must not be `nullptr`.

        yli::ontology::Entity* const scene = this->child_of_scene.get_parent();

        if (scene == nullptr)
        {
            std::cerr << "ERROR: `Species::bind_to_new_scene_parent`: `scene` is `nullptr`!\n";
            return;
        }

        if (new_parent == scene)
        {
            // Setting current parent as the new parent. Nothing to do.
            return;
        }

        if (new_parent == nullptr)
        {
            std::cerr << "ERROR: `Species::bind_to_new_scene_parent`: `new_parent` is `nullptr`!\n";
            return;
        }

        if (new_parent->has_child(this->local_name))
        {
            std::cerr << "ERROR: `Species::bind_to_new_scene_parent`: local name is already in use!\n";
            return;
        }

        this->child_of_scene.unbind_and_bind_to_new_parent(&new_parent->parent_of_species);
    }

    void Species::bind_to_new_parent(yli::ontology::Entity* const new_parent)
    {
        // this method sets pointer to this `Species` to `nullptr`, sets `scene_parent` according to the input,
        // and requests a new `childID` from the new `Scene`.
        //
        // requirements:
        // `this->scene_parent` must not be `nullptr`.
        // `new_parent` must not be `nullptr`.

        yli::ontology::Scene* const scene_parent = dynamic_cast<yli::ontology::Scene*>(new_parent);

        if (scene_parent == nullptr)
        {
            std::cerr << "ERROR: `Species::bind_to_new_parent`: `new_parent` is not `yli::ontology::Scene*`!\n";
            return;
        }

        this->bind_to_new_scene_parent(scene_parent);
    }

    void Species::bind_to_new_material(yli::ontology::Material* const new_material)
    {
        // Unbind from the current `Material` if there is such.

        this->apprentice_of_material.unbind_from_generic_master_module();

        if (new_material != nullptr)
        {
            this->apprentice_of_material.bind_to_new_generic_master_module(&new_material->master_of_species);
        }
        else
        {
            this->apprentice_of_material.bind_to_new_generic_master_module(nullptr);
        }
    }

    Species::~Species()
    {
        // destructor.

        std::cout << "`Species` with childID " << std::dec << this->childID << " will be destroyed.\n";
    }

    yli::ontology::Entity* Species::get_parent() const
    {
        return this->child_of_scene.get_parent();
    }

    void Species::render()
    {
        if (!this->should_be_rendered)
        {
            return;
        }

        this->prerender();
        yli::render::render_model<yli::ontology::GenericMasterModule&, yli::ontology::Entity*, yli::ontology::Object*>(
                this->mesh, this->master_of_objects);
        this->postrender();
    }

    uint32_t Species::get_x_step() const
    {
        return this->mesh.x_step;
    }

    uint32_t Species::get_z_step() const
    {
        return this->mesh.z_step;
    }

    uint32_t Species::get_image_width() const
    {
        return this->mesh.image_width;
    }

    uint32_t Species::get_image_height() const
    {
        return this->mesh.image_height;
    }

    const std::string& Species::get_model_file_format() const
    {
        return this->mesh.model_file_format;
    }

    yli::ontology::Scene* Species::get_scene() const
    {
        return static_cast<yli::ontology::Scene*>(this->get_parent());
    }

    yli::ontology::Shader* Species::get_shader() const
    {
        yli::ontology::Material* const material = static_cast<yli::ontology::Material*>(this->get_parent());

        if (material != nullptr)
        {
            return material->get_shader();
        }

        return nullptr;
    }

    std::size_t Species::get_number_of_children() const
    {
        return 0; // `Species` has no children.
    }

    std::size_t Species::get_number_of_descendants() const
    {
        return 0; // `Species` has no children.
    }
}
