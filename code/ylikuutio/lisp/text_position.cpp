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

#include "text_position.hpp"
#include "code/ylikuutio/string/unicode.hpp"

// Include standard headers
#include <cstddef>     // std::size_t
#include <string_view> // std::string_view

namespace yli::lisp
{
    TextPosition::TextPosition(std::string_view::const_iterator cbegin, std::string_view::const_iterator cend)
        : token_start_it { cbegin },
        current_it { cbegin },
        begin_it { cbegin },
        end_it { cend }
    {
    }

    TextPosition::TextPosition(
            std::string_view::const_iterator cbegin,
            std::string_view::const_iterator cend,
            const std::size_t offset,
            const std::size_t line,
            const std::size_t column)
        : token_start_it { cbegin },
        current_it { cbegin },
        begin_it { cbegin },
        end_it { cend },
        offset { offset },
        line   { line },
        column { column }
    {
    }

    void TextPosition::advance_to_next_token()
    {
        this->token_start_it = this->current_it;
    }

    std::optional<char32_t> TextPosition::peek_codepoint() const
    {
        std::optional<char32_t> maybe_codepoint = yli::string::peek_codepoint(this->current_it, this->end_it);

        if (!maybe_codepoint.has_value())
        {
            // Invalid UTF-8. Can not proceed any more.
            return std::nullopt;
        }

        const char32_t codepoint = maybe_codepoint.value();

        return codepoint;
    }

    std::optional<char32_t> TextPosition::scan_codepoint_and_advance()
    {
        std::optional<char32_t> maybe_codepoint = yli::string::read_codepoint(this->current_it, this->end_it);

        if (!maybe_codepoint.has_value())
        {
            // Invalid UTF-8. Can not proceed any more.
            return std::nullopt;
        }

        const char32_t codepoint = maybe_codepoint.value();

        this->update_line_and_column(codepoint);

        return codepoint;
    }

    void TextPosition::update_line_and_column(const char32_t codepoint)
    {
        if (codepoint == U'\n') [[unlikely]]
        {
            this->next_line();
        }
        else
        {
            this->column++;
        }
    }

    void TextPosition::next_line()
    {
        this->line++;
        this->column = 1;
    }

    void TextPosition::next_column()
    {
        this->column++;
    }

    std::string_view TextPosition::get_filename() const
    {
        return this->filename;
    }

    std::string_view::const_iterator TextPosition::next(const char32_t codepoint)
    {
        this->update_line_and_column(codepoint);
        return ++this->current_it;
    }

    std::string_view::const_iterator TextPosition::get_token_start_it() const
    {
        return this->token_start_it;
    }

    std::string_view::const_iterator TextPosition::get_it() const
    {
        return this->current_it;
    }

    std::string_view::const_iterator TextPosition::get_cbegin() const
    {
        return this->begin_it;
    }

    std::string_view::const_iterator TextPosition::get_cend() const
    {
        return this->end_it;
    }

    std::size_t TextPosition::get_offset() const
    {
        return this->offset;
    }

    std::size_t TextPosition::get_line() const
    {
        return this->line;
    }

    std::size_t TextPosition::get_column() const
    {
        return this->column;
    }
}
