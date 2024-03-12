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

#ifndef YLIKUUTIO_ONTOLOGY_CALLBACK_OBJECT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_CALLBACK_OBJECT_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "generic_parent_module.hpp"
#include "callback_engine.hpp"
#include "input_parameters_and_any_value_to_any_value_callback_with_universe.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <cstddef>       // std::size_t
#include <optional>      // std::optional
#include <string>        // std::string

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
    class GenericParentModule;
    class Universe;
    class CallbackEngine;
    class CallbackParameter;
    class Scene;
    struct CallbackObjectStruct;

    class CallbackObject : public yli::ontology::Entity
    {
        // CallbackObject is an object that contains a single callback.

        protected:
            CallbackObject(
                    yli::core::Application& application,
                    yli::ontology::Universe& universe,
                    const yli::ontology::CallbackObjectStruct& callback_object_struct,
                    yli::ontology::GenericParentModule* const callback_engine_parent_module);

            CallbackObject(
                    yli::core::Application& application,
                    yli::ontology::Universe& universe,
                    const yli::ontology::CallbackObjectStruct& callback_object_struct,
                    const InputParametersAndAnyValueToAnyValueCallbackWithUniverse callback,
                    yli::ontology::GenericParentModule* const callback_engine_parent_module);

            virtual ~CallbackObject() = default;

        public:
            yli::ontology::CallbackParameter* create_callback_parameter(
                    const std::string& name,
                    const yli::data::AnyValue& any_value);

            // this method changes the callback without changing the parameters of CallbackObject.
            void set_new_callback(const InputParametersAndAnyValueToAnyValueCallbackWithUniverse callback);

            std::optional<yli::data::AnyValue> get_any_value(const std::string& name) const;
            std::optional<yli::data::AnyValue> get_arg(const std::size_t arg_i) const;

            yli::ontology::Entity* get_parent() const override;
            yli::ontology::Scene* get_scene() const override;
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            template<typename T1, std::size_t DataSize>
                friend class yli::memory::MemoryStorage;

            yli::ontology::ChildModule child_of_callback_engine;
            yli::ontology::GenericParentModule parent_of_callback_parameters;

            friend class CallbackEngine;

        protected:
            InputParametersAndAnyValueToAnyValueCallbackWithUniverse callback { nullptr };

        private:
            // execute this callback with a parameter.
            virtual std::optional<yli::data::AnyValue> execute(const yli::data::AnyValue& any_value);
    };
}

#endif
