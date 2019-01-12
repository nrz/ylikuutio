#ifndef __SYMBIONT_SPECIES_HPP_INCLUDED
#define __SYMBIONT_SPECIES_HPP_INCLUDED

#include "scene.hpp"
#include "shader.hpp"
#include "species.hpp"
#include "species_or_glyph.hpp"
#include "symbiont_material.hpp"
#include "species_struct.hpp"
#include "render_templates.hpp"
#include "code/ylikuutio/opengl/vboindexer.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

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

namespace yli
{
    namespace ontology
    {
        class Entity;
        class Universe;
        class Biont;

        class SymbiontSpecies: public yli::ontology::Species
        {
            public:
                void bind_biont(yli::ontology::Biont* const biont);
                void unbind_biont(const std::size_t childID);

                // destructor.
                virtual ~SymbiontSpecies();

                std::size_t get_indices_size() const;
                uint32_t get_lightID() const;

                // constructor.
                SymbiontSpecies(yli::ontology::Universe* const universe, const SpeciesStruct& species_struct)
                    : Species(universe, species_struct)
                {
                    // constructor.
                    this->shader                   = species_struct.shader;
                    this->symbiont_material_parent = species_struct.symbiont_material;
                    this->vertices                 = species_struct.vertices;
                    this->uvs                      = species_struct.uvs;
                    this->normals                  = species_struct.normals;
                    this->light_position           = species_struct.light_position;

                    // get `childID` from `SymbiontMaterial` and set pointer to this `SymbiontSpecies`.
                    this->bind_to_parent();

                    this->number_of_bionts = 0;
                    this->child_vector_pointers_vector.push_back(&this->biont_pointer_vector);
                    this->type_string = "yli::ontology::SymbiontSpecies*";

                    if (this->shader == nullptr)
                    {
                        std::cerr << "ERROR: `SymbiontSpecies::SymbiontSpecies`: `this->shader` is `nullptr`!\n";
                        return;
                    }

                    // Get a handle for our buffers.
                    this->vertex_position_modelspaceID = glGetAttribLocation(this->shader->get_programID(), "vertexPosition_modelspace");
                    this->vertexUVID                   = glGetAttribLocation(this->shader->get_programID(), "vertexUV");
                    this->vertex_normal_modelspaceID   = glGetAttribLocation(this->shader->get_programID(), "vertexNormal_modelspace");

                    // Get a handle for our "LightPosition" uniform.
                    glUseProgram(this->shader->get_programID());
                    this->lightID = glGetUniformLocation(this->shader->get_programID(), "LightPosition_worldspace");

                    // water level.
                    uint32_t water_level_uniform_location = glGetUniformLocation(this->shader->get_programID(), "water_level");

                    const yli::ontology::Scene* const scene = static_cast<yli::ontology::Scene*>(this->shader->get_parent());
                    glUniform1f(water_level_uniform_location, scene->get_water_level());

                    // Fill the index buffer.
                    yli::opengl::indexVBO(
                            this->vertices,
                            this->uvs,
                            this->normals,
                            this->indices,
                            this->indexed_vertices,
                            this->indexed_uvs,
                            this->indexed_normals);

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

                    // TODO: Compute the vertex graph of this `SymbiontSpecies` to enable object vertex modification!

                    // `yli::ontology::Entity` member variables begin here.
                    this->type_string = "yli::ontology::SymbiontSpecies*";
                }

                yli::ontology::Entity* get_parent() const override;

            private:
                glm::vec3 light_position;                // light position.

                template<class T1>
                    friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);
                template<class T1>
                    friend void yli::ontology::render_species_or_glyph(T1 species_or_glyph_pointer);
                template<class T1>
                    friend void yli::ontology::render_children(const std::vector<T1>& child_pointer_vector);

                void bind_to_parent();

                // this method renders all `Object`s of this `SymbiontSpecies`.
                void render();

                std::vector<yli::ontology::Biont*> biont_pointer_vector;
                std::queue<std::size_t> free_biontID_queue;
                std::size_t number_of_bionts;

                yli::ontology::SymbiontMaterial* symbiont_material_parent; // pointer to `SymbiontMaterial`.
                yli::ontology::Shader* shader;           // pointer to `Shader`.

                std::string model_file_format;        // type of the model file, eg. `"bmp"`.
                std::string model_filename;           // filename of the model file.
        };
    }
}

#endif
