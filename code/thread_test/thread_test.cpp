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

// Include standard headers
#include <cstdint>    // std::uint32_t
#include <functional> // std::ref
#include <iostream>   // std::cout
#include <thread>     // std::thread
#include <vector>     // std::vector

void square(const std::uint32_t number, std::vector<std::uint32_t>& results, const std::uint32_t index)
{
    results.at(index) = number * number;
}

int main()
{
    const std::vector<std::uint32_t> inputs { 1, 5, 2, 7, 9 };
    const std::uint32_t n_inputs = inputs.size();
    std::vector<std::thread> threads;
    std::vector<std::uint32_t> results;
    threads.resize(n_inputs);
    results.resize(n_inputs);

    for (std::uint32_t i = 0; i < n_inputs; i++)
    {
        threads.at(i) = std::thread { &square, inputs.at(i), std::ref(results), i };
    }

    for (std::thread& my_thread : threads)
    {
        my_thread.join();
    }

    for (std::uint32_t& result : results)
    {
        std::cout << result << "\n";
    }
}
