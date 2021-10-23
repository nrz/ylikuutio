// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
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

#ifndef __YLIKUUTIO_LISP_LISP_TEMPLATES_HPP_INCLUDED
#define __YLIKUUTIO_LISP_LISP_TEMPLATES_HPP_INCLUDED

#include "code/ylikuutio/data/wrap.hpp"
#include "code/ylikuutio/ontology/entity.hpp"
#include "code/ylikuutio/ontology/variable.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/symbiosis.hpp"
#include "code/ylikuutio/ontology/console.hpp"
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
    // Templates for processing Lisp function arguments.

    template<typename T1>
        std::optional<typename yli::data::WrapAllButStrings<T1>::type> convert_string_to_value_and_advance_index(
                yli::ontology::Universe*,
                yli::ontology::Console*,
                yli::ontology::Entity*&, // context.
                const std::vector<std::string>&, // parameter vector.
                std::size_t&)                    // parameter_i.
        {
            static_assert(sizeof(T1) == -1, "You need to specialize this `yli::data::convert_string_to_value_and_advance_index` for the type!");
            throw;
        }

    template<>
        std::optional<typename yli::data::WrapAllButStrings<bool>::type> convert_string_to_value_and_advance_index<bool>(
                yli::ontology::Universe*,
                yli::ontology::Console*,
                yli::ontology::Entity*&, // context.
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            if (my_string == "true") // Ylikuutio is case sensitive!
            {
                return true; // OK, true.
            }
            else if (my_string == "false") // Ylikuutio is case sensitive!
            {
                return false; // OK, false.
            }
            else
            {
                return std::nullopt;
            }
        }

    template<>
        std::optional<typename yli::data::WrapAllButStrings<char>::type> convert_string_to_value_and_advance_index<char>(
                yli::ontology::Universe*,
                yli::ontology::Console*,
                yli::ontology::Entity*&, // context.
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            if (my_string.size() == 1)
            {
                return yli::data::WrapAllButStrings<char>::type(my_string[0]);
            }

            return std::nullopt;
        }

    template<>
        std::optional<typename yli::data::WrapAllButStrings<float>::type> convert_string_to_value_and_advance_index<float>(
                yli::ontology::Universe*,
                yli::ontology::Console*,
                yli::ontology::Entity*&, // context.
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            if (!yli::string::check_if_float_string(my_string))
            {
                return std::nullopt;
            }

            float value;
            std::stringstream my_stringstream;
            my_stringstream << my_string;
            my_stringstream >> value;
            return yli::data::WrapAllButStrings<float>::type(value);
        }

    template<>
        std::optional<typename yli::data::WrapAllButStrings<double>::type> convert_string_to_value_and_advance_index<double>(
                yli::ontology::Universe*,
                yli::ontology::Console*,
                yli::ontology::Entity*&, // context.
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            if (!yli::string::check_if_double_string(my_string))
            {
                return std::nullopt;
            }

            double value;
            std::stringstream my_stringstream;
            my_stringstream << my_string;
            my_stringstream >> value;
            return yli::data::WrapAllButStrings<double>::type(value);
        }

    template<>
        std::optional<typename yli::data::WrapAllButStrings<int32_t>::type> convert_string_to_value_and_advance_index<int32_t>(
                yli::ontology::Universe*,
                yli::ontology::Console*,
                yli::ontology::Entity*&, // context.
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            if (!yli::string::check_if_signed_integer_string(my_string))
            {
                return std::nullopt;
            }

            int32_t value;
            std::stringstream my_stringstream;
            my_stringstream << my_string;
            my_stringstream >> value;
            return yli::data::WrapAllButStrings<int32_t>::type(value);
        }

    template<>
        std::optional<typename yli::data::WrapAllButStrings<uint32_t>::type> convert_string_to_value_and_advance_index<uint32_t>(
                yli::ontology::Universe*,
                yli::ontology::Console*,
                yli::ontology::Entity*&, // context.
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            if (!yli::string::check_if_unsigned_integer_string(my_string))
            {
                return std::nullopt;
            }

            uint32_t value;
            std::stringstream my_stringstream;
            my_stringstream << my_string;
            my_stringstream >> value;
            return yli::data::WrapAllButStrings<uint32_t>::type(value);
        }

    template<>
        std::optional<typename yli::data::WrapAllButStrings<yli::ontology::Entity&>::type> convert_string_to_value_and_advance_index<yli::ontology::Entity&>(
                yli::ontology::Universe* universe,
                yli::ontology::Console*,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Entity* const value = universe->get_entity(my_string);

            if (value == nullptr)
            {
                return std::nullopt;
            }

            context = value;
            return yli::data::WrapAllButStrings<yli::ontology::Entity&>::type(*value);
        }

    template<>
        std::optional<typename yli::data::WrapAllButStrings<yli::ontology::Entity*>::type> convert_string_to_value_and_advance_index<yli::ontology::Entity*>(
                yli::ontology::Universe* universe,
                yli::ontology::Console*,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Entity* const value = universe->get_entity(my_string);

            if (value == nullptr)
            {
                return std::nullopt;
            }

            context = value;
            return yli::data::WrapAllButStrings<yli::ontology::Entity*>::type(value);
        }

    template<>
        std::optional<typename yli::data::WrapAllButStrings<yli::ontology::Universe&>::type> convert_string_to_value_and_advance_index<yli::ontology::Universe&>(
                yli::ontology::Universe* universe,
                yli::ontology::Console*,
                yli::ontology::Entity*& context,
                const std::vector<std::string>&, // parameter vector.
                std::size_t&)                    // parameter_i.
        {
            // Note: this specialization returns the `yli::ontology::Universe*` provided as an argument,
            // and does not do a lookup.

            context = universe;
            return yli::data::WrapAllButStrings<yli::ontology::Universe&>::type(*universe);
        }

    template<>
        std::optional<typename yli::data::WrapAllButStrings<yli::ontology::Universe*>::type> convert_string_to_value_and_advance_index<yli::ontology::Universe*>(
                yli::ontology::Universe* universe,
                yli::ontology::Console*,
                yli::ontology::Entity*& context,
                const std::vector<std::string>&, // parameter vector.
                std::size_t&)                    // parameter_i.
        {
            // Note: this specialization returns the `yli::ontology::Universe*` provided as an argument,
            // and does not do a lookup.

            if (universe == nullptr)
            {
                return std::nullopt;
            }

            context = universe;
            return yli::data::WrapAllButStrings<yli::ontology::Universe*>::type(universe);
        }

    template<>
        std::optional<typename yli::data::WrapAllButStrings<yli::ontology::Console&>::type> convert_string_to_value_and_advance_index<yli::ontology::Console&>(
                yli::ontology::Universe*,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>&, // parameter vector.
                std::size_t&)                    // parameter_i.
        {
            // Note: this specialization returns the `yli::ontology::Console*` provided as an argument,
            // and does not do a lookup.

            if (console == nullptr)
            {
                return std::nullopt;
            }

            context = console;
            return yli::data::WrapAllButStrings<yli::ontology::Console&>::type(*console);
        }

    template<>
        std::optional<typename yli::data::WrapAllButStrings<yli::ontology::Console*>::type> convert_string_to_value_and_advance_index<yli::ontology::Console*>(
                yli::ontology::Universe*,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>&, // parameter vector.
                std::size_t&)                    // parameter_i.
        {
            // Note: this specialization returns the `yli::ontology::Console*` provided as an argument,
            // and does not do a lookup.

            if (console == nullptr)
            {
                return std::nullopt;
            }

            context = console;
            return yli::data::WrapAllButStrings<yli::ontology::Console*>::type(console);
        }

    template<>
        std::optional<typename yli::data::WrapAllButStrings<yli::ontology::Variable&>::type> convert_string_to_value_and_advance_index<yli::ontology::Variable&>(
                yli::ontology::Universe* universe,
                yli::ontology::Console*,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Variable* const value = dynamic_cast<yli::ontology::Variable*>(universe->get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            context = value;
            return yli::data::WrapAllButStrings<yli::ontology::Variable&>::type(*value);
        }

    template<>
        std::optional<typename yli::data::WrapAllButStrings<yli::ontology::Variable*>::type> convert_string_to_value_and_advance_index<yli::ontology::Variable*>(
                yli::ontology::Universe* universe,
                yli::ontology::Console*,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Variable* const value = dynamic_cast<yli::ontology::Variable*>(universe->get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            context = value;
            return yli::data::WrapAllButStrings<yli::ontology::Variable*>::type(value);
        }

    template<>
        std::optional<typename yli::data::WrapAllButStrings<yli::ontology::Species&>::type> convert_string_to_value_and_advance_index<yli::ontology::Species&>(
                yli::ontology::Universe* universe,
                yli::ontology::Console*,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Species* const value = dynamic_cast<yli::ontology::Species*>(universe->get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            context = value;
            return yli::data::WrapAllButStrings<yli::ontology::Species&>::type(*value);
        }

    template<>
        std::optional<typename yli::data::WrapAllButStrings<yli::ontology::Species*>::type> convert_string_to_value_and_advance_index<yli::ontology::Species*>(
                yli::ontology::Universe* universe,
                yli::ontology::Console*,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Species* const value = dynamic_cast<yli::ontology::Species*>(universe->get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            context = value;
            return yli::data::WrapAllButStrings<yli::ontology::Species*>::type(value);
        }

    template<>
        std::optional<typename yli::data::WrapAllButStrings<yli::ontology::Symbiosis&>::type> convert_string_to_value_and_advance_index<yli::ontology::Symbiosis&>(
                yli::ontology::Universe* universe,
                yli::ontology::Console*,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Symbiosis* const value = dynamic_cast<yli::ontology::Symbiosis*>(universe->get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            context = value;
            return yli::data::WrapAllButStrings<yli::ontology::Symbiosis&>::type(*value);
        }

    template<>
        std::optional<typename yli::data::WrapAllButStrings<yli::ontology::Symbiosis*>::type> convert_string_to_value_and_advance_index<yli::ontology::Symbiosis*>(
                yli::ontology::Universe* universe,
                yli::ontology::Console*,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Symbiosis* const value = dynamic_cast<yli::ontology::Symbiosis*>(universe->get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            context = value;
            return yli::data::WrapAllButStrings<yli::ontology::Symbiosis*>::type(value);
        }

    template<>
        std::optional<typename yli::data::WrapAllButStrings<const std::string&>::type> convert_string_to_value_and_advance_index<const std::string&>(
                yli::ontology::Universe*,
                yli::ontology::Console*,
                yli::ontology::Entity*&, // context.
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            return { parameter_vector.at(parameter_i++) };
        }
}

#endif
