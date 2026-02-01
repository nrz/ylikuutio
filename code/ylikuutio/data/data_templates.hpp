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
#include <stdint.h> // uint32_t etc.
#include <memory>   // std::shared_ptr
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::data
{
    // Get the datatype of a variable.
    template<typename T1>
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
        std::string get_type_string(yli::ontology::Ecosystem* data)
        {
            return "yli::ontology::Ecosystem*";
        }

    template<>
        std::string get_type_string(yli::ontology::Scene* data)
        {
            return "yli::ontology::Scene*";
        }

    template<>
        std::string get_type_string(yli::ontology::Pipeline* data)
        {
            return "yli::ontology::Pipeline*";
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
        std::string get_type_string(yli::ontology::Font2d* data)
        {
            return "yli::ontology::Font2d*";
        }

    template<>
        std::string get_type_string(yli::ontology::Text2d* data)
        {
            return "yli::ontology::Text2d*";
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
        std::string get_type_string(yli::ontology::Text3d* data)
        {
            return "yli::ontology::Text3d*";
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
        std::string get_type_string(std::shared_ptr<AnyValue> data)
        {
            return "std::shared_ptr<yli::data::AnyValue>";
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

#endif
