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

#include "wireframe_snippets.hpp"
#include "code/ylikuutio/ontology/variable.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/variable_struct.hpp"
#include "code/ylikuutio/data/any_value.hpp"

namespace yli::snippets
{
    void set_wireframe(yli::ontology::Universe* universe, const bool use_wireframe)
    {
        yli::ontology::VariableStruct wireframe_variable_struct;
        wireframe_variable_struct.local_name = "wireframe";
        wireframe_variable_struct.activate_callback = &yli::ontology::Variable::activate_wireframe;
        wireframe_variable_struct.should_call_activate_callback_now = true;
        universe->create_variable(wireframe_variable_struct, yli::data::AnyValue(use_wireframe));
    }
}
