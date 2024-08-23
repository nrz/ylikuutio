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

#include "window_snippets.hpp"
#include "code/ylikuutio/ontology/entity.hpp"
#include "code/ylikuutio/ontology/variable.hpp"
#include "code/ylikuutio/ontology/variable_struct.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <stdint.h> // uint32_t etc.

namespace yli::snippets
{
    void set_window_size(yli::ontology::Entity* entity, const uint32_t window_width, const uint32_t window_height)
    {
        yli::ontology::VariableStruct window_width_variable_struct(entity->get_universe(), entity);
        window_width_variable_struct.local_name = "window_width";
        window_width_variable_struct.activate_callback = &yli::ontology::Variable::activate_window_width;
        window_width_variable_struct.should_call_activate_callback_now = false;
        entity->create_variable(window_width_variable_struct, yli::data::AnyValue(window_width));

        yli::ontology::VariableStruct window_height_variable_struct(entity->get_universe(), entity);
        window_height_variable_struct.local_name = "window_height";
        window_height_variable_struct.activate_callback = &yli::ontology::Variable::activate_window_height;
        window_height_variable_struct.should_call_activate_callback_now = false;
        entity->create_variable(window_height_variable_struct, yli::data::AnyValue(window_height));
    }
}
