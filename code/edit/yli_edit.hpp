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

#ifndef YLI_EDIT_YLI_EDIT_HPP_INCLUDED
#define YLI_EDIT_YLI_EDIT_HPP_INCLUDED

#include "code/ylikuutio/core/application.hpp"

// Include standard headers
#include <memory> // std::unique_ptr
#include <string> // std::string
#include <vector> // std::vector

namespace yli::ontology
{
    struct UniverseStruct;
}

namespace yli_edit
{
    class YliEditApplication : public yli::core::Application
    {
        public:
            YliEditApplication(const int argc, const char* const argv[]);

            ~YliEditApplication() = default;

            std::string get_name() const override;

            std::vector<std::string> get_valid_keys() override;

            yli::ontology::UniverseStruct get_universe_struct() override;

            bool create_simulation() override;
    };
}

namespace yli::core
{
    std::unique_ptr<yli::core::Application> create_application(const int argc, const char* const argv[]);
}

#endif
