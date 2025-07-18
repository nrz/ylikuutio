// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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

#ifndef YLIKUUTIO_DATA_WRAP_HPP_INCLUDED
#define YLIKUUTIO_DATA_WRAP_HPP_INCLUDED

#include <functional> // std::reference_wrapper
#include <string>     // std::string

namespace yli::data
{
    template<typename T>
        struct Wrap
        {
            using type = T;
        };

    template<typename T>
        struct Wrap<T&>
        {
            using type = std::reference_wrapper<T>;
        };

    template<typename T>
        struct WrapAllButStrings
        {
            using type = T;
        };

    template<typename T>
        struct WrapAllButStrings<T&>
        {
            using type = std::reference_wrapper<T>;
        };

    template<>
        struct WrapAllButStrings<const std::string&>
        {
            using type = const std::string;
        };
}

#endif
