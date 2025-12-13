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

#ifndef YLIKUUTIO_LISP_TEXT_POSITION_HPP_INCLUDED
#define YLIKUUTIO_LISP_TEXT_POSITION_HPP_INCLUDED

// Include standard headers
#include <cstddef>     // std::size_t
#include <optional>    // std::optional
#include <string_view> // std::string_view

namespace yli::lisp
{
    class TextPosition
    {
        public:
            TextPosition(std::string_view::const_iterator cbegin, std::string_view::const_iterator cend);

            void advance_to_next_token();

            std::optional<char32_t> peek_codepoint() const;
            std::optional<char32_t> scan_codepoint_and_advance();

            void update_line_and_column(const char32_t codepoint);
            void next_line();
            void next_column();

            std::string_view get_filename() const;

            std::string_view::const_iterator next(const char32_t codepoint);
            std::string_view::const_iterator get_token_start_it() const;
            std::string_view::const_iterator get_it() const;
            std::string_view::const_iterator get_cend() const;
            std::size_t get_offset() const;
            std::size_t get_line() const;
            std::size_t get_column() const;

        private:
            std::string_view filename;
            std::string_view::const_iterator token_start_it;
            std::string_view::const_iterator current_it;
            const std::string_view::const_iterator end_it;
            std::size_t offset { 0 };
            std::size_t line   { 1 };
            std::size_t column { 1 };
    };
}

#endif

