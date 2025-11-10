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

#ifndef YLIKUUTIO_DATA_TYPE_ENUM_PROVIDER_HPP_INCLUDED
#define YLIKUUTIO_DATA_TYPE_ENUM_PROVIDER_HPP_INCLUDED

#include "datatype.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/variable.hpp"
#include "code/ylikuutio/ontology/brain.hpp"
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
        inline Datatype TypeEnumProvider::get_type_enum<yli::ontology::Universe>()
        {
            return Datatype::UNIVERSE;
        }

    template<>
        inline Datatype TypeEnumProvider::get_type_enum<yli::ontology::Variable>()
        {
            return Datatype::VARIABLE;
        }

    template<>
        inline Datatype TypeEnumProvider::get_type_enum<yli::ontology::Brain>()
        {
            return Datatype::BRAIN;
        }

    template<>
        inline Datatype TypeEnumProvider::get_type_enum<yli::ontology::Ecosystem>()
        {
            return Datatype::ECOSYSTEM;
        }

    template<>
        inline Datatype TypeEnumProvider::get_type_enum<yli::ontology::Scene>()
        {
            return Datatype::SCENE;
        }

    template<>
        inline Datatype TypeEnumProvider::get_type_enum<yli::ontology::Pipeline>()
        {
            return Datatype::PIPELINE;
        }

    template<>
        inline Datatype TypeEnumProvider::get_type_enum<yli::ontology::Material>()
        {
            return Datatype::MATERIAL;
        }

    template<>
        inline Datatype TypeEnumProvider::get_type_enum<yli::ontology::Species>()
        {
            return Datatype::SPECIES;
        }

    template<>
        inline Datatype TypeEnumProvider::get_type_enum<yli::ontology::Object>()
        {
            return Datatype::OBJECT;
        }

    template<>
        inline Datatype TypeEnumProvider::get_type_enum<yli::ontology::Symbiosis>()
        {
            return Datatype::SYMBIOSIS;
        }

    template<>
        inline Datatype TypeEnumProvider::get_type_enum<yli::ontology::SymbiontMaterial>()
        {
            return Datatype::SYMBIONT_MATERIAL;
        }

    template<>
        inline Datatype TypeEnumProvider::get_type_enum<yli::ontology::SymbiontSpecies>()
        {
            return Datatype::SYMBIONT_SPECIES;
        }

    template<>
        inline Datatype TypeEnumProvider::get_type_enum<yli::ontology::Holobiont>()
        {
            return Datatype::HOLOBIONT;
        }

    template<>
        inline Datatype TypeEnumProvider::get_type_enum<yli::ontology::Biont>()
        {
            return Datatype::BIONT;
        }

    template<>
        inline Datatype TypeEnumProvider::get_type_enum<yli::ontology::ShapeshifterTransformation>()
        {
            return Datatype::SHAPESHIFTER_TRANSFORMATION;
        }

    template<>
        inline Datatype TypeEnumProvider::get_type_enum<yli::ontology::ShapeshifterSequence>()
        {
            return Datatype::SHAPESHIFTER_SEQUENCE;
        }

    template<>
        inline Datatype TypeEnumProvider::get_type_enum<yli::ontology::ShapeshifterForm>()
        {
            return Datatype::SHAPESHIFTER_FORM;
        }

    template<>
        inline Datatype TypeEnumProvider::get_type_enum<yli::ontology::Font2d>()
        {
            return Datatype::FONT_2D;
        }

    template<>
        inline Datatype TypeEnumProvider::get_type_enum<yli::ontology::Text2d>()
        {
            return Datatype::TEXT_2D;
        }

    template<>
        inline Datatype TypeEnumProvider::get_type_enum<yli::ontology::VectorFont>()
        {
            return Datatype::VECTOR_FONT;
        }

    template<>
        inline Datatype TypeEnumProvider::get_type_enum<yli::ontology::Glyph>()
        {
            return Datatype::GLYPH;
        }

    template<>
        inline Datatype TypeEnumProvider::get_type_enum<yli::ontology::Text3d>()
        {
            return Datatype::TEXT_3D;
        }

    template<>
        inline Datatype TypeEnumProvider::get_type_enum<yli::ontology::Console>()
        {
            return Datatype::CONSOLE;
        }
}

#endif
