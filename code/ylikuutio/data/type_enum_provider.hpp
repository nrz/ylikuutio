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

#ifndef YLIKUUTIO_DATA_TYPE_ENUM_PROVIDER_HPP_INCLUDED
#define YLIKUUTIO_DATA_TYPE_ENUM_PROVIDER_HPP_INCLUDED

#include "datatype.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/variable.hpp"
#include "code/ylikuutio/ontology/movable_controller.hpp"
#include "code/ylikuutio/ontology/ecosystem.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/pipeline.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/symbiosis.hpp"
#include "code/ylikuutio/ontology/symbiont_material.hpp"
#include "code/ylikuutio/ontology/symbiont_species.hpp"
#include "code/ylikuutio/ontology/holobiont.hpp"
#include "code/ylikuutio/ontology/biont.hpp"
#include "code/ylikuutio/ontology/shapeshifter_transformation.hpp"
#include "code/ylikuutio/ontology/shapeshifter_sequence.hpp"
#include "code/ylikuutio/ontology/shapeshifter_form.hpp"
#include "code/ylikuutio/ontology/font_2d.hpp"
#include "code/ylikuutio/ontology/text_2d.hpp"
#include "code/ylikuutio/ontology/vector_font.hpp"
#include "code/ylikuutio/ontology/glyph.hpp"
#include "code/ylikuutio/ontology/text_3d.hpp"
#include "code/ylikuutio/ontology/console.hpp"

namespace yli::ontology
{
    class Universe;
}

namespace yli::data
{
    struct TypeEnumProvider
    {
        template<typename T1>
        Datatype get_type_enum() = delete;
    };

    template<>
    inline Datatype TypeEnumProvider::get_type_enum<ontology::Universe>()
    {
        return UNIVERSE;
    }

    template<>
    inline Datatype TypeEnumProvider::get_type_enum<ontology::Variable>()
    {
        return VARIABLE;
    }

    template<>
    inline Datatype TypeEnumProvider::get_type_enum<ontology::MovableController>()
    {
        return MOVABLE_CONTROLLER;
    }

    template<>
    inline Datatype TypeEnumProvider::get_type_enum<ontology::Ecosystem>()
    {
        return ECOSYSTEM;
    }

    template<>
    inline Datatype TypeEnumProvider::get_type_enum<ontology::Scene>()
    {
        return SCENE;
    }

    template<>
    inline Datatype TypeEnumProvider::get_type_enum<ontology::Pipeline>()
    {
        return PIPELINE;
    }

    template<>
    inline Datatype TypeEnumProvider::get_type_enum<ontology::Material>()
    {
        return MATERIAL;
    }

    template<>
    inline Datatype TypeEnumProvider::get_type_enum<ontology::Species>()
    {
        return SPECIES;
    }

    template<>
    inline Datatype TypeEnumProvider::get_type_enum<ontology::Object>()
    {
        return OBJECT;
    }

    template<>
    inline Datatype TypeEnumProvider::get_type_enum<ontology::Symbiosis>()
    {
        return SYMBIOSIS;
    }

    template<>
    inline Datatype TypeEnumProvider::get_type_enum<ontology::SymbiontMaterial>()
    {
        return SYMBIONT_MATERIAL;
    }

    template<>
    inline Datatype TypeEnumProvider::get_type_enum<ontology::SymbiontSpecies>()
    {
        return SYMBIONT_SPECIES;
    }

    template<>
    inline Datatype TypeEnumProvider::get_type_enum<ontology::Holobiont>()
    {
        return HOLOBIONT;
    }

    template<>
    inline Datatype TypeEnumProvider::get_type_enum<ontology::Biont>()
    {
        return BIONT;
    }

    template<>
    inline Datatype TypeEnumProvider::get_type_enum<ontology::ShapeshifterTransformation>()
    {
        return SHAPESHIFTER_TRANSFORMATION;
    }

    template<>
    inline Datatype TypeEnumProvider::get_type_enum<ontology::ShapeshifterSequence>()
    {
        return SHAPESHIFTER_SEQUENCE;
    }

    template<>
    inline Datatype TypeEnumProvider::get_type_enum<ontology::ShapeshifterForm>()
    {
        return SHAPESHIFTER_FORM;
    }

    template<>
    inline Datatype TypeEnumProvider::get_type_enum<ontology::Font2d>()
    {
        return FONT_2D;
    }

    template<>
    inline Datatype TypeEnumProvider::get_type_enum<ontology::Text2d>()
    {
        return TEXT_2D;
    }

    template<>
    inline Datatype TypeEnumProvider::get_type_enum<ontology::VectorFont>()
    {
        return VECTOR_FONT;
    }

    template<>
    inline Datatype TypeEnumProvider::get_type_enum<ontology::Glyph>()
    {
        return GLYPH;
    }

    template<>
    inline Datatype TypeEnumProvider::get_type_enum<ontology::Text3d>()
    {
        return TEXT_3D;
    }

    template<>
    inline Datatype TypeEnumProvider::get_type_enum<ontology::Console>()
    {
        return CONSOLE;
    }
}

#endif
