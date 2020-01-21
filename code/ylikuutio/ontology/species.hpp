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

#ifndef __SPECIES_HPP_INCLUDED
#define __SPECIES_HPP_INCLUDED

#include "species_or_glyph.hpp"
#include "model.hpp"
#include "universe.hpp"
#include "scene.hpp"
#include "shader.hpp"
#include "material.hpp"
#include "ground_level.hpp"
#include "species_struct.hpp"
#include "render_templates.hpp"
#include "code/ylikuutio/load/species_loader.hpp"
#include "code/ylikuutio/load/species_loader_struct.hpp"
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
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace ontology
    {
        class Entity;
        class Material;
        class Object;

        class Species: public yli::ontology::Model
        {
            public:
                void bind_Object(yli::ontology::Object* const object);
                void unbind_Object(const std::size_t childID);

                // this method sets pointer to this `Species` to `nullptr`, sets `parent` according to the input, and requests a new `childID` from the new `Material`.
                void bind_to_new_parent(yli::ontology::Material* const new_parent);
                void bind_to_new_parent(yli::ontology::Entity* const new_parent) override;

                // constructor.
                Species(yli::ontology::Universe* const universe, const yli::ontology::SpeciesStruct& species_struct)
                    : Model(universe, species_struct.opengl_in_use)
                {
                    // constructor.
                    this->is_terrain          = species_struct.is_terrain;
                    this->is_symbiont_species = species_struct.is_symbiont_species;
                    this->planet_radius       = species_struct.planet_radius;
                    this->divisor             = species_struct.divisor;
                    this->model_file_format   = species_struct.model_file_format;
                    this->model_filename      = species_struct.model_filename;
                    this->color_channel       = species_struct.color_channel;
                    this->light_position      = species_struct.light_position;
                    this->latitude            = species_struct.latitude;
                    this->longitude           = species_struct.longitude;
                    this->material_parent     = species_struct.material;
                    this->mesh_i              = species_struct.mesh_i;
                    this->x_step              = species_struct.x_step;
                    this->z_step              = species_struct.z_step;
                    this->triangulation_type  = species_struct.triangulation_type;

                    this->image_width         = 0;
                    this->image_height        = 0;

                    this->use_real_texture_coordinates = species_struct.use_real_texture_coordinates;

                    if (!this->is_symbiont_species)
                    {
                        // get `childID` from `Material` and set pointer to this `Species`.
                        this->bind_to_parent();

                        const bool is_headless = (this->universe == nullptr ? true : this->universe->get_is_headless());

                        if (!is_headless && this->opengl_in_use)
                        {
                            // Get a handle for our buffers.
                            this->vertex_position_modelspaceID = glGetAttribLocation(species_struct.shader->get_programID(), "vertex_position_modelspace");
                            this->vertexUVID = glGetAttribLocation(species_struct.shader->get_programID(), "vertexUV");
                            this->vertex_normal_modelspaceID = glGetAttribLocation(species_struct.shader->get_programID(), "vertex_normal_modelspace");

                            // Get a handle for our "LightPosition" uniform.
                            glUseProgram(species_struct.shader->get_programID());
                            this->lightID = glGetUniformLocation(species_struct.shader->get_programID(), "light_position_worldspace");
                        }

                        if (this->is_terrain)
                        {
                            // set terrain `Species` pointer so that it points to this `Species`.
                            // currently there can be only one terrain `Species` in each `Scene` (used in collision detection).
                            yli::ontology::Material* const material = this->material_parent;

                            if (material != nullptr)
                            {
                                material->set_terrain_species(this);
                            }
                        }

                        if (!is_headless && this->opengl_in_use)
                        {
                            // water level.
                            GLint water_level_uniform_location = glGetUniformLocation(species_struct.shader->get_programID(), "water_level");
                            glUniform1f(water_level_uniform_location, species_struct.scene->get_water_level());
                        }

                        yli::load::SpeciesLoaderStruct species_loader_struct;
                        species_loader_struct.model_filename               = this->model_filename;
                        species_loader_struct.model_file_format            = this->model_file_format;
                        species_loader_struct.latitude                     = this->latitude;
                        species_loader_struct.longitude                    = this->longitude;
                        species_loader_struct.planet_radius                = this->planet_radius;
                        species_loader_struct.divisor                      = this->divisor;
                        species_loader_struct.color_channel                = this->color_channel;
                        species_loader_struct.mesh_i                       = this->mesh_i;
                        species_loader_struct.x_step                       = this->x_step;
                        species_loader_struct.z_step                       = this->z_step;
                        species_loader_struct.image_width_pointer          = &this->image_width;
                        species_loader_struct.image_height_pointer         = &this->image_height;
                        species_loader_struct.triangulation_type           = this->triangulation_type;
                        species_loader_struct.is_headless                  = is_headless;
                        species_loader_struct.opengl_in_use                = this->opengl_in_use;
                        species_loader_struct.use_real_texture_coordinates = this->use_real_texture_coordinates;

                        const bool is_debug_mode = true;

                        yli::load::load_Species(
                                species_loader_struct,
                                this->vertices,
                                this->uvs,
                                this->normals,
                                this->indices,
                                this->indexed_vertices,
                                this->indexed_uvs,
                                this->indexed_normals,
                                &this->vertexbuffer,
                                &this->uvbuffer,
                                &this->normalbuffer,
                                &this->elementbuffer,
                                this->opengl_in_use,
                                is_debug_mode);

                        // TODO: Compute the graph of this object type to enable object vertex modification!

                        // `yli::ontology::Entity` member variables begin here.
                        this->type_string = "yli::ontology::Species*";
                        this->can_be_erased = true;
                    }
                }

                Species(const Species&) = delete;            // Delete copy constructor.
                Species &operator=(const Species&) = delete; // Delete copy assignment.

                // destructor.
                virtual ~Species();

                yli::ontology::Entity* get_parent() const override;

                std::size_t get_x_step() const;
                std::size_t get_z_step() const;
                std::size_t get_image_width() const;
                std::size_t get_image_height() const;

                const std::string& get_model_file_format() const;

                bool is_terrain;                           // worlds currently do not rotate nor translate.
                float planet_radius;                      // radius of sea level in kilometers. used only for worlds.
                float divisor;                           // value by which SRTM values are divided to convert them to kilometers.

                std::string color_channel;               // color channel in use: `"red"`, `"green"`, `"blue"`, `"mean"` or `"all"`.
                glm::vec3 light_position;                // light position.

                template<class T1>
                    friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);
                template<class T1>
                    friend void yli::ontology::render_species_or_glyph(T1 species_or_glyph_pointer);
                template<class T1>
                    friend void yli::ontology::render_children(const std::vector<T1>& child_pointer_vector);

            private:
                void bind_to_parent();

                // this method renders all `Object`s of this `Species`.
                void render() override;

                yli::ontology::Material* material_parent; // pointer to `Material`.

                bool is_symbiont_species;

                std::string model_file_format;            // type of the model file, eg. `"bmp"`.
                std::string model_filename;               // filename of the model file.

                double latitude;                          // for SRTM.
                double longitude;                         // for SRTM.

                std::size_t mesh_i;

                std::size_t x_step;
                std::size_t z_step;

                std::string triangulation_type;

                std::size_t image_width;
                std::size_t image_height;

                bool use_real_texture_coordinates;
        };
    }
}

#endif
