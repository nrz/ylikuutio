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

#ifndef PI
#define PI 3.14159265359f
#endif

#include "gpgpu_test.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/pipeline.hpp"
#include "code/ylikuutio/ontology/compute_task.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/pipeline_struct.hpp"
#include "code/ylikuutio/ontology/compute_task_struct.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <iomanip>    // std::setfill, std::setw
#include <ios>        // std::defaultfloat, std::dec, std::fixed, std::hex, std::ios
#include <iostream>   // std::cout, std::cin, std::cerr
#include <sstream>    // std::istringstream, std::ostringstream, std::stringstream
#include <string>     // std::string

namespace yli
{
    namespace ontology
    {
        class Entity;
    }
}

namespace gpgpu_test
{
    yli::ontology::Entity* GpgpuTestApplication::create_gpgpu_test_scene()
    {
        // GPGPU test `Scene` begins here.
        std::cout << "Creating yli::ontology::Entity* gpgpu_test_scene_entity ...\n";
        yli::ontology::SceneStruct scene_struct;
        yli::ontology::Entity* const gpgpu_test_scene_entity = this->entity_factory.create_scene(scene_struct);
        std::cout << "Creating yli::ontology::Scene* gpgpu_test_scene ...\n";
        yli::ontology::Scene* const gpgpu_test_scene = dynamic_cast<yli::ontology::Scene*>(gpgpu_test_scene_entity);

        if (gpgpu_test_scene == nullptr)
        {
            std::cerr << "Failed to create `Scene`.\n";
            return nullptr;
        }

        gpgpu_test_scene->set_turbo_factor(5.0f);
        gpgpu_test_scene->set_twin_turbo_factor(100.0f);

        // Create the pipeline, store it in `identity_pipeline`.
        yli::ontology::PipelineStruct identity_pipeline_struct;
        identity_pipeline_struct.parent = gpgpu_test_scene;
        identity_pipeline_struct.vertex_shader = "identity.vert";
        identity_pipeline_struct.fragment_shader = "identity.frag";

        std::cout << "Creating yli::ontology::Entity* identity_pipeline_entity ...\n";
        yli::ontology::Entity* const identity_pipeline_entity = this->entity_factory.create_pipeline(identity_pipeline_struct);
        std::cout << "Creating yli::ontology::Pipeline* identity_pipeline ...\n";
        yli::ontology::Pipeline* const identity_pipeline = dynamic_cast<yli::ontology::Pipeline*>(identity_pipeline_entity);

        if (identity_pipeline == nullptr)
        {
            std::cerr << "Failed to create identity `Pipeline`.\n";
            return nullptr;
        }

        yli::ontology::ComputeTaskStruct identity_pipeline_png_compute_task_struct;
        identity_pipeline_png_compute_task_struct.texture_file_format = "png";
        identity_pipeline_png_compute_task_struct.texture_filename = "numbers_123456_black_and_white.png";
        identity_pipeline_png_compute_task_struct.output_filename = "gpgpu_identity_output.data";
        identity_pipeline_png_compute_task_struct.parent = identity_pipeline;
        identity_pipeline_png_compute_task_struct.texture_width = 512;
        identity_pipeline_png_compute_task_struct.texture_height = 512;

        std::cout << "Creating yli::ontology::Entity* identity_pipeline_png_compute_task_entity ...\n";
        yli::ontology::Entity* const identity_pipeline_png_compute_task_entity = this->entity_factory.create_compute_task(identity_pipeline_png_compute_task_struct);
        std::cout << "Creating yli::ontology::ComputeTask* identity_pipeline_png_compute_task ...\n";
        yli::ontology::ComputeTask* const identity_pipeline_png_compute_task = dynamic_cast<yli::ontology::ComputeTask*>(identity_pipeline_png_compute_task_entity);

        if (identity_pipeline_png_compute_task == nullptr)
        {
            std::cerr << "Failed to create identity BMP `ComputeTask`.\n";
            return nullptr;
        }

        yli::ontology::ComputeTaskStruct identity_pipeline_csv_unsigned_short_compute_task_struct;
        identity_pipeline_csv_unsigned_short_compute_task_struct.texture_file_format = "csv";
        identity_pipeline_csv_unsigned_short_compute_task_struct.texture_filename = "some_finnish_railway_stations_unsigned_integer_with_fill.csv";
        identity_pipeline_csv_unsigned_short_compute_task_struct.output_filename = "gpgpu_identity_output_unsigned_short_with_fill.data";
        identity_pipeline_csv_unsigned_short_compute_task_struct.parent = identity_pipeline;
        identity_pipeline_csv_unsigned_short_compute_task_struct.format = GL_RED;
        identity_pipeline_csv_unsigned_short_compute_task_struct.internal_format = GL_R16;
        identity_pipeline_csv_unsigned_short_compute_task_struct.type = GL_UNSIGNED_SHORT;
        identity_pipeline_csv_unsigned_short_compute_task_struct.should_save_intermediate_results = true;
        identity_pipeline_csv_unsigned_short_compute_task_struct.should_flip_texture = false;

        std::cout << "Creating yli::ontology::Entity* identity_pipeline_csv_unsigned_short_compute_task_entity ...\n";
        yli::ontology::Entity* const identity_pipeline_csv_unsigned_short_compute_task_entity = this->entity_factory.create_compute_task(identity_pipeline_csv_unsigned_short_compute_task_struct);
        std::cout << "Creating yli::ontology::ComputeTask* identity_pipeline_csv_unsigned_short_compute_task ...\n";
        yli::ontology::ComputeTask* const identity_pipeline_csv_unsigned_short_compute_task = dynamic_cast<yli::ontology::ComputeTask*>(identity_pipeline_csv_unsigned_short_compute_task_entity);

        if (identity_pipeline_csv_unsigned_short_compute_task == nullptr)
        {
            std::cerr << "Failed to create identity CSV `ComputeTask`.\n";
            return nullptr;
        }

        // Create the pipeline, store it in `sobel_pipeline`.
        yli::ontology::PipelineStruct sobel_pipeline_struct;
        sobel_pipeline_struct.parent = gpgpu_test_scene;
        sobel_pipeline_struct.vertex_shader = "identity.vert";
        sobel_pipeline_struct.fragment_shader = "sobel_gradient_magnitude.frag";

        std::cout << "Creating yli::ontology::Entity* sobel_pipeline_entity ...\n";
        yli::ontology::Entity* const sobel_pipeline_entity = this->entity_factory.create_pipeline(sobel_pipeline_struct);
        std::cout << "Creating yli::ontology::Pipeline* sobel_pipeline ...\n";
        yli::ontology::Pipeline* const sobel_pipeline = dynamic_cast<yli::ontology::Pipeline*>(sobel_pipeline_entity);

        if (sobel_pipeline == nullptr)
        {
            std::cerr << "Failed to create Sobel `Pipeline`.\n";
            return nullptr;
        }

        yli::ontology::ComputeTaskStruct sobel_pipeline_compute_task_struct;
        sobel_pipeline_compute_task_struct.texture_file_format = "png";
        sobel_pipeline_compute_task_struct.texture_filename = "numbers_123456_black_and_white.png";
        sobel_pipeline_compute_task_struct.output_filename = "gpgpu_sobel_output.data";
        sobel_pipeline_compute_task_struct.parent = sobel_pipeline;
        sobel_pipeline_compute_task_struct.n_max_iterations = 5;
        sobel_pipeline_compute_task_struct.texture_width = 512;
        sobel_pipeline_compute_task_struct.texture_height = 512;
        sobel_pipeline_compute_task_struct.should_save_intermediate_results = true;

        std::cout << "Creating yli::ontology::Entity* sobel_pipeline_compute_task_entity ...\n";
        yli::ontology::Entity* const sobel_pipeline_compute_task_entity = this->entity_factory.create_compute_task(sobel_pipeline_compute_task_struct);
        std::cout << "Creating yli::ontology::ComputeTask* sobel_pipeline_compute_task ...\n";
        yli::ontology::ComputeTask* const sobel_pipeline_compute_task = dynamic_cast<yli::ontology::ComputeTask*>(sobel_pipeline_compute_task_entity);

        if (sobel_pipeline_compute_task == nullptr)
        {
            std::cerr << "Failed to create Sobel `ComputeTask`.\n";
            return nullptr;
        }

        // Create the pipeline, store it in `go_west_pipeline`.
        yli::ontology::PipelineStruct go_west_pipeline_struct;
        go_west_pipeline_struct.parent = gpgpu_test_scene;
        go_west_pipeline_struct.vertex_shader = "identity.vert";
        go_west_pipeline_struct.fragment_shader = "go_west.frag";

        std::cout << "Creating yli::ontology::Entity* go_west_pipeline_entity ...\n";
        yli::ontology::Entity* const go_west_pipeline_entity = this->entity_factory.create_pipeline(go_west_pipeline_struct);
        std::cout << "Creating yli::ontology::Pipeline* go_west_pipeline ...\n";
        yli::ontology::Pipeline* const go_west_pipeline = dynamic_cast<yli::ontology::Pipeline*>(go_west_pipeline_entity);

        if (go_west_pipeline == nullptr)
        {
            std::cerr << "Failed to create Go West `Pipeline`.\n";
            return nullptr;
        }

        yli::ontology::ComputeTaskStruct go_west_pipeline_compute_task_struct;
        go_west_pipeline_compute_task_struct.texture_file_format = "png";
        go_west_pipeline_compute_task_struct.texture_filename = "numbers_123456_black_and_white.png";
        go_west_pipeline_compute_task_struct.output_filename = "gpgpu_go_west_output.data";
        go_west_pipeline_compute_task_struct.parent = go_west_pipeline;
        go_west_pipeline_compute_task_struct.n_max_iterations = 256;
        go_west_pipeline_compute_task_struct.texture_width = 512;
        go_west_pipeline_compute_task_struct.texture_height = 512;
        go_west_pipeline_compute_task_struct.should_save_intermediate_results = true;

        std::cout << "Creating yli::ontology::Entity* go_west_pipeline_compute_task_entity ...\n";
        yli::ontology::Entity* const go_west_pipeline_compute_task_entity = this->entity_factory.create_compute_task(go_west_pipeline_compute_task_struct);
        std::cout << "Creating yli::ontology::ComputeTask* go_west_pipeline_compute_task ...\n";
        yli::ontology::ComputeTask* const go_west_pipeline_compute_task = dynamic_cast<yli::ontology::ComputeTask*>(go_west_pipeline_compute_task_entity);

        if (go_west_pipeline_compute_task == nullptr)
        {
            std::cerr << "Failed to create Go West `ComputeTask`.\n";
            return nullptr;
        }

        // Create the pipeline, store it in `vanish_west_pipeline`.
        yli::ontology::PipelineStruct vanish_west_pipeline_struct;
        vanish_west_pipeline_struct.parent = gpgpu_test_scene;
        vanish_west_pipeline_struct.vertex_shader = "identity.vert";
        vanish_west_pipeline_struct.fragment_shader = "vanish_west.frag";

        std::cout << "Creating yli::ontology::Entity* vanish_west_pipeline_entity ...\n";
        yli::ontology::Entity* const vanish_west_pipeline_entity = this->entity_factory.create_pipeline(vanish_west_pipeline_struct);
        std::cout << "Creating yli::ontology::Pipeline* vanish_west_pipeline ...\n";
        yli::ontology::Pipeline* const vanish_west_pipeline = dynamic_cast<yli::ontology::Pipeline*>(vanish_west_pipeline_entity);

        if (vanish_west_pipeline == nullptr)
        {
            std::cerr << "Failed to create Vanish West `Pipeline`.\n";
            return nullptr;
        }

        yli::ontology::ComputeTaskStruct vanish_west_pipeline_compute_task_struct;
        vanish_west_pipeline_compute_task_struct.texture_file_format = "png";
        vanish_west_pipeline_compute_task_struct.texture_filename = "numbers_123456_black_and_white.png";
        vanish_west_pipeline_compute_task_struct.output_filename = "gpgpu_vanish_west_output.data";
        vanish_west_pipeline_compute_task_struct.parent = vanish_west_pipeline;
        vanish_west_pipeline_compute_task_struct.n_max_iterations = 256;
        vanish_west_pipeline_compute_task_struct.texture_width = 512;
        vanish_west_pipeline_compute_task_struct.texture_height = 512;
        vanish_west_pipeline_compute_task_struct.should_save_intermediate_results = true;

        std::cout << "Creating yli::ontology::Entity* vanish_west_pipeline_compute_task_entity ...\n";
        yli::ontology::Entity* const vanish_west_pipeline_compute_task_entity = this->entity_factory.create_compute_task(vanish_west_pipeline_compute_task_struct);
        std::cout << "Creating yli::ontology::ComputeTask* vanish_west_pipeline_compute_task ...\n";
        yli::ontology::ComputeTask* const vanish_west_pipeline_compute_task = dynamic_cast<yli::ontology::ComputeTask*>(vanish_west_pipeline_compute_task_entity);

        if (vanish_west_pipeline_compute_task == nullptr)
        {
            std::cerr << "Failed to create Vanish West `ComputeTask`.\n";
            return nullptr;
        }

        // Create the pipeline, store it in `floyd_warshall_pipeline`.
        yli::ontology::PipelineStruct floyd_warshall_pipeline_struct;
        floyd_warshall_pipeline_struct.parent = gpgpu_test_scene;
        floyd_warshall_pipeline_struct.vertex_shader = "identity.vert";
        floyd_warshall_pipeline_struct.fragment_shader = "floyd_warshall.frag";

        std::cout << "Creating yli::ontology::Entity* floyd_warshall_pipeline_entity ...\n";
        yli::ontology::Entity* const floyd_warshall_pipeline_entity = this->entity_factory.create_pipeline(floyd_warshall_pipeline_struct);
        std::cout << "Creating yli::ontology::Pipeline* floyd_warshall_pipeline ...\n";
        yli::ontology::Pipeline* const floyd_warshall_pipeline = dynamic_cast<yli::ontology::Pipeline*>(floyd_warshall_pipeline_entity);

        if (floyd_warshall_pipeline == nullptr)
        {
            std::cerr << "Failed to create Floyd-Warshall `Pipeline`.\n";
            return nullptr;
        }

        yli::ontology::ComputeTaskStruct floyd_warshall_pipeline_csv_unsigned_short_compute_task_struct;
        floyd_warshall_pipeline_csv_unsigned_short_compute_task_struct.texture_file_format = "csv";
        floyd_warshall_pipeline_csv_unsigned_short_compute_task_struct.texture_filename = "more_finnish_railway_stations_unsigned_integer.csv";
        floyd_warshall_pipeline_csv_unsigned_short_compute_task_struct.output_filename = "gpgpu_floyd_warshall_output_unsigned_short.data";
        floyd_warshall_pipeline_csv_unsigned_short_compute_task_struct.parent = floyd_warshall_pipeline;
        floyd_warshall_pipeline_csv_unsigned_short_compute_task_struct.n_max_iterations = 32;
        floyd_warshall_pipeline_csv_unsigned_short_compute_task_struct.format = GL_RED;
        floyd_warshall_pipeline_csv_unsigned_short_compute_task_struct.internal_format = GL_R16;
        floyd_warshall_pipeline_csv_unsigned_short_compute_task_struct.type = GL_UNSIGNED_SHORT;
        floyd_warshall_pipeline_csv_unsigned_short_compute_task_struct.should_save_intermediate_results = true;
        floyd_warshall_pipeline_csv_unsigned_short_compute_task_struct.should_flip_texture = false;

        std::cout << "Creating yli::ontology::Entity* floyd_warshall_pipeline_csv_unsigned_short_compute_task_entity ...\n";
        yli::ontology::Entity* const floyd_warshall_pipeline_csv_unsigned_short_compute_task_entity = this->entity_factory.create_compute_task(floyd_warshall_pipeline_csv_unsigned_short_compute_task_struct);
        std::cout << "Creating yli::ontology::ComputeTask* floyd_warshall_pipeline_csv_unsigned_short_compute_task ...\n";
        yli::ontology::ComputeTask* const floyd_warshall_pipeline_csv_unsigned_short_compute_task = dynamic_cast<yli::ontology::ComputeTask*>(floyd_warshall_pipeline_csv_unsigned_short_compute_task_entity);

        if (floyd_warshall_pipeline_csv_unsigned_short_compute_task == nullptr)
        {
            std::cerr << "Failed to create Floyd-Warshall CSV unsigned short `ComputeTask`.\n";
            return nullptr;
        }

        yli::ontology::ComputeTaskStruct floyd_warshall_pipeline_csv_float_compute_task_struct;
        floyd_warshall_pipeline_csv_float_compute_task_struct.texture_file_format = "csv";
        floyd_warshall_pipeline_csv_float_compute_task_struct.texture_filename = "more_finnish_railway_stations_unsigned_integer.csv";
        floyd_warshall_pipeline_csv_float_compute_task_struct.output_filename = "gpgpu_floyd_warshall_output_float.data";
        floyd_warshall_pipeline_csv_float_compute_task_struct.parent = floyd_warshall_pipeline;
        floyd_warshall_pipeline_csv_float_compute_task_struct.n_max_iterations = 32;
        floyd_warshall_pipeline_csv_float_compute_task_struct.format = GL_RED;
        floyd_warshall_pipeline_csv_float_compute_task_struct.internal_format = GL_R32F;
        floyd_warshall_pipeline_csv_float_compute_task_struct.type = GL_FLOAT;
        floyd_warshall_pipeline_csv_float_compute_task_struct.should_save_intermediate_results = true;
        floyd_warshall_pipeline_csv_float_compute_task_struct.should_flip_texture = false;

        std::cout << "Creating yli::ontology::Entity* floyd_warshall_pipeline_csv_float_compute_task_entity ...\n";
        yli::ontology::Entity* const floyd_warshall_pipeline_csv_float_compute_task_entity = this->entity_factory.create_compute_task(floyd_warshall_pipeline_csv_float_compute_task_struct);
        std::cout << "Creating yli::ontology::ComputeTask* floyd_warshall_pipeline_csv_float_compute_task ...\n";
        yli::ontology::ComputeTask* const floyd_warshall_pipeline_csv_float_compute_task = dynamic_cast<yli::ontology::ComputeTask*>(floyd_warshall_pipeline_csv_float_compute_task_entity);

        if (floyd_warshall_pipeline_csv_float_compute_task == nullptr)
        {
            std::cerr << "Failed to create Floyd-Warshall CSV float `ComputeTask`.\n";
            return nullptr;
        }

        GLenum error;

        while (true)
        {
            error = glGetError();

            if (error == GL_NO_ERROR)
            {
                break;
            }

            std::stringstream opengl_error_stringstream;
            opengl_error_stringstream << "OpenGL error: 0x" << std::setfill('0') << std::setw(4) << std::hex << error << "\n";
            std::cout << opengl_error_stringstream.str();
        }

        return gpgpu_test_scene_entity;
    }
}
