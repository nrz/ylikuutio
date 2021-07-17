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

#ifndef __YLIKUUTIO_ONTOLOGY_CHUNK_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_CHUNK_HPP_INCLUDED

#include "model.hpp"
#include "chunk_struct.hpp"
#include "chunk_master.hpp"
#include "material.hpp"
#include "code/ylikuutio/render/render_templates.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <vector>  // std::vector

// The content of any `Chunk` can be based either on some predefined
// data (eg. height map data, laser scanning data etc.) or procedurally
// (eg. Perlin noise or some other fractal). The parent of `Chunk` objects
// is a `ChunkMaster` object, that has a callback for retrieving or
// producing the content, and also the code for dividing the content into
// appropriate `Chunk` objects.
//
// Centroid:
//
// Center:
//
// From rendering point of view, `Chunk` is like `Species`, with the
// exception that `Chunk` normally contains only 1 `Object`.

namespace yli::ontology
{
    class Chunk: yli::ontology::Model
    {
        public:
            Chunk(const yli::ontology::ChunkStruct& chunk_struct)
                : Model(
                        chunk_struct.universe,
                        chunk_struct,
                        chunk_struct.opengl_in_use)
            {
                // constructor.
                this->is_original = true;

                this->parent      = chunk_struct.parent;

                // get `childID` from `ChunkMaster` and set pointer to this `Chunk`.
                this->bind_to_parent();

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "ontology::Chunk*";
            }

            Chunk(const Chunk&) = delete;            // Delete copy constructor.
            Chunk& operator=(const Chunk&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~Chunk();

            glm::vec3 light_position;            // light position.

            template<class T1, class T2>
                friend void yli::render::render_children(const std::vector<T1>& child_pointer_vector);

        private:
            void bind_to_parent();

            void render();

            yli::ontology::ChunkMaster* parent;  // pointer to the `ChunkMaster`.

            bool is_original;                    // If `Chunk` is original, if can be reconstructed using `get_content_callback`.
    };
}

#endif
