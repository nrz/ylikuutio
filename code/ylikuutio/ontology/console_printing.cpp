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

#include "console_printing.hpp"
#include "universe.hpp"
#include "console.hpp"

// Include standard headers
#include <string> // std::string
#include <vector> // std::vector

namespace yli::ontology
{
    void print_to_console(
            Console& console,
            const std::string& text)
    {
        console.print_text(text);
    }

    void print_words_to_console(
            Console& console,
            const std::vector<std::string>& words)
    {
        const Universe& universe = console.get_universe();

        std::size_t characters_for_line = universe.get_window_width() / universe.get_text_size();

        std::string keys_text;

        for (std::string key : words)
        {
            if (keys_text.size() > 0 &&
                    keys_text.size() + key.size() >= characters_for_line)
            {
                // Not enough space for this key on this line.
                // Print this line.
                console.print_text(keys_text);
                keys_text = key;
            }
            else if (keys_text.size() > 0)
            {
                // There is space, and this is not the first key on this line.
                keys_text += " " + key;
            }
            else
            {
                // This is the first key on this line.
                keys_text += key;
            }
        }
        if (keys_text.size() > 0)
        {
            // Print the last line.
            console.print_text(keys_text);
        }
    }
}
