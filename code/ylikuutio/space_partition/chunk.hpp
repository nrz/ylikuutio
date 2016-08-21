#ifndef __CHUNK_HPP_INCLUDED
#define __CHUNK_HPP_INCLUDED

#include "code/ylikuutio/ontology/model.hpp"

// Each `Chunk` contains `Triangle3D` objects.
// The `Chunk` in which a given `Triangle3D` belongs to is based on either
// on its center or its centroid. Each `Triangle3D` belongs to exactly one
// `Chunk`. Moving the vertices of the `Triangle3D` may move it to some
// other `Chunk` (to an adjacent `Chunk` or to a farther `Chunk`), as
// moving vertices moves the centroid and the center of the `Triangle3D`.
//
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

namespace space_partition
{
    class Chunk: ontology::Model
    {
        public:
            // constructor.
            Chunk();

            // destructor.
            ~Chunk();

        private:
            void render();
    };
}

#endif
