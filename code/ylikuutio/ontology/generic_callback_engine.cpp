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

#include "generic_callback_engine.hpp"
#include "generic_callback_engine_struct.hpp"

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class Entity;
    class Universe;

    GenericCallbackEngine::GenericCallbackEngine(
            yli::core::Application& application,
            yli::ontology::Universe& universe,
            const yli::ontology::GenericCallbackEngineStruct& generic_callback_engine_struct)
        : Entity(application, universe, generic_callback_engine_struct)
    {
        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "yli::ontology::GenericCallbackEngine*";
    }
}