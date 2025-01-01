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

#include "string_set.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <string>  // std::string
#include <vector>  // std::vector

namespace yli::string
{
    void StringSet::add_string(const std::string& string)
    {
        if (this->is_string(string))
        {
            return;
        }

        this->strings.insert(string);
    }

    void StringSet::erase_string(const std::string& string)
    {
        this->strings.erase(string);
    }

    bool StringSet::is_string(const std::string& string)
    {
        return this->strings.count(string) == 1;
    }

    std::size_t StringSet::get_number_of_completions(const std::string& input) const
    {
        std::size_t n_matches = 0;

        for (const std::string& string : this->strings)
        {
            if (string.compare(0, input.size(), input) == 0)
            {
                n_matches++;
            }
        }

        return n_matches;
    }

    std::string StringSet::complete(const std::string& input) const
    {
        const std::vector<std::string> completions = this->get_completions(input);

        if (completions.empty())
        {
            // No completions.
            return input;
        }

        if (completions.size() == 1)
        {
            return completions.at(0);
        }

        std::size_t completion_max_length = this->get_length_of_shortest_completion(input);

        for (std::size_t char_i = 0; char_i < completion_max_length; char_i++)
        {
            const char char_at_index = completions.at(0).at(char_i);

            for (std::size_t completion_i = 1; completion_i < completions.size(); completion_i++)
            {
                if (completions.at(completion_i).at(char_i) != char_at_index)
                {
                    return completions.at(0).substr(0, char_i);
                }
            }
        }

        return completions.at(0).substr(0, completion_max_length);
    }

    std::vector<std::string> StringSet::get_completions(const std::string& input) const
    {
        std::vector<std::string> completions;

        for (const std::string& string : this->strings)
        {
            if (string.compare(0, input.size(), input) == 0)
            {
                completions.emplace_back(string);
            }
        }

        return completions;
    }

    std::size_t StringSet::get_length_of_shortest_completion(const std::string& input) const
    {
        const std::vector<std::string> completions = this->get_completions(input);

        std::size_t length_of_shortest_completion = 0;

        for (const std::string& completion : completions)
        {
            if (length_of_shortest_completion == 0 || (length_of_shortest_completion > completion.size()))
            {
                length_of_shortest_completion = completion.size();
            }
        }

        return length_of_shortest_completion;
    }
}
