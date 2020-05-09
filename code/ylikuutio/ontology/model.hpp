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

#ifndef __MODEL_HPP_INCLUDED
#define __MODEL_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "parent_module.hpp"
#include "species_or_glyph.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::ontology
{
    class Universe;
    class Object;
    class Chunk;

    class Model: public yli::ontology::Entity
    {
        public:
            // constructor.
            Model(
                    yli::ontology::Universe* const universe,
                    const bool opengl_in_use,
                    yli::ontology::ParentModule* const parent_module)
                : Entity(universe),
                child(parent_module, this),
                parent_of_objects(this)
            {
                // constructor.

                // Initialize class members with some dummy values.
                this->lightID                      = 0;
                this->vertex_position_modelspace_id = 0;
                this->vertex_uv_id                   = 0;
                this->vertex_normal_modelspaceID   = 0;
                this->vertexbuffer                 = 0;
                this->uvbuffer                     = 0;
                this->normalbuffer                 = 0;
                this->elementbuffer                = 0;
                this->initial_rotate_angle         = 0.0f;
                this->initial_rotate_vector        = glm::vec3(0.0f, 1.0f, 1.0f);

                this->opengl_in_use = opengl_in_use;

                // `yli::ontology::Entity` member variables begin here.
                // Descendant classes of `yli::ontology::Model` need to set the value of `type_string`!
                // Descendant classes of `yli::ontology::Model` need to set the value of `can_be_erased`!
                this->type_string = "yli::ontology::Model*";
            }

            Model(const Model&) = delete;            // Delete copy constructor.
            Model &operator=(const Model&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~Model();

            yli::ontology::Entity* get_parent() const override;
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            std::size_t get_number_of_vertices() const;
            const std::vector<glm::vec3>& get_vertices() const;
            const std::vector<glm::vec2>& get_uvs() const;
            const std::vector<glm::vec3>& get_normals() const;
            const std::vector<uint32_t>& get_indices() const;

            GLint get_vertex_position_modelspace_id() const;
            GLint get_vertex_uv_id() const;
            GLint get_vertex_normal_modelspaceID() const;

            uint32_t get_vertexbuffer() const;
            uint32_t get_uvbuffer() const;
            uint32_t get_normalbuffer() const;
            uint32_t get_elementbuffer() const;

            void store_vertex_position_modelspaceID(const GLint vertex_position_modelspace_id);
            void store_vertexUVID(const GLint vertex_uv_id);
            void store_vertex_normal_modelspaceID(const GLint vertex_normal_modelspaceID);

            template<class T1>
                friend void yli::ontology::render_species_or_glyph(T1 species_or_glyph_pointer);

        protected:
            yli::ontology::ChildModule child;

        public:
            yli::ontology::ParentModule parent_of_objects;

        protected:
            float initial_rotate_angle;              // initial rotate angle.
            glm::vec3 initial_rotate_vector;         // initial rotate vector.

            std::string color_channel;               // color channel in use: `"red"`, `"green"`, `"blue"`, `"mean"` or `"all"`.
            glm::vec3 light_position;                // light position.

            GLint lightID;                           // light ID, returned by `glGetUniformLocation(programID, "light_position_worldspace");`.

            std::string triangulation_type;

            GLint vertex_position_modelspace_id;
            GLint vertex_uv_id;
            GLint vertex_normal_modelspaceID;

            std::vector<glm::vec3> vertices;         // vertices of the `Model`.
            std::vector<glm::vec2> uvs;              // UVs of the `Model`.
            std::vector<glm::vec3> normals;          // normals of the `Model`.

            std::vector<uint32_t> indices;           // the deleted vertices will be reused (though it is not required, if there's enough memory).
            std::vector<glm::vec3> indexed_vertices;
            std::vector<glm::vec2> indexed_uvs;
            std::vector<glm::vec3> indexed_normals;

            uint32_t vertexbuffer;
            uint32_t uvbuffer;
            uint32_t normalbuffer;
            uint32_t elementbuffer;

            bool opengl_in_use;
    };
}

#endif
