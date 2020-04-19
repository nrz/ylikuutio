// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
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
#include "material.hpp"
#include "species_or_glyph.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <cstddef>  // std::size_t
#include <ios>      // std::defaultfloat, std::dec, std::fixed, std::hex, std::ios
#include <iostream> // std::cout, std::cin, std::cerr
#include <string>   // std::string

namespace yli
{
    namespace ontology
    {
        void Species::bind_to_new_parent(yli::ontology::Material* const new_parent)
        {
            // this method sets pointer to this `Species` to `nullptr`, sets `material_parent` according to the input,
            // and requests a new `childID` from the new `Material`.
            //
            // requirements:
            // `this->material_parent` must not be `nullptr`.
            // `new_parent` must not be `nullptr`.

            yli::ontology::Entity* const material = this->child.get_parent();

            if (material == nullptr)
            {
                std::cerr << "ERROR: `Species::bind_to_new_parent`: `material` is `nullptr`!\n";
                return;
            }

            if (new_parent == nullptr)
            {
                std::cerr << "ERROR: `Species::bind_to_new_parent`: `new_parent` is `nullptr`!\n";
                return;
            }

            // unbind from the old parent `Material`.
            this->child.unbind_child(this->childID);

            // get `childID` from `Material` and set pointer to this `Species`.
            this->child.set_parent_module_and_bind_to_new_parent(&new_parent->parent_of_species);
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

            this->bind_to_new_parent(material_parent);
        }

        Species::~Species()
        {
            if (!this->is_symbiont_species)
            {
                // destructor.
                std::cout << "`Species` with childID " << std::dec << this->childID << " will be destroyed.\n";

                // Cleanup buffers.
                glDeleteBuffers(1, &this->vertexbuffer);
                glDeleteBuffers(1, &this->uvbuffer);
                glDeleteBuffers(1, &this->normalbuffer);
                glDeleteBuffers(1, &this->elementbuffer);
            }
        }

        void Species::render()
        {
            if (this->should_be_rendered && this->opengl_in_use)
            {
                this->prerender();

                // render this `Species`.
                yli::ontology::render_species_or_glyph<yli::ontology::Species*>(this);

                this->postrender();
            }
        }

        std::size_t Species::get_x_step() const
        {
            return this->x_step;
        }

        std::size_t Species::get_z_step() const
        {
            return this->z_step;
        }

        std::size_t Species::get_image_width() const
        {
            return this->image_width;
        }

        const std::string& Species::get_model_file_format() const
        {
            return this->model_file_format;
        }

        std::size_t Species::get_image_height() const
        {
            return this->image_height;
        }
    }
}
