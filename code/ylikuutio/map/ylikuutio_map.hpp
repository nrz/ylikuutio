// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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

#ifndef YLIKUUTIO_MAP_YLIKUUTIO_MAP_HPP_INCLUDED
#define YLIKUUTIO_MAP_YLIKUUTIO_MAP_HPP_INCLUDED

#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/console_printing.hpp"

// Include standard headers
#include <algorithm>     // std::sort
#include <cstddef>       // std::size_t
#include <iostream>      // std::cout, std::cerr
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <utility>       // std::pair
#include <vector>        // std::vector

namespace yli::ontology
{
    class Console;
}

namespace yli::map
{
    template <typename T1>
        std::vector<std::string> get_keys(const std::unordered_map<std::string, T1>& unordered_map)
        {
            std::vector<std::string> key_vector;
            key_vector.reserve(unordered_map.size());

            for (auto& key_and_value : unordered_map)
            {
                key_vector.emplace_back(key_and_value.first); // key.
            }

            // sort key vector alphabetically.
            std::sort(key_vector.begin(), key_vector.end());

            return key_vector;
        }

    template <typename T1>
        std::vector<std::pair<std::string, T1>> get_keys_and_values(const std::unordered_map<std::string, T1>& unordered_map)
        {
            std::vector<std::pair<std::string, T1>> key_and_value_vector;
            key_and_value_vector.reserve(unordered_map.size());

            for (auto& [key, value] : unordered_map)
            {
                key_and_value_vector.emplace_back(std::pair<std::string, T1>(key, value));
            }

            // sort key and value vector alphabetically.
            std::sort(key_and_value_vector.begin(), key_and_value_vector.end());

            return key_and_value_vector;
        }

    template <typename T1>
        void print_keys_to_console(const std::unordered_map<std::string, T1>& unordered_map, yli::ontology::Console& console)
        {
            std::vector<std::string> key_vector = yli::map::get_keys(unordered_map);
            yli::ontology::print_words_to_console(console, key_vector);
        }

    template <typename T1, typename T2>
        void print_keys_of_specific_type_to_console(const std::unordered_map<std::string, T1>& unordered_map, yli::ontology::Console& console)
        {
            std::vector<std::pair<std::string, T1>> keys_and_values = get_keys_and_values(unordered_map);

            for (auto& [key, value] : keys_and_values)
            {
                T2 inherited_type = dynamic_cast<T2>(value);

                if (inherited_type != nullptr)
                {
                    yli::ontology::print_to_console(console, key);
                }
            }
        }

    template <typename T1>
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

#endif
