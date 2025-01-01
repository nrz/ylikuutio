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
    std::optional<yli::data::AnyValue> square(
            yli::ontology::Universe&,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject*,
            yli::ontology::GenericParentModule& input_parameters,
            const yli::data::AnyValue&);

    std::optional<yli::data::AnyValue> square_last(
            yli::ontology::Universe&,
            yli::ontology::CallbackEngine* callback_engine,
            yli::ontology::CallbackObject*,
            yli::ontology::GenericParentModule& input_parameters,
            const yli::data::AnyValue&);

    std::optional<yli::data::AnyValue> expt(
            yli::ontology::Universe&,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject*,
            yli::ontology::GenericParentModule& input_parameters,
            const yli::data::AnyValue&);

    std::optional<yli::data::AnyValue> expt_with_named_inputs(
            yli::ontology::Universe&,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject* callback_object,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&);

    std::optional<yli::data::AnyValue> neg(
            yli::ontology::Universe&,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject*,
            yli::ontology::GenericParentModule& input_parameters,
            const yli::data::AnyValue&);

    std::optional<yli::data::AnyValue> nop(
            yli::ontology::Universe&,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject*,
            yli::ontology::GenericParentModule& /* input_parameters */,
            const yli::data::AnyValue&);

    std::optional<yli::data::AnyValue> return_uint32_t_deadbeef(
            yli::ontology::Universe&,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject*,
            yli::ontology::GenericParentModule& /* input_parameters */,
            const yli::data::AnyValue&);
}

#endif
