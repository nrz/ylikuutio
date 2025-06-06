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

#ifndef YLIKUUTIO_DATA_ANY_VALUE_HPP_INCLUDED
#define YLIKUUTIO_DATA_ANY_VALUE_HPP_INCLUDED

// Include GLM
#ifndef GLM_GLM_HPP_INCLUDED
#define GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <functional> // std::reference_wrapper
#include <optional> // std::optional
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
    class Pipeline;
    class Material;
    class Species;
    class Object;
    class Symbiosis;
    class Holobiont;
    class Font2d;
    class Text2d;
    class VectorFont;
    class Text3d;
    class Console;
    class ComputeTask;
}

namespace yli::data
{
    class AnyValue final
    {
        public:
            bool operator==(const yli::data::AnyValue& rhs) const noexcept;
            bool operator!=(const yli::data::AnyValue& rhs) const = default;
            yli::data::AnyValue& operator=(const yli::data::AnyValue& other) = default;
            std::string get_datatype() const noexcept;
            std::string get_string() const;
            const std::string& get_const_std_string_ref() const;
            yli::ontology::Entity& get_entity_ref() const;
            const yli::ontology::Entity& get_const_entity_ref() const;
            bool has_movable_ref() const;
            bool has_const_movable_ref() const;
            yli::ontology::Movable& get_movable_ref() const;
            const yli::ontology::Movable& get_const_movable_ref() const;
            bool set_new_value(const std::string& value_string);

            // copy constructor.
            AnyValue(const yli::data::AnyValue& original) = default;

            // constructor for optional `AnyValue`.
            explicit AnyValue(const std::optional<yli::data::AnyValue> original);

            // common constructors.

            AnyValue() = default;
            AnyValue(const std::string& type, const std::string& value_string); // This constructor takes also the value as a string.
            // Fundamental types.
            explicit AnyValue(const bool bool_value);
            explicit AnyValue(const char char_value);
            explicit AnyValue(const float float_value);
            explicit AnyValue(const double double_value);
            explicit AnyValue(const int32_t int32_t_value);
            explicit AnyValue(const uint32_t uint32_t_value);
            // Strings.
            explicit AnyValue(std::string& std_string_ref);
            explicit AnyValue(const std::string& const_std_string_ref);
            // Variable-size vectors.
            explicit AnyValue(std::vector<int8_t>& std_vector_int8_t_ref);
            explicit AnyValue(std::vector<uint8_t>& std_vector_uint8_t_ref);
            explicit AnyValue(std::vector<int16_t>& std_vector_int16_t_ref);
            explicit AnyValue(std::vector<uint16_t>& std_vector_uint16_t_ref);
            explicit AnyValue(std::vector<int32_t>& std_vector_int32_t_ref);
            explicit AnyValue(std::vector<uint32_t>& std_vector_uint32_t_ref);
            explicit AnyValue(std::vector<float>& std_vector_float_ref);
            // Fixed-size vectors.
            explicit AnyValue(glm::vec3& glm_vec3_ref);
            explicit AnyValue(const glm::vec3& const_glm_vec3_ref);
            explicit AnyValue(glm::vec4& glm_vec4_ref);
            explicit AnyValue(const glm::vec4& const_glm_vec4_ref);
            // Ontology.
            explicit AnyValue(yli::ontology::Entity& entity_ref);
            explicit AnyValue(yli::ontology::Movable& movable_ref);
            explicit AnyValue(const yli::ontology::Movable& const_movable_ref);
            explicit AnyValue(yli::ontology::Universe& universe_ref);
            explicit AnyValue(yli::ontology::Ecosystem& ecosystem_ref);
            explicit AnyValue(yli::ontology::Scene& scene_ref);
            explicit AnyValue(yli::ontology::Pipeline& pipeline_ref);
            explicit AnyValue(yli::ontology::Material& material_ref);
            explicit AnyValue(yli::ontology::Species& species_ref);
            explicit AnyValue(yli::ontology::Object& object_ref);
            explicit AnyValue(yli::ontology::Symbiosis& symbiosis_ref);
            explicit AnyValue(yli::ontology::Holobiont& holobiont_ref);
            explicit AnyValue(yli::ontology::Font2d& font_2d_ref);
            explicit AnyValue(yli::ontology::Text2d& text_2d_ref);
            explicit AnyValue(yli::ontology::VectorFont& vector_font_ref);
            explicit AnyValue(yli::ontology::Text3d& text_3d_ref);
            explicit AnyValue(yli::ontology::Console& console_ref);
            explicit AnyValue(yli::ontology::ComputeTask& compute_task_ref);

            std::variant<
                // Uninitialized state.
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
                // `yli::ontology` datatypes, 'entity' path.
                std::reference_wrapper<yli::ontology::Entity>,
                std::reference_wrapper<yli::ontology::Movable>,
                std::reference_wrapper<const yli::ontology::Movable>,
                // `yli::ontology` datatypes, 'universe' path.
                std::reference_wrapper<yli::ontology::Universe>,
                // `yli::ontology` datatypes, 'ecosystem' path.
                std::reference_wrapper<yli::ontology::Ecosystem>,
                // `yli::ontology` datatypes, 'simple' path.
                std::reference_wrapper<yli::ontology::Scene>,
                std::reference_wrapper<yli::ontology::Pipeline>,
                std::reference_wrapper<yli::ontology::Material>,
                std::reference_wrapper<yli::ontology::Species>,
                std::reference_wrapper<yli::ontology::Object>,
                // `yli::ontology` datatypes, 'heightmap' path.
                // TODO
                // `yli::ontology` datatypes, 'symbiont' path.
                std::reference_wrapper<yli::ontology::Symbiosis>,
                // `yli::ontology` datatypes, 'holobiont' path.
                std::reference_wrapper<yli::ontology::Holobiont>,
                // `yli::ontology` datatypes, 'shapeshifter' path.
                // TODO
                // `yli::ontology` datatypes, 'text 2D' path.
                std::reference_wrapper<yli::ontology::Font2d>,
                std::reference_wrapper<yli::ontology::Text2d>,
                // `yli::ontology` datatypes, 'text 3D' path.
                std::reference_wrapper<yli::ontology::VectorFont>,
                std::reference_wrapper<yli::ontology::Text3d>,
                // `yli::ontology` datatypes, 'console' path.
                std::reference_wrapper<yli::ontology::Console>,
                // `yli::ontology` datatypes, 'compute' path.
                std::reference_wrapper<yli::ontology::ComputeTask>> data;
    };
}

#endif
