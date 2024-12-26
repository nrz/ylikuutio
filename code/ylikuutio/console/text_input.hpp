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

#ifndef YLIKUUTIO_CONSOLE_TEXT_INPUT_HPP_INCLUDED
#define YLIKUUTIO_CONSOLE_TEXT_INPUT_HPP_INCLUDED

#include "text_input_iterator.hpp"
#include "code/ylikuutio/data/codepoint.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <optional> // std::optional
#include <vector>   // std::vector

namespace yli::console
{
    class TextInput
    {
        public:
            // Iterator typedefs.
            typedef TextInputIterator       iterator;
            typedef TextInputIterator const_iterator;

            bool operator==(const TextInput& other) const
            {
                return this->input == other.input;
            }

            bool operator!=(const TextInput& other) const
            {
                return this->input != other.input;
            }

            void add_character(const yli::data::Codepoint& character);

            template<typename Alloc, template<typename, typename> typename Type>
                void add_characters(const Type<yli::data::Codepoint, Alloc>& char_container)
                {
                    // Assume there is memory available.
                    // Insert 0 or more characters starting from `begin` iterator (inclusive) to `end` iterator (exclusive).
                    this->input.insert(this->input.end(), char_container.begin(), char_container.end());
                    this->cursor_index += char_container.size();
                    this->cursor_it = this->input.begin() + this->cursor_index;
                }

            std::optional<yli::data::Codepoint> get_character_at_current_index() const;
            std::optional<yli::data::Codepoint> get_character_to_the_left() const;

            bool delete_character();
            void ctrl_w();
            void clear();
            bool move_cursor_left();
            bool move_cursor_right();
            void move_cursor_to_start_of_line();
            void move_cursor_to_end_of_line();
            std::size_t size() const;
            const std::vector<yli::data::Codepoint>& data() const;
            std::size_t get_cursor_index() const;

            // Iterator functions.
            iterator begin()
            {
                return iterator(this->input.begin());
            }

            iterator end()
            {
                return iterator(this->input.end());
            }

            const_iterator cbegin()
            {
                return const_iterator(this->input.begin());
            }

            const_iterator cend()
            {
                return const_iterator(this->input.end());
            }

        private:
            std::vector<yli::data::Codepoint> input; // This is used for actual inputs.
            std::vector<yli::data::Codepoint>::iterator cursor_it { this->input.begin() };
            std::size_t cursor_index { 0 };
    };
}

#endif
