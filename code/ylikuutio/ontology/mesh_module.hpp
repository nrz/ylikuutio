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

#ifndef __YLIKUUTIO_ONTOLOGY_MESH_MODULE_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_MESH_MODULE_HPP_INCLUDED

#include "universe.hpp"
#include "scene.hpp"
#include "shader.hpp"
#include "model_struct.hpp"
#include "code/ylikuutio/load/model_loader.hpp"
#include "code/ylikuutio/load/model_loader_struct.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

#include <iostream>

namespace yli::ontology
{
    class MeshModule
    {
        public:
            MeshModule(
                    yli::ontology::Universe* const universe,
                    const yli::ontology::ModelStruct& model_struct)
                : model_filename { model_struct.model_filename },
                model_file_format { model_struct.model_file_format },
                color_channel { model_struct.color_channel },
                triangulation_type { model_struct.triangulation_type },
                planet_radius { model_struct.planet_radius },
                divisor { model_struct.divisor },
                latitude { model_struct.latitude },
                longitude { model_struct.longitude },
                mesh_i { model_struct.mesh_i },
                x_step { model_struct.x_step },
                z_step { model_struct.z_step },
                light_position { model_struct.light_position }
            {
                // constructor.

                // If software rendering is in use, the vertices, UVs, and normals can not be loaded into GPU memory,
                // but they can still be loaded into CPU memory to be used by the software rendering.
                const bool should_load_vertices_uvs_and_normals = (universe != nullptr &&
                        (universe->get_is_opengl_in_use() ||
                         universe->get_is_vulkan_in_use() ||
                         universe->get_is_software_rendering_in_use()));

                if (should_load_vertices_uvs_and_normals &&
                        universe->get_is_opengl_in_use() &&
                        model_struct.scene != nullptr &&
                        model_struct.shader != nullptr)
                {
                    // VAO.
                    glGenVertexArrays(1, &this->vao);

                    // Get a handle for our buffers.
                    this->vertex_position_modelspace_id = glGetAttribLocation(model_struct.shader->get_program_id(), "vertex_position_modelspace");
                    this->vertex_uv_id = glGetAttribLocation(model_struct.shader->get_program_id(), "vertexUV");
                    this->vertex_normal_modelspace_id = glGetAttribLocation(model_struct.shader->get_program_id(), "vertex_normal_modelspace");

                    // Get a handle for our "LightPosition" uniform.
                    glUseProgram(model_struct.shader->get_program_id());
                    this->light_id = glGetUniformLocation(model_struct.shader->get_program_id(), "light_position_worldspace");

                    // water level.
                    GLint water_level_uniform_location = glGetUniformLocation(model_struct.shader->get_program_id(), "water_level");
                    glUniform1f(water_level_uniform_location, model_struct.scene->get_water_level());

                    yli::load::ModelLoaderStruct model_loader_struct;
                    model_loader_struct.model_struct.model_filename               = this->model_filename;
                    model_loader_struct.model_struct.model_file_format            = this->model_file_format;
                    model_loader_struct.model_struct.color_channel                = this->color_channel;
                    model_loader_struct.model_struct.triangulation_type           = this->triangulation_type;
                    model_loader_struct.model_struct.planet_radius                = this->planet_radius;
                    model_loader_struct.model_struct.divisor                      = this->divisor;
                    model_loader_struct.model_struct.latitude                     = this->latitude;
                    model_loader_struct.model_struct.longitude                    = this->longitude;
                    model_loader_struct.model_struct.mesh_i                       = this->mesh_i;
                    model_loader_struct.model_struct.x_step                       = this->x_step;
                    model_loader_struct.model_struct.z_step                       = this->z_step;
                    model_loader_struct.model_struct.scene                        = model_struct.scene;
                    model_loader_struct.model_struct.shader                       = model_struct.shader;
                    model_loader_struct.model_struct.material                     = model_struct.material;
                    model_loader_struct.model_struct.symbiont_material            = model_struct.symbiont_material;
                    model_loader_struct.model_struct.use_real_texture_coordinates = this->use_real_texture_coordinates;
                    model_loader_struct.image_width_pointer                       = &this->image_width;
                    model_loader_struct.image_height_pointer                      = &this->image_height;

                    const bool is_debug_mode = true;

                    yli::load::load_model(
                            model_loader_struct,
                            this->vertices,
                            this->uvs,
                            this->normals,
                            this->indices,
                            this->indexed_vertices,
                            this->indexed_uvs,
                            this->indexed_normals,
                            this->vao,
                            this->vertexbuffer,
                            this->uvbuffer,
                            this->normalbuffer,
                            this->elementbuffer,
                            universe->get_graphics_api_backend(),
                            is_debug_mode);

                    this->are_opengl_buffers_initialized = true;
                }
                else if (should_load_vertices_uvs_and_normals && universe->get_is_opengl_in_use())
                {
                    if (model_struct.scene == nullptr)
                    {
                        std::cerr << "ERROR: `MeshModule::MeshModule`: `this->scene` is `nullptr`!\n";
                    }

                    if (model_struct.shader == nullptr)
                    {
                        std::cerr << "ERROR: `MeshModule::MeshModule`: `this->shader` is `nullptr`!\n";
                    }

                    // Do not load model.
                }
            }

            MeshModule(const MeshModule&) = delete;            // Delete copy constructor.
            MeshModule& operator=(const MeshModule&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~MeshModule();

            std::size_t get_number_of_vertices() const;
            const std::vector<glm::vec3>& get_vertices() const;
            const std::vector<glm::vec2>& get_uvs() const;
            const std::vector<glm::vec3>& get_normals() const;
            const std::vector<uint32_t>& get_indices() const;

            std::size_t get_indices_size() const;

            GLint get_vertex_position_modelspace_id() const;
            GLint get_vertex_uv_id() const;
            GLint get_vertex_normal_modelspace_id() const;

            GLuint get_vao() const;
            GLuint get_vertexbuffer() const;
            GLuint get_uvbuffer() const;
            GLuint get_normalbuffer() const;
            GLuint get_elementbuffer() const;

            void set_vertex_position_modelspace_id(const GLint vertex_position_modelspace_id);
            void set_vertex_uv_id(const GLint vertex_uv_id);
            void set_vertex_normal_modelspace_id(const GLint vertex_normal_modelspace_id);

            std::string model_filename;    // Filename of the model file.
            std::string model_file_format; // Type of the model file. supported file formats so far:
            // `"png"`/`"PNG"` - PNG heightmap.
            // `"fbx"`/`"FBX"` - FBX model.
            // `"obj"`/`"OBJ"` - OBJ model.
            // `"srtm"`/`"SRTM"` - SRTM heightmap.
            // `"asc"`/`"ascii_grid"`/`"ASCII_grid"` - ASCII grid.

        private:
            std::string color_channel;    // Color channel to use for altitude data, for PNG model files.
            std::string triangulation_type { "bilinear_interpolation" }; // `"bilinear_interpolation"`, `"southwest_northeast_edges"`, `"southeast_northwest_edges"`.

        public:
            float planet_radius { NAN };  // Radius of sea level in kilometers. used only for terrains (planets and moons). `6371.0f` for Earth.

        private:
            float divisor       { 1.0f }; // Value by which SRTM values are divided to convert them to kilometers.
            float latitude      { 0.0f }; // In degrees, for SRTM model files.
            float longitude     { 0.0f }; // In degrees, for SRTM model files.
            uint32_t mesh_i     { 0 };    // For FBX.

        public:
            uint32_t x_step     { 1 };    // Step in x-dimension for input data (set to 1 to load all data points/measurements).
            uint32_t z_step     { 1 };    // Step in z-dimension for input data (set to 1 to load all data points/measurements).

            uint32_t image_width  { 0 };
            uint32_t image_height { 0 };

        private:
            std::vector<glm::vec3> vertices; // Vertices of the `MeshModule`.
            std::vector<glm::vec2> uvs;      // UVs of the `MeshModule`.
            std::vector<glm::vec3> normals;  // Normals of the `MeshModule`.

        public:
            glm::vec3 light_position { NAN, NAN, NAN };

            GLint light_id                      { 0 }; // Dummy value.
            GLint vertex_position_modelspace_id { 0 }; // Dummy value.
            GLint vertex_uv_id                  { 0 }; // Dummy value.
            GLint vertex_normal_modelspace_id   { 0 }; // Dummy value.

        private:
            std::vector<uint32_t> indices;
            std::vector<glm::vec3> indexed_vertices;
            std::vector<glm::vec2> indexed_uvs;
            std::vector<glm::vec3> indexed_normals;

            GLuint vao           { 0 }; // Dummy value.
            GLuint vertexbuffer  { 0 }; // Dummy value.
            GLuint uvbuffer      { 0 }; // Dummy value.
            GLuint normalbuffer  { 0 }; // Dummy value.
            GLuint elementbuffer { 0 }; // Dummy value.

            bool use_real_texture_coordinates { true };
            bool are_opengl_buffers_initialized { false };
    };
}

#endif
