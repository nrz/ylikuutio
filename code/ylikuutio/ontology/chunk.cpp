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

#include "chunk.hpp"
#include "chunk_master.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr

namespace yli
{
    namespace ontology
    {
        void Chunk::bind_to_parent()
        {
            // requirements:
            // `this->parent` must not be `nullptr`.
            yli::ontology::ChunkMaster* const chunk_master = this->parent;

            if (chunk_master == nullptr)
            {
                std::cerr << "ERROR: `Chunk::bind_to_parent`: `chunk_master` is `nullptr`!\n";
                return;
            }

            // get `childID` from the `ChunkMaster` and set pointer to this `Chunk`.
            chunk_master->parent_of_chunks.bind_child(this);
        }

        Chunk::~Chunk()
        {
            // destructor.
            //
            // requirements:
            // `this->parent` must not be `nullptr`.
            yli::ontology::ChunkMaster* const chunk_master = this->parent;

            if (chunk_master == nullptr)
            {
                std::cerr << "ERROR: `Chunk::~Chunk`: `chunk_master` is `nullptr`!\n";
                return;
            }

            chunk_master->parent_of_chunks.unbind_child(this->childID);
        }

        void Chunk::render()
        {
            if (this->opengl_in_use)
            {
                // Render this `Chunk`.
                // If any vertex of the `Chunk` has changed, the vertex data
                // of the `Chunk` needs to be reconstructed before rendering.
            }
        }
    }
}
