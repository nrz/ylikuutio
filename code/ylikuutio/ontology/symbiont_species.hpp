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

#ifndef __YLIKUUTIO_ONTOLOGY_SYMBIONT_SPECIES_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_SYMBIONT_SPECIES_HPP_INCLUDED

#include "universe.hpp"
#include "scene.hpp"
#include "shader.hpp"
#include "species.hpp"
#include "species_or_glyph.hpp"
#include "symbiont_material.hpp"
#include "species_struct.hpp"
#include "code/ylikuutio/opengl/vboindexer.hpp"
#include "code/ylikuutio/render/render_templates.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::ontology
{
    class Entity;
    class Biont;
    class ParentModule;

    class SymbiontSpecies: public yli::ontology::Species
    {
        public:
            void bind_biont(yli::ontology::Biont* const biont);
            void unbind_biont(const std::size_t childID);

            std::size_t get_indices_size() const;
            GLint get_light_id() const;

            SymbiontSpecies(
                    yli::ontology::Universe* const universe,
                    const yli::ontology::SpeciesStruct& species_struct,
                    yli::ontology::ParentModule* const parent_module)
                : Species(universe, species_struct, parent_module)
            {
                // constructor.
                this->shader                   = species_struct.shader;
                this->vertices                 = species_struct.vertices;
                this->uvs                      = species_struct.uvs;
                this->normals                  = species_struct.normals;
                this->light_position           = species_struct.light_position;

                this->number_of_bionts = 0;
                this->type_string = "yli::ontology::SymbiontSpecies*";

                if (this->shader == nullptr)
                {
                    std::cerr << "ERROR: `SymbiontSpecies::SymbiontSpecies`: `this->shader` is `nullptr`!\n";
                    return;
                }

                const bool is_headless = (this->universe == nullptr ? true : this->universe->get_is_headless());

                if (!is_headless)
                {
                    // Get a handle for our buffers.
                    this->vertex_position_modelspace_id = glGetAttribLocation(this->shader->get_program_id(), "vertex_position_modelspace");
                    this->vertex_uv_id                  = glGetAttribLocation(this->shader->get_program_id(), "vertexUV");
                    this->vertex_normal_modelspace_id   = glGetAttribLocation(this->shader->get_program_id(), "vertex_normal_modelspace");

                    // Get a handle for our "LightPosition" uniform.
                    glUseProgram(this->shader->get_program_id());
                    this->light_id = glGetUniformLocation(this->shader->get_program_id(), "light_position_worldspace");

                    // water level.
                    GLint water_level_uniform_location = glGetUniformLocation(this->shader->get_program_id(), "water_level");

                    const yli::ontology::Scene* const scene = static_cast<yli::ontology::Scene*>(this->shader->get_parent());
                    glUniform1f(water_level_uniform_location, scene->get_water_level());
                }

                // Fill the index buffer.
                yli::opengl::indexVBO(
                        this->vertices,
                        this->uvs,
                        this->normals,
                        this->indices,
                        this->indexed_vertices,
                        this->indexed_uvs,
                        this->indexed_normals);

                if (!is_headless)
                {
                    // Load it into a VBO.
                    glGenBuffers(1, &this->vertexbuffer);
                    glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
                    glBufferData(GL_ARRAY_BUFFER, this->indexed_vertices.size() * sizeof(glm::vec3), &this->indexed_vertices[0], GL_STATIC_DRAW);

                    glGenBuffers(1, &this->uvbuffer);
                    glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
                    glBufferData(GL_ARRAY_BUFFER, this->indexed_uvs.size() * sizeof(glm::vec2), &this->indexed_uvs[0], GL_STATIC_DRAW);

                    glGenBuffers(1, &this->normalbuffer);
                    glBindBuffer(GL_ARRAY_BUFFER, this->normalbuffer);
                    glBufferData(GL_ARRAY_BUFFER, this->indexed_normals.size() * sizeof(glm::vec3), &this->indexed_normals[0], GL_STATIC_DRAW);

                    glGenBuffers(1, &this->elementbuffer);
                    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->elementbuffer);
                    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(uint32_t), &this->indices[0] , GL_STATIC_DRAW);
                }

                // TODO: Compute the vertex graph of this `SymbiontSpecies` to enable object vertex modification!

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::SymbiontSpecies*";
            }

            SymbiontSpecies(const SymbiontSpecies&) = delete;            // Delete copy constructor.
            yli::ontology::SymbiontSpecies& operator=(const SymbiontSpecies&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~SymbiontSpecies();

            template<class T1, class T2>
                friend void yli::render::render_children(const std::vector<T1>& child_pointer_vector);

        private:
            glm::vec3 light_position; // light position.

            template<class T1>
                friend void yli::ontology::render_species_or_glyph(T1 species_or_glyph_pointer);

            void bind_to_parent();

            // this method renders all `Object`s of this `SymbiontSpecies`.
            void render();

            std::vector<yli::ontology::Biont*> biont_pointer_vector;
            std::queue<std::size_t> free_biontID_queue;
            std::size_t number_of_bionts;

            yli::ontology::Shader* shader; // pointer to `Shader` (not a parent!).

            std::string model_file_format; // type of the model file, eg. `"bmp"`.
            std::string model_filename;    // filename of the model file.
    };
}

#endif
