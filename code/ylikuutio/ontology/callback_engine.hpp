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

#ifndef YLIKUUTIO_ONTOLOGY_CALLBACK_ENGINE_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_CALLBACK_ENGINE_HPP_INCLUDED

#include "generic_callback_engine.hpp"
#include "child_module.hpp"
#include "generic_parent_module.hpp"
#include "input_parameters_and_any_value_to_any_value_callback_with_universe.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <optional> // std::optional
#include <vector>   // std::vector

namespace yli::core
{
    class Application;
}

namespace yli::memory
{
    template<typename T1, std::size_t DataSize>
        class MemoryStorage;
}

namespace yli::ontology
{
    class Universe;
    class CallbackObject;
    class Scene;
    struct CallbackEngineStruct;

    class CallbackEngine : public yli::ontology::GenericCallbackEngine
    {
        // `CallbackEngine` is an object that contains some callbacks and hashmaps that are used for input and output parameters.
        // `CallbackEngine` provides a way to create callback chains.
        //
        // Hierarchy of callbacks:
        //
        //     CallbackEngine
        //           ^
        //     CallbackObject
        //           ^
        //   CallbackParameter
        //
        // How to use.
        // 1. Create a new `CallbackEngine`. No callbacks have been
        //    defined yet. Calling `CallbackEngine.execute(nullptr)` at this
        //    point will simply go through an empty vector and
        //    practically won't do anything interesting.
        // 2. Create a new `CallbackObject`, give pointer to the
        //    recently created `CallbackEngine` as input parameter.
        // 3. If the callback has parameter[s], create a new
        //    `CallbackParameter` for each parameter, give `CallbackObject`
        //    as input parameter for the `CallbackParameter` constructor.

        protected:
            CallbackEngine(
                    yli::core::Application& application,
                    yli::ontology::Universe& universe,
                    const yli::ontology::CallbackEngineStruct&,
                    yli::ontology::GenericParentModule* const entity_parent_module);

            virtual ~CallbackEngine() = default;

        public:
            yli::ontology::CallbackObject* create_callback_object();
            yli::ontology::CallbackObject* create_callback_object(
                    const InputParametersAndAnyValueToAnyValueCallbackWithUniverse callback);

            // execute all callbacks with a parameter.
            std::optional<yli::data::AnyValue> execute(const yli::data::AnyValue& any_value) override;

            std::size_t get_n_of_return_values() const;
            std::optional<yli::data::AnyValue> get_nth_return_value(const std::size_t n) const;
            std::optional<yli::data::AnyValue> get_previous_return_value() const;

            yli::ontology::Entity* get_parent() const override;
            yli::ontology::Scene* get_scene() const override;
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            template<typename T1, std::size_t DataSize>
                friend class yli::memory::MemoryStorage;

            yli::ontology::ChildModule child_of_entity;
            yli::ontology::GenericParentModule parent_of_callback_objects;

        private:
            std::vector<std::optional<yli::data::AnyValue>> return_values;
    };
}

#endif
