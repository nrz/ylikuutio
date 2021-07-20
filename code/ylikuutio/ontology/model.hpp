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

#ifndef __YLIKUUTIO_ONTOLOGY_MODEL_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_MODEL_HPP_INCLUDED

#include "entity.hpp"
#include "parent_module.hpp"
#include "model_struct.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.
#include "code/ylikuutio/render/render_species_or_glyph.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace yli::ontology
{
    class Universe;
    class Object;
    class Chunk;

    class Model: public yli::ontology::Entity
    {
        public:
            Model(
                    yli::ontology::Universe* const universe,
                    const yli::ontology::ModelStruct& model_struct,
                    const bool opengl_in_use)
                : Entity(universe, model_struct),
                parent_of_objects(this, &this->registry, "objects"),
                light_position { model_struct.light_position },
                opengl_in_use { opengl_in_use }
            {
                // constructor.

                // `yli::ontology::Entity` member variables begin here.
                // Descendant classes of `yli::ontology::Model` need to set the value of `type_string`!
                // Descendant classes of `yli::ontology::Model` need to set the value of `can_be_erased`!
                this->type_string = "yli::ontology::Model*";
            }

            Model(const Model&) = delete;            // Delete copy constructor.
            Model& operator=(const Model&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~Model();

            std::size_t get_number_of_vertices() const;
            const std::vector<glm::vec3>& get_vertices() const;
            const std::vector<glm::vec2>& get_uvs() const;
            const std::vector<glm::vec3>& get_normals() const;
            const std::vector<uint32_t>& get_indices() const;

            GLint get_vertex_position_modelspace_id() const;
            GLint get_vertex_uv_id() const;
            GLint get_vertex_normal_modelspace_id() const;

            GLuint get_vertexbuffer() const;
            GLuint get_uvbuffer() const;
            GLuint get_normalbuffer() const;
            GLuint get_elementbuffer() const;

            void set_vertex_position_modelspace_id(const GLint vertex_position_modelspace_id);
            void set_vertex_uv_id(const GLint vertex_uv_id);
            void set_vertex_normal_modelspace_id(const GLint vertex_normal_modelspace_id);

            template<class T1, class T2, class T3>
                friend void yli::render::render_species_or_glyph(T1 species_or_glyph_pointer);

        public:
            yli::ontology::ParentModule parent_of_objects;

        protected:
            glm::vec3 light_position;                // light position.

            GLint light_id { 0 };                    // light ID, returned by `glGetUniformLocation(program_id, "light_position_worldspace");`. Dummy value.

            GLint vertex_position_modelspace_id { 0 }; // dummy value.
            GLint vertex_uv_id                  { 0 }; // dummy value.
            GLint vertex_normal_modelspace_id   { 0 }; // dummy value.

            std::vector<glm::vec3> vertices;         // vertices of the `Model`.
            std::vector<glm::vec2> uvs;              // UVs of the `Model`.
            std::vector<glm::vec3> normals;          // normals of the `Model`.

            std::vector<uint32_t> indices;           // the deleted vertices will be reused (though it is not required, if there's enough memory).
            std::vector<glm::vec3> indexed_vertices;
            std::vector<glm::vec2> indexed_uvs;
            std::vector<glm::vec3> indexed_normals;

            GLuint vertexbuffer  { 0 }; // dummy value.
            GLuint uvbuffer      { 0 }; // dummy value.
            GLuint normalbuffer  { 0 }; // dummy value.
            GLuint elementbuffer { 0 }; // dummy value.

            bool opengl_in_use;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;
    };
}

#endif
