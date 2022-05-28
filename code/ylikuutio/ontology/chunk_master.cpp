// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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
#include "universe.hpp"
#include "material.hpp"
#include "chunk.hpp"
#include "material.hpp"
#include "entity_struct.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/render/render_system.hpp"
#include "code/ylikuutio/render/render_templates.hpp"

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr

namespace yli::ontology
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

    ChunkMaster::ChunkMaster(yli::ontology::Universe& universe, yli::ontology::Material* const parent, GetContentCallback get_content_callback)
        : yli::ontology::Entity(universe, yli::ontology::EntityStruct()),
        parent_of_chunks(this, &this->registry, "chunks")
    {
        // constructor.
        this->get_content_callback = get_content_callback;
        this->parent               = parent;

        // get `childID` from `Material` and set pointer to this `ChunkMaster`.
        this->bind_to_parent();

        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "ontology::ChunkMaster*";
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
        if (!this->should_be_rendered)
        {
            return;
        }

        yli::render::RenderSystem* const render_system = this->universe.get_render_system();

        if (render_system == nullptr)
        {
            std::cerr << "ERROR: `ChunkMaster::render`: `render_system` is `nullptr`!\n";
            return;
        }

        render_system->render_chunks(this->parent_of_chunks);
    }
}
