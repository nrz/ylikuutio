// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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

#ifndef YLIKUUTIO_LISP_LISP_TEMPLATES_HPP_INCLUDED
#define YLIKUUTIO_LISP_LISP_TEMPLATES_HPP_INCLUDED

#include "code/ylikuutio/data/wrap.hpp"
#include "code/ylikuutio/ontology/entity.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/variable.hpp"
#include "code/ylikuutio/ontology/brain.hpp"
#include "code/ylikuutio/ontology/movable.hpp"
#include "code/ylikuutio/ontology/ecosystem.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/pipeline.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/symbiosis.hpp"
#include "code/ylikuutio/ontology/shapeshifter_transformation.hpp"
#include "code/ylikuutio/ontology/shapeshifter_sequence.hpp"
#include "code/ylikuutio/ontology/font_2d.hpp"
#include "code/ylikuutio/ontology/text_2d.hpp"
#include "code/ylikuutio/ontology/vector_font.hpp"
#include "code/ylikuutio/ontology/text_3d.hpp"
#include "code/ylikuutio/ontology/console.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <stdint.h> // uint32_t etc.
#include <sstream>  // std::stringstream
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::lisp
{
    // Templates for processing Lisp function arguments.
    //
    // The default context is `Universe`.
    //
    // 1. If the callback has `yli::ontology::Universe&` or `yli::ontology::Universe*` as an argument,
    //    then the `Universe*` will be provided. This does not consume any parameters.
    //    The `Universe` is set as context.
    //
    // 2. If the callback has `yli::ontology::Console&` or `yli::ontology::Console*` as an argument,
    //    then this `Console*` will be provided. This does not consume any parameters.
    //    In the future other `Console`s will be made reachable as well, with `yli::ontology::SomeConsole*`.
    //    The `Console` is set as context.
    //
    // 3. Otherwise, if the callback has `yli::ontology::Entity&` or `yli::ontology::Entity*` or
    //    some subtype of `Entity` as an argument, then the string will be looked up and converted into that.
    //    The `Entity` is set as context.
    //
    // 4. If the callback has `bool` as an argument, then the string will be converted into that.
    //
    // 5. If the callback has `float` as an argument, then the string will be converted into that.
    //
    // 6. If the callback has `double` as an argument, then the string will be converted into that.
    //
    // 7. If the callback has `int32_t` as an argument, then the string will be converted into that.
    //
    // 8. If the callback has `uint32_t` as an argument, then the string will be converted into that.

    template<typename T1>
        std::optional<typename yli::data::WrapAllButStrings<T1>::type> convert_string_to_value_and_advance_index(
                yli::ontology::Universe&,
                yli::ontology::Console&,
                yli::ontology::Entity*&, // context.
                const std::vector<std::string>&, // parameter vector.
                std::size_t&) = delete;          // parameter_i.

    template<>
        inline std::optional<typename yli::data::WrapAllButStrings<bool>::type> convert_string_to_value_and_advance_index<bool>(
                yli::ontology::Universe&,
                yli::ontology::Console&,
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
        inline std::optional<typename yli::data::WrapAllButStrings<char>::type> convert_string_to_value_and_advance_index<char>(
                yli::ontology::Universe&,
                yli::ontology::Console&,
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
        inline std::optional<typename yli::data::WrapAllButStrings<float>::type> convert_string_to_value_and_advance_index<float>(
                yli::ontology::Universe&,
                yli::ontology::Console&,
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
        inline std::optional<typename yli::data::WrapAllButStrings<double>::type> convert_string_to_value_and_advance_index<double>(
                yli::ontology::Universe&,
                yli::ontology::Console&,
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
        inline std::optional<typename yli::data::WrapAllButStrings<int32_t>::type> convert_string_to_value_and_advance_index<int32_t>(
                yli::ontology::Universe&,
                yli::ontology::Console&,
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
        inline std::optional<typename yli::data::WrapAllButStrings<uint32_t>::type> convert_string_to_value_and_advance_index<uint32_t>(
                yli::ontology::Universe&,
                yli::ontology::Console&,
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
        inline std::optional<typename yli::data::WrapAllButStrings<yli::ontology::Entity&>::type> convert_string_to_value_and_advance_index<yli::ontology::Entity&>(
                yli::ontology::Universe& universe,
                yli::ontology::Console&,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Entity* const value = universe.get_entity(my_string);

            if (value == nullptr)
            {
                return std::nullopt;
            }

            context = value;
            return yli::data::WrapAllButStrings<yli::ontology::Entity&>::type(*value);
        }

    template<>
        inline std::optional<typename yli::data::WrapAllButStrings<const yli::ontology::Entity&>::type> convert_string_to_value_and_advance_index<const yli::ontology::Entity&>(
                yli::ontology::Universe& universe,
                yli::ontology::Console&,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Entity* const value = universe.get_entity(my_string);

            if (value == nullptr)
            {
                return std::nullopt;
            }

            context = value;
            return yli::data::WrapAllButStrings<const yli::ontology::Entity&>::type(*value);
        }

    template<>
        inline std::optional<typename yli::data::WrapAllButStrings<yli::ontology::Entity*>::type> convert_string_to_value_and_advance_index<yli::ontology::Entity*>(
                yli::ontology::Universe& universe,
                yli::ontology::Console&,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Entity* const value = universe.get_entity(my_string);

            if (value == nullptr)
            {
                return std::nullopt;
            }

            context = value;
            return yli::data::WrapAllButStrings<yli::ontology::Entity*>::type(value);
        }

    template<>
        inline std::optional<typename yli::data::WrapAllButStrings<yli::ontology::Universe&>::type> convert_string_to_value_and_advance_index<yli::ontology::Universe&>(
                yli::ontology::Universe& universe,
                yli::ontology::Console&,
                yli::ontology::Entity*& context,
                const std::vector<std::string>&, // parameter vector.
                std::size_t&)                    // parameter_i.
        {
            // Note: this specialization returns the `yli::ontology::Universe&` provided as an argument,
            // and does not do a lookup.

            context = &universe;
            return yli::data::WrapAllButStrings<yli::ontology::Universe&>::type(universe);
        }

    template<>
        inline std::optional<typename yli::data::WrapAllButStrings<const yli::ontology::Universe&>::type> convert_string_to_value_and_advance_index<const yli::ontology::Universe&>(
                yli::ontology::Universe& universe,
                yli::ontology::Console&,
                yli::ontology::Entity*& context,
                const std::vector<std::string>&, // parameter vector.
                std::size_t&)                    // parameter_i.
        {
            // Note: this specialization returns the `yli::ontology::Universe&` provided as an argument,
            // and does not do a lookup.

            context = &universe;
            return yli::data::WrapAllButStrings<const yli::ontology::Universe&>::type(universe);
        }

    template<>
        inline std::optional<typename yli::data::WrapAllButStrings<yli::ontology::Universe*>::type> convert_string_to_value_and_advance_index<yli::ontology::Universe*>(
                yli::ontology::Universe& universe,
                yli::ontology::Console&,
                yli::ontology::Entity*& context,
                const std::vector<std::string>&, // parameter vector.
                std::size_t&)                    // parameter_i.
        {
            // Note: this specialization returns the `yli::ontology::Universe*` provided as an argument,
            // and does not do a lookup.

            context = &universe;
            return &universe;
        }

    template<>
        inline std::optional<typename yli::data::WrapAllButStrings<yli::ontology::Console&>::type> convert_string_to_value_and_advance_index<yli::ontology::Console&>(
                yli::ontology::Universe&,
                yli::ontology::Console& console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>&, // parameter vector.
                std::size_t&)                    // parameter_i.
        {
            // Note: this specialization returns the `yli::ontology::Console&` provided as an argument,
            // and does not do a lookup.

            context = &console;
            return yli::data::WrapAllButStrings<yli::ontology::Console&>::type(console);
        }

    template<>
        inline std::optional<typename yli::data::WrapAllButStrings<yli::ontology::Console*>::type> convert_string_to_value_and_advance_index<yli::ontology::Console*>(
                yli::ontology::Universe&,
                yli::ontology::Console& console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>&, // parameter vector.
                std::size_t&)                    // parameter_i.
        {
            // Note: this specialization returns the `yli::ontology::Console&` provided as an argument,
            // and does not do a lookup.

            context = &console;
            return yli::data::WrapAllButStrings<yli::ontology::Console*>::type(&console);
        }

    template<>
        inline std::optional<typename yli::data::WrapAllButStrings<yli::ontology::Variable&>::type> convert_string_to_value_and_advance_index<yli::ontology::Variable&>(
                yli::ontology::Universe& universe,
                yli::ontology::Console&,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Variable* const value = dynamic_cast<yli::ontology::Variable*>(universe.get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            context = value;
            return yli::data::WrapAllButStrings<yli::ontology::Variable&>::type(*value);
        }

    template<>
        inline std::optional<typename yli::data::WrapAllButStrings<yli::ontology::Brain&>::type> convert_string_to_value_and_advance_index<yli::ontology::Brain&>(
                yli::ontology::Universe& universe,
                yli::ontology::Console&,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Brain* const value = dynamic_cast<yli::ontology::Brain*>(universe.get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            context = value;
            return yli::data::WrapAllButStrings<yli::ontology::Brain&>::type(*value);
        }

    template<>
        inline std::optional<typename yli::data::WrapAllButStrings<yli::ontology::Movable&>::type> convert_string_to_value_and_advance_index<yli::ontology::Movable&>(
                yli::ontology::Universe& universe,
                yli::ontology::Console&,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Movable* const value = dynamic_cast<yli::ontology::Movable*>(universe.get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            context = value;
            return yli::data::WrapAllButStrings<yli::ontology::Movable&>::type(*value);
        }

    template<>
        inline std::optional<typename yli::data::WrapAllButStrings<const yli::ontology::Variable&>::type> convert_string_to_value_and_advance_index<const yli::ontology::Variable&>(
                yli::ontology::Universe& universe,
                yli::ontology::Console&,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Variable* const value = dynamic_cast<yli::ontology::Variable*>(universe.get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            context = value;
            return yli::data::WrapAllButStrings<const yli::ontology::Variable&>::type(*value);
        }

    template<>
        inline std::optional<typename yli::data::WrapAllButStrings<yli::ontology::Variable*>::type> convert_string_to_value_and_advance_index<yli::ontology::Variable*>(
                yli::ontology::Universe& universe,
                yli::ontology::Console&,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Variable* const value = dynamic_cast<yli::ontology::Variable*>(universe.get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            context = value;
            return yli::data::WrapAllButStrings<yli::ontology::Variable*>::type(value);
        }

    template<>
        inline std::optional<typename yli::data::WrapAllButStrings<yli::ontology::Ecosystem&>::type> convert_string_to_value_and_advance_index<yli::ontology::Ecosystem&>(
                yli::ontology::Universe& universe,
                yli::ontology::Console&,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Ecosystem* const value = dynamic_cast<yli::ontology::Ecosystem*>(universe.get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            context = value;
            return yli::data::WrapAllButStrings<yli::ontology::Ecosystem&>::type(*value);
        }

    template<>
        inline std::optional<typename yli::data::WrapAllButStrings<yli::ontology::Scene&>::type> convert_string_to_value_and_advance_index<yli::ontology::Scene&>(
                yli::ontology::Universe& universe,
                yli::ontology::Console&,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Scene* const value = dynamic_cast<yli::ontology::Scene*>(universe.get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            context = value;
            return yli::data::WrapAllButStrings<yli::ontology::Scene&>::type(*value);
        }

    template<>
        inline std::optional<typename yli::data::WrapAllButStrings<yli::ontology::Pipeline&>::type> convert_string_to_value_and_advance_index<yli::ontology::Pipeline&>(
                yli::ontology::Universe& universe,
                yli::ontology::Console&,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Pipeline* const value = dynamic_cast<yli::ontology::Pipeline*>(universe.get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            context = value;
            return yli::data::WrapAllButStrings<yli::ontology::Pipeline&>::type(*value);
        }

    template<>
        inline std::optional<typename yli::data::WrapAllButStrings<yli::ontology::Material&>::type> convert_string_to_value_and_advance_index<yli::ontology::Material&>(
                yli::ontology::Universe& universe,
                yli::ontology::Console&,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Material* const value = dynamic_cast<yli::ontology::Material*>(universe.get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            context = value;
            return yli::data::WrapAllButStrings<yli::ontology::Material&>::type(*value);
        }

    template<>
        inline std::optional<typename yli::data::WrapAllButStrings<yli::ontology::Species&>::type> convert_string_to_value_and_advance_index<yli::ontology::Species&>(
                yli::ontology::Universe& universe,
                yli::ontology::Console&,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Species* const value = dynamic_cast<yli::ontology::Species*>(universe.get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            context = value;
            return yli::data::WrapAllButStrings<yli::ontology::Species&>::type(*value);
        }

    template<>
        inline std::optional<typename yli::data::WrapAllButStrings<yli::ontology::Species*>::type> convert_string_to_value_and_advance_index<yli::ontology::Species*>(
                yli::ontology::Universe& universe,
                yli::ontology::Console&,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Species* const value = dynamic_cast<yli::ontology::Species*>(universe.get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            context = value;
            return yli::data::WrapAllButStrings<yli::ontology::Species*>::type(value);
        }

    template<>
        inline std::optional<typename yli::data::WrapAllButStrings<yli::ontology::Object&>::type> convert_string_to_value_and_advance_index<yli::ontology::Object&>(
                yli::ontology::Universe& universe,
                yli::ontology::Console&,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Object* const value = dynamic_cast<yli::ontology::Object*>(universe.get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            context = value;
            return yli::data::WrapAllButStrings<yli::ontology::Object&>::type(*value);
        }

    template<>
        inline std::optional<typename yli::data::WrapAllButStrings<yli::ontology::Symbiosis&>::type> convert_string_to_value_and_advance_index<yli::ontology::Symbiosis&>(
                yli::ontology::Universe& universe,
                yli::ontology::Console&,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Symbiosis* const value = dynamic_cast<yli::ontology::Symbiosis*>(universe.get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            context = value;
            return yli::data::WrapAllButStrings<yli::ontology::Symbiosis&>::type(*value);
        }

    template<>
        inline std::optional<typename yli::data::WrapAllButStrings<yli::ontology::ShapeshifterTransformation&>::type> convert_string_to_value_and_advance_index<yli::ontology::ShapeshifterTransformation&>(
                yli::ontology::Universe& universe,
                yli::ontology::Console&,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            yli::ontology::ShapeshifterTransformation* const value = dynamic_cast<yli::ontology::ShapeshifterTransformation*>(universe.get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            context = value;
            return yli::data::WrapAllButStrings<yli::ontology::ShapeshifterTransformation&>::type(*value);
        }

    template<>
        inline std::optional<typename yli::data::WrapAllButStrings<yli::ontology::ShapeshifterSequence&>::type> convert_string_to_value_and_advance_index<yli::ontology::ShapeshifterSequence&>(
                yli::ontology::Universe& universe,
                yli::ontology::Console&,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            yli::ontology::ShapeshifterSequence* const value = dynamic_cast<yli::ontology::ShapeshifterSequence*>(universe.get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            context = value;
            return yli::data::WrapAllButStrings<yli::ontology::ShapeshifterSequence&>::type(*value);
        }

    template<>
        inline std::optional<typename yli::data::WrapAllButStrings<yli::ontology::Symbiosis*>::type> convert_string_to_value_and_advance_index<yli::ontology::Symbiosis*>(
                yli::ontology::Universe& universe,
                yli::ontology::Console&,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Symbiosis* const value = dynamic_cast<yli::ontology::Symbiosis*>(universe.get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            context = value;
            return yli::data::WrapAllButStrings<yli::ontology::Symbiosis*>::type(value);
        }

    template<>
        inline std::optional<typename yli::data::WrapAllButStrings<yli::ontology::Font2d&>::type> convert_string_to_value_and_advance_index<yli::ontology::Font2d&>(
                yli::ontology::Universe& universe,
                yli::ontology::Console&,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Font2d* const value = dynamic_cast<yli::ontology::Font2d*>(universe.get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            context = value;
            return yli::data::WrapAllButStrings<yli::ontology::Font2d&>::type(*value);
        }

    template<>
        inline std::optional<typename yli::data::WrapAllButStrings<yli::ontology::Text2d&>::type> convert_string_to_value_and_advance_index<yli::ontology::Text2d&>(
                yli::ontology::Universe& universe,
                yli::ontology::Console&,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Text2d* const value = dynamic_cast<yli::ontology::Text2d*>(universe.get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            context = value;
            return yli::data::WrapAllButStrings<yli::ontology::Text2d&>::type(*value);
        }

    template<>
        inline std::optional<typename yli::data::WrapAllButStrings<yli::ontology::VectorFont&>::type> convert_string_to_value_and_advance_index<yli::ontology::VectorFont&>(
                yli::ontology::Universe& universe,
                yli::ontology::Console&,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            yli::ontology::VectorFont* const value = dynamic_cast<yli::ontology::VectorFont*>(universe.get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            context = value;
            return yli::data::WrapAllButStrings<yli::ontology::VectorFont&>::type(*value);
        }

    template<>
        inline std::optional<typename yli::data::WrapAllButStrings<yli::ontology::Text3d&>::type> convert_string_to_value_and_advance_index<yli::ontology::Text3d&>(
                yli::ontology::Universe& universe,
                yli::ontology::Console&,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Text3d* const value = dynamic_cast<yli::ontology::Text3d*>(universe.get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            context = value;
            return yli::data::WrapAllButStrings<yli::ontology::Text3d&>::type(*value);
        }

    template<>
        inline std::optional<typename yli::data::WrapAllButStrings<const std::string&>::type> convert_string_to_value_and_advance_index<const std::string&>(
                yli::ontology::Universe&,
                yli::ontology::Console&,
                yli::ontology::Entity*&, // context.
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            return parameter_vector.at(parameter_i++);
        }
}

#endif
