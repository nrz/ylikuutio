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

#include "application_core.hpp"

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    struct UniverseStruct;
}

namespace yli::core
{
    ApplicationCore::ApplicationCore(Application& application, const yli::ontology::UniverseStruct& universe_struct)
        : entity_factory(application, this->memory_system),
        system_factory(this->memory_system),
        universe { this->entity_factory.create_universe(universe_struct) },
        event_system { this->system_factory.create_event_system(this->get_universe()) },
        input_system { this->system_factory.create_input_system(this->get_universe()) },
        audio_system { this->system_factory.create_audio_system(this->get_universe()) }
    {
    }

    yli::ontology::Universe& ApplicationCore::get_universe() const
    {
        if (this->universe == nullptr) [[unlikely]]
        {
            throw std::logic_error("ERROR: `ApplicationCore::get_universe`: `this->universe` is `nullptr`!");
        }

        return *this->universe;
    }
}
