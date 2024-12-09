// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
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

#ifndef YLIKUUTIO_INPUT_TEXT_INPUT_HPP_INCLUDED
#define YLIKUUTIO_INPUT_TEXT_INPUT_HPP_INCLUDED

#include "codepoint.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <vector>  // std::vector

namespace yli::input
{
    class TextInput
    {
        public:
            void add_character(const Codepoint& character);

            template<typename Alloc, template<typename, typename> typename Type>
                void add_characters(const Type<Codepoint, Alloc>& char_container)
                {
                    // Assume there is memory available.
                    // Insert 0 or more characters starting from `begin` iterator (inclusive) to `end` iterator (exclusive).
                    this->input.insert(this->input.end(), char_container.begin(), char_container.end());
                    this->cursor_index += char_container.size();
                    this->cursor_it = this->input.begin() + this->cursor_index;
                }

            bool delete_character();
            void clear();
            bool move_cursor_left();
            bool move_cursor_right();
            void move_cursor_to_start_of_line();
            void move_cursor_to_end_of_line();
            std::size_t size() const;
            const std::vector<Codepoint>& data() const;
            std::size_t get_cursor_index() const;

        private:
            std::vector<Codepoint> input; // This is used for actual inputs.
            std::vector<Codepoint>::iterator cursor_it { this->input.begin() };
            std::size_t cursor_index { 0 };
    };
}

#endif
