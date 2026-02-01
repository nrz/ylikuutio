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

#ifndef YLIKUUTIO_ONTOLOGY_GENERIC_CALLBACK_ENGINE_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_GENERIC_CALLBACK_ENGINE_HPP_INCLUDED

#include "entity.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <cstddef>  // std::size_t

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class Universe;
    struct GenericCallbackEngineStruct;

    class GenericCallbackEngine : public Entity
    {
        public:
            GenericCallbackEngine(
                    yli::core::Application& application,
                    Universe& universe,
                    const GenericCallbackEngineStruct& generic_callback_engine_struct);

            GenericCallbackEngine(const GenericCallbackEngine&) = delete;            // Delete copy constructor.
            GenericCallbackEngine &operator=(const GenericCallbackEngine&) = delete; // Delete copy assignment.

            virtual ~GenericCallbackEngine() = default;

            // execute all callbacks with a parameter.
            virtual std::optional<yli::data::AnyValue> execute(const yli::data::AnyValue& any_value) = 0;
    };
}

#endif
