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

#ifndef __YLIKUUTIO_ONTOLOGY_SPECIES_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_SPECIES_HPP_INCLUDED

#include "child_module.hpp"
#include "model.hpp"
#include "universe.hpp"
#include "scene.hpp"
#include "shader.hpp"
#include "species_struct.hpp"
#include "code/ylikuutio/load/species_loader.hpp"
#include "code/ylikuutio/load/species_loader_struct.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.
#include "code/ylikuutio/render/render_templates.hpp"

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::ontology
{
    class Entity;
    class Material;
    class ParentModule;

    class Species: public yli::ontology::Model
    {
        public:
            // this method sets pointer to this `Species` to `nullptr`, sets `parent` according to the input, and requests a new `childID` from the new `Material`.
            void bind_to_new_material_parent(yli::ontology::Material* const new_parent);
            void bind_to_new_parent(yli::ontology::Entity* const new_parent) override;

            Species(
                    yli::ontology::Universe* const universe,
                    const yli::ontology::SpeciesStruct& species_struct,
                    yli::ontology::ParentModule* const material_parent_module)
                : Model(universe, species_struct, species_struct.opengl_in_use),
                child_of_material(material_parent_module, this),
                planet_radius                { species_struct.planet_radius },
                divisor                      { species_struct.divisor },
                model_file_format            { species_struct.model_file_format },
                model_filename               { species_struct.model_filename },
                color_channel                { species_struct.color_channel },
                triangulation_type           { species_struct.triangulation_type },
                latitude                     { species_struct.latitude },
                longitude                    { species_struct.longitude },
                mesh_i                       { species_struct.mesh_i },
                x_step                       { species_struct.x_step },
                z_step                       { species_struct.z_step },
                is_terrain                   { species_struct.is_terrain },
                is_symbiont_species          { species_struct.is_symbiont_species },
                use_real_texture_coordinates { species_struct.use_real_texture_coordinates }
            {
                // constructor.

                if (!this->is_symbiont_species)
                {
                    const bool is_headless = (this->universe == nullptr ? true : this->universe->get_is_headless());

                    if (!is_headless && this->opengl_in_use)
                    {
                        // Get a handle for our buffers.
                        this->vertex_position_modelspace_id = glGetAttribLocation(species_struct.shader->get_program_id(), "vertex_position_modelspace");
                        this->vertex_uv_id = glGetAttribLocation(species_struct.shader->get_program_id(), "vertexUV");
                        this->vertex_normal_modelspace_id = glGetAttribLocation(species_struct.shader->get_program_id(), "vertex_normal_modelspace");

                        // Get a handle for our "LightPosition" uniform.
                        glUseProgram(species_struct.shader->get_program_id());
                        this->light_id = glGetUniformLocation(species_struct.shader->get_program_id(), "light_position_worldspace");
                    }

                    if (!is_headless && this->opengl_in_use)
                    {
                        // water level.
                        GLint water_level_uniform_location = glGetUniformLocation(species_struct.shader->get_program_id(), "water_level");
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

                    yli::load::load_species(
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
            Species& operator=(const Species&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~Species();

            yli::ontology::Entity* get_parent() const override;

            uint32_t get_x_step() const;
            uint32_t get_z_step() const;
            uint32_t get_image_width() const;
            uint32_t get_image_height() const;

            const std::string& get_model_file_format() const;

            // this method renders all `Object`s of this `Species`.
            void render();

            template<class T1, class T2>
                friend void yli::render::render_children(const std::vector<T1>& child_pointer_vector);

        private:
            yli::ontology::ChildModule child_of_material;

        public:
            float planet_radius;           // Radius of sea level in kilometers. Used only for terrains.
            float divisor;                 // Value by which SRTM values are divided to convert them to kilometers.

        private:
            std::string model_file_format; // Type of the model file, eg. `"png"`.
            std::string model_filename;    // Filename of the model file.
            std::string color_channel;     // Color channel in use: `"red"`, `"green"`, `"blue"`, `"mean"` or `"all"`.
            std::string triangulation_type;

            float latitude;                // For SRTM.
            float longitude;               // For SRTM.

            uint32_t mesh_i;

            uint32_t x_step;
            uint32_t z_step;

            uint32_t image_width  { 0 };
            uint32_t image_height { 0 };

            bool is_terrain;               // Terrains do not rotate nor translate.
            bool is_symbiont_species;
            bool use_real_texture_coordinates;
    };
}

#endif
