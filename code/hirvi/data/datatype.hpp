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

#ifndef HIRVI_DATA_DATATYPE_HPP_INCLUDED
#define HIRVI_DATA_DATATYPE_HPP_INCLUDED

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
        UNKNOWN    = 0,
        // Fundamental types.
        BOOL       = 1,
        CHAR       = 2,
        FLOAT      = 3,
        DOUBLE     = 4,
        INT32_T    = 5,
        UINT32_T   = 6,
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
        GLM_VEC3            = 15,
        GLM_VEC4            = 16,
        // Systems.
        EVENT_SYSTEM        = 30,
        INPUT_SYSTEM        = 40,
        AUDIO_SYSTEM        = 50,
        // `yli::ontology` datatypes, interfaces.
        ENTITY              = 110,
        MESH_PROVIDER       = 111,
        MOVABLE             = 112,
        // `yli::ontology` datatypes, 'universe' path.
        UNIVERSE            = 119,
        // `yli::ontology` datatypes, 'variable' path.
        VARIABLE            = 120,
        // `yli::ontology` datatypes, 'callback' path.
        GENERIC_CALLBACK_ENGINE    = 121,
        GENERIC_CALLBACK_OBJECT    = 122,
        GENERIC_CALLBACK_PARAMETER = 123,
        CALLBACK_ENGINE     = 124,
        CALLBACK_OBJECT     = 125,
        CALLBACK_PARAMETER  = 126,
        // `yli::ontology` datatypes, 'window' path.
        WINDOW              = 130,
        WIDGET              = 131,
        // `yli::ontology` datatypes, 'ecosystem' path.
        ECOSYSTEM             = 150,
        // `yli::ontology` datatypes, 'scene' path.
        SCENE                 = 160,
        // `yli::ontology` datatypes, 'brain' path.
        BRAIN                 = 161,
        WAYPOINT              = 162,
        // `yli::ontology` datatypes, 'camera' path.
        CAMERA                = 163,
        CAMERA_WIDGET         = 164,
        // `yli::ontology` datatypes, 'simple' path.
        PIPELINE              = 165,
        MATERIAL              = 166,
        SPECIES               = 167,
        OBJECT                = 168,
        // `yli::ontology` datatypes, 'heightmap' path.
        HEIGHTMAP             = 170,
        HEIGHTMAP_SHEET       = 171,
        // `yli::ontology` datatypes, 'symbiont' path.
        SYMBIOSIS             = 180,
        SYMBIONT_MATERIAL     = 181,
        SYMBIONT_SPECIES      = 182,
        // `yli::ontology` datatypes, 'holobiont' path.
        HOLOBIONT             = 190,
        BIONT                 = 191,
        // `yli::ontology` datatypes, 'shapeshifter' path.
        SHAPESHIFTER_TRANSFORMATION = 200,
        SHAPESHIFTER_SEQUENCE       = 201,
        SHAPESHIFTER_FORM           = 202,
        SHAPESHIFTER                = 203,
        // `yli::ontology` datatypes, 'text 2D' path.
        FONT_2D                     = 210,
        TEXT_2D                     = 211,
        // `yli::ontology` datatypes, 'text 3D' path.
        VECTOR_FONT                 = 220,
        GLYPH                       = 221,
        TEXT_3D                     = 222,
        GLYPH_OBJECT                = 223,
        // `yli::ontology` datatypes, 'input' path.
        INPUT_MODE                  = 230,
        KEY_BINDING                 = 231,
        // `yli::ontology` datatypes, 'track' path.
        PLAYLIST                    = 240,
        // `yli::ontology` datatypes, 'audio' path.
        AUDIO_TRACK                 = 250,
        // `yli::ontology` datatypes, 'console' path.
        CONSOLE                     = 260,
        CONSOLE_CALLBACK_ENGINE     = 261,
        CONSOLE_CALLBACK_OBJECT     = 262,
        CONSOLE_CALLBACK_PARAMETER  = 263,
        // `yli::ontology` datatypes, 'graph' path.
        GRAPH                       = 270,
        NODE                        = 271,
        // `yli::ontology` datatypes, 'compute' path.
        COMPUTE_TASK                = 280,
        // `yli::ontology` datatypes, 'lisp' path.
        LISP_FUNCTION                  = 290,
        GENERIC_LISP_FUNCTION_OVERLOAD = 291,
        LISP_FUNCTION_OVERLOAD         = 292,
        // Custom datatypes of Hirvi.
        CAT               = 1001,
        ELK               = 1002,
        POLICE_CAR        = 1003,
        POLICE_DOG        = 1004,
        POLICE_HELICOPTER = 1005,
        POLICE_HORSE      = 1006,
        POLICE_TRAIN      = 1007,
        POLICE_TRAM       = 1008,
        TRAIN             = 1009,
        MAX_VALUE         = TRAIN + 1
    };
}

#endif
