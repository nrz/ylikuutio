#ifndef __CHUNK_MASTER_HPP_INCLUDED
#define __CHUNK_MASTER_HPP_INCLUDED

#include "code/ylikuutio/common/globals.hpp"

// `ChunkMaster` takes care of acquiring vertices (through `callback`),
// organizing vertices into `Chunk` objects, reconstructing `Chunk`
// objects (if vertices have been modified) and deactivating (by
// unbinding) and possibly deleting `Chunk` objects (if needed).

namespace space_partition
{
    class ChunkMaster
    {
        public:
            // constructor.
            ChunkMaster(InputParametersToAnyValueCallback callback);

            // destructor.
            ~ChunkMaster();

        private:
            // Callback used to get the content based on x, y, z.
            InputParametersToAnyValueCallback callback;
    };
};

#endif
