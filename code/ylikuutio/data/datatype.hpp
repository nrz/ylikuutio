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
    enum class Datatype
    {
        // Unknown. This should be used as the default.
        UNKNOWN,
        // Fundamental types.
        BOOL,
        CHAR,
        FLOAT,
        DOUBLE,
        INT32_T,
        UINT32_T,
        // Strings.
        STD_STRING,
        // Variable-size vectors.
        STD_VECTOR_INT8_T,
        STD_VECTOR_UINT8_T,
        STD_VECTOR_INT16_T,
        STD_VECTOR_UINT16_T,
        STD_VECTOR_INT32_T,
        STD_VECTOR_UINT32_T,
        STD_VECTOR_FLOAT,
        // Fixed-size vectors.
        GLM_VEC3,
        GLM_VEC4,
        // Spherical coordinates.
        SPHERICAL_COORDINATES_STRUCT,
        // `yli::ontology` datatypes, 'entity' path.
        ENTITY,
        MOVABLE,
        // `yli::ontology` datatypes, 'universe' path.
        UNIVERSE,
        // `yli::ontology` datatypes, 'variable' path.
        VARIABLE,
        // `yli::ontology` datatypes, 'window' path.
        WINDOW,
        WIDGET,
        CAMERAWIDGET,
        // `yli::ontology` datatypes, 'brain' path.
        BRAIN,
        // `yli::ontology` datatypes, 'ecosystem' path.
        ECOSYSTEM,
        // `yli::ontology` datatypes, 'simple' path.
        SCENE,
        PIPELINE,
        MATERIAL,
        SPECIES,
        OBJECT,
        // `yli::ontology` datatypes, 'heightmap' path.
        HEIGHTMAP,
        HEIGHTMAP_SHEET,
        // `yli::ontology` datatypes, 'symbiont' path.
        SYMBIOSIS,
        SYMBIONT_MATERIAL,
        SYMBIONT_SPECIES,
        // `yli::ontology` datatypes, 'holobiont' path.
        HOLOBIONT,
        BIONT,
        // `yli::ontology` datatypes, 'shapeshifter' path.
        SHAPESHIFTER_TRANSFORMATION,
        SHAPESHIFTER_SEQUENCE,
        SHAPESHIFTER_FORM,
        // `yli::ontology` datatypes, 'text 2D' path.
        FONT2D,
        TEXT2D,
        // `yli::ontology` datatypes, 'text 3D' path.
        VECTORFONT,
        GLYPH,
        TEXT3D,
        // `yli::ontology` datatypes, 'console' path.
        CONSOLE,
        // `yli::ontology` datatypes, 'compute' path.
        COMPUTETASK
    };
}

#endif
