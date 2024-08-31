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

#ifndef YLIKUUTIO_ONTOLOGY_GENERIC_ENTITY_FACTORY_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_GENERIC_ENTITY_FACTORY_HPP_INCLUDED

#include "input_parameters_and_any_value_to_any_value_callback_with_universe.hpp"

// Include standard headers
#include <string> // std::string

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
    class Font2d;
    class Text2d;
    class VectorFont;
    class Glyph;
    class Text3d;
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
    struct VectorFontStruct;
    struct GlyphStruct;
    struct Text3dStruct;
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
            virtual yli::ontology::Variable* create_variable(
                    const yli::ontology::VariableStruct& variable_struct,
                    const yli::data::AnyValue& any_value) const = 0;

            virtual yli::ontology::CallbackEngine* create_callback_engine(
                    const yli::ontology::CallbackEngineStruct& callback_engine_struct) const = 0;

            virtual yli::ontology::CallbackObject* create_callback_object(
                    const yli::ontology::CallbackObjectStruct& callback_object_struct) const = 0;

            virtual yli::ontology::CallbackParameter* create_callback_parameter(
                    const yli::ontology::CallbackParameterStruct& callback_parameter_struct,
                    yli::data::AnyValue&& any_value) const = 0;

            virtual yli::ontology::Ecosystem* create_ecosystem(const yli::ontology::EcosystemStruct& ecosystem_struct) const = 0;
            virtual yli::ontology::Scene* create_scene(const yli::ontology::SceneStruct& scene_struct) const = 0;
            virtual yli::ontology::Brain* create_brain(const yli::ontology::BrainStruct& brain_struct) const = 0;
            virtual yli::ontology::Waypoint* create_waypoint(const yli::ontology::WaypointStruct& waypoint_struct) const = 0;
            virtual yli::ontology::Camera* create_camera(const yli::ontology::CameraStruct& camera_struct) const = 0;
            virtual yli::ontology::Camera* create_default_camera(const yli::ontology::CameraStruct& camera_struct) const = 0;
            virtual yli::ontology::Pipeline* create_pipeline(const yli::ontology::PipelineStruct& pipeline_struct) const = 0;
            virtual yli::ontology::Material* create_material(const yli::ontology::MaterialStruct& material_struct) const = 0;
            virtual yli::ontology::Species* create_species(const yli::ontology::SpeciesStruct& species_struct) const = 0;
            virtual yli::ontology::Object* create_object(const yli::ontology::ObjectStruct& object_struct) const = 0;
            virtual yli::ontology::Symbiosis* create_symbiosis(const yli::ontology::SymbiosisStruct& symbiosis_struct) const = 0;
            virtual yli::ontology::SymbiontMaterial* create_symbiont_material(const SymbiontMaterialStruct& symbiont_material_struct) const = 0;
            virtual yli::ontology::SymbiontSpecies* create_symbiont_species(const yli::ontology::SymbiontSpeciesStruct& symbiont_species_struct) const = 0;
            virtual yli::ontology::Holobiont* create_holobiont(const yli::ontology::HolobiontStruct& holobiont_struct) const = 0;
            virtual yli::ontology::Biont* create_biont(const yli::ontology::BiontStruct& biont_struct) const = 0;
            virtual yli::ontology::ShapeshifterTransformation* create_shapeshifter_transformation(
                    const yli::ontology::ShapeshifterTransformationStruct& shapeshifter_transformation_struct) const = 0;
            virtual yli::ontology::ShapeshifterSequence* create_shapeshifter_sequence(
                    const yli::ontology::ShapeshifterSequenceStruct& shapeshifter_sequence_struct) const = 0;
            virtual yli::ontology::ShapeshifterForm* create_shapeshifter_form(
                    const yli::ontology::ShapeshifterFormStruct& shapeshifter_form_struct) const = 0;
            virtual yli::ontology::VectorFont* create_vector_font(const yli::ontology::VectorFontStruct& vector_font_struct) const = 0;
            virtual yli::ontology::Glyph* create_glyph(const yli::ontology::GlyphStruct& glyph_struct) const = 0;
            virtual yli::ontology::Text2d* create_text_2d(const yli::ontology::TextStruct& text_struct) const = 0;
            virtual yli::ontology::Text3d* create_text_3d(const yli::ontology::Text3dStruct& text_3d_struct) const = 0;
            virtual yli::ontology::Font2d* create_font_2d(const yli::ontology::FontStruct& font_struct) const = 0;
            virtual yli::ontology::InputMode* create_input_mode(const yli::ontology::InputModeStruct& input_mode_struct) const = 0;
            virtual yli::ontology::AudioTrack* create_audio_track(const yli::ontology::AudioTrackStruct& audio_track_struct) const = 0;
            virtual yli::ontology::Console* create_console(const yli::ontology::ConsoleStruct& console_struct) const = 0;
            virtual yli::ontology::ConsoleCallbackEngine* create_console_callback_engine(
                    const yli::ontology::ConsoleCallbackEngineStruct& console_callback_engine_struct) const = 0;
            virtual yli::ontology::ConsoleCallbackObject* create_console_callback_object(
                    const yli::ontology::ConsoleCallbackObjectStruct& console_callback_object_struct) const = 0;
            virtual yli::ontology::ConsoleCallbackParameter* create_console_callback_parameter(
                    const yli::ontology::ConsoleCallbackParameterStruct& console_callback_parameter_struct,
                    const yli::data::AnyValue& any_value) const = 0;
            virtual yli::ontology::LispFunction* create_lisp_function(const yli::ontology::LispFunctionStruct& lisp_function_struct) const = 0;
            virtual yli::ontology::ComputeTask* create_compute_task(const yli::ontology::ComputeTaskStruct& compute_task_struct) const = 0;
    };
}

#endif
