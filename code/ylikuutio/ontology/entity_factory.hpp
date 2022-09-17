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

#ifndef __YLIKUUTIO_ONTOLOGY_ENTITY_FACTORY_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_ENTITY_FACTORY_HPP_INCLUDED

// Include standard headers
#include <memory>    // std::make_shared, std::shared_ptr
#include <string>    // std::string

namespace yli::data
{
    class AnyValue;
}

namespace yli::ontology
{
    class Entity;
    class Universe;
    struct VariableStruct;
    struct EcosystemStruct;
    struct SceneStruct;
    struct ShaderStruct;
    struct MaterialStruct;
    struct ModelStruct;
    struct ObjectStruct;
    struct HolobiontStruct;
    struct VectorFontStruct;
    struct FontStruct;
    struct TextStruct;
    struct Text3DStruct;
    struct ConsoleStruct;
    struct LispFunctionStruct;
    struct CameraStruct;
    struct ComputeTaskStruct;
    struct BrainStruct;

    class EntityFactory final
    {
        public:
            // constructor.
            explicit EntityFactory(yli::ontology::Universe& universe);

            EntityFactory(const EntityFactory&) = delete;            // Delete copy constructor.
            EntityFactory& operator=(const EntityFactory&) = delete; // Delete copy assignment.

            // destructor.
            ~EntityFactory() = default;

            yli::ontology::Universe& get_universe() const;

            yli::ontology::Entity* create_variable(const yli::ontology::VariableStruct& variable_struct, const yli::data::AnyValue& any_value) const;
            yli::ontology::Entity* create_ecosystem(const yli::ontology::EcosystemStruct& ecosystem_struct) const;
            yli::ontology::Entity* create_scene(const yli::ontology::SceneStruct& scene_struct) const;
            yli::ontology::Entity* create_shader(const yli::ontology::ShaderStruct& shader_struct) const;
            yli::ontology::Entity* create_material(const yli::ontology::MaterialStruct& material_struct) const;
            yli::ontology::Entity* create_species(const yli::ontology::ModelStruct& model_struct) const;
            yli::ontology::Entity* create_object(const yli::ontology::ObjectStruct& object_struct) const;
            yli::ontology::Entity* create_symbiosis(const yli::ontology::ModelStruct& model_struct) const;
            yli::ontology::Entity* create_holobiont(const yli::ontology::HolobiontStruct& holobiont_struct) const;
            yli::ontology::Entity* create_vector_font(const yli::ontology::VectorFontStruct& vector_font_struct) const;
            yli::ontology::Entity* create_text2d(const yli::ontology::TextStruct& text_struct) const;
            yli::ontology::Entity* create_text3d(const yli::ontology::Text3DStruct& text_3d_struct) const;
            yli::ontology::Entity* create_font2d(const yli::ontology::FontStruct& font_struct) const;
            yli::ontology::Entity* create_console(const yli::ontology::ConsoleStruct& console_struct) const;
            yli::ontology::Entity* create_lisp_function(const yli::ontology::LispFunctionStruct& lisp_function_struct) const;
            yli::ontology::Entity* create_camera(const yli::ontology::CameraStruct& camera_struct) const;
            yli::ontology::Entity* create_compute_task(const yli::ontology::ComputeTaskStruct& compute_task_struct) const;
            yli::ontology::Entity* create_brain(const yli::ontology::BrainStruct& brain_struct) const;
            yli::ontology::Entity* create_callback_engine_entity() const;

        private:
            yli::ontology::Universe& universe;
    };
}

#endif
