#ifndef __YLIKUUTIO_MAP_HPP_INCLUDED
#define __YLIKUUTIO_MAP_HPP_INCLUDED

#include "code/ylikuutio/console/console.hpp"
#include "code/ylikuutio/ontology/universe.hpp"

// Include standard headers
#include <algorithm>     // std::sort
#include <cstddef>       // std::size_t
#include <iostream>      // std::cout, std::cin, std::cerr
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

namespace yli
{
    namespace map
    {
        template <class T1>
            std::vector<std::string> get_keys(const std::unordered_map<std::string, T1>& unordered_map)
            {
                std::vector<std::string> key_vector;
                key_vector.reserve(unordered_map.size());

                for (auto key_and_value : unordered_map)
                {
                    key_vector.push_back(key_and_value.first); // key.
                }

                // sort key vector alphabetically.
                std::sort(key_vector.begin(), key_vector.end());

                return key_vector;
            }

        template <class T1>
            void print_keys_to_console(const std::unordered_map<std::string, T1>& unordered_map, yli::console::Console* const console)
            {
                std::vector<std::string> key_vector = yli::map::get_keys(unordered_map);

                std::size_t characters_for_line = console->get_universe()->get_window_width() / console->get_universe()->get_text_size();

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

        template <class T1>
            void print_keys_and_values(const std::unordered_map<std::string, T1>& unordered_map)
            {
                if (unordered_map.size() == 0)
                {
                    std::cout << "no keys.\n";
                    return;
                }

                std::vector<std::string> key_vector = yli::map::get_keys(unordered_map);

                for (std::string key : key_vector)
                {
                    if (unordered_map.at(key).empty())
                    {
                        std::cout << key << " (no value)\n";
                    }
                    else
                    {
                        std::cout << key << " = " << unordered_map.at(key) << "\n";
                    }
                }
            }
    }
}

#endif
