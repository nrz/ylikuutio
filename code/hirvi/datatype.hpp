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

#ifndef HIRVI_DATATYPE_HPP_INCLUDED
#define HIRVI_DATATYPE_HPP_INCLUDED

// `yli::data::Datatype` defines the canonical order of datatypes
// that should be followed throughout Ylikuutio code.
//
// Only references and raw pointers are supported for `yli::ontology` Entities,
// as they don't support any kind of shared ownership.

namespace hirvi
{
    enum Datatype
    {
        // Unknown. This should be used as the default.
        UNKNOWN = 0,
        // Fundamental types.
        BOOL = 1,
        CHAR = 2,
        FLOAT = 3,
        DOUBLE = 4,
        INT32_T = 5,
        UINT32_T = 6,
        // Strings.
        STD_STRING = 7,
        // Variable-size vectors.
        STD_VECTOR_INT8_T   = 8,
        STD_VECTOR_UINT8_T  = 9,
        STD_VECTOR_INT16_T  = 10,
        STD_VECTOR_UINT16_T = 11,
        STD_VECTOR_INT32_T  = 12,
        STD_VECTOR_UINT32_T = 13,
        STD_VECTOR_FLOAT    = 14,
        // Fixed-size vectors.
        GLM_VEC3 = 15,
        GLM_VEC4 = 16,
        // Spherical coordinates.
        SPHERICAL_COORDINATES_STRUCT,
        // `yli::ontology` datatypes, 'entity' path.
        ENTITY   = 17,
        MOVABLE  = 18,
        // `yli::ontology` datatypes, 'universe' path.
        UNIVERSE = 19,
        // `yli::ontology` datatypes, 'variable' path.
        VARIABLE = 20,
        // `yli::ontology` datatypes, 'window' path.
        WINDOW       = 21,
        WIDGET       = 22,
        CAMERA       = 23,
        CAMERAWIDGET = 24,
        // `yli::ontology` datatypes, 'brain' path.
        BRAIN        = 25,
        // `yli::ontology` datatypes, 'ecosystem' path.
        ECOSYSTEM    = 26,
        // `yli::ontology` datatypes, 'simple' path.
        SCENE        = 27,
        PIPELINE     = 28,
        MATERIAL     = 29,
        SPECIES      = 30,
        OBJECT       = 31,
        // `yli::ontology` datatypes, 'heightmap' path.
        HEIGHTMAP       = 32,
        HEIGHTMAP_SHEET = 33,
        // `yli::ontology` datatypes, 'symbiont' path.
        SYMBIOSIS         = 34,
        SYMBIONT_MATERIAL = 35,
        SYMBIONT_SPECIES  = 36,
        // `yli::ontology` datatypes, 'holobiont' path.
        HOLOBIONT         = 37,
        BIONT             = 38,
        // `yli::ontology` datatypes, 'shapeshifter' path.
        SHAPESHIFTER_TRANSFORMATION = 39,
        SHAPESHIFTER_SEQUENCE       = 40,
        SHAPESHIFTER_FORM           = 41,
        // `yli::ontology` datatypes, 'text 2D' path.
        FONT2D                      = 42,
        TEXT2D                      = 43,
        // `yli::ontology` datatypes, 'text 3D' path.
        VECTORFONT                  = 44,
        GLYPH                       = 45,
        TEXT3D                      = 46,
        // `yli::ontology` datatypes, 'console' path.
        CONSOLE                     = 47,
        // `yli::ontology` datatypes, 'compute' path.
        COMPUTETASK                 = 48,
        // `yli::ontology` datatypes, 'lisp' path.
        LISP_FUNCTION                  = 49,
        GENERIC_LISP_FUNCTION_OVERLOAD = 50,
        LISP_FUNCTION_OVERLOAD         = 51,
        // Custom datatypes of Hirvi.
        CAT               = 101,
        ELK               = 102,
        POLICE_CAR        = 103,
        POLICE_DOG        = 104,
        POLICE_HELICOPTER = 105,
        POLICE_HORSE      = 106,
        POLICE_TRAIN      = 107,
        POLICE_TRAM       = 108,
        TRAIN             = 109
    };
}

#endif
