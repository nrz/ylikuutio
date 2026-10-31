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

#include "lisp_context.hpp"
#include "universe.hpp"
#include "lisp_context_struct.hpp"

// Include standard headers
#include <utility> // std::move

namespace yli::core
{
    class Application;
}

namespace yli::memory
{
    struct ConstructibleModule;
}

namespace yli::ontology
{
    class Entity;

    LispContext::LispContext(
            memory::ConstructibleModule&& constructible_module,
            core::Application& application,
            Universe& universe,
            const LispContextStruct& lisp_context_struct)
        : Entity(std::move(constructible_module), application, universe, lisp_context_struct)
    {
        // `yli::ontology::Entity` member variables begin here.
        this->can_be_erased = true;
    }
}
