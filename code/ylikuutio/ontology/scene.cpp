#ifndef PI
#define PI 3.14159265359f
#endif

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

#include "scene.hpp"
#include "world.hpp"
#include "ground_level.hpp"
#include "shader.hpp"
#include "camera.hpp"
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
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <unordered_map> // std::unordered_map

namespace yli
{
    namespace ontology
    {
        void Scene::bind_shader(yli::ontology::Shader* const shader)
        {
            // get `childID` from `Scene` and set pointer to `shader`.
            hierarchy::bind_child_to_parent<yli::ontology::Shader*>(
                    shader,
                    this->shader_pointer_vector,
                    this->free_shaderID_queue,
                    &this->number_of_shaders);
        }

        void Scene::bind_camera(yli::ontology::Camera* const camera)
        {
            // get `childID` from `Scene` and set pointer to `camera`.
            hierarchy::bind_child_to_parent<yli::ontology::Camera*>(
                    camera,
                    this->camera_pointer_vector,
                    this->free_cameraID_queue,
                    &this->number_of_cameras);
        }

        void Scene::unbind_shader(const int32_t childID)
        {
            yli::ontology::Shader* dummy_child_pointer = nullptr;
            hierarchy::set_child_pointer(
                    childID,
                    dummy_child_pointer,
                    this->shader_pointer_vector,
                    this->free_shaderID_queue,
                    &this->number_of_shaders);
        }

        void Scene::unbind_camera(const int32_t childID)
        {
            yli::ontology::Camera* dummy_child_pointer = nullptr;
            hierarchy::set_child_pointer(
                    childID,
                    dummy_child_pointer,
                    this->camera_pointer_vector,
                    this->free_cameraID_queue,
                    &this->number_of_cameras);
        }

        void Scene::bind_to_parent()
        {
            // get `childID` from `World` and set pointer to this `Scene`.
            this->parent->bind(this);
        }

        Scene::~Scene()
        {
            // destructor.
            std::cout << "Scene with childID " << std::dec << this->childID << " will be destroyed.\n";

            // destroy all `Shader`s of this `Scene`.
            std::cout << "All shaders of this scene will be destroyed.\n";
            hierarchy::delete_children<yli::ontology::Shader*>(this->shader_pointer_vector, &this->number_of_shaders);

            // destroy all `Camera`s of this `Scene`.
            std::cout << "All cameras of this scene will be destroyed.\n";
            hierarchy::delete_children<yli::ontology::Camera*>(this->camera_pointer_vector, &this->number_of_cameras);

            if (this->parent->get_active_scene() == this)
            {
                // Make this `Scene` no more the active `Scene`.
                this->parent->set_active_scene(nullptr);
            }

            // set pointer to this `Scene` to `nullptr`.
            this->parent->set_scene_pointer(this->childID, nullptr);
        }

        void Scene::render()
        {
            this->prerender();

            // render this `Scene` by calling `render()` function of each `Shader`.
            yli::ontology::render_children<yli::ontology::Shader*>(this->shader_pointer_vector);

            this->postrender();
        }

        yli::ontology::Camera* Scene::get_active_camera()
        {
            return this->active_camera;
        }

        void Scene::set_active_camera(yli::ontology::Camera* camera)
        {
            this->active_camera = camera;

            if (this->active_camera != nullptr)
            {
                this->universe->current_camera_cartesian_coordinates = camera->get_cartesian_coordinates();
                this->universe->set_projection_matrix(camera->get_projection_matrix());
                this->universe->set_view_matrix(camera->get_view_matrix());
                this->universe->current_camera_horizontal_angle = camera->get_horizontal_angle();
                this->universe->current_camera_vertical_angle = camera->get_vertical_angle();
            }
        }

        yli::ontology::Entity* Scene::get_parent() const
        {
            return this->parent;
        }

        std::size_t Scene::get_number_of_children() const
        {
            return this->number_of_shaders;
        }

        std::size_t Scene::get_number_of_descendants() const
        {
            return 0; // TODO; write the code!
        }

        // this method returns a pointer to an `Entity` using the name as key.
        yli::ontology::Entity* Scene::get_entity(const std::string name) const
        {
            if (this->name_map.count(name) != 1)
            {
                return nullptr;
            }

            return this->name_map.at(name);
        }

        float Scene::get_turbo_factor() const
        {
            if (this->parent == this->universe->get_active_world() && this == this->parent->get_active_scene())
            {
                return this->universe->turbo_factor;
            }

            return NAN;
        }

        void Scene::set_turbo_factor(float turbo_factor)
        {
            this->turbo_factor = turbo_factor;

            if (this->parent == this->universe->get_active_world() && this == this->parent->get_active_scene())
            {
                this->universe->turbo_factor = this->turbo_factor;
            }
        }

        float Scene::get_twin_turbo_factor() const
        {
            if (this->parent == this->universe->get_active_world() && this == this->parent->get_active_scene())
            {
                return this->universe->twin_turbo_factor;
            }

            return NAN;
        }

        void Scene::set_twin_turbo_factor(float twin_turbo_factor)
        {
            this->twin_turbo_factor = twin_turbo_factor;

            if (this->parent == this->universe->get_active_world() && this == this->parent->get_active_scene())
            {
                this->universe->twin_turbo_factor = this->twin_turbo_factor;
            }
        }

        float Scene::get_water_level() const
        {
            return this->water_level;
        }

        void Scene::set_shader_pointer(const int32_t childID, yli::ontology::Shader* const child_pointer)
        {
            hierarchy::set_child_pointer(childID, child_pointer, this->shader_pointer_vector, this->free_shaderID_queue, &this->number_of_shaders);
        }

        void Scene::set_camera_pointer(const int32_t childID, yli::ontology::Camera* const child_pointer)
        {
            hierarchy::set_child_pointer(childID, child_pointer, this->camera_pointer_vector, this->free_cameraID_queue, &this->number_of_cameras);
        }
    }
}
