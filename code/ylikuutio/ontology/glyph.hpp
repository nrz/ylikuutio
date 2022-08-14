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

#ifndef __YLIKUUTIO_ONTOLOGY_GLYPH_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_GLYPH_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "generic_master_module.hpp"
#include "mesh_module.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <vector>   // std::vector

namespace yli::ontology
{
    class GenericParentModule;
    class Universe;
    class Scene;
    class Object;
    class VectorFont;
    struct ModelStruct;

    class Glyph final : public yli::ontology::Entity
    {
        public:
            // destructor.
            // `Glyph`s should be destroyed only by destroying the entire `VectorFont`.
            virtual ~Glyph() = default;

            yli::ontology::Entity* get_parent() const override;

            const char* get_unicode_char_pointer() const;

            friend class yli::ontology::VectorFont;

        private:
            Glyph(
                    yli::ontology::Universe& universe,
                    const yli::ontology::ModelStruct& model_struct,
                    yli::ontology::GenericParentModule* const vector_font_parent_module);

            Glyph(const Glyph&) = delete;            // Delete copy constructor.
            Glyph& operator=(const Glyph&) = delete; // Delete copy assignment.

        public:
            yli::ontology::Scene* get_scene() const override;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

        public:
            void render(const yli::ontology::Scene* const target_scene);

            yli::ontology::GenericMasterModule* get_renderables_container();

        private:
            yli::ontology::ChildModule child_of_vector_font;
            yli::ontology::GenericMasterModule master_of_objects;

        public:
            yli::ontology::MeshModule mesh;

        private:
            std::vector<std::vector<glm::vec2>>* glyph_vertex_data { nullptr };
            const char* glyph_name_pointer                         { nullptr };
            const char* unicode_char_pointer                       { nullptr };
    };
}

#endif
