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

#ifndef HIRVI_DATA_DATATYPE_HPP_INCLUDED
#define HIRVI_DATA_DATATYPE_HPP_INCLUDED

#include "code/ylikuutio/memory/handle.hpp"

// `yli::data::Datatype` defines the canonical order of datatypes
// that should be followed throughout Ylikuutio code.
//
// Only references and raw pointers are supported for `yli::ontology` Entities,
// as they don't support any kind of shared ownership.

namespace hirvi::data
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
        INT64_T    = 7,
        UINT64_T   = 8,
        // Strings.
        STD_STRING = 9,
        // Variable-size vectors.
        STD_VECTOR_INT8_T   = 11,
        STD_VECTOR_UINT8_T  = 12,
        STD_VECTOR_INT16_T  = 13,
        STD_VECTOR_UINT16_T = 14,
        STD_VECTOR_INT32_T  = 15,
        STD_VECTOR_UINT32_T = 16,
        STD_VECTOR_FLOAT    = 17,
        // Fixed-size vectors.
        GLM_VEC3            = 21,
        GLM_VEC4            = 22,
        // Systems.
        EVENT_SYSTEM        = 30, // ESYS
        INPUT_SYSTEM        = 40, // ISYS
        AUDIO_SYSTEM        = 50, // ASYS
        // `yli::ontology` datatypes, interfaces.
        ENTITY              = 110, // ENTY
        LISP_CONTEXT        = 111, // LCTX
        LISP_FUNCTION                  = 112, // LFUN
        GENERIC_LISP_FUNCTION_OVERLOAD = 113, // GLFO
        CAPABILITY                     = 114, // CAPB
        MESH_PROVIDER       = 116, // MPRO
        ABSTRACT_MOVABLE    = 117, // AMOV
        // `yli::ontology` datatypes, 'universe' path.
        UNIVERSE            = 119, // UNIV
        // `yli::ontology` datatypes, 'variable' path.
        VARIABLE            = 120, // VARI
        // `yli::ontology` datatypes, 'callback' path.
        ABSTRACT_CALLBACK_ENGINE = 121, // ACEN
        CALLBACK_ENGINE     = 124, // CENG
        CALLBACK_OBJECT     = 125, // COBJ
        CALLBACK_PARAMETER  = 126, // CPAR
        // `yli::ontology` datatypes, 'window' path.
        WINDOW              = 130, // WNDW
        WIDGET              = 131, // WDGT
        // `yli::ontology` datatypes, 'ecosystem' path.
        ECOSYSTEM             = 150, // ECOS
        // `yli::ontology` datatypes, 'scene' path.
        SCENE                 = 160, // SCEN
        // `yli::ontology` datatypes, 'movable_controller' path.
        MOVABLE_CONTROLLER                   = 161, // MCTL
        MOVABLE_CONTROLLER_LISP_FUNCTION                  = 162, // MCLF
        GENERIC_MOVABLE_CONTROLLER_LISP_FUNCTION_OVERLOAD = 163, // GMCL
        MOVABLE_CONTROLLER_LISP_FUNCTION_OVERLOAD         = 164, // MCFO
        WAYPOINT                             = 165, // WAYP
        // `yli::ontology` datatypes, 'camera' path.
        CAMERA                = 166, // CAMR
        CAMERA_WIDGET         = 167, // CAMW
        // `yli::ontology` datatypes, 'simple' path.
        PIPELINE              = 170, // PIPE
        MATERIAL              = 171, // MATE
        SPECIES               = 172, // SPEC
        OBJECT                = 173, // OBJE
        // `yli::ontology` datatypes, 'heightmap' path.
        HEIGHTMAP             = 174, // HMAP
        HEIGHTMAP_SECTOR      = 175, // HSEC
        // `yli::ontology` datatypes, 'citymodel' path.
        CITYMODEL             = 176, // CMOD
        CITYMODEL_SECTOR      = 177, // CSEC
        CITYMODEL_MATERIAL    = 178, // CMAT
        CITYMODEL_MESH        = 189, // CMSH
        // `yli::ontology` datatypes, 'symbiont' path.
        SYMBIOSIS             = 180, // SYMB
        SYMBIONT_MATERIAL     = 181, // SYMM
        SYMBIONT_SPECIES      = 182, // SYMS
        // `yli::ontology` datatypes, 'ability' path.
        ABILITY               = 185, // ABIL
        // `yli::ontology` datatypes, 'holobiont' path.
        HOLOBIONT             = 190, // HBNT
        BIONT                 = 191, // BION
        // `yli::ontology` datatypes, 'skill' path.
        SKILL                 = 195, // SKIL
        // `yli::ontology` datatypes, 'shapeshifter' path.
        SHAPESHIFTER_TRANSFORMATION = 200, // SSTR
        SHAPESHIFTER_SEQUENCE       = 201, // SSSQ
        SHAPESHIFTER_FORM           = 202, // SSFR
        SHAPESHIFTER                = 203, // SSHF
        // `yli::ontology` datatypes, 'text 2D' path.
        FONT_2D                     = 210, // FO2D
        TEXT_2D                     = 211, // TX2D
        // `yli::ontology` datatypes, 'text 3D' path.
        VECTOR_FONT                 = 220, // VFNT
        GLYPH                       = 221, // GLYP
        TEXT_3D                     = 222, // TX3D
        GLYPH_OBJECT                = 223, // GLOB
        // `yli::ontology` datatypes, 'input' path.
        INPUT_MODE                  = 230, // IMOD
        KEY_BINDING                 = 231, // KBND
        // `yli::ontology` datatypes, 'track' path.
        PLAYLIST                    = 240, // PLIS
        // `yli::ontology` datatypes, 'audio' path.
        AUDIO_TRACK                 = 250, // ATRK
        // `yli::ontology` datatypes, 'console' path.
        CONSOLE                     = 261, // CONS
        CONSOLE_CALLBACK_ENGINE     = 262, // CCEN
        CONSOLE_CALLBACK_OBJECT     = 263, // CCOB
        CONSOLE_CALLBACK_PARAMETER  = 264, // CCPR
        CONSOLE_LISP_FUNCTION                  = 265, // CLFU
        GENERIC_CONSOLE_LISP_FUNCTION_OVERLOAD = 266, // GCLF
        CONSOLE_LISP_FUNCTION_OVERLOAD         = 267, // CLFO
        // `yli::ontology` datatypes, 'compute' path.
        COMPUTE_TASK                = 280, // CTSK
        // Custom datatypes of Hirvi.
        HIRVI_SCENE       = 500, // HSCE
        POLICE_CONTROL_CENTER = 501, // PCON
        CAT               = 511, // CAT!
        ELK               = 512, // ELK!
        POLICE_BEAR       = 520, // PBEA
        POLICE_CAR        = 521, // PCAR
        POLICE_DOG        = 522, // PDOG
        POLICE_HELICOPTER = 523, // PHEL
        POLICE_HORSE      = 524, // PHRS
        POLICE_TRAIN      = 525, // PTRN
        POLICE_TRAM       = 526, // PTRM
        TRAIN             = 530, // TRAN
        MAX_VALUE         = TRAIN
    };

    static_assert(MAX_VALUE < (1 << yli::memory::Handle::n_type_bits));
}

#endif
