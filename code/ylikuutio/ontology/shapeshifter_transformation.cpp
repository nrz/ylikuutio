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

#include "shapeshifter_transformation.hpp"
#include "universe.hpp"
#include "material.hpp"
#include "shapeshifter_sequence.hpp"
#include "model_struct.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/core/application.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/data/datatype.hpp"
#include "code/ylikuutio/render/render_system.hpp"
#include "code/ylikuutio/render/render_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <optional> // std::optional
#include <iostream> // std::cout, std::cin, std::cerr

namespace yli::ontology
{
    class GenericParentModule;
    class Entity;
    class Scene;
    class Pipeline;

    std::optional<yli::data::AnyValue> ShapeshifterTransformation::bind_to_new_material_parent(
            yli::ontology::ShapeshifterTransformation& shapeshifter_transformation,
            yli::ontology::Material& new_parent) noexcept
    {
        // Set pointer to `shapeshifter_transformation` to `nullptr`, set parent according to the input,
        // and request a new childID from `new_parent`.

        const yli::ontology::Entity* const material = shapeshifter_transformation.get_parent();

        if (material == nullptr)
        {
            std::cerr << "ERROR: `ShapeshifterTransformation::bind_to_new_material_parent`: `material` is `nullptr`!\n";
            return std::nullopt;
        }

        if (new_parent.has_child(shapeshifter_transformation.local_name))
        {
            std::cerr << "ERROR: `ShapeshifterTransformation::bind_to_new_material_parent`: local name is already in use!\n";
            return std::nullopt;
        }

        shapeshifter_transformation.child_of_material.unbind_and_bind_to_new_parent(
                &new_parent.parent_of_shapeshifter_transformations);

        return std::nullopt;
    }

    ShapeshifterTransformation::ShapeshifterTransformation(
            yli::core::Application& application,
            yli::ontology::Universe& universe,
            const yli::ontology::ModelStruct& model_struct,
            yli::ontology::GenericParentModule* const material_parent_module)
        : Entity(application, universe, model_struct),
        child_of_material(material_parent_module, *this),
        parent_of_shapeshifter_forms(
                *this,
                this->registry,
                application.get_memory_allocator(yli::data::Datatype::SHAPESHIFTER_FORM),
                "shapeshifter_forms"),
        parent_of_shapeshifter_sequences(
                *this,
                this->registry,
                application.get_memory_allocator(yli::data::Datatype::SHAPESHIFTER_SEQUENCE),
                "shapeshifter_sequences")
    {
        // constructor.

        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "yli::ontology::ShapeshifterTransformation*";
        this->can_be_erased = true;
    }

    void ShapeshifterTransformation::render(const yli::ontology::Scene* const target_scene)
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

        if (render_system == nullptr)
        {
            std::cerr << "ERROR: `ShapeshifterTransformation::render`: `render_system` is `nullptr`!\n";
            return;
        }

        render_system->render_shapeshifter_sequences(this->parent_of_shapeshifter_sequences, new_target_scene);
    }

    yli::ontology::Entity* ShapeshifterTransformation::get_parent() const
    {
        return this->child_of_material.get_parent();
    }

    yli::ontology::Scene* ShapeshifterTransformation::get_scene() const
    {
        yli::ontology::Entity* parent = this->get_parent();

        if (parent != nullptr)
        {
            return parent->get_scene();
        }

        return nullptr;
    }

    yli::ontology::Pipeline* ShapeshifterTransformation::get_pipeline() const
    {
        const yli::ontology::Material* const material = static_cast<yli::ontology::Material*>(this->get_parent());

        if (material != nullptr)
        {
            return material->get_pipeline();
        }

        return nullptr;
    }

    std::size_t ShapeshifterTransformation::get_number_of_children() const
    {
        return this->parent_of_shapeshifter_forms.get_number_of_children() +
            this->parent_of_shapeshifter_sequences.get_number_of_children();
    }

    std::size_t ShapeshifterTransformation::get_number_of_descendants() const
    {
        return yli::ontology::get_number_of_descendants(this->parent_of_shapeshifter_forms.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_shapeshifter_sequences.child_pointer_vector);
    }
}
