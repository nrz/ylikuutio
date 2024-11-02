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

#ifndef YLIKUUTIO_ONTOLOGY_GLYPH_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_GLYPH_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "apprentice_module.hpp"
#include "generic_master_module.hpp"
#include "mesh_module.hpp"

// Include GLM
#ifndef GLM_GLM_HPP_INCLUDED
#define GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <vector>   // std::vector

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
    class GenericParentModule;
    class GenericMasterModule;
    class Universe;
    class Scene;
    class Pipeline;
    class VectorFont;
    class GlyphObject;
    struct GlyphStruct;

    class Glyph final : public Entity
    {
        private:
            Glyph(
                    yli::core::Application& application,
                    Universe& universe,
                    const GlyphStruct& glyph_struct,
                    GenericParentModule* const vector_font_parent_module,
                    GenericMasterModule* const material_master_module);

            // `Glyph`s should be destroyed only by destroying the entire `VectorFont`.
            ~Glyph() = default;

        public:
            Entity* get_parent() const override;

            const char* get_unicode_char_pointer() const;

            friend class VectorFont;

        private:
            Glyph(const Glyph&) = delete;            // Delete copy constructor.
            Glyph& operator=(const Glyph&) = delete; // Delete copy assignment.

        public:
            Scene* get_scene() const override;

            Pipeline* get_pipeline() const;

            template<typename ApprenticeType>
                GenericMasterModule* get_generic_master_module() = delete;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

        public:
            void render(const Scene* const target_scene);

            GenericMasterModule* get_renderables_container();

            template<typename T1, std::size_t DataSize>
                friend class yli::memory::MemoryStorage;

        private:
            ChildModule child_of_vector_font;
            ApprenticeModule apprentice_of_material;
            GenericMasterModule master_of_glyph_objects;

        public:
            MeshModule mesh;

        private:
            std::vector<std::vector<glm::vec2>>* glyph_vertex_data { nullptr };
            const char* glyph_name_pointer                         { nullptr };
            const char* unicode_char_pointer                       { nullptr };
    };

    template<>
        inline GenericMasterModule* Glyph::get_generic_master_module<GlyphObject>()
        {
            return &this->master_of_glyph_objects;
        }
}

#endif
