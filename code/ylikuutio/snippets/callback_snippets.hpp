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

#ifndef YLIKUUTIO_SNIPPETS_CALLBACK_SNIPPETS_HPP_INCLUDED
#define YLIKUUTIO_SNIPPETS_CALLBACK_SNIPPETS_HPP_INCLUDED

// Include standard headers
#include <optional> // std::optional

namespace yli::data
{
    class AnyValue;
}

namespace yli::ontology
{
    class GenericParentModule;
    class Universe;
    class CallbackEngine;
    class CallbackObject;
    class CallbackParameter;
}

namespace yli::snippets
{
    std::optional<data::AnyValue> square(
            ontology::Universe&,
            ontology::CallbackEngine*,
            ontology::CallbackObject*,
            ontology::GenericParentModule& input_parameters,
            const data::AnyValue&);

    std::optional<data::AnyValue> square_last(
            ontology::Universe&,
            ontology::CallbackEngine* callback_engine,
            ontology::CallbackObject*,
            ontology::GenericParentModule& input_parameters,
            const data::AnyValue&);

    std::optional<data::AnyValue> expt(
            ontology::Universe&,
            ontology::CallbackEngine*,
            ontology::CallbackObject*,
            ontology::GenericParentModule& input_parameters,
            const data::AnyValue&);

    std::optional<data::AnyValue> expt_with_named_inputs(
            ontology::Universe&,
            ontology::CallbackEngine*,
            ontology::CallbackObject* callback_object,
            ontology::GenericParentModule&,
            const data::AnyValue&);

    std::optional<data::AnyValue> neg(
            ontology::Universe&,
            ontology::CallbackEngine*,
            ontology::CallbackObject*,
            ontology::GenericParentModule& input_parameters,
            const data::AnyValue&);

    std::optional<data::AnyValue> nop(
            ontology::Universe&,
            ontology::CallbackEngine*,
            ontology::CallbackObject*,
            ontology::GenericParentModule& /* input_parameters */,
            const data::AnyValue&);

    std::optional<data::AnyValue> return_uint32_t_deadbeef(
            ontology::Universe&,
            ontology::CallbackEngine*,
            ontology::CallbackObject*,
            ontology::GenericParentModule& /* input_parameters */,
            const data::AnyValue&);
}

#endif
