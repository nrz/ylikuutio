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

#ifndef YLIKUUTIO_ONTOLOGY_BRAIN_STRUCT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_BRAIN_STRUCT_HPP_INCLUDED

#include "entity_struct.hpp"

// Include standard headers
#include <variant> // std::monostate, std::variant

namespace yli::ontology
{
    class CallbackEngine;
    class Scene;

    struct BrainStruct : public yli::ontology::EntityStruct
    {
        BrainStruct(
                yli::ontology::Scene* const scene_parent,
                yli::ontology::CallbackEngine* const callback_engine)
            : parent        { scene_parent },
            callback_engine { callback_engine }
        {
        }

        BrainStruct(
                const std::string& scene_parent,
                yli::ontology::CallbackEngine* const callback_engine)
            : parent        { scene_parent },
            callback_engine { callback_engine }
        {
        }

        std::variant<std::monostate, yli::ontology::Scene*, std::string> parent {};
        yli::ontology::CallbackEngine* callback_engine { nullptr };
    };
}

#endif
