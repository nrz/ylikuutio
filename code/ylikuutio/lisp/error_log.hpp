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

#ifndef YLIKUUTIO_LISP_ERROR_LOG_HPP_INCLUDED
#define YLIKUUTIO_LISP_ERROR_LOG_HPP_INCLUDED

#include "error.hpp"
#include "error_type.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <vector>  // std::vector

namespace yli::lisp
{
    class TextPosition;

    class ErrorLog
    {
        public:
            void add_error(const TextPosition& text_position, ErrorType error_type);

            const Error& at(const std::size_t index) const;

            bool empty() const;
            std::size_t size() const;

        private:
            std::vector<Error> errors;
    };
}

#endif
