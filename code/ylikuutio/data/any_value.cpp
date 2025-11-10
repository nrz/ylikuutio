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

#ifndef __STDC_FORMAT_MACROS
// For MinGW.
#define __STDC_FORMAT_MACROS
#endif

#include "any_value.hpp"
#include "variant_templates.hpp"
#include "code/ylikuutio/ontology/entity.hpp"
#include "code/ylikuutio/ontology/movable.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/ecosystem.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/pipeline.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/symbiosis.hpp"
#include "code/ylikuutio/ontology/holobiont.hpp"
#include "code/ylikuutio/ontology/font_2d.hpp"
#include "code/ylikuutio/ontology/text_2d.hpp"
#include "code/ylikuutio/ontology/vector_font.hpp"
#include "code/ylikuutio/ontology/text_3d.hpp"
#include "code/ylikuutio/ontology/console.hpp"
#include "code/ylikuutio/ontology/compute_task.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <functional> // std::reference_wrapper
#include <ios>        // std::boolalpha, std::dec, std::fixed, std::hex
#include <optional>   // std::optional
#include <sstream>    // std::stringstream
#include <string>     // std::string
#include <stdexcept>  // std::runtime_error
#include <stdint.h>   // uint32_t etc.
#include <variant>    // std::holds_alternative, std::monostate
#include <vector>     // std::vector

namespace yli::data
{
    bool AnyValue::operator==(const AnyValue& rhs) const noexcept
    {
        if (this->get_datatype() != rhs.get_datatype())
        {
            return false;
        }

        // Fundamental types.
        if (std::holds_alternative<bool>(this->data) && std::holds_alternative<bool>(rhs.data))
        {
            return std::get<bool>(this->data) == std::get<bool>(rhs.data);
        }
        else if (std::holds_alternative<char>(this->data) && std::holds_alternative<char>(rhs.data))
        {
            return std::get<char>(this->data) == std::get<char>(rhs.data);
        }
        else if (std::holds_alternative<float>(this->data) && std::holds_alternative<float>(rhs.data))
        {
            return std::get<float>(this->data) == std::get<float>(rhs.data);
        }
        else if (std::holds_alternative<double>(this->data) && std::holds_alternative<double>(rhs.data))
        {
            return std::get<double>(this->data) == std::get<double>(rhs.data);
        }
        else if (std::holds_alternative<int32_t>(this->data) && std::holds_alternative<int32_t>(rhs.data))
        {
            return std::get<int32_t>(this->data) == std::get<int32_t>(rhs.data);
        }
        else if (std::holds_alternative<uint32_t>(this->data) && std::holds_alternative<uint32_t>(rhs.data))
        {
            return std::get<uint32_t>(this->data) == std::get<uint32_t>(rhs.data);
        }
        // Strings.
        else if (std::holds_alternative<std::reference_wrapper<std::string>>(this->data) &&
                std::holds_alternative<std::reference_wrapper<std::string>>(rhs.data))
        {
            return std::get<std::reference_wrapper<std::string>>(this->data).get() ==
                std::get<std::reference_wrapper<std::string>>(rhs.data).get();
        }
        else if (std::holds_alternative<std::reference_wrapper<const std::string>>(this->data) &&
                std::holds_alternative<std::reference_wrapper<const std::string>>(rhs.data))
        {
            return std::get<std::reference_wrapper<const std::string>>(this->data).get() ==
                std::get<std::reference_wrapper<const std::string>>(rhs.data).get();
        }
        // Variable-size vectors.
        else if (std::holds_alternative<std::reference_wrapper<std::vector<int8_t>>>(this->data) &&
                std::holds_alternative<std::reference_wrapper<std::vector<int8_t>>>(rhs.data))
        {
            return std::get<std::reference_wrapper<std::vector<int8_t>>>(this->data).get() ==
                std::get<std::reference_wrapper<std::vector<int8_t>>>(rhs.data).get();
        }
        else if (std::holds_alternative<std::reference_wrapper<std::vector<uint8_t>>>(this->data) &&
                std::holds_alternative<std::reference_wrapper<std::vector<uint8_t>>>(rhs.data))
        {
            return std::get<std::reference_wrapper<std::vector<uint8_t>>>(this->data).get() ==
                std::get<std::reference_wrapper<std::vector<uint8_t>>>(rhs.data).get();
        }
        else if (std::holds_alternative<std::reference_wrapper<std::vector<int16_t>>>(this->data) &&
                std::holds_alternative<std::reference_wrapper<std::vector<int16_t>>>(rhs.data))
        {
            return std::get<std::reference_wrapper<std::vector<int16_t>>>(this->data).get() ==
                std::get<std::reference_wrapper<std::vector<int16_t>>>(rhs.data).get();
        }
        else if (std::holds_alternative<std::reference_wrapper<std::vector<uint16_t>>>(this->data) &&
                std::holds_alternative<std::reference_wrapper<std::vector<uint16_t>>>(rhs.data))
        {
            return std::get<std::reference_wrapper<std::vector<uint16_t>>>(this->data).get() ==
                std::get<std::reference_wrapper<std::vector<uint16_t>>>(rhs.data).get();
        }
        else if (std::holds_alternative<std::reference_wrapper<std::vector<int32_t>>>(this->data) &&
                std::holds_alternative<std::reference_wrapper<std::vector<int32_t>>>(rhs.data))
        {
            return std::get<std::reference_wrapper<std::vector<int32_t>>>(this->data).get() ==
                std::get<std::reference_wrapper<std::vector<int32_t>>>(rhs.data).get();
        }
        else if (std::holds_alternative<std::reference_wrapper<std::vector<uint32_t>>>(this->data) &&
                std::holds_alternative<std::reference_wrapper<std::vector<uint32_t>>>(rhs.data))
        {
            return std::get<std::reference_wrapper<std::vector<uint32_t>>>(this->data).get() ==
                std::get<std::reference_wrapper<std::vector<uint32_t>>>(rhs.data).get();
        }
        else if (std::holds_alternative<std::reference_wrapper<std::vector<float>>>(this->data) &&
                std::holds_alternative<std::reference_wrapper<std::vector<float>>>(rhs.data))
        {
            return std::get<std::reference_wrapper<std::vector<float>>>(this->data).get() ==
                std::get<std::reference_wrapper<std::vector<float>>>(rhs.data).get();
        }
        // Fixed-size vectors.
        else if (std::holds_alternative<std::reference_wrapper<glm::vec3>>(this->data) &&
                std::holds_alternative<std::reference_wrapper<glm::vec3>>(rhs.data))
        {
            return std::get<std::reference_wrapper<glm::vec3>>(this->data).get() ==
                std::get<std::reference_wrapper<glm::vec3>>(rhs.data).get();
        }
        else if (std::holds_alternative<std::reference_wrapper<const glm::vec3>>(this->data) &&
                std::holds_alternative<std::reference_wrapper<const glm::vec3>>(rhs.data))
        {
            return std::get<std::reference_wrapper<const glm::vec3>>(this->data).get() ==
                std::get<std::reference_wrapper<const glm::vec3>>(rhs.data).get();
        }
        else if (std::holds_alternative<std::reference_wrapper<glm::vec4>>(this->data) &&
                std::holds_alternative<std::reference_wrapper<glm::vec4>>(rhs.data))
        {
            return std::get<std::reference_wrapper<glm::vec4>>(this->data).get() ==
                std::get<std::reference_wrapper<glm::vec4>>(rhs.data).get();
        }
        else if (std::holds_alternative<std::reference_wrapper<const glm::vec4>>(this->data) &&
                std::holds_alternative<std::reference_wrapper<const glm::vec4>>(rhs.data))
        {
            return std::get<std::reference_wrapper<const glm::vec4>>(this->data).get() ==
                std::get<std::reference_wrapper<const glm::vec4>>(rhs.data).get();
        }
        // Ontology.
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Entity>>(this->data) &&
                std::holds_alternative<std::reference_wrapper<yli::ontology::Entity>>(rhs.data))
        {
            return std::get<std::reference_wrapper<yli::ontology::Entity>>(this->data).get() ==
                std::get<std::reference_wrapper<yli::ontology::Entity>>(rhs.data).get();
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Movable>>(this->data) &&
                std::holds_alternative<std::reference_wrapper<yli::ontology::Movable>>(rhs.data))
        {
            return std::get<std::reference_wrapper<yli::ontology::Movable>>(this->data).get() ==
                std::get<std::reference_wrapper<yli::ontology::Movable>>(rhs.data).get();
        }
        else if (std::holds_alternative<std::reference_wrapper<const yli::ontology::Movable>>(this->data) &&
                std::holds_alternative<std::reference_wrapper<const yli::ontology::Movable>>(rhs.data))
        {
            return std::get<std::reference_wrapper<const yli::ontology::Movable>>(this->data).get() ==
                std::get<std::reference_wrapper<const yli::ontology::Movable>>(rhs.data).get();
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Universe>>(this->data) &&
                std::holds_alternative<std::reference_wrapper<yli::ontology::Universe>>(rhs.data))
        {
            return std::get<std::reference_wrapper<yli::ontology::Universe>>(this->data).get() ==
                std::get<std::reference_wrapper<yli::ontology::Universe>>(rhs.data).get();
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Ecosystem>>(this->data) &&
                std::holds_alternative<std::reference_wrapper<yli::ontology::Ecosystem>>(rhs.data))
        {
            return std::get<std::reference_wrapper<yli::ontology::Ecosystem>>(this->data).get() ==
                std::get<std::reference_wrapper<yli::ontology::Ecosystem>>(rhs.data).get();
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Scene>>(this->data) &&
                std::holds_alternative<std::reference_wrapper<yli::ontology::Scene>>(rhs.data))
        {
            return std::get<std::reference_wrapper<yli::ontology::Scene>>(this->data).get() ==
                std::get<std::reference_wrapper<yli::ontology::Scene>>(rhs.data).get();
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Pipeline>>(this->data) &&
                std::holds_alternative<std::reference_wrapper<yli::ontology::Pipeline>>(rhs.data))
        {
            return std::get<std::reference_wrapper<yli::ontology::Pipeline>>(this->data).get() ==
                std::get<std::reference_wrapper<yli::ontology::Pipeline>>(rhs.data).get();
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Material>>(this->data) &&
                std::holds_alternative<std::reference_wrapper<yli::ontology::Material>>(rhs.data))
        {
            return std::get<std::reference_wrapper<yli::ontology::Material>>(this->data).get() ==
                std::get<std::reference_wrapper<yli::ontology::Material>>(rhs.data).get();
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Species>>(this->data) &&
                std::holds_alternative<std::reference_wrapper<yli::ontology::Species>>(rhs.data))
        {
            return std::get<std::reference_wrapper<yli::ontology::Species>>(this->data).get() ==
                std::get<std::reference_wrapper<yli::ontology::Species>>(rhs.data).get();
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Object>>(this->data) &&
                std::holds_alternative<std::reference_wrapper<yli::ontology::Object>>(rhs.data))
        {
            return std::get<std::reference_wrapper<yli::ontology::Object>>(this->data).get() ==
                std::get<std::reference_wrapper<yli::ontology::Object>>(rhs.data).get();
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Symbiosis>>(this->data) &&
                std::holds_alternative<std::reference_wrapper<yli::ontology::Symbiosis>>(rhs.data))
        {
            return std::get<std::reference_wrapper<yli::ontology::Symbiosis>>(this->data).get() ==
                std::get<std::reference_wrapper<yli::ontology::Symbiosis>>(rhs.data).get();
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Holobiont>>(this->data) &&
                std::holds_alternative<std::reference_wrapper<yli::ontology::Holobiont>>(rhs.data))
        {
            return std::get<std::reference_wrapper<yli::ontology::Holobiont>>(this->data).get() ==
                std::get<std::reference_wrapper<yli::ontology::Holobiont>>(rhs.data).get();
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Font2d>>(this->data) &&
                std::holds_alternative<std::reference_wrapper<yli::ontology::Font2d>>(rhs.data))
        {
            return std::get<std::reference_wrapper<yli::ontology::Font2d>>(this->data).get() ==
                std::get<std::reference_wrapper<yli::ontology::Font2d>>(rhs.data).get();
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Text2d>>(this->data) &&
                std::holds_alternative<std::reference_wrapper<yli::ontology::Text2d>>(rhs.data))
        {
            return std::get<std::reference_wrapper<yli::ontology::Text2d>>(this->data).get() ==
                std::get<std::reference_wrapper<yli::ontology::Text2d>>(rhs.data).get();
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::VectorFont>>(this->data) &&
                std::holds_alternative<std::reference_wrapper<yli::ontology::VectorFont>>(rhs.data))
        {
            return std::get<std::reference_wrapper<yli::ontology::VectorFont>>(this->data).get() ==
                std::get<std::reference_wrapper<yli::ontology::VectorFont>>(rhs.data).get();
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Text3d>>(this->data) &&
                std::holds_alternative<std::reference_wrapper<yli::ontology::Text3d>>(rhs.data))
        {
            return std::get<std::reference_wrapper<yli::ontology::Text3d>>(this->data).get() ==
                std::get<std::reference_wrapper<yli::ontology::Text3d>>(rhs.data).get();
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Console>>(this->data) &&
                std::holds_alternative<std::reference_wrapper<yli::ontology::Console>>(rhs.data))
        {
            return std::get<std::reference_wrapper<yli::ontology::Console>>(this->data).get() ==
                std::get<std::reference_wrapper<yli::ontology::Console>>(rhs.data).get();
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::ComputeTask>>(this->data) &&
                std::holds_alternative<std::reference_wrapper<yli::ontology::ComputeTask>>(rhs.data))
        {
            return std::get<std::reference_wrapper<yli::ontology::ComputeTask>>(this->data).get() ==
                std::get<std::reference_wrapper<yli::ontology::ComputeTask>>(rhs.data).get();
        }

        return false;
    }

    std::string AnyValue::get_datatype() const noexcept
    {
        // Fundamental types.
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
        // Strings.
        else if (std::holds_alternative<std::reference_wrapper<std::string>>(this->data))
        {
            return "std::string&";
        }
        else if (std::holds_alternative<std::reference_wrapper<const std::string>>(this->data))
        {
            return "const std::string&";
        }
        // Variable-size vectors.
        else if (std::holds_alternative<std::reference_wrapper<std::vector<int8_t>>>(this->data))
        {
            return "std::vector<int8_t>&";
        }
        else if (std::holds_alternative<std::reference_wrapper<std::vector<uint8_t>>>(this->data))
        {
            return "std::vector<uint8_t>&";
        }
        else if (std::holds_alternative<std::reference_wrapper<std::vector<int16_t>>>(this->data))
        {
            return "std::vector<int16_t>&";
        }
        else if (std::holds_alternative<std::reference_wrapper<std::vector<uint16_t>>>(this->data))
        {
            return "std::vector<uint16_t>&";
        }
        else if (std::holds_alternative<std::reference_wrapper<std::vector<int32_t>>>(this->data))
        {
            return "std::vector<int32_t>&";
        }
        else if (std::holds_alternative<std::reference_wrapper<std::vector<uint32_t>>>(this->data))
        {
            return "std::vector<uint32_t>&";
        }
        else if (std::holds_alternative<std::reference_wrapper<std::vector<float>>>(this->data))
        {
            return "std::vector<float>&";
        }
        // Fixed-size vectors.
        else if (std::holds_alternative<std::reference_wrapper<glm::vec3>>(this->data))
        {
            return "glm::vec3&";
        }
        else if (std::holds_alternative<std::reference_wrapper<const glm::vec3>>(this->data))
        {
            return "const glm::vec3&";
        }
        else if (std::holds_alternative<std::reference_wrapper<glm::vec4>>(this->data))
        {
            return "glm::vec4&";
        }
        else if (std::holds_alternative<std::reference_wrapper<const glm::vec4>>(this->data))
        {
            return "const glm::vec4&";
        }
        // Ontology.
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Entity>>(this->data))
        {
            return "yli::ontology::Entity&";
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Movable>>(this->data))
        {
            return "yli::ontology::Movable&";
        }
        else if (std::holds_alternative<std::reference_wrapper<const yli::ontology::Movable>>(this->data))
        {
            return "const yli::ontology::Movable&";
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Universe>>(this->data))
        {
            return "yli::ontology::Universe&";
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Ecosystem>>(this->data))
        {
            return "yli::ontology::Ecosystem&";
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Scene>>(this->data))
        {
            return "yli::ontology::Scene&";
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Pipeline>>(this->data))
        {
            return "yli::ontology::Pipeline&";
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Material>>(this->data))
        {
            return "yli::ontology::Material&";
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Species>>(this->data))
        {
            return "yli::ontology::Species&";
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Object>>(this->data))
        {
            return "yli::ontology::Object&";
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Symbiosis>>(this->data))
        {
            return "yli::ontology::Symbiosis&";
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Holobiont>>(this->data))
        {
            return "yli::ontology::Holobiont&";
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Font2d>>(this->data))
        {
            return "yli::ontology::Font2d&";
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Text2d>>(this->data))
        {
            return "yli::ontology::Text2d&";
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::VectorFont>>(this->data))
        {
            return "yli::ontology::VectorFont&";
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Text3d>>(this->data))
        {
            return "yli::ontology::Text3d&";
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Console>>(this->data))
        {
            return "yli::ontology::Console&";
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::ComputeTask>>(this->data))
        {
            return "yli::ontology::ComputeTask&";
        }

        return "ERROR: `AnyValue::get_datatype`: no datatype string defined for this datatype!";
    }

    std::string AnyValue::get_string() const
    {
        std::stringstream any_value_stringstream;
        any_value_stringstream.precision(6); // 6 decimals in floating point output.

        // Fundamental types.
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
        // Strings.
        else if (std::holds_alternative<std::reference_wrapper<std::string>>(this->data))
        {
            any_value_stringstream << std::get<std::reference_wrapper<std::string>>(this->data).get();
        }
        else if (std::holds_alternative<std::reference_wrapper<const std::string>>(this->data))
        {
            any_value_stringstream << std::get<std::reference_wrapper<const std::string>>(this->data).get();
        }
        // Variable-size vectors.
        else if (std::holds_alternative<std::reference_wrapper<std::vector<int8_t>>>(this->data))
        {
            any_value_stringstream << "std::vector<int8_t>&";
        }
        else if (std::holds_alternative<std::reference_wrapper<std::vector<uint8_t>>>(this->data))
        {
            any_value_stringstream << "std::vector<uint8_t>&";
        }
        else if (std::holds_alternative<std::reference_wrapper<std::vector<int16_t>>>(this->data))
        {
            any_value_stringstream << "std::vector<int16_t>&";
        }
        else if (std::holds_alternative<std::reference_wrapper<std::vector<uint16_t>>>(this->data))
        {
            any_value_stringstream << "std::vector<uint16_t>&";
        }
        else if (std::holds_alternative<std::reference_wrapper<std::vector<int32_t>>>(this->data))
        {
            any_value_stringstream << "std::vector<int32_t>&";
        }
        else if (std::holds_alternative<std::reference_wrapper<std::vector<uint32_t>>>(this->data))
        {
            any_value_stringstream << "std::vector<uint32_t>&";
        }
        else if (std::holds_alternative<std::reference_wrapper<std::vector<float>>>(this->data))
        {
            any_value_stringstream << "std::vector<float>&";
        }
        // Fixed-size vectors.
        else if (std::holds_alternative<std::reference_wrapper<glm::vec3>>(this->data))
        {
            const glm::vec3& cartesian_coordinates = std::get<std::reference_wrapper<glm::vec3>>(this->data);

            any_value_stringstream << std::fixed << "{ " << cartesian_coordinates.x
                << ", " << cartesian_coordinates.y
                << ", " << cartesian_coordinates.z
                << " }";
        }
        else if (std::holds_alternative<std::reference_wrapper<const glm::vec3>>(this->data))
        {
            const glm::vec3& cartesian_coordinates = std::get<std::reference_wrapper<const glm::vec3>>(this->data);

            any_value_stringstream << std::fixed << "{ " << cartesian_coordinates.x
                << ", " << cartesian_coordinates.y
                << ", " << cartesian_coordinates.z
                << " }";
        }
        else if (std::holds_alternative<std::reference_wrapper<glm::vec4>>(this->data))
        {
            const glm::vec4& cartesian_coordinates = std::get<std::reference_wrapper<glm::vec4>>(this->data);

            any_value_stringstream << std::fixed << "{ " << cartesian_coordinates.x
                << ", " << cartesian_coordinates.y
                << ", " << cartesian_coordinates.z
                << ", " << cartesian_coordinates.w
                << " }";
        }
        else if (std::holds_alternative<std::reference_wrapper<const glm::vec4>>(this->data))
        {
            const glm::vec4& cartesian_coordinates = std::get<std::reference_wrapper<const glm::vec4>>(this->data);

            any_value_stringstream << std::fixed << "{ " << cartesian_coordinates.x
                << ", " << cartesian_coordinates.y
                << ", " << cartesian_coordinates.z
                << ", " << cartesian_coordinates.w
                << " }";
        }
        // Ontology.
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Entity>>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) &std::get<std::reference_wrapper<yli::ontology::Entity>>(this->data) << std::dec;
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Movable>>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) &std::get<std::reference_wrapper<yli::ontology::Movable>>(this->data) << std::dec;
        }
        else if (std::holds_alternative<std::reference_wrapper<const yli::ontology::Movable>>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) &std::get<std::reference_wrapper<const yli::ontology::Movable>>(this->data) << std::dec;
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Universe>>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) &std::get<std::reference_wrapper<yli::ontology::Universe>>(this->data) << std::dec;
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Ecosystem>>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) &std::get<std::reference_wrapper<yli::ontology::Ecosystem>>(this->data) << std::dec;
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Scene>>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) &std::get<std::reference_wrapper<yli::ontology::Scene>>(this->data) << std::dec;
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Pipeline>>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) &std::get<std::reference_wrapper<yli::ontology::Pipeline>>(this->data) << std::dec;
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Material>>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) &std::get<std::reference_wrapper<yli::ontology::Material>>(this->data) << std::dec;
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Species>>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) &std::get<std::reference_wrapper<yli::ontology::Species>>(this->data) << std::dec;
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Object>>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) &std::get<std::reference_wrapper<yli::ontology::Object>>(this->data) << std::dec;
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Symbiosis>>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) &std::get<std::reference_wrapper<yli::ontology::Symbiosis>>(this->data) << std::dec;
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Holobiont>>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) &std::get<std::reference_wrapper<yli::ontology::Holobiont>>(this->data) << std::dec;
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Font2d>>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) &std::get<std::reference_wrapper<yli::ontology::Font2d>>(this->data) << std::dec;
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Text2d>>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) &std::get<std::reference_wrapper<yli::ontology::Text2d>>(this->data) << std::dec;
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::VectorFont>>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) &std::get<std::reference_wrapper<yli::ontology::VectorFont>>(this->data) << std::dec;
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Text3d>>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) &std::get<std::reference_wrapper<yli::ontology::Text3d>>(this->data) << std::dec;
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Console>>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) &std::get<std::reference_wrapper<yli::ontology::Console>>(this->data) << std::dec;
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::ComputeTask>>(this->data))
        {
            any_value_stringstream << std::hex << (uint64_t) &std::get<std::reference_wrapper<yli::ontology::ComputeTask>>(this->data) << std::dec;
        }
        else
        {
            return "ERROR: `AnyValue::get_string`: no string defined for this datatype!";
        }

        return any_value_stringstream.str();
    }

    const std::string& AnyValue::get_const_std_string_ref() const
    {
        if (std::holds_alternative<std::reference_wrapper<std::string>>(this->data))
        {
            return std::get<std::reference_wrapper<std::string>>(this->data);
        }
        else if (std::holds_alternative<std::reference_wrapper<const std::string>>(this->data))
        {
            return std::get<std::reference_wrapper<const std::string>>(this->data);
        }

        throw std::runtime_error("Requested `const std::string&` for `AnyValue` that didn't hold `std::string` or `const std::string` reference!");
    }

    yli::ontology::Entity& AnyValue::get_entity_ref() const
    {
        if (std::holds_alternative<std::reference_wrapper<yli::ontology::Entity>>(this->data))
        {
            return std::get<std::reference_wrapper<yli::ontology::Entity>>(this->data);
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Universe>>(this->data))
        {
            return std::get<std::reference_wrapper<yli::ontology::Universe>>(this->data);
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Movable>>(this->data))
        {
            return std::get<std::reference_wrapper<yli::ontology::Movable>>(this->data);
        }
        else if (std::holds_alternative<std::reference_wrapper<const yli::ontology::Movable>>(this->data))
        {
            throw std::runtime_error("Requested `Entity&` for `AnyValue` that holds `const Movable` reference!");
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Ecosystem>>(this->data))
        {
            return std::get<std::reference_wrapper<yli::ontology::Ecosystem>>(this->data);
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Scene>>(this->data))
        {
            return std::get<std::reference_wrapper<yli::ontology::Scene>>(this->data);
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Pipeline>>(this->data))
        {
            return std::get<std::reference_wrapper<yli::ontology::Pipeline>>(this->data);
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Material>>(this->data))
        {
            return std::get<std::reference_wrapper<yli::ontology::Material>>(this->data);
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Species>>(this->data))
        {
            return std::get<std::reference_wrapper<yli::ontology::Species>>(this->data);
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Object>>(this->data))
        {
            return std::get<std::reference_wrapper<yli::ontology::Object>>(this->data);
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Symbiosis>>(this->data))
        {
            return std::get<std::reference_wrapper<yli::ontology::Symbiosis>>(this->data);
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Holobiont>>(this->data))
        {
            return std::get<std::reference_wrapper<yli::ontology::Holobiont>>(this->data);
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Font2d>>(this->data))
        {
            return std::get<std::reference_wrapper<yli::ontology::Font2d>>(this->data);
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Text2d>>(this->data))
        {
            return std::get<std::reference_wrapper<yli::ontology::Text2d>>(this->data);
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::VectorFont>>(this->data))
        {
            return std::get<std::reference_wrapper<yli::ontology::VectorFont>>(this->data);
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Text3d>>(this->data))
        {
            return std::get<std::reference_wrapper<yli::ontology::Text3d>>(this->data);
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Console>>(this->data))
        {
            return std::get<std::reference_wrapper<yli::ontology::Console>>(this->data);
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::ComputeTask>>(this->data))
        {
            return std::get<std::reference_wrapper<yli::ontology::ComputeTask>>(this->data);
        }

        throw std::runtime_error("Requested `Entity&` for `AnyValue` that didn't hold `Entity` reference!");
    }

    const yli::ontology::Entity& AnyValue::get_const_entity_ref() const
    {
        if (std::holds_alternative<std::reference_wrapper<const yli::ontology::Movable>>(this->data))
        {
            return std::get<std::reference_wrapper<const yli::ontology::Movable>>(this->data);
        }

        return this->get_entity_ref();
    }

    bool AnyValue::has_movable_ref() const
    {
        if (std::holds_alternative<std::reference_wrapper<yli::ontology::Movable>>(this->data))
        {
            return true;
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Object>>(this->data))
        {
            return true;
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Holobiont>>(this->data))
        {
            return true;
        }

        return false;
    }

    bool AnyValue::has_const_movable_ref() const
    {
        if (std::holds_alternative<std::reference_wrapper<const yli::ontology::Movable>>(this->data))
        {
            return true;
        }

        return this->has_movable_ref();
    }

    yli::ontology::Movable& AnyValue::get_movable_ref() const
    {
        if (std::holds_alternative<std::reference_wrapper<yli::ontology::Movable>>(this->data))
        {
            return std::get<std::reference_wrapper<yli::ontology::Movable>>(this->data);
        }
        else if (std::holds_alternative<std::reference_wrapper<const yli::ontology::Movable>>(this->data))
        {
            throw std::runtime_error("Requested `Movable&` for `AnyValue` that holds `const Movable` reference!");
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Object>>(this->data))
        {
            return std::get<std::reference_wrapper<yli::ontology::Object>>(this->data);
        }
        else if (std::holds_alternative<std::reference_wrapper<yli::ontology::Holobiont>>(this->data))
        {
            return std::get<std::reference_wrapper<yli::ontology::Holobiont>>(this->data);
        }

        throw std::runtime_error("Requested `Movable&` for `AnyValue` that didn't hold `Movable` reference!");
    }

    const yli::ontology::Movable& AnyValue::get_const_movable_ref() const
    {
        if (std::holds_alternative<std::reference_wrapper<const yli::ontology::Movable>>(this->data))
        {
            return std::get<std::reference_wrapper<const yli::ontology::Movable>>(this->data);
        }

        return this->get_movable_ref();
    }

    bool AnyValue::set_new_value(const std::string& value_string)
    {
        std::stringstream value_stringstream;

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
            if (!yli::string::check_if_float_string<char>(value_string))
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
            if (!yli::string::check_if_double_string<char>(value_string))
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
            if (!yli::string::check_if_signed_integer_string<char>(value_string))
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
            if (!yli::string::check_if_unsigned_integer_string<char>(value_string))
            {
                return false;
            }

            uint32_t uint32_t_value;
            value_stringstream << value_string;
            value_stringstream >> uint32_t_value;
            this->data = uint32_t_value;
            return true;
        }

        return false;
    }

    AnyValue::AnyValue(const std::optional<AnyValue> original)
    {
        // constructor for optional `AnyValue`.

        if (original)
        {
            this->data = (*original).data;
        }
    }

    AnyValue::AnyValue(const std::string& type, const std::string& value_string)
        : data(get_variant<
                std::monostate,
                // Fundamental types.
                bool,
                char,
                float,
                double,
                int32_t,
                uint32_t,
                // Strings.
                std::reference_wrapper<std::string>,
                std::reference_wrapper<const std::string>,
                // Variable-size vectors.
                std::reference_wrapper<std::vector<int8_t>>,
                std::reference_wrapper<std::vector<uint8_t>>,
                std::reference_wrapper<std::vector<int16_t>>,
                std::reference_wrapper<std::vector<uint16_t>>,
                std::reference_wrapper<std::vector<int32_t>>,
                std::reference_wrapper<std::vector<uint32_t>>,
                std::reference_wrapper<std::vector<float>>,
                // Fixed-size vectors.
                std::reference_wrapper<glm::vec3>,
                std::reference_wrapper<const glm::vec3>,
                std::reference_wrapper<glm::vec4>,
                std::reference_wrapper<const glm::vec4>,
                // Ontology.
                std::reference_wrapper<yli::ontology::Entity>,
                std::reference_wrapper<yli::ontology::Movable>,
                std::reference_wrapper<const yli::ontology::Movable>,
                std::reference_wrapper<yli::ontology::Universe>,
                std::reference_wrapper<yli::ontology::Ecosystem>,
                std::reference_wrapper<yli::ontology::Scene>,
                std::reference_wrapper<yli::ontology::Pipeline>,
                std::reference_wrapper<yli::ontology::Material>,
                std::reference_wrapper<yli::ontology::Species>,
                std::reference_wrapper<yli::ontology::Object>,
                std::reference_wrapper<yli::ontology::Symbiosis>,
                std::reference_wrapper<yli::ontology::Holobiont>,
                std::reference_wrapper<yli::ontology::Font2d>,
                std::reference_wrapper<yli::ontology::Text2d>,
                std::reference_wrapper<yli::ontology::VectorFont>,
                std::reference_wrapper<yli::ontology::Text3d>,
                std::reference_wrapper<yli::ontology::Console>,
                std::reference_wrapper<yli::ontology::ComputeTask>>(type, value_string))
    {
    }

    // Fundamental types.

    AnyValue::AnyValue(const bool bool_value)
        : data(bool_value)
    {
    }

    AnyValue::AnyValue(const char char_value)
        : data(char_value)
    {
    }

    AnyValue::AnyValue(const float float_value)
        : data(float_value)
    {
    }

    AnyValue::AnyValue(const double double_value)
        : data(double_value)
    {
    }

    AnyValue::AnyValue(const int32_t int32_t_value)
        : data(int32_t_value)
    {
    }

    AnyValue::AnyValue(const uint32_t uint32_t_value)
        : data(uint32_t_value)
    {
    }

    // Strings.

    AnyValue::AnyValue(std::string& std_string_ref)
        : data(std::reference_wrapper<std::string>(std_string_ref))
    {
    }

    AnyValue::AnyValue(const std::string& const_std_string_ref)
        : data(std::reference_wrapper<const std::string>(const_std_string_ref))
    {
    }

    // Variable-size vectors.

    AnyValue::AnyValue(std::vector<int8_t>& std_vector_int8_t_ref)
        : data(std::reference_wrapper<std::vector<int8_t>>(std_vector_int8_t_ref))
    {
    }

    AnyValue::AnyValue(std::vector<uint8_t>& std_vector_uint8_t_ref)
        : data(std::reference_wrapper<std::vector<uint8_t>>(std_vector_uint8_t_ref))
    {
    }

    AnyValue::AnyValue(std::vector<int16_t>& std_vector_int16_t_ref)
        : data(std::reference_wrapper<std::vector<int16_t>>(std_vector_int16_t_ref))
    {
    }

    AnyValue::AnyValue(std::vector<uint16_t>& std_vector_uint16_t_ref)
        : data(std::reference_wrapper<std::vector<uint16_t>>(std_vector_uint16_t_ref))
    {
    }

    AnyValue::AnyValue(std::vector<int32_t>& std_vector_int32_t_ref)
        : data(std::reference_wrapper<std::vector<int32_t>>(std_vector_int32_t_ref))
    {
    }

    AnyValue::AnyValue(std::vector<uint32_t>& std_vector_uint32_t_ref)
        : data(std::reference_wrapper<std::vector<uint32_t>>(std_vector_uint32_t_ref))
    {
    }

    AnyValue::AnyValue(std::vector<float>& std_vector_float_ref)
        : data(std::reference_wrapper<std::vector<float>>(std_vector_float_ref))
    {
    }

    // Fixed-size vectors.

    AnyValue::AnyValue(glm::vec3& glm_vec3_ref)
        : data(std::reference_wrapper<glm::vec3>(glm_vec3_ref))
    {
    }

    AnyValue::AnyValue(const glm::vec3& const_glm_vec3_ref)
        : data(std::reference_wrapper<const glm::vec3>(const_glm_vec3_ref))
    {
    }

    AnyValue::AnyValue(glm::vec4& glm_vec4_ref)
        : data(std::reference_wrapper<glm::vec4>(glm_vec4_ref))
    {
    }

    AnyValue::AnyValue(const glm::vec4& const_glm_vec4_ref)
        : data(std::reference_wrapper<const glm::vec4>(const_glm_vec4_ref))
    {
    }

    // Ontology.

    AnyValue::AnyValue(yli::ontology::Entity& entity_ref)
        : data(std::reference_wrapper<yli::ontology::Entity>(entity_ref))
    {
    }

    AnyValue::AnyValue(yli::ontology::Movable& movable_ref)
        : data(std::reference_wrapper<yli::ontology::Movable>(movable_ref))
    {
    }

    AnyValue::AnyValue(const yli::ontology::Movable& const_movable_ref)
        : data(std::reference_wrapper<const yli::ontology::Movable>(const_movable_ref))
    {
    }

    AnyValue::AnyValue(yli::ontology::Universe& universe_ref)
        : data(std::reference_wrapper<yli::ontology::Universe>(universe_ref))
    {
    }

    AnyValue::AnyValue(yli::ontology::Ecosystem& ecosystem_ref)
        : data(std::reference_wrapper<yli::ontology::Ecosystem>(ecosystem_ref))
    {
    }

    AnyValue::AnyValue(yli::ontology::Scene& scene_ref)
        : data(std::reference_wrapper<yli::ontology::Scene>(scene_ref))
    {
    }

    AnyValue::AnyValue(yli::ontology::Pipeline& pipeline_ref)
        : data(std::reference_wrapper<yli::ontology::Pipeline>(pipeline_ref))
    {
    }

    AnyValue::AnyValue(yli::ontology::Material& material_ref)
        : data(std::reference_wrapper<yli::ontology::Material>(material_ref))
    {
    }

    AnyValue::AnyValue(yli::ontology::Species& species_ref)
        : data(std::reference_wrapper<yli::ontology::Species>(species_ref))
    {
    }

    AnyValue::AnyValue(yli::ontology::Object& object_ref)
        : data(std::reference_wrapper<yli::ontology::Object>(object_ref))
    {
    }

    AnyValue::AnyValue(yli::ontology::Symbiosis& symbiosis_ref)
        : data(std::reference_wrapper<yli::ontology::Symbiosis>(symbiosis_ref))
    {
    }

    AnyValue::AnyValue(yli::ontology::Holobiont& holobiont_ref)
        : data(std::reference_wrapper<yli::ontology::Holobiont>(holobiont_ref))
    {
    }

    AnyValue::AnyValue(yli::ontology::Font2d& font_2d_ref)
        : data(std::reference_wrapper<yli::ontology::Font2d>(font_2d_ref))
    {
    }

    AnyValue::AnyValue(yli::ontology::Text2d& text_2d_ref)
        : data(std::reference_wrapper<yli::ontology::Text2d>(text_2d_ref))
    {
    }

    AnyValue::AnyValue(yli::ontology::VectorFont& vector_font_ref)
        : data(std::reference_wrapper<yli::ontology::VectorFont>(vector_font_ref))
    {
    }

    AnyValue::AnyValue(yli::ontology::Text3d& text_3d_ref)
        : data(std::reference_wrapper<yli::ontology::Text3d>(text_3d_ref))
    {
    }

    AnyValue::AnyValue(yli::ontology::Console& console_ref)
        : data(std::reference_wrapper<yli::ontology::Console>(console_ref))
    {
    }

    AnyValue::AnyValue(yli::ontology::ComputeTask& compute_task_ref)
        : data(std::reference_wrapper<yli::ontology::ComputeTask>(compute_task_ref))
    {
    }
}
