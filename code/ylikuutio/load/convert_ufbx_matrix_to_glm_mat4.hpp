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

#ifndef YLIKUUTIO_LOAD_CONVERT_UFBX_MATRIX_TO_GLM_MAT4_HPP_INCLUDED
#define YLIKUUTIO_LOAD_CONVERT_UFBX_MATRIX_TO_GLM_MAT4_HPP_INCLUDED

#include <ufbx.h>

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

namespace yli::load
{
    glm::mat4 convert_ufbx_matrix_to_glm_mat4(const ufbx_matrix* my_ufbx_matrix);
}

#endif
