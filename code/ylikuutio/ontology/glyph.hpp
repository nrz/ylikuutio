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

#ifndef __YLIKUUTIO_ONTOLOGY_GLYPH_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_GLYPH_HPP_INCLUDED

#include "child_module.hpp"
#include "universe.hpp"
#include "model.hpp"
#include "glyph_struct.hpp"
#include "gl_attrib_locations.hpp"
#include "code/ylikuutio/render/render_templates.hpp"
#include "code/ylikuutio/triangulation/triangulate_polygons_struct.hpp"
#include "code/ylikuutio/triangulation/polygon_triangulation.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::ontology
{
    class Entity;
    class VectorFont;
    class Object;
    class ParentModule;

    class Glyph: public yli::ontology::Model
    {
        public:
            // destructor.
            // `Glyph`s should be destroyed only by destroying the entire `VectorFont`.
            virtual ~Glyph();

            yli::ontology::Entity* get_parent() const override;

            const char* get_unicode_char_pointer() const;

            friend class yli::ontology::VectorFont;
            template<class T1, class T2>
                friend void yli::render::render_children(const std::vector<T1>& child_pointer_vector);

        private:
            Glyph(const yli::ontology::GlyphStruct& glyph_struct, yli::ontology::ParentModule* const vector_font_parent_module)
                : Model(glyph_struct.universe, glyph_struct, glyph_struct.opengl_in_use),
                child_of_vector_font(vector_font_parent_module, this),
                glyph_vertex_data    { glyph_struct.glyph_vertex_data },
                glyph_name_pointer   { glyph_struct.glyph_name_pointer },
                unicode_char_pointer { glyph_struct.unicode_char_pointer }
            {
                // constructor.

                // TODO: implement triangulation of `Glyph` objects!
                yli::triangulation::TriangulatePolygonsStruct triangulate_polygons_struct;
                triangulate_polygons_struct.input_vertices = this->glyph_vertex_data;
                bool triangulating_result = yli::triangulation::triangulate_polygons(
                        triangulate_polygons_struct,
                        this->vertices,
                        this->uvs,
                        this->normals);

                if (!triangulating_result)
                {
                    std::cerr << "triangulation failed!\n";
                }
                const bool is_headless = (this->universe == nullptr ? true : this->universe->get_is_headless());

                if (!is_headless && glyph_struct.shader != nullptr)
                {
                    // Get a handle for our buffers.
                    yli::ontology::store_gl_attrib_locations(glyph_struct.shader, this);
                }

                // TODO: triangulate the vertex data!

                // TODO: load the vertex data the same way as in `yli::ontology::Species::Species(yli::ontology::SpeciesStruct species_struct)`!

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::Glyph*";
            }

            Glyph(const Glyph&) = delete;            // Delete copy constructor.
            Glyph& operator=(const Glyph&) = delete; // Delete copy assignment.

            // this method renders all `Object`s of this `Glyph`.
            void render();

            std::vector<std::vector<glm::vec2>>* glyph_vertex_data;
            const char* glyph_name_pointer;    // we need only a pointer, because glyphs are always created by the `VectorFont` constructor.
            const char* unicode_char_pointer;  // we need only a pointer, because glyphs are always created by the `VectorFont` constructor.

            yli::ontology::ChildModule child_of_vector_font;
    };
}

#endif
