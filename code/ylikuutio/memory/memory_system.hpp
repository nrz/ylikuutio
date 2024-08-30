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

#ifndef YLIKUUTIO_MEMORY_MEMORY_SYSTEM_HPP_INCLUDED
#define YLIKUUTIO_MEMORY_MEMORY_SYSTEM_HPP_INCLUDED

#include "generic_memory_system.hpp"
#include "generic_memory_allocator.hpp"
#include "memory_allocator.hpp"
#include "code/ylikuutio/core/application.hpp"
#include "code/ylikuutio/data/datatype.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/variable.hpp"
#include "code/ylikuutio/ontology/callback_engine.hpp"
#include "code/ylikuutio/ontology/callback_object.hpp"
#include "code/ylikuutio/ontology/callback_parameter.hpp"
#include "code/ylikuutio/ontology/camera.hpp"
#include "code/ylikuutio/ontology/brain.hpp"
#include "code/ylikuutio/ontology/waypoint.hpp"
#include "code/ylikuutio/ontology/ecosystem.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/pipeline.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/symbiosis.hpp"
#include "code/ylikuutio/ontology/symbiont_material.hpp"
#include "code/ylikuutio/ontology/symbiont_species.hpp"
#include "code/ylikuutio/ontology/holobiont.hpp"
#include "code/ylikuutio/ontology/biont.hpp"
#include "code/ylikuutio/ontology/shapeshifter_transformation.hpp"
#include "code/ylikuutio/ontology/shapeshifter_sequence.hpp"
#include "code/ylikuutio/ontology/shapeshifter_form.hpp"
#include "code/ylikuutio/ontology/font_2d.hpp"
#include "code/ylikuutio/ontology/text_2d.hpp"
#include "code/ylikuutio/ontology/vector_font.hpp"
#include "code/ylikuutio/ontology/glyph.hpp"
#include "code/ylikuutio/ontology/text_3d.hpp"
#include "code/ylikuutio/ontology/input_mode.hpp"
#include "code/ylikuutio/ontology/console.hpp"
#include "code/ylikuutio/ontology/console_callback_engine.hpp"
#include "code/ylikuutio/ontology/console_callback_object.hpp"
#include "code/ylikuutio/ontology/console_callback_parameter.hpp"
#include "code/ylikuutio/ontology/compute_task.hpp"
#include "code/ylikuutio/ontology/lisp_function.hpp"
#include "code/ylikuutio/ontology/generic_lisp_function_overload.hpp"

// Include standard headers
#include <cstddef>       // std::size_t
#include <map>           // std::map
#include <stdexcept>     // std::runtime_error
#include <string>        // std::string
#include <utility>       // std::forward

namespace yli::memory
{
    using UniverseMemoryAllocator                    = yli::memory::MemoryAllocator<yli::ontology::Universe, 1>;
    using VariableMemoryAllocator                    = yli::memory::MemoryAllocator<yli::ontology::Variable, 4096>;
    using CallbackEngineMemoryAllocator              = yli::memory::MemoryAllocator<yli::ontology::CallbackEngine, 256>;
    using CallbackObjectMemoryAllocator              = yli::memory::MemoryAllocator<yli::ontology::CallbackObject, 256>;
    using CallbackParameterMemoryAllocator           = yli::memory::MemoryAllocator<yli::ontology::CallbackParameter, 256>;
    using CameraMemoryAllocator                      = yli::memory::MemoryAllocator<yli::ontology::Camera, 256>;
    using BrainMemoryAllocator                       = yli::memory::MemoryAllocator<yli::ontology::Brain, 16>;
    using WaypointMemoryAllocator                    = yli::memory::MemoryAllocator<yli::ontology::Waypoint, 256>;
    using EcosystemMemoryAllocator                   = yli::memory::MemoryAllocator<yli::ontology::Ecosystem, 16>;
    using SceneMemoryAllocator                       = yli::memory::MemoryAllocator<yli::ontology::Scene, 256>;
    using PipelineMemoryAllocator                    = yli::memory::MemoryAllocator<yli::ontology::Pipeline, 256>;
    using MaterialMemoryAllocator                    = yli::memory::MemoryAllocator<yli::ontology::Material, 256>;
    using SpeciesMemoryAllocator                     = yli::memory::MemoryAllocator<yli::ontology::Species, 256>;
    using ObjectMemoryAllocator                      = yli::memory::MemoryAllocator<yli::ontology::Object, 256>;
    using SymbiosisMemoryAllocator                   = yli::memory::MemoryAllocator<yli::ontology::Symbiosis, 256>;
    using SymbiontMaterialMemoryAllocator            = yli::memory::MemoryAllocator<yli::ontology::SymbiontMaterial, 256>;
    using SymbiontSpeciesMemoryAllocator             = yli::memory::MemoryAllocator<yli::ontology::SymbiontSpecies, 256>;
    using HolobiontMemoryAllocator                   = yli::memory::MemoryAllocator<yli::ontology::Holobiont, 256>;
    using BiontMemoryAllocator                       = yli::memory::MemoryAllocator<yli::ontology::Biont, 1024>;
    using ShapeshifterTransformationMemoryAllocator  = yli::memory::MemoryAllocator<yli::ontology::ShapeshifterTransformation, 1024>;
    using ShapeshifterSequenceMemoryAllocator        = yli::memory::MemoryAllocator<yli::ontology::ShapeshifterSequence, 1024>;
    using ShapeshifterFormMemoryAllocator            = yli::memory::MemoryAllocator<yli::ontology::ShapeshifterForm, 1024>;
    using Font2DMemoryAllocator                      = yli::memory::MemoryAllocator<yli::ontology::Font2D, 256>;
    using Text2dMemoryAllocator                      = yli::memory::MemoryAllocator<yli::ontology::Text2d, 256>;
    using VectorFontMemoryAllocator                  = yli::memory::MemoryAllocator<yli::ontology::VectorFont, 256>;
    using GlyphMemoryAllocator                       = yli::memory::MemoryAllocator<yli::ontology::Glyph, 256>;
    using Text3dMemoryAllocator                      = yli::memory::MemoryAllocator<yli::ontology::Text3d, 256>;
    using InputModeMemoryAllocator                   = yli::memory::MemoryAllocator<yli::ontology::InputMode, 256>;
    using ConsoleMemoryAllocator                     = yli::memory::MemoryAllocator<yli::ontology::Console, 256>;
    using ConsoleCallbackEngineMemoryAllocator       = yli::memory::MemoryAllocator<yli::ontology::ConsoleCallbackEngine, 256>;
    using ConsoleCallbackObjectMemoryAllocator       = yli::memory::MemoryAllocator<yli::ontology::ConsoleCallbackObject, 256>;
    using ConsoleCallbackParameterMemoryAllocator    = yli::memory::MemoryAllocator<yli::ontology::ConsoleCallbackParameter, 256>;
    using ComputeTaskMemoryAllocator                 = yli::memory::MemoryAllocator<yli::ontology::ComputeTask, 256>;
    using LispFunctionMemoryAllocator                = yli::memory::MemoryAllocator<yli::ontology::LispFunction, 256>;
    using GenericLispFunctionOverloadMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::GenericLispFunctionOverload, 256>;

    struct ConstructibleModule;

    // `GetTypeEnumFunction` is a function template that return `TypeEnumType` values for different types.
    template<typename TypeEnumType = yli::data::Datatype>
        class MemorySystem final : public yli::memory::GenericMemorySystem
        {
            // Each class instance takes care of memory
            // management for a given application.

            public:
                MemorySystem(yli::core::Application* const application, TypeEnumType universe_datatype)
                    : universe_datatype { universe_datatype }
                {
                    // `application` is given as a pointer to enable
                    // unit testing without a mock `Application` derivative.
                    if (application != nullptr) [[likely]]
                    {
                        this->create_allocators();
                    }
                }

                ~MemorySystem()
                {
                    // Delete other except `Universe` allocators.

                    for (auto it = this->memory_allocators.begin(); it != this->memory_allocators.end(); )
                    {
                        if (it->first != this->universe_datatype)
                        {
                            auto old_it = it;
                            ++it;
                            delete old_it->second;
                            this->memory_allocators.erase(old_it);
                        }
                        else
                        {
                            ++it;
                        }
                    }

                    // Delete `Universe` allocator.
                    for (auto it = this->memory_allocators.begin(); it != this->memory_allocators.end(); )
                    {
                        if (it->first == this->universe_datatype)
                        {
                            auto old_it = it;
                            ++it;
                            delete old_it->second;
                            this->memory_allocators.erase(old_it);
                        }
                        else
                        {
                            ++it;
                        }
                    }
                }

                MemorySystem(const MemorySystem&) = delete;            // Delete copy constructor.
                MemorySystem& operator=(const MemorySystem&) = delete; // Delete copy assignment.

                TypeEnumType get_universe_datatype() const
                {
                    return this->universe_datatype;
                }

                yli::memory::MemorySystem<TypeEnumType>& get() const
                {
                    return const_cast<yli::memory::MemorySystem<TypeEnumType>&>(*this);
                }

                std::size_t get_number_of_allocators() const override
                {
                    return this->memory_allocators.size();
                }

                void create_allocators()
                {
                    this->create_allocator<UniverseMemoryAllocator>(yli::data::Datatype::UNIVERSE);
                    this->create_allocator<VariableMemoryAllocator>(yli::data::Datatype::VARIABLE);
                    this->create_allocator<CallbackEngineMemoryAllocator>(yli::data::Datatype::CALLBACK_ENGINE);
                    this->create_allocator<CallbackObjectMemoryAllocator>(yli::data::Datatype::CALLBACK_OBJECT);
                    this->create_allocator<CallbackParameterMemoryAllocator>(yli::data::Datatype::CALLBACK_PARAMETER);
                    this->create_allocator<CameraMemoryAllocator>(yli::data::Datatype::CAMERA);
                    this->create_allocator<BrainMemoryAllocator>(yli::data::Datatype::BRAIN);
                    this->create_allocator<WaypointMemoryAllocator>(yli::data::Datatype::WAYPOINT);
                    this->create_allocator<EcosystemMemoryAllocator>(yli::data::Datatype::ECOSYSTEM);
                    this->create_allocator<SceneMemoryAllocator>(yli::data::Datatype::SCENE);
                    this->create_allocator<PipelineMemoryAllocator>(yli::data::Datatype::PIPELINE);
                    this->create_allocator<MaterialMemoryAllocator>(yli::data::Datatype::MATERIAL);
                    this->create_allocator<SpeciesMemoryAllocator>(yli::data::Datatype::SPECIES);
                    this->create_allocator<ObjectMemoryAllocator>(yli::data::Datatype::OBJECT);
                    this->create_allocator<SymbiosisMemoryAllocator>(yli::data::Datatype::SYMBIOSIS);
                    this->create_allocator<SymbiontMaterialMemoryAllocator>(yli::data::Datatype::SYMBIONT_MATERIAL);
                    this->create_allocator<SymbiontSpeciesMemoryAllocator>(yli::data::Datatype::SYMBIONT_SPECIES);
                    this->create_allocator<HolobiontMemoryAllocator>(yli::data::Datatype::HOLOBIONT);
                    this->create_allocator<BiontMemoryAllocator>(yli::data::Datatype::BIONT);
                    this->create_allocator<ShapeshifterTransformationMemoryAllocator>(yli::data::Datatype::SHAPESHIFTER_TRANSFORMATION);
                    this->create_allocator<ShapeshifterSequenceMemoryAllocator>(yli::data::Datatype::SHAPESHIFTER_SEQUENCE);
                    this->create_allocator<ShapeshifterFormMemoryAllocator>(yli::data::Datatype::SHAPESHIFTER_FORM);
                    this->create_allocator<Font2DMemoryAllocator>(yli::data::Datatype::FONT_2D);
                    this->create_allocator<Text2dMemoryAllocator>(yli::data::Datatype::TEXT_2D);
                    this->create_allocator<VectorFontMemoryAllocator>(yli::data::Datatype::VECTOR_FONT);
                    this->create_allocator<GlyphMemoryAllocator>(yli::data::Datatype::GLYPH);
                    this->create_allocator<Text3dMemoryAllocator>(yli::data::Datatype::TEXT_3D);
                    this->create_allocator<ConsoleMemoryAllocator>(yli::data::Datatype::CONSOLE);
                    this->create_allocator<ConsoleCallbackEngineMemoryAllocator>(yli::data::Datatype::CONSOLE_CALLBACK_ENGINE);
                    this->create_allocator<ConsoleCallbackObjectMemoryAllocator>(yli::data::Datatype::CONSOLE_CALLBACK_OBJECT);
                    this->create_allocator<ConsoleCallbackParameterMemoryAllocator>(yli::data::Datatype::CONSOLE_CALLBACK_PARAMETER);
                    this->create_allocator<InputModeMemoryAllocator>(yli::data::Datatype::INPUT_MODE);
                    this->create_allocator<ComputeTaskMemoryAllocator>(yli::data::Datatype::COMPUTETASK);
                    this->create_allocator<LispFunctionMemoryAllocator>(yli::data::Datatype::LISP_FUNCTION);
                    this->create_allocator<GenericLispFunctionOverloadMemoryAllocator>(yli::data::Datatype::GENERIC_LISP_FUNCTION_OVERLOAD);
                }

                template<typename T1, typename... Args>
                    void create_allocator(int type, Args&&... args)
                    {
                        // TODO: Return the return value of `try_emplace`.
                        // TODO: Throw an exception if creating an allocator fails.
                        this->memory_allocators.try_emplace(type, new T1(type, std::forward<Args>(args)...));
                    }

                // TODO: use `TypeEnumType` instead of `int`!
                bool has_allocator(const int type) const override
                {
                    return this->memory_allocators.contains(type);
                }

                // TODO: use `TypeEnumType` instead of `int`!
                yli::memory::GenericMemoryAllocator& get_generic_allocator(const int type) const override
                {
                    if (this->has_allocator(type)) [[likely]]
                    {
                        return *(this->memory_allocators.at(type));
                    }

                    throw std::runtime_error("ERROR: `MemorySystem::get_generic_allocator`: allocator for type " + std::to_string(type) + " does not exist!");
                }

                template<typename T1, typename... Args>
                    // TODO: use `TypeEnumType` instead of `int`!
                    yli::memory::MemoryAllocator<T1>& get_allocator(const int type) const
                    {
                        if (this->has_allocator(type)) [[likely]]
                        {
                            return static_cast<yli::memory::MemoryAllocator<T1>&>(*(this->memory_allocators.at(type)));
                        }

                        throw std::runtime_error("ERROR: `MemorySystem::get_allocator`: allocator for type " + std::to_string(type) + " does not exist!");
                    }

                virtual void destroy(const yli::memory::ConstructibleModule& constructible_module) override
                {
                    if (constructible_module.alive && constructible_module.generic_allocator != nullptr)
                    {
                        yli::memory::GenericMemoryAllocator& allocator = *constructible_module.generic_allocator;
                        allocator.destroy(constructible_module);
                    }
                }

                template<typename T1, typename... Args>
                    // TODO: use `TypeEnumType` instead of `int`!
                    yli::memory::GenericMemoryAllocator& get_or_create_allocator(int type, Args&&... args)
                    {
                        if (this->has_allocator(type))
                        {
                            return this->get_generic_allocator(type);
                        }

                        this->create_allocator<T1, Args...>(type, std::forward<Args>(args)...);
                        return this->get_generic_allocator(type);
                    }

            private:
                // Allocators need to be created elsewhere and only stored here.
                // TODO: use `TypeEnumType` as the key type instead of `int`!
                std::map<int, yli::memory::GenericMemoryAllocator*> memory_allocators;
                const TypeEnumType universe_datatype;
        };
}

#endif
