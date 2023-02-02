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

#ifndef HIRVI_DATATYPE_HPP_INCLUDED
#define HIRVI_DATATYPE_HPP_INCLUDED

// `yli::data::Datatype` defines the canonical order of datatypes
// that should be followed throughout Ylikuutio code.
//
// Only references and raw pointers are supported for `yli::ontology` Entities,
// as they don't support any kind of shared ownership.

namespace hirvi
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
        CONST_STD_STRING,
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
        CONST_GLM_VEC3,
        GLM_VEC4,
        CONST_GLM_VEC4,
        // Spherical coordinates.
        SPHERICAL_COORDINATES_STRUCT,
        CONST_SPHERICAL_COORDINATES_STRUCT,
        // `yli::ontology` datatypes, 'entity' path.
        ENTITY,
        MOVABLE,
        CONST_MOVABLE,
        // `yli::ontology` datatypes, 'universe' path.
        UNIVERSE,
        CONST_UNIVERSE,
        // `yli::ontology` datatypes, 'variable' path.
        VARIABLE,
        CONST_VARIABLE,
        // `yli::ontology` datatypes, 'window' path.
        WINDOW,
        CONST_WINDOW,
        WIDGET,
        CONST_WIDGET,
        CAMERAWIDGET,
        CONST_CAMERAWIDGET,
        // `yli::ontology` datatypes, 'brain' path.
        BRAIN,
        CONST_BRAIN,
        // `yli::ontology` datatypes, 'ecosystem' path.
        ECOSYSTEM,
        CONST_ECOSYSTEM,
        // `yli::ontology` datatypes, 'simple' path.
        SCENE,
        CONST_SCENE,
        PIPELINE,
        CONST_PIPELINE,
        MATERIAL,
        CONST_MATERIAL,
        SPECIES,
        CONST_SPECIES,
        OBJECT,
        CONST_OBJECT,
        // `yli::ontology` datatypes, 'heightmap' path.
        HEIGHTMAP,
        CONST_HEIGHTMAP,
        HEIGHTMAP_SHEET,
        CONST_HEIGHTMAP_SHEET,
        // `yli::ontology` datatypes, 'symbiont' path.
        SYMBIOSIS,
        CONST_SYMBIOSIS,
        SYMBIONTMATERIAL,
        CONST_SYMBIONTMATERIAL,
        SYMBIONTSPECIES,
        CONST_SYMBIONTSPECIES,
        // `yli::ontology` datatypes, 'holobiont' path.
        HOLOBIONT,
        CONST_HOLOBIONT,
        BIONT,
        CONST_BIONT,
        // `yli::ontology` datatypes, 'shapeshifter' path.
        SHAPESHIFTER_TRANSFORMATION,
        CONST_SHAPESHIFTER_TRANSFORMATION,
        SHAPESHIFTER_SEQUENCE,
        CONST_SHAPESHIFTER_SEQUENCE,
        SHAPESHIFTER_FORM,
        CONST_SHAPESHIFTER_FORM,
        // `yli::ontology` datatypes, 'text 2D' path.
        FONT2D,
        CONST_FONT2D,
        TEXT2D,
        CONST_TEXT2D,
        // `yli::ontology` datatypes, 'text 3D' path.
        VECTORFONT,
        CONST_VECTORFONT,
        GLYPH,
        CONST_GLYPH,
        TEXT3D,
        CONST_TEXT3D,
        // `yli::ontology` datatypes, 'console' path.
        CONSOLE,
        CONST_CONSOLE,
        // `yli::ontology` datatypes, 'compute' path.
        COMPUTETASK,
        CONST_COMPUTETASK,
        FRAMEBUFFER_MATERIAL,
        CONST_FRAMEBUFFER_MATERIAL,
        // Custom datatypes of Hirvi.
        CAT,
        ELK,
        POLICE_CAR,
        POLICE_DOG,
        POLICE_HELICOPTER,
        POLICE_HORSE,
        POLICE_TRAIN,
        POLICE_TRAM,
        TRAIN
    };
}

#endif
