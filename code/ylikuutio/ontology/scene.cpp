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
#include "family_templates.hpp"
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
#include <unordered_map> // std::unordered_map

namespace yli
{
    namespace ontology
    {
        class Species;

        void Scene::bind_shader(yli::ontology::Shader* const shader)
        {
            // get `childID` from `Scene` and set pointer to `shader`.
            yli::hierarchy::bind_child_to_parent<yli::ontology::Shader*>(
                    shader,
                    this->shader_pointer_vector,
                    this->free_shaderID_queue,
                    this->number_of_shaders);
        }

        void Scene::bind_camera(yli::ontology::Camera* const camera)
        {
            // get `childID` from `Scene` and set pointer to `camera`.
            yli::hierarchy::bind_child_to_parent<yli::ontology::Camera*>(
                    camera,
                    this->camera_pointer_vector,
                    this->free_cameraID_queue,
                    this->number_of_cameras);
        }

        void Scene::unbind_shader(const std::size_t childID)
        {
            yli::hierarchy::unbind_child_from_parent(
                    childID,
                    this->shader_pointer_vector,
                    this->free_shaderID_queue,
                    this->number_of_shaders);
        }

        void Scene::unbind_camera(const std::size_t childID)
        {
            yli::hierarchy::unbind_child_from_parent(
                    childID,
                    this->camera_pointer_vector,
                    this->free_cameraID_queue,
                    this->number_of_cameras);
        }

        void Scene::bind_to_parent()
        {
            // requirements:
            // `this->parent` must not be `nullptr`.
            yli::ontology::World* const world = this->parent;

            if (world == nullptr)
            {
                std::cerr << "ERROR: `Scene::bind_to_parent`: `world` is `nullptr`!\n";
                return;
            }

            // get `childID` from the `World` and set pointer to this `Scene`.
            world->bind_scene(this);
        }

        Scene::~Scene()
        {
            // destructor.
            std::cout << "Scene with childID " << std::dec << this->childID << " will be destroyed.\n";

            // destroy all `Shader`s of this `Scene`.
            std::cout << "All shaders of this scene will be destroyed.\n";
            yli::hierarchy::delete_children<yli::ontology::Shader*>(this->shader_pointer_vector, this->number_of_shaders);

            // destroy all `Camera`s of this `Scene`.
            std::cout << "All cameras of this scene will be destroyed.\n";
            yli::hierarchy::delete_children<yli::ontology::Camera*>(this->camera_pointer_vector, this->number_of_cameras);

            // requirements for further actions:
            // `this->parent` must not be `nullptr`.

            yli::ontology::World* const world = this->parent;

            if (world == nullptr)
            {
                std::cerr << "ERROR: `Scene::~Scene`: `world` is `nullptr`!\n";
                return;
            }

            if (world->get_active_scene() == this)
            {
                // Make this `Scene` no more the active `Scene`.
                this->parent->set_active_scene(nullptr);
            }

            // set pointer to this `Scene` to `nullptr`.
            world->unbind_scene(this->childID);
        }

        void Scene::render()
        {
            if (this->should_be_rendered)
            {
                this->prerender();

                // render this `Scene` by calling `render()` function of each `Shader`.
                yli::ontology::render_children<yli::ontology::Shader*>(this->shader_pointer_vector);

                this->postrender();
            }
        }

        yli::ontology::Camera* Scene::get_active_camera() const
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
            return this->number_of_shaders + this->number_of_cameras;
        }

        std::size_t Scene::get_number_of_descendants() const
        {
            return yli::ontology::get_number_of_descendants(this->shader_pointer_vector) +
                yli::ontology::get_number_of_descendants(this->camera_pointer_vector);
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
            if (this->parent != nullptr &&
                    this->universe != nullptr &&
                    this->parent == this->universe->get_active_world() &&
                    this == this->parent->get_active_scene())
            {
                return this->universe->turbo_factor;
            }

            return NAN;
        }

        void Scene::set_turbo_factor(float turbo_factor)
        {
            this->turbo_factor = turbo_factor;

            if (this->parent != nullptr &&
                    this->universe != nullptr &&
                    this->parent == this->universe->get_active_world() &&
                    this == this->parent->get_active_scene())
            {
                this->universe->turbo_factor = this->turbo_factor;
            }
        }

        float Scene::get_twin_turbo_factor() const
        {
            if (this->parent != nullptr &&
                    this->universe != nullptr &&
                    this->parent == this->universe->get_active_world() &&
                    this == this->parent->get_active_scene())
            {
                return this->universe->twin_turbo_factor;
            }

            return NAN;
        }

        void Scene::set_twin_turbo_factor(float twin_turbo_factor)
        {
            this->twin_turbo_factor = twin_turbo_factor;

            if (this->parent != nullptr &&
                    this->universe != nullptr &&
                    this->parent == this->universe->get_active_world() &&
                    this == this->parent->get_active_scene())
            {
                this->universe->twin_turbo_factor = this->twin_turbo_factor;
            }
        }

        yli::ontology::Species* Scene::get_terrain_species() const
        {
            if (this->parent != nullptr &&
                    this->universe != nullptr &&
                    this->parent == this->universe->get_active_world() &&
                    this == this->parent->get_active_scene())
            {
                return this->terrain_species;
            }

            return nullptr;
        }

        void Scene::set_terrain_species(yli::ontology::Species* const terrain_species)
        {
            this->terrain_species = terrain_species;

            if (this->parent != nullptr &&
                    this->universe != nullptr &&
                    this->parent == this->universe->get_active_world() &&
                    this == this->parent->get_active_scene())
            {
                this->universe->set_terrain_species(this->terrain_species);
            }
        }

        yli::ontology::World* Scene::get_world_parent() const
        {
            return this->parent;
        }

        float Scene::get_water_level() const
        {
            return this->water_level;
        }
    }
}
