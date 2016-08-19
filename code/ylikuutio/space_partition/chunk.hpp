#ifndef __CHUNK_HPP_INCLUDED
#define __CHUNK_HPP_INCLUDED

#include "code/ylikuutio/ontology/model.hpp"

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
