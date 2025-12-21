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

#include "error.hpp"
#include "error_type.hpp"
#include "text_position.hpp"

// Include standard headers
#include <cstddef>     // std::size_t
#include <string_view> // std::string_view

namespace yli::lisp
{
    Error::Error(const TextPosition& text_position, ErrorType error_type)
        : filename { text_position.get_filename() },
        line       { text_position.get_line() },
        column     { text_position.get_column() },
        type       { error_type }
    {
    }

    std::string_view Error::get_filename() const
    {
        return this->filename;
    }

    std::size_t Error::get_line() const
    {
        return this->line;
    }

    std::size_t Error::get_column() const
    {
        return this->column;
    }

    ErrorType Error::get_type() const
    {
        return this->type;
    }
}
