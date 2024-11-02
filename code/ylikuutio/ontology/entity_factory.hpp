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
#include "shapeshifter.hpp"
#include "font_2d.hpp"
#include "text_2d.hpp"
#include "vector_font.hpp"
#include "glyph.hpp"
#include "text_3d.hpp"
#include "glyph_object.hpp"
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
#include "request.hpp"
#include "request_resolver.hpp"
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
#include "shapeshifter_struct.hpp"
#include "font_struct.hpp"
#include "text_struct.hpp"
#include "vector_font_struct.hpp"
#include "glyph_struct.hpp"
#include "text_3d_struct.hpp"
#include "glyph_object_struct.hpp"
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
#include <variant>   // std::holds_alternative, std::variant, std::visit

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

            template<EntityNotUniverse ParentType>
                GenericParentModule* get_generic_parent_module(const int child_type, const Request<ParentType>& entity_request) const
                {
                    ParentType* const parent = yli::ontology::resolve_request<ParentType>(entity_request, this->universe->registry);

                    if (parent != nullptr) [[likely]]
                    {
                        return parent->get_generic_parent_module(child_type);
                    }

                    return nullptr;
                }

            template<EntityNotUniverse ApprenticeType, EntityNotUniverse MasterType>
                GenericMasterModule* get_generic_master_module(const Request<MasterType>& entity_request) const
                {
                    MasterType* const master = yli::ontology::resolve_request<MasterType>(entity_request, this->get_universe().registry);

                    if (master != nullptr) [[likely]]
                    {
                        return master->template get_generic_master_module<ApprenticeType>();
                    }

                    return nullptr;
                }

            template<typename... Requests>
                GenericParentModule* get_generic_parent_module_from_variant(const int type, const std::variant<Requests...>& variant) const
                {
                    auto lambda = [this, type](auto&& request){ return this->get_generic_parent_module(type, request); };
                    return std::visit(lambda, variant);
                }

            template<typename ApprenticeType, typename... Requests>
                GenericMasterModule* get_generic_master_module_from_variant(const std::variant<Requests...>& variant) const
                {
                    auto lambda = [this](auto&& request){ return this->get_generic_master_module<ApprenticeType>(request); };
                    return std::visit(lambda, variant);
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
                return this->create_child_of_known_parent_type<
                    CallbackObject, CallbackEngine, yli::memory::CallbackObjectMemoryAllocator, CallbackObjectStruct>(
                            yli::data::Datatype::CALLBACK_OBJECT,
                            yli::data::Datatype::CALLBACK_OBJECT,
                            callback_object_struct.callback_engine_parent,
                            callback_object_struct,
                            {});
            }

            CallbackParameter* create_callback_parameter(
                    const CallbackParameterStruct& callback_parameter_struct,
                    yli::data::AnyValue&& any_value) const final
            {
                return this->create_child_of_known_parent_type<
                    CallbackParameter, CallbackObject, yli::memory::CallbackParameterMemoryAllocator, CallbackParameterStruct>(
                            yli::data::Datatype::CALLBACK_PARAMETER,
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
                return this->create_child_of_known_parent_type<
                    Brain, Scene, yli::memory::BrainMemoryAllocator, BrainStruct>(
                            yli::data::Datatype::BRAIN,
                            yli::data::Datatype::BRAIN,
                            brain_struct.scene_parent,
                            brain_struct,
                            {},
                            this->get_generic_master_module<Brain, CallbackEngine>(brain_struct.callback_engine_master));
            }

            Waypoint* create_waypoint(const WaypointStruct& waypoint_struct) const final
            {
                return this->create_child_of_known_parent_type<
                    Waypoint, Scene, yli::memory::WaypointMemoryAllocator, WaypointStruct>(
                            yli::data::Datatype::WAYPOINT,
                            yli::data::Datatype::WAYPOINT,
                            waypoint_struct.scene,
                            waypoint_struct,
                            {},
                            this->get_generic_master_module<Movable, Brain>(waypoint_struct.brain_master));
            }

            Camera* create_camera(const CameraStruct& camera_struct) const final
            {
                return this->create_child_of_known_parent_type<
                    Camera, Scene, yli::memory::CameraMemoryAllocator, CameraStruct>(
                            yli::data::Datatype::CAMERA,
                            yli::data::Datatype::CAMERA,
                            camera_struct.scene,
                            camera_struct,
                            {},
                            this->get_generic_master_module<Movable, Brain>(camera_struct.brain_master));
            }

            Camera* create_default_camera(const CameraStruct& camera_struct) const final
            {
                return this->create_child_of_known_parent_type<
                    Camera, Scene, yli::memory::CameraMemoryAllocator, CameraStruct>(
                            yli::data::Datatype::CAMERA,
                            yli::data::Datatype::CAMERA,
                            camera_struct.scene,
                            camera_struct,
                            {},
                            this->get_generic_master_module<Movable, Brain>(camera_struct.brain_master));
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
                            this->get_generic_master_module<Material, Pipeline>(material_struct.pipeline_master));
            }

            Species* create_species(const SpeciesStruct& species_struct) const final
            {
                return this->create_child_of_ecosystem_or_scene<
                    Species, yli::memory::SpeciesMemoryAllocator, SpeciesStruct>(
                            yli::data::Datatype::SPECIES,
                            species_struct,
                            this->get_generic_master_module<Species, Material>(species_struct.material_master));
            }

            Object* create_object(const ObjectStruct& object_struct) const final
            {
                return this->create_object_derivative<
                    Object, yli::memory::ObjectMemoryAllocator>(
                            yli::data::Datatype::OBJECT,
                            object_struct);
            }

            // TODO: implement `create_heightmap` here!

            // TODO: implement `create_heightmap_sheet` here!

            Symbiosis* create_symbiosis(const SymbiosisStruct& symbiosis_struct) const final
            {
                return this->create_child_of_ecosystem_or_scene<
                    Symbiosis, yli::memory::SymbiosisMemoryAllocator, SymbiosisStruct>(
                            yli::data::Datatype::SYMBIOSIS,
                            symbiosis_struct,
                            this->get_generic_master_module<Symbiosis, Pipeline>(symbiosis_struct.pipeline_master));
            }

            SymbiontMaterial* create_symbiont_material(const SymbiontMaterialStruct& symbiont_material_struct) const final
            {
                return this->create_child_of_known_parent_type<
                    SymbiontMaterial,
                    Symbiosis,
                    yli::memory::SymbiontMaterialMemoryAllocator,
                    SymbiontMaterialStruct>(
                            yli::data::Datatype::SYMBIONT_MATERIAL,
                            yli::data::Datatype::SYMBIONT_MATERIAL,
                            symbiont_material_struct.symbiosis_parent,
                            symbiont_material_struct,
                            {});
            }

            SymbiontSpecies* create_symbiont_species(const SymbiontSpeciesStruct& symbiont_species_struct) const final
            {
                return this->create_child_of_known_parent_type<
                    SymbiontSpecies, SymbiontMaterial, yli::memory::SymbiontSpeciesMemoryAllocator, SymbiontSpeciesStruct>(
                            yli::data::Datatype::SYMBIONT_SPECIES,
                            yli::data::Datatype::SYMBIONT_SPECIES,
                            symbiont_species_struct.symbiont_material_parent,
                            symbiont_species_struct,
                            {});
            }

            Holobiont* create_holobiont(const HolobiontStruct& holobiont_struct) const final
            {
                return this->create_holobiont_derivative<
                    Holobiont, yli::memory::HolobiontMemoryAllocator>(
                            yli::data::Datatype::HOLOBIONT,
                            holobiont_struct);
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
                        this->get_generic_parent_module<Holobiont>(static_cast<int>(yli::data::Datatype::BIONT), biont_struct.holobiont_parent),
                        this->get_generic_master_module<Biont, SymbiontSpecies>(biont_struct.symbiont_species_master));
            }

            ShapeshifterTransformation* create_shapeshifter_transformation(
                    const ShapeshifterTransformationStruct& shapeshifter_transformation_struct) const final
            {
                return this->create_child_of_known_parent_type<
                    ShapeshifterTransformation, Material, yli::memory::ShapeshifterTransformationMemoryAllocator, ShapeshifterTransformationStruct>(
                            yli::data::Datatype::SHAPESHIFTER_TRANSFORMATION,
                            yli::data::Datatype::SHAPESHIFTER_TRANSFORMATION,
                            shapeshifter_transformation_struct.material_parent,
                            shapeshifter_transformation_struct,
                            {});
            }

            ShapeshifterSequence* create_shapeshifter_sequence(
                    const ShapeshifterSequenceStruct& shapeshifter_sequence_struct) const final
            {
                return this->create_child_of_known_parent_type<
                    ShapeshifterSequence, ShapeshifterTransformation, yli::memory::ShapeshifterSequenceMemoryAllocator, ShapeshifterSequenceStruct>(
                            yli::data::Datatype::SHAPESHIFTER_SEQUENCE,
                            yli::data::Datatype::SHAPESHIFTER_SEQUENCE,
                            shapeshifter_sequence_struct.shapeshifter_transformation_parent,
                            shapeshifter_sequence_struct,
                            {});
            }

            ShapeshifterForm* create_shapeshifter_form(
                    const ShapeshifterFormStruct& shapeshifter_form_struct) const final
            {
                return this->create_child_of_known_parent_type<
                    ShapeshifterForm, ShapeshifterTransformation, yli::memory::ShapeshifterFormMemoryAllocator, ShapeshifterFormStruct>(
                            yli::data::Datatype::SHAPESHIFTER_FORM,
                            yli::data::Datatype::SHAPESHIFTER_FORM,
                            shapeshifter_form_struct.shapeshifter_transformation_parent,
                            shapeshifter_form_struct,
                            {});
            }

            Shapeshifter* create_shapeshifter(const ShapeshifterStruct& shapeshifter_struct) const final
            {
                return this->create_child_of_known_parent_type<
                    Shapeshifter, Scene, yli::memory::ShapeshifterMemoryAllocator, ShapeshifterStruct>(
                            yli::data::Datatype::SHAPESHIFTER,
                            yli::data::Datatype::SHAPESHIFTER,
                            shapeshifter_struct.scene,
                            shapeshifter_struct,
                            {},
                            // `Brain` master.
                            this->get_generic_master_module<Movable, Brain>(shapeshifter_struct.brain_master),
                            // `ShapeshifterSequence` master.
                            this->get_generic_master_module<Shapeshifter, ShapeshifterSequence>(shapeshifter_struct.shapeshifter_sequence_master));
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
                return this->create_child_of_known_parent_type<
                    Text2d, Font2d, yli::memory::Text2dMemoryAllocator, TextStruct>(
                            yli::data::Datatype::TEXT_2D,
                            yli::data::Datatype::TEXT_2D,
                            text_struct.font_2d_parent,
                            text_struct,
                            {});
            }

            VectorFont* create_vector_font(const VectorFontStruct& vector_font_struct) const final
            {
                return this->create_child_of_known_parent_type<
                    VectorFont, Material, yli::memory::VectorFontMemoryAllocator, VectorFontStruct>(
                            yli::data::Datatype::VECTOR_FONT,
                            yli::data::Datatype::VECTOR_FONT,
                            vector_font_struct.material_parent,
                            vector_font_struct,
                            {});
            }

            Glyph* create_glyph(const GlyphStruct& glyph_struct) const final
            {
                return this->create_child_of_known_parent_type<
                    Glyph, VectorFont, yli::memory::GlyphMemoryAllocator, GlyphStruct>(
                            yli::data::Datatype::GLYPH,
                            yli::data::Datatype::GLYPH,
                            glyph_struct.vector_font_parent,
                            glyph_struct,
                            {},
                            this->get_generic_master_module<Glyph, Material>(glyph_struct.material_master));
            }

            GlyphObject* create_glyph_object(const GlyphObjectStruct& glyph_object_struct) const final
            {
                return this->create_child_of_known_parent_type<
                    GlyphObject, Scene, yli::memory::GlyphObjectMemoryAllocator, GlyphObjectStruct>(
                            yli::data::Datatype::GLYPH_OBJECT,
                            yli::data::Datatype::GLYPH_OBJECT,
                            glyph_object_struct.scene_parent,
                            glyph_object_struct,
                            {},
                            this->get_generic_master_module<GlyphObject, Glyph>(glyph_object_struct.glyph_master),
                            this->get_generic_master_module<GlyphObject, Text3d>(glyph_object_struct.text_3d_master));
            }

            Text3d* create_text_3d(const Text3dStruct& text_3d_struct) const final
            {
                return this->create_child_of_known_parent_type<
                    Text3d, Scene, yli::memory::Text3dMemoryAllocator, Text3dStruct>(
                            yli::data::Datatype::TEXT_3D,
                            yli::data::Datatype::TEXT_3D,
                            text_3d_struct.scene,
                            text_3d_struct,
                            {},
                            this->get_generic_master_module<Movable, Brain>(text_3d_struct.brain_master),
                            this->get_generic_master_module<Text3d, VectorFont>(text_3d_struct.vector_font_master));
            }

            InputMode* create_input_mode(const InputModeStruct& input_mode_struct) const final
            {
                return this->create_child_of_universe<
                    InputMode, ParentOfInputModesModule, yli::memory::InputModeMemoryAllocator, InputModeStruct>(
                            yli::data::Datatype::INPUT_MODE,
                            input_mode_struct,
                            &this->get_universe().parent_of_input_modes,
                            this->get_generic_master_module<InputMode, Console>(input_mode_struct.console_master));
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
                            this->get_generic_master_module<Console, Font2d>(console_struct.font_2d_master));
            }

            ConsoleCallbackEngine* create_console_callback_engine(
                    const ConsoleCallbackEngineStruct& console_callback_engine_struct) const final
            {
                return this->create_child_of_known_parent_type<
                    ConsoleCallbackEngine, Console, yli::memory::ConsoleCallbackEngineMemoryAllocator, ConsoleCallbackEngineStruct>(
                            yli::data::Datatype::CONSOLE_CALLBACK_ENGINE,
                            yli::data::Datatype::CONSOLE_CALLBACK_ENGINE,
                            console_callback_engine_struct.console_parent,
                            console_callback_engine_struct,
                            {});
            }

            ConsoleCallbackObject* create_console_callback_object(
                    const ConsoleCallbackObjectStruct& console_callback_object_struct) const final
            {
                return this->create_child_of_known_parent_type<
                    ConsoleCallbackObject, ConsoleCallbackEngine, yli::memory::ConsoleCallbackObjectMemoryAllocator, ConsoleCallbackObjectStruct>(
                            yli::data::Datatype::CONSOLE_CALLBACK_OBJECT,
                            yli::data::Datatype::CONSOLE_CALLBACK_OBJECT,
                            console_callback_object_struct.console_callback_engine_parent,
                            console_callback_object_struct,
                            {});
            }

            ConsoleCallbackParameter* create_console_callback_parameter(
                    const ConsoleCallbackParameterStruct& console_callback_parameter_struct,
                    const yli::data::AnyValue& any_value) const final
            {
                return this->create_child_of_known_parent_type<
                    ConsoleCallbackParameter, ConsoleCallbackObject, yli::memory::ConsoleCallbackParameterMemoryAllocator, ConsoleCallbackParameterStruct>(
                            yli::data::Datatype::CONSOLE_CALLBACK_PARAMETER,
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
                return this->create_child_of_known_parent_type<
                    ComputeTask, Pipeline, yli::memory::ComputeTaskMemoryAllocator, ComputeTaskStruct>(
                            yli::data::Datatype::COMPUTE_TASK,
                            yli::data::Datatype::COMPUTE_TASK,
                            compute_task_struct.pipeline_parent,
                            compute_task_struct,
                            {});
            }

            LispFunction* create_lisp_function(const LispFunctionStruct& lisp_function_struct) const final
            {
                return this->create_child_of_known_parent_type<
                    LispFunction, Console, yli::memory::LispFunctionMemoryAllocator, LispFunctionStruct>(
                            yli::data::Datatype::LISP_FUNCTION,
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
                        LispFunctionStruct lisp_function_struct((Request<Console>(&console)));
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
                        ModuleArgs&&... module_args) const
                {
                    return this->create_child_of_known_parent_type<
                        T, Scene, ObjectDerivativeMemoryAllocator, ObjectStruct>(
                                object_derivative_type,
                                yli::data::Datatype::OBJECT,
                                object_struct.scene,
                                object_struct,
                                {},
                                // `Brain` master.
                                this->get_generic_master_module<Movable, Brain>(object_struct.brain_master),
                                // `Species` master.
                                this->get_generic_master_module<Object, Species>(object_struct.species_master),
                                // Skill modules.
                                std::forward<ModuleArgs>(module_args)...);
                }

            template<typename T, typename HolobiontDerivativeMemoryAllocator, typename... ModuleArgs>
                T* create_holobiont_derivative(
                        int holobiont_derivative_type,
                        const HolobiontStruct& holobiont_struct,
                        ModuleArgs&&... module_args) const
                {
                    return this->create_child_of_known_parent_type<
                        T, Scene, HolobiontDerivativeMemoryAllocator, HolobiontStruct>(
                                holobiont_derivative_type,
                                yli::data::Datatype::HOLOBIONT,
                                holobiont_struct.scene,
                                holobiont_struct,
                                {},
                                this->get_generic_master_module<Movable, Brain>(holobiont_struct.brain_master),
                                this->get_generic_master_module<Holobiont, Symbiosis>(holobiont_struct.symbiosis_master),
                                std::forward<ModuleArgs>(module_args)...);
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

                    T* instance = allocator.build_in(
                            this->application,
                            this->get_universe(),
                            data_struct,
                            this->get_generic_parent_module_from_variant(type, data_struct.parent),
                            std::forward<Args>(args)...);

                    instance->set_global_name(data_struct.global_name);
                    instance->set_local_name(data_struct.local_name);
                    return instance;
                }

            template<EntityNotUniverse Type, EntityNotUniverse ParentType, typename TypeAllocator, typename DataStruct, typename... Masters, typename... Types, typename... Args>
                Type* create_child_of_known_parent_type(
                        const int allocator_type,
                        const int parent_module_type,
                        const Request<ParentType>& parent,
                        const DataStruct& data_struct,
                        std::tuple<Masters...> masters,
                        Args&&... args) const
                {
                    // Create an instance of a derived class of `Entity`.
                    // The type of the `Entity` must not be `Universe`.
                    // The type of the parent of the `Entity` must not be `Universe`.

                    yli::memory::GenericMemoryAllocator& generic_allocator =
                        this->memory_system.template get_or_create_allocator<TypeAllocator>(
                                static_cast<int>(allocator_type));
                    auto& allocator = static_cast<TypeAllocator&>(generic_allocator);

                    Type* const instance = allocator.build_in(
                            this->application,
                            this->get_universe(),
                            data_struct,
                            this->get_generic_parent_module<ParentType>(parent_module_type, parent),
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
