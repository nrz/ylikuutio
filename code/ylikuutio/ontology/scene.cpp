#ifndef PI
#define PI 3.14159265359f
#endif

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

#include "scene.hpp"
#include "ground_level.hpp"
#include "shader.hpp"
#include "render_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/common/pi.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <unordered_map> // std::unordered_map

namespace ontology
{
    class Object;

    void Scene::bind_to_parent()
    {
        // get `childID` from `Universe` and set pointer to this `Scene`.
        hierarchy::bind_child_to_parent<ontology::Scene*>(this, this->parent->scene_pointer_vector, this->parent->free_sceneID_queue, &this->parent->number_of_scenes);
    }

    Scene::~Scene()
    {
        // destructor.
        std::cout << "Scene with childID " << std::dec << this->childID << " will be destroyed.\n";

        // destroy all shaders of this scene.
        std::cout << "All shaders of this scene will be destroyed.\n";
        hierarchy::delete_children<ontology::Shader*>(this->shader_pointer_vector, &this->number_of_shaders);

        // If this is the active `Scene`, set all `Scene`-related variables to `nullptr` or invalid.
        if (this->universe->active_scene == this)
        {
            this->universe->cartesian_coordinates = nullptr;

            this->universe->direction = glm::vec3(NAN, NAN, NAN);

            this->universe->right = glm::vec3(NAN, NAN, NAN);
            this->universe->up = glm::vec3(NAN, NAN, NAN);

            this->universe->spherical_coordinates = nullptr;

            this->universe->horizontal_angle = NAN;
            this->universe->vertical_angle = NAN;

            // Make this `Scene` no more the active `Scene`.
            this->universe->active_scene = nullptr;
        }
    }

    void Scene::render()
    {
        this->prerender();

        // render this `Scene` by calling `render()` function of each `Shader`.
        ontology::render_children<ontology::Shader*>(this->shader_pointer_vector);

        this->postrender();
    }

    ontology::Entity* Scene::get_parent()
    {
        return this->parent;
    }

    int32_t Scene::get_number_of_children()
    {
        return this->number_of_shaders;
    }

    int32_t Scene::get_number_of_descendants()
    {
        return -1;
    }

    // this method returns a pointer to an `Entity` using the name as key.
    ontology::Entity* Scene::get_entity(const std::string name)
    {
        if (this->name_map.count(name) != 1)
        {
            return nullptr;
        }

        return this->name_map[name];
    }

    void Scene::set_name(const std::string name)
    {
        ontology::set_name(name, this);
    }

    void Scene::set_turbo_factor(float turbo_factor)
    {
        this->turbo_factor = turbo_factor;

        if (this == this->universe->active_scene)
        {
            this->universe->turbo_factor = this->turbo_factor;
        }
    }

    void Scene::set_twin_turbo_factor(float twin_turbo_factor)
    {
        this->twin_turbo_factor = twin_turbo_factor;

        if (this == this->universe->active_scene)
        {
            this->universe->twin_turbo_factor = this->twin_turbo_factor;
        }
    }

    void Scene::set_shader_pointer(const int32_t childID, ontology::Shader* const child_pointer)
    {
        hierarchy::set_child_pointer(childID, child_pointer, this->shader_pointer_vector, this->free_shaderID_queue, &this->number_of_shaders);
    }
}
