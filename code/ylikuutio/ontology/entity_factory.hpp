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
#include "movable.hpp"
#include "universe.hpp"
#include "variable.hpp"
#include "callback_engine.hpp"
#include "callback_object.hpp"
#include "callback_parameter.hpp"
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
#include "shapeshifter_transformation.hpp"
#include "shapeshifter_sequence.hpp"
#include "shapeshifter_form.hpp"
#include "font_2d.hpp"
#include "text_2d.hpp"
#include "vector_font.hpp"
#include "glyph.hpp"
#include "text_3d.hpp"
#include "input_mode.hpp"
#include "audio_track.hpp"
#include "console.hpp"
#include "console_callback_engine.hpp"
#include "console_callback_object.hpp"
#include "console_callback_parameter.hpp"
#include "compute_task.hpp"
#include "lisp_function.hpp"
#include "generic_lisp_function_overload.hpp"
#include "lisp_function_overload.hpp"
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
#include "species_struct.hpp"
#include "object_struct.hpp"
#include "symbiosis_struct.hpp"
#include "symbiont_material_struct.hpp"
#include "symbiont_species_struct.hpp"
#include "holobiont_struct.hpp"
#include "biont_struct.hpp"
#include "shapeshifter_transformation_struct.hpp"
#include "shapeshifter_sequence_struct.hpp"
#include "shapeshifter_form_struct.hpp"
#include "font_struct.hpp"
#include "text_struct.hpp"
#include "vector_font_struct.hpp"
#include "glyph_struct.hpp"
#include "text_3d_struct.hpp"
#include "input_mode_struct.hpp"
#include "audio_track_struct.hpp"
#include "console_struct.hpp"
#include "console_callback_engine_struct.hpp"
#include "console_callback_object_struct.hpp"
#include "console_callback_parameter_struct.hpp"
#include "compute_task_struct.hpp"
#include "lisp_function_struct.hpp"
#include "input_parameters_and_any_value_to_any_value_callback_with_universe.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/data/datatype.hpp"
#include "code/ylikuutio/memory/memory_system.hpp"
#include "code/ylikuutio/memory/memory_allocator.hpp"
#include "code/ylikuutio/memory/memory_allocator_types.hpp"

// Include standard headers
#include <concepts>  // std::derived_from, std::same_as
#include <iostream>  // std::cerr
#include <optional>  // std::optional
#include <stdexcept> // std::runtime_error
#include <string>    // std::string
#include <tuple>     // std::tuple
#include <utility>   // std::forward, std::move
#include <variant>   // std::holds_alternative

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
    struct UniverseStruct;

    template<typename T>
        concept EntityNotUniverse =
        std::derived_from<T, Entity> && (!std::same_as<T, Universe>);

    template<typename TypeEnumType>
        class EntityFactory : public GenericEntityFactory
    {
        public:
            EntityFactory(
                    yli::core::Application& application,
                    yli::memory::MemorySystem<TypeEnumType>& memory_system)
                : application { application },
                memory_system { memory_system }
            {
            }

            EntityFactory<TypeEnumType>& get() const
            {
                return const_cast<EntityFactory<TypeEnumType>&>(*this);
            }

            Universe* create_universe(const UniverseStruct& universe_struct)
            {
                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<yli::memory::UniverseMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::UNIVERSE));
                auto& allocator = static_cast<yli::memory::UniverseMemoryAllocator&>(generic_allocator);

                Universe* const universe = allocator.build_in(
                        this->application,
                        universe_struct);

                this->universe = universe;
                return universe;
            }

            Universe& get_universe() const
            {
                if (this->universe == nullptr) [[unlikely]]
                {
                    throw std::runtime_error("ERROR: `EntityFactory::get_universe`: `this->universe` is `nullptr`!");
                }

                return *this->universe;
            }

            Variable* create_variable(
                    const VariableStruct& variable_struct,
                    yli::data::AnyValue&& any_value) const final
            {
                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<yli::memory::VariableMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::VARIABLE));
                auto& allocator = static_cast<yli::memory::VariableMemoryAllocator&>(generic_allocator);

                Entity* entity_parent { nullptr };
                if (std::holds_alternative<Entity*>(variable_struct.entity_parent))
                {
                    entity_parent = std::get<Entity*>(variable_struct.entity_parent);
                }
                else if (std::holds_alternative<std::string>(variable_struct.entity_parent))
                {
                    entity_parent = this->get_universe().registry.get_entity(std::get<std::string>(variable_struct.entity_parent));
                }

                // The `Universe&` needs to be taken from `VariableStruct`
                // because `Universe` constructor creates its `Variable`
                // instances using `EntityFactory` before `EntityFactory::create_universe`
                // has initialized `universe` member variable of `EntityFactory`.
                Variable* const variable = allocator.build_in(
                        this->application,
                        variable_struct.universe,
                        variable_struct,
                        ((entity_parent != nullptr) ? &entity_parent->parent_of_variables : nullptr),
                        std::move(any_value));

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

            CallbackEngine* create_callback_engine(
                    const CallbackEngineStruct& callback_engine_struct) const final
            {
                return this->create_child_of_universe<
                    CallbackEngine, GenericParentModule, yli::memory::CallbackEngineMemoryAllocator, CallbackEngineStruct>(
                            yli::data::Datatype::CALLBACK_ENGINE,
                            callback_engine_struct,
                            &this->get_universe().parent_of_callback_engines);
            }

            CallbackObject* create_callback_object(
                    const CallbackObjectStruct& callback_object_struct) const final
            {
                return this->create_child<
                    CallbackObject, CallbackEngine, yli::memory::CallbackObjectMemoryAllocator, CallbackObjectStruct>(
                            yli::data::Datatype::CALLBACK_OBJECT,
                            callback_object_struct.callback_engine_parent,
                            callback_object_struct,
                            {});
            }

            CallbackParameter* create_callback_parameter(
                    const CallbackParameterStruct& callback_parameter_struct,
                    yli::data::AnyValue&& any_value) const final
            {
                return this->create_child<
                    CallbackParameter, CallbackObject, yli::memory::CallbackParameterMemoryAllocator, CallbackParameterStruct>(
                            yli::data::Datatype::CALLBACK_PARAMETER,
                            callback_parameter_struct.callback_object_parent,
                            callback_parameter_struct,
                            {},
                            std::move(any_value));
            }

            // TODO: implement `create_window` here!

            // TODO: implement `create_widget` here!

            Ecosystem* create_ecosystem(const EcosystemStruct& ecosystem_struct) const final
            {
                return this->create_child_of_universe<
                    Ecosystem, GenericParentModule, yli::memory::EcosystemMemoryAllocator, EcosystemStruct>(
                            yli::data::Datatype::ECOSYSTEM,
                            ecosystem_struct,
                            &this->get_universe().parent_of_ecosystems);
            }

            Scene* create_scene(const SceneStruct& scene_struct) const final
            {
                return this->create_child_of_universe<
                    Scene, GenericParentModule, yli::memory::SceneMemoryAllocator, SceneStruct>(
                            yli::data::Datatype::SCENE,
                            scene_struct,
                            &this->get_universe().parent_of_scenes);
            }

            Brain* create_brain(const BrainStruct& brain_struct) const final
            {
                return this->create_child<
                    Brain, Scene, yli::memory::BrainMemoryAllocator, BrainStruct>(
                            yli::data::Datatype::BRAIN,
                            brain_struct.parent,
                            brain_struct,
                            {});
            }

            Waypoint* create_waypoint(const WaypointStruct& waypoint_struct) const final
            {
                return this->create_child<
                    Waypoint, Scene, yli::memory::WaypointMemoryAllocator, WaypointStruct>(
                            yli::data::Datatype::WAYPOINT,
                            waypoint_struct.scene,
                            waypoint_struct,
                            {},
                            (waypoint_struct.brain_master != nullptr ? waypoint_struct.brain_master->get_generic_master_module<Movable>() : nullptr));
            }

            Camera* create_camera(const CameraStruct& camera_struct) const final
            {
                return this->create_child<
                    Camera, Scene, yli::memory::CameraMemoryAllocator, CameraStruct>(
                            yli::data::Datatype::CAMERA,
                            camera_struct.scene,
                            camera_struct,
                            {},
                            (camera_struct.brain_master != nullptr ? camera_struct.brain_master->get_generic_master_module<Movable>() : nullptr));
            }

            Camera* create_default_camera(const CameraStruct& camera_struct) const final
            {
                return this->create_child<
                    Camera, Scene, yli::memory::CameraMemoryAllocator, CameraStruct>(
                            yli::data::Datatype::CAMERA,
                            camera_struct.scene,
                            camera_struct,
                            {},
                            (camera_struct.brain_master != nullptr ? camera_struct.brain_master->get_generic_master_module<Movable>() : nullptr));
            }

            // TODO: implement `create_camera_widget` here!

            Pipeline* create_pipeline(const PipelineStruct& pipeline_struct) const final
            {
                return this->create_child_of_ecosystem_or_scene<
                    Pipeline, yli::memory::PipelineMemoryAllocator, PipelineStruct>(
                            yli::data::Datatype::PIPELINE,
                            pipeline_struct);
            }

            Material* create_material(const MaterialStruct& material_struct) const final
            {
                return this->create_child_of_ecosystem_or_scene<
                    Material, yli::memory::MaterialMemoryAllocator, MaterialStruct>(
                            yli::data::Datatype::MATERIAL,
                            material_struct,
                            (material_struct.pipeline != nullptr ? material_struct.pipeline->get_master_module() : nullptr));
            }

            Species* create_species(const SpeciesStruct& species_struct) const final
            {
                auto& material_or_symbiont_material = species_struct.material_or_symbiont_material;
                auto const species_master_module = (std::holds_alternative<Material*>(material_or_symbiont_material) &&
                        std::get<Material*>(material_or_symbiont_material) != nullptr ?
                        &(std::get<Material*>(material_or_symbiont_material)->master_of_species) : nullptr);

                return this->create_child_of_ecosystem_or_scene<
                    Species, yli::memory::SpeciesMemoryAllocator, SpeciesStruct>(
                            yli::data::Datatype::SPECIES,
                            species_struct,
                            species_master_module);
            }

            Object* create_object(const ObjectStruct& object_struct) const final
            {
                return this->create_child<
                    Object, Scene, yli::memory::ObjectMemoryAllocator, ObjectStruct>(
                            yli::data::Datatype::OBJECT,
                            object_struct.scene,
                            object_struct,
                            {},
                            // `Brain` master.
                            (object_struct.brain_master != nullptr ? object_struct.brain_master->get_generic_master_module<Movable>() : nullptr),
                            // mesh master.
                            ((std::holds_alternative<Species*>(object_struct.mesh_master) && std::get<Species*>(object_struct.mesh_master) != nullptr) ?
                             &(std::get<Species*>(object_struct.mesh_master)->master_of_objects) :
                             (std::holds_alternative<ShapeshifterSequence*>(object_struct.mesh_master) && std::get<ShapeshifterSequence*>(object_struct.mesh_master) != nullptr) ?
                             &(std::get<ShapeshifterSequence*>(object_struct.mesh_master)->master_of_objects) :
                             (std::holds_alternative<Text3d*>(object_struct.mesh_master) && std::get<Text3d*>(object_struct.mesh_master) != nullptr) ?
                             &(std::get<Text3d*>(object_struct.mesh_master)->master_of_objects) :
                             nullptr));
            }

            // TODO: implement `create_heightmap` here!

            // TODO: implement `create_heightmap_sheet` here!

            Symbiosis* create_symbiosis(const SymbiosisStruct& symbiosis_struct) const final
            {
                auto& pipeline = symbiosis_struct.pipeline;
                auto const pipeline_master_module = (pipeline != nullptr ? &(pipeline->master_of_symbioses) : nullptr);

                return this->create_child_of_ecosystem_or_scene<
                    Symbiosis, yli::memory::SymbiosisMemoryAllocator, SymbiosisStruct>(
                            yli::data::Datatype::SYMBIOSIS,
                            symbiosis_struct,
                            pipeline_master_module);
            }

            SymbiontMaterial* create_symbiont_material(const SymbiontMaterialStruct& symbiont_material_struct) const final
            {
                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<yli::memory::SymbiontMaterialMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::SYMBIONT_MATERIAL));
                auto& allocator = static_cast<yli::memory::SymbiontMaterialMemoryAllocator&>(generic_allocator);

                return allocator.build_in(
                        this->application,
                        this->get_universe(),
                        symbiont_material_struct,
                        (symbiont_material_struct.symbiosis_parent != nullptr ?
                         &(symbiont_material_struct.symbiosis_parent->parent_of_symbiont_materials) :
                         nullptr));
            }

            SymbiontSpecies* create_symbiont_species(const SymbiontSpeciesStruct& symbiont_species_struct) const final
            {
                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<yli::memory::SymbiontSpeciesMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::SYMBIONT_SPECIES));
                auto& allocator = static_cast<yli::memory::SymbiontSpeciesMemoryAllocator&>(generic_allocator);

                SymbiontMaterial* symbiont_material_parent { nullptr };
                if (std::holds_alternative<SymbiontMaterial*>(symbiont_species_struct.symbiont_material_parent))
                {
                    symbiont_material_parent = std::get<SymbiontMaterial*>(symbiont_species_struct.symbiont_material_parent);
                }
                else if (std::holds_alternative<std::string>(symbiont_species_struct.symbiont_material_parent))
                {
                    symbiont_material_parent = dynamic_cast<SymbiontMaterial*>(this->get_universe().registry.get_entity(
                                std::get<std::string>(symbiont_species_struct.symbiont_material_parent)));
                }

                return allocator.build_in(
                        this->application,
                        this->get_universe(),
                        symbiont_species_struct,
                        (symbiont_material_parent != nullptr ?
                         &(symbiont_material_parent->parent_of_symbiont_species) :
                         nullptr));
            }

            Holobiont* create_holobiont(const HolobiontStruct& holobiont_struct) const final
            {
                return this->create_child<
                    Holobiont, Scene, yli::memory::HolobiontMemoryAllocator, HolobiontStruct>(
                            yli::data::Datatype::HOLOBIONT,
                            holobiont_struct.scene,
                            holobiont_struct,
                            {},
                            (holobiont_struct.symbiosis_master != nullptr ? &holobiont_struct.symbiosis_master->master_of_holobionts : nullptr),
                            (holobiont_struct.brain_master != nullptr ? holobiont_struct.brain_master->get_generic_master_module<Movable>() : nullptr));
            }

            Biont* create_biont(const BiontStruct& biont_struct) const final
            {
                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<yli::memory::BiontMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::BIONT));
                auto& allocator = static_cast<yli::memory::BiontMemoryAllocator&>(generic_allocator);

                return allocator.build_in(
                        this->application,
                        this->get_universe(),
                        biont_struct,
                        (biont_struct.parent != nullptr ? &biont_struct.parent->parent_of_bionts : nullptr),
                        (biont_struct.symbiont_species != nullptr ? &biont_struct.symbiont_species->master_of_bionts : nullptr));
            }

            ShapeshifterTransformation* create_shapeshifter_transformation(
                    const ShapeshifterTransformationStruct& shapeshifter_transformation_struct) const final
            {
                return this->create_child<
                    ShapeshifterTransformation, Material, yli::memory::ShapeshifterTransformationMemoryAllocator, ShapeshifterTransformationStruct>(
                            yli::data::Datatype::SHAPESHIFTER_TRANSFORMATION,
                            shapeshifter_transformation_struct.material_parent,
                            shapeshifter_transformation_struct,
                            {});
            }

            ShapeshifterSequence* create_shapeshifter_sequence(
                    const ShapeshifterSequenceStruct& shapeshifter_sequence_struct) const final
            {
                return this->create_child<
                    ShapeshifterSequence, ShapeshifterTransformation, yli::memory::ShapeshifterSequenceMemoryAllocator, ShapeshifterSequenceStruct>(
                            yli::data::Datatype::SHAPESHIFTER_SEQUENCE,
                            shapeshifter_sequence_struct.shapeshifter_transformation_parent,
                            shapeshifter_sequence_struct,
                            {});
            }

            ShapeshifterForm* create_shapeshifter_form(
                    const ShapeshifterFormStruct& shapeshifter_form_struct) const final
            {
                return this->create_child<
                    ShapeshifterForm, ShapeshifterTransformation, yli::memory::ShapeshifterFormMemoryAllocator, ShapeshifterFormStruct>(
                            yli::data::Datatype::SHAPESHIFTER_FORM,
                            shapeshifter_form_struct.parent,
                            shapeshifter_form_struct,
                            {});
            }

            Font2d* create_font_2d(const FontStruct& font_struct) const final
            {
                return this->create_child_of_universe<
                    Font2d, GenericParentModule, yli::memory::Font2dMemoryAllocator, FontStruct>(
                            yli::data::Datatype::FONT_2D,
                            font_struct,
                            &this->get_universe().parent_of_font_2ds);
            }

            Text2d* create_text_2d(const TextStruct& text_struct) const final
            {
                return this->create_child<
                    Text2d, Font2d, yli::memory::Text2dMemoryAllocator, TextStruct>(
                            yli::data::Datatype::TEXT_2D,
                            text_struct.font_2d_parent,
                            text_struct,
                            {});
            }

            VectorFont* create_vector_font(const VectorFontStruct& vector_font_struct) const final
            {
                return this->create_child<
                    VectorFont, Material, yli::memory::VectorFontMemoryAllocator, VectorFontStruct>(
                            yli::data::Datatype::VECTOR_FONT,
                            vector_font_struct.material_parent,
                            vector_font_struct,
                            {});
            }

            Glyph* create_glyph(const GlyphStruct& glyph_struct) const final
            {
                return this->create_child<
                    Glyph, VectorFont, yli::memory::GlyphMemoryAllocator, GlyphStruct>(
                            yli::data::Datatype::GLYPH,
                            glyph_struct.parent,
                            glyph_struct,
                            {});
            }

            Text3d* create_text_3d(const Text3dStruct& text_3d_struct) const final
            {
                return this->create_child<
                    Text3d, VectorFont, yli::memory::Text3dMemoryAllocator, Text3dStruct>(
                            yli::data::Datatype::TEXT_3D,
                            text_3d_struct.vector_font_parent,
                            text_3d_struct,
                            {},
                            (text_3d_struct.brain_master != nullptr ? text_3d_struct.brain_master->get_generic_master_module<Movable>() : nullptr));
            }

            InputMode* create_input_mode(const InputModeStruct& input_mode_struct) const final
            {
                return this->create_child_of_universe<
                    InputMode, ParentOfInputModesModule, yli::memory::InputModeMemoryAllocator, InputModeStruct>(
                            yli::data::Datatype::INPUT_MODE,
                            input_mode_struct,
                            &this->get_universe().parent_of_input_modes,
                            (input_mode_struct.console_master != nullptr ? &input_mode_struct.console_master->master_of_input_modes : nullptr));
            }

            // TODO: implement `create_key_binding` here!

            // TODO: implement `create_playlist` here!

            AudioTrack* create_audio_track(const AudioTrackStruct& audio_track_struct) const final
            {
                return this->create_child_of_universe<
                    AudioTrack, GenericParentModule, yli::memory::AudioTrackMemoryAllocator, AudioTrackStruct>(
                            yli::data::Datatype::AUDIO_TRACK,
                            audio_track_struct,
                            &this->get_universe().parent_of_audio_tracks);
            }

            Console* create_console(const ConsoleStruct& console_struct) const final
            {
                return this->create_child_of_universe<
                    Console, GenericParentModule, yli::memory::ConsoleMemoryAllocator, ConsoleStruct>(
                            yli::data::Datatype::CONSOLE,
                            console_struct,
                            &this->get_universe().parent_of_consoles,
                            (console_struct.font_2d != nullptr ? &console_struct.font_2d->master_of_consoles : nullptr));
            }

            ConsoleCallbackEngine* create_console_callback_engine(
                    const ConsoleCallbackEngineStruct& console_callback_engine_struct) const final
            {
                return this->create_child_of_universe<
                    ConsoleCallbackEngine, GenericParentModule, yli::memory::ConsoleCallbackEngineMemoryAllocator, ConsoleCallbackEngineStruct>(
                            yli::data::Datatype::CONSOLE_CALLBACK_ENGINE,
                            console_callback_engine_struct,
                            &this->get_universe().parent_of_console_callback_engines);
            }

            ConsoleCallbackObject* create_console_callback_object(
                    const ConsoleCallbackObjectStruct& console_callback_object_struct) const final
            {
                return this->create_child<
                    ConsoleCallbackObject, ConsoleCallbackEngine, yli::memory::ConsoleCallbackObjectMemoryAllocator, ConsoleCallbackObjectStruct>(
                            yli::data::Datatype::CONSOLE_CALLBACK_OBJECT,
                            console_callback_object_struct.console_callback_engine_parent,
                            console_callback_object_struct,
                            {});
            }

            ConsoleCallbackParameter* create_console_callback_parameter(
                    const ConsoleCallbackParameterStruct& console_callback_parameter_struct,
                    const yli::data::AnyValue& any_value) const final
            {
                return this->create_child<
                    ConsoleCallbackParameter, ConsoleCallbackObject, yli::memory::ConsoleCallbackParameterMemoryAllocator, ConsoleCallbackParameterStruct>(
                            yli::data::Datatype::CONSOLE_CALLBACK_PARAMETER,
                            console_callback_parameter_struct.console_callback_object_parent,
                            console_callback_parameter_struct,
                            {},
                            any_value);
            }

            // TODO: implement `create_graph` here!

            // TODO: implement `create_node` here!

            ComputeTask* create_compute_task(const ComputeTaskStruct& compute_task_struct) const final
            {
                return this->create_child<
                    ComputeTask, Pipeline, yli::memory::ComputeTaskMemoryAllocator, ComputeTaskStruct>(
                            yli::data::Datatype::COMPUTE_TASK,
                            compute_task_struct.pipeline_parent,
                            compute_task_struct,
                            {});
            }

            LispFunction* create_lisp_function(const LispFunctionStruct& lisp_function_struct) const final
            {
                return this->create_child<
                    LispFunction, Console, yli::memory::LispFunctionMemoryAllocator, LispFunctionStruct>(
                            yli::data::Datatype::LISP_FUNCTION,
                            lisp_function_struct.console_parent,
                            lisp_function_struct,
                            {});
            }

            template<typename... Args>
                GenericLispFunctionOverload* create_lisp_function_overload(
                        const std::string& name,
                        Console& console,
                        std::optional<yli::data::AnyValue>(*callback)(Args...))
                {
                    Entity* const lisp_function_entity = this->get_universe().get_entity(name);

                    LispFunction* lisp_function = nullptr;

                    if (lisp_function_entity == nullptr)
                    {
                        // There was not any `Entity` with that name.
                        LispFunctionStruct lisp_function_struct(&console);
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
                        lisp_function = dynamic_cast<LispFunction*>(lisp_function_entity);

                        if (lisp_function == nullptr)
                        {
                            // The name is in use and the `Entity` is not a `LispFunction`.
                            return nullptr;
                        }
                    }

                    yli::memory::GenericMemoryAllocator& generic_allocator =
                        this->memory_system.template get_or_create_allocator<yli::memory::GenericLispFunctionOverloadMemoryAllocator>(
                                static_cast<int>(yli::data::Datatype::GENERIC_LISP_FUNCTION_OVERLOAD));

                    auto& allocator =
                        static_cast<yli::memory::GenericLispFunctionOverloadMemoryAllocator&>(generic_allocator);

                    GenericLispFunctionOverload* const generic_lisp_function_overload = allocator.build_in(
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
                        const ObjectStruct& object_struct,
                        ModuleArgs&&... module_args)
                {
                    return this->create_child<
                        T, Scene, ObjectDerivativeMemoryAllocator, ObjectStruct>(
                                object_derivative_type,
                                object_struct.scene,
                                object_struct,
                                {},
                                // `Brain` master.
                                (object_struct.brain_master != nullptr ? object_struct.brain_master->get_generic_master_module<Movable>() : nullptr),
                                // mesh master.
                                ((std::holds_alternative<Species*>(object_struct.mesh_master) && std::get<Species*>(object_struct.mesh_master) != nullptr) ?
                                 &(std::get<Species*>(object_struct.mesh_master)->master_of_objects) :
                                 (std::holds_alternative<ShapeshifterSequence*>(object_struct.mesh_master) && std::get<ShapeshifterSequence*>(object_struct.mesh_master) != nullptr) ?
                                 &(std::get<ShapeshifterSequence*>(object_struct.mesh_master)->master_of_objects) :
                                 (std::holds_alternative<Text3d*>(object_struct.mesh_master) && std::get<Text3d*>(object_struct.mesh_master) != nullptr) ?
                                 &(std::get<Text3d*>(object_struct.mesh_master)->master_of_objects) :
                                 nullptr),
                                // Skill modules.
                                std::forward<ModuleArgs>(module_args)...);
                }

            template<typename T, typename HolobiontDerivativeMemoryAllocator, typename... ModuleArgs>
                T* create_holobiont_derivative(
                        int holobiont_derivative_type,
                        const HolobiontStruct& holobiont_struct,
                        ModuleArgs&&... module_args)
                {
                    yli::memory::GenericMemoryAllocator& generic_allocator =
                        this->memory_system.template get_or_create_allocator<HolobiontDerivativeMemoryAllocator>(
                                static_cast<int>(holobiont_derivative_type));

                    HolobiontDerivativeMemoryAllocator& allocator =
                        static_cast<HolobiontDerivativeMemoryAllocator&>(generic_allocator);

                    Scene* scene_parent { nullptr };
                    if (std::holds_alternative<Scene*>(holobiont_struct.scene))
                    {
                        scene_parent = std::get<Scene*>(holobiont_struct.scene);
                    }
                    else if (std::holds_alternative<std::string>(holobiont_struct.scene))
                    {
                        scene_parent = dynamic_cast<Scene*>(this->get_universe().registry.get_entity(std::get<std::string>(holobiont_struct.scene)));
                    }

                    T* const holobiont = allocator.build_in(
                            this->application,
                            this->get_universe(),
                            holobiont_struct,
                            (scene_parent != nullptr ? &scene_parent->parent_of_holobionts : nullptr),
                            (holobiont_struct.symbiosis_master != nullptr ? &holobiont_struct.symbiosis_master->master_of_holobionts : nullptr),
                            (holobiont_struct.brain_master != nullptr ? holobiont_struct.brain_master->get_generic_master_module<Movable>() : nullptr),
                            module_args...);

                    holobiont->set_global_name(holobiont_struct.global_name);
                    holobiont->set_local_name(holobiont_struct.local_name);
                    return holobiont;
                }

        private:
            template<typename T, typename ParentModuleType, typename TypeAllocator, typename DataStruct, typename... Args>
                T* create_child_of_universe(
                        const int type,
                        const DataStruct& data_struct,
                        ParentModuleType* const parent_module,
                        Args&&... args) const
                {
                    yli::memory::GenericMemoryAllocator& generic_allocator =
                        this->memory_system.template get_or_create_allocator<TypeAllocator>(type);
                    auto& allocator = static_cast<TypeAllocator&>(generic_allocator);

                    T* const instance = allocator.build_in(
                            this->application,
                            this->get_universe(),
                            data_struct,
                            parent_module,
                            std::forward<Args>(args)...);

                    if (!data_struct.global_name.empty() && data_struct.local_name.empty())
                    {
                        // Only `global_name` given, OK.
                        instance->set_global_name(data_struct.global_name);
                    }
                    else if (data_struct.global_name.empty() && !data_struct.local_name.empty())
                    {
                        // Only `local_name` given, OK.
                        instance->set_local_name(data_struct.local_name);
                    }
                    else if (!data_struct.global_name.empty() && !data_struct.local_name.empty())
                    {
                        std::cerr << "ERROR: `EntityFactory::create_child_of_universe`: both global and local names given for type: " << instance->get_type() << "\n";
                        std::cerr << "which is a child of `Universe`. For children of the `Universe` global and local names\n";
                        std::cerr << "are the same and only 1 of them can be given. No name given to this instance of type: " << instance->get_type() << " !\n";
                    }

                    return instance;
                }

            template<EntityNotUniverse T, typename TypeAllocator, typename DataStruct, typename... Args>
                T* create_child_of_ecosystem_or_scene(
                        const int type,
                        const DataStruct& data_struct,
                        Args&&... args) const
                {
                    yli::memory::GenericMemoryAllocator& generic_allocator =
                        this->memory_system.template get_or_create_allocator<TypeAllocator>(
                                static_cast<int>(type));
                    auto& allocator = static_cast<TypeAllocator&>(generic_allocator);

                    T* instance { nullptr };
                    if (std::holds_alternative<Ecosystem*>(data_struct.parent))
                    {
                        auto const ecosystem_parent = std::get<Ecosystem*>(data_struct.parent);

                        instance = allocator.build_in(
                                this->application,
                                this->get_universe(),
                                data_struct,
                                (ecosystem_parent != nullptr ? ecosystem_parent->get_generic_parent_module(type) : nullptr),
                                std::forward<Args>(args)...);
                    }
                    else if (std::holds_alternative<Scene*>(data_struct.parent))
                    {
                        auto const scene_parent = std::get<Scene*>(data_struct.parent);

                        instance = allocator.build_in(
                                this->application,
                                this->get_universe(),
                                data_struct,
                                (scene_parent != nullptr ? scene_parent->get_generic_parent_module(type) : nullptr),
                                std::forward<Args>(args)...);
                    }
                    else if (std::holds_alternative<std::string>(data_struct.parent))
                    {
                        Entity* const entity_parent = this->get_universe().registry.get_entity(std::get<std::string>(data_struct.parent));

                        if (auto const ecosystem_parent = dynamic_cast<Ecosystem*>(entity_parent); ecosystem_parent != nullptr)
                        {
                            instance = allocator.build_in(
                                    this->application,
                                    this->get_universe(),
                                    data_struct,
                                    ecosystem_parent->get_generic_parent_module(type),
                                    std::forward<Args>(args)...);
                        }
                        else if (auto const scene_parent = dynamic_cast<Scene*>(entity_parent); scene_parent != nullptr)
                        {
                            instance = allocator.build_in(
                                    this->application,
                                    this->get_universe(),
                                    data_struct,
                                    scene_parent->get_generic_parent_module(type),
                                    std::forward<Args>(args)...);
                        }
                        else
                        {
                            instance = allocator.build_in(this->application, this->get_universe(), data_struct, nullptr, std::forward<Args>(args)...);
                        }
                    }

                    instance->set_global_name(data_struct.global_name);
                    instance->set_local_name(data_struct.local_name);
                    return instance;
                }

            template<EntityNotUniverse Type, EntityNotUniverse ParentType, typename TypeAllocator, typename DataStruct, typename... Masters, typename... Types, typename... Args>
                Type* create_child(
                        const int type,
                        std::variant<Types...> parent,
                        const DataStruct& data_struct,
                        std::tuple<Masters...> masters,
                        Args&&... args) const
                {
                    // Create an instance of a derived class of `Entity`.
                    // The type of the `Entity` must not be `Universe`.
                    // The type of the parent of the `Entity` must not be `Universe`.

                    yli::memory::GenericMemoryAllocator& generic_allocator =
                        this->memory_system.template get_or_create_allocator<TypeAllocator>(
                                static_cast<int>(type));
                    auto& allocator = static_cast<TypeAllocator&>(generic_allocator);

                    ParentType* parent_type_parent { nullptr };
                    if (std::holds_alternative<ParentType*>(parent))
                    {
                        parent_type_parent = std::get<ParentType*>(parent);
                    }
                    else if (std::holds_alternative<std::string>(parent))
                    {
                        parent_type_parent = dynamic_cast<ParentType*>(this->get_universe().registry.get_entity(
                                    std::get<std::string>(parent)));
                    }

                    Type* const instance = allocator.build_in(
                            this->application,
                            this->get_universe(),
                            data_struct,
                            (parent_type_parent != nullptr ? parent_type_parent->get_generic_parent_module(type) : nullptr),
                            std::forward<Args>(args)...);

                    instance->set_global_name(data_struct.global_name);
                    instance->set_local_name(data_struct.local_name);
                    return instance;
                }

            yli::core::Application& application;
            yli::memory::MemorySystem<TypeEnumType>& memory_system;
            Universe* universe { nullptr };
    };
}

#endif
