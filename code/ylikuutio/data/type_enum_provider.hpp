// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
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
            yli::data::Datatype get_type_enum()
            {
                static_assert(sizeof(T1) == -1, "You need to specialize `yli::data::TypeEnumProvider::get_type_enum` for the type!");
                return yli::data::Datatype::UNKNOWN;
            }
    };

    template<>
        inline yli::data::Datatype TypeEnumProvider::get_type_enum<yli::ontology::Universe>()
        {
            return yli::data::Datatype::UNIVERSE;
        }

    template<>
        inline yli::data::Datatype TypeEnumProvider::get_type_enum<yli::ontology::Variable>()
        {
            return yli::data::Datatype::VARIABLE;
        }

    template<>
        inline yli::data::Datatype TypeEnumProvider::get_type_enum<yli::ontology::Brain>()
        {
            return yli::data::Datatype::BRAIN;
        }

    template<>
        inline yli::data::Datatype TypeEnumProvider::get_type_enum<yli::ontology::Ecosystem>()
        {
            return yli::data::Datatype::ECOSYSTEM;
        }

    template<>
        inline yli::data::Datatype TypeEnumProvider::get_type_enum<yli::ontology::Scene>()
        {
            return yli::data::Datatype::SCENE;
        }

    template<>
        inline yli::data::Datatype TypeEnumProvider::get_type_enum<yli::ontology::Pipeline>()
        {
            return yli::data::Datatype::PIPELINE;
        }

    template<>
        inline yli::data::Datatype TypeEnumProvider::get_type_enum<yli::ontology::Material>()
        {
            return yli::data::Datatype::MATERIAL;
        }

    template<>
        inline yli::data::Datatype TypeEnumProvider::get_type_enum<yli::ontology::Species>()
        {
            return yli::data::Datatype::SPECIES;
        }

    template<>
        inline yli::data::Datatype TypeEnumProvider::get_type_enum<yli::ontology::Object>()
        {
            return yli::data::Datatype::OBJECT;
        }

    template<>
        inline yli::data::Datatype TypeEnumProvider::get_type_enum<yli::ontology::Symbiosis>()
        {
            return yli::data::Datatype::SYMBIOSIS;
        }

    template<>
        inline yli::data::Datatype TypeEnumProvider::get_type_enum<yli::ontology::SymbiontMaterial>()
        {
            return yli::data::Datatype::SYMBIONT_MATERIAL;
        }

    template<>
        inline yli::data::Datatype TypeEnumProvider::get_type_enum<yli::ontology::SymbiontSpecies>()
        {
            return yli::data::Datatype::SYMBIONT_SPECIES;
        }

    template<>
        inline yli::data::Datatype TypeEnumProvider::get_type_enum<yli::ontology::Holobiont>()
        {
            return yli::data::Datatype::HOLOBIONT;
        }

    template<>
        inline yli::data::Datatype TypeEnumProvider::get_type_enum<yli::ontology::Biont>()
        {
            return yli::data::Datatype::BIONT;
        }

    template<>
        inline yli::data::Datatype TypeEnumProvider::get_type_enum<yli::ontology::ShapeshifterTransformation>()
        {
            return yli::data::Datatype::SHAPESHIFTER_TRANSFORMATION;
        }

    template<>
        inline yli::data::Datatype TypeEnumProvider::get_type_enum<yli::ontology::ShapeshifterSequence>()
        {
            return yli::data::Datatype::SHAPESHIFTER_SEQUENCE;
        }

    template<>
        inline yli::data::Datatype TypeEnumProvider::get_type_enum<yli::ontology::ShapeshifterForm>()
        {
            return yli::data::Datatype::SHAPESHIFTER_FORM;
        }

    template<>
        inline yli::data::Datatype TypeEnumProvider::get_type_enum<yli::ontology::Font2D>()
        {
            return yli::data::Datatype::FONT_2D;
        }

    template<>
        inline yli::data::Datatype TypeEnumProvider::get_type_enum<yli::ontology::Text2d>()
        {
            return yli::data::Datatype::TEXT_2D;
        }

    template<>
        inline yli::data::Datatype TypeEnumProvider::get_type_enum<yli::ontology::VectorFont>()
        {
            return yli::data::Datatype::VECTOR_FONT;
        }

    template<>
        inline yli::data::Datatype TypeEnumProvider::get_type_enum<yli::ontology::Glyph>()
        {
            return yli::data::Datatype::GLYPH;
        }

    template<>
        inline yli::data::Datatype TypeEnumProvider::get_type_enum<yli::ontology::Text3d>()
        {
            return yli::data::Datatype::TEXT_3D;
        }

    template<>
        inline yli::data::Datatype TypeEnumProvider::get_type_enum<yli::ontology::Console>()
        {
            return yli::data::Datatype::CONSOLE;
        }
}

#endif
