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

#ifndef YLIKUUTIO_LISP_LISP_TEMPLATES_HPP_INCLUDED
#define YLIKUUTIO_LISP_LISP_TEMPLATES_HPP_INCLUDED

#include "code/ylikuutio/data/wrap.hpp"
#include "code/ylikuutio/ontology/entity.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/variable.hpp"
#include "code/ylikuutio/ontology/movable_controller.hpp"
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
#include <cstdint>  // std::int32_t, std::int64_t, std::uint32_t, std::uint64_t
#include <sstream>  // std::stringstream
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::lisp
{
    // Templates for processing Lisp function arguments.
    //
    // The default environment is `Universe`.
    //
    // 1. If the callback has `yli::ontology::Universe&` or `yli::ontology::Universe*` as an argument,
    //    then the `Universe*` will be provided. This does not consume any parameters.
    //    The `Universe` is set as environment.
    //
    // 2. If the callback has `yli::ontology::Console&` or `yli::ontology::Console*` as an argument,
    //    then this `Console*` will be provided. This does not consume any parameters.
    //    In the future other `Console`s will be made reachable as well, with `yli::ontology::SomeContext*`.
    //    The `Console` is set as environment.
    //
    // 3. Otherwise, if the callback has `yli::ontology::Entity&` or `yli::ontology::Entity*` or
    //    some subtype of `Entity` as an argument, then the string will be looked up and converted into that.
    //    The `Entity` is set as environment.
    //
    // 4. If the callback has `bool` as an argument, then the string will be converted into that.
    //
    // 5. If the callback has `float` as an argument, then the string will be converted into that.
    //
    // 6. If the callback has `double` as an argument, then the string will be converted into that.
    //
    // 7. If the callback has `std::int32_t` as an argument, then the string will be converted into that.
    //
    // 8. If the callback has `std::uint32_t` as an argument, then the string will be converted into that.

    template<typename T1>
        std::optional<typename data::WrapAllButStrings<T1>::type> convert_string_to_value_and_advance_index(
                ontology::Universe&,
                ontology::Console&,
                ontology::Entity*&,         // environment.
                const std::vector<std::string>&, // parameter vector.
                std::size_t&) = delete;          // parameter_i.

    template<>
        inline std::optional<data::WrapAllButStrings<bool>::type> convert_string_to_value_and_advance_index<bool>(
                ontology::Universe&,
                ontology::Console&,
                ontology::Entity*&, // environment.
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
            if (my_string == "false") // Ylikuutio is case sensitive!
            {
                return false; // OK, false.
            }
            return std::nullopt;
        }

    template<>
        inline std::optional<data::WrapAllButStrings<char>::type> convert_string_to_value_and_advance_index<char>(
                ontology::Universe&,
                ontology::Console&,
                ontology::Entity*&, // environment.
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            if (const std::string& my_string = parameter_vector.at(parameter_i++); my_string.size() == 1)
            {
                return my_string[0];
            }

            return std::nullopt;
        }

    template<>
        inline std::optional<data::WrapAllButStrings<float>::type> convert_string_to_value_and_advance_index<float>(
                ontology::Universe&,
                ontology::Console&,
                ontology::Entity*&, // environment.
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            if (!string::check_if_float_string<char>(my_string))
            {
                return std::nullopt;
            }

            float value;
            std::stringstream my_stringstream;
            my_stringstream << my_string;
            my_stringstream >> value;
            return value;
        }

    template<>
        inline std::optional<data::WrapAllButStrings<double>::type> convert_string_to_value_and_advance_index<double>(
                ontology::Universe&,
                ontology::Console&,
                ontology::Entity*&, // environment.
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            if (!string::check_if_double_string<char>(my_string))
            {
                return std::nullopt;
            }

            double value;
            std::stringstream my_stringstream;
            my_stringstream << my_string;
            my_stringstream >> value;
            return value;
        }

    template<>
        inline std::optional<data::WrapAllButStrings<std::int32_t>::type> convert_string_to_value_and_advance_index<std::int32_t>(
                ontology::Universe&,
                ontology::Console&,
                ontology::Entity*&, // environment.
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            if (!string::check_if_signed_integer_string<char>(my_string))
            {
                return std::nullopt;
            }

            std::int32_t value;
            std::stringstream my_stringstream;
            my_stringstream << my_string;
            my_stringstream >> value;
            return value;
        }

    template<>
        inline std::optional<data::WrapAllButStrings<std::uint32_t>::type> convert_string_to_value_and_advance_index<std::uint32_t>(
                ontology::Universe&,
                ontology::Console&,
                ontology::Entity*&, // environment.
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            if (!string::check_if_unsigned_integer_string<char>(my_string))
            {
                return std::nullopt;
            }

            std::uint32_t value;
            std::stringstream my_stringstream;
            my_stringstream << my_string;
            my_stringstream >> value;
            return value;
        }

    template<>
        inline std::optional<data::WrapAllButStrings<std::int64_t>::type> convert_string_to_value_and_advance_index<std::int64_t>(
                ontology::Universe&,
                ontology::Console&,
                ontology::Entity*&, // environment.
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            if (!string::check_if_signed_integer_string<char>(my_string))
            {
                return std::nullopt;
            }

            std::int64_t value;
            std::stringstream my_stringstream;
            my_stringstream << my_string;
            my_stringstream >> value;
            return value;
        }

    template<>
        inline std::optional<data::WrapAllButStrings<std::uint64_t>::type> convert_string_to_value_and_advance_index<std::uint64_t>(
                ontology::Universe&,
                ontology::Console&,
                ontology::Entity*&, // environment.
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            if (!string::check_if_unsigned_integer_string<char>(my_string))
            {
                return std::nullopt;
            }

            std::uint64_t value;
            std::stringstream my_stringstream;
            my_stringstream << my_string;
            my_stringstream >> value;
            return value;
        }

    template<>
        inline std::optional<data::WrapAllButStrings<const std::string&>::type> convert_string_to_value_and_advance_index<const std::string&>(
                ontology::Universe&,
                ontology::Console&,
                ontology::Entity*&, // environment.
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            return parameter_vector.at(parameter_i++);
        }

    template<>
        inline std::optional<data::WrapAllButStrings<ontology::Entity&>::type> convert_string_to_value_and_advance_index<ontology::Entity&>(
                ontology::Universe& universe,
                ontology::Console&,
                ontology::Entity*& environment,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            ontology::Entity* const value = universe.get_entity(my_string);

            if (value == nullptr)
            {
                return std::nullopt;
            }

            environment = value;
            return data::WrapAllButStrings<ontology::Entity&>::type(*value);
        }

    template<>
        inline std::optional<data::WrapAllButStrings<ontology::Entity*>::type> convert_string_to_value_and_advance_index<ontology::Entity*>(
                ontology::Universe& universe,
                ontology::Console&,
                ontology::Entity*& environment,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            ontology::Entity* const value = universe.get_entity(my_string);

            if (value == nullptr)
            {
                return std::nullopt;
            }

            environment = value;
            return value;
        }

    template<>
        inline std::optional<data::WrapAllButStrings<const ontology::Entity&>::type> convert_string_to_value_and_advance_index<const ontology::Entity&>(
                ontology::Universe& universe,
                ontology::Console&,
                ontology::Entity*& environment,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            ontology::Entity* const value = universe.get_entity(my_string);

            if (value == nullptr)
            {
                return std::nullopt;
            }

            environment = value;
            return data::WrapAllButStrings<const ontology::Entity&>::type(*value);
        }

    template<>
        inline std::optional<data::WrapAllButStrings<ontology::Movable&>::type> convert_string_to_value_and_advance_index<ontology::Movable&>(
                ontology::Universe& universe,
                ontology::Console&,
                ontology::Entity*& environment,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            ontology::Movable* const value = dynamic_cast<ontology::Movable*>(universe.get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            environment = value;
            return data::WrapAllButStrings<ontology::Movable&>::type(*value);
        }

    template<>
        inline std::optional<data::WrapAllButStrings<ontology::Universe&>::type> convert_string_to_value_and_advance_index<ontology::Universe&>(
                ontology::Universe& universe,
                ontology::Console&,
                ontology::Entity*& environment,
                const std::vector<std::string>&, // parameter vector.
                std::size_t&)                    // parameter_i.
        {
            // Note: this specialization returns the `yli::ontology::Universe&` provided as an argument,
            // and does not do a lookup.

            environment = &universe;
            return data::WrapAllButStrings<ontology::Universe&>::type(universe);
        }

    template<>
        inline std::optional<data::WrapAllButStrings<ontology::Universe*>::type> convert_string_to_value_and_advance_index<ontology::Universe*>(
                ontology::Universe& universe,
                ontology::Console&,
                ontology::Entity*& environment,
                const std::vector<std::string>&, // parameter vector.
                std::size_t&)                    // parameter_i.
        {
            // Note: this specialization returns the `yli::ontology::Universe*` provided as an argument,
            // and does not do a lookup.

            environment = &universe;
            return &universe;
        }

    template<>
        inline std::optional<data::WrapAllButStrings<const ontology::Universe&>::type> convert_string_to_value_and_advance_index<const ontology::Universe&>(
                ontology::Universe& universe,
                ontology::Console&,
                ontology::Entity*& environment,
                const std::vector<std::string>&, // parameter vector.
                std::size_t&)                    // parameter_i.
        {
            // Note: this specialization returns the `yli::ontology::Universe&` provided as an argument,
            // and does not do a lookup.

            environment = &universe;
            return data::WrapAllButStrings<const ontology::Universe&>::type(universe);
        }

    template<>
        inline std::optional<data::WrapAllButStrings<ontology::Variable&>::type> convert_string_to_value_and_advance_index<ontology::Variable&>(
                ontology::Universe& universe,
                ontology::Console&,
                ontology::Entity*& environment,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            ontology::Variable* const value = dynamic_cast<ontology::Variable*>(universe.get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            environment = value;
            return data::WrapAllButStrings<ontology::Variable&>::type(*value);
        }

    template<>
        inline std::optional<data::WrapAllButStrings<ontology::Variable*>::type> convert_string_to_value_and_advance_index<ontology::Variable*>(
                ontology::Universe& universe,
                ontology::Console&,
                ontology::Entity*& environment,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            ontology::Variable* const value = dynamic_cast<ontology::Variable*>(universe.get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            environment = value;
            return value;
        }

    template<>
        inline std::optional<data::WrapAllButStrings<const ontology::Variable&>::type> convert_string_to_value_and_advance_index<const ontology::Variable&>(
                ontology::Universe& universe,
                ontology::Console&,
                ontology::Entity*& environment,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            ontology::Variable* const value = dynamic_cast<ontology::Variable*>(universe.get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            environment = value;
            return data::WrapAllButStrings<const ontology::Variable&>::type(*value);
        }

    template<>
        inline std::optional<data::WrapAllButStrings<ontology::Ecosystem&>::type> convert_string_to_value_and_advance_index<ontology::Ecosystem&>(
                ontology::Universe& universe,
                ontology::Console&,
                ontology::Entity*& environment,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            ontology::Ecosystem* const value = dynamic_cast<ontology::Ecosystem*>(universe.get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            environment = value;
            return data::WrapAllButStrings<ontology::Ecosystem&>::type(*value);
        }

    template<>
        inline std::optional<data::WrapAllButStrings<ontology::Scene&>::type> convert_string_to_value_and_advance_index<ontology::Scene&>(
                ontology::Universe& universe,
                ontology::Console&,
                ontology::Entity*& environment,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            ontology::Scene* const value = dynamic_cast<ontology::Scene*>(universe.get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            environment = value;
            return data::WrapAllButStrings<ontology::Scene&>::type(*value);
        }

    template<>
        inline std::optional<data::WrapAllButStrings<ontology::MovableController&>::type> convert_string_to_value_and_advance_index<ontology::MovableController&>(
                ontology::Universe& universe,
                ontology::Console&,
                ontology::Entity*& environment,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            ontology::MovableController* const value = dynamic_cast<ontology::MovableController*>(universe.get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            environment = value;
            return data::WrapAllButStrings<ontology::MovableController&>::type(*value);
        }

    template<>
        inline std::optional<data::WrapAllButStrings<ontology::Pipeline&>::type> convert_string_to_value_and_advance_index<ontology::Pipeline&>(
                ontology::Universe& universe,
                ontology::Console&,
                ontology::Entity*& environment,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            ontology::Pipeline* const value = dynamic_cast<ontology::Pipeline*>(universe.get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            environment = value;
            return data::WrapAllButStrings<ontology::Pipeline&>::type(*value);
        }

    template<>
        inline std::optional<data::WrapAllButStrings<ontology::Material&>::type> convert_string_to_value_and_advance_index<ontology::Material&>(
                ontology::Universe& universe,
                ontology::Console&,
                ontology::Entity*& environment,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            ontology::Material* const value = dynamic_cast<ontology::Material*>(universe.get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            environment = value;
            return data::WrapAllButStrings<ontology::Material&>::type(*value);
        }

    template<>
        inline std::optional<data::WrapAllButStrings<ontology::Species&>::type> convert_string_to_value_and_advance_index<ontology::Species&>(
                ontology::Universe& universe,
                ontology::Console&,
                ontology::Entity*& environment,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            ontology::Species* const value = dynamic_cast<ontology::Species*>(universe.get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            environment = value;
            return data::WrapAllButStrings<ontology::Species&>::type(*value);
        }

    template<>
        inline std::optional<data::WrapAllButStrings<ontology::Species*>::type> convert_string_to_value_and_advance_index<ontology::Species*>(
                ontology::Universe& universe,
                ontology::Console&,
                ontology::Entity*& environment,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            ontology::Species* const value = dynamic_cast<ontology::Species*>(universe.get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            environment = value;
            return value;
        }

    template<>
        inline std::optional<data::WrapAllButStrings<ontology::Object&>::type> convert_string_to_value_and_advance_index<ontology::Object&>(
                ontology::Universe& universe,
                ontology::Console&,
                ontology::Entity*& environment,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            ontology::Object* const value = dynamic_cast<ontology::Object*>(universe.get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            environment = value;
            return data::WrapAllButStrings<ontology::Object&>::type(*value);
        }

    template<>
        inline std::optional<data::WrapAllButStrings<ontology::Symbiosis&>::type> convert_string_to_value_and_advance_index<ontology::Symbiosis&>(
                ontology::Universe& universe,
                ontology::Console&,
                ontology::Entity*& environment,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            ontology::Symbiosis* const value = dynamic_cast<ontology::Symbiosis*>(universe.get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            environment = value;
            return data::WrapAllButStrings<ontology::Symbiosis&>::type(*value);
        }

    template<>
        inline std::optional<data::WrapAllButStrings<ontology::Symbiosis*>::type> convert_string_to_value_and_advance_index<ontology::Symbiosis*>(
                ontology::Universe& universe,
                ontology::Console&,
                ontology::Entity*& environment,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            ontology::Symbiosis* const value = dynamic_cast<ontology::Symbiosis*>(universe.get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            environment = value;
            return value;
        }

    template<>
        inline std::optional<data::WrapAllButStrings<ontology::ShapeshifterTransformation&>::type> convert_string_to_value_and_advance_index<ontology::ShapeshifterTransformation&>(
                ontology::Universe& universe,
                ontology::Console&,
                ontology::Entity*& environment,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            ontology::ShapeshifterTransformation* const value = dynamic_cast<ontology::ShapeshifterTransformation*>(universe.get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            environment = value;
            return data::WrapAllButStrings<ontology::ShapeshifterTransformation&>::type(*value);
        }

    template<>
        inline std::optional<data::WrapAllButStrings<ontology::ShapeshifterSequence&>::type> convert_string_to_value_and_advance_index<ontology::ShapeshifterSequence&>(
                ontology::Universe& universe,
                ontology::Console&,
                ontology::Entity*& environment,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            ontology::ShapeshifterSequence* const value = dynamic_cast<ontology::ShapeshifterSequence*>(universe.get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            environment = value;
            return data::WrapAllButStrings<ontology::ShapeshifterSequence&>::type(*value);
        }

    template<>
        inline std::optional<data::WrapAllButStrings<ontology::Font2d&>::type> convert_string_to_value_and_advance_index<ontology::Font2d&>(
                ontology::Universe& universe,
                ontology::Console&,
                ontology::Entity*& environment,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            ontology::Font2d* const value = dynamic_cast<ontology::Font2d*>(universe.get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            environment = value;
            return data::WrapAllButStrings<ontology::Font2d&>::type(*value);
        }

    template<>
        inline std::optional<data::WrapAllButStrings<ontology::Text2d&>::type> convert_string_to_value_and_advance_index<ontology::Text2d&>(
                ontology::Universe& universe,
                ontology::Console&,
                ontology::Entity*& environment,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            ontology::Text2d* const value = dynamic_cast<ontology::Text2d*>(universe.get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            environment = value;
            return data::WrapAllButStrings<ontology::Text2d&>::type(*value);
        }

    template<>
        inline std::optional<data::WrapAllButStrings<ontology::VectorFont&>::type> convert_string_to_value_and_advance_index<ontology::VectorFont&>(
                ontology::Universe& universe,
                ontology::Console&,
                ontology::Entity*& environment,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            ontology::VectorFont* const value = dynamic_cast<ontology::VectorFont*>(universe.get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            environment = value;
            return data::WrapAllButStrings<ontology::VectorFont&>::type(*value);
        }

    template<>
        inline std::optional<data::WrapAllButStrings<ontology::Text3d&>::type> convert_string_to_value_and_advance_index<ontology::Text3d&>(
                ontology::Universe& universe,
                ontology::Console&,
                ontology::Entity*& environment,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                return std::nullopt;
            }

            const std::string& my_string = parameter_vector.at(parameter_i++);

            ontology::Text3d* const value = dynamic_cast<ontology::Text3d*>(universe.get_entity(my_string));

            if (value == nullptr)
            {
                return std::nullopt;
            }

            environment = value;
            return data::WrapAllButStrings<ontology::Text3d&>::type(*value);
        }

    template<>
        inline std::optional<data::WrapAllButStrings<ontology::Console&>::type> convert_string_to_value_and_advance_index<ontology::Console&>(
                ontology::Universe&,
                ontology::Console& context,
                ontology::Entity*& environment,
                const std::vector<std::string>&, // parameter vector.
                std::size_t&)                    // parameter_i.
        {
            // Note: this specialization returns the `yli::ontology::Console&` provided as an argument,
            // and does not do a lookup.

            environment = &context;
            return data::WrapAllButStrings<ontology::Console&>::type(context);
        }

    template<>
        inline std::optional<data::WrapAllButStrings<ontology::Console*>::type> convert_string_to_value_and_advance_index<ontology::Console*>(
                ontology::Universe&,
                ontology::Console& context,
                ontology::Entity*& environment,
                const std::vector<std::string>&, // parameter vector.
                std::size_t&)                    // parameter_i.
        {
            // Note: this specialization returns the `yli::ontology::Console&` provided as an argument,
            // and does not do a lookup.

            environment = &context;
            return &context;
        }
}

#endif
