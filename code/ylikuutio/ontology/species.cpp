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

#include "species.hpp"
#include "entity.hpp"
#include "ecosystem.hpp"
#include "scene.hpp"
#include "material.hpp"
#include "object.hpp"
#include "species_struct.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/render/render_model.hpp"

// Include standard headers
#include <iostream>  // std::cout, std::cerr
#include <optional>  // std::optional
#include <stdexcept> // std::runtime_error
#include <stdint.h>  // uint32_t etc.

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class GenericParentModule;
    class GenericMasterModule;
    class Universe;
    class Pipeline;

    std::optional<yli::data::AnyValue> Species::bind_to_new_ecosystem_parent(
            Species& species,
            Ecosystem& new_parent)
    {
        // Set pointer to `Species` to `nullptr`, set parent according to the input,
        // and request a new childID from `new_parent`.

        const Entity* const old_ecosystem_or_scene_parent = species.get_parent();

        if (old_ecosystem_or_scene_parent == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Species::bind_to_new_ecosystem_parent`: `old_ecosystem_or_scene_parent` is `nullptr`!");
        }

        if (&new_parent == old_ecosystem_or_scene_parent)
        {
            // Setting current parent as the new parent. Nothing to do.
            return std::nullopt;
        }

        if (new_parent.has_child(species.local_name))
        {
            std::cerr << "ERROR: `Species::bind_to_new_ecosystem_parent`: local name is already in use!\n";
            return std::nullopt;
        }

        // `Ecosystem`s do not care in which `Ecosystem`s their apprentices reside,
        // so binding to an `Ecosystem` does not unbind any apprentices.
        species.child_of_ecosystem_or_scene.unbind_and_bind_to_new_parent(
                &new_parent.parent_of_species);

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Species::bind_to_new_scene_parent(
            Species& species,
            Scene& new_parent)
    {
        // Set pointer to `species` to `nullptr`, set parent according to the input,
        // and request a new childID from the new `new_parent`.

        const Entity* const old_ecosystem_or_scene_parent = species.get_parent();

        if (old_ecosystem_or_scene_parent == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Species::bind_to_new_scene_parent`: `old_ecosystem_or_scene_parent` is `nullptr`!");
        }

        if (&new_parent == old_ecosystem_or_scene_parent)
        {
            // Setting current parent as the new parent. Nothing to do.
            return std::nullopt;
        }

        if (new_parent.has_child(species.local_name))
        {
            std::cerr << "ERROR: `Species::bind_to_new_scene_parent`: local name is already in use!\n";
            return std::nullopt;
        }

        species.master_of_objects.unbind_all_apprentice_modules_belonging_to_other_scenes(&new_parent);
        species.apprentice_of_material.unbind_from_any_master_belonging_to_other_scene(new_parent);
        species.child_of_ecosystem_or_scene.unbind_and_bind_to_new_parent(
                &new_parent.parent_of_species);

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Species::bind_to_new_material(
            Species& species,
            Material& new_material) noexcept
    {
        // Set pointer to `species` to `nullptr`, set material according to the input,
        // and request a new apprenticeID from `new_material`.

        // Master and apprentice must belong to the same `Scene`,
        // if both belong to some `Scene`, and not `Ecosystem`.
        if (species.get_scene() == new_material.get_scene() ||
                species.get_scene() == nullptr ||
                new_material.get_scene() == nullptr)
        {
            species.apprentice_of_material.unbind_and_bind_to_new_generic_master_module(
                    &new_material.master_of_species);
        }
        else
        {
            std::cerr << "ERROR: `Species::bind_to_new_material`: master and apprentice can not belong to different `Scene`s!\n";
        }

        return std::nullopt;
    }

    Species::Species(
            yli::core::Application& application,
            Universe& universe,
            const SpeciesStruct& species_struct,
            GenericParentModule* const ecosystem_or_scene_parent_module,
            GenericMasterModule* const material_master_module)
        : Entity(application, universe, species_struct),
        child_of_ecosystem_or_scene(ecosystem_or_scene_parent_module, *this),
        master_of_objects(this, &this->registry, "objects"),
        apprentice_of_material(material_master_module, this),
        mesh(universe, species_struct, this->get_pipeline())
    {
        // `Entity` member variables begin here.
        this->type_string = "yli::ontology::Species*";
        this->can_be_erased = true;
    }

    Entity* Species::get_parent() const
    {
        return this->child_of_ecosystem_or_scene.get_parent();
    }

    std::size_t Species::get_number_of_apprentices() const
    {
        return this->master_of_objects.get_number_of_apprentices();
    }

    void Species::render(const Scene* const target_scene)
    {
        if (!this->should_render)
        {
            return;
        }

        Scene* const scene = this->get_scene();

        if (target_scene != nullptr && scene != nullptr && scene != target_scene)
        {
            // Different `Scene`s, do not render.
            return;
        }

        const Scene* const new_target_scene = (target_scene != nullptr ? target_scene : scene);

        yli::render::render_model<GenericMasterModule&, Object*>(
                this->mesh, this->master_of_objects, new_target_scene);
    }

    uint32_t Species::get_image_width() const
    {
        return this->mesh.image_width;
    }

    uint32_t Species::get_image_height() const
    {
        return this->mesh.image_height;
    }

    Scene* Species::get_scene() const
    {
        return this->child_of_ecosystem_or_scene.get_scene();
    }

    Pipeline* Species::get_pipeline() const
    {
        Material* const material = static_cast<Material*>(
                this->apprentice_of_material.get_master());

        if (material != nullptr)
        {
            return material->get_pipeline();
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
