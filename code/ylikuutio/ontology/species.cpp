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
#include "material.hpp"
#include "object.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.
#include "code/ylikuutio/render/render_species_or_glyph.hpp"

// Include standard headers
#include <ios>      // std::defaultfloat, std::dec, std::fixed, std::hex, std::ios
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

namespace yli::ontology
{
    void Species::bind_to_new_material_parent(yli::ontology::Material* const new_parent)
    {
        // this method sets pointer to this `Species` to `nullptr`, sets `material_parent` according to the input,
        // and requests a new `childID` from the new `Material`.
        //
        // requirements:
        // `this->material_parent` must not be `nullptr`.
        // `new_parent` must not be `nullptr`.

        yli::ontology::Entity* const material = this->child_of_material.get_parent();

        if (material == nullptr)
        {
            std::cerr << "ERROR: `Species::bind_to_new_material_parent`: `material` is `nullptr`!\n";
            return;
        }

        if (new_parent == nullptr)
        {
            std::cerr << "ERROR: `Species::bind_to_new_material_parent`: `new_parent` is `nullptr`!\n";
            return;
        }

        if (new_parent->has_child(this->local_name))
        {
            std::cerr << "ERROR: `Species::bind_to_new_material_parent`: local name is already in use!\n";
            return;
        }

        // unbind from the old parent `Material`.
        this->child_of_material.unbind_child();

        // get `childID` from `Material` and set pointer to this `Species`.
        this->child_of_material.set_parent_module_and_bind_to_new_parent(&new_parent->parent_of_species);
    }

    void Species::bind_to_new_parent(yli::ontology::Entity* const new_parent)
    {
        // this method sets pointer to this `Species` to `nullptr`, sets `material_parent` according to the input,
        // and requests a new `childID` from the new `Material`.
        //
        // requirements:
        // `this->material_parent` must not be `nullptr`.
        // `new_parent` must not be `nullptr`.

        yli::ontology::Material* const material_parent = dynamic_cast<yli::ontology::Material*>(new_parent);

        if (material_parent == nullptr)
        {
            std::cerr << "ERROR: `Species::bind_to_new_parent`: `new_parent` is not `yli::ontology::Material*`!\n";
            return;
        }

        this->bind_to_new_material_parent(material_parent);
    }

    Species::~Species()
    {
        // destructor.

        if (!this->is_symbiont_species)
        {
            std::cout << "`Species` with childID " << std::dec << this->childID << " will be destroyed.\n";

            // Cleanup buffers.
            glDeleteBuffers(1, &this->vertexbuffer);
            glDeleteBuffers(1, &this->uvbuffer);
            glDeleteBuffers(1, &this->normalbuffer);
            glDeleteBuffers(1, &this->elementbuffer);
        }
    }

    yli::ontology::Entity* Species::get_parent() const
    {
        return this->child_of_material.get_parent();
    }

    void Species::render()
    {
        if (!this->should_be_rendered)
        {
            return;
        }

        this->prerender();
        yli::render::render_species_or_glyph<yli::ontology::Species*, yli::ontology::Entity*, yli::ontology::Object*>(this);
        this->postrender();
    }

    uint32_t Species::get_x_step() const
    {
        return this->x_step;
    }

    uint32_t Species::get_z_step() const
    {
        return this->z_step;
    }

    uint32_t Species::get_image_width() const
    {
        return this->image_width;
    }

    uint32_t Species::get_image_height() const
    {
        return this->image_height;
    }

    const std::string& Species::get_model_file_format() const
    {
        return this->model_file_format;
    }
}
