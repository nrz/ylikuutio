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

#include "parent_of_callback_parameters_module.hpp"
#include "generic_parent_module.hpp"
#include "callback_object.hpp"
#include "callback_parameter.hpp"

namespace yli::ontology
{
    class Entity;
    class Registry;

    bool ParentOfCallbackParametersModule::bind_child(yli::ontology::Entity* const callback_parameter) noexcept
    {
        if (this->GenericParentModule::bind_child(callback_parameter))
        {
            if (!callback_parameter->get_local_name().empty())
            {
                // This parameter is a named variable, so store it in `anyvalue_hashmap`.
                static_cast<yli::ontology::CallbackObject*>(this->get_entity())->set_any_value(
                        callback_parameter->get_local_name(), yli::data::AnyValue(
                            static_cast<yli::ontology::CallbackParameter*>(callback_parameter)->get_any_value()));
            }
        }

        return true;
    }

    ParentOfCallbackParametersModule::ParentOfCallbackParametersModule(
            yli::ontology::Entity* const entity,
            yli::ontology::Registry* const registry,
            const std::string& name) noexcept
        : GenericParentModule(entity, registry, name)
    {
    }
}
