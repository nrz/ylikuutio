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

#include "scrollback_buffer.hpp"
#include "console_state.hpp"
#include "text_line.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <limits>   // std::numeric_limits
#include <optional> // std::optional
#include <span>     // std::span
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace yli::console
{
    class TextInput;

    ScrollbackBuffer::ScrollbackBuffer(const uint32_t n_columns, const uint32_t n_rows)
        : n_columns { (n_columns > 0 ? n_columns : 1) },
        n_rows     { (n_rows > 0 ? n_rows : 1) }
    {
    }

    void ScrollbackBuffer::add_to_buffer(const TextInput& text)
    {
        this->add_to_buffer(TextLine(text));
    }

    void ScrollbackBuffer::add_to_buffer(const TextLine& text)
    {
        for (std::size_t text_i = 0; text_i < text.size(); text_i += this->n_columns)
        {
            if (text_i + this->n_columns <= text.size())
            {
                TextLine text_line(text.cbegin() + text_i, text.cbegin() + text_i + this->n_columns);
                this->buffer.emplace_back(text_line);
            }
            else
            {
                TextLine text_line(text.cbegin() + text_i, text.cend());
                this->buffer.emplace_back(text_line);
            }
        }
    }

    void ScrollbackBuffer::emplace_back(const TextLine& text)
    {
        this->buffer.emplace_back(text);
    }

    void ScrollbackBuffer::push_back(const TextLine& text)
    {
        this->buffer.push_back(text);
    }

    bool ScrollbackBuffer::enter_buffer()
    {
        if (std::size_t buffer_size = this->buffer.size(); buffer_size > 0) [[likely]]
        {
            if (this->get_is_active_in_buffer()) [[unlikely]]
            {
                // Nothing to do. This function should be idempotent.
                return true;
            }

            // If we are not in buffer and the buffer is not empty, enter the buffer.
            this->buffer_index = buffer_size - 1;
            this->buffer_it = this->buffer.begin() + this->buffer_index;
            return true;
        }

        // Otherwise, entering buffer failed.
        return false;
    }

    bool ScrollbackBuffer::exit_buffer()
    {
        if (this->get_is_active_in_buffer())
        {
            // If we are in buffer, exit the buffer.
            this->buffer_index = std::numeric_limits<std::size_t>::max();
            this->buffer_it = this->buffer.end();
            return true;
        }

        return false;
    }

    bool ScrollbackBuffer::move_to_previous()
    {
        if (this->get_is_active_in_buffer() && this->buffer_index > 0) [[likely]]
        {
            // If we are in the buffer and not in the oldest input, move to the previous input.
            this->buffer_index--;
            this->buffer_it--;
            return true;
        }

        // Otherwise either buffer is empty, or we are not in buffer, or we are in the first input of the buffer.
        return false;
    }

    bool ScrollbackBuffer::move_to_next()
    {
        if (this->get_is_active_in_buffer() && this->buffer_index < this->size()) [[likely]]
        {
            // If we are in the buffer and not in the newest input, move to the next input.
            this->buffer_index++;
            this->buffer_it++;
            return true;
        }

        // Otherwise either buffer is empty, or we are not in buffer, or we are in the last input of the buffer.
        return false;
    }

    void ScrollbackBuffer::move_to_first()
    {
        if (this->size() > 0 && this->get_is_active_in_buffer()) [[likely]]
        {
            this->buffer_index = 0;
            this->buffer_it = this->buffer.begin();
        }
    }

    void ScrollbackBuffer::move_to_last()
    {
        if (this->size() > 0 && this->get_is_active_in_buffer()) [[likely]]
        {
            this->buffer_index = this->size() - 1;
            this->buffer_it = this->buffer.begin() + this->size() - 1;
        }
    }

    std::span<const TextLine> ScrollbackBuffer::get_view(const std::size_t top_index, const std::size_t max_rows) const
    {
        if (top_index >= this->size()) [[unlikely]]
        {
            // Top index is too big.
            return std::span(this->data().begin(), this->data().begin()); // Empty view.
        }
        else if (max_rows <= this->size() && top_index <= this->size() - max_rows) [[likely]]
        {
            return std::span(&this->data()[top_index], &this->data()[top_index + max_rows]);
        }

        return std::span(&this->data()[top_index], &this->data()[this->size()]);
    }

    std::span<const TextLine> ScrollbackBuffer::get_view_to_last(const std::size_t max_rows) const
    {
        if (this->size() > max_rows) [[likely]]
        {
            auto top_of_view_it = this->data().cend() - max_rows;
            return std::span(top_of_view_it, this->data().cend());
        }

        return std::span(this->data().cbegin(), this->data().cend());
    }

    const TextLine& ScrollbackBuffer::at(const std::size_t line_i) const
    {
        return *(this->buffer.begin() + line_i);
    }

    bool ScrollbackBuffer::get_is_active_in_buffer() const
    {
        return this->buffer_index < std::numeric_limits<std::size_t>::max();
    }

    std::size_t ScrollbackBuffer::size() const
    {
        return this->buffer.size();
    }

    bool ScrollbackBuffer::empty() const
    {
        return this->size() == 0;
    }

    const std::vector<TextLine>& ScrollbackBuffer::data() const
    {
        return this->buffer;
    }

    uint32_t ScrollbackBuffer::get_n_columns() const
    {
        return this->n_columns;
    }

    uint32_t ScrollbackBuffer::get_n_rows() const
    {
        return this->n_rows;
    }

    std::size_t ScrollbackBuffer::get_buffer_index() const
    {
        return this->buffer_index;
    }

    void ScrollbackBuffer::on_change(const yli::console::ConsoleState old_state, const yli::console::ConsoleState new_state)
    {
        if (new_state == old_state)
        {
            // No change.
            return;
        }

        // Console state change.

        if (new_state == ConsoleState::ACTIVE_IN_SCROLLBACK_BUFFER_WHILE_IN_NEW_INPUT ||
                new_state == ACTIVE_IN_SCROLLBACK_BUFFER_WHILE_IN_HISTORICAL_INPUT ||
                new_state == ACTIVE_IN_SCROLLBACK_BUFFER_WHILE_IN_TEMP_INPUT)
        {
            this->enter_buffer();
        }
        else if (new_state == ConsoleState::ACTIVE_IN_NEW_INPUT ||
                new_state == ConsoleState::ACTIVE_IN_HISTORICAL_INPUT ||
                new_state == ConsoleState::ACTIVE_IN_TEMP_INPUT)
        {
            // We exited scrollback buffer.
            this->exit_buffer();
        }
    }

    bool ScrollbackBuffer::page_up()
    {
        // Page up succeeds even if position does not change.
        if (this->size() > 0 && this->get_is_active_in_buffer()) [[likely]]
        {
            if (this->buffer_index >= this->n_rows) [[likely]]
            {
                this->buffer_index -= this->n_rows;
            }
            else
            {
                this->buffer_index = 0;
            }

            this->buffer_it = this->buffer.begin() + this->buffer_index;
            return true;
        }

        return false;
    }

    bool ScrollbackBuffer::page_down()
    {
        // Page down fails if page down would exit the scrollback buffer.
        // That way it `ConsoleLogicModule` receives the information and
        // can do appropriate state transition instead.
        if (this->size() > 0 &&
                this->get_is_active_in_buffer() &&
                this->buffer_index + this->n_rows < this->size()) [[likely]]
        {
            this->buffer_index += this->n_rows;
            this->buffer_it = this->buffer.begin() + this->buffer_index;
            return true;
        }

        return false;
    }

    void ScrollbackBuffer::clear()
    {
        this->buffer.clear();
        this->buffer_it = this->buffer.end();
        this->buffer_index = std::numeric_limits<std::size_t>::max();
    }
}
