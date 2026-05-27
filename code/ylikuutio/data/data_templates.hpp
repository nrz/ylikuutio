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

#ifndef YLIKUUTIO_DATA_DATA_TEMPLATES_HPP_INCLUDED
#define YLIKUUTIO_DATA_DATA_TEMPLATES_HPP_INCLUDED

// Include standard headers
#include <cstdint>  // std::int8_t, std::int16_t, std::int32_t, std::uint8_t, std::uint16_t, std::uint32_t
#include <memory>   // std::shared_ptr
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::data
{
    // Get the datatype of a variable.
    template<typename T1>
        std::string get_type_string(T1)
        {
            return "unknown";
        }

    template<>
        std::string get_type_string(bool)
        {
            return "bool";
        }

    template<>
        std::string get_type_string(char)
        {
            return "char";
        }

    template<>
        std::string get_type_string(float)
        {
            return "float";
        }

    template<>
        std::string get_type_string(double)
        {
            return "double";
        }

    template<>
        std::string get_type_string(std::int32_t)
        {
            return "std::int32_t";
        }

    template<>
        std::string get_type_string(std::uint32_t)
        {
            return "std::uint32_t";
        }

    template<>
        std::string get_type_string(bool*)
        {
            return "bool*";
        }

    template<>
        std::string get_type_string(char*)
        {
            return "char*";
        }

    template<>
        std::string get_type_string(float*)
        {
            return "float*";
        }

    template<>
        std::string get_type_string(double*)
        {
            return "double*";
        }

    template<>
        std::string get_type_string(std::int32_t*)
        {
            return "std::int32_t*";
        }

    template<>
        std::string get_type_string(std::uint32_t*)
        {
            return "std::uint32_t*";
        }

    template<>
        std::string get_type_string(yli::ontology::Entity*)
        {
            return "yli::ontology::Entity*";
        }

    template<>
        std::string get_type_string(yli::ontology::Movable*)
        {
            return "yli::ontology::Movable*";
        }

    template<>
        std::string get_type_string(const yli::ontology::Movable*)
        {
            return "const yli::ontology::Movable*";
        }

    template<>
        std::string get_type_string(yli::ontology::Universe*)
        {
            return "yli::ontology::Universe*";
        }

    template<>
        std::string get_type_string(yli::ontology::Ecosystem*)
        {
            return "yli::ontology::Ecosystem*";
        }

    template<>
        std::string get_type_string(yli::ontology::Scene*)
        {
            return "yli::ontology::Scene*";
        }

    template<>
        std::string get_type_string(yli::ontology::Pipeline*)
        {
            return "yli::ontology::Pipeline*";
        }

    template<>
        std::string get_type_string(yli::ontology::Material*)
        {
            return "yli::ontology::Material*";
        }

    template<>
        std::string get_type_string(yli::ontology::Species*)
        {
            return "yli::ontology::Species*";
        }

    template<>
        std::string get_type_string(yli::ontology::Object*)
        {
            return "yli::ontology::Object*";
        }

    template<>
        std::string get_type_string(yli::ontology::Symbiosis*)
        {
            return "yli::ontology::Symbiosis*";
        }

    template<>
        std::string get_type_string(yli::ontology::SymbiontMaterial*)
        {
            return "yli::ontology::SymbiontMaterial*";
        }

    template<>
        std::string get_type_string(yli::ontology::SymbiontSpecies*)
        {
            return "yli::ontology::SymbiontSpecies*";
        }

    template<>
        std::string get_type_string(yli::ontology::Holobiont*)
        {
            return "yli::ontology::Holobiont*";
        }

    template<>
        std::string get_type_string(yli::ontology::Biont*)
        {
            return "yli::ontology::Biont*";
        }

    template<>
        std::string get_type_string(yli::ontology::Font2d*)
        {
            return "yli::ontology::Font2d*";
        }

    template<>
        std::string get_type_string(yli::ontology::Text2d*)
        {
            return "yli::ontology::Text2d*";
        }

    template<>
        std::string get_type_string(yli::ontology::VectorFont*)
        {
            return "yli::ontology::VectorFont*";
        }

    template<>
        std::string get_type_string(yli::ontology::Glyph*)
        {
            return "yli::ontology::Glyph*";
        }

    template<>
        std::string get_type_string(yli::ontology::Text3d*)
        {
            return "yli::ontology::Text3d*";
        }

    template<>
        std::string get_type_string(yli::ontology::Console*)
        {
            return "yli::ontology::Console*";
        }

    template<>
        std::string get_type_string(yli::ontology::ComputeTask*)
        {
            return "yli::ontology::ComputeTask*";
        }

    template<>
        std::string get_type_string(std::shared_ptr<AnyValue>)
        {
            return "std::shared_ptr<yli::data::AnyValue>";
        }

    template<>
        std::string get_type_string(std::string*)
        {
            return "std::string*";
        }

    template<>
        std::string get_type_string(const std::string*)
        {
            return "const std::string*";
        }

    template<>
        std::string get_type_string(std::shared_ptr<std::vector<std::int8_t>>)
        {
            return "std::shared_ptr<std::vector<std::int8_t>>";
        }

    template<>
        std::string get_type_string(std::shared_ptr<std::vector<std::uint8_t>>)
        {
            return "std::shared_ptr<std::vector<std::uint8_t>>";
        }

    template<>
        std::string get_type_string(std::shared_ptr<std::vector<std::int16_t>>)
        {
            return "std::shared_ptr<std::vector<std::int16_t>>";
        }

    template<>
        std::string get_type_string(std::shared_ptr<std::vector<std::uint16_t>>)
        {
            return "std::shared_ptr<std::vector<std::uint16_t>>";
        }

    template<>
        std::string get_type_string(std::shared_ptr<std::vector<std::int32_t>>)
        {
            return "std::shared_ptr<std::vector<std::int32_t>>";
        }

    template<>
        std::string get_type_string(std::shared_ptr<std::vector<std::uint32_t>>)
        {
            return "std::shared_ptr<std::vector<std::uint32_t>>";
        }

    template<>
        std::string get_type_string(std::shared_ptr<std::vector<float>>)
        {
            return "std::shared_ptr<std::vector<float>>";
        }

    template<>
        std::string get_type_string(std::shared_ptr<glm::vec3>)
        {
            return "std::shared_ptr<glm::vec3>";
        }

    template<>
        std::string get_type_string(std::shared_ptr<glm::vec4>)
        {
            return "std::shared_ptr<glm::vec4>";
        }

#endif
