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

#include "chunk_master.hpp"
#include "material.hpp"
#include "chunk.hpp"
#include "material.hpp"
#include "render_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr

namespace yli
{
    namespace ontology
    {
        void ChunkMaster::bind_to_parent()
        {
            // requirements:
            // `this->parent` must not be `nullptr`.
            yli::ontology::Material* const material = this->parent;

            if (material == nullptr)
            {
                std::cerr << "ERROR: `ChunkMaster::bind_to_parent`: `material` is `nullptr`!\n";
                return;
            }

            // get `childID` from `Material` and set pointer to this `ChunkMaster`.
            material->parent_of_chunk_masters.bind_child(this);
        }

        ChunkMaster::~ChunkMaster()
        {
            // destructor.

            // requirements for further actions:
            // `this->parent` must not be `nullptr`.
            yli::ontology::Material* const material = this->parent;

            if (material == nullptr)
            {
                std::cerr << "ERROR: `ChunkMaster::~ChunkMaster`: `material` is `nullptr`!\n";
                return;
            }

            // set pointer to this `ChunkMaster` to `nullptr`.
            material->parent_of_chunk_masters.unbind_child(this->childID);
        }

        void ChunkMaster::render()
        {
            if (this->should_be_rendered)
            {
                // render `ChunkMaster` by calling `render()` function of each `Chunk`.
                yli::ontology::render_children<ontology::Entity*>(this->parent_of_chunks.child_pointer_vector);
            }
        }
    }
}
