// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
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

#ifndef __DATATYPE_HPP_INCLUDED
#define __DATATYPE_HPP_INCLUDED

namespace yli
{
    namespace common
    {
        enum class Datatype
        {
            UNKNOWN,
            ANY_STRUCT_SHARED_PTR,
            BOOL,
            CHAR,
            FLOAT,
            DOUBLE,
            INT32_T,
            UINT32_T,
            BOOL_POINTER,
            FLOAT_POINTER,
            DOUBLE_POINTER,
            INT32_T_POINTER,
            UINT32_T_POINTER,
            UNIVERSE_POINTER,
            WORLD_POINTER,
            SCENE_POINTER,
            SHADER_POINTER,
            MATERIAL_POINTER,
            SPECIES_POINTER,
            OBJECT_POINTER,
            VECTORFONT_POINTER,
            GLYPH_POINTER,
            TEXT3D_POINTER,
            SYMBIOSIS_POINTER,
            TEXT2D_POINTER,
            CONSOLE_POINTER,
            MOVABLE_POINTER,
            CONST_MOVABLE_POINTER,
            SPHERICAL_COORDINATES_STRUCT_POINTER,
            STD_STRING_POINTER,
            CONST_STD_STRING_POINTER,
            STD_VECTOR_INT8_T_SHARED_PTR,
            STD_VECTOR_UINT8_T_SHARED_PTR,
            STD_VECTOR_INT16_T_SHARED_PTR,
            STD_VECTOR_UINT16_T_SHARED_PTR,
            STD_VECTOR_INT32_T_SHARED_PTR,
            STD_VECTOR_UINT32_T_SHARED_PTR,
            STD_VECTOR_FLOAT_SHARED_PTR,
            GLM_VEC3_POINTER,
            GLM_VEC4_POINTER
        };
    }
}

#endif
