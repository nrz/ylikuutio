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

#include <future>   // std::async, std::launch, std::future
#include <iostream> // std::cout
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

uint32_t square(const uint32_t number)
{
    return number * number;
}

int main()
{
    const std::vector<uint32_t> inputs { 1, 5, 2, 7, 9 };
    const uint32_t n_inputs = inputs.size();
    std::vector<std::future<uint32_t>> future_results;
    future_results.resize(n_inputs);

    for (uint32_t i = 0; i < n_inputs; i++)
    {
        future_results.at(i) = std::async(std::launch::async, square, inputs.at(i));
    }

    for (const auto& my_future : future_results)
    {
        my_future.wait();
    }

    for (auto& my_future : future_results)
    {
        std::cout << my_future.get() << "\n";
    }
}
