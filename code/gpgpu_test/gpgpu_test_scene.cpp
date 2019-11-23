// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2019 Antti Nuortimo.
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

#include "gpgpu_test_scene.hpp"
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/shader.hpp"
#include "code/ylikuutio/ontology/compute_task.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/shader_struct.hpp"
#include "code/ylikuutio/ontology/compute_task_struct.hpp"
#include "code/ylikuutio/ontology/entity_factory.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <iomanip>    // std::setfill, std::setw
#include <iostream>   // std::cout, std::cin, std::cerr
#include <sstream>    // std::istringstream, std::ostringstream, std::stringstream
#include <string>     // std::string

namespace yli
{
    namespace ontology
    {
        class World;
        class Entity;
    }
}

namespace gpgpu_test
{
    yli::ontology::Entity* create_gpgpu_test_scene(yli::ontology::EntityFactory* entity_factory, yli::ontology::World* const world)
    {
        // GPGPU test `Scene` begins here.
        std::cout << "Creating yli::ontology::Entity* gpgpu_test_scene_entity ...\n";
        yli::ontology::SceneStruct scene_struct;
        scene_struct.world = world;
        yli::ontology::Entity* const gpgpu_test_scene_entity = entity_factory->create_Scene(scene_struct);
        std::cout << "Creating yli::ontology::Scene* gpgpu_test_scene ...\n";
        yli::ontology::Scene* const gpgpu_test_scene = dynamic_cast<yli::ontology::Scene*>(gpgpu_test_scene_entity);

        if (gpgpu_test_scene == nullptr)
        {
            std::cerr << "Failed to create `Scene`.\n";
            return nullptr;
        }

        gpgpu_test_scene->set_turbo_factor(5.0f);
        gpgpu_test_scene->set_twin_turbo_factor(100.0f);

        // Create the shader, store it in `identity_shader`.
        yli::ontology::ShaderStruct identity_shader_struct;
        identity_shader_struct.parent = gpgpu_test_scene;
        identity_shader_struct.vertex_shader = "identity.vert";
        identity_shader_struct.fragment_shader = "identity.frag";

        std::cout << "Creating yli::ontology::Entity* identity_shader_entity ...\n";
        yli::ontology::Entity* const identity_shader_entity = entity_factory->create_Shader(identity_shader_struct);
        std::cout << "Creating yli::ontology::Shader* identity_shader ...\n";
        yli::ontology::Shader* const identity_shader = dynamic_cast<yli::ontology::Shader*>(identity_shader_entity);

        if (identity_shader == nullptr)
        {
            std::cerr << "Failed to create identity `Shader`.\n";
            return nullptr;
        }

        yli::ontology::ComputeTaskStruct identity_shader_BMP_compute_task_struct;
        identity_shader_BMP_compute_task_struct.texture_file_format = "bmp";
        identity_shader_BMP_compute_task_struct.texture_filename = "numbers_123456_black_and_white.bmp";
        identity_shader_BMP_compute_task_struct.output_filename = "gpgpu_identity_output.data";
        identity_shader_BMP_compute_task_struct.parent = identity_shader;
        identity_shader_BMP_compute_task_struct.texture_width = 512;
        identity_shader_BMP_compute_task_struct.texture_height = 512;

        std::cout << "Creating yli::ontology::Entity* identity_shader_BMP_compute_task_entity ...\n";
        yli::ontology::Entity* const identity_shader_BMP_compute_task_entity = entity_factory->create_ComputeTask(identity_shader_BMP_compute_task_struct);
        std::cout << "Creating yli::ontology::ComputeTask* identity_shader_BMP_compute_task ...\n";
        yli::ontology::ComputeTask* const identity_shader_BMP_compute_task = dynamic_cast<yli::ontology::ComputeTask*>(identity_shader_BMP_compute_task_entity);

        if (identity_shader_BMP_compute_task == nullptr)
        {
            std::cerr << "Failed to create identity BMP `ComputeTask`.\n";
            return nullptr;
        }

        yli::ontology::ComputeTaskStruct identity_shader_CSV_unsigned_short_compute_task_struct;
        identity_shader_CSV_unsigned_short_compute_task_struct.texture_file_format = "csv";
        identity_shader_CSV_unsigned_short_compute_task_struct.texture_filename = "some_finnish_railway_stations_unsigned_integer_with_fill.csv";
        identity_shader_CSV_unsigned_short_compute_task_struct.output_filename = "gpgpu_identity_output_unsigned_short_with_fill.data";
        identity_shader_CSV_unsigned_short_compute_task_struct.parent = identity_shader;
        identity_shader_CSV_unsigned_short_compute_task_struct.format = GL_RED;
        identity_shader_CSV_unsigned_short_compute_task_struct.internal_format = GL_R16;
        identity_shader_CSV_unsigned_short_compute_task_struct.type = GL_UNSIGNED_SHORT;
        identity_shader_CSV_unsigned_short_compute_task_struct.should_ylikuutio_save_intermediate_results = true;
        identity_shader_CSV_unsigned_short_compute_task_struct.should_ylikuutio_flip_texture = false;

        std::cout << "Creating yli::ontology::Entity* identity_shader_CSV_unsigned_short_compute_task_entity ...\n";
        yli::ontology::Entity* const identity_shader_CSV_unsigned_short_compute_task_entity = entity_factory->create_ComputeTask(identity_shader_CSV_unsigned_short_compute_task_struct);
        std::cout << "Creating yli::ontology::ComputeTask* identity_shader_CSV_unsigned_short_compute_task ...\n";
        yli::ontology::ComputeTask* const identity_shader_CSV_unsigned_short_compute_task = dynamic_cast<yli::ontology::ComputeTask*>(identity_shader_CSV_unsigned_short_compute_task_entity);

        if (identity_shader_CSV_unsigned_short_compute_task == nullptr)
        {
            std::cerr << "Failed to create identity CSV `ComputeTask`.\n";
            return nullptr;
        }

        // Create the shader, store it in `sobel_shader`.
        yli::ontology::ShaderStruct sobel_shader_struct;
        sobel_shader_struct.parent = gpgpu_test_scene;
        sobel_shader_struct.vertex_shader = "identity.vert";
        sobel_shader_struct.fragment_shader = "sobel_gradient_magnitude.frag";

        std::cout << "Creating yli::ontology::Entity* sobel_shader_entity ...\n";
        yli::ontology::Entity* const sobel_shader_entity = entity_factory->create_Shader(sobel_shader_struct);
        std::cout << "Creating yli::ontology::Shader* sobel_shader ...\n";
        yli::ontology::Shader* const sobel_shader = dynamic_cast<yli::ontology::Shader*>(sobel_shader_entity);

        if (sobel_shader == nullptr)
        {
            std::cerr << "Failed to create Sobel `Shader`.\n";
            return nullptr;
        }

        yli::ontology::ComputeTaskStruct sobel_shader_compute_task_struct;
        sobel_shader_compute_task_struct.texture_file_format = "bmp";
        sobel_shader_compute_task_struct.texture_filename = "numbers_123456_black_and_white.bmp";
        sobel_shader_compute_task_struct.output_filename = "gpgpu_sobel_output.data";
        sobel_shader_compute_task_struct.parent = sobel_shader;
        sobel_shader_compute_task_struct.n_max_iterations = 5;
        sobel_shader_compute_task_struct.texture_width = 512;
        sobel_shader_compute_task_struct.texture_height = 512;
        sobel_shader_compute_task_struct.should_ylikuutio_save_intermediate_results = true;

        std::cout << "Creating yli::ontology::Entity* sobel_shader_compute_task_entity ...\n";
        yli::ontology::Entity* const sobel_shader_compute_task_entity = entity_factory->create_ComputeTask(sobel_shader_compute_task_struct);
        std::cout << "Creating yli::ontology::ComputeTask* sobel_shader_compute_task ...\n";
        yli::ontology::ComputeTask* const sobel_shader_compute_task = dynamic_cast<yli::ontology::ComputeTask*>(sobel_shader_compute_task_entity);

        if (sobel_shader_compute_task == nullptr)
        {
            std::cerr << "Failed to create Sobel `ComputeTask`.\n";
            return nullptr;
        }

        // Create the shader, store it in `go_west_shader`.
        yli::ontology::ShaderStruct go_west_shader_struct;
        go_west_shader_struct.parent = gpgpu_test_scene;
        go_west_shader_struct.vertex_shader = "identity.vert";
        go_west_shader_struct.fragment_shader = "go_west.frag";

        std::cout << "Creating yli::ontology::Entity* go_west_shader_entity ...\n";
        yli::ontology::Entity* const go_west_shader_entity = entity_factory->create_Shader(go_west_shader_struct);
        std::cout << "Creating yli::ontology::Shader* go_west_shader ...\n";
        yli::ontology::Shader* const go_west_shader = dynamic_cast<yli::ontology::Shader*>(go_west_shader_entity);

        if (go_west_shader == nullptr)
        {
            std::cerr << "Failed to create Go West `Shader`.\n";
            return nullptr;
        }

        yli::ontology::ComputeTaskStruct go_west_shader_compute_task_struct;
        go_west_shader_compute_task_struct.texture_file_format = "bmp";
        go_west_shader_compute_task_struct.texture_filename = "numbers_123456_black_and_white.bmp";
        go_west_shader_compute_task_struct.output_filename = "gpgpu_go_west_output.data";
        go_west_shader_compute_task_struct.parent = go_west_shader;
        go_west_shader_compute_task_struct.n_max_iterations = 256;
        go_west_shader_compute_task_struct.texture_width = 512;
        go_west_shader_compute_task_struct.texture_height = 512;
        go_west_shader_compute_task_struct.should_ylikuutio_save_intermediate_results = true;

        std::cout << "Creating yli::ontology::Entity* go_west_shader_compute_task_entity ...\n";
        yli::ontology::Entity* const go_west_shader_compute_task_entity = entity_factory->create_ComputeTask(go_west_shader_compute_task_struct);
        std::cout << "Creating yli::ontology::ComputeTask* go_west_shader_compute_task ...\n";
        yli::ontology::ComputeTask* const go_west_shader_compute_task = dynamic_cast<yli::ontology::ComputeTask*>(go_west_shader_compute_task_entity);

        if (go_west_shader_compute_task == nullptr)
        {
            std::cerr << "Failed to create Go West `ComputeTask`.\n";
            return nullptr;
        }

        // Create the shader, store it in `vanish_west_shader`.
        yli::ontology::ShaderStruct vanish_west_shader_struct;
        vanish_west_shader_struct.parent = gpgpu_test_scene;
        vanish_west_shader_struct.vertex_shader = "identity.vert";
        vanish_west_shader_struct.fragment_shader = "vanish_west.frag";

        std::cout << "Creating yli::ontology::Entity* vanish_west_shader_entity ...\n";
        yli::ontology::Entity* const vanish_west_shader_entity = entity_factory->create_Shader(vanish_west_shader_struct);
        std::cout << "Creating yli::ontology::Shader* vanish_west_shader ...\n";
        yli::ontology::Shader* const vanish_west_shader = dynamic_cast<yli::ontology::Shader*>(vanish_west_shader_entity);

        if (vanish_west_shader == nullptr)
        {
            std::cerr << "Failed to create Vanish West `Shader`.\n";
            return nullptr;
        }

        yli::ontology::ComputeTaskStruct vanish_west_shader_compute_task_struct;
        vanish_west_shader_compute_task_struct.texture_file_format = "bmp";
        vanish_west_shader_compute_task_struct.texture_filename = "numbers_123456_black_and_white.bmp";
        vanish_west_shader_compute_task_struct.output_filename = "gpgpu_vanish_west_output.data";
        vanish_west_shader_compute_task_struct.parent = vanish_west_shader;
        vanish_west_shader_compute_task_struct.n_max_iterations = 256;
        vanish_west_shader_compute_task_struct.texture_width = 512;
        vanish_west_shader_compute_task_struct.texture_height = 512;
        vanish_west_shader_compute_task_struct.should_ylikuutio_save_intermediate_results = true;

        std::cout << "Creating yli::ontology::Entity* vanish_west_shader_compute_task_entity ...\n";
        yli::ontology::Entity* const vanish_west_shader_compute_task_entity = entity_factory->create_ComputeTask(vanish_west_shader_compute_task_struct);
        std::cout << "Creating yli::ontology::ComputeTask* vanish_west_shader_compute_task ...\n";
        yli::ontology::ComputeTask* const vanish_west_shader_compute_task = dynamic_cast<yli::ontology::ComputeTask*>(vanish_west_shader_compute_task_entity);

        if (vanish_west_shader_compute_task == nullptr)
        {
            std::cerr << "Failed to create Vanish West `ComputeTask`.\n";
            return nullptr;
        }

        // Create the shader, store it in `floyd_warshall_shader`.
        yli::ontology::ShaderStruct floyd_warshall_shader_struct;
        floyd_warshall_shader_struct.parent = gpgpu_test_scene;
        floyd_warshall_shader_struct.vertex_shader = "identity.vert";
        floyd_warshall_shader_struct.fragment_shader = "floyd_warshall.frag";

        std::cout << "Creating yli::ontology::Entity* floyd_warshall_shader_entity ...\n";
        yli::ontology::Entity* const floyd_warshall_shader_entity = entity_factory->create_Shader(floyd_warshall_shader_struct);
        std::cout << "Creating yli::ontology::Shader* floyd_warshall_shader ...\n";
        yli::ontology::Shader* const floyd_warshall_shader = dynamic_cast<yli::ontology::Shader*>(floyd_warshall_shader_entity);

        if (floyd_warshall_shader == nullptr)
        {
            std::cerr << "Failed to create Floyd-Warshall `Shader`.\n";
            return nullptr;
        }

        yli::ontology::ComputeTaskStruct floyd_warshall_shader_CSV_unsigned_short_compute_task_struct;
        floyd_warshall_shader_CSV_unsigned_short_compute_task_struct.texture_file_format = "csv";
        floyd_warshall_shader_CSV_unsigned_short_compute_task_struct.texture_filename = "more_finnish_railway_stations_unsigned_integer.csv";
        floyd_warshall_shader_CSV_unsigned_short_compute_task_struct.output_filename = "gpgpu_floyd_warshall_output_unsigned_short.data";
        floyd_warshall_shader_CSV_unsigned_short_compute_task_struct.parent = floyd_warshall_shader;
        floyd_warshall_shader_CSV_unsigned_short_compute_task_struct.n_max_iterations = 32;
        floyd_warshall_shader_CSV_unsigned_short_compute_task_struct.format = GL_RED;
        floyd_warshall_shader_CSV_unsigned_short_compute_task_struct.internal_format = GL_R16;
        floyd_warshall_shader_CSV_unsigned_short_compute_task_struct.type = GL_UNSIGNED_SHORT;
        floyd_warshall_shader_CSV_unsigned_short_compute_task_struct.should_ylikuutio_save_intermediate_results = true;
        floyd_warshall_shader_CSV_unsigned_short_compute_task_struct.should_ylikuutio_flip_texture = false;

        std::cout << "Creating yli::ontology::Entity* floyd_warshall_shader_CSV_unsigned_short_compute_task_entity ...\n";
        yli::ontology::Entity* const floyd_warshall_shader_CSV_unsigned_short_compute_task_entity = entity_factory->create_ComputeTask(floyd_warshall_shader_CSV_unsigned_short_compute_task_struct);
        std::cout << "Creating yli::ontology::ComputeTask* floyd_warshall_shader_CSV_unsigned_short_compute_task ...\n";
        yli::ontology::ComputeTask* const floyd_warshall_shader_CSV_unsigned_short_compute_task = dynamic_cast<yli::ontology::ComputeTask*>(floyd_warshall_shader_CSV_unsigned_short_compute_task_entity);

        if (floyd_warshall_shader_CSV_unsigned_short_compute_task == nullptr)
        {
            std::cerr << "Failed to create Floyd-Warshall CSV unsigned short `ComputeTask`.\n";
            return nullptr;
        }

        yli::ontology::ComputeTaskStruct floyd_warshall_shader_CSV_float_compute_task_struct;
        floyd_warshall_shader_CSV_float_compute_task_struct.texture_file_format = "csv";
        floyd_warshall_shader_CSV_float_compute_task_struct.texture_filename = "more_finnish_railway_stations_unsigned_integer.csv";
        floyd_warshall_shader_CSV_float_compute_task_struct.output_filename = "gpgpu_floyd_warshall_output_float.data";
        floyd_warshall_shader_CSV_float_compute_task_struct.parent = floyd_warshall_shader;
        floyd_warshall_shader_CSV_float_compute_task_struct.n_max_iterations = 32;
        floyd_warshall_shader_CSV_float_compute_task_struct.format = GL_RED;
        floyd_warshall_shader_CSV_float_compute_task_struct.internal_format = GL_R32F;
        floyd_warshall_shader_CSV_float_compute_task_struct.type = GL_FLOAT;
        floyd_warshall_shader_CSV_float_compute_task_struct.should_ylikuutio_save_intermediate_results = true;
        floyd_warshall_shader_CSV_float_compute_task_struct.should_ylikuutio_flip_texture = false;

        std::cout << "Creating yli::ontology::Entity* floyd_warshall_shader_CSV_float_compute_task_entity ...\n";
        yli::ontology::Entity* const floyd_warshall_shader_CSV_float_compute_task_entity = entity_factory->create_ComputeTask(floyd_warshall_shader_CSV_float_compute_task_struct);
        std::cout << "Creating yli::ontology::ComputeTask* floyd_warshall_shader_CSV_float_compute_task ...\n";
        yli::ontology::ComputeTask* const floyd_warshall_shader_CSV_float_compute_task = dynamic_cast<yli::ontology::ComputeTask*>(floyd_warshall_shader_CSV_float_compute_task_entity);

        if (floyd_warshall_shader_CSV_float_compute_task == nullptr)
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
