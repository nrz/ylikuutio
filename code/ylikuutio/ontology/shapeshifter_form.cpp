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

#include "shapeshifter_form.hpp"
#include "shapeshifter_transformation.hpp"
#include "shapeshifter_form_struct.hpp"

// Include standard headers
#include <cstddef>   // std::size_t
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

    ShapeshifterForm::ShapeshifterForm(
            yli::core::Application& application,
            Universe& universe,
            const ShapeshifterFormStruct& shapeshifter_form_struct,
            GenericParentModule* const shapeshifter_transformation_parent_module)
        : Entity(application, universe, shapeshifter_form_struct),
        child_of_shapeshifter_transformation(shapeshifter_transformation_parent_module, *this),
        mesh(universe, shapeshifter_form_struct, this->get_pipeline())
    {
        // `Entity` member variables begin here.
        this->type_string = "yli::ontology::ShapeshifterForm*";
    }

    Entity* ShapeshifterForm::get_parent() const
    {
        return this->child_of_shapeshifter_transformation.get_parent();
    }

    Scene* ShapeshifterForm::get_scene() const
    {
        const Entity* const shapeshifter_transformation_parent = this->get_parent();

        if (shapeshifter_transformation_parent == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `ShapeshifterForm::get_scene`: `shapeshifter_transformation_parent` is `nullptr`!");
        }

        return shapeshifter_transformation_parent->get_scene();
    }

    Pipeline* ShapeshifterForm::get_pipeline() const
    {
        auto* const shapeshifter_transformation_parent = static_cast<ShapeshifterTransformation*>(this->get_parent());

        if (shapeshifter_transformation_parent != nullptr)
        {
            return shapeshifter_transformation_parent->get_pipeline();
        }

        return nullptr;
    }

    std::size_t ShapeshifterForm::get_number_of_children() const
    {
        return 0; // `ShapeshifterForm` has no children.
    }

    std::size_t ShapeshifterForm::get_number_of_descendants() const
    {
        return 0; // `ShapeshifterForm` has no children.
    }

    void ShapeshifterForm::render()
    {
        // Render this `ShapeshifterForm`.

        // TODO.
    }
}
