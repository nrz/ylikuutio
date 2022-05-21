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
#include "universe.hpp"
#include "model_struct.hpp"
#include "gl_attrib_locations.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::ontology
{
    class GenericParentModule;
    class Scene;
    class Object;
    class VectorFont;

    class Glyph: public yli::ontology::Entity
    {
        public:
            // destructor.
            // `Glyph`s should be destroyed only by destroying the entire `VectorFont`.
            virtual ~Glyph();

            yli::ontology::Entity* get_parent() const override;

            const char* get_unicode_char_pointer() const;

            friend class yli::ontology::VectorFont;

        private:
            Glyph(
                    yli::ontology::Universe& universe,
                    const yli::ontology::ModelStruct& model_struct,
                    yli::ontology::GenericParentModule* const vector_font_parent_module)
                : Entity(universe, model_struct),
                child_of_vector_font(vector_font_parent_module, this),
                master_of_objects(this, &this->registry, "objects"),
                mesh(universe, model_struct),
                glyph_vertex_data    { model_struct.glyph_vertex_data },
                glyph_name_pointer   { model_struct.glyph_name_pointer },
                unicode_char_pointer { model_struct.unicode_char_pointer }
            {
                // constructor.

                // If software rendering is in use, the vertices and UVs can not be loaded into GPU memory,
                // but they can still be loaded into CPU memory to be used by the software rendering.
                const bool should_load_texture =
                    this->universe.get_is_opengl_in_use() ||
                    this->universe.get_is_vulkan_in_use() ||
                    this->universe.get_is_software_rendering_in_use();

                if (should_load_texture && model_struct.shader != nullptr)
                {
                    // Get a handle for our buffers.
                    yli::ontology::set_gl_attrib_locations(model_struct.shader, &this->mesh);
                }

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::Glyph*";
            }

            Glyph(const Glyph&) = delete;            // Delete copy constructor.
            Glyph& operator=(const Glyph&) = delete; // Delete copy assignment.

            yli::ontology::Scene* get_scene() const override;
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

        public:
            // this method renders all `Object`s of this `Glyph`.
            void render();

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
