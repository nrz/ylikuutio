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

#ifndef YLIKUUTIO_ONTOLOGY_GENERIC_ENTITY_FACTORY_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_GENERIC_ENTITY_FACTORY_HPP_INCLUDED

namespace yli::data
{
    class AnyValue;
}

namespace yli::ontology
{
    class Entity;
    struct VariableStruct;
    struct EcosystemStruct;
    struct SceneStruct;
    struct PipelineStruct;
    struct MaterialStruct;
    struct ModelStruct;
    struct ObjectStruct;
    struct HolobiontStruct;
    struct BiontStruct;
    struct VectorFontStruct;
    struct Text3DStruct;
    struct ConsoleStruct;
    struct FontStruct;
    struct TextStruct;
    struct LispFunctionStruct;
    struct CameraStruct;
    struct ComputeTaskStruct;
    struct BrainStruct;

    class GenericEntityFactory
    {
        public:
            virtual yli::ontology::Entity* create_variable(
                    const yli::ontology::VariableStruct& variable_struct,
                    const yli::data::AnyValue& any_value) const = 0;

            virtual yli::ontology::Entity* create_ecosystem(const yli::ontology::EcosystemStruct& ecosystem_struct) const = 0;
            virtual yli::ontology::Entity* create_scene(const yli::ontology::SceneStruct& scene_struct) const = 0;
            virtual yli::ontology::Entity* create_pipeline(const yli::ontology::PipelineStruct& pipeline_struct) const = 0;
            virtual yli::ontology::Entity* create_material(const yli::ontology::MaterialStruct& material_struct) const = 0;
            virtual yli::ontology::Entity* create_species(const yli::ontology::ModelStruct& model_struct) const = 0;
            virtual yli::ontology::Entity* create_object(const yli::ontology::ObjectStruct& object_struct) const = 0;
            virtual yli::ontology::Entity* create_symbiosis(const yli::ontology::ModelStruct& model_struct) const = 0;
            virtual yli::ontology::Entity* create_symbiont_material(const MaterialStruct& material_struct) const = 0;
            virtual yli::ontology::Entity* create_symbiont_species(const yli::ontology::ModelStruct& model_struct) const = 0;
            virtual yli::ontology::Entity* create_holobiont(const yli::ontology::HolobiontStruct& holobiont_struct) const = 0;
            virtual yli::ontology::Entity* create_biont(const yli::ontology::BiontStruct& biont_struct) const = 0;
            virtual yli::ontology::Entity* create_vector_font(const yli::ontology::VectorFontStruct& vector_font_struct) const = 0;
            virtual yli::ontology::Entity* create_glyph(const yli::ontology::ModelStruct& model_struct) const = 0;
            virtual yli::ontology::Entity* create_text2d(const yli::ontology::TextStruct& text_struct) const = 0;
            virtual yli::ontology::Entity* create_text3d(const yli::ontology::Text3DStruct& text_3d_struct) const = 0;
            virtual yli::ontology::Entity* create_font2d(const yli::ontology::FontStruct& font_struct) const = 0;
            virtual yli::ontology::Entity* create_console(const yli::ontology::ConsoleStruct& console_struct) const = 0;
            virtual yli::ontology::Entity* create_lisp_function(const yli::ontology::LispFunctionStruct& lisp_function_struct) const = 0;
            virtual yli::ontology::Entity* create_camera(const yli::ontology::CameraStruct& camera_struct) const = 0;
            virtual yli::ontology::Entity* create_compute_task(const yli::ontology::ComputeTaskStruct& compute_task_struct) const = 0;
            virtual yli::ontology::Entity* create_brain(const yli::ontology::BrainStruct& brain_struct) const = 0;
    };
}

#endif
