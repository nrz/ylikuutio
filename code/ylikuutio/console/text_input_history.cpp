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

#include "text_input_history.hpp"
#include "console_state.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cerr
#include <limits>   // std::numeric_limits
#include <vector>   // std::vector

namespace yli::console
{
    class TextInput;

    void TextInputHistory::add_to_history(const TextInput& text_input)
    {
        this->history.emplace_back(text_input);

        // The iterator needs to be updated because `emplace_back` invalidates iterators.
        if (this->history_index == std::numeric_limits<std::size_t>::max()) [[likely]]
        {
            // We are not in history. Adding input to history must keep the iterator past end.
            this->history_it = this->history.end();
        }
        else
        {
            // We are in history. Adding input to history must keep the iterator correct.
            this->history_it = this->history.begin() + this->history_index;
        }

        // Set copied `TextInput` into a valid state.
        this->history.back().move_cursor_to_end_of_line();
    }

    void TextInputHistory::emplace_back(const TextInput& text_input)
    {
        this->history.emplace_back(text_input);

        // The iterator needs to be updated because `emplace_back` invalidates iterators.
        if (this->history_index == std::numeric_limits<std::size_t>::max()) [[likely]]
        {
            // We are not in history. Emplacing input to history must keep the iterator past end.
            this->history_it = this->history.end();
        }
        else
        {
            // We are in history. Emplacing input to history must keep the iterator correct.
            this->history_it = this->history.begin() + this->history_index;
        }

        // Set copied `TextInput` into a valid state.
        this->history.back().move_cursor_to_end_of_line();
    }

    void TextInputHistory::push_back(const TextInput& text_input)
    {
        this->history.push_back(text_input);

        // The iterator needs to be updated because `emplace_back` invalidates iterators.
        if (this->history_index == std::numeric_limits<std::size_t>::max()) [[likely]]
        {
            // We are not in history. Pushing input to history must keep the iterator past end.
            this->history_it = this->history.end();
        }
        else
        {
            // We are in history. Pushing input to history must keep the iterator correct.
            this->history_it = this->history.begin() + this->history_index;
        }

        // Set copied `TextInput` into a valid state.
        this->history.back().move_cursor_to_end_of_line();
    }

    bool TextInputHistory::enter_history()
    {
        if (std::size_t history_size = this->size(); !this->get_is_in_history() && history_size > 0) [[likely]]
        {
            // If we are not in history and the history is not empty, enter the history.
            this->history_index = history_size - 1;
            this->history_it = this->history.begin() + history_index;
            return true;
        }

        // Otherwise, entering history failed.
        std::cerr << "ERROR: `TextInputHistory::enter_history`: entering history failed!\n";
        return false;
    }

    bool TextInputHistory::exit_history()
    {
        if (this->get_is_in_history())
        {
            // If we are in history, exit the history.
            this->history_index = std::numeric_limits<std::size_t>::max();
            this->history_it = this->history.end();
            return true;
        }

        return false;
    }

    bool TextInputHistory::edit_historical_input()
    {
        if (this->get_is_in_history())
        {
            // If we are in history, enter temp input.
            // We still stay in the some historical index.
            return true;
        }

        return false;
    }

    bool TextInputHistory::move_to_previous()
    {
        if (this->get_is_in_history() && this->history_index > 0 && this->history_index < this->size()) [[likely]]
        {
            // If we are in the history and not in the oldest input, move to the previous input.
            this->history_index--;
            this->history_it--;
            return true;
        }

        // Otherwise either history is empty, or we are not in history, or we are in the first input of the history.
        return false;
    }

    bool TextInputHistory::move_to_next()
    {
        if (this->get_is_in_history() && this->history_index < this->size() - 1) [[likely]]
        {
            // If we are in the history and not in the newest input, move to the next input.
            this->history_index++;
            this->history_it++;
            return true;
        }

        // Otherwise either history is empty, or we are not in history, or we are in the last input of the history.
        return false;
    }

    void TextInputHistory::move_to_first()
    {
        if (this->size() > 0 && this->get_is_in_history()) [[likely]]
        {
            this->history_index = 0;
            this->history_it = this->history.begin();
        }
    }

    void TextInputHistory::move_to_last()
    {
        if (this->size() > 0 && this->get_is_in_history()) [[likely]]
        {
            this->history_index = this->size() - 1;
            this->history_it = this->history.begin() + this->size() - 1;
        }
    }

    bool TextInputHistory::move_to_nth(const std::size_t new_history_index)
    {
        if (history_index < this->size())
        {
            this->history_index = new_history_index;
            this->history_it = this->history.begin() + this->history_index;
            return true;
        }

        return false;
    }

    void TextInputHistory::clear()
    {
        this->history.clear();
        this->history_it = this->history.end();
        this->history_index = std::numeric_limits<std::size_t>::max();
    }

    const TextInput* TextInputHistory::get() const
    {
        if (this->history_index < this->history.size()) [[likely]]
        {
            return &this->history.at(this->history_index);
        }

        return nullptr;
    }

    const TextInput& TextInputHistory::at(const std::size_t input_i) const
    {
        return *(this->history.begin() + input_i);
    }

    bool TextInputHistory::get_is_in_history() const
    {
        return this->history_index < std::numeric_limits<std::size_t>::max();
    }

    std::size_t TextInputHistory::size() const
    {
        return this->history.size();
    }

    bool TextInputHistory::empty() const
    {
        return this->size() == 0;
    }

    const std::vector<TextInput>& TextInputHistory::data() const
    {
        return this->history;
    }

    std::size_t TextInputHistory::get_history_index() const
    {
        return this->history_index;
    }

    void TextInputHistory::on_change(const yli::console::ConsoleState old_state, const yli::console::ConsoleState new_state)
    {
        if (new_state == old_state)
        {
            // No change.
            return;
        }

        // Console state change.

        if (new_state == ConsoleState::ACTIVE_IN_HISTORICAL_INPUT)
        {
            this->enter_history();
        }
        else if (new_state == ConsoleState::ACTIVE_IN_NEW_INPUT)
        {
            this->exit_history();
        }
    }
}
