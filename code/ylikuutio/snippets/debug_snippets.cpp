// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
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

#include "debug_snippets.hpp"
#include "code/ylikuutio/ontology/variable.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/variable_struct.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <memory> // std::make_shared, std::shared_ptr

namespace yli::snippets
{
    void set_flight_mode(yli::ontology::Universe* universe, const bool is_flight_mode_in_use)
    {
        std::shared_ptr<yli::data::AnyValue> any_value_is_flight_mode_in_use = std::make_shared<yli::data::AnyValue>(is_flight_mode_in_use);
        yli::ontology::VariableStruct is_flight_mode_in_use_variable_struct(any_value_is_flight_mode_in_use);
        is_flight_mode_in_use_variable_struct.local_name = "is_flight_mode_in_use";
        is_flight_mode_in_use_variable_struct.activate_callback = &yli::ontology::Variable::activate_is_flight_mode_in_use;
        is_flight_mode_in_use_variable_struct.read_callback = &yli::ontology::Variable::read_is_flight_mode_in_use;
        is_flight_mode_in_use_variable_struct.should_call_activate_callback_now = true;
        universe->create_variable(is_flight_mode_in_use_variable_struct);
    }
}
