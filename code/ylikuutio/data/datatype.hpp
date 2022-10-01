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
        // Strings.
        STD_STRING_REF,
        CONST_STD_STRING_REF,
        // `yli::ontology` datatypes, 'entity' path.
        ENTITY_POINTER,
        // `yli::ontology` datatypes, 'universe' path.
        UNIVERSE_POINTER,
        CONST_UNIVERSE_POINTER,
        // `yli::ontology` datatypes, 'variable' path.
        VARIABLE_POINTER,
        CONST_VARIABLE_POINTER,
        // `yli::ontology` datatypes, 'window' path.
        WINDOW_POINTER,
        CONST_WINDOW_POINTER,
        WIDGET_POINTER,
        CONST_WIDGET_POINTER,
        CAMERAWIDGET_POINTER,
        CONST_CAMERAWIDGET_POINTER,
        // `yli::ontology` datatypes, 'brain' path.
        BRAIN_POINTER,
        CONST_BRAIN_POINTER,
        // `yli::ontology` datatypes, 'movable' path.
        MOVABLE_POINTER,
        CONST_MOVABLE_POINTER,
        // `yli::ontology` datatypes, 'ecosystem' path.
        ECOSYSTEM_POINTER,
        CONST_ECOSYSTEM_POINTER,
        // `yli::ontology` datatypes, 'simple' path.
        SCENE_POINTER,
        CONST_SCENE_POINTER,
        PIPELINE_POINTER,
        CONST_PIPELINE_POINTER,
        MATERIAL_POINTER,
        CONST_MATERIAL_POINTER,
        SPECIES_POINTER,
        CONST_SPECIES_POINTER,
        OBJECT_POINTER,
        CONST_OBJECT_POINTER,
        // `yli::ontology` datatypes, 'heightmap' path.
        HEIGHTMAP_POINTER,
        CONST_HEIGHTMAP_POINTER,
        HEIGHTMAP_SHEET_POINTER,
        CONST_HEIGHTMAP_SHEET_POINTER,
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
        // `yli::ontology` datatypes, 'shapeshifter' path.
        SHAPESHIFTER_TRANSFORMATION_POINTER,
        CONST_SHAPESHIFTER_TRANSFORMATION_POINTER,
        SHAPESHIFTER_SEQUENCE_POINTER,
        CONST_SHAPESHIFTER_SEQUENCE_POINTER,
        SHAPESHIFTER_FORM_POINTER,
        CONST_SHAPESHIFTER_FORM_POINTER,
        // `yli::ontology` datatypes, 'voxel' path.
        CHUNK_MASTER_POINTER,
        CONST_CHUNK_MASTER_POINTER,
        CHUNK_POINTER,
        CONST_CHUNK_POINTER,
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
        FRAMEBUFFER_MATERIAL_POINTER,
        CONST_FRAMEBUFFER_MATERIAL_POINTER,
        // Structs.
        SPHERICAL_COORDINATES_STRUCT_POINTER,
        CONST_SPHERICAL_COORDINATES_STRUCT_POINTER,
    };
}

#endif
