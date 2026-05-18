// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2026 Antti Nuortimo.
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
#include <cstdint>  // std::uint32_t
#include <memory>   // std::shared_ptr
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
        CallbackEngine*,
        CallbackObject*,
        std::vector<CallbackParameter*>&,
        std::uint32_t x_start,
        std::uint32_t y_start,
        std::uint32_t z_start,
        std::uint32_t x_size,
        std::uint32_t y_size,
        std::uint32_t z_size);

#endif
