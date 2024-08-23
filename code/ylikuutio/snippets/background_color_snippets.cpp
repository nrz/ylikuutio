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

#include "background_color_snippets.hpp"
#include "code/ylikuutio/ontology/variable.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/variable_struct.hpp"
#include "code/ylikuutio/data/any_value.hpp"

namespace yli::snippets
{
    void set_background_colors(yli::ontology::Universe* universe, const float red, const float green, const float blue, const float alpha)
    {
        if (universe == nullptr)
        {
            return;
        }

        yli::ontology::VariableStruct red_variable_struct(*universe, universe);
        red_variable_struct.local_name = "red";
        red_variable_struct.activate_callback = &yli::ontology::Variable::activate_background_color;
        red_variable_struct.should_call_activate_callback_now = false;
        universe->create_variable(red_variable_struct, yli::data::AnyValue(red));

        yli::ontology::VariableStruct green_variable_struct(*universe, universe);
        green_variable_struct.local_name = "green";
        green_variable_struct.activate_callback = &yli::ontology::Variable::activate_background_color;
        green_variable_struct.should_call_activate_callback_now = false;
        universe->create_variable(green_variable_struct, yli::data::AnyValue(green));

        yli::ontology::VariableStruct blue_variable_struct(*universe, universe);
        blue_variable_struct.local_name = "blue";
        blue_variable_struct.activate_callback = &yli::ontology::Variable::activate_background_color;
        blue_variable_struct.should_call_activate_callback_now = false;
        universe->create_variable(blue_variable_struct, yli::data::AnyValue(blue));

        yli::ontology::VariableStruct alpha_variable_struct(*universe, universe);
        alpha_variable_struct.local_name = "alpha";
        alpha_variable_struct.activate_callback = &yli::ontology::Variable::activate_background_color;
        alpha_variable_struct.should_call_activate_callback_now = true;
        universe->create_variable(alpha_variable_struct, yli::data::AnyValue(alpha));
    }
}
