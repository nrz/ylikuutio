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

#ifndef YLIKUUTIO_ONTOLOGY_CALLBACK_PARAMETER_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_CALLBACK_PARAMETER_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <string>  // std::string

namespace yli::ontology
{
    class GenericParentModule;
    class Universe;
    class CallbackObject;
    struct CallbackParameterStruct;

    class CallbackParameter final : public yli::ontology::Entity
    {
        public:
            CallbackParameter(
                    yli::ontology::Universe& universe,
                    const yli::ontology::CallbackParameterStruct& callback_parameter_struct,
                    const yli::data::AnyValue& any_value,
                    yli::ontology::GenericParentModule* const callback_object_parent);

            ~CallbackParameter() = default;

            const yli::data::AnyValue& get_any_value() const;

            yli::ontology::Entity* get_parent() const override;
            yli::ontology::Scene* get_scene() const override;
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            yli::ontology::ChildModule child_of_callback_object;

            friend class CallbackObject;

        private:
            yli::data::AnyValue any_value;  // this is `private` to make sure that someone does not overwrite it.
    };
}

#endif