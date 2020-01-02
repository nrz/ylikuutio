// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
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

#include "entity_factory.hpp"
#include "entity.hpp"
#include "universe.hpp"
#include "world.hpp"
#include "scene.hpp"
#include "shader.hpp"
#include "material.hpp"
#include "species.hpp"
#include "object.hpp"
#include "symbiosis.hpp"
#include "holobiont.hpp"
#include "vector_font.hpp"
#include "text2D.hpp"
#include "text3D.hpp"
#include "font2D.hpp"
#include "console.hpp"
#include "camera.hpp"
#include "compute_task.hpp"
#include "brain.hpp"
#include "any_value_entity.hpp"
#include "any_struct_entity.hpp"
#include "callback_engine_entity.hpp"
#include "scene_struct.hpp"
#include "shader_struct.hpp"
#include "material_struct.hpp"
#include "species_struct.hpp"
#include "object_struct.hpp"
#include "symbiosis_struct.hpp"
#include "holobiont_struct.hpp"
#include "vector_font_struct.hpp"
#include "text3D_struct.hpp"
#include "camera_struct.hpp"
#include "compute_task_struct.hpp"
#include "brain_struct.hpp"
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/common/any_struct.hpp"
#include "code/ylikuutio/callback/input_parameters_and_any_value_to_any_value_callback_with_universe.hpp"

// Include standard headers
#include <cstddef>   // std::size_t
#include <memory>    // std::make_shared, std::shared_ptr
#include <string>    // std::string

namespace yli
{
    namespace ontology
    {
        EntityFactory::EntityFactory(yli::ontology::Universe* const universe)
        {
            // constructor.
            this->universe = universe;
        }

        EntityFactory::~EntityFactory()
        {
            // destructor.
        }

        yli::ontology::Universe* EntityFactory::get_universe() const
        {
            return this->universe;
        }

        yli::ontology::Entity* EntityFactory::create_World() const
        {
            return new yli::ontology::World(this->universe);
        }

        yli::ontology::Entity* EntityFactory::create_Scene(const yli::ontology::SceneStruct& scene_struct) const
        {
            return new yli::ontology::Scene(this->universe, scene_struct);
        }

        yli::ontology::Entity* EntityFactory::create_Shader(const yli::ontology::ShaderStruct& shader_struct) const
        {
            return new yli::ontology::Shader(this->universe, shader_struct);
        }

        yli::ontology::Entity* EntityFactory::create_Material(const yli::ontology::MaterialStruct& material_struct) const
        {
            return new yli::ontology::Material(this->universe, material_struct);
        }

        yli::ontology::Entity* EntityFactory::create_Species(const yli::ontology::SpeciesStruct& species_struct) const
        {
            return new yli::ontology::Species(this->universe, species_struct);
        }

        yli::ontology::Entity* EntityFactory::create_Object(const yli::ontology::ObjectStruct& object_struct) const
        {
            return new yli::ontology::Object(this->universe, object_struct);
        }

        yli::ontology::Entity* EntityFactory::create_Symbiosis(const yli::ontology::SymbiosisStruct& symbiosis_struct) const
        {
            return new yli::ontology::Symbiosis(this->universe, symbiosis_struct);
        }

        yli::ontology::Entity* EntityFactory::create_Holobiont(const yli::ontology::HolobiontStruct& holobiont_struct) const
        {
            return new yli::ontology::Holobiont(this->universe, holobiont_struct);
        }

        yli::ontology::Entity* EntityFactory::create_VectorFont(const yli::ontology::VectorFontStruct& vector_font_struct) const
        {
            return new yli::ontology::VectorFont(this->universe, vector_font_struct);
        }

        yli::ontology::Entity* EntityFactory::create_Text2D(const yli::ontology::TextStruct& text_struct) const
        {
            return new yli::ontology::Text2D(this->universe, text_struct);
        }

        yli::ontology::Entity* EntityFactory::create_Text3D(const yli::ontology::Text3DStruct& text3D_struct) const
        {
            return new yli::ontology::Text3D(this->universe, text3D_struct);
        }

        yli::ontology::Entity* EntityFactory::create_Font2D(
                const std::size_t screen_width,
                const std::size_t screen_height,
                const std::string& texture_filename,
                const std::string& font_texture_file_format) const
        {
            return new yli::ontology::Font2D(
                    this->universe,
                    universe->get_window_width(),
                    universe->get_window_height(),
                    universe->get_text_size(),
                    universe->get_font_size(),
                    texture_filename.c_str(),
                    font_texture_file_format.c_str());
        }

        yli::ontology::Entity* EntityFactory::create_Console() const
        {
            return new yli::ontology::Console(this->universe);
        }

        yli::ontology::Entity* EntityFactory::create_Camera(const yli::ontology::CameraStruct& camera_struct) const
        {
            return new yli::ontology::Camera(this->universe, camera_struct);
        }

        yli::ontology::Entity* EntityFactory::create_ComputeTask(const yli::ontology::ComputeTaskStruct& compute_task_struct) const
        {
            return new yli::ontology::ComputeTask(this->universe, compute_task_struct);
        }

        yli::ontology::Entity* EntityFactory::create_Brain(const yli::ontology::BrainStruct& brain_struct) const
        {
            return new yli::ontology::Brain(this->universe, brain_struct);
        }

        yli::ontology::Entity* EntityFactory::create_AnyValueEntity(const std::shared_ptr<yli::common::AnyValue> any_value_shared_ptr) const
        {
            return new yli::ontology::AnyValueEntity(this->universe, any_value_shared_ptr);
        }

        yli::ontology::Entity* EntityFactory::create_AnyValueEntity(const yli::common::AnyValue& any_value) const
        {
            return new yli::ontology::AnyValueEntity(this->universe, any_value);
        }

        yli::ontology::Entity* EntityFactory::create_AnyStructEntity() const
        {
            return new yli::ontology::AnyStructEntity(this->universe);
        }

        yli::ontology::Entity* EntityFactory::create_AnyStructEntity(const yli::common::AnyStruct& any_struct) const
        {
            return new yli::ontology::AnyStructEntity(this->universe, any_struct);
        }

        yli::ontology::Entity* EntityFactory::create_CallbackEngineEntity(const InputParametersAndAnyValueToAnyValueCallbackWithUniverse callback) const
        {
            return new yli::ontology::CallbackEngineEntity(this->universe, callback);
        }
    }
}
