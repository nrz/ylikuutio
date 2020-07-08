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

#ifndef __VARIANT_TEMPLATES_HPP_INCLUDED
#define __VARIANT_TEMPLATES_HPP_INCLUDED

#include "any_value.hpp"
#include "any_struct.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <memory>   // std::make_shared, std::shared_ptr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <sstream>  // std::istringstream, std::ostringstream, std::stringstream
#include <variant>  // std::holds_alternative, std::variant

namespace yli::ontology
{
    class Entity;
    class Movable;
    class Universe;
    class World;
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
    struct SphericalCoordinatesStruct;

    // Get a variant based on `std::variant` type, a type string and a value string.
    template<class... V>
        std::variant<V...> get_variant(const std::string& type, const std::string& value_string)
        {
            std::stringstream value_stringstream;
            std::variant<V...> my_variant;

            if (type == "bool")
            {
                if (value_string == "true")       // Ylikuutio is case sensitive!
                {
                    my_variant = true;
                }
                else if (value_string == "false") // Ylikuutio is case sensitive!
                {
                    my_variant = false;
                }
            }
            else if (type == "char")
            {
                if (value_string.size() == 1)
                {
                    my_variant = value_string[0];
                }
            }
            else if (type == "float")
            {
                if (yli::string::check_if_float_string(value_string))
                {
                    float float_value;
                    value_stringstream << value_string;
                    value_stringstream >> float_value;
                    my_variant = float_value;
                }
            }
            else if (type == "double")
            {
                if (yli::string::check_if_double_string(value_string))
                {
                    double double_value;
                    value_stringstream << value_string;
                    value_stringstream >> double_value;
                    my_variant = double_value;
                }
            }
            else if (type == "int32_t")
            {
                if (yli::string::check_if_signed_integer_string(value_string))
                {
                    int32_t int32_t_value;
                    value_stringstream << value_string;
                    value_stringstream >> int32_t_value;
                    my_variant = int32_t_value;
                }
            }
            else if (type == "uint32_t")
            {
                if (yli::string::check_if_unsigned_integer_string(value_string))
                {
                    uint32_t uint32_t_value;
                    value_stringstream << value_string;
                    value_stringstream >> uint32_t_value;
                    my_variant = uint32_t_value;
                }
            }
            else if (type == "bool*")
            {
                if (yli::string::check_if_unsigned_integer_string(value_string))
                {
                    void* void_pointer = nullptr;
                    value_stringstream << value_string;
                    value_stringstream >> void_pointer;
                    my_variant = static_cast<bool*>(void_pointer);
                }
            }
            else if (type == "char*")
            {
                if (yli::string::check_if_unsigned_integer_string(value_string))
                {
                    void* void_pointer = nullptr;
                    value_stringstream << value_string;
                    value_stringstream >> void_pointer;
                    my_variant = static_cast<char*>(void_pointer);
                }
            }
            else if (type == "float*")
            {
                if (yli::string::check_if_unsigned_integer_string(value_string))
                {
                    void* void_pointer = nullptr;
                    value_stringstream << value_string;
                    value_stringstream >> void_pointer;
                    my_variant = static_cast<float*>(void_pointer);
                }
            }
            else if (type == "double*")
            {
                if (yli::string::check_if_unsigned_integer_string(value_string))
                {
                    void* void_pointer = nullptr;
                    value_stringstream << value_string;
                    value_stringstream >> void_pointer;
                    my_variant = static_cast<double*>(void_pointer);
                }
            }
            else if (type == "int32_t*")
            {
                if (yli::string::check_if_unsigned_integer_string(value_string))
                {
                    void* void_pointer = nullptr;
                    value_stringstream << value_string;
                    value_stringstream >> void_pointer;
                    my_variant = static_cast<int32_t*>(void_pointer);
                }
            }
            else if (type == "uint32_t*")
            {
                if (yli::string::check_if_unsigned_integer_string(value_string))
                {
                    void* void_pointer = nullptr;
                    value_stringstream << value_string;
                    value_stringstream >> void_pointer;
                    my_variant = static_cast<uint32_t*>(void_pointer);
                }
            }
            else if (type == "yli::ontology::Entity*")
            {
                if (yli::string::check_if_unsigned_integer_string(value_string))
                {
                    void* void_pointer = nullptr;
                    value_stringstream << value_string;
                    value_stringstream >> void_pointer;
                    my_variant = static_cast<yli::ontology::Entity*>(void_pointer);
                }
            }
            else if (type == "yli::ontology::Movable*")
            {
                if (yli::string::check_if_unsigned_integer_string(value_string))
                {
                    void* void_pointer = nullptr;
                    value_stringstream << value_string;
                    value_stringstream >> void_pointer;
                    my_variant = static_cast<yli::ontology::Movable*>(void_pointer);
                }
            }
            else if (type == "const yli::ontology::Movable*")
            {
                if (yli::string::check_if_unsigned_integer_string(value_string))
                {
                    void* void_pointer = nullptr;
                    value_stringstream << value_string;
                    value_stringstream >> void_pointer;
                    my_variant = static_cast<const yli::ontology::Movable*>(void_pointer);
                }
            }
            else if (type == "yli::ontology::Universe*")
            {
                if (yli::string::check_if_unsigned_integer_string(value_string))
                {
                    void* void_pointer = nullptr;
                    value_stringstream << value_string;
                    value_stringstream >> void_pointer;
                    my_variant = static_cast<yli::ontology::Universe*>(void_pointer);
                }
            }
            else if (type == "yli::ontology::World*")
            {
                if (yli::string::check_if_unsigned_integer_string(value_string))
                {
                    void* void_pointer = nullptr;
                    value_stringstream << value_string;
                    value_stringstream >> void_pointer;
                    my_variant = static_cast<yli::ontology::World*>(void_pointer);
                }
            }
            else if (type == "yli::ontology::Scene*")
            {
                if (yli::string::check_if_unsigned_integer_string(value_string))
                {
                    void* void_pointer = nullptr;
                    value_stringstream << value_string;
                    value_stringstream >> void_pointer;
                    my_variant = static_cast<yli::ontology::Scene*>(void_pointer);
                }
            }
            else if (type == "yli::ontology::Shader*")
            {
                if (yli::string::check_if_unsigned_integer_string(value_string))
                {
                    void* void_pointer = nullptr;
                    value_stringstream << value_string;
                    value_stringstream >> void_pointer;
                    my_variant = static_cast<yli::ontology::Shader*>(void_pointer);
                }
            }
            else if (type == "yli::ontology::Material*")
            {
                if (yli::string::check_if_unsigned_integer_string(value_string))
                {
                    void* void_pointer = nullptr;
                    value_stringstream << value_string;
                    value_stringstream >> void_pointer;
                    my_variant = static_cast<yli::ontology::Material*>(void_pointer);
                }
            }
            else if (type == "yli::ontology::Species*")
            {
                if (yli::string::check_if_unsigned_integer_string(value_string))
                {
                    void* void_pointer = nullptr;
                    value_stringstream << value_string;
                    value_stringstream >> void_pointer;
                    my_variant = static_cast<yli::ontology::Species*>(void_pointer);
                }
            }
            else if (type == "yli::ontology::Object*")
            {
                if (yli::string::check_if_unsigned_integer_string(value_string))
                {
                    void* void_pointer = nullptr;
                    value_stringstream << value_string;
                    value_stringstream >> void_pointer;
                    my_variant = static_cast<yli::ontology::Object*>(void_pointer);
                }
            }
            else if (type == "yli::ontology::Symbiosis*")
            {
                if (yli::string::check_if_unsigned_integer_string(value_string))
                {
                    void* void_pointer = nullptr;
                    value_stringstream << value_string;
                    value_stringstream >> void_pointer;
                    my_variant = static_cast<yli::ontology::Symbiosis*>(void_pointer);
                }
            }
            else if (type == "yli::ontology::SymbiontMaterial*")
            {
                if (yli::string::check_if_unsigned_integer_string(value_string))
                {
                    void* void_pointer = nullptr;
                    value_stringstream << value_string;
                    value_stringstream >> void_pointer;
                    my_variant = static_cast<yli::ontology::SymbiontMaterial*>(void_pointer);
                }
            }
            else if (type == "yli::ontology::SymbiontSpecies*")
            {
                if (yli::string::check_if_unsigned_integer_string(value_string))
                {
                    void* void_pointer = nullptr;
                    value_stringstream << value_string;
                    value_stringstream >> void_pointer;
                    my_variant = static_cast<yli::ontology::SymbiontSpecies*>(void_pointer);
                }
            }
            else if (type == "yli::ontology::Holobiont*")
            {
                if (yli::string::check_if_unsigned_integer_string(value_string))
                {
                    void* void_pointer = nullptr;
                    value_stringstream << value_string;
                    value_stringstream >> void_pointer;
                    my_variant = static_cast<yli::ontology::Holobiont*>(void_pointer);
                }
            }
            else if (type == "yli::ontology::Biont*")
            {
                if (yli::string::check_if_unsigned_integer_string(value_string))
                {
                    void* void_pointer = nullptr;
                    value_stringstream << value_string;
                    value_stringstream >> void_pointer;
                    my_variant = static_cast<yli::ontology::Biont*>(void_pointer);
                }
            }
            else if (type == "yli::ontology::Font2D*")
            {
                if (yli::string::check_if_unsigned_integer_string(value_string))
                {
                    void* void_pointer = nullptr;
                    value_stringstream << value_string;
                    value_stringstream >> void_pointer;
                    my_variant = static_cast<yli::ontology::Font2D*>(void_pointer);
                }
            }
            else if (type == "yli::ontology::Text2D*")
            {
                if (yli::string::check_if_unsigned_integer_string(value_string))
                {
                    void* void_pointer = nullptr;
                    value_stringstream << value_string;
                    value_stringstream >> void_pointer;
                    my_variant = static_cast<yli::ontology::Text2D*>(void_pointer);
                }
            }
            else if (type == "yli::ontology::VectorFont*")
            {
                if (yli::string::check_if_unsigned_integer_string(value_string))
                {
                    void* void_pointer = nullptr;
                    value_stringstream << value_string;
                    value_stringstream >> void_pointer;
                    my_variant = static_cast<yli::ontology::VectorFont*>(void_pointer);
                }
            }
            else if (type == "yli::ontology::Glyph*")
            {
                if (yli::string::check_if_unsigned_integer_string(value_string))
                {
                    void* void_pointer = nullptr;
                    value_stringstream << value_string;
                    value_stringstream >> void_pointer;
                    my_variant = static_cast<yli::ontology::Glyph*>(void_pointer);
                }
            }
            else if (type == "yli::ontology::Text3D*")
            {
                if (yli::string::check_if_unsigned_integer_string(value_string))
                {
                    void* void_pointer = nullptr;
                    value_stringstream << value_string;
                    value_stringstream >> void_pointer;
                    my_variant = static_cast<yli::ontology::Text3D*>(void_pointer);
                }
            }
            else if (type == "yli::ontology::Console*")
            {
                if (yli::string::check_if_unsigned_integer_string(value_string))
                {
                    void* void_pointer = nullptr;
                    value_stringstream << value_string;
                    value_stringstream >> void_pointer;
                    my_variant = static_cast<yli::ontology::Console*>(void_pointer);
                }
            }
            else if (type == "yli::ontology::ComputeTask*")
            {
                if (yli::string::check_if_unsigned_integer_string(value_string))
                {
                    void* void_pointer = nullptr;
                    value_stringstream << value_string;
                    value_stringstream >> void_pointer;
                    my_variant = static_cast<yli::ontology::ComputeTask*>(void_pointer);
                }
            }
            else if (type == "std::shared_ptr<yli::data::AnyValue>")
            {
                if (yli::string::check_if_unsigned_integer_string(value_string))
                {
                    std::shared_ptr<yli::data::AnyValue> any_value_shared_ptr =
                        std::make_shared<yli::data::AnyValue>();
                    my_variant = any_value_shared_ptr;
                }
            }
            else if (type == "std::shared_ptr<yli::data::AnyStruct>")
            {
                if (yli::string::check_if_unsigned_integer_string(value_string))
                {
                    std::shared_ptr<yli::data::AnyStruct> any_struct_shared_ptr =
                        std::make_shared<yli::data::AnyStruct>();
                    my_variant = any_struct_shared_ptr;
                }
            }
            else if (type == "yli::data::SphericalCoordinatesStruct*")
            {
                if (yli::string::check_if_unsigned_integer_string(value_string))
                {
                    void* void_pointer = nullptr;
                    value_stringstream << value_string;
                    value_stringstream >> void_pointer;
                    my_variant = static_cast<yli::data::SphericalCoordinatesStruct*>(void_pointer);
                }
            }
            else if (type == "std::string*")
            {
                if (yli::string::check_if_unsigned_integer_string(value_string))
                {
                    void* void_pointer = nullptr;
                    value_stringstream << value_string;
                    value_stringstream >> void_pointer;
                    my_variant = static_cast<std::string*>(void_pointer);
                }
            }
            else if (type == "const std::string*")
            {
                if (yli::string::check_if_unsigned_integer_string(value_string))
                {
                    void* void_pointer = nullptr;
                    value_stringstream << value_string;
                    value_stringstream >> void_pointer;
                    my_variant = static_cast<const std::string*>(void_pointer);
                }
            }
            else if (type == "std::shared_ptr<glm::vec3>")
            {
                if (yli::string::check_if_unsigned_integer_string(value_string))
                {
                    std::shared_ptr<glm::vec3> glm_vec3_shared_ptr =
                        std::make_shared<glm::vec3>();
                    my_variant = glm_vec3_shared_ptr;
                }
            }
            else if (type == "std::shared_ptr<glm::vec4>")
            {
                if (yli::string::check_if_unsigned_integer_string(value_string))
                {
                    std::shared_ptr<glm::vec4> glm_vec4_shared_ptr =
                        std::make_shared<glm::vec4>();
                    my_variant = glm_vec4_shared_ptr;
                }
            }

            return my_variant;
        }
}

#endif
