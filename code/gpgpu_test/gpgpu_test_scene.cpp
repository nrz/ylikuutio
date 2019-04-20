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

        // Create the shader, store it in `gpgpu_test_shader`.
        ShaderStruct gpgpu_test_shader_struct;
        gpgpu_test_shader_struct.parent = gpgpu_test_scene;
        gpgpu_test_shader_struct.vertex_shader = "identity.vert";
        gpgpu_test_shader_struct.fragment_shader = "identity.frag";

        std::cout << "Creating yli::ontology::Entity* gpgpu_test_shader_entity ...\n";
        yli::ontology::Entity* const gpgpu_test_shader_entity = entity_factory->create_Shader(gpgpu_test_shader_struct);
        std::cout << "Creating yli::ontology::Shader* gpgpu_test_shader ...\n";
        yli::ontology::Shader* const gpgpu_test_shader = dynamic_cast<yli::ontology::Shader*>(gpgpu_test_shader_entity);

        if (gpgpu_test_shader == nullptr)
        {
            std::cerr << "Failed to create Shader.\n";
            return nullptr;
        }

        gpgpu_test_shader->set_name("gpgpu_test_shader");

        ComputeTaskStruct compute_task_struct;
        compute_task_struct.texture_file_format = "bmp";
        compute_task_struct.texture_filename = "numbers_123456_black_and_white.bmp";
        compute_task_struct.output_filename = "gpgpu_output.data";
        compute_task_struct.parent = gpgpu_test_shader;
        compute_task_struct.texture_width = 512;
        compute_task_struct.texture_height = 512;

        std::cout << "Creating yli::ontology::Entity* compute_task_entity ...\n";
        yli::ontology::Entity* const compute_task_entity = entity_factory->create_ComputeTask(compute_task_struct);
        std::cout << "Creating yli::ontology::ComputeTask* gpgpu_test_shader ...\n";
        yli::ontology::ComputeTask* const compute_task = dynamic_cast<yli::ontology::ComputeTask*>(compute_task_entity);

        if (compute_task == nullptr)
        {
            std::cerr << "Failed to create ComputeTask.\n";
            return nullptr;
        }

        return gpgpu_test_scene_entity;
    }
}
