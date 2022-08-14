// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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

// Include standard headers
#include <cstddef> // std::size_t
#include <set>     // std::set
#include <string>  // std::string
#include <vector>  // std::vector

namespace yli::string
{
    class StringSet final
    {
        public:
            // constructor.
            StringSet();

            StringSet(const StringSet&) = delete;            // Delete copy constructor.
            StringSet& operator=(const StringSet&) = delete; // Delete copy assignment.

            // destructor.
            ~StringSet() = default;

            void add_string(const std::string& string);
            void erase_string(const std::string& string);
            bool is_string(const std::string& string);
            std::size_t get_number_of_completions(const std::string& input) const;
            std::string complete(const std::string& input) const;
            std::vector<std::string> get_completions(const std::string& input) const;
            std::size_t get_length_of_shortest_completion(const std::string& input) const;

        private:
            std::set<std::string> strings;
    };
}
