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

// `yli::data::Datatype` defines the canonical order of datatypes
// that should be followed throughout Ylikuutio code.
//
// Both raw pointers and `std::shared_ptr` pointers may be supported
// to some datatypes in the future. However, only raw pointers are
// supported for `yli::ontology` Entities, as the shared ownership is
// not supported for any of the `yli::ontology` Entities.

namespace yli::data
{
    enum class Datatype
    {
        // Unknown. This should be used as the default.
        UNKNOWN,
        // Primitive datatypes:
        BOOL,
        CHAR,
        FLOAT,
        DOUBLE,
        INT32_T,
        UINT32_T,
        // Raw pointers to primitive datatypes:
        BOOL_POINTER,
        CHAR_POINTER,
        FLOAT_POINTER,
        DOUBLE_POINTER,
        INT32_T_POINTER,
        UINT32_T_POINTER,
        // `yli::ontology` datatypes, 'entity' path.
        ENTITY_POINTER,
        // `yli::ontology` datatypes, 'movable' path.
        MOVABLE_POINTER,
        CONST_MOVABLE_POINTER,
        // `yli::ontology` datatypes, 'simple' path.
        UNIVERSE_POINTER,
        CONST_UNIVERSE_POINTER,
        WORLD_POINTER,
        CONST_WORLD_POINTER,
        SCENE_POINTER,
        CONST_SCENE_POINTER,
        SHADER_POINTER,
        CONST_SHADER_POINTER,
        MATERIAL_POINTER,
        CONST_MATERIAL_POINTER,
        SPECIES_POINTER,
        CONST_SPECIES_POINTER,
        OBJECT_POINTER,
        CONST_OBJECT_POINTER,
        // `yli::ontology` datatypes, 'symbiont' path.
        SYMBIOSIS_POINTER,
        CONST_SYMBIOSIS_POINTER,
        SYMBIONTMATERIAL_POINTER,
        CONST_SYMBIONTMATERIAL_POINTER,
        SYMBIONTSPECIES_POINTER,
        CONST_SYMBIONTSPECIES_POINTER,
        // `yli::ontology` datatypes, 'holobiont' path.
        HOLOBIONT_POINTER,
        CONST_HOLOBIONT_POINTER,
        BIONT_POINTER,
        CONST_BIONT_POINTER,
        // `yli::ontology` datatypes, 'text 2D' path.
        FONT2D_POINTER,
        CONST_FONT2D_POINTER,
        TEXT2D_POINTER,
        CONST_TEXT2D_POINTER,
        // `yli::ontology` datatypes, 'text 3D' path.
        VECTORFONT_POINTER,
        CONST_VECTORFONT_POINTER,
        GLYPH_POINTER,
        CONST_GLYPH_POINTER,
        TEXT3D_POINTER,
        CONST_TEXT3D_POINTER,
        // `yli::ontology` datatypes, 'console' path.
        CONSOLE_POINTER,
        CONST_CONSOLE_POINTER,
        // `yli::ontology` datatypes, 'compute' path.
        COMPUTETASK_POINTER,
        CONST_COMPUTETASK_POINTER,
        // `yli::config` datatypes.
        SETTING_POINTER,
        CONST_SETTING_POINTER,
        // `std::shared_ptr` objects.
        ANY_VALUE_SHARED_PTR,
        ANY_STRUCT_SHARED_PTR,
        // Structs.
        SPHERICAL_COORDINATES_STRUCT_POINTER,
        CONST_SPHERICAL_COORDINATES_STRUCT_POINTER,
        // Raw pointers to standard library datatypes.
        STD_STRING_POINTER,
        CONST_STD_STRING_POINTER,
        // Shared pointers to standard library datatypes.
        STD_VECTOR_INT8_T_SHARED_PTR,
        STD_VECTOR_UINT8_T_SHARED_PTR,
        STD_VECTOR_INT16_T_SHARED_PTR,
        STD_VECTOR_UINT16_T_SHARED_PTR,
        STD_VECTOR_INT32_T_SHARED_PTR,
        STD_VECTOR_UINT32_T_SHARED_PTR,
        STD_VECTOR_FLOAT_SHARED_PTR,
        STD_STRING_SHARED_PTR,
        // Shared pointers to GLM datatypes.
        GLM_VEC3_SHARED_PTR,
        GLM_VEC4_SHARED_PTR
    };
}

#endif