// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2026 Antti Nuortimo.
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

#ifndef YLIKUUTIO_MEMORY_MEMORY_ALLOCATOR_TYPES_HPP_INCLUDED
#define YLIKUUTIO_MEMORY_MEMORY_ALLOCATOR_TYPES_HPP_INCLUDED

#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/variable.hpp"
#include "code/ylikuutio/ontology/callback_engine.hpp"
#include "code/ylikuutio/ontology/callback_object.hpp"
#include "code/ylikuutio/ontology/callback_parameter.hpp"
#include "code/ylikuutio/ontology/camera.hpp"
#include "code/ylikuutio/ontology/movable_controller.hpp"
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
#include "code/ylikuutio/ontology/ability.hpp"
#include "code/ylikuutio/ontology/holobiont.hpp"
#include "code/ylikuutio/ontology/biont.hpp"
#include "code/ylikuutio/ontology/skill.hpp"
#include "code/ylikuutio/ontology/shapeshifter_transformation.hpp"
#include "code/ylikuutio/ontology/shapeshifter_sequence.hpp"
#include "code/ylikuutio/ontology/shapeshifter_form.hpp"
#include "code/ylikuutio/ontology/shapeshifter.hpp"
#include "code/ylikuutio/ontology/font_2d.hpp"
#include "code/ylikuutio/ontology/text_2d.hpp"
#include "code/ylikuutio/ontology/vector_font.hpp"
#include "code/ylikuutio/ontology/glyph.hpp"
#include "code/ylikuutio/ontology/text_3d.hpp"
#include "code/ylikuutio/ontology/glyph_object.hpp"
#include "code/ylikuutio/ontology/input_mode.hpp"
#include "code/ylikuutio/ontology/audio_track.hpp"
#include "code/ylikuutio/ontology/console.hpp"
#include "code/ylikuutio/ontology/console_callback_engine.hpp"
#include "code/ylikuutio/ontology/console_callback_object.hpp"
#include "code/ylikuutio/ontology/console_callback_parameter.hpp"
#include "code/ylikuutio/ontology/compute_task.hpp"
#include "code/ylikuutio/ontology/console_lisp_function.hpp"
#include "code/ylikuutio/ontology/generic_console_lisp_function_overload.hpp"

namespace yli::memory
{
    using UniverseMemoryAllocator                    = MemoryAllocator<ontology::Universe, 1>;
    using VariableMemoryAllocator                    = MemoryAllocator<ontology::Variable, 4096>;
    using CallbackEngineMemoryAllocator              = MemoryAllocator<ontology::CallbackEngine, 256>;
    using CallbackObjectMemoryAllocator              = MemoryAllocator<ontology::CallbackObject, 256>;
    using CallbackParameterMemoryAllocator           = MemoryAllocator<ontology::CallbackParameter, 256>;
    using EcosystemMemoryAllocator                   = MemoryAllocator<ontology::Ecosystem, 16>;
    using SceneMemoryAllocator                       = MemoryAllocator<ontology::Scene, 256>;
    using MovableControllerMemoryAllocator           = MemoryAllocator<ontology::MovableController, 16>;
    using WaypointMemoryAllocator                    = MemoryAllocator<ontology::Waypoint, 256>;
    using CameraMemoryAllocator                      = MemoryAllocator<ontology::Camera, 256>;
    using PipelineMemoryAllocator                    = MemoryAllocator<ontology::Pipeline, 256>;
    using MaterialMemoryAllocator                    = MemoryAllocator<ontology::Material, 256>;
    using SpeciesMemoryAllocator                     = MemoryAllocator<ontology::Species, 256>;
    using ObjectMemoryAllocator                      = MemoryAllocator<ontology::Object, 256>;
    using SymbiosisMemoryAllocator                   = MemoryAllocator<ontology::Symbiosis, 256>;
    using SymbiontMaterialMemoryAllocator            = MemoryAllocator<ontology::SymbiontMaterial, 256>;
    using SymbiontSpeciesMemoryAllocator             = MemoryAllocator<ontology::SymbiontSpecies, 256>;
    using AbilityMemoryAllocator                     = MemoryAllocator<ontology::Ability, 256>;
    using HolobiontMemoryAllocator                   = MemoryAllocator<ontology::Holobiont, 256>;
    using BiontMemoryAllocator                       = MemoryAllocator<ontology::Biont, 1024>;
    using SkillMemoryAllocator                       = MemoryAllocator<ontology::Skill, 256>;
    using ShapeshifterTransformationMemoryAllocator  = MemoryAllocator<ontology::ShapeshifterTransformation, 1024>;
    using ShapeshifterSequenceMemoryAllocator        = MemoryAllocator<ontology::ShapeshifterSequence, 1024>;
    using ShapeshifterFormMemoryAllocator            = MemoryAllocator<ontology::ShapeshifterForm, 1024>;
    using ShapeshifterMemoryAllocator                = MemoryAllocator<ontology::Shapeshifter, 256>;
    using Font2dMemoryAllocator                      = MemoryAllocator<ontology::Font2d, 256>;
    using Text2dMemoryAllocator                      = MemoryAllocator<ontology::Text2d, 256>;
    using VectorFontMemoryAllocator                  = MemoryAllocator<ontology::VectorFont, 256>;
    using GlyphMemoryAllocator                       = MemoryAllocator<ontology::Glyph, 256>;
    using Text3dMemoryAllocator                      = MemoryAllocator<ontology::Text3d, 256>;
    using GlyphObjectMemoryAllocator                 = MemoryAllocator<ontology::GlyphObject, 256>;
    using InputModeMemoryAllocator                   = MemoryAllocator<ontology::InputMode, 256>;
    using AudioTrackMemoryAllocator                  = MemoryAllocator<ontology::AudioTrack, 256>;
    using ConsoleMemoryAllocator                     = MemoryAllocator<ontology::Console, 256>;
    using ConsoleCallbackEngineMemoryAllocator       = MemoryAllocator<ontology::ConsoleCallbackEngine, 256>;
    using ConsoleCallbackObjectMemoryAllocator       = MemoryAllocator<ontology::ConsoleCallbackObject, 256>;
    using ConsoleCallbackParameterMemoryAllocator    = MemoryAllocator<ontology::ConsoleCallbackParameter, 256>;
    using ComputeTaskMemoryAllocator                 = MemoryAllocator<ontology::ComputeTask, 256>;
    using ConsoleLispFunctionMemoryAllocator                = MemoryAllocator<ontology::ConsoleLispFunction, 256>;
    using GenericConsoleLispFunctionOverloadMemoryAllocator = MemoryAllocator<ontology::GenericConsoleLispFunctionOverload, 256>;
}

#endif
