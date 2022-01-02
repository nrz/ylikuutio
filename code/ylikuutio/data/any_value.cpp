// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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

#ifndef __STDC_FORMAT_MACROS
// For MinGW.
#define __STDC_FORMAT_MACROS
#endif

#include "any_value.hpp"
#include "any_struct.hpp"
#include "variant_templates.hpp"
#include "spherical_coordinates_struct.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <ios>      // std::boolalpha, std::defaultfloat, std::dec, std::fixed, std::hex, std::ios
#include <memory>   // std::make_shared, std::shared_ptr
#include <optional> // std::optional
#include <sstream>  // std::istringstream, std::ostringstream, std::stringstream
#include <string>   // std::string
#include <stdint.h> // uint32_t etc.
#include <variant>  // std::holds_alternative, std::monostate, std::variant
#include <vector>   // std::vector

namespace yli::ontology
{
    class Entity;
    class Movable;
    class Universe;
    class Ecosystem;
    class Scene;
    class Shader;
    class Material;
    class Species;
    class Object;
    class Symbiosis;
    class SymbiontMaterial;
    class SymbiontSpecies;
    class Holobiont;
    class Biont;
    class Font2D;
    class Text2D;
    class VectorFont;
    class Glyph;
    class Text3D;
    class Console;
    class ComputeTask;
}

namespace yli::data
{
    bool AnyValue::operator==(const yli::data::AnyValue& rhs) const
    {
        return this->data == rhs.data;
    }

    bool AnyValue::operator!=(const yli::data::AnyValue& rhs) const
    {
        return !this->operator==(rhs);
    }

    std::string AnyValue::get_datatype() const
    {
        if (std::holds_alternative<bool>(this->data))
        {
            return "bool";
        }
        else if (std::holds_alternative<char>(this->data))
        {
            return "char";
        }
        else if (std::holds_alternative<float>(this->data))
        {
            return "float";
        }
        else if (std::holds_alternative<double>(this->data))
        {
            return "double";
        }
        else if (std::holds_alternative<int32_t>(this->data))
        {
            return "int32_t";
        }
        else if (std::holds_alternative<uint32_t>(this->data))
        {
            return "uint32_t";
        }
        else if (std::holds_alternative<bool*>(this->data))
        {
            return "bool*";
        }
        else if (std::holds_alternative<char*>(this->data))
        {
            return "char*";
        }
        else if (std::holds_alternative<float*>(this->data))
        {
            return "float*";
        }
        else if (std::holds_alternative<double*>(this->data))
        {
            return "double*";
        }
        else if (std::holds_alternative<int32_t*>(this->data))
        {
            return "int32_t*";
        }
        else if (std::holds_alternative<uint32_t*>(this->data))
        {
            return "uint32_t*";
        }
        else if (std::holds_alternative<yli::ontology::Entity*>(this->data))
        {
            return "yli::ontology::Entity*";
        }
        else if (std::holds_alternative<yli::ontology::Movable*>(this->data))
        {
            return "yli::ontology::Movable*";
        }
        else if (std::holds_alternative<const yli::ontology::Movable*>(this->data))
        {
            return "const yli::ontology::Movable*";
        }
        else if (std::holds_alternative<yli::ontology::Universe*>(this->data))
        {
            return "yli::ontology::Universe*";
        }
        else if (std::holds_alternative<yli::ontology::Ecosystem*>(this->data))
        {
            return "yli::ontology::Ecosystem*";
        }
        else if (std::holds_alternative<yli::ontology::Scene*>(this->data))
        {
            return "yli::ontology::Scene*";
        }
        else if (std::holds_alternative<yli::ontology::Shader*>(this->data))
        {
            return "yli::ontology::Shader*";
        }
        else if (std::holds_alternative<yli::ontology::Material*>(this->data))
        {
            return "yli::ontology::Material*";
        }
        else if (std::holds_alternative<yli::ontology::Species*>(this->data))
        {
            return "yli::ontology::Species*";
        }
        else if (std::holds_alternative<yli::ontology::Object*>(this->data))
        {
            return "yli::ontology::Object*";
        }
        else if (std::holds_alternative<yli::ontology::Symbiosis*>(this->data))
        {
            return "yli::ontology::Symbiosis*";
        }
        else if (std::holds_alternative<yli::ontology::SymbiontMaterial*>(this->data))
        {
            return "yli::ontology::SymbiontMaterial*";
        }
        else if (std::holds_alternative<yli::ontology::SymbiontSpecies*>(this->data))
        {
            return "yli::ontology::SymbiontSpecies*";
        }
        else if (std::holds_alternative<yli::ontology::Holobiont*>(this->data))
        {
            return "yli::ontology::Holobiont*";
        }
        else if (std::holds_alternative<yli::ontology::Biont*>(this->data))
        {
            return "yli::ontology::Biont*";
        }
        else if (std::holds_alternative<yli::ontology::Font2D*>(this->data))
        {
            return "yli::ontology::Font2D*";
        }
        else if (std::holds_alternative<yli::ontology::Text2D*>(this->data))
        {
            return "yli::ontology::Text2D*";
        }
        else if (std::holds_alternative<yli::ontology::VectorFont*>(this->data))
        {
            return "yli::ontology::VectorFont*";
        }
        else if (std::holds_alternative<yli::ontology::Glyph*>(this->data))
        {
            return "yli::ontology::Glyph*";
        }
        else if (std::holds_alternative<yli::ontology::Text3D*>(this->data))
        {
            return "yli::ontology::Text3D*";
        }
        else if (std::holds_alternative<yli::ontology::Console*>(this->data))
        {
            return "yli::ontology::Console*";
        }
        else if (std::holds_alternative<yli::ontology::ComputeTask*>(this->data))
        {
            return "yli::ontology::ComputeTask*";
        }
        else if (std::holds_alternative<std::shared_ptr<yli::data::AnyValue>>(this->data))
        {
            return "std::shared_ptr<yli::data::AnyValue>";
        }
        else if (std::holds_alternative<std::shared_ptr<yli::data::AnyStruct>>(this->data))
        {
            return "std::shared_ptr<yli::data::AnyStruct>";
        }
        else if (std::holds_alternative<yli::data::SphericalCoordinatesStruct*>(this->data))
        {
            return "yli::data::SphericalCoordinatesStruct*";
        }
        else if (std::holds_alternative<std::string*>(this->data))
        {
            return "std::string*";
        }
        else if (std::holds_alternative<const std::string*>(this->data))
        {
            return "const std::string*";
        }
        else if (std::holds_alternative<std::shared_ptr<std::vector<int8_t>>>(this->data))
        {
            return "std::shared_ptr<std::vector<int8_t>>";
        }
        else if (std::holds_alternative<std::shared_ptr<std::vector<uint8_t>>>(this->data))
        {
            return "std::shared_ptr<std::vector<uint8_t>>";
        }
        else if (std::holds_alternative<std::shared_ptr<std::vector<int16_t>>>(this->data))
        {
            return "std::shared_ptr<std::vector<int16_t>>";
        }
        else if (std::holds_alternative<std::shared_ptr<std::vector<uint16_t>>>(this->data))
        {
            return "std::shared_ptr<std::vector<uint16_t>>";
        }
        else if (std::holds_alternative<std::shared_ptr<std::vector<int32_t>>>(this->data))
        {
            return "std::shared_ptr<std::vector<int32_t>>";
        }
        else if (std::holds_alternative<std::shared_ptr<std::vector<uint32_t>>>(this->data))
        {
            return "std::shared_ptr<std::vector<uint32_t>>";
        }
        else if (std::holds_alternative<std::shared_ptr<std::vector<float>>>(this->data))
        {
            return "std::shared_ptr<std::vector<float>>";
        }
        else if (std::holds_alternative<std::shared_ptr<std::string>>(this->data))
        {
            return "std::shared_ptr<std::string>";
        }
        else if (std::holds_alternative<std::shared_ptr<glm::vec3>>(this->data))
        {
            return "std::shared_ptr<glm::vec3>";
        }
        else if (std::holds_alternative<std::shared_ptr<glm::vec4>>(this->data))
        {
            return "std::shared_ptr<glm::vec4>";
        }

        return "ERROR: `AnyValue::get_datatype`: no datatype string defined for this datatype!";
    }

    std::string AnyValue::get_string() const
    {
        std::stringstream any_value_stringstream;
        any_value_stringstream.precision(6); // 6 decimals in floating point output.

        if (std::holds_alternative<bool>(this->data))
        {
            any_value_stringstream << std::boolalpha << std::get<bool>(this->data);
        }
        else if (std::holds_alternative<char>(this->data))
        {
            any_value_stringstream << std::get<char>(this->data);
        }
        else if (std::holds_alternative<float>(this->data))
        {
            any_value_stringstream << std::fixed << std::get<float>(this->data);
        }
        else if (std::holds_alternative<double>(this->data))
        {
            any_value_stringstream << std::fixed << std::get<double>(this->data);
        }
        else if (std::holds_alternative<int32_t>(this->data))
        {
            // in Linux `int` is 32 bits, `long` is 64 bits, `long long` is also 64 bits.
            // in Windows `int` is 32 bits, `long` is also 32 bits, `long long` is 64 bits.
            any_value_stringstream << std::get<int32_t>(this->data);
        }
        else if (std::holds_alternative<uint32_t>(this->data))
        {
            // in Linux `int` is 32 bits, `long` is 64 bits, `long long` is also 64 bits.
            // in Windows `int` is 32 bits, `long` is also 32 bits, `long long` is 64 bits.
            any_value_stringstream << std::get<uint32_t>(this->data);
        }
        else if (std::holds_alternative<bool*>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) std::get<bool*>(this->data) << std::dec;
        }
        else if (std::holds_alternative<char*>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) std::get<char*>(this->data) << std::dec;
        }
        else if (std::holds_alternative<float*>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) std::get<float*>(this->data) << std::dec;
        }
        else if (std::holds_alternative<double*>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) std::get<double*>(this->data) << std::dec;
        }
        else if (std::holds_alternative<int32_t*>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) std::get<int32_t*>(this->data) << std::dec;
        }
        else if (std::holds_alternative<uint32_t*>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) std::get<uint32_t*>(this->data) << std::dec;
        }
        else if (std::holds_alternative<yli::ontology::Entity*>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) std::get<yli::ontology::Entity*>(this->data) << std::dec;
        }
        else if (std::holds_alternative<yli::ontology::Movable*>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) std::get<yli::ontology::Movable*>(this->data) << std::dec;
        }
        else if (std::holds_alternative<const yli::ontology::Movable*>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) std::get<const yli::ontology::Movable*>(this->data) << std::dec;
        }
        else if (std::holds_alternative<yli::ontology::Universe*>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) std::get<yli::ontology::Universe*>(this->data) << std::dec;
        }
        else if (std::holds_alternative<yli::ontology::Ecosystem*>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) std::get<yli::ontology::Ecosystem*>(this->data) << std::dec;
        }
        else if (std::holds_alternative<yli::ontology::Scene*>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) std::get<yli::ontology::Scene*>(this->data) << std::dec;
        }
        else if (std::holds_alternative<yli::ontology::Shader*>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) std::get<yli::ontology::Shader*>(this->data) << std::dec;
        }
        else if (std::holds_alternative<yli::ontology::Material*>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) std::get<yli::ontology::Material*>(this->data) << std::dec;
        }
        else if (std::holds_alternative<yli::ontology::Species*>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) std::get<yli::ontology::Species*>(this->data) << std::dec;
        }
        else if (std::holds_alternative<yli::ontology::Object*>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) std::get<yli::ontology::Object*>(this->data) << std::dec;
        }
        else if (std::holds_alternative<yli::ontology::Symbiosis*>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) std::get<yli::ontology::Symbiosis*>(this->data) << std::dec;
        }
        else if (std::holds_alternative<yli::ontology::SymbiontMaterial*>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) std::get<yli::ontology::SymbiontMaterial*>(this->data) << std::dec;
        }
        else if (std::holds_alternative<yli::ontology::SymbiontSpecies*>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) std::get<yli::ontology::SymbiontSpecies*>(this->data) << std::dec;
        }
        else if (std::holds_alternative<yli::ontology::Holobiont*>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) std::get<yli::ontology::Holobiont*>(this->data) << std::dec;
        }
        else if (std::holds_alternative<yli::ontology::Biont*>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) std::get<yli::ontology::Biont*>(this->data) << std::dec;
        }
        else if (std::holds_alternative<yli::ontology::Font2D*>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) std::get<yli::ontology::Font2D*>(this->data) << std::dec;
        }
        else if (std::holds_alternative<yli::ontology::Text2D*>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) std::get<yli::ontology::Text2D*>(this->data) << std::dec;
        }
        else if (std::holds_alternative<yli::ontology::VectorFont*>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) std::get<yli::ontology::VectorFont*>(this->data) << std::dec;
        }
        else if (std::holds_alternative<yli::ontology::Glyph*>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) std::get<yli::ontology::Glyph*>(this->data) << std::dec;
        }
        else if (std::holds_alternative<yli::ontology::Text3D*>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) std::get<yli::ontology::Text3D*>(this->data) << std::dec;
        }
        else if (std::holds_alternative<yli::ontology::Console*>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) std::get<yli::ontology::Console*>(this->data) << std::dec;
        }
        else if (std::holds_alternative<yli::ontology::ComputeTask*>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) std::get<yli::ontology::ComputeTask*>(this->data) << std::dec;
        }
        else if (std::holds_alternative<std::shared_ptr<yli::data::AnyValue>>(this->data))
        {
            if (std::get<std::shared_ptr<yli::data::AnyValue>>(this->data) == nullptr)
            {
                any_value_stringstream << "nullptr";
            }
            else
            {
                any_value_stringstream << std::hex << std::get<std::shared_ptr<yli::data::AnyValue>>(this->data).get() << std::dec;
            }
        }
        else if (std::holds_alternative<std::shared_ptr<yli::data::AnyStruct>>(this->data))
        {
            if (std::get<std::shared_ptr<yli::data::AnyStruct>>(this->data) == nullptr)
            {
                any_value_stringstream << "nullptr";
            }
            else
            {
                any_value_stringstream << std::hex << std::get<std::shared_ptr<yli::data::AnyStruct>>(this->data).get() << std::dec;
            }
        }
        else if (std::holds_alternative<yli::data::SphericalCoordinatesStruct*>(this->data))
        {
            if (std::get<yli::data::SphericalCoordinatesStruct*>(this->data) == nullptr)
            {
                any_value_stringstream << "nullptr";
            }
            else
            {
                any_value_stringstream << std::fixed << "{ " << std::get<yli::data::SphericalCoordinatesStruct*>(this->data)->rho
                    << ", " << std::get<yli::data::SphericalCoordinatesStruct*>(this->data)->theta
                    << ", " << std::get<yli::data::SphericalCoordinatesStruct*>(this->data)->phi
                    << " }";
            }
        }
        else if (std::holds_alternative<std::string*>(this->data))
        {
            if (std::get<std::string*>(this->data) == nullptr)
            {
                any_value_stringstream << "nullptr";
            }
            else
            {
                any_value_stringstream << *(std::get<std::string*>(this->data));
            }
        }
        else if (std::holds_alternative<const std::string*>(this->data))
        {
            if (std::get<const std::string*>(this->data) == nullptr)
            {
                any_value_stringstream << "nullptr";
            }
            else
            {
                any_value_stringstream << *(std::get<const std::string*>(this->data));
            }
        }
        else if (std::holds_alternative<std::shared_ptr<std::vector<int8_t>>>(this->data))
        {
            if (std::get<std::shared_ptr<std::vector<int8_t>>>(this->data) == nullptr)
            {
                any_value_stringstream << "nullptr";
            }
            else
            {
                any_value_stringstream << "std::shared_ptr<std::vector<int8_t>>";
            }
        }
        else if (std::holds_alternative<std::shared_ptr<std::vector<uint8_t>>>(this->data))
        {
            if (std::get<std::shared_ptr<std::vector<uint8_t>>>(this->data) == nullptr)
            {
                any_value_stringstream << "nullptr";
            }
            else
            {
                any_value_stringstream << "std::shared_ptr<std::vector<uint8_t>>";
            }
        }
        else if (std::holds_alternative<std::shared_ptr<std::vector<int16_t>>>(this->data))
        {
            if (std::get<std::shared_ptr<std::vector<int16_t>>>(this->data) == nullptr)
            {
                any_value_stringstream << "nullptr";
            }
            else
            {
                any_value_stringstream << "std::shared_ptr<std::vector<int16_t>>";
            }
        }
        else if (std::holds_alternative<std::shared_ptr<std::vector<uint16_t>>>(this->data))
        {
            if (std::get<std::shared_ptr<std::vector<uint16_t>>>(this->data) == nullptr)
            {
                any_value_stringstream << "nullptr";
            }
            else
            {
                any_value_stringstream << "std::shared_ptr<std::vector<uint16_t>>";
            }
        }
        else if (std::holds_alternative<std::shared_ptr<std::vector<int32_t>>>(this->data))
        {
            if (std::get<std::shared_ptr<std::vector<int32_t>>>(this->data) == nullptr)
            {
                any_value_stringstream << "nullptr";
            }
            else
            {
                any_value_stringstream << "std::shared_ptr<std::vector<int32_t>>";
            }
        }
        else if (std::holds_alternative<std::shared_ptr<std::vector<uint32_t>>>(this->data))
        {
            if (std::get<std::shared_ptr<std::vector<uint32_t>>>(this->data) == nullptr)
            {
                any_value_stringstream << "nullptr";
            }
            else
            {
                any_value_stringstream << "std::shared_ptr<std::vector<uint32_t>>";
            }
        }
        else if (std::holds_alternative<std::shared_ptr<std::vector<float>>>(this->data))
        {
            if (std::get<std::shared_ptr<std::vector<float>>>(this->data) == nullptr)
            {
                any_value_stringstream << "nullptr";
            }
            else
            {
                any_value_stringstream << "std::shared_ptr<std::vector<float>>";
            }
        }
        else if (std::holds_alternative<std::shared_ptr<std::string>>(this->data))
        {
            if (std::get<std::shared_ptr<std::string>>(this->data) == nullptr)
            {
                any_value_stringstream << "nullptr";
            }
            else
            {
                any_value_stringstream << "std::shared_ptr<std::string>";
            }
        }
        else if (std::holds_alternative<std::shared_ptr<glm::vec3>>(this->data))
        {
            if (std::get<std::shared_ptr<glm::vec3>>(this->data) == nullptr)
            {
                any_value_stringstream << "nullptr";
            }
            else
            {
                any_value_stringstream << std::fixed << "{ " << std::get<std::shared_ptr<glm::vec3>>(this->data)->x
                    << ", " << std::get<std::shared_ptr<glm::vec3>>(this->data)->y
                    << ", " << std::get<std::shared_ptr<glm::vec3>>(this->data)->z
                    << " }";
            }
        }
        else if (std::holds_alternative<std::shared_ptr<glm::vec4>>(this->data))
        {
            if (std::get<std::shared_ptr<glm::vec4>>(this->data) == nullptr)
            {
                any_value_stringstream << "nullptr";
            }
            else
            {
                any_value_stringstream << std::fixed << "{ " << std::get<std::shared_ptr<glm::vec4>>(this->data)->x
                    << ", " << std::get<std::shared_ptr<glm::vec4>>(this->data)->y
                    << ", " << std::get<std::shared_ptr<glm::vec4>>(this->data)->z
                    << ", " << std::get<std::shared_ptr<glm::vec4>>(this->data)->w
                    << " }";
            }
        }
        else
        {
            return "ERROR: `AnyValue::get_string`: no string defined for this datatype!";
        }

        return any_value_stringstream.str();
    }

    yli::ontology::Entity* AnyValue::get_entity_pointer() const
    {
        if (std::holds_alternative<yli::ontology::Entity*>(this->data))
        {
            return std::get<yli::ontology::Entity*>(this->data);
        }
        else if (std::holds_alternative<yli::ontology::Universe*>(this->data))
        {
            return static_cast<yli::ontology::Entity*>(static_cast<void*>(std::get<yli::ontology::Universe*>(this->data)));
        }
        else if (std::holds_alternative<yli::ontology::Movable*>(this->data))
        {
            return static_cast<yli::ontology::Entity*>(static_cast<void*>(std::get<yli::ontology::Movable*>(this->data)));
        }
        else if (std::holds_alternative<const yli::ontology::Movable*>(this->data))
        {
            return nullptr; // Conversion which loses constness is not supported.
        }
        else if (std::holds_alternative<yli::ontology::Ecosystem*>(this->data))
        {
            return static_cast<yli::ontology::Entity*>(static_cast<void*>(std::get<yli::ontology::Ecosystem*>(this->data)));
        }
        else if (std::holds_alternative<yli::ontology::Scene*>(this->data))
        {
            return static_cast<yli::ontology::Entity*>(static_cast<void*>(std::get<yli::ontology::Scene*>(this->data)));
        }
        else if (std::holds_alternative<yli::ontology::Shader*>(this->data))
        {
            return static_cast<yli::ontology::Entity*>(static_cast<void*>(std::get<yli::ontology::Shader*>(this->data)));
        }
        else if (std::holds_alternative<yli::ontology::Material*>(this->data))
        {
            return static_cast<yli::ontology::Entity*>(static_cast<void*>(std::get<yli::ontology::Material*>(this->data)));
        }
        else if (std::holds_alternative<yli::ontology::Species*>(this->data))
        {
            return static_cast<yli::ontology::Entity*>(static_cast<void*>(std::get<yli::ontology::Species*>(this->data)));
        }
        else if (std::holds_alternative<yli::ontology::Object*>(this->data))
        {
            return static_cast<yli::ontology::Entity*>(static_cast<void*>(std::get<yli::ontology::Object*>(this->data)));
        }
        else if (std::holds_alternative<yli::ontology::Symbiosis*>(this->data))
        {
            return static_cast<yli::ontology::Entity*>(static_cast<void*>(std::get<yli::ontology::Symbiosis*>(this->data)));
        }
        else if (std::holds_alternative<yli::ontology::SymbiontMaterial*>(this->data))
        {
            return static_cast<yli::ontology::Entity*>(static_cast<void*>(std::get<yli::ontology::SymbiontMaterial*>(this->data)));
        }
        else if (std::holds_alternative<yli::ontology::SymbiontSpecies*>(this->data))
        {
            return static_cast<yli::ontology::Entity*>(static_cast<void*>(std::get<yli::ontology::SymbiontSpecies*>(this->data)));
        }
        else if (std::holds_alternative<yli::ontology::Holobiont*>(this->data))
        {
            return static_cast<yli::ontology::Entity*>(static_cast<void*>(std::get<yli::ontology::Holobiont*>(this->data)));
        }
        else if (std::holds_alternative<yli::ontology::Biont*>(this->data))
        {
            return static_cast<yli::ontology::Entity*>(static_cast<void*>(std::get<yli::ontology::Biont*>(this->data)));
        }
        else if (std::holds_alternative<yli::ontology::Font2D*>(this->data))
        {
            return static_cast<yli::ontology::Entity*>(static_cast<void*>(std::get<yli::ontology::Font2D*>(this->data)));
        }
        else if (std::holds_alternative<yli::ontology::Text2D*>(this->data))
        {
            return static_cast<yli::ontology::Entity*>(static_cast<void*>(std::get<yli::ontology::Text2D*>(this->data)));
        }
        else if (std::holds_alternative<yli::ontology::VectorFont*>(this->data))
        {
            return static_cast<yli::ontology::Entity*>(static_cast<void*>(std::get<yli::ontology::VectorFont*>(this->data)));
        }
        else if (std::holds_alternative<yli::ontology::Glyph*>(this->data))
        {
            return static_cast<yli::ontology::Entity*>(static_cast<void*>(std::get<yli::ontology::Glyph*>(this->data)));
        }
        else if (std::holds_alternative<yli::ontology::Text3D*>(this->data))
        {
            return static_cast<yli::ontology::Entity*>(static_cast<void*>(std::get<yli::ontology::Text3D*>(this->data)));
        }
        else if (std::holds_alternative<yli::ontology::Console*>(this->data))
        {
            return static_cast<yli::ontology::Entity*>(static_cast<void*>(std::get<yli::ontology::Console*>(this->data)));
        }
        else if (std::holds_alternative<yli::ontology::ComputeTask*>(this->data))
        {
            return static_cast<yli::ontology::Entity*>(static_cast<void*>(std::get<yli::ontology::ComputeTask*>(this->data)));
        }

        return nullptr;
    }

    bool AnyValue::set_new_value(const std::string& value_string)
    {
        std::stringstream value_stringstream;
        void* void_pointer = nullptr;

        if (std::holds_alternative<bool>(this->data))
        {
            if (value_string == "true") // Ylikuutio is case sensitive!
            {
                this->data = true;
                return true;
            }
            else if (value_string == "false") // Ylikuutio is case sensitive!
            {
                this->data = false;
                return true;
            }
            return false;
        }
        else if (std::holds_alternative<char>(this->data))
        {
            if (value_string.size() == 1)
            {
                this->data = value_string[0];
                return true;
            }
            return false;
        }
        else if (std::holds_alternative<float>(this->data))
        {
            if (!yli::string::check_if_float_string(value_string))
            {
                return false;
            }

            float float_value;
            value_stringstream << value_string;
            value_stringstream >> float_value;
            this->data = float_value;
            return true;
        }
        else if (std::holds_alternative<double>(this->data))
        {
            if (!yli::string::check_if_double_string(value_string))
            {
                return false;
            }

            double double_value;
            value_stringstream << value_string;
            value_stringstream >> double_value;
            this->data = double_value;
            return true;
        }
        else if (std::holds_alternative<int32_t>(this->data))
        {
            if (!yli::string::check_if_signed_integer_string(value_string))
            {
                return false;
            }

            int32_t int32_t_value;
            value_stringstream << value_string;
            value_stringstream >> int32_t_value;
            this->data = int32_t_value;
            return true;
        }
        else if (std::holds_alternative<uint32_t>(this->data))
        {
            if (!yli::string::check_if_unsigned_integer_string(value_string))
            {
                return false;
            }

            uint32_t uint32_t_value;
            value_stringstream << value_string;
            value_stringstream >> uint32_t_value;
            this->data = uint32_t_value;
            return true;
        }
        else if (std::holds_alternative<bool*>(this->data))
        {
            if (!yli::string::check_if_unsigned_integer_string(value_string))
            {
                return false;
            }

            value_stringstream << value_string;
            value_stringstream >> void_pointer;
            this->data = static_cast<bool*>(void_pointer);
            return true;
        }
        else if (std::holds_alternative<char*>(this->data))
        {
            if (!yli::string::check_if_unsigned_integer_string(value_string))
            {
                return false;
            }

            value_stringstream << value_string;
            value_stringstream >> void_pointer;
            this->data = static_cast<char*>(void_pointer);
            return true;
        }
        else if (std::holds_alternative<float*>(this->data))
        {
            if (!yli::string::check_if_unsigned_integer_string(value_string))
            {
                return false;
            }

            value_stringstream << value_string;
            value_stringstream >> void_pointer;
            this->data = static_cast<float*>(void_pointer);
            return true;
        }
        else if (std::holds_alternative<double*>(this->data))
        {
            if (!yli::string::check_if_unsigned_integer_string(value_string))
            {
                return false;
            }

            value_stringstream << value_string;
            value_stringstream >> void_pointer;
            this->data = static_cast<double*>(void_pointer);
            return true;
        }
        else if (std::holds_alternative<int32_t*>(this->data))
        {
            if (!yli::string::check_if_unsigned_integer_string(value_string))
            {
                return false;
            }

            value_stringstream << value_string;
            value_stringstream >> void_pointer;
            this->data = static_cast<int32_t*>(void_pointer);
            return true;
        }
        else if (std::holds_alternative<uint32_t*>(this->data))
        {
            if (!yli::string::check_if_unsigned_integer_string(value_string))
            {
                return false;
            }

            value_stringstream << value_string;
            value_stringstream >> void_pointer;
            this->data = static_cast<uint32_t*>(void_pointer);
            return true;
        }
        else if (std::holds_alternative<yli::ontology::Entity*>(this->data))
        {
            if (!yli::string::check_if_unsigned_integer_string(value_string))
            {
                return false;
            }

            value_stringstream << value_string;
            value_stringstream >> void_pointer;
            this->data = static_cast<yli::ontology::Entity*>(void_pointer);
            return true;
        }
        else if (std::holds_alternative<yli::ontology::Movable*>(this->data))
        {
            if (!yli::string::check_if_unsigned_integer_string(value_string))
            {
                return false;
            }

            value_stringstream << value_string;
            value_stringstream >> void_pointer;
            this->data = static_cast<yli::ontology::Movable*>(void_pointer);
            return true;
        }
        else if (std::holds_alternative<const yli::ontology::Movable*>(this->data))
        {
            if (!yli::string::check_if_unsigned_integer_string(value_string))
            {
                return false;
            }

            value_stringstream << value_string;
            value_stringstream >> void_pointer;
            this->data = static_cast<const yli::ontology::Movable*>(void_pointer);
            return true;
        }
        else if (std::holds_alternative<yli::ontology::Universe*>(this->data))
        {
            if (!yli::string::check_if_unsigned_integer_string(value_string))
            {
                return false;
            }

            value_stringstream << value_string;
            value_stringstream >> void_pointer;
            this->data = static_cast<yli::ontology::Universe*>(void_pointer);
            return true;
        }
        else if (std::holds_alternative<yli::ontology::Ecosystem*>(this->data))
        {
            if (!yli::string::check_if_unsigned_integer_string(value_string))
            {
                return false;
            }

            value_stringstream << value_string;
            value_stringstream >> void_pointer;
            this->data = static_cast<yli::ontology::Ecosystem*>(void_pointer);
            return true;
        }
        else if (std::holds_alternative<yli::ontology::Scene*>(this->data))
        {
            if (!yli::string::check_if_unsigned_integer_string(value_string))
            {
                return false;
            }

            value_stringstream << value_string;
            value_stringstream >> void_pointer;
            this->data = static_cast<yli::ontology::Scene*>(void_pointer);
            return true;
        }
        else if (std::holds_alternative<yli::ontology::Shader*>(this->data))
        {
            if (!yli::string::check_if_unsigned_integer_string(value_string))
            {
                return false;
            }

            value_stringstream << value_string;
            value_stringstream >> void_pointer;
            this->data = static_cast<yli::ontology::Shader*>(void_pointer);
            return true;
        }
        else if (std::holds_alternative<yli::ontology::Material*>(this->data))
        {
            if (!yli::string::check_if_unsigned_integer_string(value_string))
            {
                return false;
            }

            value_stringstream << value_string;
            value_stringstream >> void_pointer;
            this->data = static_cast<yli::ontology::Material*>(void_pointer);
            return true;
        }
        else if (std::holds_alternative<yli::ontology::Species*>(this->data))
        {
            if (!yli::string::check_if_unsigned_integer_string(value_string))
            {
                return false;
            }

            value_stringstream << value_string;
            value_stringstream >> void_pointer;
            this->data = static_cast<yli::ontology::Species*>(void_pointer);
            return true;
        }
        else if (std::holds_alternative<yli::ontology::Object*>(this->data))
        {
            if (!yli::string::check_if_unsigned_integer_string(value_string))
            {
                return false;
            }

            value_stringstream << value_string;
            value_stringstream >> void_pointer;
            this->data = static_cast<yli::ontology::Object*>(void_pointer);
            return true;
        }
        else if (std::holds_alternative<yli::ontology::Symbiosis*>(this->data))
        {
            if (!yli::string::check_if_unsigned_integer_string(value_string))
            {
                return false;
            }

            value_stringstream << value_string;
            value_stringstream >> void_pointer;
            this->data = static_cast<yli::ontology::Symbiosis*>(void_pointer);
            return true;
        }
        else if (std::holds_alternative<yli::ontology::SymbiontMaterial*>(this->data))
        {
            if (!yli::string::check_if_unsigned_integer_string(value_string))
            {
                return false;
            }

            value_stringstream << value_string;
            value_stringstream >> void_pointer;
            this->data = static_cast<yli::ontology::SymbiontMaterial*>(void_pointer);
            return true;
        }
        else if (std::holds_alternative<yli::ontology::SymbiontSpecies*>(this->data))
        {
            if (!yli::string::check_if_unsigned_integer_string(value_string))
            {
                return false;
            }

            value_stringstream << value_string;
            value_stringstream >> void_pointer;
            this->data = static_cast<yli::ontology::SymbiontSpecies*>(void_pointer);
            return true;
        }
        else if (std::holds_alternative<yli::ontology::Holobiont*>(this->data))
        {
            if (!yli::string::check_if_unsigned_integer_string(value_string))
            {
                return false;
            }

            value_stringstream << value_string;
            value_stringstream >> void_pointer;
            this->data = static_cast<yli::ontology::Holobiont*>(void_pointer);
            return true;
        }
        else if (std::holds_alternative<yli::ontology::Biont*>(this->data))
        {
            if (!yli::string::check_if_unsigned_integer_string(value_string))
            {
                return false;
            }

            value_stringstream << value_string;
            value_stringstream >> void_pointer;
            this->data = static_cast<yli::ontology::Biont*>(void_pointer);
            return true;
        }
        else if (std::holds_alternative<yli::ontology::Font2D*>(this->data))
        {
            if (!yli::string::check_if_unsigned_integer_string(value_string))
            {
                return false;
            }

            value_stringstream << value_string;
            value_stringstream >> void_pointer;
            this->data = static_cast<yli::ontology::Font2D*>(void_pointer);
            return true;
        }
        else if (std::holds_alternative<yli::ontology::Text2D*>(this->data))
        {
            if (!yli::string::check_if_unsigned_integer_string(value_string))
            {
                return false;
            }

            value_stringstream << value_string;
            value_stringstream >> void_pointer;
            this->data = static_cast<yli::ontology::Text2D*>(void_pointer);
            return true;
        }
        else if (std::holds_alternative<yli::ontology::VectorFont*>(this->data))
        {
            if (!yli::string::check_if_unsigned_integer_string(value_string))
            {
                return false;
            }

            value_stringstream << value_string;
            value_stringstream >> void_pointer;
            this->data = static_cast<yli::ontology::VectorFont*>(void_pointer);
            return true;
        }
        else if (std::holds_alternative<yli::ontology::Glyph*>(this->data))
        {
            if (!yli::string::check_if_unsigned_integer_string(value_string))
            {
                return false;
            }

            value_stringstream << value_string;
            value_stringstream >> void_pointer;
            this->data = static_cast<yli::ontology::Glyph*>(void_pointer);
            return true;
        }
        else if (std::holds_alternative<yli::ontology::Text3D*>(this->data))
        {
            if (!yli::string::check_if_unsigned_integer_string(value_string))
            {
                return false;
            }

            value_stringstream << value_string;
            value_stringstream >> void_pointer;
            this->data = static_cast<yli::ontology::Text3D*>(void_pointer);
            return true;
        }
        else if (std::holds_alternative<yli::ontology::Console*>(this->data))
        {
            if (!yli::string::check_if_unsigned_integer_string(value_string))
            {
                return false;
            }

            value_stringstream << value_string;
            value_stringstream >> void_pointer;
            this->data = static_cast<yli::ontology::Console*>(void_pointer);
            return true;
        }
        else if (std::holds_alternative<yli::ontology::ComputeTask*>(this->data))
        {
            if (!yli::string::check_if_unsigned_integer_string(value_string))
            {
                return false;
            }

            value_stringstream << value_string;
            value_stringstream >> void_pointer;
            this->data = static_cast<yli::ontology::ComputeTask*>(void_pointer);
            return true;
        }
        else if (std::holds_alternative<std::shared_ptr<yli::data::AnyValue>>(this->data))
        {
            if (!yli::string::check_if_unsigned_integer_string(value_string))
            {
                return false;
            }

            std::shared_ptr<yli::data::AnyValue> any_value_shared_ptr =
                std::make_shared<yli::data::AnyValue>(this);
            any_value_shared_ptr->set_new_value(value_string);
            this->data = any_value_shared_ptr;
            return true;
        }
        else if (std::holds_alternative<std::shared_ptr<yli::data::AnyStruct>>(this->data))
        {
            if (!yli::string::check_if_unsigned_integer_string(value_string))
            {
                return false;
            }

            std::shared_ptr<yli::data::AnyStruct> any_struct_shared_ptr =
                std::make_shared<yli::data::AnyStruct>();
            this->data = any_struct_shared_ptr;
            return true;
        }
        else if (std::holds_alternative<yli::data::SphericalCoordinatesStruct*>(this->data))
        {
            if (!yli::string::check_if_unsigned_integer_string(value_string))
            {
                return false;
            }

            value_stringstream << value_string;
            value_stringstream >> void_pointer;
            this->data = static_cast<yli::data::SphericalCoordinatesStruct*>(void_pointer);
            return true;
        }
        else if (std::holds_alternative<std::string*>(this->data))
        {
            if (!yli::string::check_if_unsigned_integer_string(value_string))
            {
                return false;
            }

            value_stringstream << value_string;
            value_stringstream >> void_pointer;
            this->data = static_cast<std::string*>(void_pointer);
            return true;
        }
        else if (std::holds_alternative<const std::string*>(this->data))
        {
            if (!yli::string::check_if_unsigned_integer_string(value_string))
            {
                return false;
            }

            value_stringstream << value_string;
            value_stringstream >> void_pointer;
            this->data = static_cast<const std::string*>(void_pointer);
            return true;
        }
        else if (std::holds_alternative<std::shared_ptr<glm::vec3>>(this->data))
        {
            if (!yli::string::check_if_unsigned_integer_string(value_string))
            {
                return false;
            }

            std::shared_ptr<glm::vec3> glm_vec3_shared_ptr =
                std::make_shared<glm::vec3>();
            this->data = glm_vec3_shared_ptr;
            return true;
        }
        else if (std::holds_alternative<std::shared_ptr<glm::vec4>>(this->data))
        {
            if (!yli::string::check_if_unsigned_integer_string(value_string))
            {
                return false;
            }

            std::shared_ptr<glm::vec4> glm_vec4_shared_ptr =
                std::make_shared<glm::vec4>();
            this->data = glm_vec4_shared_ptr;
            return true;
        }

        return false;
    }

    AnyValue::AnyValue(const yli::data::AnyValue& original)
    {
        // copy constructor.
        this->data = original.data;
    }

    AnyValue::AnyValue(const std::optional<yli::data::AnyValue> original)
    {
        // constructor for optional `AnyValue`.

        if (original)
        {
            this->data = (*original).data;
        }
    }

    AnyValue::AnyValue()
    {
        // Default constructor. Do not use.
    }

    AnyValue::AnyValue(const std::string& type, const std::string& value_string)
        : data(yli::data::get_variant<
                std::monostate,
                bool,
                char,
                float,
                double,
                int32_t,
                uint32_t,
                bool*,
                char*,
                float*,
                double*,
                int32_t*,
                uint32_t*,
                yli::ontology::Entity*,
                yli::ontology::Movable*,
                const yli::ontology::Movable*,
                yli::ontology::Universe*,
                yli::ontology::Ecosystem*,
                yli::ontology::Scene*,
                yli::ontology::Shader*,
                yli::ontology::Material*,
                yli::ontology::Species*,
                yli::ontology::Object*,
                yli::ontology::Symbiosis*,
                yli::ontology::SymbiontMaterial*,
                yli::ontology::SymbiontSpecies*,
                yli::ontology::Holobiont*,
                yli::ontology::Biont*,
                yli::ontology::Font2D*,
                yli::ontology::Text2D*,
                yli::ontology::VectorFont*,
                yli::ontology::Glyph*,
                yli::ontology::Text3D*,
                yli::ontology::Console*,
                yli::ontology::ComputeTask*,
                std::shared_ptr<yli::data::AnyValue>,
                std::shared_ptr<yli::data::AnyStruct>,
                std::shared_ptr<std::vector<int8_t>>,
                std::shared_ptr<std::vector<uint8_t>>,
                std::shared_ptr<std::vector<int16_t>>,
                std::shared_ptr<std::vector<uint16_t>>,
                std::shared_ptr<std::vector<int32_t>>,
                std::shared_ptr<std::vector<uint32_t>>,
                std::shared_ptr<std::vector<float>>,
                std::shared_ptr<std::string>,
                std::shared_ptr<glm::vec3>,
                std::shared_ptr<glm::vec4>,
                yli::data::SphericalCoordinatesStruct*,
                std::string*,
                const std::string*>(type, value_string))
    {
        // constructor.
    }

    AnyValue::AnyValue(const bool bool_value)
        : data(bool_value)
    {
        // constructor.
    }

    AnyValue::AnyValue(const char char_value)
        : data(char_value)
    {
        // constructor.
    }

    AnyValue::AnyValue(const float float_value)
        : data(float_value)
    {
        // constructor.
    }

    AnyValue::AnyValue(const double double_value)
        : data(double_value)
    {
        // constructor.
    }

    AnyValue::AnyValue(const int32_t int32_t_value)
        : data(int32_t_value)
    {
        // constructor.
    }

    AnyValue::AnyValue(const uint32_t uint32_t_value)
        : data(uint32_t_value)
    {
        // constructor.
    }

    AnyValue::AnyValue(bool* const bool_pointer)
        : data(bool_pointer)
    {
        // constructor.
    }

    AnyValue::AnyValue(char* const char_pointer)
        : data(char_pointer)
    {
        // constructor.
    }

    AnyValue::AnyValue(float* const float_pointer)
        : data(float_pointer)
    {
        // constructor.
    }

    AnyValue::AnyValue(double* const double_pointer)
        : data(double_pointer)
    {
        // constructor.
    }

    AnyValue::AnyValue(int32_t* const int32_t_pointer)
        : data(int32_t_pointer)
    {
        // constructor.
    }

    AnyValue::AnyValue(uint32_t* const uint32_t_pointer)
        : data(uint32_t_pointer)
    {
        // constructor.
    }

    AnyValue::AnyValue(yli::ontology::Entity* const entity_pointer)
        : data(entity_pointer)
    {
        // constructor.
    }

    AnyValue::AnyValue(yli::ontology::Movable* const movable_pointer)
        : data(movable_pointer)
    {
        // constructor.
    }

    AnyValue::AnyValue(const yli::ontology::Movable* const const_movable_pointer)
        : data(const_movable_pointer)
    {
        // constructor.
    }

    AnyValue::AnyValue(yli::ontology::Universe* const universe_pointer)
        : data(universe_pointer)
    {
        // constructor.
    }

    AnyValue::AnyValue(yli::ontology::Ecosystem* const ecosystem_pointer)
        : data(ecosystem_pointer)
    {
        // constructor.
    }

    AnyValue::AnyValue(yli::ontology::Scene* const scene_pointer)
        : data(scene_pointer)
    {
        // constructor.
    }

    AnyValue::AnyValue(yli::ontology::Shader* const shader_pointer)
        : data(shader_pointer)
    {
        // constructor.
    }

    AnyValue::AnyValue(yli::ontology::Material* const material_pointer)
        : data(material_pointer)
    {
        // constructor.
    }

    AnyValue::AnyValue(yli::ontology::Species* const species_pointer)
        : data(species_pointer)
    {
        // constructor.
    }

    AnyValue::AnyValue(yli::ontology::Object* const object_pointer)
        : data(object_pointer)
    {
        // constructor.
    }

    AnyValue::AnyValue(yli::ontology::Symbiosis* const symbiosis_pointer)
        : data(symbiosis_pointer)
    {
        // constructor.
    }

    AnyValue::AnyValue(yli::ontology::SymbiontMaterial* const symbiont_material_pointer)
        : data(symbiont_material_pointer)
    {
        // constructor.
    }

    AnyValue::AnyValue(yli::ontology::SymbiontSpecies* const symbiont_species_pointer)
        : data(symbiont_species_pointer)
    {
        // constructor.
    }

    AnyValue::AnyValue(yli::ontology::Holobiont* const holobiont_pointer)
        : data(holobiont_pointer)
    {
        // constructor.
    }

    AnyValue::AnyValue(yli::ontology::Biont* const biont_pointer)
        : data(biont_pointer)
    {
        // constructor.
    }

    AnyValue::AnyValue(yli::ontology::Font2D* const font_2d_pointer)
        : data(font_2d_pointer)
    {
        // constructor.
    }

    AnyValue::AnyValue(yli::ontology::Text2D* const text_2d_pointer)
        : data(text_2d_pointer)
    {
        // constructor.
    }

    AnyValue::AnyValue(yli::ontology::VectorFont* const vector_font_pointer)
        : data(vector_font_pointer)
    {
        // constructor.
    }

    AnyValue::AnyValue(yli::ontology::Glyph* const glyph_pointer)
        : data(glyph_pointer)
    {
        // constructor.
    }

    AnyValue::AnyValue(yli::ontology::Text3D* const text_3d_pointer)
        : data(text_3d_pointer)
    {
        // constructor.
    }

    AnyValue::AnyValue(yli::ontology::Console* const console_pointer)
        : data(console_pointer)
    {
        // constructor.
    }

    AnyValue::AnyValue(yli::ontology::ComputeTask* const compute_task_pointer)
        : data(compute_task_pointer)
    {
        // constructor.
    }

    AnyValue::AnyValue(std::shared_ptr<yli::data::AnyValue> any_value_shared_ptr)
        : data(any_value_shared_ptr)
    {
        // constructor.
    }

    AnyValue::AnyValue(std::shared_ptr<yli::data::AnyStruct> any_struct_shared_ptr)
        : data(any_struct_shared_ptr)
    {
        // constructor.
    }

    AnyValue::AnyValue(yli::data::SphericalCoordinatesStruct* const spherical_coordinates_struct_pointer)
        : data(spherical_coordinates_struct_pointer)
    {
        // constructor.
    }

    AnyValue::AnyValue(std::string* const std_string_pointer)
        : data(std_string_pointer)
    {
        // constructor.
    }

    AnyValue::AnyValue(const std::string* const const_std_string_pointer)
        : data(const_std_string_pointer)
    {
        // constructor.
    }

    AnyValue::AnyValue(std::shared_ptr<std::vector<int8_t>> std_vector_int8_t_shared_ptr)
        : data(std_vector_int8_t_shared_ptr)
    {
        // constructor.
    }

    AnyValue::AnyValue(std::shared_ptr<std::vector<uint8_t>> std_vector_uint8_t_shared_ptr)
        : data(std_vector_uint8_t_shared_ptr)
    {
        // constructor.
    }

    AnyValue::AnyValue(std::shared_ptr<std::vector<int16_t>> std_vector_int16_t_shared_ptr)
        : data(std_vector_int16_t_shared_ptr)
    {
        // constructor.
    }

    AnyValue::AnyValue(std::shared_ptr<std::vector<uint16_t>> std_vector_uint16_t_shared_ptr)
        : data(std_vector_uint16_t_shared_ptr)
    {
        // constructor.
    }

    AnyValue::AnyValue(std::shared_ptr<std::vector<int32_t>> std_vector_int32_t_shared_ptr)
        : data(std_vector_int32_t_shared_ptr)
    {
        // constructor.
    }

    AnyValue::AnyValue(std::shared_ptr<std::vector<uint32_t>> std_vector_uint32_t_shared_ptr)
        : data(std_vector_uint32_t_shared_ptr)
    {
        // constructor.
    }

    AnyValue::AnyValue(std::shared_ptr<std::vector<float>> std_vector_float_shared_ptr)
        : data(std_vector_float_shared_ptr)
    {
        // constructor.
    }

    AnyValue::AnyValue(std::shared_ptr<std::string> std_string_shared_ptr)
        : data(std_string_shared_ptr)
    {
        // constructor.
    }

    AnyValue::AnyValue(std::shared_ptr<glm::vec3> glm_vec3_shared_ptr)
        : data(glm_vec3_shared_ptr)
    {
        // constructor.
    }

    AnyValue::AnyValue(std::shared_ptr<glm::vec4> glm_vec4_shared_ptr)
        : data(glm_vec4_shared_ptr)
    {
        // constructor.
    }
}
