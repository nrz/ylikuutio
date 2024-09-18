// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
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

#ifndef YLIKUUTIO_ONTOLOGY_VECTOR_FONT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_VECTOR_FONT_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "generic_parent_module.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include GLM
#ifndef GLM_GLM_HPP_INCLUDED
#define GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>       // std::size_t
#include <optional>      // std::optional
#include <stdint.h>      // uint32_t etc.
#include <string>        // std::string
#include <vector>        // std::vector
#include <unordered_map> // std::unordered_map

namespace yli::core
{
    class Application;
}

namespace yli::memory
{
    template<typename T1, std::size_t DataSize>
        class MemoryStorage;
}

namespace yli::ontology
{
    class Universe;
    class Scene;
    class Pipeline;
    class Material;
    class Glyph;
    struct VectorFontStruct;

    class VectorFont final : public Entity
    {
        public:
            // Set pointer to `vector_font` to `nullptr`, set parent according to the input,
            // and request a new childID from `new_parent`.
            static std::optional<yli::data::AnyValue> bind_to_new_material_parent(
                    VectorFont& vector_font,
                    Material& new_parent);

        private:
            VectorFont(
                    yli::core::Application& application,
                    Universe& universe,
                    const VectorFontStruct& vector_font_struct,
                    GenericParentModule* const material_parent_module);

            ~VectorFont() = default;

        public:
            VectorFont(const VectorFont&) = delete;            // Delete copy constructor.
            VectorFont& operator=(const VectorFont&) = delete; // Delete copy assignment.

            Entity* get_parent() const override;

            // This method returns a pointer to `Glyph` that matches the given `unicode_value`,
            // and `nullptr` if this `VectorFont` does not contain such a `Glyph`.
            Glyph* get_glyph_pointer(const int32_t unicode_value) const;

            GenericParentModule* get_generic_parent_module(const int type);

            // The rest fields are created in the constructor.

            template<typename T1, std::size_t DataSize>
                friend class yli::memory::MemoryStorage;

            ChildModule child_of_material;
            GenericParentModule parent_of_glyphs;
            GenericParentModule parent_of_text_3ds;

        public:
            Scene* get_scene() const override;
            Pipeline* get_pipeline() const;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

        public:
            // This method renders all `Glyph`s of this `VectorFont`.
            void render(const Scene* const target_scene);

        private:
            std::string font_file_format; // Type of the model file, eg. `"png"`.
            std::string font_filename;    // Filename of the model file.
            float vertex_scaling_factor;

            std::vector<std::vector<std::vector<glm::vec2>>> glyph_vertex_data;
            std::vector<std::vector<glm::vec2>> glyph_uv_data;
            std::vector<std::vector<glm::vec2>> glyph_normal_data;
            std::vector<std::string> glyph_names;
            std::vector<std::string> unicode_strings;

            std::unordered_map<int32_t, Glyph*> unicode_glyph_map;
    };
}

#endif
