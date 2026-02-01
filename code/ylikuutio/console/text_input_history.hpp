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

#ifndef YLIKUUTIO_CONSOLE_TEXT_INPUT_HISTORY_HPP_INCLUDED
#define YLIKUUTIO_CONSOLE_TEXT_INPUT_HISTORY_HPP_INCLUDED

#include "text_input_history_iterator.hpp"
#include "text_input_history_const_iterator.hpp"
#include "text_input.hpp"
#include "console_state.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <limits>   // std::numeric_limits
#include <vector>   // std::vector

namespace yli::console
{
    class TextInputHistory
    {
        public:
            // Iterator typedefs.
            typedef TextInputHistoryIterator      iterator;
            typedef TextInputHistoryConstIterator const_iterator;

            void add_to_history(const TextInput& text_input);
            void emplace_back(const TextInput& text_input);
            void push_back(const TextInput& text_input);

            bool enter_history();
            bool exit_history();

            bool move_to_previous();
            bool move_to_next();
            void move_to_first();
            void move_to_last();
            bool move_to_nth(const std::size_t new_history_index);

            void clear();

            const TextInput* get() const;
            const TextInput& at(const std::size_t input_i) const;

            bool get_is_in_history() const;
            std::size_t size() const;
            bool empty() const;
            const std::vector<TextInput>& data() const;

            std::size_t get_history_index() const;

            void on_change(const ConsoleState old_state, const ConsoleState new_state);

            // Iterator functions.
            iterator begin()
            {
                return iterator(this->history.begin());
            }

            iterator end()
            {
                return iterator(this->history.end());
            }

            const_iterator cbegin() const
            {
                return const_iterator(this->history.cbegin());
            }

            const_iterator cend() const
            {
                return const_iterator(this->history.cend());
            }

            std::vector<TextInput>::const_iterator get_history_it() const
            {
                return this->history_it;
            }

        private:
            std::vector<TextInput> history;
            std::vector<TextInput>::iterator history_it { this->history.end() };
            std::size_t history_index { std::numeric_limits<std::size_t>::max() };
    };
}

#endif
