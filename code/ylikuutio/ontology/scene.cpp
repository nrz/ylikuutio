// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif

#include "scene.hpp"
#include "rigid_body_module.hpp"
#include "universe.hpp"
#include "pipeline.hpp"
#include "material.hpp"
#include "camera.hpp"
#include "brain.hpp"
#include "generic_entity_factory.hpp"
#include "request.hpp"
#include "scene_struct.hpp"
#include "camera_struct.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/core/application.hpp"
#include "code/ylikuutio/data/datatype.hpp"
#include "code/ylikuutio/opengl/ubo_block_enums.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.
#include "code/ylikuutio/render/render_system.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

#ifndef __GLM_GTC_TYPE_PTR_HPP_INCLUDED
#define __GLM_GTC_TYPE_PTR_HPP_INCLUDED
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#endif

// Include standard headers
#include <cmath>     // NAN
#include <cstddef>   // std::size_t
#include <iostream>  // std::cerr
#include <stdexcept> // std::runtime_error

namespace yli::ontology
{
    class Entity;

    Scene::Scene(
            yli::core::Application& application,
            Universe& universe,
            const SceneStruct& scene_struct,
            GenericParentModule* const universe_parent_module)
    : Entity(application, universe, scene_struct),
        child_of_universe(universe_parent_module, *this),
        parent_of_brains(
                *this,
                this->registry,
                "brains"),
        parent_of_waypoints(
                *this,
                this->registry,
                "waypoints"),
        parent_of_cameras(
                *this,
                this->registry,
                "cameras"),
        parent_of_pipelines(
                *this,
                this->registry,
                "pipelines"),
        parent_of_materials(
                *this,
                this->registry,
                "materials"),
        parent_of_species(
                *this,
                this->registry,
                "species"),
        parent_of_objects(
                *this,
                this->registry,
                "objects"),
        parent_of_symbioses(
                *this,
                this->registry,
                "symbioses"),
        parent_of_holobionts(
                *this,
                this->registry,
                "holobionts"),
        parent_of_shapeshifters(
                *this,
                this->registry,
                "shapeshifters"),
        parent_of_text_3ds(
                *this,
                this->registry,
                "text_3ds"),
        gravity               { scene_struct.gravity },
        light_position        { scene_struct.light_position },
        water_level           { scene_struct.water_level },
        is_flight_mode_in_use { scene_struct.is_flight_mode_in_use }
    {
        if (this->universe.get_is_opengl_in_use())
        {
            // Uniform block for data related to this `Scene`.
            // Multiple uniform blocks may be rendered in the same frame
            // by using multiple `Camera`s.
            // TODO: add support for using multiple `Camera`s in the same frame!
            glGenBuffers(1, &this->scene_uniform_block);
            glBindBuffer(GL_UNIFORM_BUFFER, this->scene_uniform_block);
            glBufferData(GL_UNIFORM_BUFFER, yli::opengl::scene_ubo::SceneUboBlockOffsets::TOTAL_SIZE, nullptr, GL_STATIC_DRAW);
            glBindBuffer(GL_UNIFORM_BUFFER, 0);
        }
        else if (this->universe.get_is_vulkan_in_use())
        {
            std::cerr << "ERROR: `Scene::Scene`: Vulkan is not supported yet!\n";
        }

        this->activate();

        // create the default `Camera`.
        CameraStruct camera_struct = scene_struct.default_camera_struct;
        camera_struct.scene = Request(this);
        this->get_application().get_generic_entity_factory().create_default_camera(camera_struct);

        // `Entity` member variables begin here.
        this->type_string = "yli::ontology::Scene*";
        this->can_be_erased = true;
    }

    Scene::~Scene()
    {
        if (this->universe.get_active_scene() == this)
        {
            // Set active `Scene` to `nullptr`.
            this->universe.set_active_scene(nullptr);
        }
    }

    void Scene::do_physics()
    {
        // TODO: implement physics!
    }

    void Scene::update()
    {
        // Intentional actors (AIs and keyboard controlled ones).

        for (Entity* const brain_entity : this->parent_of_brains.child_pointer_vector)
        {
            Brain* const brain = static_cast<Brain*>(brain_entity);

            if (brain != nullptr)
            {
                brain->update();
            }
        }
    }

    void Scene::activate()
    {
        // This function should be called upon `Camera::render`
        // of any `Camera` located in this `Scene`.

        this->universe.set_active_scene(this);
    }

    void Scene::render()
    {
        if (!this->should_render)
        {
            return;
        }

        yli::render::RenderSystem* const render_system = this->universe.get_render_system();

        if (render_system == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Scene::render`: `render_system` is `nullptr`!");
        }

        if (this->universe.get_is_opengl_in_use())
        {
            // Set the uniform values specific to a `Scene`.
            glBindBuffer(GL_UNIFORM_BUFFER, this->scene_uniform_block);
            glBufferSubData(GL_UNIFORM_BUFFER, yli::opengl::scene_ubo::SceneUboBlockOffsets::LIGHT_POSITION_WORLDSPACE, sizeof(glm::vec4), glm::value_ptr(this->light_position));
            glBufferSubData(GL_UNIFORM_BUFFER, yli::opengl::scene_ubo::SceneUboBlockOffsets::WATER_LEVEL, sizeof(float), &this->water_level);
            glBindBuffer(GL_UNIFORM_BUFFER, 0);

            glBindBufferBase(GL_UNIFORM_BUFFER, yli::opengl::UboBlockIndices::SCENE, this->scene_uniform_block);
        }
        else if (this->universe.get_is_vulkan_in_use())
        {
            throw std::runtime_error("ERROR: `Scene::render`: Vulkan is not supported yet!");
        }

        render_system->render_pipelines_of_ecosystems(this->universe.get_parent_of_ecosystems(), this);
        render_system->render_pipelines(this->parent_of_pipelines, this);
    }

    Camera* Scene::get_default_camera() const
    {
        return static_cast<Camera*>(this->parent_of_cameras.get(0));
    }

    Camera* Scene::get_active_camera() const
    {
        return this->active_camera;
    }

    void Scene::set_active_camera(Camera* camera)
    {
        if (camera != nullptr && camera->get_parent() != this)
        {
            // `Camera`s of other `Scene`s can not be set
            // as the active `Camera` for this `Scene`.
            return;
        }

        // It is OK to disactivate the active camera by setting `active_camera` to `nullptr`.
        this->active_camera = camera;

        // requirements for further actions:
        // `this->parent` must not be `nullptr`.

        Scene* const active_scene = this->universe.get_active_scene();

        if (active_scene == nullptr)
        {
            return;
        }
    }

    Entity* Scene::get_parent() const
    {
        return this->child_of_universe.get_parent();
    }

    Scene* Scene::get_scene() const
    {
        return const_cast<Scene*>(this);
    }

    std::size_t Scene::get_number_of_children() const
    {
        return this->parent_of_brains.get_number_of_children() +
            this->parent_of_waypoints.get_number_of_children() +
            this->parent_of_cameras.get_number_of_children() +
            this->parent_of_pipelines.get_number_of_children() +
            this->parent_of_materials.get_number_of_children() +
            this->parent_of_species.get_number_of_children() +
            this->parent_of_objects.get_number_of_children() +
            this->parent_of_symbioses.get_number_of_children() +
            this->parent_of_holobionts.get_number_of_children() +
            this->parent_of_shapeshifters.get_number_of_children() +
            this->parent_of_text_3ds.get_number_of_children();
    }

    std::size_t Scene::get_number_of_descendants() const
    {
        return yli::ontology::get_number_of_descendants(this->parent_of_brains.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_waypoints.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_cameras.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_pipelines.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_materials.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_species.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_objects.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_symbioses.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_holobionts.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_shapeshifters.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_text_3ds.child_pointer_vector);
    }

    float Scene::get_turbo_factor() const
    {
        if (this == this->universe.get_active_scene())
        {
            return this->universe.turbo_factor;
        }

        return NAN;
    }

    void Scene::set_turbo_factor(const float turbo_factor)
    {
        this->turbo_factor = turbo_factor;

        if (this == this->universe.get_active_scene())
        {
            this->universe.turbo_factor = this->turbo_factor;
        }
    }

    float Scene::get_twin_turbo_factor() const
    {
        if (this == this->universe.get_active_scene())
        {
            return this->universe.twin_turbo_factor;
        }

        return NAN;
    }

    void Scene::set_twin_turbo_factor(const float twin_turbo_factor)
    {
        this->twin_turbo_factor = twin_turbo_factor;

        if (this == this->universe.get_active_scene())
        {
            this->universe.twin_turbo_factor = this->twin_turbo_factor;
        }
    }

    float Scene::get_gravity() const
    {
        return this->gravity;
    }

    void Scene::set_gravity(const float gravity)
    {
        this->gravity = gravity;
    }

    void Scene::add_rigid_body_module(const RigidBodyModule& /* rigid_body_module */, Scene& /* scene */ )
    {
        // TODO: implement!
    }

    const glm::vec4& Scene::get_light_position() const
    {
        return this->light_position;
    }

    float Scene::get_water_level() const
    {
        return this->water_level;
    }

    bool Scene::get_is_flight_mode_in_use() const
    {
        return this->is_flight_mode_in_use;
    }

    void Scene::set_is_flight_mode_in_use(const bool is_flight_mode_in_use)
    {
        this->is_flight_mode_in_use = is_flight_mode_in_use;
    }

    GenericParentModule* Scene::get_generic_parent_module(const int type)
    {
        if (type == yli::data::Datatype::BRAIN)
        {
            return &this->parent_of_brains;
        }
        else if (type == yli::data::Datatype::WAYPOINT)
        {
            return &this->parent_of_waypoints;
        }
        else if (type == yli::data::Datatype::CAMERA)
        {
            return &this->parent_of_cameras;
        }
        else if (type == yli::data::Datatype::PIPELINE)
        {
            return &this->parent_of_pipelines;
        }
        else if (type == yli::data::Datatype::MATERIAL)
        {
            return &this->parent_of_materials;
        }
        else if (type == yli::data::Datatype::SPECIES)
        {
            return &this->parent_of_species;
        }
        else if (type == yli::data::Datatype::OBJECT)
        {
            return &this->parent_of_objects;
        }
        else if (type == yli::data::Datatype::SYMBIOSIS)
        {
            return &this->parent_of_symbioses;
        }
        else if (type == yli::data::Datatype::HOLOBIONT)
        {
            return &this->parent_of_holobionts;
        }
        else if (type == yli::data::Datatype::SHAPESHIFTER)
        {
            return &this->parent_of_shapeshifters;
        }
        else if (type == yli::data::Datatype::TEXT_3D)
        {
            return &this->parent_of_text_3ds;
        }

        return nullptr;
    }
}
