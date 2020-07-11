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
#include "variable.hpp"
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
#include "lisp_function.hpp"
#include "shapeshifter_sequence.hpp"
#include "camera.hpp"
#include "compute_task.hpp"
#include "brain.hpp"
#include "any_struct_entity.hpp"
#include "callback_engine_entity.hpp"
#include "variable_struct.hpp"
#include "world_struct.hpp"
#include "scene_struct.hpp"
#include "shader_struct.hpp"
#include "material_struct.hpp"
#include "species_struct.hpp"
#include "object_struct.hpp"
#include "symbiosis_struct.hpp"
#include "holobiont_struct.hpp"
#include "vector_font_struct.hpp"
#include "text3D_struct.hpp"
#include "console_struct.hpp"
#include "font_struct.hpp"
#include "lisp_function_struct.hpp"
#include "camera_struct.hpp"
#include "compute_task_struct.hpp"
#include "brain_struct.hpp"
#include "any_struct_entity_struct.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/data/any_struct.hpp"
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

    yli::ontology::Entity* EntityFactory::create_variable(const yli::ontology::VariableStruct& variable_struct) const
    {
        yli::ontology::Entity* variable_entity = new yli::ontology::Variable(this->universe, variable_struct);

        if (this->universe == variable_struct.parent)
        {
            // OK, this is a `variable` of the `Universe`.

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
        }
        else
        {
            // This is not a `variable` of the `Universe`.

            variable_entity->set_global_name(variable_struct.global_name);
            variable_entity->set_local_name(variable_struct.local_name);
        }

        if (variable_struct.should_ylikuutio_call_activate_callback_now)
        {
            variable_entity->activate();
        }

        return variable_entity;
    }

    yli::ontology::Entity* EntityFactory::create_world(const yli::ontology::WorldStruct& world_struct) const
    {
        yli::ontology::Entity* world_entity = new yli::ontology::World(this->universe, world_struct, (this->universe == nullptr ? nullptr : &this->universe->parent_of_worlds));

        if (!world_struct.global_name.empty() && world_struct.local_name.empty())
        {
            // Only `global_name` given, OK.
            world_entity->set_global_name(world_struct.global_name);
        }
        else if (world_struct.global_name.empty() && !world_struct.local_name.empty())
        {
            // Only `local_name` given, OK.
            world_entity->set_local_name(world_struct.local_name);
        }

        return world_entity;
    }

    yli::ontology::Entity* EntityFactory::create_scene(const yli::ontology::SceneStruct& scene_struct) const
    {
        yli::ontology::Entity* scene_entity = new yli::ontology::Scene(this->universe, scene_struct, (scene_struct.world == nullptr ? nullptr : &scene_struct.world->parent_of_scenes));
        scene_entity->set_global_name(scene_struct.global_name);
        scene_entity->set_local_name(scene_struct.local_name);
        return scene_entity;
    }

    yli::ontology::Entity* EntityFactory::create_shader(const yli::ontology::ShaderStruct& shader_struct) const
    {
        yli::ontology::Entity* shader_entity = new yli::ontology::Shader(this->universe, shader_struct);
        shader_entity->set_global_name(shader_struct.global_name);
        shader_entity->set_local_name(shader_struct.local_name);
        return shader_entity;
    }

    yli::ontology::Entity* EntityFactory::create_material(const yli::ontology::MaterialStruct& material_struct) const
    {
        yli::ontology::Entity* material_entity = new yli::ontology::Material(
                this->universe,
                material_struct,
                (material_struct.shader == nullptr ? nullptr : &material_struct.shader->parent_of_materials));

        material_entity->set_global_name(material_struct.global_name);
        material_entity->set_local_name(material_struct.local_name);
        return material_entity;
    }

    yli::ontology::Entity* EntityFactory::create_species(const yli::ontology::SpeciesStruct& species_struct) const
    {
        yli::ontology::Entity* species_entity = new yli::ontology::Species(
                this->universe,
                species_struct,
                (species_struct.material == nullptr ? nullptr : &species_struct.material->parent_of_species));

        species_entity->set_global_name(species_struct.global_name);
        species_entity->set_local_name(species_struct.local_name);
        return species_entity;
    }

    yli::ontology::Entity* EntityFactory::create_object(const yli::ontology::ObjectStruct& object_struct) const
    {
        yli::ontology::Entity* object_entity = new yli::ontology::Object(
                this->universe,
                object_struct,
                (object_struct.object_type == yli::ontology::ObjectType::REGULAR ? &object_struct.species_parent->parent_of_objects :
                 object_struct.object_type == yli::ontology::ObjectType::SHAPESHIFTER ? &object_struct.shapeshifter_sequence_parent->parent_of_objects :
                 object_struct.object_type == yli::ontology::ObjectType::CHARACTER ? &object_struct.text3D_parent->parent_of_objects :
                 nullptr));

        object_entity->set_global_name(object_struct.global_name);
        object_entity->set_local_name(object_struct.local_name);
        return object_entity;
    }

    yli::ontology::Entity* EntityFactory::create_symbiosis(const yli::ontology::SymbiosisStruct& symbiosis_struct) const
    {
        yli::ontology::Entity* symbiosis_entity = new yli::ontology::Symbiosis(this->universe, symbiosis_struct, (symbiosis_struct.parent == nullptr ? nullptr : &symbiosis_struct.parent->parent_of_symbioses));
        symbiosis_entity->set_global_name(symbiosis_struct.global_name);
        symbiosis_entity->set_local_name(symbiosis_struct.local_name);
        return symbiosis_entity;
    }

    yli::ontology::Entity* EntityFactory::create_holobiont(const yli::ontology::HolobiontStruct& holobiont_struct) const
    {
        yli::ontology::Entity* holobiont_entity = new yli::ontology::Holobiont(this->universe, holobiont_struct, (holobiont_struct.symbiosis_parent == nullptr ? nullptr : &holobiont_struct.symbiosis_parent->parent_of_holobionts));
        holobiont_entity->set_global_name(holobiont_struct.global_name);
        holobiont_entity->set_local_name(holobiont_struct.local_name);
        return holobiont_entity;
    }

    yli::ontology::Entity* EntityFactory::create_vector_font(const yli::ontology::VectorFontStruct& vector_font_struct) const
    {
        yli::ontology::Entity* vector_font_entity = new yli::ontology::VectorFont(this->universe, vector_font_struct);
        vector_font_entity->set_global_name(vector_font_struct.global_name);
        vector_font_entity->set_local_name(vector_font_struct.local_name);
        return vector_font_entity;
    }

    yli::ontology::Entity* EntityFactory::create_text2d(const yli::ontology::TextStruct& text_struct) const
    {
        yli::ontology::Entity* text2d_entity = new yli::ontology::Text2D(this->universe, text_struct, (text_struct.font2D_parent == nullptr ? nullptr : &text_struct.font2D_parent->parent_of_text2Ds));
        text2d_entity->set_global_name(text_struct.global_name);
        text2d_entity->set_local_name(text_struct.local_name);
        return text2d_entity;
    }

    yli::ontology::Entity* EntityFactory::create_text3d(const yli::ontology::Text3DStruct& text3D_struct) const
    {
        yli::ontology::Entity* text3d_entity = new yli::ontology::Text3D(this->universe, text3D_struct, (text3D_struct.parent == nullptr ? nullptr : &text3D_struct.parent->parent_of_text3Ds));
        text3d_entity->set_global_name(text3D_struct.global_name);
        text3d_entity->set_local_name(text3D_struct.local_name);
        return text3d_entity;
    }

    yli::ontology::Entity* EntityFactory::create_font2d(const yli::ontology::FontStruct& font_struct) const
    {
        yli::ontology::Entity* font2d_entity = new yli::ontology::Font2D(this->universe, font_struct, (this->universe == nullptr ? nullptr : &this->universe->parent_of_font2Ds));

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

        return font2d_entity;
    }

    yli::ontology::Entity* EntityFactory::create_console(const yli::ontology::ConsoleStruct& console_struct) const
    {
        yli::ontology::Entity* console_entity = new yli::ontology::Console(this->universe, console_struct, (this->universe == nullptr ? nullptr : &this->universe->parent_of_consoles));

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

        return console_entity;
    }

    yli::ontology::Entity* EntityFactory::create_lisp_function(const yli::ontology::LispFunctionStruct& lisp_function_struct) const
    {
        yli::ontology::Entity* lisp_function_entity = new yli::ontology::LispFunction(
                this->universe,
                lisp_function_struct,
                (lisp_function_struct.parent == nullptr ? nullptr : &lisp_function_struct.parent->parent_of_lisp_functions));

        lisp_function_entity->set_global_name(lisp_function_struct.global_name);
        lisp_function_entity->set_local_name(lisp_function_struct.local_name);
        return lisp_function_entity;
    }

    yli::ontology::Entity* EntityFactory::create_camera(const yli::ontology::CameraStruct& camera_struct) const
    {
        yli::ontology::Entity* camera_entity = new yli::ontology::Camera(this->universe, camera_struct, (camera_struct.parent == nullptr ? nullptr : &camera_struct.parent->parent_of_cameras));
        camera_entity->set_global_name(camera_struct.global_name);
        camera_entity->set_local_name(camera_struct.local_name);
        return camera_entity;
    }

    yli::ontology::Entity* EntityFactory::create_compute_task(const yli::ontology::ComputeTaskStruct& compute_task_struct) const
    {
        yli::ontology::Entity* compute_task_entity = new yli::ontology::ComputeTask(this->universe, compute_task_struct);
        compute_task_entity->set_global_name(compute_task_struct.global_name);
        compute_task_entity->set_local_name(compute_task_struct.local_name);
        return compute_task_entity;
    }

    yli::ontology::Entity* EntityFactory::create_brain(const yli::ontology::BrainStruct& brain_struct) const
    {
        yli::ontology::Entity* brain_entity = new yli::ontology::Brain(this->universe, brain_struct, (brain_struct.parent == nullptr ? nullptr : &brain_struct.parent->parent_of_brains));
        brain_entity->set_global_name(brain_struct.global_name);
        brain_entity->set_local_name(brain_struct.local_name);
        return brain_entity;
    }

    yli::ontology::Entity* EntityFactory::create_any_struct_entity(
            yli::ontology::Entity* const parent,
            const yli::ontology::AnyStructEntityStruct& any_struct_entity_struct) const
    {
        yli::ontology::Entity* any_struct_entity_entity = new yli::ontology::AnyStructEntity(this->universe, any_struct_entity_struct, (parent == nullptr ? nullptr : &parent->parent_of_any_struct_entities));

        any_struct_entity_entity->set_local_name(any_struct_entity_struct.local_name);

        if (this->universe == parent)
        {
            // OK, this is a `any_struct_entity` of the `Universe`.

            if (!any_struct_entity_struct.global_name.empty() && any_struct_entity_struct.local_name.empty())
            {
                // Only `global_name` given, OK.
                any_struct_entity_entity->set_global_name(any_struct_entity_struct.global_name);
            }
            else if (any_struct_entity_struct.global_name.empty() && !any_struct_entity_struct.local_name.empty())
            {
                // Only `local_name` given, OK.
                any_struct_entity_entity->set_local_name(any_struct_entity_struct.local_name);
            }
        }
        else
        {
            // This is not a `any_struct_entity` of the `Universe`.

            any_struct_entity_entity->set_global_name(any_struct_entity_struct.global_name);
            any_struct_entity_entity->set_local_name(any_struct_entity_struct.local_name);
        }

        return any_struct_entity_entity;
    }

    yli::ontology::Entity* EntityFactory::create_callback_engine_entity(const InputParametersAndAnyValueToAnyValueCallbackWithUniverse callback) const
    {
        return new yli::ontology::CallbackEngineEntity(
                this->universe,
                callback,
                (this->universe == nullptr ? nullptr : &this->universe->parent_of_callback_engine_entities));
    }
}
