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
#include "console_command.hpp"
#include "shapeshifter_sequence.hpp"
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
#include "font_struct.hpp"
#include "console_command_struct.hpp"
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

namespace yli::ontology
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

    yli::ontology::Entity* EntityFactory::create_world() const
    {
        return new yli::ontology::World(this->universe, (this->universe == nullptr ? nullptr : &this->universe->parent_of_worlds));
    }

    yli::ontology::Entity* EntityFactory::create_scene(const yli::ontology::SceneStruct& scene_struct) const
    {
        return new yli::ontology::Scene(this->universe, scene_struct, (scene_struct.world == nullptr ? nullptr : &scene_struct.world->parent_of_scenes));
    }

    yli::ontology::Entity* EntityFactory::create_shader(const yli::ontology::ShaderStruct& shader_struct) const
    {
        return new yli::ontology::Shader(this->universe, shader_struct);
    }

    yli::ontology::Entity* EntityFactory::create_material(const yli::ontology::MaterialStruct& material_struct) const
    {
        return new yli::ontology::Material(
                this->universe,
                material_struct,
                (material_struct.shader == nullptr ? nullptr : &material_struct.shader->parent_of_materials));
    }

    yli::ontology::Entity* EntityFactory::create_species(const yli::ontology::SpeciesStruct& species_struct) const
    {
        return new yli::ontology::Species(
                this->universe,
                species_struct,
                (species_struct.material == nullptr ? nullptr : &species_struct.material->parent_of_species));
    }

    yli::ontology::Entity* EntityFactory::create_object(const yli::ontology::ObjectStruct& object_struct) const
    {
        return new yli::ontology::Object(
                this->universe,
                object_struct,
                (object_struct.object_type == yli::ontology::ObjectType::REGULAR ? &object_struct.species_parent->parent_of_objects :
                 object_struct.object_type == yli::ontology::ObjectType::SHAPESHIFTER ? &object_struct.shapeshifter_sequence_parent->parent_of_objects :
                 object_struct.object_type == yli::ontology::ObjectType::CHARACTER ? &object_struct.text3D_parent->parent_of_objects :
                 nullptr));
    }

    yli::ontology::Entity* EntityFactory::create_symbiosis(const yli::ontology::SymbiosisStruct& symbiosis_struct) const
    {
        return new yli::ontology::Symbiosis(this->universe, symbiosis_struct, (symbiosis_struct.parent == nullptr ? nullptr : &symbiosis_struct.parent->parent_of_symbioses));
    }

    yli::ontology::Entity* EntityFactory::create_holobiont(const yli::ontology::HolobiontStruct& holobiont_struct) const
    {
        return new yli::ontology::Holobiont(this->universe, holobiont_struct, (holobiont_struct.symbiosis_parent == nullptr ? nullptr : &holobiont_struct.symbiosis_parent->parent_of_holobionts));
    }

    yli::ontology::Entity* EntityFactory::create_vector_font(const yli::ontology::VectorFontStruct& vector_font_struct) const
    {
        return new yli::ontology::VectorFont(this->universe, vector_font_struct);
    }

    yli::ontology::Entity* EntityFactory::create_text2d(const yli::ontology::TextStruct& text_struct) const
    {
        return new yli::ontology::Text2D(this->universe, text_struct, (text_struct.font2D_parent == nullptr ? nullptr : &text_struct.font2D_parent->parent_of_text2Ds));
    }

    yli::ontology::Entity* EntityFactory::create_text3d(const yli::ontology::Text3DStruct& text3D_struct) const
    {
        return new yli::ontology::Text3D(this->universe, text3D_struct, (text3D_struct.parent == nullptr ? nullptr : &text3D_struct.parent->parent_of_text3Ds));
    }

    yli::ontology::Entity* EntityFactory::create_font2d(const yli::ontology::FontStruct& font_struct) const
    {
        return new yli::ontology::Font2D(this->universe, font_struct, (this->universe == nullptr ? nullptr : &this->universe->parent_of_font2Ds));
    }

    yli::ontology::Entity* EntityFactory::create_console() const
    {
        return new yli::ontology::Console(this->universe, (this->universe == nullptr ? nullptr : &this->universe->parent_of_consoles));
    }

    yli::ontology::Entity* EntityFactory::create_console_command(const yli::ontology::ConsoleCommandStruct& console_command_struct) const
    {
        return new yli::ontology::ConsoleCommand(
                this->universe,
                console_command_struct,
                (console_command_struct.parent == nullptr ? nullptr : &console_command_struct.parent->parent_of_console_commands));
    }

    yli::ontology::Entity* EntityFactory::create_camera(const yli::ontology::CameraStruct& camera_struct) const
    {
        return new yli::ontology::Camera(this->universe, camera_struct, (camera_struct.parent == nullptr ? nullptr : &camera_struct.parent->parent_of_cameras));
    }

    yli::ontology::Entity* EntityFactory::create_compute_task(const yli::ontology::ComputeTaskStruct& compute_task_struct) const
    {
        return new yli::ontology::ComputeTask(this->universe, compute_task_struct);
    }

    yli::ontology::Entity* EntityFactory::create_brain(const yli::ontology::BrainStruct& brain_struct) const
    {
        return new yli::ontology::Brain(this->universe, brain_struct, (brain_struct.parent == nullptr ? nullptr : &brain_struct.parent->parent_of_brains));
    }

    yli::ontology::Entity* EntityFactory::create_any_value_entity(const std::shared_ptr<yli::common::AnyValue> any_value_shared_ptr) const
    {
        return new yli::ontology::AnyValueEntity(this->universe, any_value_shared_ptr);
    }

    yli::ontology::Entity* EntityFactory::create_any_value_entity(const yli::common::AnyValue& any_value) const
    {
        return new yli::ontology::AnyValueEntity(this->universe, any_value);
    }

    yli::ontology::Entity* EntityFactory::create_any_struct_entity() const
    {
        return new yli::ontology::AnyStructEntity(this->universe);
    }

    yli::ontology::Entity* EntityFactory::create_any_struct_entity(const yli::common::AnyStruct& any_struct) const
    {
        return new yli::ontology::AnyStructEntity(this->universe, any_struct);
    }

    yli::ontology::Entity* EntityFactory::create_callback_engine_entity(const InputParametersAndAnyValueToAnyValueCallbackWithUniverse callback) const
    {
        return new yli::ontology::CallbackEngineEntity(
                this->universe,
                callback,
                (this->universe == nullptr ? nullptr : &this->universe->parent_of_callback_engine_entities));
    }
}
