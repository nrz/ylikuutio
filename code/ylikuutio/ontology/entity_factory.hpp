// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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
#include "universe.hpp"
#include "ecosystem.hpp"
#include "scene.hpp"
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
#include "text_2d.hpp"
#include "text_3d.hpp"
#include "font_2d.hpp"
#include "console.hpp"
#include "lisp_function.hpp"
#include "generic_lisp_function_overload.hpp"
#include "lisp_function_overload.hpp"
#include "shapeshifter_sequence.hpp"
#include "camera.hpp"
#include "compute_task.hpp"
#include "brain.hpp"
#include "variable_struct.hpp"
#include "ecosystem_struct.hpp"
#include "scene_struct.hpp"
#include "pipeline_struct.hpp"
#include "material_struct.hpp"
#include "model_struct.hpp"
#include "object_struct.hpp"
#include "holobiont_struct.hpp"
#include "biont_struct.hpp"
#include "vector_font_struct.hpp"
#include "text_3d_struct.hpp"
#include "console_struct.hpp"
#include "font_struct.hpp"
#include "text_struct.hpp"
#include "lisp_function_struct.hpp"
#include "camera_struct.hpp"
#include "compute_task_struct.hpp"
#include "brain_struct.hpp"
#include "code/ylikuutio/core/application.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/data/datatype.hpp"
#include "code/ylikuutio/memory/memory_system.hpp"
#include "code/ylikuutio/memory/memory_allocator.hpp"

// Include standard headers
#include <functional> // std::function
#include <iostream>  // std::cout, std::cin, std::cerr
#include <optional>  // std::optional
#include <string>    // std::string
#include <utility>   // std::move
#include <variant>   // std::holds_alternative, std::variant

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
            EntityFactory<TypeEnumType>(
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

                yli::ontology::Entity* universe_entity = allocator.build_in(
                        this->application,
                        universe_struct);

                yli::ontology::Universe* const universe = static_cast<yli::ontology::Universe*>(universe_entity);
                this->universe = universe;
                return universe;
            }

            yli::ontology::Universe& get_universe() const
            {
                if (this->universe == nullptr)
                {
                    throw std::runtime_error("ERROR: `EntityFactory::get_universe`: `this->universe` is `nullptr`!");
                }

                return *this->universe;
            }

            yli::ontology::Entity* create_variable(
                    const yli::ontology::VariableStruct& variable_struct,
                    const yli::data::AnyValue& any_value) const override
            {
                using VariableMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::Variable, 1024>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<VariableMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::VARIABLE));
                VariableMemoryAllocator& allocator = static_cast<VariableMemoryAllocator&>(generic_allocator);

                // The `Universe&` needs to be taken from `VariableStruct`
                // because `Universe` constructor creates its `Variable`
                // instances using `EntityFactory` before `EntityFactory::create_universe`
                // has initialized `universe` member variable of `EntityFactory`.
                yli::ontology::Entity* variable_entity = allocator.build_in(
                        this->application,
                        variable_struct.universe,
                        variable_struct,
                        any_value);

                if (variable_struct.is_variable_of_universe)
                {
                    // OK, this is a `Variable` of the `Universe`.

                    if (!variable_struct.global_name.empty() && variable_struct.local_name.empty())
                    {
                        // Only `global_name` given, OK.
                        variable_entity->set_global_name(variable_struct.global_name);
                    }
                    else if (variable_struct.global_name.empty() && !variable_struct.local_name.empty())
                    {
                        // Only `local_name` given, OK.
                        variable_entity->set_local_name(variable_struct.local_name);
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

                    variable_entity->set_global_name(variable_struct.global_name);
                    variable_entity->set_local_name(variable_struct.local_name);
                }

                if (variable_struct.should_call_activate_callback_now)
                {
                    variable_entity->activate();
                }

                return variable_entity;
            }

            yli::ontology::Entity* create_ecosystem(const yli::ontology::EcosystemStruct& ecosystem_struct) const override
            {
                using EcosystemMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::Ecosystem, 1024>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<EcosystemMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::ECOSYSTEM));
                EcosystemMemoryAllocator& allocator = static_cast<EcosystemMemoryAllocator&>(generic_allocator);

                yli::ontology::Entity* ecosystem_entity = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        ecosystem_struct,
                        &this->get_universe().parent_of_ecosystems);

                if (!ecosystem_struct.global_name.empty() && ecosystem_struct.local_name.empty())
                {
                    // Only `global_name` given, OK.
                    ecosystem_entity->set_global_name(ecosystem_struct.global_name);
                }
                else if (ecosystem_struct.global_name.empty() && !ecosystem_struct.local_name.empty())
                {
                    // Only `local_name` given, OK.
                    ecosystem_entity->set_local_name(ecosystem_struct.local_name);
                }
                else if (!ecosystem_struct.global_name.empty() && !ecosystem_struct.local_name.empty())
                {
                    std::cerr << "ERROR: `EntityFactory::create_ecosystem`: both global and local names given for a `Ecosystem`\n";
                    std::cerr << "which is a child of `Universe`. For children of the `Universe` global and local names\n";
                    std::cerr << "are the same and only 1 of them can be given. No name given to this `Ecosystem`!\n";
                }

                return ecosystem_entity;
            }

            yli::ontology::Entity* create_scene(const yli::ontology::SceneStruct& scene_struct) const override
            {
                using SceneMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::Scene, 1024>;

                yli::memory::GenericMemoryAllocator& generic_scene_allocator =
                    this->memory_system.template get_or_create_allocator<SceneMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::SCENE));
                SceneMemoryAllocator& scene_allocator = static_cast<SceneMemoryAllocator&>(generic_scene_allocator);

                yli::ontology::Entity* scene_entity = scene_allocator.build_in(
                        this->application,
                        this->get_universe(),
                        scene_struct,
                        &this->get_universe().parent_of_scenes);

                if (!scene_struct.global_name.empty() && scene_struct.local_name.empty())
                {
                    // Only `global_name` given, OK.
                    scene_entity->set_global_name(scene_struct.global_name);
                }
                else if (scene_struct.global_name.empty() && !scene_struct.local_name.empty())
                {
                    // Only `local_name` given, OK.
                    scene_entity->set_local_name(scene_struct.local_name);
                }
                else if (!scene_struct.global_name.empty() && !scene_struct.local_name.empty())
                {
                    std::cerr << "ERROR: `EntityFactory::create_scene`: both global and local names given for a `Scene`\n";
                    std::cerr << "which is a child of `Universe`. For children of the `Universe` global and local names\n";
                    std::cerr << "are the same and only 1 of them can be given. No name given to this `Scene`!\n";
                }

                yli::ontology::Scene* const scene = static_cast<yli::ontology::Scene*>(scene_entity);

                // Create the default `Camera`.
                yli::ontology::CameraStruct camera_struct = scene_struct.default_camera_struct;
                camera_struct.scene = scene;

                using CameraMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::Camera, 1024>;

                yli::memory::GenericMemoryAllocator& generic_camera_allocator =
                    this->memory_system.template get_or_create_allocator<CameraMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::CAMERA));
                CameraMemoryAllocator& camera_allocator = static_cast<CameraMemoryAllocator&>(generic_camera_allocator);

                camera_allocator.build_in(
                        this->application,
                        this->get_universe(),
                        camera_struct,
                        &scene->parent_of_default_camera,
                        nullptr); // Create the default `Camera`.

                return scene;
            }

            yli::ontology::Entity* create_pipeline(const yli::ontology::PipelineStruct& pipeline_struct) const override
            {
                using PipelineMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::Pipeline, 1024>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<PipelineMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::PIPELINE));
                PipelineMemoryAllocator& allocator = static_cast<PipelineMemoryAllocator&>(generic_allocator);

                yli::ontology::Entity* pipeline_entity = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        pipeline_struct,
                        // `Ecosystem` or `Scene` parent.
                        ((std::holds_alternative<yli::ontology::Ecosystem*>(pipeline_struct.parent) && std::get<yli::ontology::Ecosystem*>(pipeline_struct.parent) != nullptr) ?
                         &(std::get<yli::ontology::Ecosystem*>(pipeline_struct.parent)->parent_of_pipelines) :
                         (std::holds_alternative<yli::ontology::Scene*>(pipeline_struct.parent) && std::get<yli::ontology::Scene*>(pipeline_struct.parent) != nullptr) ?
                         &(std::get<yli::ontology::Scene*>(pipeline_struct.parent)->parent_of_pipelines) :
                         nullptr));
                pipeline_entity->set_global_name(pipeline_struct.global_name);
                pipeline_entity->set_local_name(pipeline_struct.local_name);
                return pipeline_entity;
            }

            yli::ontology::Entity* create_material(const yli::ontology::MaterialStruct& material_struct) const override
            {
                using MaterialMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::Material, 1024>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<MaterialMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::MATERIAL));
                MaterialMemoryAllocator& allocator = static_cast<MaterialMemoryAllocator&>(generic_allocator);

                yli::ontology::Entity* material_entity = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        material_struct,
                        // `Ecosystem` or `Scene` parent.
                        ((std::holds_alternative<yli::ontology::Ecosystem*>(material_struct.parent) && std::get<yli::ontology::Ecosystem*>(material_struct.parent) != nullptr) ?
                         &(std::get<yli::ontology::Ecosystem*>(material_struct.parent)->parent_of_materials) :
                         (std::holds_alternative<yli::ontology::Scene*>(material_struct.parent) && std::get<yli::ontology::Scene*>(material_struct.parent) != nullptr) ?
                         &(std::get<yli::ontology::Scene*>(material_struct.parent)->parent_of_materials) :
                         nullptr),
                        (material_struct.pipeline == nullptr ? nullptr : material_struct.pipeline->get_master_module()));

                material_entity->set_global_name(material_struct.global_name);
                material_entity->set_local_name(material_struct.local_name);
                return material_entity;
            }

            yli::ontology::Entity* create_species(const yli::ontology::ModelStruct& model_struct) const override
            {
                using SpeciesMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::Species, 1024>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<SpeciesMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::SPECIES));
                SpeciesMemoryAllocator& allocator = static_cast<SpeciesMemoryAllocator&>(generic_allocator);

                yli::ontology::Entity* species_entity = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        model_struct,
                        // `Ecosystem` or `Scene` parent.
                        ((std::holds_alternative<yli::ontology::Ecosystem*>(model_struct.parent) && std::get<yli::ontology::Ecosystem*>(model_struct.parent) != nullptr) ? &(std::get<yli::ontology::Ecosystem*>(model_struct.parent)->parent_of_species) :
                         (std::holds_alternative<yli::ontology::Scene*>(model_struct.parent) && std::get<yli::ontology::Scene*>(model_struct.parent) != nullptr) ? &(std::get<yli::ontology::Scene*>(model_struct.parent)->parent_of_species) :
                         nullptr),
                        (model_struct.material == nullptr ? nullptr : &model_struct.material->master_of_species));

                species_entity->set_global_name(model_struct.global_name);
                species_entity->set_local_name(model_struct.local_name);
                return species_entity;
            }

            yli::ontology::Entity* create_object(const yli::ontology::ObjectStruct& object_struct) const override
            {
                using ObjectMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::Object, 1024>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<ObjectMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::OBJECT));
                ObjectMemoryAllocator& allocator = static_cast<ObjectMemoryAllocator&>(generic_allocator);

                yli::ontology::Entity* object_entity = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        object_struct,
                        // `Scene` parent.
                        ((object_struct.parent != nullptr) ?  &object_struct.parent->parent_of_objects : nullptr),
                        // mesh master.
                        ((std::holds_alternative<yli::ontology::Species*>(object_struct.mesh_master) && std::get<yli::ontology::Species*>(object_struct.mesh_master) != nullptr) ?
                         &(std::get<yli::ontology::Species*>(object_struct.mesh_master)->master_of_objects) :
                         (std::holds_alternative<yli::ontology::ShapeshifterSequence*>(object_struct.mesh_master) && std::get<yli::ontology::ShapeshifterSequence*>(object_struct.mesh_master) != nullptr) ?
                         &(std::get<yli::ontology::ShapeshifterSequence*>(object_struct.mesh_master)->master_of_objects) :
                         (std::holds_alternative<yli::ontology::Text3D*>(object_struct.mesh_master) && std::get<yli::ontology::Text3D*>(object_struct.mesh_master) != nullptr) ?
                         &(std::get<yli::ontology::Text3D*>(object_struct.mesh_master)->master_of_objects) :
                         nullptr),
                        // `Brain` master.
                        (object_struct.brain == nullptr ? nullptr : object_struct.brain->get_generic_master_module()));

                object_entity->set_global_name(object_struct.global_name);
                object_entity->set_local_name(object_struct.local_name);
                return object_entity;
            }

            yli::ontology::Entity* create_symbiosis(const yli::ontology::ModelStruct& model_struct) const override
            {
                using SymbiosisMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::Symbiosis, 1024>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<SymbiosisMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::SYMBIOSIS));
                SymbiosisMemoryAllocator& allocator = static_cast<SymbiosisMemoryAllocator&>(generic_allocator);

                yli::ontology::Entity* symbiosis_entity = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        model_struct,
                        // `Ecosystem` or `Scene` parent.
                        ((std::holds_alternative<yli::ontology::Ecosystem*>(model_struct.parent) && std::get<yli::ontology::Ecosystem*>(model_struct.parent) != nullptr) ? &(std::get<yli::ontology::Ecosystem*>(model_struct.parent)->parent_of_species) :
                         (std::holds_alternative<yli::ontology::Scene*>(model_struct.parent) && std::get<yli::ontology::Scene*>(model_struct.parent) != nullptr) ? &(std::get<yli::ontology::Scene*>(model_struct.parent)->parent_of_species) :
                         nullptr),
                        (model_struct.pipeline == nullptr ? nullptr : &model_struct.pipeline->master_of_symbioses));

                symbiosis_entity->set_global_name(model_struct.global_name);
                symbiosis_entity->set_local_name(model_struct.local_name);
                return symbiosis_entity;
            }

            yli::ontology::Entity* create_symbiont_material(const MaterialStruct& material_struct) const override
            {
                using SymbiontMaterialMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::SymbiontMaterial, 1024>;

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

            yli::ontology::Entity* create_symbiont_species(const yli::ontology::ModelStruct& model_struct) const override
            {
                using SymbiontSpeciesMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::SymbiontSpecies, 1024>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<SymbiontSpeciesMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::SYMBIONT_SPECIES));
                SymbiontSpeciesMemoryAllocator& allocator = static_cast<SymbiontSpeciesMemoryAllocator&>(generic_allocator);

                return allocator.build_in(
                        this->application,
                        this->get_universe(),
                        model_struct,
                        (model_struct.symbiont_material == nullptr ?
                         nullptr :
                         &model_struct.symbiont_material->parent_of_symbiont_species));
            }

            yli::ontology::Entity* create_holobiont(const yli::ontology::HolobiontStruct& holobiont_struct) const override
            {
                using HolobiontMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::Holobiont, 1024>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<HolobiontMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::HOLOBIONT));
                HolobiontMemoryAllocator& allocator = static_cast<HolobiontMemoryAllocator&>(generic_allocator);

                yli::ontology::Entity* holobiont_entity = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        holobiont_struct,
                        (holobiont_struct.parent == nullptr ? nullptr : &holobiont_struct.parent->parent_of_holobionts),
                        (holobiont_struct.symbiosis == nullptr ? nullptr : &holobiont_struct.symbiosis->master_of_holobionts),
                        (holobiont_struct.brain == nullptr ? nullptr : holobiont_struct.brain->get_generic_master_module()));

                holobiont_entity->set_global_name(holobiont_struct.global_name);
                holobiont_entity->set_local_name(holobiont_struct.local_name);
                return holobiont_entity;
            }

            yli::ontology::Entity* create_biont(const yli::ontology::BiontStruct& biont_struct) const override
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
                        (biont_struct.parent == nullptr ? nullptr : &biont_struct.parent->parent_of_bionts),
                        (biont_struct.symbiont_species == nullptr ? nullptr : &biont_struct.symbiont_species->master_of_bionts));
            }

            yli::ontology::Entity* create_vector_font(const yli::ontology::VectorFontStruct& vector_font_struct) const override
            {
                using VectorFontMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::VectorFont, 1024>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<VectorFontMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::VECTORFONT));
                VectorFontMemoryAllocator& allocator = static_cast<VectorFontMemoryAllocator&>(generic_allocator);

                yli::ontology::Entity* vector_font_entity = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        vector_font_struct);

                vector_font_entity->set_global_name(vector_font_struct.global_name);
                vector_font_entity->set_local_name(vector_font_struct.local_name);
                return vector_font_entity;
            }

            yli::ontology::Entity* create_text2d(const yli::ontology::TextStruct& text_struct) const override
            {
                using Text2DMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::Text2D, 1024>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<Text2DMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::TEXT2D));
                Text2DMemoryAllocator& allocator = static_cast<Text2DMemoryAllocator&>(generic_allocator);

                yli::ontology::Entity* text2d_entity = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        text_struct,
                        (text_struct.parent == nullptr ? nullptr : &text_struct.parent->parent_of_text_2ds));

                text2d_entity->set_global_name(text_struct.global_name);
                text2d_entity->set_local_name(text_struct.local_name);
                return text2d_entity;
            }

            yli::ontology::Entity* create_glyph(const yli::ontology::ModelStruct& model_struct) const override
            {
                using GlyphMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::Glyph, 1024>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<GlyphMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::GLYPH));
                GlyphMemoryAllocator& allocator = static_cast<GlyphMemoryAllocator&>(generic_allocator);

                yli::ontology::Entity* glyph_entity = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        model_struct,
                        (std::holds_alternative<yli::ontology::VectorFont*>(model_struct.parent) && (std::get<yli::ontology::VectorFont*>(model_struct.parent) != nullptr) ?
                         &(std::get<yli::ontology::VectorFont*>(model_struct.parent)->parent_of_glyphs) :
                         nullptr));

                return glyph_entity;
            }

            yli::ontology::Entity* create_text3d(const yli::ontology::Text3DStruct& text_3d_struct) const override
            {
                using Text3DMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::Text3D, 1024>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<Text3DMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::TEXT3D));
                Text3DMemoryAllocator& allocator = static_cast<Text3DMemoryAllocator&>(generic_allocator);

                yli::ontology::Entity* text3d_entity = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        text_3d_struct,
                        (text_3d_struct.parent == nullptr ? nullptr : &text_3d_struct.parent->parent_of_text_3ds),
                        (text_3d_struct.brain == nullptr ? nullptr : text_3d_struct.brain->get_generic_master_module()));

                text3d_entity->set_global_name(text_3d_struct.global_name);
                text3d_entity->set_local_name(text_3d_struct.local_name);
                return text3d_entity;
            }

            yli::ontology::Entity* create_font2d(const yli::ontology::FontStruct& font_struct) const override
            {
                using Font2DMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::Font2D, 1024>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<Font2DMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::FONT2D));
                Font2DMemoryAllocator& allocator = static_cast<Font2DMemoryAllocator&>(generic_allocator);

                yli::ontology::Entity* font2d_entity = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        font_struct,
                        &this->get_universe().parent_of_font_2ds);

                if (!font_struct.global_name.empty() && font_struct.local_name.empty())
                {
                    // Only `global_name` given, OK.
                    font2d_entity->set_global_name(font_struct.global_name);
                }
                else if (font_struct.global_name.empty() && !font_struct.local_name.empty())
                {
                    // Only `local_name` given, OK.
                    font2d_entity->set_local_name(font_struct.local_name);
                }
                else if (!font_struct.global_name.empty() && !font_struct.local_name.empty())
                {
                    std::cerr << "ERROR: `EntityFactory::create_font2d`: both global and local names given for a `Font2D`\n";
                    std::cerr << "which is a child of `Universe`. For children of the `Universe` global and local names\n";
                    std::cerr << "are the same and only 1 of them can be given. No name given to this `Font2D`!\n";
                }

                return font2d_entity;
            }

            yli::ontology::Entity* create_console(const yli::ontology::ConsoleStruct& console_struct) const override
            {
                using ConsoleMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::Console, 1024>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<ConsoleMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::CONSOLE));
                ConsoleMemoryAllocator& allocator = static_cast<ConsoleMemoryAllocator&>(generic_allocator);

                yli::ontology::Entity* console_entity = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        console_struct,
                        &this->get_universe().parent_of_consoles,
                        (console_struct.font_2d == nullptr ? nullptr : &console_struct.font_2d->master_of_consoles));

                if (!console_struct.global_name.empty() && console_struct.local_name.empty())
                {
                    // Only `global_name` given, OK.
                    console_entity->set_global_name(console_struct.global_name);
                }
                else if (console_struct.global_name.empty() && !console_struct.local_name.empty())
                {
                    // Only `local_name` given, OK.
                    console_entity->set_local_name(console_struct.local_name);
                }
                else if (!console_struct.global_name.empty() && !console_struct.local_name.empty())
                {
                    std::cerr << "ERROR: `EntityFactory::create_console`: both global and local names given for a `Console`\n";
                    std::cerr << "which is a child of `Universe`. For children of the `Universe` global and local names\n";
                    std::cerr << "are the same and only 1 of them can be given. No name given to this `Console`!\n";
                }

                return console_entity;
            }

            yli::ontology::Entity* create_lisp_function(const yli::ontology::LispFunctionStruct& lisp_function_struct) const override
            {
                using LispFunctionMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::LispFunction, 1024>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<LispFunctionMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::LISP_FUNCTION));
                LispFunctionMemoryAllocator& allocator = static_cast<LispFunctionMemoryAllocator&>(generic_allocator);

                yli::ontology::Entity* lisp_function_entity = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        lisp_function_struct,
                        (lisp_function_struct.parent == nullptr ? nullptr : &lisp_function_struct.parent->parent_of_lisp_functions));

                lisp_function_entity->set_global_name(lisp_function_struct.global_name);
                lisp_function_entity->set_local_name(lisp_function_struct.local_name);
                return lisp_function_entity;
            }

            yli::ontology::Entity* create_camera(const yli::ontology::CameraStruct& camera_struct) const override
            {
                using CameraMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::Camera, 1024>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<CameraMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::CAMERA));
                CameraMemoryAllocator& allocator = static_cast<CameraMemoryAllocator&>(generic_allocator);

                yli::ontology::Entity* camera_entity = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        camera_struct,
                        (camera_struct.scene == nullptr ? nullptr : &camera_struct.scene->parent_of_cameras),
                        (camera_struct.brain == nullptr ? nullptr : camera_struct.brain->get_generic_master_module()));

                camera_entity->set_global_name(camera_struct.global_name);
                camera_entity->set_local_name(camera_struct.local_name);
                return camera_entity;
            }

            yli::ontology::Entity* create_compute_task(const yli::ontology::ComputeTaskStruct& compute_task_struct) const override
            {
                using ComputeTaskMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::ComputeTask, 1024>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<ComputeTaskMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::COMPUTETASK));
                ComputeTaskMemoryAllocator& allocator = static_cast<ComputeTaskMemoryAllocator&>(generic_allocator);

                yli::ontology::Entity* compute_task_entity = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        compute_task_struct);

                compute_task_entity->set_global_name(compute_task_struct.global_name);
                compute_task_entity->set_local_name(compute_task_struct.local_name);
                return compute_task_entity;
            }

            yli::ontology::Entity* create_brain(const yli::ontology::BrainStruct& brain_struct) const override
            {
                using BrainMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::Brain, 1024>;

                yli::memory::GenericMemoryAllocator& generic_allocator =
                    this->memory_system.template get_or_create_allocator<BrainMemoryAllocator>(
                            static_cast<int>(yli::data::Datatype::BRAIN));
                BrainMemoryAllocator& allocator = static_cast<BrainMemoryAllocator&>(generic_allocator);

                yli::ontology::Entity* brain_entity = allocator.build_in(
                        this->application,
                        this->get_universe(),
                        brain_struct,
                        (brain_struct.parent == nullptr ? nullptr : &brain_struct.parent->parent_of_brains));

                brain_entity->set_global_name(brain_struct.global_name);
                brain_entity->set_local_name(brain_struct.local_name);
                return brain_entity;
            }

            template<typename... Args>
                yli::ontology::GenericLispFunctionOverload* create_lisp_function_overload(
                        const std::string& name,
                        yli::ontology::Console* const console,
                        std::function<std::optional<yli::data::AnyValue>(Args...)> callback)
                {
                    if (console == nullptr)
                    {
                        return nullptr;
                    }

                    yli::ontology::Entity* const lisp_function_entity = this->get_universe().get_entity(name);

                    yli::ontology::LispFunction* lisp_function = nullptr;

                    if (lisp_function_entity == nullptr)
                    {
                        // There was not any `Entity` with that name.
                        yli::ontology::LispFunctionStruct lisp_function_struct;
                        lisp_function_struct.parent = console;
                        yli::ontology::Entity* const new_lisp_function_entity = this->create_lisp_function(lisp_function_struct);

                        lisp_function = dynamic_cast<yli::ontology::LispFunction*>(new_lisp_function_entity);

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
                        yli::memory::MemoryAllocator<yli::ontology::GenericLispFunctionOverload, 1024>;

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
                yli::ontology::Entity* create_object_derivative(
                        const yli::ontology::ObjectStruct& object_struct,
                        ModuleArgs&&... module_args)
                {
                    yli::memory::GenericMemoryAllocator& generic_allocator =
                        this->memory_system.template get_or_create_allocator<ObjectDerivativeMemoryAllocator>(
                                static_cast<int>(yli::data::Datatype::OBJECT));
                    ObjectDerivativeMemoryAllocator& allocator =
                        static_cast<ObjectDerivativeMemoryAllocator&>(generic_allocator);

                    yli::ontology::Entity* object_entity = allocator.build_in(
                            this->application,
                            this->get_universe(),
                            object_struct,
                            module_args...,
                            // `Scene` parent.
                            ((object_struct.parent != nullptr) ?  &object_struct.parent->parent_of_objects : nullptr),
                            // mesh master.
                            ((std::holds_alternative<yli::ontology::Species*>(object_struct.mesh_master) && std::get<yli::ontology::Species*>(object_struct.mesh_master) != nullptr) ?
                             &(std::get<yli::ontology::Species*>(object_struct.mesh_master)->master_of_objects) :
                             (std::holds_alternative<yli::ontology::ShapeshifterSequence*>(object_struct.mesh_master) && std::get<yli::ontology::ShapeshifterSequence*>(object_struct.mesh_master) != nullptr) ?
                             &(std::get<yli::ontology::ShapeshifterSequence*>(object_struct.mesh_master)->master_of_objects) :
                             (std::holds_alternative<yli::ontology::Text3D*>(object_struct.mesh_master) && std::get<yli::ontology::Text3D*>(object_struct.mesh_master) != nullptr) ?
                             &(std::get<yli::ontology::Text3D*>(object_struct.mesh_master)->master_of_objects) :
                             nullptr),
                            // `Brain` master.
                            (object_struct.brain == nullptr ? nullptr : object_struct.brain->get_generic_master_module()));

                    object_entity->set_global_name(object_struct.global_name);
                    object_entity->set_local_name(object_struct.local_name);
                    return object_entity;
                }

            template<typename T, typename HolobiontDerivativeMemoryAllocator, typename... ModuleArgs>
                yli::ontology::Entity* create_holobiont_derivative(
                        const yli::ontology::HolobiontStruct& holobiont_struct,
                        ModuleArgs&&... module_args)
                {
                    yli::memory::GenericMemoryAllocator& generic_allocator =
                        this->memory_system.template get_or_create_allocator<HolobiontDerivativeMemoryAllocator>(
                                static_cast<int>(yli::data::Datatype::HOLOBIONT));
                    HolobiontDerivativeMemoryAllocator& allocator =
                        static_cast<HolobiontDerivativeMemoryAllocator&>(generic_allocator);

                    yli::ontology::Entity* holobiont_entity = allocator.build_in(
                            this->application,
                            this->get_universe(),
                            holobiont_struct,
                            module_args...,
                            (holobiont_struct.parent == nullptr ? nullptr : &holobiont_struct.parent->parent_of_holobionts),
                            (holobiont_struct.symbiosis == nullptr ? nullptr : &holobiont_struct.symbiosis->master_of_holobionts),
                            (holobiont_struct.brain == nullptr ? nullptr : holobiont_struct.brain->get_generic_master_module()));

                    holobiont_entity->set_global_name(holobiont_struct.global_name);
                    holobiont_entity->set_local_name(holobiont_struct.local_name);
                    return holobiont_entity;
                }

        private:
            yli::core::Application& application;
            yli::memory::MemorySystem<TypeEnumType>& memory_system;
            yli::ontology::Universe* universe { nullptr };
    };
}

#endif
