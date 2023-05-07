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

#ifndef YLIKUUTIO_DATA_DATATYPE_HPP_INCLUDED
#define YLIKUUTIO_DATA_DATATYPE_HPP_INCLUDED

// `yli::data::Datatype` defines the canonical order of datatypes
// that should be followed throughout Ylikuutio code.
//
// Only references and raw pointers are supported for `yli::ontology` Entities,
// as they don't support any kind of shared ownership.

namespace yli::data
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
        // Spherical coordinates.
        SPHERICAL_COORDINATES_STRUCT,
        // Systems.
        AUDIO_SYSTEM        = 50,
        // `yli::ontology` datatypes, 'entity' path.
        ENTITY              = 117,
        MOVABLE             = 118,
        // `yli::ontology` datatypes, 'universe' path.
        UNIVERSE            = 119,
        // `yli::ontology` datatypes, 'variable' path.
        VARIABLE            = 120,
        // `yli::ontology` datatypes, 'callback' path.
        CALLBACK_ENGINE     = 121,
        CALLBACK_OBJECT     = 122,
        CALLBACK_PARAMETER  = 123,
        // `yli::ontology` datatypes, 'window' path.
        WINDOW              = 124,
        WIDGET              = 125,
        CAMERA              = 126,
        CAMERAWIDGET        = 127,
        // `yli::ontology` datatypes, 'brain' path.
        BRAIN               = 128,
        // `yli::ontology` datatypes, 'ecosystem' path.
        ECOSYSTEM           = 129,
        // `yli::ontology` datatypes, 'simple' path.
        SCENE               = 130,
        PIPELINE            = 131,
        MATERIAL            = 132,
        SPECIES             = 133,
        OBJECT              = 134,
        // `yli::ontology` datatypes, 'heightmap' path.
        HEIGHTMAP           = 135,
        HEIGHTMAP_SHEET     = 136,
        // `yli::ontology` datatypes, 'symbiont' path.
        SYMBIOSIS           = 137,
        SYMBIONT_MATERIAL   = 138,
        SYMBIONT_SPECIES    = 139,
        // `yli::ontology` datatypes, 'holobiont' path.
        HOLOBIONT           = 140,
        BIONT               = 141,
        // `yli::ontology` datatypes, 'shapeshifter' path.
        SHAPESHIFTER_TRANSFORMATION = 142,
        SHAPESHIFTER_SEQUENCE       = 143,
        SHAPESHIFTER_FORM           = 144,
        // `yli::ontology` datatypes, 'text 2D' path.
        FONT_2D                     = 145,
        TEXT_2D                     = 146,
        // `yli::ontology` datatypes, 'text 3D' path.
        VECTOR_FONT                 = 147,
        GLYPH                       = 148,
        TEXT_3D                     = 149,
        // `yli::ontology` datatypes, 'input' path.
        INPUT_MODE                  = 150,
        // `yli::ontology` datatypes, 'audio' path.
        AUDIO_TRACK                 = 151,
        // `yli::ontology` datatypes, 'track' path.
        PLAYLIST                    = 152,
        // `yli::ontology` datatypes, 'console' path.
        CONSOLE                     = 153,
        CONSOLE_CALLBACK_ENGINE     = 154,
        CONSOLE_CALLBACK_OBJECT     = 155,
        // `yli::ontology` datatypes, 'graph' path.
        GRAPH                       = 156,
        NODE                        = 157,
        // `yli::ontology` datatypes, 'compute' path.
        COMPUTETASK                 = 158,
        // `yli::ontology` datatypes, 'lisp' path.
        LISP_FUNCTION                  = 159,
        GENERIC_LISP_FUNCTION_OVERLOAD = 160,
        LISP_FUNCTION_OVERLOAD         = 161
    };
}

#endif
