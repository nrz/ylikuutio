#ifndef PI
#define PI 3.14159265359f
#endif

#include "gpgpu_test_scene.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/shader.hpp"
#include "code/ylikuutio/ontology/compute_task.hpp"
#include "code/ylikuutio/ontology/shader_struct.hpp"
#include "code/ylikuutio/ontology/compute_task_struct.hpp"
#include "code/ylikuutio/ontology/entity_factory.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <iostream>   // std::cout, std::cin, std::cerr
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
        yli::ontology::Entity* const gpgpu_test_scene_entity = entity_factory->create_Scene(world, 0.9f);
        std::cout << "Creating yli::ontology::Scene* gpgpu_test_scene ...\n";
        yli::ontology::Scene* const gpgpu_test_scene = dynamic_cast<yli::ontology::Scene*>(gpgpu_test_scene_entity);

        if (gpgpu_test_scene == nullptr)
        {
            std::cerr << "Failed to create Scene.\n";
            return nullptr;
        }

        gpgpu_test_scene->set_name("gpgpu_test_scene");

        gpgpu_test_scene->set_turbo_factor(5.0f);
        gpgpu_test_scene->set_twin_turbo_factor(100.0f);

        // Create the shader, store it in `identity_shader`.
        ShaderStruct identity_shader_struct;
        identity_shader_struct.parent = gpgpu_test_scene;
        identity_shader_struct.vertex_shader = "identity.vert";
        identity_shader_struct.fragment_shader = "identity.frag";

        std::cout << "Creating yli::ontology::Entity* identity_shader_entity ...\n";
        yli::ontology::Entity* const identity_shader_entity = entity_factory->create_Shader(identity_shader_struct);
        std::cout << "Creating yli::ontology::Shader* identity_shader ...\n";
        yli::ontology::Shader* const identity_shader = dynamic_cast<yli::ontology::Shader*>(identity_shader_entity);

        if (identity_shader == nullptr)
        {
            std::cerr << "Failed to create Shader.\n";
            return nullptr;
        }

        identity_shader->set_name("identity_shader");

        ComputeTaskStruct identity_shader_compute_task_struct;
        identity_shader_compute_task_struct.texture_file_format = "bmp";
        identity_shader_compute_task_struct.texture_filename = "numbers_123456_black_and_white.bmp";
        identity_shader_compute_task_struct.output_filename = "gpgpu_identity_output.data";
        identity_shader_compute_task_struct.parent = identity_shader;
        identity_shader_compute_task_struct.texture_width = 512;
        identity_shader_compute_task_struct.texture_height = 512;

        std::cout << "Creating yli::ontology::Entity* identity_shader_compute_task_entity ...\n";
        yli::ontology::Entity* const identity_shader_compute_task_entity = entity_factory->create_ComputeTask(identity_shader_compute_task_struct);
        std::cout << "Creating yli::ontology::ComputeTask* identity_shader ...\n";
        yli::ontology::ComputeTask* const identity_shader_compute_task = dynamic_cast<yli::ontology::ComputeTask*>(identity_shader_compute_task_entity);

        if (identity_shader_compute_task == nullptr)
        {
            std::cerr << "Failed to create ComputeTask.\n";
            return nullptr;
        }

        // Create the shader, store it in `sobel_shader`.
        ShaderStruct sobel_shader_struct;
        sobel_shader_struct.parent = gpgpu_test_scene;
        sobel_shader_struct.vertex_shader = "identity.vert";
        sobel_shader_struct.fragment_shader = "sobel_gradient_magnitude.frag";

        std::cout << "Creating yli::ontology::Entity* sobel_shader_entity ...\n";
        yli::ontology::Entity* const sobel_shader_entity = entity_factory->create_Shader(sobel_shader_struct);
        std::cout << "Creating yli::ontology::Shader* sobel_shader ...\n";
        yli::ontology::Shader* const sobel_shader = dynamic_cast<yli::ontology::Shader*>(sobel_shader_entity);

        if (sobel_shader == nullptr)
        {
            std::cerr << "Failed to create Shader.\n";
            return nullptr;
        }

        sobel_shader->set_name("sobel_shader");

        ComputeTaskStruct sobel_shader_compute_task_struct;
        sobel_shader_compute_task_struct.texture_file_format = "bmp";
        sobel_shader_compute_task_struct.texture_filename = "numbers_123456_black_and_white.bmp";
        sobel_shader_compute_task_struct.output_filename = "gpgpu_sobel_output.data";
        sobel_shader_compute_task_struct.parent = sobel_shader;
        sobel_shader_compute_task_struct.texture_width = 512;
        sobel_shader_compute_task_struct.texture_height = 512;

        std::cout << "Creating yli::ontology::Entity* sobel_shader_compute_task_entity ...\n";
        yli::ontology::Entity* const sobel_shader_compute_task_entity = entity_factory->create_ComputeTask(sobel_shader_compute_task_struct);
        std::cout << "Creating yli::ontology::ComputeTask* sobel_shader ...\n";
        yli::ontology::ComputeTask* const sobel_shader_compute_task = dynamic_cast<yli::ontology::ComputeTask*>(sobel_shader_compute_task_entity);

        if (sobel_shader_compute_task == nullptr)
        {
            std::cerr << "Failed to create ComputeTask.\n";
            return nullptr;
        }

        return gpgpu_test_scene_entity;
    }
}
