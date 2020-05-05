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

#ifndef __DATA_TEMPLATES_HPP_INCLUDED
#define __DATA_TEMPLATES_HPP_INCLUDED

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
#include <cmath>    // NAN, std::isnan, std::pow
#include <memory>   // std::make_shared, std::shared_ptr
#include <sstream>  // std::istringstream, std::ostringstream, std::stringstream
#include <string>   // std::string
#include <tuple>    // std::apply, std::tuple, std::tuple_cat
#include <vector>   // std::vector

namespace yli::common
{
    // Get the datatype of a variable.
    template<class T1>
        std::string get_type_string(T1 data)
        {
            return "unknown";
        }

    template<>
        std::string get_type_string(bool data)
        {
            return "bool";
        }

    template<>
        std::string get_type_string(char data)
        {
            return "char";
        }

    template<>
        std::string get_type_string(float data)
        {
            return "float";
        }

    template<>
        std::string get_type_string(double data)
        {
            return "double";
        }

    template<>
        std::string get_type_string(int32_t data)
        {
            return "int32_t";
        }

    template<>
        std::string get_type_string(uint32_t data)
        {
            return "uint32_t";
        }

    template<>
        std::string get_type_string(bool* data)
        {
            return "bool*";
        }

    template<>
        std::string get_type_string(char* data)
        {
            return "char*";
        }

    template<>
        std::string get_type_string(float* data)
        {
            return "float*";
        }

    template<>
        std::string get_type_string(double* data)
        {
            return "double*";
        }

    template<>
        std::string get_type_string(int32_t* data)
        {
            return "int32_t*";
        }

    template<>
        std::string get_type_string(uint32_t* data)
        {
            return "uint32_t*";
        }

    template<>
        std::string get_type_string(yli::ontology::Entity* data)
        {
            return "yli::ontology::Entity*";
        }

    template<>
        std::string get_type_string(yli::ontology::Movable* data)
        {
            return "yli::ontology::Movable*";
        }

    template<>
        std::string get_type_string(const yli::ontology::Movable* data)
        {
            return "const yli::ontology::Movable*";
        }

    template<>
        std::string get_type_string(yli::ontology::Universe* data)
        {
            return "yli::ontology::Universe*";
        }

    template<>
        std::string get_type_string(yli::ontology::World* data)
        {
            return "yli::ontology::World*";
        }

    template<>
        std::string get_type_string(yli::ontology::Scene* data)
        {
            return "yli::ontology::Scene*";
        }

    template<>
        std::string get_type_string(yli::ontology::Shader* data)
        {
            return "yli::ontology::Shader*";
        }

    template<>
        std::string get_type_string(yli::ontology::Material* data)
        {
            return "yli::ontology::Material*";
        }

    template<>
        std::string get_type_string(yli::ontology::Species* data)
        {
            return "yli::ontology::Species*";
        }

    template<>
        std::string get_type_string(yli::ontology::Object* data)
        {
            return "yli::ontology::Object*";
        }

    template<>
        std::string get_type_string(yli::ontology::Symbiosis* data)
        {
            return "yli::ontology::Symbiosis*";
        }

    template<>
        std::string get_type_string(yli::ontology::SymbiontMaterial* data)
        {
            return "yli::ontology::SymbiontMaterial*";
        }

    template<>
        std::string get_type_string(yli::ontology::SymbiontSpecies* data)
        {
            return "yli::ontology::SymbiontSpecies*";
        }

    template<>
        std::string get_type_string(yli::ontology::Holobiont* data)
        {
            return "yli::ontology::Holobiont*";
        }

    template<>
        std::string get_type_string(yli::ontology::Biont* data)
        {
            return "yli::ontology::Biont*";
        }

    template<>
        std::string get_type_string(yli::ontology::Font2D* data)
        {
            return "yli::ontology::Font2D*";
        }

    template<>
        std::string get_type_string(yli::ontology::Text2D* data)
        {
            return "yli::ontology::Text2D*";
        }

    template<>
        std::string get_type_string(yli::ontology::VectorFont* data)
        {
            return "yli::ontology::VectorFont*";
        }

    template<>
        std::string get_type_string(yli::ontology::Glyph* data)
        {
            return "yli::ontology::Glyph*";
        }

    template<>
        std::string get_type_string(yli::ontology::Text3D* data)
        {
            return "yli::ontology::Text3D*";
        }

    template<>
        std::string get_type_string(yli::ontology::Console* data)
        {
            return "yli::ontology::Console*";
        }

    template<>
        std::string get_type_string(yli::ontology::ComputeTask* data)
        {
            return "yli::ontology::ComputeTask*";
        }

    template<>
        std::string get_type_string(std::shared_ptr<yli::common::AnyValue> data)
        {
            return "std::shared_ptr<yli::common::AnyValue>";
        }

    template<>
        std::string get_type_string(std::shared_ptr<yli::common::AnyStruct> data)
        {
            return "std::shared_ptr<yli::common::AnyStruct>";
        }

    template<>
        std::string get_type_string(yli::common::SphericalCoordinatesStruct* data)
        {
            return "yli::common::SphericalCoordinatesStruct*";
        }

    template<>
        std::string get_type_string(std::string* data)
        {
            return "std::string*";
        }

    template<>
        std::string get_type_string(const std::string* data)
        {
            return "const std::string*";
        }

    template<>
        std::string get_type_string(std::shared_ptr<std::vector<int8_t>> data)
        {
            return "std::shared_ptr<std::vector<int8_t>>";
        }

    template<>
        std::string get_type_string(std::shared_ptr<std::vector<uint8_t>> data)
        {
            return "std::shared_ptr<std::vector<uint8_t>>";
        }

    template<>
        std::string get_type_string(std::shared_ptr<std::vector<int16_t>> data)
        {
            return "std::shared_ptr<std::vector<int16_t>>";
        }

    template<>
        std::string get_type_string(std::shared_ptr<std::vector<uint16_t>> data)
        {
            return "std::shared_ptr<std::vector<uint16_t>>";
        }

    template<>
        std::string get_type_string(std::shared_ptr<std::vector<int32_t>> data)
        {
            return "std::shared_ptr<std::vector<int32_t>>";
        }

    template<>
        std::string get_type_string(std::shared_ptr<std::vector<uint32_t>> data)
        {
            return "std::shared_ptr<std::vector<uint32_t>>";
        }

    template<>
        std::string get_type_string(std::shared_ptr<std::vector<float>> data)
        {
            return "std::shared_ptr<std::vector<float>>";
        }

    template<>
        std::string get_type_string(std::shared_ptr<glm::vec3> data)
        {
            return "std::shared_ptr<glm::vec3>";
        }

    template<>
        std::string get_type_string(std::shared_ptr<glm::vec4> data)
        {
            return "std::shared_ptr<glm::vec4>";
        }

    template<class T1>
        T1 convert_string_to_value(const std::string& my_string, yli::ontology::Universe* universe, yli::ontology::Console* console, bool& success)
        {
            success = false;
            static_assert(sizeof(T1) == -1, "You need to specialize this `yli::common::convert_string_to_value` for the type!");
        }

    template<>
        bool convert_string_to_value(const std::string& my_string, yli::ontology::Universe* universe, yli::ontology::Console* console, bool& success)
        {
            if (my_string == "true") // Ylikuutio is case sensitive!
            {
                success = true;
                return true;
            }
            else if (my_string == "false") // Ylikuutio is case sensitive!
            {
                success = true;
                return false;
            }
            else
            {
                success = false;
                return false;
            }
        }

    template<>
        char convert_string_to_value(const std::string& my_string, ontology::Universe* universe, yli::ontology::Console* console, bool& success)
        {
            if (my_string.size() == 1)
            {
                success = true;
                return my_string[0];
            }

            success = false;
            return '?';
        }

    template<>
        float convert_string_to_value(const std::string& my_string, ontology::Universe* universe, yli::ontology::Console* console, bool& success)
        {
            if (!yli::string::check_if_float_string(my_string))
            {
                success = false;
                return NAN;
            }

            float float_value;
            std::stringstream my_stringstream;
            my_stringstream << my_string;
            my_stringstream >> float_value;
            success = true;
            return float_value;
        }

    template<>
        double convert_string_to_value(const std::string& my_string, yli::ontology::Universe* universe, yli::ontology::Console* console, bool& success)
        {
            if (!yli::string::check_if_double_string(my_string))
            {
                success = false;
                return NAN;
            }

            double double_value;
            std::stringstream my_stringstream;
            my_stringstream << my_string;
            my_stringstream >> double_value;
            success = true;
            return double_value;
        }

    template<>
        int32_t convert_string_to_value(const std::string& my_string, yli::ontology::Universe* universe, yli::ontology::Console* console, bool& success)
        {
            if (!yli::string::check_if_signed_integer_string(my_string))
            {
                success = false;
                return 0;
            }

            int32_t int32_t_value;
            std::stringstream my_stringstream;
            my_stringstream << my_string;
            my_stringstream >> int32_t_value;
            success = true;
            return int32_t_value;
        }

    template<>
        uint32_t convert_string_to_value(const std::string& my_string, yli::ontology::Universe* universe, yli::ontology::Console* console, bool& success)
        {
            if (!yli::string::check_if_unsigned_integer_string(my_string))
            {
                success = false;
                return 0;
            }

            uint32_t uint32_t_value;
            std::stringstream my_stringstream;
            my_stringstream << my_string;
            my_stringstream >> uint32_t_value;
            success = true;
            return uint32_t_value;
        }

    template<>
        yli::ontology::Entity* convert_string_to_value(const std::string& my_string, yli::ontology::Universe* universe, yli::ontology::Console* console, bool& success)
        {
            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                success = false;
                return nullptr;
            }

            success = true;
            return entity;
        }

    template<>
        yli::ontology::Movable* convert_string_to_value(const std::string& my_string, yli::ontology::Universe* universe, yli::ontology::Console* console, bool& success)
        {
            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                success = false;
                return nullptr;
            }

            yli::ontology::Movable* movable = dynamic_cast<yli::ontology::Movable*>(entity);

            if (movable == nullptr)
            {
                success = false;
                return nullptr;
            }

            success = true;
            return movable;
        }

    template<>
        const yli::ontology::Movable* convert_string_to_value(const std::string& my_string, yli::ontology::Universe* universe, yli::ontology::Console* console, bool& success)
        {
            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                success = false;
                return nullptr;
            }

            const yli::ontology::Movable* const_movable = dynamic_cast<const yli::ontology::Movable*>(entity);

            if (const_movable == nullptr)
            {
                success = false;
                return nullptr;
            }

            success = true;
            return const_movable;
        }

    template<>
        yli::ontology::Universe* convert_string_to_value(const std::string& my_string, yli::ontology::Universe* universe, yli::ontology::Console* console, bool& success)
        {
            // Note: this specialization returns the `yli::ontology::Universe*` provided as an argument,
            // and does not do a lookup.

            if (universe == nullptr)
            {
                success = false;
                return nullptr;
            }

            success = true;
            return universe;
        }

    template<>
        yli::ontology::World* convert_string_to_value(const std::string& my_string, yli::ontology::Universe* universe, yli::ontology::Console* console, bool& success)
        {
            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                success = false;
                return nullptr;
            }

            yli::ontology::World* world = dynamic_cast<yli::ontology::World*>(entity);

            if (world == nullptr)
            {
                success = false;
                return nullptr;
            }

            success = true;
            return world;
        }

    template<>
        yli::ontology::Scene* convert_string_to_value(const std::string& my_string, yli::ontology::Universe* universe, yli::ontology::Console* console, bool& success)
        {
            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                success = false;
                return nullptr;
            }

            yli::ontology::Scene* scene = dynamic_cast<yli::ontology::Scene*>(entity);

            if (scene == nullptr)
            {
                success = false;
                return nullptr;
            }

            success = true;
            return scene;
        }

    template<>
        yli::ontology::Shader* convert_string_to_value(const std::string& my_string, yli::ontology::Universe* universe, yli::ontology::Console* console, bool& success)
        {
            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                success = false;
                return nullptr;
            }

            yli::ontology::Shader* shader = dynamic_cast<yli::ontology::Shader*>(entity);

            if (shader == nullptr)
            {
                success = false;
                return nullptr;
            }

            success = true;
            return shader;
        }

    template<>
        yli::ontology::Material* convert_string_to_value(const std::string& my_string, yli::ontology::Universe* universe, yli::ontology::Console* console, bool& success)
        {
            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                success = false;
                return nullptr;
            }

            yli::ontology::Material* material = dynamic_cast<yli::ontology::Material*>(entity);

            if (material == nullptr)
            {
                success = false;
                return nullptr;
            }

            success = true;
            return material;
        }

    template<>
        yli::ontology::Species* convert_string_to_value(const std::string& my_string, yli::ontology::Universe* universe, yli::ontology::Console* console, bool& success)
        {
            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                success = false;
                return nullptr;
            }

            yli::ontology::Species* species = dynamic_cast<yli::ontology::Species*>(entity);

            if (species == nullptr)
            {
                success = false;
                return nullptr;
            }

            success = true;
            return species;
        }

    template<>
        yli::ontology::Object* convert_string_to_value(const std::string& my_string, yli::ontology::Universe* universe, yli::ontology::Console* console, bool& success)
        {
            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                success = false;
                return nullptr;
            }

            yli::ontology::Object* object = dynamic_cast<yli::ontology::Object*>(entity);

            if (object == nullptr)
            {
                success = false;
                return nullptr;
            }

            success = true;
            return object;
        }

    template<>
        yli::ontology::Symbiosis* convert_string_to_value(const std::string& my_string, yli::ontology::Universe* universe, yli::ontology::Console* console, bool& success)
        {
            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                success = false;
                return nullptr;
            }

            yli::ontology::Symbiosis* symbiosis = dynamic_cast<yli::ontology::Symbiosis*>(entity);

            if (symbiosis == nullptr)
            {
                success = false;
                return nullptr;
            }

            success = true;
            return symbiosis;
        }

    template<>
        yli::ontology::Holobiont* convert_string_to_value(const std::string& my_string, yli::ontology::Universe* universe, yli::ontology::Console* console, bool& success)
        {
            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                success = false;
                return nullptr;
            }

            yli::ontology::Holobiont* holobiont = dynamic_cast<yli::ontology::Holobiont*>(entity);

            if (holobiont == nullptr)
            {
                success = false;
                return nullptr;
            }

            success = true;
            return holobiont;
        }

    template<>
        yli::ontology::Font2D* convert_string_to_value(const std::string& my_string, yli::ontology::Universe* universe, yli::ontology::Console* console, bool& success)
        {
            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                success = false;
                return nullptr;
            }

            yli::ontology::Font2D* font2D = dynamic_cast<yli::ontology::Font2D*>(entity);

            if (font2D == nullptr)
            {
                success = false;
                return nullptr;
            }

            success = true;
            return font2D;
        }

    template<>
        yli::ontology::Text2D* convert_string_to_value(const std::string& my_string, yli::ontology::Universe* universe, yli::ontology::Console* console, bool& success)
        {
            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                success = false;
                return nullptr;
            }

            yli::ontology::Text2D* text2D = dynamic_cast<yli::ontology::Text2D*>(entity);

            if (text2D == nullptr)
            {
                success = false;
                return nullptr;
            }

            success = true;
            return text2D;
        }

    template<>
        yli::ontology::Console* convert_string_to_value(const std::string& my_string, yli::ontology::Universe* universe, yli::ontology::Console* console, bool& success)
        {
            // Note: this specialization returns the `yli::ontology::Console*` provided as an argument,
            // and does not do a lookup.

            if (console == nullptr)
            {
                success = false;
                return nullptr;
            }

            success = true;
            return console;
        }

    template<>
        yli::ontology::ComputeTask* convert_string_to_value(const std::string& my_string, yli::ontology::Universe* universe, yli::ontology::Console* console, bool& success)
        {
            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                success = false;
                return nullptr;
            }

            yli::ontology::ComputeTask* compute_task = dynamic_cast<yli::ontology::ComputeTask*>(entity);

            if (compute_task == nullptr)
            {
                success = false;
                return nullptr;
            }

            success = true;
            return compute_task;
        }

    // Templates for processing console command arguments.

    template<class T1>
        T1 convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                bool& success)
        {
            success = false;
            static_assert(sizeof(T1) == -1, "You need to specialize this `yli::common::convert_string_to_value_and_advance_index` for the type!");
        }

    template<>
        bool convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                bool& success)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                success = false;
                return false;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            if (my_string == "true") // Ylikuutio is case sensitive!
            {
                success = true;
                return true;
            }
            else if (my_string == "false") // Ylikuutio is case sensitive!
            {
                success = true;
                return false;
            }
            else
            {
                success = false;
                return false;
            }
        }

    template<>
        char convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                bool& success)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                success = false;
                return '?';
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            if (my_string.size() == 1)
            {
                success = true;
                return my_string[0];
            }

            success = false;
            return '?';
        }

    template<>
        float convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                bool& success)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                success = false;
                return NAN;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            if (!yli::string::check_if_float_string(my_string))
            {
                success = false;
                return NAN;
            }

            float float_value;
            std::stringstream my_stringstream;
            my_stringstream << my_string;
            my_stringstream >> float_value;
            success = true;
            return float_value;
        }

    template<>
        double convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                bool& success)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                success = false;
                return NAN;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            if (!yli::string::check_if_double_string(my_string))
            {
                success = false;
                return NAN;
            }

            double double_value;
            std::stringstream my_stringstream;
            my_stringstream << my_string;
            my_stringstream >> double_value;
            success = true;
            return double_value;
        }

    template<>
        int32_t convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                bool& success)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                success = false;
                return 0;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            if (!yli::string::check_if_signed_integer_string(my_string))
            {
                success = false;
                return 0;
            }

            int32_t int32_t_value;
            std::stringstream my_stringstream;
            my_stringstream << my_string;
            my_stringstream >> int32_t_value;
            success = true;
            return int32_t_value;
        }

    template<>
        uint32_t convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                bool& success)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                success = false;
                return 0;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            if (!yli::string::check_if_unsigned_integer_string(my_string))
            {
                success = false;
                return 0;
            }

            uint32_t uint32_t_value;
            std::stringstream my_stringstream;
            my_stringstream << my_string;
            my_stringstream >> uint32_t_value;
            success = true;
            return uint32_t_value;
        }

    template<>
        yli::ontology::Entity* convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                bool& success)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                success = false;
                return nullptr;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                success = false;
                return nullptr;
            }

            context = entity;
            success = true;
            return entity;
        }

    template<>
        yli::ontology::Movable* convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                bool& success)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                success = false;
                return nullptr;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                success = false;
                return nullptr;
            }

            yli::ontology::Movable* movable = dynamic_cast<yli::ontology::Movable*>(entity);

            if (movable == nullptr)
            {
                success = false;
                return nullptr;
            }

            context = movable;
            success = true;
            return movable;
        }

    template<>
        const yli::ontology::Movable* convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                bool& success)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                success = false;
                return nullptr;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                success = false;
                return nullptr;
            }

            const yli::ontology::Movable* const_movable = dynamic_cast<const yli::ontology::Movable*>(entity);

            if (const_movable == nullptr)
            {
                success = false;
                return nullptr;
            }

            context = const_cast<yli::ontology::Movable*>(const_movable); // Can
            success = true;
            return const_movable;
        }

    template<>
        yli::ontology::Universe* convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                bool& success)
        {
            // Note: this specialization returns the `yli::ontology::Universe*` provided as an argument,
            // and does not do a lookup.

            if (universe == nullptr)
            {
                success = false;
                return nullptr;
            }

            context = universe;
            success = true;
            return universe;
        }

    template<>
        yli::ontology::World* convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                bool& success)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                success = false;
                return nullptr;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                success = false;
                return nullptr;
            }

            yli::ontology::World* world = dynamic_cast<yli::ontology::World*>(entity);

            if (world == nullptr)
            {
                success = false;
                return nullptr;
            }

            context = world;
            success = true;
            return world;
        }

    template<>
        yli::ontology::Scene* convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                bool& success)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                success = false;
                return nullptr;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                success = false;
                return nullptr;
            }

            yli::ontology::Scene* scene = dynamic_cast<yli::ontology::Scene*>(entity);

            if (scene == nullptr)
            {
                success = false;
                return nullptr;
            }

            context = scene;
            success = true;
            return scene;
        }

    template<>
        yli::ontology::Shader* convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                bool& success)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                success = false;
                return nullptr;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                success = false;
                return nullptr;
            }

            yli::ontology::Shader* shader = dynamic_cast<yli::ontology::Shader*>(entity);

            if (shader == nullptr)
            {
                success = false;
                return nullptr;
            }

            context = shader;
            success = true;
            return shader;
        }

    template<>
        yli::ontology::Material* convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                bool& success)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                success = false;
                return nullptr;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                success = false;
                return nullptr;
            }

            yli::ontology::Material* material = dynamic_cast<yli::ontology::Material*>(entity);

            if (material == nullptr)
            {
                success = false;
                return nullptr;
            }

            context = material;
            success = true;
            return material;
        }

    template<>
        yli::ontology::Species* convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                bool& success)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                success = false;
                return nullptr;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                success = false;
                return nullptr;
            }

            yli::ontology::Species* species = dynamic_cast<yli::ontology::Species*>(entity);

            if (species == nullptr)
            {
                success = false;
                return nullptr;
            }

            context = species;
            success = true;
            return species;
        }

    template<>
        yli::ontology::Object* convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                bool& success)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                success = false;
                return nullptr;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                success = false;
                return nullptr;
            }

            yli::ontology::Object* object = dynamic_cast<yli::ontology::Object*>(entity);

            if (object == nullptr)
            {
                success = false;
                return nullptr;
            }

            context = object;
            success = true;
            return object;
        }

    template<>
        yli::ontology::Symbiosis* convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                bool& success)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                success = false;
                return nullptr;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                success = false;
                return nullptr;
            }

            yli::ontology::Symbiosis* symbiosis = dynamic_cast<yli::ontology::Symbiosis*>(entity);

            if (symbiosis == nullptr)
            {
                success = false;
                return nullptr;
            }

            context = symbiosis;
            success = true;
            return symbiosis;
        }

    template<>
        yli::ontology::Holobiont* convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                bool& success)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                success = false;
                return nullptr;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                success = false;
                return nullptr;
            }

            yli::ontology::Holobiont* holobiont = dynamic_cast<yli::ontology::Holobiont*>(entity);

            if (holobiont == nullptr)
            {
                success = false;
                return nullptr;
            }

            context = holobiont;
            success = true;
            return holobiont;
        }

    template<>
        yli::ontology::Font2D* convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                bool& success)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                success = false;
                return nullptr;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                success = false;
                return nullptr;
            }

            yli::ontology::Font2D* font2D = dynamic_cast<yli::ontology::Font2D*>(entity);

            if (font2D == nullptr)
            {
                success = false;
                return nullptr;
            }

            context = font2D;
            success = true;
            return font2D;
        }

    template<>
        yli::ontology::Text2D* convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                bool& success)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                success = false;
                return nullptr;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                success = false;
                return nullptr;
            }

            yli::ontology::Text2D* text2D = dynamic_cast<yli::ontology::Text2D*>(entity);

            if (text2D == nullptr)
            {
                success = false;
                return nullptr;
            }

            context = text2D;
            success = true;
            return text2D;
        }

    template<>
        yli::ontology::Console* convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                bool& success)
        {
            // Note: this specialization returns the `yli::ontology::Console*` provided as an argument,
            // and does not do a lookup.

            if (console == nullptr)
            {
                success = false;
                return nullptr;
            }

            context = console;
            success = true;
            return console;
        }

    template<>
        yli::ontology::ComputeTask* convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                bool& success)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                success = false;
                return nullptr;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            yli::ontology::Entity* entity = universe->get_entity(my_string);

            if (entity == nullptr)
            {
                success = false;
                return nullptr;
            }

            yli::ontology::ComputeTask* compute_task = dynamic_cast<yli::ontology::ComputeTask*>(entity);

            if (compute_task == nullptr)
            {
                success = false;
                return nullptr;
            }

            context = compute_task;
            success = true;
            return compute_task;
        }

    template<>
        yli::config::Setting* convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                bool& success)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                success = false;
                return nullptr;
            }

            yli::config::SettingMaster* setting_master = context->get_setting_master();

            if (setting_master == nullptr)
            {
                success = false;
                return nullptr;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            yli::config::Setting* setting = setting_master->get(my_string);

            if (setting == nullptr)
            {
                success = false;
                return nullptr;
            }

            success = true;
            return setting;
        }

    template<>
        const yli::config::Setting* convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                bool& success)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                success = false;
                return nullptr;
            }

            yli::config::SettingMaster* setting_master = context->get_setting_master();

            if (setting_master == nullptr)
            {
                success = false;
                return nullptr;
            }

            const std::string my_string = parameter_vector.at(parameter_i++);

            const yli::config::Setting* const_setting = setting_master->get(my_string);

            if (const_setting == nullptr)
            {
                success = false;
                return nullptr;
            }

            success = true;
            return const_setting;
        }

    template<>
        std::shared_ptr<std::string> convert_string_to_value_and_advance_index(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                bool& success)
        {
            if (parameter_i >= parameter_vector.size()) // No argument left to consume.
            {
                success = false;
                return nullptr;
            }

            success = true;
            return std::make_shared<std::string>(parameter_vector.at(parameter_i++));
        }
}

#endif
