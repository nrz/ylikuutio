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

#include "shapeshifter_transformation.hpp"
#include "universe.hpp"
#include "material.hpp"
#include "shapeshifter_sequence.hpp"
#include "shapeshifter_transformation_struct.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/data/datatype.hpp"
#include "code/ylikuutio/render/render_system.hpp"
#include "code/ylikuutio/render/render_templates.hpp"

// Include standard headers
#include <cstddef>   // std::size_t
#include <iostream>  // std::cout, std::cerr
#include <optional>  // std::optional
#include <stdexcept> // std::runtime_error

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class GenericParentModule;
    class Entity;
    class Scene;
    class Pipeline;

    std::optional<yli::data::AnyValue> ShapeshifterTransformation::bind_to_new_material_parent(
            ShapeshifterTransformation& shapeshifter_transformation,
            Material& new_parent)
    {
        // Set pointer to `shapeshifter_transformation` to `nullptr`, set parent according to the input,
        // and request a new childID from `new_parent`.

        const Entity* const material_parent = shapeshifter_transformation.get_parent();

        if (material_parent == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `ShapeshifterTransformation::bind_to_new_material_parent`: `material_parent` is `nullptr`!");
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
            Universe& universe,
            const ShapeshifterTransformationStruct& shapeshifter_transformation_struct,
            GenericParentModule* const material_parent_module)
        : Entity(application, universe, shapeshifter_transformation_struct),
        child_of_material(material_parent_module, *this),
        parent_of_shapeshifter_forms(
                *this,
                this->registry,
                "shapeshifter_forms"),
        parent_of_shapeshifter_sequences(
                *this,
                this->registry,
                "shapeshifter_sequences")
    {
        // `Entity` member variables begin here.
        this->type_string = "yli::ontology::ShapeshifterTransformation*";
        this->can_be_erased = true;
    }

    void ShapeshifterTransformation::render(const Scene* const target_scene)
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

        yli::render::RenderSystem* const render_system = this->universe.get_render_system();

        if (render_system == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `ShapeshifterTransformation::render`: `render_system` is `nullptr`!");
        }

        render_system->render_shapeshifter_sequences(this->parent_of_shapeshifter_sequences, new_target_scene);
    }

    Entity* ShapeshifterTransformation::get_parent() const
    {
        return this->child_of_material.get_parent();
    }

    Scene* ShapeshifterTransformation::get_scene() const
    {
        Entity* material_parent = this->get_parent();

        if (material_parent == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `ShapeshifterTransformation::get_scene`: `material_parent` is `nullptr`!");
        }

        return material_parent->get_scene();
    }

    Pipeline* ShapeshifterTransformation::get_pipeline() const
    {
        const Material* const material_parent = static_cast<Material*>(this->get_parent());

        if (material_parent == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `ShapeshifterTransformation::get_pipeline`: `material_parent` is `nullptr`!");
        }

        return material_parent->get_pipeline();
    }

    GenericParentModule* ShapeshifterTransformation::get_generic_parent_module(const int type)
    {
        if (type == yli::data::Datatype::SHAPESHIFTER_FORM)
        {
            return &this->parent_of_shapeshifter_forms;
        }
        else if (type == yli::data::Datatype::SHAPESHIFTER_SEQUENCE)
        {
            return &this->parent_of_shapeshifter_sequences;
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
