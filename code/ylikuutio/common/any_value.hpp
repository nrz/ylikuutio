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

#ifndef __ANY_VALUE_HPP_INCLUDED
#define __ANY_VALUE_HPP_INCLUDED

#include "datatype.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <memory>   // std::make_shared, std::shared_ptr
#include <string>   // std::string
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace yli
{
    namespace ontology
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

    namespace common
    {
        class AnyStruct;
        class SphericalCoordinatesStruct;

        class AnyValue
        {
            public:
                std::string get_datatype() const;
                std::string get_string() const;
                yli::ontology::Entity* get_entity_pointer() const;
                bool set_value(const std::string& value_string);

                // copy constructor.
                AnyValue(const yli::common::AnyValue& original);

                // common constructors.

                AnyValue(); // This constructor initializes `AnyValue` with default values.
                AnyValue(const std::string& type, const std::string& value_string); // This constructor takes also the value as a string.
                AnyValue(const bool bool_value);
                AnyValue(const char char_value);
                AnyValue(const float float_value);
                AnyValue(const double double_value);
                AnyValue(const int32_t int32_t_value);
                AnyValue(const uint32_t uint32_t_value);
                AnyValue(bool* const bool_pointer);
                AnyValue(char* const char_pointer);
                AnyValue(float* const float_pointer);
                AnyValue(double* const double_pointer);
                AnyValue(int32_t* const int32_t_pointer);
                AnyValue(uint32_t* const uint32_t_pointer);
                AnyValue(yli::ontology::Entity* const entity_pointer);
                AnyValue(yli::ontology::Movable* const movable_pointer);
                AnyValue(const yli::ontology::Movable* const const_movable_pointer);
                AnyValue(yli::ontology::Universe* const universe_pointer);
                AnyValue(yli::ontology::World* const world_pointer);
                AnyValue(yli::ontology::Scene* const scene_pointer);
                AnyValue(yli::ontology::Shader* const shader_pointer);
                AnyValue(yli::ontology::Material* const material_pointer);
                AnyValue(yli::ontology::Species* const species_pointer);
                AnyValue(yli::ontology::Object* const object_pointer);
                AnyValue(yli::ontology::Symbiosis* const symbiosis_pointer);
                AnyValue(yli::ontology::SymbiontMaterial* const symbiont_material_pointer);
                AnyValue(yli::ontology::SymbiontSpecies* const symbiont_species_pointer);
                AnyValue(yli::ontology::Holobiont* const holobiont_pointer);
                AnyValue(yli::ontology::Biont* const biont_pointer);
                AnyValue(yli::ontology::Font2D* const font2D_pointer);
                AnyValue(yli::ontology::Text2D* const text2D_pointer);
                AnyValue(yli::ontology::VectorFont* const vector_font_pointer);
                AnyValue(yli::ontology::Glyph* const glyph_pointer);
                AnyValue(yli::ontology::Text3D* const text3D_pointer);
                AnyValue(yli::ontology::Console* const console_pointer);
                AnyValue(yli::ontology::ComputeTask* const compute_task_pointer);
                AnyValue(std::shared_ptr<yli::common::AnyValue> any_value_shared_ptr);
                AnyValue(std::shared_ptr<yli::common::AnyStruct> any_struct_shared_ptr);
                AnyValue(yli::common::SphericalCoordinatesStruct* const spherical_coordinates_struct_pointer);
                AnyValue(std::string* const std_string_pointer);
                AnyValue(const std::string* const const_std_string_pointer);
                AnyValue(std::shared_ptr<std::vector<int8_t>> std_vector_int8_t_shared_ptr);
                AnyValue(std::shared_ptr<std::vector<uint8_t>> std_vector_uint8_t_shared_ptr);
                AnyValue(std::shared_ptr<std::vector<int16_t>> std_vector_int16_t_shared_ptr);
                AnyValue(std::shared_ptr<std::vector<uint16_t>> std_vector_uint16_t_shared_ptr);
                AnyValue(std::shared_ptr<std::vector<int32_t>> std_vector_int32_t_shared_ptr);
                AnyValue(std::shared_ptr<std::vector<uint32_t>> std_vector_uint32_t_shared_ptr);
                AnyValue(std::shared_ptr<std::vector<float>> std_vector_float_shared_ptr);
                AnyValue(glm::vec3* const glm_vec3_pointer);
                AnyValue(glm::vec4* const glm_vec4_pointer);

                AnyValue(const std::string& type, const bool bool_value);
                AnyValue(const std::string& type, const char char_value);
                AnyValue(const std::string& type, const float float_value);
                AnyValue(const std::string& type, const double double_value);
                AnyValue(const std::string& type, const int32_t int32_t_value);
                AnyValue(const std::string& type, const uint32_t uint32_t_value);
                AnyValue(const std::string& type, bool* const bool_pointer);
                AnyValue(const std::string& type, char* const char_pointer);
                AnyValue(const std::string& type, float* const float_pointer);
                AnyValue(const std::string& type, double* const double_pointer);
                AnyValue(const std::string& type, int32_t* const int32_t_pointer);
                AnyValue(const std::string& type, uint32_t* const uint32_t_pointer);
                AnyValue(const std::string& type, yli::ontology::Entity* const entity_pointer);
                AnyValue(const std::string& type, yli::ontology::Movable* const movable_pointer);
                AnyValue(const std::string& type, const yli::ontology::Movable* const const_movable_pointer);
                AnyValue(const std::string& type, yli::ontology::Universe* const universe_pointer);
                AnyValue(const std::string& type, yli::ontology::World* const world_pointer);
                AnyValue(const std::string& type, yli::ontology::Scene* const scene_pointer);
                AnyValue(const std::string& type, yli::ontology::Shader* const shader_pointer);
                AnyValue(const std::string& type, yli::ontology::Material* const material_pointer);
                AnyValue(const std::string& type, yli::ontology::Species* const species_pointer);
                AnyValue(const std::string& type, yli::ontology::Object* const object_pointer);
                AnyValue(const std::string& type, yli::ontology::Symbiosis* const symbiosis_pointer);
                AnyValue(const std::string& type, yli::ontology::SymbiontMaterial* const symbiont_material_pointer);
                AnyValue(const std::string& type, yli::ontology::SymbiontSpecies* const symbiont_species_pointer);
                AnyValue(const std::string& type, yli::ontology::Holobiont* const holobiont_pointer);
                AnyValue(const std::string& type, yli::ontology::Biont* const biont_pointer);
                AnyValue(const std::string& type, yli::ontology::Font2D* const font2D_pointer);
                AnyValue(const std::string& type, yli::ontology::Text2D* const text2D_pointer);
                AnyValue(const std::string& type, yli::ontology::VectorFont* const vector_font_pointer);
                AnyValue(const std::string& type, yli::ontology::Glyph* const glyph_pointer);
                AnyValue(const std::string& type, yli::ontology::Text3D* const text3D_pointer);
                AnyValue(const std::string& type, yli::ontology::Console* const console_pointer);
                AnyValue(const std::string& type, yli::ontology::ComputeTask* const compute_task_pointer);
                AnyValue(const std::string& type, std::shared_ptr<yli::common::AnyValue> any_value_shared_ptr);
                AnyValue(const std::string& type, std::shared_ptr<yli::common::AnyStruct> any_struct_shared_ptr);
                AnyValue(const std::string& type, yli::common::SphericalCoordinatesStruct* const spherical_coordinates_struct_pointer);
                AnyValue(const std::string& type, std::string* const std_string_pointer);
                AnyValue(const std::string& type, const std::string* const const_std_string_pointer);
                AnyValue(const std::string& type, std::shared_ptr<std::vector<int8_t>> std_vector_int8_t_shared_ptr);
                AnyValue(const std::string& type, std::shared_ptr<std::vector<uint8_t>> std_vector_uint8_t_shared_ptr);
                AnyValue(const std::string& type, std::shared_ptr<std::vector<int16_t>> std_vector_int16_t_shared_ptr);
                AnyValue(const std::string& type, std::shared_ptr<std::vector<uint16_t>> std_vector_uint16_t_shared_ptr);
                AnyValue(const std::string& type, std::shared_ptr<std::vector<int32_t>> std_vector_int32_t_shared_ptr);
                AnyValue(const std::string& type, std::shared_ptr<std::vector<uint32_t>> std_vector_uint32_t_shared_ptr);
                AnyValue(const std::string& type, std::shared_ptr<std::vector<float>> std_vector_float_shared_ptr);
                AnyValue(const std::string& type, glm::vec3* const glm_vec3_pointer);
                AnyValue(const std::string& type, glm::vec4* const glm_vec3_pointer);

                yli::common::Datatype type;
                std::shared_ptr<yli::common::AnyValue> any_value_shared_ptr;
                std::shared_ptr<yli::common::AnyStruct> any_struct_shared_ptr;
                std::shared_ptr<std::vector<int8_t>> std_vector_int8_t_shared_ptr;
                std::shared_ptr<std::vector<uint8_t>> std_vector_uint8_t_shared_ptr;
                std::shared_ptr<std::vector<int16_t>> std_vector_int16_t_shared_ptr;
                std::shared_ptr<std::vector<uint16_t>> std_vector_uint16_t_shared_ptr;
                std::shared_ptr<std::vector<int32_t>> std_vector_int32_t_shared_ptr;
                std::shared_ptr<std::vector<uint32_t>> std_vector_uint32_t_shared_ptr;
                std::shared_ptr<std::vector<float>> std_vector_float_shared_ptr;

                union
                {
                    bool bool_value;
                    char char_value;
                    float float_value;
                    double double_value;
                    int32_t int32_t_value;
                    uint32_t uint32_t_value;
                    bool* bool_pointer;
                    char* char_pointer;
                    float* float_pointer;
                    double* double_pointer;
                    int32_t* int32_t_pointer;
                    uint32_t* uint32_t_pointer;
                    yli::ontology::Entity* entity_pointer;
                    yli::ontology::Movable* movable_pointer;
                    const yli::ontology::Movable* const_movable_pointer;
                    yli::ontology::Universe* universe_pointer;
                    yli::ontology::World* world_pointer;
                    yli::ontology::Scene* scene_pointer;
                    yli::ontology::Shader* shader_pointer;
                    yli::ontology::Material* material_pointer;
                    yli::ontology::Species* species_pointer;
                    yli::ontology::Object* object_pointer;
                    yli::ontology::Symbiosis* symbiosis_pointer;
                    yli::ontology::SymbiontMaterial* symbiont_material_pointer;
                    yli::ontology::SymbiontSpecies* symbiont_species_pointer;
                    yli::ontology::Holobiont* holobiont_pointer;
                    yli::ontology::Biont* biont_pointer;
                    yli::ontology::Font2D* font2D_pointer;
                    yli::ontology::Text2D* text2D_pointer;
                    yli::ontology::VectorFont* vector_font_pointer;
                    yli::ontology::Glyph* glyph_pointer;
                    yli::ontology::Text3D* text3D_pointer;
                    yli::ontology::Console* console_pointer;
                    yli::ontology::ComputeTask* compute_task_pointer;
                    yli::common::SphericalCoordinatesStruct* spherical_coordinates_struct_pointer;
                    std::string* std_string_pointer;
                    const std::string* const_std_string_pointer;
                    glm::vec3* glm_vec3_pointer;
                    glm::vec4* glm_vec4_pointer;
                };

            private:
                void set_default_values();
        };
    }
}

#endif
