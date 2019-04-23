#ifndef __SCHEME_MASTER_HPP_INCLUDED
#define __SCHEME_MASTER_HPP_INCLUDED

// Include standard headers
#include <string> // std::string

#include "s7.h"

namespace yli
{
    namespace scheme
    {
        class SchemeMaster
        {
            public:
                // constructor.
                SchemeMaster();

                // destructor.
                ~SchemeMaster();

                std::string eval_string(const std::string& my_string) const;

            private:
                s7_scheme* s7;
        };
    }
}

#endif
