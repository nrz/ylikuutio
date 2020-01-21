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

#include "holobiont.hpp"
#include "symbiosis.hpp"
#include "biont.hpp"
#include "render_templates.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <memory>   // std::make_shared, std::shared_ptr
#include <string>   // std::string

namespace yli
{
    namespace ontology
    {
        class Entity;

        void Holobiont::bind_Biont(yli::ontology::Biont* const biont)
        {
            // get `childID` from `Holobiont` and set pointer to `object`.
            yli::hierarchy::bind_child_to_parent<yli::ontology::Biont*>(
                    biont,
                    this->biont_pointer_vector,
                    this->free_biontID_queue,
                    this->number_of_bionts);
        }

        void Holobiont::unbind_Biont(const std::size_t childID)
        {
            yli::hierarchy::unbind_child_from_parent<yli::ontology::Biont*>(
                    childID,
                    this->biont_pointer_vector,
                    this->free_biontID_queue,
                    this->number_of_bionts);
        }

        void Holobiont::bind_to_parent()
        {
            // requirements:
            // `this->symbiosis_parent` must not be `nullptr`.
            yli::ontology::Symbiosis* const symbiosis = this->symbiosis_parent;

            if (symbiosis == nullptr)
            {
                std::cerr << "ERROR: `Holobiont::bind_to_parent`: `symbiosis` is `nullptr`!\n";
                return;
            }

            // get `childID` from `Symbiosis` and set pointer to this `Holobiont`.
            symbiosis->parent_of_holobionts.bind_child(this);
        }

        void Holobiont::bind_to_new_parent(yli::ontology::Symbiosis* const new_parent)
        {
            // this method sets pointer to this `Holobiont` to `nullptr`, sets `symbiosis_parent` according to the input,
            // and requests a new `childID` from the new `Symbiosis`.
            //
            // requirements:
            // `this->symbiosis_parent` must not be `nullptr`.
            // `new_parent` must not be `nullptr`.

            yli::ontology::Symbiosis* const symbiosis = this->symbiosis_parent;

            if (symbiosis == nullptr)
            {
                std::cerr << "ERROR: `Holobiont::bind_to_new_parent`: `symbiosis` is `nullptr`!\n";
                return;
            }

            if (new_parent == nullptr)
            {
                std::cerr << "ERROR: `Holobiont::bind_to_new_parent`: `new_parent` is `nullptr`!\n";
                return;
            }

            // unbind from the old parent `Symbiosis`.
            symbiosis->parent_of_holobionts.unbind_child(this->childID);

            // get `childID` from `Symbiosis` and set pointer to this `Holobiont`.
            this->symbiosis_parent = new_parent;
            this->symbiosis_parent->parent_of_holobionts.bind_child(this);
        }

        Holobiont::~Holobiont()
        {
            // destructor.
            std::cout << "`Holobiont` with childID " << std::dec << this->childID << " will be destroyed.\n";

            // always delete all `Biont`s of this `Holobiont`.
            std::cout << "All `Biont`s of this `Holobiont` will be destroyed.\n";
            yli::hierarchy::delete_children<yli::ontology::Biont*>(this->biont_pointer_vector, this->number_of_bionts);

            // requirements for further actions:
            // `this->symbiosis_parent` must not be `nullptr`.

            yli::ontology::Symbiosis* const symbiosis = this->symbiosis_parent;

            if (symbiosis == nullptr)
            {
                std::cerr << "ERROR: `Holobiont::~Holobiont`: `symbiosis` is `nullptr`!\n";
                return;
            }

            // set pointer to this `Holobiont` to `nullptr`.
            symbiosis->parent_of_holobionts.unbind_child(this->childID);
        }

        void Holobiont::render()
        {
            // render this `Holobiont`.

            if (this->should_be_rendered)
            {
                this->prerender();

                // render this `Holobiont` by calling `render()` function of each `Biont`.
                yli::ontology::render_children<yli::ontology::Biont*>(this->biont_pointer_vector);

                this->postrender();
            }
        }

        void Holobiont::create_Bionts()
        {
            // requirements:
            // `this->symbiosis_parent` must not be `nullptr`.

            yli::ontology::Symbiosis* const symbiosis = this->symbiosis_parent;

            if (symbiosis == nullptr)
            {
                std::cerr << "ERROR: `Holobiont::create_Bionts`: `symbiosis` is `nullptr`!\n";
                return;
            }

            std::cout << "Creating bionts for Holobiont located at 0x" << std::hex << (uint64_t) this << std::dec << " ...\n";

            // Create `Biont` entities so that they bind to this `Holobiont`.
            const std::size_t correct_number_of_bionts = symbiosis->get_number_of_ofbx_meshes();
            std::cout << "Number of bionts to be created: " << correct_number_of_bionts << "\n";

            for (std::size_t biontID = 0; biontID < correct_number_of_bionts; biontID++)
            {
                if (!symbiosis->has_texture(biontID))
                {
                    std::cerr << "ERROR: `Holobiont::create_Bionts`: There is no texture for biont with biontID " << biontID << "\n";
                    continue;
                }

                yli::ontology::BiontStruct biont_struct;
                biont_struct.biontID               = biontID;
                biont_struct.holobiont_parent      = this;
                biont_struct.symbiont_species      = symbiosis->get_symbiont_species(biontID);
                biont_struct.original_scale_vector = this->original_scale_vector;
                biont_struct.rotate_angle          = this->rotate_angle;
                biont_struct.rotate_vector         = this->rotate_vector;
                biont_struct.initial_rotate_angle  = this->initial_rotate_angle;
                biont_struct.initial_rotate_vector = this->initial_rotate_vector;
                biont_struct.cartesian_coordinates = this->cartesian_coordinates;
                biont_struct.translate_vector      = this->translate_vector;

                std::cout << "Creating biont with biontID " << biontID << " ...\n";

                new yli::ontology::Biont(this->universe, biont_struct);
            }
        }

        void Holobiont::update_x(float x)
        {
            this->cartesian_coordinates.x = x;
            this->model_matrix[3][0] = x;

            for (yli::ontology::Biont* biont : this->biont_pointer_vector)
            {
                if (biont != nullptr)
                {
                    biont->cartesian_coordinates.x = x;
                    biont->model_matrix[3][0] = x;
                }
            }
        }

        void Holobiont::update_y(float y)
        {
            this->cartesian_coordinates.y = y;
            this->model_matrix[3][1] = y;

            for (yli::ontology::Biont* biont : this->biont_pointer_vector)
            {
                if (biont != nullptr)
                {
                    biont->cartesian_coordinates.y = y;
                    biont->model_matrix[3][1] = y;
                }
            }
        }

        void Holobiont::update_z(float z)
        {
            this->cartesian_coordinates.z = z;
            this->model_matrix[3][2] = z;

            for (yli::ontology::Biont* biont : this->biont_pointer_vector)
            {
                if (biont != nullptr)
                {
                    biont->cartesian_coordinates.z = z;
                    biont->model_matrix[3][2] = z;
                }
            }
        }

        yli::ontology::Entity* Holobiont::get_parent() const
        {
            return this->symbiosis_parent;
        }

        std::size_t Holobiont::get_number_of_children() const
        {
            return this->number_of_bionts;
        }

        std::size_t Holobiont::get_number_of_descendants() const
        {
            return yli::ontology::get_number_of_descendants(this->biont_pointer_vector);
        }
    }
}
