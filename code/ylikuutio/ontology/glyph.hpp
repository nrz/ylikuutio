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

#ifndef __GLYPH_HPP_INCLUDED
#define __GLYPH_HPP_INCLUDED

#include "universe.hpp"
#include "species_or_glyph.hpp"
#include "model.hpp"
#include "glyph_struct.hpp"
#include "gl_attrib_locations.hpp"
#include "render_templates.hpp"
#include "code/ylikuutio/triangulation/triangulate_polygons_struct.hpp"
#include "code/ylikuutio/triangulation/polygon_triangulation.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <queue>    // std::queue
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace ontology
    {
        class VectorFont;
        class Object;

        class Glyph: public yli::ontology::Model
        {
            public:
                // destructor.
                // `Glyph`s should be destroyed only by destroying the entire `VectorFont`.
                virtual ~Glyph();

                yli::ontology::Entity* get_parent() const override;

                const char* get_unicode_char_pointer() const;

                friend class VectorFont;
                template<class T1>
                    friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);
                template<class T1>
                    friend void yli::ontology::render_species_or_glyph(T1 species_or_glyph_pointer);
                template<class T1>
                    friend void yli::ontology::render_children(const std::vector<T1>& child_pointer_vector);

            private:
                Glyph(const yli::ontology::GlyphStruct& glyph_struct)
                    : Model(glyph_struct.universe, glyph_struct.opengl_in_use)
                {
                    // constructor.
                    this->parent               = glyph_struct.parent;
                    this->glyph_vertex_data    = glyph_struct.glyph_vertex_data;
                    this->glyph_name_pointer   = glyph_struct.glyph_name_pointer;
                    this->unicode_char_pointer = glyph_struct.unicode_char_pointer;
                    this->light_position       = glyph_struct.light_position;

                    // get `childID` from `VectorFont` and set pointer to this `Glyph`.
                    this->bind_to_parent();

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

                    if (!is_headless)
                    {
                        // Get a handle for our buffers.
                        yli::ontology::store_gl_attrib_locations(glyph_struct.shader_pointer, this);
                    }

                    // TODO: triangulate the vertex data!

                    // TODO: load the vertex data the same way as in `yli::ontology::Species::Species(yli::ontology::SpeciesStruct species_struct)`!

                    // `yli::ontology::Entity` member variables begin here.
                    // `yli::ontology::Model` constructor takes care of `child_vector_pointers_vector`.
                    this->type_string = "yli::ontology::Glyph*";
                }

                Glyph(const Glyph&) = delete;            // Delete copy constructor.
                Glyph &operator=(const Glyph&) = delete; // Delete copy assignment.

                void bind_to_parent();

                // this method renders all `Object`s of this `Glyph`.
                void render();

                yli::ontology::VectorFont* parent; // pointer to the `VectorFont`.

                std::vector<std::vector<glm::vec2>>* glyph_vertex_data;
                const char* glyph_name_pointer;    // we need only a pointer, because glyphs are always created by the `VectorFont` constructor.
                const char* unicode_char_pointer;  // we need only a pointer, because glyphs are always created by the `VectorFont` constructor.
        };
    }
}

#endif
