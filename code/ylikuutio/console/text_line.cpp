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

#include "text_line.hpp"
#include "text_input.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <stdexcept>   // std::runtime_error
#include <string>      // std::string
#include <string_view> // std::string_view
#include <vector>      // std::vector

namespace yli::console
{
    bool TextLine::operator==(const TextLine& other) const
    {
        return this->line == other.line;
    }

    bool TextLine::operator!=(const TextLine& other) const
    {
        return this->line != other.line;
    }

    TextLine::TextLine(std::string_view text_line)
        : line { text_line }
    {
    }

    TextLine::TextLine(const TextInput& text_input)
        : line { text_input.data() }
    {
    }

    TextLine::TextLine(const TextLine::const_iterator begin, const TextLine::const_iterator end)
        : line(begin.unwrap(), end.unwrap())
    {
    }

    const std::string& TextLine::data() const
    {
        return this->line;
    }

    std::vector<std::string_view> TextLine::split_into_lines(const std::size_t n_columns) const
    {
        if (n_columns == 0)
        {
            throw std::runtime_error("ERROR: `TextLine::split_into_lines`: `n_columns` is 0!");
        }

        std::vector<std::string_view> views;

        for (std::size_t begin_line_i = 0; begin_line_i < this->line.size(); begin_line_i += n_columns)
        {
            const std::size_t end_line_i = (begin_line_i + n_columns < this->line.size() ? begin_line_i + n_columns : this->line.size());
            views.emplace_back(std::string_view(&this->line[begin_line_i], &this->line[end_line_i]));
        }

        return views;
    }

    std::size_t TextLine::size() const
    {
        return this->line.size();
    }

    std::vector<std::string_view> TextLine::get_n_last_lines(const std::size_t n_lines, const std::size_t n_columns) const
    {
        // First, get all the lines.
        std::vector<std::string_view> views = this->split_into_lines(n_columns);

        // Select only `n_lines`, the last ones.
        if (views.size() < n_lines)
        {
            return views;
        }
        else
        {
            return std::vector<std::string_view>(views.end() - n_lines, views.end());
        }
    }
}
