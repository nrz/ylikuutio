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

#ifndef __YLIKUUTIO_DATA_ANY_VALUE_HPP_INCLUDED
#define __YLIKUUTIO_DATA_ANY_VALUE_HPP_INCLUDED

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <memory>   // std::make_shared, std::shared_ptr
#include <optional> // std::optional
#include <string>   // std::string
#include <stdint.h> // uint32_t etc.
#include <variant>  // std::holds_alternative, std::variant
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
    class AnyStruct;
    struct SphericalCoordinatesStruct;

    class AnyValue
    {
        public:
            bool operator==(const yli::data::AnyValue& rhs) const;
            bool operator!=(const yli::data::AnyValue& rhs) const;
            std::string get_datatype() const;
            std::string get_string() const;
            yli::ontology::Entity* get_entity_pointer() const;
            bool set_new_value(const std::string& value_string);

            // copy constructor.
            AnyValue(const yli::data::AnyValue& original);

            // constructor for optional `AnyValue`.
            AnyValue(const std::optional<yli::data::AnyValue> original);

            // common constructors.

            AnyValue(); // This constructor initializes `AnyValue` with default values.
            AnyValue(const std::string& type, const std::string& value_string); // This constructor takes also the value as a string.
            explicit AnyValue(const bool bool_value);
            explicit AnyValue(const char char_value);
            explicit AnyValue(const float float_value);
            explicit AnyValue(const double double_value);
            explicit AnyValue(const int32_t int32_t_value);
            explicit AnyValue(const uint32_t uint32_t_value);
            explicit AnyValue(bool* const bool_pointer);
            explicit AnyValue(char* const char_pointer);
            explicit AnyValue(float* const float_pointer);
            explicit AnyValue(double* const double_pointer);
            explicit AnyValue(int32_t* const int32_t_pointer);
            explicit AnyValue(uint32_t* const uint32_t_pointer);
            explicit AnyValue(yli::ontology::Entity* const entity_pointer);
            explicit AnyValue(yli::ontology::Movable* const movable_pointer);
            explicit AnyValue(const yli::ontology::Movable* const const_movable_pointer);
            explicit AnyValue(yli::ontology::Universe* const universe_pointer);
            explicit AnyValue(yli::ontology::Ecosystem* const ecosystem_pointer);
            explicit AnyValue(yli::ontology::Scene* const scene_pointer);
            explicit AnyValue(yli::ontology::Shader* const shader_pointer);
            explicit AnyValue(yli::ontology::Material* const material_pointer);
            explicit AnyValue(yli::ontology::Species* const species_pointer);
            explicit AnyValue(yli::ontology::Object* const object_pointer);
            explicit AnyValue(yli::ontology::Symbiosis* const symbiosis_pointer);
            explicit AnyValue(yli::ontology::SymbiontMaterial* const symbiont_material_pointer);
            explicit AnyValue(yli::ontology::SymbiontSpecies* const symbiont_species_pointer);
            explicit AnyValue(yli::ontology::Holobiont* const holobiont_pointer);
            explicit AnyValue(yli::ontology::Biont* const biont_pointer);
            explicit AnyValue(yli::ontology::Font2D* const font_2d_pointer);
            explicit AnyValue(yli::ontology::Text2D* const text_2d_pointer);
            explicit AnyValue(yli::ontology::VectorFont* const vector_font_pointer);
            explicit AnyValue(yli::ontology::Glyph* const glyph_pointer);
            explicit AnyValue(yli::ontology::Text3D* const text_3d_pointer);
            explicit AnyValue(yli::ontology::Console* const console_pointer);
            explicit AnyValue(yli::ontology::ComputeTask* const compute_task_pointer);
            explicit AnyValue(std::shared_ptr<yli::data::AnyValue> any_value_shared_ptr);
            explicit AnyValue(std::shared_ptr<yli::data::AnyStruct> any_struct_shared_ptr);
            explicit AnyValue(yli::data::SphericalCoordinatesStruct* const spherical_coordinates_struct_pointer);
            explicit AnyValue(std::string* const std_string_pointer);
            explicit AnyValue(const std::string* const const_std_string_pointer);
            explicit AnyValue(std::shared_ptr<std::vector<int8_t>> std_vector_int8_t_shared_ptr);
            explicit AnyValue(std::shared_ptr<std::vector<uint8_t>> std_vector_uint8_t_shared_ptr);
            explicit AnyValue(std::shared_ptr<std::vector<int16_t>> std_vector_int16_t_shared_ptr);
            explicit AnyValue(std::shared_ptr<std::vector<uint16_t>> std_vector_uint16_t_shared_ptr);
            explicit AnyValue(std::shared_ptr<std::vector<int32_t>> std_vector_int32_t_shared_ptr);
            explicit AnyValue(std::shared_ptr<std::vector<uint32_t>> std_vector_uint32_t_shared_ptr);
            explicit AnyValue(std::shared_ptr<std::vector<float>> std_vector_float_shared_ptr);
            explicit AnyValue(std::shared_ptr<std::string> std_string_shared_ptr);
            explicit AnyValue(std::shared_ptr<glm::vec3> const glm_vec3_shared_ptr);
            explicit AnyValue(std::shared_ptr<glm::vec4> const glm_vec4_shared_ptr);

            std::variant<
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
                const std::string*
                    > data;
    };
}

#endif
