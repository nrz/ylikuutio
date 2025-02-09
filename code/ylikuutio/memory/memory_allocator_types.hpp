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

#ifndef YLIKUUTIO_MEMORY_MEMORY_ALLOCATOR_TYPES_HPP_INCLUDED
#define YLIKUUTIO_MEMORY_MEMORY_ALLOCATOR_TYPES_HPP_INCLUDED

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
#include "code/ylikuutio/ontology/lisp_function.hpp"
#include "code/ylikuutio/ontology/generic_lisp_function_overload.hpp"

namespace yli::memory
{
    using UniverseMemoryAllocator                    = yli::memory::MemoryAllocator<yli::ontology::Universe, 1>;
    using VariableMemoryAllocator                    = yli::memory::MemoryAllocator<yli::ontology::Variable, 4096>;
    using CallbackEngineMemoryAllocator              = yli::memory::MemoryAllocator<yli::ontology::CallbackEngine, 256>;
    using CallbackObjectMemoryAllocator              = yli::memory::MemoryAllocator<yli::ontology::CallbackObject, 256>;
    using CallbackParameterMemoryAllocator           = yli::memory::MemoryAllocator<yli::ontology::CallbackParameter, 256>;
    using EcosystemMemoryAllocator                   = yli::memory::MemoryAllocator<yli::ontology::Ecosystem, 16>;
    using SceneMemoryAllocator                       = yli::memory::MemoryAllocator<yli::ontology::Scene, 256>;
    using BrainMemoryAllocator                       = yli::memory::MemoryAllocator<yli::ontology::Brain, 16>;
    using WaypointMemoryAllocator                    = yli::memory::MemoryAllocator<yli::ontology::Waypoint, 256>;
    using CameraMemoryAllocator                      = yli::memory::MemoryAllocator<yli::ontology::Camera, 256>;
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
    using ShapeshifterMemoryAllocator                = yli::memory::MemoryAllocator<yli::ontology::Shapeshifter, 256>;
    using Font2dMemoryAllocator                      = yli::memory::MemoryAllocator<yli::ontology::Font2d, 256>;
    using Text2dMemoryAllocator                      = yli::memory::MemoryAllocator<yli::ontology::Text2d, 256>;
    using VectorFontMemoryAllocator                  = yli::memory::MemoryAllocator<yli::ontology::VectorFont, 256>;
    using GlyphMemoryAllocator                       = yli::memory::MemoryAllocator<yli::ontology::Glyph, 256>;
    using Text3dMemoryAllocator                      = yli::memory::MemoryAllocator<yli::ontology::Text3d, 256>;
    using GlyphObjectMemoryAllocator                 = yli::memory::MemoryAllocator<yli::ontology::GlyphObject, 256>;
    using InputModeMemoryAllocator                   = yli::memory::MemoryAllocator<yli::ontology::InputMode, 256>;
    using AudioTrackMemoryAllocator                  = yli::memory::MemoryAllocator<yli::ontology::AudioTrack, 256>;
    using ConsoleMemoryAllocator                     = yli::memory::MemoryAllocator<yli::ontology::Console, 256>;
    using ConsoleCallbackEngineMemoryAllocator       = yli::memory::MemoryAllocator<yli::ontology::ConsoleCallbackEngine, 256>;
    using ConsoleCallbackObjectMemoryAllocator       = yli::memory::MemoryAllocator<yli::ontology::ConsoleCallbackObject, 256>;
    using ConsoleCallbackParameterMemoryAllocator    = yli::memory::MemoryAllocator<yli::ontology::ConsoleCallbackParameter, 256>;
    using ComputeTaskMemoryAllocator                 = yli::memory::MemoryAllocator<yli::ontology::ComputeTask, 256>;
    using LispFunctionMemoryAllocator                = yli::memory::MemoryAllocator<yli::ontology::LispFunction, 256>;
    using GenericLispFunctionOverloadMemoryAllocator = yli::memory::MemoryAllocator<yli::ontology::GenericLispFunctionOverload, 256>;
}

#endif
