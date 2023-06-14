// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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

#ifndef YLIKUUTIO_ONTOLOGY_GET_CONTENT_CALLBACK_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_GET_CONTENT_CALLBACK_HPP_INCLUDED

// Include standard headers
#include <memory>   // std::shared_ptr
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace yli::data
{
    class AnyValue;
}

namespace yli::ontology
{
    class CallbackEngine;
    class CallbackObject;
    class CallbackParameter;
}

typedef std::shared_ptr<yli::data::AnyValue> (*GetContentCallback) (
        yli::ontology::CallbackEngine*,
        yli::ontology::CallbackObject*,
        std::vector<yli::ontology::CallbackParameter*>&,
        uint32_t x_start,
        uint32_t y_start,
        uint32_t z_start,
        uint32_t x_size,
        uint32_t y_size,
        uint32_t z_size);

#endif
