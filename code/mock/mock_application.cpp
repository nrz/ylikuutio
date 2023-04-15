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

#include "mock_application.hpp"
#include "code/ylikuutio/core/application.hpp"

#ifndef GOOGLE_TEST
// Google Test provides its own `main` entrypoint.
#include "code/ylikuutio/core/entrypoint.hpp"
#endif

#include "code/ylikuutio/data/datatype.hpp"
#include "code/ylikuutio/ontology/universe_struct.hpp"
#include "code/ylikuutio/render/graphics_api_backend.hpp"

// Include standard headers
#include <memory> // std::make_unique, std::unique_ptr
#include <string> // std::string
#include <vector> // std::vector

namespace mock
{
    static constexpr yli::data::Datatype universe_enum_value = yli::data::Datatype::UNIVERSE;

    MockApplication::MockApplication()
        : yli::core::Application(0, nullptr)
    {
        std::cout << "MockApplication initialized!\n";
    }

    std::string MockApplication::get_name() const
    {
        return "MockApplication";
    }

    std::vector<std::string> MockApplication::get_valid_keys() const
    {
        return std::vector<std::string>();
    }

    yli::ontology::UniverseStruct MockApplication::get_universe_struct() const
    {
        return yli::ontology::UniverseStruct(yli::render::GraphicsApiBackend::HEADLESS);
    }

    bool MockApplication::create_simulation()
    {
        // Do nothing.
        return true;
    }
}

namespace yli::core
{
    std::unique_ptr<yli::core::Application> create_application(const int argc, const char* const argv[])
    {
        return std::make_unique<mock::MockApplication>();
    }
}
