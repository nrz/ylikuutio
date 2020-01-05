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

#include "scheme_master.hpp"

// Include standard headers
#include <memory> // std::make_shared, std::shared_ptr
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
            std::shared_ptr<char> output(s7_object_to_c_string(this->s7, my_s7_pointer), std::default_delete<char[]>());
            return std::string(output.get());
        }
    }
}
