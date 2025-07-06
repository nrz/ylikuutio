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

#ifndef YLIKUUTIO_ONTOLOGY_GENERIC_ENTITY_FACTORY_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_GENERIC_ENTITY_FACTORY_HPP_INCLUDED

#include "input_parameters_and_any_value_to_any_value_callback_with_universe.hpp"

namespace yli::data
{
    class AnyValue;
}

namespace yli::ontology
{
    class Variable;
    class CallbackEngine;
    class CallbackObject;
    class CallbackParameter;
    class Ecosystem;
    class Scene;
    class Brain;
    class Waypoint;
    class Camera;
    class Pipeline;
    class Material;
    class Species;
    class Object;
    class Symbiosis;
    class SymbiontMaterial;
    class SymbiontSpecies;
    class Holobiont;
    class Biont;
    class ShapeshifterTransformation;
    class ShapeshifterSequence;
    class ShapeshifterForm;
    class Shapeshifter;
    class Font2d;
    class Text2d;
    class VectorFont;
    class Glyph;
    class Text3d;
    class GlyphObject;
    class InputMode;
    class AudioTrack;
    class Console;
    class ConsoleCallbackEngine;
    class ConsoleCallbackObject;
    class ConsoleCallbackParameter;
    class ComputeTask;
    class LispFunction;
    struct CallbackEngineStruct;
    struct CallbackObjectStruct;
    struct VariableStruct;
    struct EcosystemStruct;
    struct SceneStruct;
    struct BrainStruct;
    struct WaypointStruct;
    struct CameraStruct;
    struct PipelineStruct;
    struct MaterialStruct;
    struct SpeciesStruct;
    struct ObjectStruct;
    struct SymbiosisStruct;
    struct SymbiontMaterialStruct;
    struct SymbiontSpeciesStruct;
    struct HolobiontStruct;
    struct BiontStruct;
    struct ShapeshifterTransformationStruct;
    struct ShapeshifterSequenceStruct;
    struct ShapeshifterFormStruct;
    struct ShapeshifterStruct;
    struct VectorFontStruct;
    struct GlyphStruct;
    struct Text3dStruct;
    struct GlyphObjectStruct;
    struct InputModeStruct;
    struct AudioTrackStruct;
    struct ConsoleStruct;
    struct ConsoleCallbackEngineStruct;
    struct ConsoleCallbackObjectStruct;
    struct ConsoleCallbackParameterStruct;
    struct FontStruct;
    struct TextStruct;
    struct LispFunctionStruct;
    struct CallbackParameterStruct;
    struct ComputeTaskStruct;

    class GenericEntityFactory
    {
        public:
            virtual Variable* create_variable(
                    const VariableStruct& variable_struct,
                    yli::data::AnyValue&& any_value) const = 0;

            virtual CallbackEngine* create_callback_engine(
                    const CallbackEngineStruct& callback_engine_struct) const = 0;

            virtual CallbackObject* create_callback_object(
                    const CallbackObjectStruct& callback_object_struct) const = 0;

            virtual CallbackParameter* create_callback_parameter(
                    const CallbackParameterStruct& callback_parameter_struct,
                    yli::data::AnyValue&& any_value) const = 0;

            virtual Ecosystem* create_ecosystem(const EcosystemStruct& ecosystem_struct) const = 0;
            virtual Scene* create_scene(const SceneStruct& scene_struct) const = 0;
            virtual Brain* create_brain(const BrainStruct& brain_struct) const = 0;
            virtual Waypoint* create_waypoint(const WaypointStruct& waypoint_struct) const = 0;
            virtual Camera* create_camera(const CameraStruct& camera_struct) const = 0;
            virtual Camera* create_default_camera(const CameraStruct& camera_struct) const = 0;
            virtual Pipeline* create_pipeline(const PipelineStruct& pipeline_struct) const = 0;
            virtual Material* create_material(const MaterialStruct& material_struct) const = 0;
            virtual Species* create_species(const SpeciesStruct& species_struct) const = 0;
            virtual Object* create_object(const ObjectStruct& object_struct) const = 0;
            virtual Symbiosis* create_symbiosis(const SymbiosisStruct& symbiosis_struct) const = 0;
            virtual SymbiontMaterial* create_symbiont_material(const SymbiontMaterialStruct& symbiont_material_struct) const = 0;
            virtual SymbiontSpecies* create_symbiont_species(const SymbiontSpeciesStruct& symbiont_species_struct) const = 0;
            virtual Holobiont* create_holobiont(const HolobiontStruct& holobiont_struct) const = 0;
            virtual Biont* create_biont(const BiontStruct& biont_struct) const = 0;
            virtual ShapeshifterTransformation* create_shapeshifter_transformation(
                    const ShapeshifterTransformationStruct& shapeshifter_transformation_struct) const = 0;
            virtual ShapeshifterSequence* create_shapeshifter_sequence(
                    const ShapeshifterSequenceStruct& shapeshifter_sequence_struct) const = 0;
            virtual ShapeshifterForm* create_shapeshifter_form(
                    const ShapeshifterFormStruct& shapeshifter_form_struct) const = 0;
            virtual Shapeshifter* create_shapeshifter(
                    const ShapeshifterStruct& shapeshifter_struct) const = 0;
            virtual VectorFont* create_vector_font(const VectorFontStruct& vector_font_struct) const = 0;
            virtual Glyph* create_glyph(const GlyphStruct& glyph_struct) const = 0;
            virtual Text2d* create_text_2d(const TextStruct& text_struct) const = 0;
            virtual Text3d* create_text_3d(const Text3dStruct& text_3d_struct) const = 0;
            virtual GlyphObject* create_glyph_object(const GlyphObjectStruct& glyph_object_struct) const = 0;
            virtual Font2d* create_font_2d(const FontStruct& font_struct) const = 0;
            virtual InputMode* create_input_mode(const InputModeStruct& input_mode_struct) const = 0;
            virtual AudioTrack* create_audio_track(const AudioTrackStruct& audio_track_struct) const = 0;
            virtual Console* create_console(const ConsoleStruct& console_struct) const = 0;
            virtual ConsoleCallbackEngine* create_console_callback_engine(
                    const ConsoleCallbackEngineStruct& console_callback_engine_struct) const = 0;
            virtual ConsoleCallbackObject* create_console_callback_object(
                    const ConsoleCallbackObjectStruct& console_callback_object_struct) const = 0;
            virtual ConsoleCallbackParameter* create_console_callback_parameter(
                    const ConsoleCallbackParameterStruct& console_callback_parameter_struct,
                    const yli::data::AnyValue& any_value) const = 0;
            virtual LispFunction* create_lisp_function(const LispFunctionStruct& lisp_function_struct) const = 0;
            virtual ComputeTask* create_compute_task(const ComputeTaskStruct& compute_task_struct) const = 0;
    };
}

#endif
