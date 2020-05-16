// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
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

#ifndef __LISP_TEMPLATES_HPP_INCLUDED
#define __LISP_TEMPLATES_HPP_INCLUDED

#include "code/ylikuutio/ontology/entity.hpp"
#include "code/ylikuutio/ontology/movable.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/world.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/shader.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/symbiosis.hpp"
#include "code/ylikuutio/ontology/holobiont.hpp"
#include "code/ylikuutio/ontology/font2D.hpp"
#include "code/ylikuutio/ontology/text2D.hpp"
#include "code/ylikuutio/ontology/vector_font.hpp"
#include "code/ylikuutio/ontology/text3D.hpp"
#include "code/ylikuutio/ontology/console.hpp"
#include "code/ylikuutio/ontology/compute_task.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <stdint.h> // uint32_t etc.
#include <memory>   // std::make_shared, std::shared_ptr
#include <sstream>  // std::istringstream, std::ostringstream, std::stringstream
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::lisp
{
    // Templates for processing console command arguments.

    template<class T1>
        bool convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                T1& value)
        {
            static_assert(sizeof(T1) == -1, "You need to specialize this `yli::data::convert_string_to_value_and_advance_index` for the type!");
            return false;
        }

    template<>
        bool convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                bool& value)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return false;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            if (my_string == "true") // Ylikuutio is case sensitive!
            {
                value = true;
                return true;
            }
            else if (my_string == "false") // Ylikuutio is case sensitive!
            {
                value = false;
                return true;
            }
            else
            {
                return false;
            }
        }

    template<>
        bool convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                char& value)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return false;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            if (my_string.size() == 1)
            {
                value = my_string[0];
                return true;
            }

            return false;
        }

    template<>
        bool convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                float& value)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return false;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            if (!yli::string::check_if_float_string(my_string))
            {
                return false;
            }

            std::stringstream my_stringstream;
            my_stringstream << my_string;
            my_stringstream >> value;
            return true;
        }

    template<>
        bool convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                double& value)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return false;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            if (!yli::string::check_if_double_string(my_string))
            {
                return false;
            }

            std::stringstream my_stringstream;
            my_stringstream << my_string;
            my_stringstream >> value;
            return true;
        }

    template<>
        bool convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                int32_t& value)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return false;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            if (!yli::string::check_if_signed_integer_string(my_string))
            {
                return false;
            }

            std::stringstream my_stringstream;
            my_stringstream << my_string;
            my_stringstream >> value;
            return true;
        }

    template<>
        bool convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                uint32_t& value)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return false;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            if (!yli::string::check_if_unsigned_integer_string(my_string))
            {
                return false;
            }

            std::stringstream my_stringstream;
            my_stringstream << my_string;
            my_stringstream >> value;
            return true;
        }

    template<>
        bool convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                yli::ontology::Entity*& value)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return false;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            value = universe->get_entity(my_string);

            if (value == nullptr)
            {
                return false;
            }

            context = value;
            return true;
        }

    template<>
        bool convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                yli::ontology::Movable*& value)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return false;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                return false;
            }

            value = dynamic_cast<yli::ontology::Movable*>(entity);

            if (value == nullptr)
            {
                return false;
            }

            context = value;
            return true;
        }

    template<>
        bool convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                const yli::ontology::Movable*& value)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return false;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                return false;
            }

            value = dynamic_cast<const yli::ontology::Movable*>(entity);

            if (value == nullptr)
            {
                return false;
            }

            context = entity;
            return true;
        }

    template<>
        bool convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                yli::ontology::Universe*& value)
        {
            // Note: this specialization returns the `yli::ontology::Universe*` provided as an argument,
            // and does not do a lookup.

            if (universe == nullptr)
            {
                return false;
            }

            value = universe;
            context = universe;
            return true;
        }

    template<>
        bool convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                yli::ontology::World*& value)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return false;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                return false;
            }

            value = dynamic_cast<yli::ontology::World*>(entity);

            if (value == nullptr)
            {
                return false;
            }

            context = value;
            return true;
        }

    template<>
        bool convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                yli::ontology::Scene*& value)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return false;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                return false;
            }

            value = dynamic_cast<yli::ontology::Scene*>(entity);

            if (value == nullptr)
            {
                return false;
            }

            context = value;
            return true;
        }

    template<>
        bool convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                yli::ontology::Shader*& value)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return false;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                return false;
            }

            value = dynamic_cast<yli::ontology::Shader*>(entity);

            if (value == nullptr)
            {
                return false;
            }

            context = value;
            return true;
        }

    template<>
        bool convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                yli::ontology::Material*& value)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return false;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                return false;
            }

            value = dynamic_cast<yli::ontology::Material*>(entity);

            if (value == nullptr)
            {
                return false;
            }

            context = value;
            return true;
        }

    template<>
        bool convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                yli::ontology::Species*& value)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return false;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                return false;
            }

            value = dynamic_cast<yli::ontology::Species*>(entity);

            if (value == nullptr)
            {
                return false;
            }

            context = value;
            return true;
        }

    template<>
        bool convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                yli::ontology::Object*& value)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return false;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                return false;
            }

            value = dynamic_cast<yli::ontology::Object*>(entity);

            if (value == nullptr)
            {
                return false;
            }

            context = value;
            return true;
        }

    template<>
        bool convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                yli::ontology::Symbiosis*& value)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return false;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                return false;
            }

            value = dynamic_cast<yli::ontology::Symbiosis*>(entity);

            if (value == nullptr)
            {
                return false;
            }

            context = value;
            return true;
        }

    template<>
        bool convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                yli::ontology::Holobiont*& value)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return false;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                return false;
            }

            value = dynamic_cast<yli::ontology::Holobiont*>(entity);

            if (value == nullptr)
            {
                return false;
            }

            context = value;
            return true;
        }

    template<>
        bool convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                yli::ontology::Font2D*& value)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return false;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                return false;
            }

            value = dynamic_cast<yli::ontology::Font2D*>(entity);

            if (value == nullptr)
            {
                return false;
            }

            context = value;
            return true;
        }

    template<>
        bool convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                yli::ontology::Text2D*& value)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return false;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                return false;
            }

            value = dynamic_cast<yli::ontology::Text2D*>(entity);

            if (value == nullptr)
            {
                return false;
            }

            context = value;
            return true;
        }

    template<>
        bool convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                yli::ontology::Console*& value)
        {
            // Note: this specialization returns the `yli::ontology::Console*` provided as an argument,
            // and does not do a lookup.

            if (console == nullptr)
            {
                return false;
            }

            value = console;
            context = console;
            return true;
        }

    template<>
        bool convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                yli::ontology::ComputeTask*& value)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return false;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                return false;
            }

            value = dynamic_cast<yli::ontology::ComputeTask*>(entity);

            if (value == nullptr)
            {
                return false;
            }

            context = value;
            return true;
        }

    template<>
        bool convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                yli::config::Setting*& value)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return false;
            }

            yli::config::SettingMaster* setting_master = context->get_setting_master();

            if (setting_master == nullptr)
            {
                return false;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            value = setting_master->get(my_string);

            if (value == nullptr)
            {
                return false;
            }

            return true;
        }

    template<>
        bool convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                const yli::config::Setting*& value)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return false;
            }

            yli::config::SettingMaster* setting_master = context->get_setting_master();

            if (setting_master == nullptr)
            {
                return false;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            value = setting_master->get(my_string);

            if (value == nullptr)
            {
                return false;
            }

            return true;
        }

    template<>
        bool convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                std::shared_ptr<std::string>& value)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return false;
            }

            value = std::make_shared<std::string>(parameter_vector.at(parameter_i++));
            return true;
        }

    template<>
        bool convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                std::string& value)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return false;
            }

            value = parameter_vector.at(parameter_i++);
            return true;
        }
}

#endif