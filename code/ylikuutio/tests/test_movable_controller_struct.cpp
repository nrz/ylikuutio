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

#include "gtest/gtest.h"
#include "code/ylikuutio/ontology/request.hpp"
#include "code/ylikuutio/ontology/movable_controller_struct.hpp"

// Include standard headers
#include <variant> // std::holds_alternative

namespace yli::ontology
{
    class CallbackEngine;
    class Scene;
}

TEST(movable_controller_struct_must_be_initialized_appropriately, movable_controller_struct)
{
    const yli::ontology::MovableControllerStruct test_movable_controller_struct {
            yli::ontology::Request<yli::ontology::Scene>(nullptr),
            yli::ontology::Request<yli::ontology::CallbackEngine>(nullptr) };

    ASSERT_TRUE(std::holds_alternative<yli::ontology::Scene*>(test_movable_controller_struct.scene_parent.data));
    ASSERT_EQ(std::get<yli::ontology::Scene*>(test_movable_controller_struct.scene_parent.data), nullptr);

    ASSERT_TRUE(std::holds_alternative<yli::ontology::CallbackEngine*>(test_movable_controller_struct.callback_engine_master.data));
    ASSERT_EQ(std::get<yli::ontology::CallbackEngine*>(test_movable_controller_struct.callback_engine_master.data), nullptr);
}
