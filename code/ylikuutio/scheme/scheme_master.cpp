#include "scheme_master.hpp"

// Include standard headers
#include <string> // std::string

#include "s7.h"

namespace yli
{
    namespace scheme
    {
        SchemeMaster::SchemeMaster()
        {
            // constructor.
            this->s7 = s7_init();
        }

        SchemeMaster::~SchemeMaster()
        {
            // destructor.
            free(this->s7);
        }

        std::string SchemeMaster::eval_string(const std::string& my_string) const
        {
            s7_pointer my_s7_pointer = s7_eval_c_string(this->s7, my_string.c_str());
            const char* const output = s7_object_to_c_string(this->s7, my_s7_pointer);
            return std::string(output);
        }
    }
}
