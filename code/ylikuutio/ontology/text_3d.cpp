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

#include "text_3d.hpp"
#include "vector_font.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <ios>      // std::defaultfloat, std::dec, std::fixed, std::hex, std::ios
#include <iostream> // std::cout, std::cin, std::cerr

namespace yli::ontology
{
    class Entity;
    class Scene;
    class Shader;

    void Text3D::bind_to_new_vector_font_parent(yli::ontology::VectorFont* const new_parent)
    {
        // This method sets pointer to this `Text3D` to `nullptr`, sets `parent` according to the input,
        // and requests a new `childID` from the new `VectorFont`.
        //
        // Requirements:
        // `this->parent` must not be `nullptr`.
        // `new_parent` must not be `nullptr`.

        yli::ontology::Entity* const vector_font = this->child_of_vector_font.get_parent();

        if (vector_font == nullptr)
        {
            std::cerr << "ERROR: `Text3D::bind_to_new_vector_font_parent`: `vector_font` is `nullptr`!\n";
            return;
        }

        if (new_parent == nullptr)
        {
            std::cerr << "ERROR: `Text3D::bind_to_new_vector_font_parent`: `new_parent` is `nullptr`!\n";
            return;
        }

        if (new_parent->has_child(this->local_name))
        {
            std::cerr << "ERROR: `Text3D::bind_to_new_vector_font_parent`: local name is already in use!\n";
            return;
        }

        // Unbind from the old parent `VectorFont`.
        this->child_of_vector_font.unbind_child();

        // Get `childID` from `VectorFont` and set pointer to this `Text3D`.
        this->child_of_vector_font.set_parent_module_and_bind_to_new_parent(&new_parent->parent_of_text_3ds);
    }

    void Text3D::bind_to_new_parent(yli::ontology::Entity* const new_parent)
    {
        // this method sets pointer to this `Text3D` to `nullptr`, sets parent according to the input,
        // and requests a new `childID` from the new `VectorFont`.
        //
        // requirements:
        // `new_parent` must not be `nullptr`.

        yli::ontology::VectorFont* const vector_font_parent = dynamic_cast<yli::ontology::VectorFont*>(new_parent);

        if (vector_font_parent == nullptr)
        {
            std::cerr << "ERROR: `Text3D::bind_to_new_parent`: `new_parent` is not `yli::ontology::VectorFont*`!\n";
            return;
        }

        this->bind_to_new_vector_font_parent(vector_font_parent);
    }

    Text3D::~Text3D()
    {
        // destructor.
        std::cout << "This `Text3D` (\"" << this->text_string << "\", childID " << std::dec << this->childID << ") will be destroyed.\n";
    }

    yli::ontology::Entity* Text3D::get_parent() const
    {
        return this->child_of_vector_font.get_parent();
    }

    yli::ontology::Scene* Text3D::get_scene() const
    {
        yli::ontology::Entity* const parent = this->get_parent();

        if (parent != nullptr)
        {
            return parent->get_scene();
        }

        return nullptr;
    }

    yli::ontology::Shader* Text3D::get_shader() const
    {
        yli::ontology::VectorFont* const vector_font = static_cast<yli::ontology::VectorFont*>(this->get_parent());

        if (vector_font != nullptr)
        {
            return vector_font->get_shader();
        }

        return nullptr;
    }

    std::size_t Text3D::get_number_of_children() const
    {
        return 0; // `Text3D` has no children.
    }

    std::size_t Text3D::get_number_of_descendants() const
    {
        return 0; // `Text3D` has no children.
    }
}
