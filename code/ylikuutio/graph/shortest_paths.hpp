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

#ifndef YLIKUUTIO_GRAPH_SHORTEST_PATHS_HPP_INCLUDED
#define YLIKUUTIO_GRAPH_SHORTEST_PATHS_HPP_INCLUDED

// Include standard headers
#include <memory>  // std::make_shared, std::shared_ptr

namespace yli::linear_algebra
{
    class Matrix;
}

namespace yli::graph
{
    // TODO: convert `yli::linear_algebra::Matrix` into a class template.
    // TODO: convert this function into a function template.
    // Then, the maximum value of `T` is considered as infinite distance (no link).
    std::shared_ptr<yli::linear_algebra::Matrix> floyd_warshall(const yli::linear_algebra::Matrix& adjacency_matrix);
}

#endif
