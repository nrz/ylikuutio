// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
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

#ifndef YLIKUUTIO_ONTOLOGY_ENTITY_FACTORY_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_ENTITY_FACTORY_HPP_INCLUDED

#include "generic_entity_factory.hpp"
#include "generic_master_module.hpp"
#include "entity.hpp"
#include "variable.hpp"
#include "callback_engine.hpp"
#include "callback_object.hpp"
#include "callback_parameter.hpp"
#include "universe.hpp"
#include "ecosystem.hpp"
#include "scene.hpp"
#include "brain.hpp"
#include "waypoint.hpp"
#include "camera.hpp"
#include "pipeline.hpp"
#include "material.hpp"
#include "species.hpp"
#include "object.hpp"
#include "symbiosis.hpp"
#include "symbiont_material.hpp"
#include "symbiont_species.hpp"
#include "holobiont.hpp"
#include "biont.hpp"
#include "vector_font.hpp"
#include "glyph.hpp"
#include "text_2d.hpp"
#include "text_3d.hpp"
#include "font_2d.hpp"
#include "input_mode.hpp"
#include "audio_track.hpp"
#include "console.hpp"
#include "console_callback_engine.hpp"
#include "console_callback_object.hpp"
#include "console_callback_parameter.hpp"
#include "lisp_function.hpp"
#include "generic_lisp_function_overload.hpp"
#include "lisp_function_overload.hpp"
#include "shapeshifter_transformation.hpp"
#include "shapeshifter_sequence.hpp"
#include "shapeshifter_form.hpp"
#include "compute_task.hpp"
#include "variable_struct.hpp"
#include "callback_engine_struct.hpp"
#include "callback_object_struct.hpp"
#include "callback_parameter_struct.hpp"
#include "ecosystem_struct.hpp"
#include "scene_struct.hpp"
#include "brain_struct.hpp"
#include "waypoint_struct.hpp"
#include "camera_struct.hpp"
#include "pipeline_struct.hpp"
#include "material_struct.hpp"
#include "model_struct.hpp"
#include "species_struct.hpp"
#include "object_struct.hpp"
#include "symbiosis_struct.hpp"
#include "symbiont_species_struct.hpp"
#include "holobiont_struct.hpp"
#include "biont_struct.hpp"
#include "shapeshifter_sequence_struct.hpp"
#include "vector_font_struct.hpp"
#include "text_3d_struct.hpp"
#include "input_mode_struct.hpp"
#include "audio_track_struct.hpp"
#include "console_struct.hpp"
#include "console_callback_engine_struct.hpp"
#include "console_callback_object_struct.hpp"
#include "console_callback_parameter_struct.hpp"
#include "font_struct.hpp"
#include "text_struct.hpp"
#include "lisp_function_struct.hpp"
#include "compute_task_struct.hpp"
#include "input_parameters_and_any_value_to_any_value_callback_with_universe.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/data/datatype.hpp"
#include "code/ylikuutio/memory/memory_system.hpp"
#include "code/ylikuutio/memory/memory_allocator.hpp"

// Include standard headers
#include <iostream>   // std::cerr
#include <optional>   // std::optional
#include <stdexcept>  // std::runtime_error
#include <string>     // std::string
#include <variant>    // std::holds_alternative

namespace yli::core
{
    class Application;
}

namespace yli::memory
{
    class GenericMemoryAllocator;
}

namespace yli::ontology
{
    template<typename TypeEnumType>
        class EntityFactory : public yli::ontology::GenericEntityFactory
    {
        public:
            EntityFactory(
                    yli::core::Application& application,
                    yli::memory::MemorySystem<TypeEnumType>& memory_system)
                : application { application },
                memory_system { memory_system }
            {
            }

            yli::ontology::EntityFactory<TypeEnumType>& get() const
            {
                return const_cast<yli::ontology::EntityFactory<TypeEnumType>&>(*this);
            }

            yli::ontology::Universe* create_universe(const yli::ontology::UniverseStruct& universe_struct)
            {
                using UniverseMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::Universe, 1>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<UniverseMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::UNIVERSE));
                UniverseMemoryAllocator& allocator = static_cast<UniverseMemoryAllocator&>(generic_allocator);

                yli::ontology::Universe* const universe = allocator.build_in(
                        this->application,
                        universe_struct);

                this->universe = universe;
                return universe;
            }

            yli::ontology::Universe& get_universe() const
            {
                if (this->universe == nullptr) [[unlikely]]
                {
                    throw std::runtime_error("ERROR: `EntityFactory::get_universe`: `this->universe` is `nullptr`!");
                }

                return *this->universe;
            }

            yli::ontology::Variable* create_variable(
                    const yli::ontology::VariableStruct& variable_struct,
                    const yli::data::AnyValue& any_value) const override
            {
                using VariableMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::Variable, 4096>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<VariableMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::VARIABLE));
                VariableMemoryAllocator& allocator = static_cast<VariableMemoryAllocator&>(generic_allocator);

                yli::ontology::Entity* entity_parent { nullptr };
                if (std::holds_alternative<yli::ontology::Entity*>(variable_struct.parent))
                {
                    entity_parent = std::get<yli::ontology::Entity*>(variable_struct.parent);
                }
                else if (std::holds_alternative<std::string>(variable_struct.parent))
                {
                    entity_parent = this->get_universe().registry.get_entity(std::get<std::string>(variable_struct.parent));
                }

                // The `Universe&` needs to be taken from `VariableStruct`
                // because `Universe` constructor creates its `Variable`
                // instances using `EntityFactory` before `EntityFactory::create_universe`
                // has initialized `universe` member variable of `EntityFactory`.
                yli::ontology::Variable* const variable = allocator.build_in(
                        this->application,
                        variable_struct.universe,
                        variable_struct,
                        ((entity_parent != nullptr) ? &entity_parent->parent_of_variables : nullptr),
                        any_value);

                if (variable_struct.is_variable_of_universe)
                {
                    // OK, this is a `Variable` of the `Universe`.

                    if (!variable_struct.global_name.empty() && variable_struct.local_name.empty())
                    {
                        // Only `global_name` given, OK.
                        variable->set_global_name(variable_struct.global_name);
                    }
                    else if (variable_struct.global_name.empty() && !variable_struct.local_name.empty())
                    {
                        // Only `local_name` given, OK.
                        variable->set_local_name(variable_struct.local_name);
                    }
                    else if (!variable_struct.global_name.empty() && !variable_struct.local_name.empty())
                    {
                        std::cerr << "ERROR: `EntityFactory::create_variable`: both global and local names given for a `Variable`\n";
                        std::cerr << "which is a child of `Universe`. For children of the `Universe` global and local names\n";
                        std::cerr << "are the same and only 1 of them can be given. No name given to this `Variable`!\n";
                    }
                }
                else
                {
                    // This is not a `Variable` of the `Universe`.

                    variable->set_global_name(variable_struct.global_name);
                    variable->set_local_name(variable_struct.local_name);
                }

                if (variable_struct.should_call_activate_callback_now)
                {
                    variable->activate();
                }

                return variable;
            }

            yli::ontology::CallbackEngine* create_callback_engine(
                    const yli::ontology::CallbackEngineStruct& callback_engine_struct) const override
            {
                using CallbackEngineMemoryAllocator =
                    yli::memory::MemoryAllocator<yli::ontology::CallbackEngine, 256>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<CallbackEngineMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::CALLBACK_ENGINE));
                CallbackEngineMemoryAllocator& allocator = static_cast<CallbackEngineMemoryAllocator&>(generic_allocator);

                yli::ontology::CallbackEngine* const callback_engine = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        &this->get_universe().parent_of_callback_engines);

                if (!callback_engine_struct.global_name.empty() && callback_engine_struct.local_name.empty())
                {
                    // Only `global_name` given, OK.
                    callback_engine->set_global_name(callback_engine_struct.global_name);
                }
                else if (callback_engine_struct.global_name.empty() && !callback_engine_struct.local_name.empty())
                {
                    // Only `local_name` given, OK.
                    callback_engine->set_local_name(callback_engine_struct.local_name);
                }
                else if (!callback_engine_struct.global_name.empty() && !callback_engine_struct.local_name.empty())
                {
                    std::cerr << "ERROR: `EntityFactory::create_callback_engine`: both global and local names given for a `CallbackEngine`\n";
                    std::cerr << "which is a child of `Universe`. For children of the `Universe` global and local names\n";
                    std::cerr << "are the same and only 1 of them can be given. No name given to this `CallbackEngine`!\n";
                }

                return callback_engine;
            }

            yli::ontology::CallbackObject* create_callback_object(
                    const yli::ontology::CallbackObjectStruct& callback_object_struct) const override
            {
                using CallbackObjectMemoryAllocator =
                    yli::memory::MemoryAllocator<yli::ontology::CallbackObject, 256>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<CallbackObjectMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::CALLBACK_OBJECT));
                CallbackObjectMemoryAllocator& allocator = static_cast<CallbackObjectMemoryAllocator&>(generic_allocator);

                yli::ontology::CallbackEngine* callback_engine_parent { nullptr };
                if (std::holds_alternative<yli::ontology::CallbackEngine*>(callback_object_struct.callback_engine_parent))
                {
                    callback_engine_parent = std::get<yli::ontology::CallbackEngine*>(callback_object_struct.callback_engine_parent);
                }
                else if (std::holds_alternative<std::string>(callback_object_struct.callback_engine_parent))
                {
                    callback_engine_parent = dynamic_cast<yli::ontology::CallbackEngine*>(this->get_universe().registry.get_entity(
                                std::get<std::string>(callback_object_struct.callback_engine_parent)));
                }

                yli::ontology::CallbackObject* const callback_object = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        callback_object_struct,
                        ((callback_engine_parent != nullptr) ?
                         &callback_engine_parent->parent_of_callback_objects :
                         nullptr));
                callback_object->set_global_name(callback_object_struct.global_name);
                callback_object->set_local_name(callback_object_struct.local_name);
                return callback_object;
            }

            yli::ontology::CallbackParameter* create_callback_parameter(
                    const yli::ontology::CallbackParameterStruct& callback_parameter_struct,
                    const yli::data::AnyValue& any_value) const override
            {
                using CallbackParameterMemoryAllocator =
                    yli::memory::MemoryAllocator<yli::ontology::CallbackParameter, 256>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<CallbackParameterMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::CALLBACK_PARAMETER));
                CallbackParameterMemoryAllocator& allocator = static_cast<CallbackParameterMemoryAllocator&>(generic_allocator);

                yli::ontology::CallbackObject* callback_object_parent { nullptr };
                if (std::holds_alternative<yli::ontology::CallbackObject*>(callback_parameter_struct.callback_object_parent))
                {
                    callback_object_parent = std::get<yli::ontology::CallbackObject*>(callback_parameter_struct.callback_object_parent);
                }
                else if (std::holds_alternative<std::string>(callback_parameter_struct.callback_object_parent))
                {
                    callback_object_parent = dynamic_cast<yli::ontology::CallbackObject*>(this->get_universe().registry.get_entity(
                                std::get<std::string>(callback_parameter_struct.callback_object_parent)));
                }

                yli::ontology::CallbackParameter* const callback_parameter = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        callback_parameter_struct,
                        any_value,
                        ((callback_object_parent != nullptr) ?
                         &callback_object_parent->parent_of_callback_parameters :
                         nullptr));

                callback_parameter->set_global_name(callback_parameter_struct.global_name);
                callback_parameter->set_local_name(callback_parameter_struct.local_name);
                return callback_parameter;
            }

            // TODO: implement `create_window` here!

            // TODO: implement `create_widget` here!

            yli::ontology::Ecosystem* create_ecosystem(const yli::ontology::EcosystemStruct& ecosystem_struct) const override
            {
                using EcosystemMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::Ecosystem, 16>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<EcosystemMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::ECOSYSTEM));
                EcosystemMemoryAllocator& allocator = static_cast<EcosystemMemoryAllocator&>(generic_allocator);

                yli::ontology::Ecosystem* const ecosystem = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        ecosystem_struct,
                        &this->get_universe().parent_of_ecosystems);

                if (!ecosystem_struct.global_name.empty() && ecosystem_struct.local_name.empty())
                {
                    // Only `global_name` given, OK.
                    ecosystem->set_global_name(ecosystem_struct.global_name);
                }
                else if (ecosystem_struct.global_name.empty() && !ecosystem_struct.local_name.empty())
                {
                    // Only `local_name` given, OK.
                    ecosystem->set_local_name(ecosystem_struct.local_name);
                }
                else if (!ecosystem_struct.global_name.empty() && !ecosystem_struct.local_name.empty())
                {
                    std::cerr << "ERROR: `EntityFactory::create_ecosystem`: both global and local names given for a `Ecosystem`\n";
                    std::cerr << "which is a child of `Universe`. For children of the `Universe` global and local names\n";
                    std::cerr << "are the same and only 1 of them can be given. No name given to this `Ecosystem`!\n";
                }

                return ecosystem;
            }

            yli::ontology::Scene* create_scene(const yli::ontology::SceneStruct& scene_struct) const override
            {
                using SceneMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::Scene, 256>;

                yli::memory::GenericMemoryAllocator& generic_scene_allocator =
                    this->memory_system.template get_or_create_allocator<SceneMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::SCENE));
                SceneMemoryAllocator& scene_allocator = static_cast<SceneMemoryAllocator&>(generic_scene_allocator);

                yli::ontology::Scene* const scene = scene_allocator.build_in(
                        this->application,
                        this->get_universe(),
                        scene_struct,
                        &this->get_universe().parent_of_scenes);

                if (!scene_struct.global_name.empty() && scene_struct.local_name.empty())
                {
                    // Only `global_name` given, OK.
                    scene->set_global_name(scene_struct.global_name);
                }
                else if (scene_struct.global_name.empty() && !scene_struct.local_name.empty())
                {
                    // Only `local_name` given, OK.
                    scene->set_local_name(scene_struct.local_name);
                }
                else if (!scene_struct.global_name.empty() && !scene_struct.local_name.empty())
                {
                    std::cerr << "ERROR: `EntityFactory::create_scene`: both global and local names given for a `Scene`\n";
                    std::cerr << "which is a child of `Universe`. For children of the `Universe` global and local names\n";
                    std::cerr << "are the same and only 1 of them can be given. No name given to this `Scene`!\n";
                }

                return scene;
            }

            yli::ontology::Brain* create_brain(const yli::ontology::BrainStruct& brain_struct) const override
            {
                using BrainMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::Brain, 16>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<BrainMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::BRAIN));
                BrainMemoryAllocator& allocator = static_cast<BrainMemoryAllocator&>(generic_allocator);

                yli::ontology::Scene* scene_parent { nullptr };
                if (std::holds_alternative<yli::ontology::Scene*>(brain_struct.parent))
                {
                    scene_parent = std::get<yli::ontology::Scene*>(brain_struct.parent);
                }
                else if (std::holds_alternative<std::string>(brain_struct.parent))
                {
                    scene_parent = dynamic_cast<yli::ontology::Scene*>(this->get_universe().registry.get_entity(std::get<std::string>(brain_struct.parent)));
                }

                yli::ontology::Brain* const brain = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        brain_struct,
                        (scene_parent != nullptr ? &scene_parent->parent_of_brains : nullptr));

                brain->set_global_name(brain_struct.global_name);
                brain->set_local_name(brain_struct.local_name);
                return brain;
            }

            yli::ontology::Waypoint* create_waypoint(const yli::ontology::WaypointStruct& waypoint_struct) const override
            {
                using WaypointMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::Waypoint, 256>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<WaypointMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::WAYPOINT));
                WaypointMemoryAllocator& allocator = static_cast<WaypointMemoryAllocator&>(generic_allocator);

                yli::ontology::Scene* scene_parent { nullptr };
                if (std::holds_alternative<yli::ontology::Scene*>(waypoint_struct.scene))
                {
                    scene_parent = std::get<yli::ontology::Scene*>(waypoint_struct.scene);
                }
                else if (std::holds_alternative<std::string>(waypoint_struct.scene))
                {
                    scene_parent = dynamic_cast<yli::ontology::Scene*>(this->get_universe().registry.get_entity(std::get<std::string>(waypoint_struct.scene)));
                }

                yli::ontology::Waypoint* const waypoint = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        waypoint_struct,
                        (scene_parent != nullptr ? &scene_parent->parent_of_waypoints : nullptr),
                        // `Brain` master.
                        (waypoint_struct.brain != nullptr ? waypoint_struct.brain->get_generic_master_module() : nullptr));

                waypoint->set_global_name(waypoint_struct.global_name);
                waypoint->set_local_name(waypoint_struct.local_name);
                return waypoint;
            }

            yli::ontology::Camera* create_camera(const yli::ontology::CameraStruct& camera_struct) const override
            {
                using CameraMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::Camera, 256>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<CameraMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::CAMERA));
                CameraMemoryAllocator& allocator = static_cast<CameraMemoryAllocator&>(generic_allocator);

                yli::ontology::Scene* scene_parent { nullptr };
                if (std::holds_alternative<yli::ontology::Scene*>(camera_struct.scene))
                {
                    scene_parent = std::get<yli::ontology::Scene*>(camera_struct.scene);
                }
                else if (std::holds_alternative<std::string>(camera_struct.scene))
                {
                    scene_parent = dynamic_cast<yli::ontology::Scene*>(this->get_universe().registry.get_entity(std::get<std::string>(camera_struct.scene)));
                }

                yli::ontology::Camera* const camera = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        camera_struct,
                        (scene_parent != nullptr ? &scene_parent->parent_of_cameras : nullptr),
                        (camera_struct.brain != nullptr ? camera_struct.brain->get_generic_master_module() : nullptr));

                camera->set_global_name(camera_struct.global_name);
                camera->set_local_name(camera_struct.local_name);
                return camera;
            }

            yli::ontology::Camera* create_default_camera(const yli::ontology::CameraStruct& camera_struct) const override
            {
                using CameraMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::Camera, 256>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<CameraMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::CAMERA));
                CameraMemoryAllocator& allocator = static_cast<CameraMemoryAllocator&>(generic_allocator);

                yli::ontology::Scene* scene_parent { nullptr };
                if (std::holds_alternative<yli::ontology::Scene*>(camera_struct.scene))
                {
                    scene_parent = std::get<yli::ontology::Scene*>(camera_struct.scene);
                }
                else if (std::holds_alternative<std::string>(camera_struct.scene))
                {
                    scene_parent = dynamic_cast<yli::ontology::Scene*>(this->get_universe().registry.get_entity(std::get<std::string>(camera_struct.scene)));
                }

                yli::ontology::Camera* const camera = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        camera_struct,
                        (scene_parent != nullptr ? &scene_parent->parent_of_default_camera : nullptr),
                        (camera_struct.brain != nullptr ? camera_struct.brain->get_generic_master_module() : nullptr));

                camera->set_global_name(camera_struct.global_name);
                camera->set_local_name(camera_struct.local_name);
                return camera;
            }

            // TODO: implement `create_camera_widget` here!

            yli::ontology::Pipeline* create_pipeline(const yli::ontology::PipelineStruct& pipeline_struct) const override
            {
                using PipelineMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::Pipeline, 256>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<PipelineMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::PIPELINE));
                PipelineMemoryAllocator& allocator = static_cast<PipelineMemoryAllocator&>(generic_allocator);

                yli::ontology::Pipeline* const pipeline = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        pipeline_struct,
                        // `Ecosystem` or `Scene` parent.
                        ((std::holds_alternative<yli::ontology::Ecosystem*>(pipeline_struct.parent) && std::get<yli::ontology::Ecosystem*>(pipeline_struct.parent) != nullptr) ?
                         &(std::get<yli::ontology::Ecosystem*>(pipeline_struct.parent)->parent_of_pipelines) :
                         (std::holds_alternative<yli::ontology::Scene*>(pipeline_struct.parent) && std::get<yli::ontology::Scene*>(pipeline_struct.parent) != nullptr) ?
                         &(std::get<yli::ontology::Scene*>(pipeline_struct.parent)->parent_of_pipelines) :
                         nullptr));
                pipeline->set_global_name(pipeline_struct.global_name);
                pipeline->set_local_name(pipeline_struct.local_name);
                return pipeline;
            }

            yli::ontology::Material* create_material(const yli::ontology::MaterialStruct& material_struct) const override
            {
                using MaterialMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::Material, 256>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<MaterialMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::MATERIAL));
                MaterialMemoryAllocator& allocator = static_cast<MaterialMemoryAllocator&>(generic_allocator);

                yli::ontology::Material* const material = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        material_struct,
                        // `Ecosystem` or `Scene` parent.
                        ((std::holds_alternative<yli::ontology::Ecosystem*>(material_struct.parent) && std::get<yli::ontology::Ecosystem*>(material_struct.parent) != nullptr) ?
                         &(std::get<yli::ontology::Ecosystem*>(material_struct.parent)->parent_of_materials) :
                         (std::holds_alternative<yli::ontology::Scene*>(material_struct.parent) && std::get<yli::ontology::Scene*>(material_struct.parent) != nullptr) ?
                         &(std::get<yli::ontology::Scene*>(material_struct.parent)->parent_of_materials) :
                         nullptr),
                        (material_struct.pipeline != nullptr ? material_struct.pipeline->get_master_module() : nullptr));

                material->set_global_name(material_struct.global_name);
                material->set_local_name(material_struct.local_name);
                return material;
            }

            yli::ontology::Species* create_species(const yli::ontology::SpeciesStruct& species_struct) const override
            {
                using SpeciesMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::Species, 256>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<SpeciesMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::SPECIES));
                SpeciesMemoryAllocator& allocator = static_cast<SpeciesMemoryAllocator&>(generic_allocator);

                auto& material_or_symbiont_material = species_struct.material_or_symbiont_material;

                yli::ontology::Species* const species = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        species_struct,
                        // `Ecosystem` or `Scene` parent.
                        ((std::holds_alternative<yli::ontology::Ecosystem*>(species_struct.parent) && std::get<yli::ontology::Ecosystem*>(species_struct.parent) != nullptr) ? &(std::get<yli::ontology::Ecosystem*>(species_struct.parent)->parent_of_species) :
                         (std::holds_alternative<yli::ontology::Scene*>(species_struct.parent) && std::get<yli::ontology::Scene*>(species_struct.parent) != nullptr) ? &(std::get<yli::ontology::Scene*>(species_struct.parent)->parent_of_species) :
                         nullptr),
                        (std::holds_alternative<yli::ontology::Material*>(material_or_symbiont_material) &&
                         std::get<yli::ontology::Material*>(material_or_symbiont_material) != nullptr ?
                         &(std::get<yli::ontology::Material*>(material_or_symbiont_material)->master_of_species) : nullptr));

                species->set_global_name(species_struct.global_name);
                species->set_local_name(species_struct.local_name);
                return species;
            }

            yli::ontology::Object* create_object(const yli::ontology::ObjectStruct& object_struct) const override
            {
                using ObjectMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::Object, 256>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<ObjectMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::OBJECT));
                ObjectMemoryAllocator& allocator = static_cast<ObjectMemoryAllocator&>(generic_allocator);

                yli::ontology::Scene* scene_parent { nullptr };
                if (std::holds_alternative<yli::ontology::Scene*>(object_struct.scene))
                {
                    scene_parent = std::get<yli::ontology::Scene*>(object_struct.scene);
                }
                else if (std::holds_alternative<std::string>(object_struct.scene))
                {
                    scene_parent = dynamic_cast<yli::ontology::Scene*>(this->get_universe().registry.get_entity(std::get<std::string>(object_struct.scene)));
                }

                yli::ontology::Object* const object = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        object_struct,
                        // `Scene` parent.
                        ((scene_parent != nullptr) ? &scene_parent->parent_of_objects : nullptr),
                        // mesh master.
                        ((std::holds_alternative<yli::ontology::Species*>(object_struct.mesh_master) && std::get<yli::ontology::Species*>(object_struct.mesh_master) != nullptr) ?
                         &(std::get<yli::ontology::Species*>(object_struct.mesh_master)->master_of_objects) :
                         (std::holds_alternative<yli::ontology::ShapeshifterSequence*>(object_struct.mesh_master) && std::get<yli::ontology::ShapeshifterSequence*>(object_struct.mesh_master) != nullptr) ?
                         &(std::get<yli::ontology::ShapeshifterSequence*>(object_struct.mesh_master)->master_of_objects) :
                         (std::holds_alternative<yli::ontology::Text3D*>(object_struct.mesh_master) && std::get<yli::ontology::Text3D*>(object_struct.mesh_master) != nullptr) ?
                         &(std::get<yli::ontology::Text3D*>(object_struct.mesh_master)->master_of_objects) :
                         nullptr),
                        // `Brain` master.
                        (object_struct.brain != nullptr ? object_struct.brain->get_generic_master_module() : nullptr));

                object->set_global_name(object_struct.global_name);
                object->set_local_name(object_struct.local_name);
                return object;
            }

            // TODO: implement `create_heightmap` here!

            // TODO: implement `create_heightmap_sheet` here!

            yli::ontology::Symbiosis* create_symbiosis(const yli::ontology::SymbiosisStruct& symbiosis_struct) const override
            {
                using SymbiosisMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::Symbiosis, 256>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<SymbiosisMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::SYMBIOSIS));
                SymbiosisMemoryAllocator& allocator = static_cast<SymbiosisMemoryAllocator&>(generic_allocator);

                yli::ontology::Symbiosis* const symbiosis = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        symbiosis_struct,
                        // `Ecosystem` or `Scene` parent.
                        ((std::holds_alternative<yli::ontology::Ecosystem*>(symbiosis_struct.parent) && std::get<yli::ontology::Ecosystem*>(symbiosis_struct.parent) != nullptr) ? &(std::get<yli::ontology::Ecosystem*>(symbiosis_struct.parent)->parent_of_symbioses) :
                         (std::holds_alternative<yli::ontology::Scene*>(symbiosis_struct.parent) && std::get<yli::ontology::Scene*>(symbiosis_struct.parent) != nullptr) ? &(std::get<yli::ontology::Scene*>(symbiosis_struct.parent)->parent_of_symbioses) :
                         nullptr),
                        (symbiosis_struct.pipeline != nullptr ? &symbiosis_struct.pipeline->master_of_symbioses : nullptr));

                symbiosis->set_global_name(symbiosis_struct.global_name);
                symbiosis->set_local_name(symbiosis_struct.local_name);
                return symbiosis;
            }

            yli::ontology::SymbiontMaterial* create_symbiont_material(const MaterialStruct& material_struct) const override
            {
                using SymbiontMaterialMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::SymbiontMaterial, 256>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<SymbiontMaterialMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::SYMBIONT_MATERIAL));
                SymbiontMaterialMemoryAllocator& allocator = static_cast<SymbiontMaterialMemoryAllocator&>(generic_allocator);

                return allocator.build_in(
                        this->application,
                        this->get_universe(),
                        material_struct,
                        ((std::holds_alternative<yli::ontology::Symbiosis*>(material_struct.parent) &&
                          std::get<yli::ontology::Symbiosis*>(material_struct.parent) != nullptr) ?
                         &(std::get<yli::ontology::Symbiosis*>(material_struct.parent)->parent_of_symbiont_materials) :
                         nullptr));
            }

            yli::ontology::SymbiontSpecies* create_symbiont_species(const yli::ontology::SymbiontSpeciesStruct& symbiont_species_struct) const override
            {
                using SymbiontSpeciesMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::SymbiontSpecies, 256>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<SymbiontSpeciesMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::SYMBIONT_SPECIES));
                SymbiontSpeciesMemoryAllocator& allocator = static_cast<SymbiontSpeciesMemoryAllocator&>(generic_allocator);

                return allocator.build_in(
                        this->application,
                        this->get_universe(),
                        symbiont_species_struct,
                        (symbiont_species_struct.symbiont_material != nullptr ?
                         &(symbiont_species_struct.symbiont_material->parent_of_symbiont_species) :
                         nullptr));
            }

            yli::ontology::Holobiont* create_holobiont(const yli::ontology::HolobiontStruct& holobiont_struct) const override
            {
                using HolobiontMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::Holobiont, 256>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<HolobiontMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::HOLOBIONT));
                HolobiontMemoryAllocator& allocator = static_cast<HolobiontMemoryAllocator&>(generic_allocator);

                yli::ontology::Scene* scene_parent { nullptr };
                if (std::holds_alternative<yli::ontology::Scene*>(holobiont_struct.scene))
                {
                    scene_parent = std::get<yli::ontology::Scene*>(holobiont_struct.scene);
                }
                else if (std::holds_alternative<std::string>(holobiont_struct.scene))
                {
                    scene_parent = dynamic_cast<yli::ontology::Scene*>(this->get_universe().registry.get_entity(std::get<std::string>(holobiont_struct.scene)));
                }

                yli::ontology::Holobiont* const holobiont = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        holobiont_struct,
                        (scene_parent != nullptr ? &scene_parent->parent_of_holobionts : nullptr),
                        (holobiont_struct.symbiosis != nullptr ? &holobiont_struct.symbiosis->master_of_holobionts : nullptr),
                        (holobiont_struct.brain != nullptr ? holobiont_struct.brain->get_generic_master_module() : nullptr));

                holobiont->set_global_name(holobiont_struct.global_name);
                holobiont->set_local_name(holobiont_struct.local_name);
                return holobiont;
            }

            yli::ontology::Biont* create_biont(const yli::ontology::BiontStruct& biont_struct) const override
            {
                using BiontMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::Biont, 1024>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<BiontMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::BIONT));
                BiontMemoryAllocator& allocator = static_cast<BiontMemoryAllocator&>(generic_allocator);

                return allocator.build_in(
                        this->application,
                        this->get_universe(),
                        biont_struct,
                        (biont_struct.parent != nullptr ? &biont_struct.parent->parent_of_bionts : nullptr),
                        (biont_struct.symbiont_species != nullptr ? &biont_struct.symbiont_species->master_of_bionts : nullptr));
            }

            yli::ontology::ShapeshifterTransformation* create_shapeshifter_transformation(
                    const yli::ontology::ModelStruct& model_struct) const override
            {
                using ShapeshifterTransformationMemoryAllocator =
                    yli::memory::MemoryAllocator<yli::ontology::ShapeshifterTransformation, 1024>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<ShapeshifterTransformationMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::SHAPESHIFTER_TRANSFORMATION));
                ShapeshifterTransformationMemoryAllocator& allocator = static_cast<ShapeshifterTransformationMemoryAllocator&>(generic_allocator);

                auto& material_or_symbiont_material = model_struct.material_or_symbiont_material;

                yli::ontology::ShapeshifterTransformation* const shapeshifter_transformation = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        model_struct,
                        (std::holds_alternative<yli::ontology::Material*>(material_or_symbiont_material) &&
                         std::get<yli::ontology::Material*>(material_or_symbiont_material) != nullptr ?
                         &(std::get<yli::ontology::Material*>(material_or_symbiont_material)->parent_of_shapeshifter_transformations) :
                         nullptr));

                shapeshifter_transformation->set_global_name(model_struct.global_name);
                shapeshifter_transformation->set_local_name(model_struct.local_name);
                return shapeshifter_transformation;
            }

            yli::ontology::ShapeshifterSequence* create_shapeshifter_sequence(
                    const yli::ontology::ShapeshifterSequenceStruct& shapeshifter_sequence_struct) const override
            {
                using ShapeshifterSequenceMemoryAllocator =
                    yli::memory::MemoryAllocator<yli::ontology::ShapeshifterSequence, 1024>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<ShapeshifterSequenceMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::SHAPESHIFTER_SEQUENCE));
                ShapeshifterSequenceMemoryAllocator& allocator = static_cast<ShapeshifterSequenceMemoryAllocator&>(generic_allocator);

                yli::ontology::ShapeshifterSequence* const shapeshifter_sequence = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        shapeshifter_sequence_struct,
                        (shapeshifter_sequence_struct.parent != nullptr ? &shapeshifter_sequence_struct.parent->parent_of_shapeshifter_sequences :
                         nullptr));

                shapeshifter_sequence->set_global_name(shapeshifter_sequence_struct.global_name);
                shapeshifter_sequence->set_local_name(shapeshifter_sequence_struct.local_name);
                return shapeshifter_sequence;
            }

            yli::ontology::ShapeshifterForm* create_shapeshifter_form(
                    const yli::ontology::ModelStruct& model_struct) const override
            {
                using ShapeshifterFormMemoryAllocator =
                    yli::memory::MemoryAllocator<yli::ontology::ShapeshifterForm, 1024>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<ShapeshifterFormMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::SHAPESHIFTER_FORM));
                ShapeshifterFormMemoryAllocator& allocator = static_cast<ShapeshifterFormMemoryAllocator&>(generic_allocator);

                yli::ontology::ShapeshifterForm* const shapeshifter_form = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        model_struct,
                        (model_struct.shapeshifter_transformation != nullptr ? &model_struct.shapeshifter_transformation->parent_of_shapeshifter_forms :
                         nullptr));

                shapeshifter_form->set_global_name(model_struct.global_name);
                shapeshifter_form->set_local_name(model_struct.local_name);
                return shapeshifter_form;
            }

            yli::ontology::Font2D* create_font_2d(const yli::ontology::FontStruct& font_struct) const override
            {
                using Font2DMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::Font2D, 256>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<Font2DMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::FONT_2D));
                Font2DMemoryAllocator& allocator = static_cast<Font2DMemoryAllocator&>(generic_allocator);

                yli::ontology::Font2D* const font_2d = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        font_struct,
                        &this->get_universe().parent_of_font_2ds);

                if (!font_struct.global_name.empty() && font_struct.local_name.empty())
                {
                    // Only `global_name` given, OK.
                    font_2d->set_global_name(font_struct.global_name);
                }
                else if (font_struct.global_name.empty() && !font_struct.local_name.empty())
                {
                    // Only `local_name` given, OK.
                    font_2d->set_local_name(font_struct.local_name);
                }
                else if (!font_struct.global_name.empty() && !font_struct.local_name.empty())
                {
                    std::cerr << "ERROR: `EntityFactory::create_font_2d`: both global and local names given for a `Font2D`\n";
                    std::cerr << "which is a child of `Universe`. For children of the `Universe` global and local names\n";
                    std::cerr << "are the same and only 1 of them can be given. No name given to this `Font2D`!\n";
                }

                return font_2d;
            }

            yli::ontology::Text2D* create_text_2d(const yli::ontology::TextStruct& text_struct) const override
            {
                using Text2DMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::Text2D, 256>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<Text2DMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::TEXT_2D));
                Text2DMemoryAllocator& allocator = static_cast<Text2DMemoryAllocator&>(generic_allocator);

                yli::ontology::Text2D* const text_2d = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        text_struct,
                        (text_struct.parent != nullptr ? &text_struct.parent->parent_of_text_2ds : nullptr));

                text_2d->set_global_name(text_struct.global_name);
                text_2d->set_local_name(text_struct.local_name);
                return text_2d;
            }

            yli::ontology::VectorFont* create_vector_font(const yli::ontology::VectorFontStruct& vector_font_struct) const override
            {
                using VectorFontMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::VectorFont, 256>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<VectorFontMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::VECTOR_FONT));
                VectorFontMemoryAllocator& allocator = static_cast<VectorFontMemoryAllocator&>(generic_allocator);

                yli::ontology::VectorFont* const vector_font = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        vector_font_struct,
                        (vector_font_struct.parent != nullptr ? &vector_font_struct.parent->parent_of_vector_fonts : nullptr));

                vector_font->set_global_name(vector_font_struct.global_name);
                vector_font->set_local_name(vector_font_struct.local_name);
                return vector_font;
            }

            yli::ontology::Glyph* create_glyph(const yli::ontology::ModelStruct& model_struct) const override
            {
                using GlyphMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::Glyph, 256>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<GlyphMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::GLYPH));
                GlyphMemoryAllocator& allocator = static_cast<GlyphMemoryAllocator&>(generic_allocator);

                yli::ontology::Glyph* const glyph = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        model_struct,
                        (std::holds_alternative<yli::ontology::VectorFont*>(model_struct.parent) && (std::get<yli::ontology::VectorFont*>(model_struct.parent) != nullptr) ?
                         &(std::get<yli::ontology::VectorFont*>(model_struct.parent)->parent_of_glyphs) :
                         nullptr));

                return glyph;
            }

            yli::ontology::Text3D* create_text_3d(const yli::ontology::Text3DStruct& text_3d_struct) const override
            {
                using Text3DMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::Text3D, 256>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<Text3DMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::TEXT_3D));
                Text3DMemoryAllocator& allocator = static_cast<Text3DMemoryAllocator&>(generic_allocator);

                yli::ontology::Text3D* const text_3d = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        text_3d_struct,
                        (text_3d_struct.parent != nullptr ? &text_3d_struct.parent->parent_of_text_3ds : nullptr),
                        (text_3d_struct.brain != nullptr ? text_3d_struct.brain->get_generic_master_module() : nullptr));

                text_3d->set_global_name(text_3d_struct.global_name);
                text_3d->set_local_name(text_3d_struct.local_name);
                return text_3d;
            }

            yli::ontology::InputMode* create_input_mode(const yli::ontology::InputModeStruct& input_mode_struct) const override
            {
                using InputModeMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::InputMode, 256>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<InputModeMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::INPUT_MODE));
                InputModeMemoryAllocator& allocator = static_cast<InputModeMemoryAllocator&>(generic_allocator);

                yli::ontology::InputMode* const input_mode = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        input_mode_struct,
                        &this->get_universe().parent_of_input_modes,
                        (input_mode_struct.console != nullptr ? &input_mode_struct.console->master_of_input_modes : nullptr));

                if (!input_mode_struct.global_name.empty() && input_mode_struct.local_name.empty())
                {
                    // Only `global_name` given, OK.
                    input_mode->set_global_name(input_mode_struct.global_name);
                }
                else if (input_mode_struct.global_name.empty() && !input_mode_struct.local_name.empty())
                {
                    // Only `local_name` given, OK.
                    input_mode->set_local_name(input_mode_struct.local_name);
                }
                else if (!input_mode_struct.global_name.empty() && !input_mode_struct.local_name.empty())
                {
                    std::cerr << "ERROR: `EntityFactory::create_input_mode`: both global and local names given for a `InputMode`\n";
                    std::cerr << "which is a child of `Universe`. For children of the `Universe` global and local names\n";
                    std::cerr << "are the same and only 1 of them can be given. No name given to this `InputMode`!\n";
                }

                return input_mode;
            }

            // TODO: implement `create_key_binding` here!

            // TODO: implement `create_playlist` here!

            yli::ontology::AudioTrack* create_audio_track(const yli::ontology::AudioTrackStruct& audio_track_struct) const override
            {
                using AudioTrackMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::AudioTrack, 256>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<AudioTrackMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::AUDIO_TRACK));
                AudioTrackMemoryAllocator& allocator = static_cast<AudioTrackMemoryAllocator&>(generic_allocator);

                yli::ontology::AudioTrack* const audio_track = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        audio_track_struct,
                        &this->get_universe().parent_of_audio_tracks);

                if (!audio_track_struct.global_name.empty() && audio_track_struct.local_name.empty())
                {
                    // Only `global_name` given, OK.
                    audio_track->set_global_name(audio_track_struct.global_name);
                }
                else if (audio_track_struct.global_name.empty() && !audio_track_struct.local_name.empty())
                {
                    // Only `local_name` given, OK.
                    audio_track->set_local_name(audio_track_struct.local_name);
                }
                else if (!audio_track_struct.global_name.empty() && !audio_track_struct.local_name.empty())
                {
                    std::cerr << "ERROR: `EntityFactory::create_audio_track`: both global and local names given for a `AudioTrack`\n";
                    std::cerr << "which is a child of `Universe`. For children of the `Universe` global and local names\n";
                    std::cerr << "are the same and only 1 of them can be given. No name given to this `AudioTrack`!\n";
                }

                return audio_track;
            }

            yli::ontology::Console* create_console(const yli::ontology::ConsoleStruct& console_struct) const override
            {
                using ConsoleMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::Console, 256>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<ConsoleMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::CONSOLE));
                ConsoleMemoryAllocator& allocator = static_cast<ConsoleMemoryAllocator&>(generic_allocator);

                yli::ontology::Console* const console = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        console_struct,
                        &this->get_universe().parent_of_consoles,
                        (console_struct.font_2d != nullptr ? &console_struct.font_2d->master_of_consoles : nullptr));

                if (!console_struct.global_name.empty() && console_struct.local_name.empty())
                {
                    // Only `global_name` given, OK.
                    console->set_global_name(console_struct.global_name);
                }
                else if (console_struct.global_name.empty() && !console_struct.local_name.empty())
                {
                    // Only `local_name` given, OK.
                    console->set_local_name(console_struct.local_name);
                }
                else if (!console_struct.global_name.empty() && !console_struct.local_name.empty())
                {
                    std::cerr << "ERROR: `EntityFactory::create_console`: both global and local names given for a `Console`\n";
                    std::cerr << "which is a child of `Universe`. For children of the `Universe` global and local names\n";
                    std::cerr << "are the same and only 1 of them can be given. No name given to this `Console`!\n";
                }

                return console;
            }

            yli::ontology::ConsoleCallbackEngine* create_console_callback_engine(
                    const yli::ontology::ConsoleCallbackEngineStruct& console_callback_engine_struct) const override
            {
                using ConsoleCallbackEngineMemoryAllocator =
                    yli::memory::MemoryAllocator<yli::ontology::ConsoleCallbackEngine, 256>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<ConsoleCallbackEngineMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::CONSOLE_CALLBACK_ENGINE));
                ConsoleCallbackEngineMemoryAllocator& allocator = static_cast<ConsoleCallbackEngineMemoryAllocator&>(generic_allocator);

                yli::ontology::ConsoleCallbackEngine* const console_callback_engine = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        &this->get_universe().parent_of_console_callback_engines);

                if (!console_callback_engine_struct.global_name.empty() && console_callback_engine_struct.local_name.empty())
                {
                    // Only `global_name` given, OK.
                    console_callback_engine->set_global_name(console_callback_engine_struct.global_name);
                }
                else if (console_callback_engine_struct.global_name.empty() && !console_callback_engine_struct.local_name.empty())
                {
                    // Only `local_name` given, OK.
                    console_callback_engine->set_local_name(console_callback_engine_struct.local_name);
                }
                else if (!console_callback_engine_struct.global_name.empty() && !console_callback_engine_struct.local_name.empty())
                {
                    std::cerr << "ERROR: `EntityFactory::create_console_callback_engine`: both global and local names given for a `ConsoleCallbackEngine`\n";
                    std::cerr << "which is a child of `Universe`. For children of the `Universe` global and local names\n";
                    std::cerr << "are the same and only 1 of them can be given. No name given to this `ConsoleCallbackEngine`!\n";
                }

                return console_callback_engine;
            }

            yli::ontology::ConsoleCallbackObject* create_console_callback_object(
                    const yli::ontology::ConsoleCallbackObjectStruct& console_callback_object_struct) const override
            {
                using ConsoleCallbackObjectMemoryAllocator =
                    yli::memory::MemoryAllocator<yli::ontology::ConsoleCallbackObject, 256>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<ConsoleCallbackObjectMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::CONSOLE_CALLBACK_OBJECT));
                ConsoleCallbackObjectMemoryAllocator& allocator = static_cast<ConsoleCallbackObjectMemoryAllocator&>(generic_allocator);

                yli::ontology::ConsoleCallbackObject* const console_callback_object = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        console_callback_object_struct,
                        ((console_callback_object_struct.parent != nullptr) ?
                         &console_callback_object_struct.parent->parent_of_console_callback_objects :
                         nullptr));

                console_callback_object->set_global_name(console_callback_object_struct.global_name);
                console_callback_object->set_local_name(console_callback_object_struct.local_name);
                return console_callback_object;
            }

            yli::ontology::ConsoleCallbackParameter* create_console_callback_parameter(
                    const yli::ontology::ConsoleCallbackParameterStruct& console_callback_parameter_struct,
                    const yli::data::AnyValue& any_value) const override
            {
                using ConsoleCallbackParameterMemoryAllocator =
                    yli::memory::MemoryAllocator<yli::ontology::ConsoleCallbackParameter, 256>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<ConsoleCallbackParameterMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::CONSOLE_CALLBACK_PARAMETER));
                ConsoleCallbackParameterMemoryAllocator& allocator = static_cast<ConsoleCallbackParameterMemoryAllocator&>(generic_allocator);

                yli::ontology::ConsoleCallbackParameter* const console_callback_parameter = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        console_callback_parameter_struct,
                        any_value,
                        ((console_callback_parameter_struct.parent != nullptr) ?
                         &console_callback_parameter_struct.parent->parent_of_console_callback_parameters :
                         nullptr));

                console_callback_parameter->set_global_name(console_callback_parameter_struct.global_name);
                console_callback_parameter->set_local_name(console_callback_parameter_struct.local_name);
                return console_callback_parameter;
            }

            // TODO: implement `create_graph` here!

            // TODO: implement `create_node` here!

            yli::ontology::ComputeTask* create_compute_task(const yli::ontology::ComputeTaskStruct& compute_task_struct) const override
            {
                using ComputeTaskMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::ComputeTask, 256>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<ComputeTaskMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::COMPUTETASK));
                ComputeTaskMemoryAllocator& allocator = static_cast<ComputeTaskMemoryAllocator&>(generic_allocator);

                yli::ontology::ComputeTask* const compute_task = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        compute_task_struct,
                        compute_task_struct.parent != nullptr ? &compute_task_struct.parent->parent_of_compute_tasks : nullptr);

                compute_task->set_global_name(compute_task_struct.global_name);
                compute_task->set_local_name(compute_task_struct.local_name);
                return compute_task;
            }

            yli::ontology::LispFunction* create_lisp_function(const yli::ontology::LispFunctionStruct& lisp_function_struct) const override
            {
                using LispFunctionMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::LispFunction, 256>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<LispFunctionMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::LISP_FUNCTION));
                LispFunctionMemoryAllocator& allocator = static_cast<LispFunctionMemoryAllocator&>(generic_allocator);

                yli::ontology::LispFunction* const lisp_function = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        lisp_function_struct,
                        (lisp_function_struct.parent != nullptr ? &lisp_function_struct.parent->parent_of_lisp_functions : nullptr));

                lisp_function->set_global_name(lisp_function_struct.global_name);
                lisp_function->set_local_name(lisp_function_struct.local_name);
                return lisp_function;
            }

            template<typename... Args>
                yli::ontology::GenericLispFunctionOverload* create_lisp_function_overload(
                        const std::string& name,
                        yli::ontology::Console& console,
                        std::optional<yli::data::AnyValue>(*callback)(Args...))
                {
                    yli::ontology::Entity* const lisp_function_entity = this->get_universe().get_entity(name);

                    yli::ontology::LispFunction* lisp_function = nullptr;

                    if (lisp_function_entity == nullptr)
                    {
                        // There was not any `Entity` with that name.
                        yli::ontology::LispFunctionStruct lisp_function_struct;
                        lisp_function_struct.parent = &console;
                        lisp_function = this->create_lisp_function(lisp_function_struct);

                        if (lisp_function == nullptr)
                        {
                            // Creating `LispFunction` failed.
                            return nullptr;
                        }

                        // OK, set a name for the newly created `LispFunction`.
                        lisp_function->set_global_name(name);
                    }
                    else
                    {
                        lisp_function = dynamic_cast<yli::ontology::LispFunction*>(lisp_function_entity);

                        if (lisp_function == nullptr)
                        {
                            // The name is in use and the `Entity` is not a `LispFunction`.
                            return nullptr;
                        }
                    }

                    using GenericLispFunctionOverloadMemoryAllocator =
                        yli::memory::MemoryAllocator<yli::ontology::GenericLispFunctionOverload, 256>;

                    yli::memory::GenericMemoryAllocator& generic_allocator =
                        this->memory_system.template get_or_create_allocator<GenericLispFunctionOverloadMemoryAllocator>(
                                static_cast<int>(yli::data::Datatype::GENERIC_LISP_FUNCTION_OVERLOAD));

                    GenericLispFunctionOverloadMemoryAllocator& allocator =
                        static_cast<GenericLispFunctionOverloadMemoryAllocator&>(generic_allocator);

                    yli::ontology::GenericLispFunctionOverload* const generic_lisp_function_overload = allocator.build_in(
                            this->application,
                            this->get_universe(),
                            &lisp_function->parent_of_generic_lisp_function_overloads,
                            callback);
                    generic_lisp_function_overload->set_global_name(name);
                    return generic_lisp_function_overload;
                }

            template<typename T, typename ObjectDerivativeMemoryAllocator, typename... ModuleArgs>
                T* create_object_derivative(
                        int object_derivative_type,
                        const yli::ontology::ObjectStruct& object_struct,
                        ModuleArgs&&... module_args)
                {
                    yli::memory::GenericMemoryAllocator& generic_allocator =
                        this->memory_system.template get_or_create_allocator<ObjectDerivativeMemoryAllocator>(
                                static_cast<int>(object_derivative_type));

                    ObjectDerivativeMemoryAllocator& allocator =
                        static_cast<ObjectDerivativeMemoryAllocator&>(generic_allocator);

                    yli::ontology::Scene* scene_parent { nullptr };
                    if (std::holds_alternative<yli::ontology::Scene*>(object_struct.scene))
                    {
                        scene_parent = std::get<yli::ontology::Scene*>(object_struct.scene);
                    }
                    else if (std::holds_alternative<std::string>(object_struct.scene))
                    {
                        scene_parent = dynamic_cast<yli::ontology::Scene*>(this->get_universe().registry.get_entity(std::get<std::string>(object_struct.scene)));
                    }

                    T* const object = allocator.build_in(
                            this->application,
                            this->get_universe(),
                            object_struct,
                            module_args...,
                            // `Scene` parent.
                            ((scene_parent != nullptr) ? &scene_parent->parent_of_objects : nullptr),
                            // mesh master.
                            ((std::holds_alternative<yli::ontology::Species*>(object_struct.mesh_master) && std::get<yli::ontology::Species*>(object_struct.mesh_master) != nullptr) ?
                             &(std::get<yli::ontology::Species*>(object_struct.mesh_master)->master_of_objects) :
                             (std::holds_alternative<yli::ontology::ShapeshifterSequence*>(object_struct.mesh_master) && std::get<yli::ontology::ShapeshifterSequence*>(object_struct.mesh_master) != nullptr) ?
                             &(std::get<yli::ontology::ShapeshifterSequence*>(object_struct.mesh_master)->master_of_objects) :
                             (std::holds_alternative<yli::ontology::Text3D*>(object_struct.mesh_master) && std::get<yli::ontology::Text3D*>(object_struct.mesh_master) != nullptr) ?
                             &(std::get<yli::ontology::Text3D*>(object_struct.mesh_master)->master_of_objects) :
                             nullptr),
                            // `Brain` master.
                            (object_struct.brain != nullptr ? object_struct.brain->get_generic_master_module() : nullptr));

                    object->set_global_name(object_struct.global_name);
                    object->set_local_name(object_struct.local_name);
                    return object;
                }

            template<typename T, typename HolobiontDerivativeMemoryAllocator, typename... ModuleArgs>
                T* create_holobiont_derivative(
                        int holobiont_derivative_type,
                        const yli::ontology::HolobiontStruct& holobiont_struct,
                        ModuleArgs&&... module_args)
                {
                    yli::memory::GenericMemoryAllocator& generic_allocator =
                        this->memory_system.template get_or_create_allocator<HolobiontDerivativeMemoryAllocator>(
                                static_cast<int>(holobiont_derivative_type));

                    HolobiontDerivativeMemoryAllocator& allocator =
                        static_cast<HolobiontDerivativeMemoryAllocator&>(generic_allocator);

                    yli::ontology::Scene* scene_parent { nullptr };
                    if (std::holds_alternative<yli::ontology::Scene*>(holobiont_struct.scene))
                    {
                        scene_parent = std::get<yli::ontology::Scene*>(holobiont_struct.scene);
                    }
                    else if (std::holds_alternative<std::string>(holobiont_struct.scene))
                    {
                        scene_parent = dynamic_cast<yli::ontology::Scene*>(this->get_universe().registry.get_entity(std::get<std::string>(holobiont_struct.scene)));
                    }

                    T* const holobiont = allocator.build_in(
                            this->application,
                            this->get_universe(),
                            holobiont_struct,
                            module_args...,
                            (scene_parent != nullptr ? &scene_parent->parent_of_holobionts : nullptr),
                            (holobiont_struct.symbiosis != nullptr ? &holobiont_struct.symbiosis->master_of_holobionts : nullptr),
                            (holobiont_struct.brain != nullptr ? holobiont_struct.brain->get_generic_master_module() : nullptr));

                    holobiont->set_global_name(holobiont_struct.global_name);
                    holobiont->set_local_name(holobiont_struct.local_name);
                    return holobiont;
                }

        private:
            yli::core::Application& application;
            yli::memory::MemorySystem<TypeEnumType>& memory_system;
            yli::ontology::Universe* universe { nullptr };
    };
}

#endif
