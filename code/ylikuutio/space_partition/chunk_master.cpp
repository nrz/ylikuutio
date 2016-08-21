#include "chunk_master.hpp"
#include "code/ylikuutio/common/globals.hpp"

namespace space_partition
{
    ChunkMaster::ChunkMaster(InputParametersToAnyValueCallback callback)
    {
        // constructor.
        this->callback = callback;
    }

    ChunkMaster::~ChunkMaster()
    {
        // destructor.
    }
}
