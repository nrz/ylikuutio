#ifndef __YLIKUUTIO_MAP_HPP_INCLUDED
#define __YLIKUUTIO_MAP_HPP_INCLUDED

#include "code/ylikuutio/console/console.hpp"

// Include standard headers
#include <algorithm>     // std::sort
#include <stdint.h>      // uint32_t etc.
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

namespace map
{
    template <class T1>
        void print_keys_to_console(const std::unordered_map<std::string, T1>* const unordered_map_pointer, console::Console* const console)
        {
            std::vector<std::string> key_vector;
            key_vector.reserve(unordered_map_pointer->size());

            for (auto key_and_value : *unordered_map_pointer)
            {
                key_vector.push_back(key_and_value.first); // key.
            }

            // sort key vector alphabetically.
            std::sort(key_vector.begin(), key_vector.end());

            uint32_t characters_for_line = console->get_universe()->get_window_width() / console->get_universe()->get_text_size();

            std::string keys_text;

            for (std::string key : key_vector)
            {
                if (keys_text.size() > 0 &&
                        keys_text.size() + key.size() >= characters_for_line)
                {
                    // Not enough space for this key on this line.
                    // Print this line.
                    console->print_text(keys_text);
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
                console->print_text(keys_text);
            }
        }
}

#endif
