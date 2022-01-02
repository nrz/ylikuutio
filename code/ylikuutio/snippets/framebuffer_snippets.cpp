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

#include "framebuffer_snippets.hpp"
#include "code/ylikuutio/ontology/variable.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/variable_struct.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <memory>   // std::make_shared, std::shared_ptr
#include <stdint.h> // uint32_t etc.

namespace yli::snippets
{
    void set_framebuffer_size(yli::ontology::Universe* universe, const uint32_t framebuffer_width, const uint32_t framebuffer_height)
    {
        yli::ontology::VariableStruct framebuffer_width_variable_struct;
        framebuffer_width_variable_struct.local_name = "framebuffer_width";
        framebuffer_width_variable_struct.activate_callback = &yli::ontology::Variable::activate_framebuffer_width;
        framebuffer_width_variable_struct.should_call_activate_callback_now = false;
        universe->create_variable(framebuffer_width_variable_struct, yli::data::AnyValue(framebuffer_width));

        yli::ontology::VariableStruct framebuffer_height_variable_struct;
        framebuffer_height_variable_struct.local_name = "framebuffer_height";
        framebuffer_height_variable_struct.activate_callback = &yli::ontology::Variable::activate_framebuffer_height;
        framebuffer_height_variable_struct.should_call_activate_callback_now = true;
        universe->create_variable(framebuffer_height_variable_struct, yli::data::AnyValue(framebuffer_height));
    }
}
