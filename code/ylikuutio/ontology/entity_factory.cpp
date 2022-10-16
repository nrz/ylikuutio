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

#include "entity_factory.hpp"
#include "generic_master_module.hpp"
#include "entity.hpp"
#include "variable.hpp"
#include "universe.hpp"
#include "ecosystem.hpp"
#include "scene.hpp"
#include "pipeline.hpp"
#include "material.hpp"
#include "species.hpp"
#include "object.hpp"
#include "symbiosis.hpp"
#include "holobiont.hpp"
#include "vector_font.hpp"
#include "text_2d.hpp"
#include "text_3d.hpp"
#include "font_2d.hpp"
#include "console.hpp"
#include "lisp_function.hpp"
#include "shapeshifter_sequence.hpp"
#include "camera.hpp"
#include "compute_task.hpp"
#include "brain.hpp"
#include "variable_struct.hpp"
#include "ecosystem_struct.hpp"
#include "scene_struct.hpp"
#include "pipeline_struct.hpp"
#include "material_struct.hpp"
#include "model_struct.hpp"
#include "object_struct.hpp"
#include "holobiont_struct.hpp"
#include "vector_font_struct.hpp"
#include "text_3d_struct.hpp"
#include "console_struct.hpp"
#include "font_struct.hpp"
#include "text_struct.hpp"
#include "lisp_function_struct.hpp"
#include "camera_struct.hpp"
#include "compute_task_struct.hpp"
#include "brain_struct.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <iostream>  // std::cout, std::cin, std::cerr
#include <string>    // std::string
#include <variant>   // std::holds_alternative, std::variant

namespace yli::ontology
{
    EntityFactory::EntityFactory(yli::ontology::Universe& universe)
        : universe { universe }
    {
        // constructor.
    }

    yli::ontology::Universe& EntityFactory::get_universe() const
    {
        return this->universe;
    }

    yli::ontology::Entity* EntityFactory::create_variable(const yli::ontology::VariableStruct& variable_struct, const yli::data::AnyValue& any_value) const
    {
        yli::ontology::Entity* variable_entity = new yli::ontology::Variable(this->universe, variable_struct, any_value);

        if (&this->universe == variable_struct.parent)
        {
            // OK, this is a `Variable` of the `Universe`.

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
            else if (!variable_struct.global_name.empty() && !variable_struct.local_name.empty())
            {
                std::cerr << "ERROR: `EntityFactory::create_variable`: both global and local names given for a `Variable`\n";
                std::cerr << "which is a child of `Universe`. For children of the `Universe` global and local names\n";
                std::cerr << "are the same and only 1 of them can be given. No name given to this `Variable`!\n";
            }
        }
        else
        {
            // This is not a `Variable` of the `Universe`.

            variable_entity->set_global_name(variable_struct.global_name);
            variable_entity->set_local_name(variable_struct.local_name);
        }

        if (variable_struct.should_call_activate_callback_now)
        {
            variable_entity->activate();
        }

        return variable_entity;
    }

    yli::ontology::Entity* EntityFactory::create_ecosystem(const yli::ontology::EcosystemStruct& ecosystem_struct) const
    {
        yli::ontology::Entity* ecosystem_entity = new yli::ontology::Ecosystem(
                this->universe,
                ecosystem_struct,
                &this->universe.parent_of_ecosystems);

        if (!ecosystem_struct.global_name.empty() && ecosystem_struct.local_name.empty())
        {
            // Only `global_name` given, OK.
            ecosystem_entity->set_global_name(ecosystem_struct.global_name);
        }
        else if (ecosystem_struct.global_name.empty() && !ecosystem_struct.local_name.empty())
        {
            // Only `local_name` given, OK.
            ecosystem_entity->set_local_name(ecosystem_struct.local_name);
        }
        else if (!ecosystem_struct.global_name.empty() && !ecosystem_struct.local_name.empty())
        {
            std::cerr << "ERROR: `EntityFactory::create_ecosystem`: both global and local names given for a `Ecosystem`\n";
            std::cerr << "which is a child of `Universe`. For children of the `Universe` global and local names\n";
            std::cerr << "are the same and only 1 of them can be given. No name given to this `Ecosystem`!\n";
        }

        return ecosystem_entity;
    }

    yli::ontology::Entity* EntityFactory::create_scene(const yli::ontology::SceneStruct& scene_struct) const
    {
        yli::ontology::Entity* scene_entity = new yli::ontology::Scene(
                this->universe,
                scene_struct,
                &this->universe.parent_of_scenes);

        if (!scene_struct.global_name.empty() && scene_struct.local_name.empty())
        {
            // Only `global_name` given, OK.
            scene_entity->set_global_name(scene_struct.global_name);
        }
        else if (scene_struct.global_name.empty() && !scene_struct.local_name.empty())
        {
            // Only `local_name` given, OK.
            scene_entity->set_local_name(scene_struct.local_name);
        }
        else if (!scene_struct.global_name.empty() && !scene_struct.local_name.empty())
        {
            std::cerr << "ERROR: `EntityFactory::create_scene`: both global and local names given for a `Scene`\n";
            std::cerr << "which is a child of `Universe`. For children of the `Universe` global and local names\n";
            std::cerr << "are the same and only 1 of them can be given. No name given to this `Scene`!\n";
        }

        yli::ontology::Scene* const scene = static_cast<yli::ontology::Scene*>(scene_entity);

        // Create the default `Camera`.
        yli::ontology::CameraStruct camera_struct = scene_struct.default_camera_struct;
        camera_struct.scene = scene;
        new yli::ontology::Camera(this->universe, camera_struct, &scene->parent_of_default_camera, nullptr); // Create the default `Camera`.

        return scene_entity;
    }

    yli::ontology::Entity* EntityFactory::create_pipeline(const yli::ontology::PipelineStruct& pipeline_struct) const
    {
        yli::ontology::Entity* pipeline_entity = new yli::ontology::Pipeline(
                this->universe,
                pipeline_struct,
                // `Ecosystem` or `Scene` parent.
                ((std::holds_alternative<yli::ontology::Ecosystem*>(pipeline_struct.parent) && std::get<yli::ontology::Ecosystem*>(pipeline_struct.parent) != nullptr) ?
                 &(std::get<yli::ontology::Ecosystem*>(pipeline_struct.parent)->parent_of_pipelines) :
                 (std::holds_alternative<yli::ontology::Scene*>(pipeline_struct.parent) && std::get<yli::ontology::Scene*>(pipeline_struct.parent) != nullptr) ?
                 &(std::get<yli::ontology::Scene*>(pipeline_struct.parent)->parent_of_pipelines) :
                 nullptr));
        pipeline_entity->set_global_name(pipeline_struct.global_name);
        pipeline_entity->set_local_name(pipeline_struct.local_name);
        return pipeline_entity;
    }

    yli::ontology::Entity* EntityFactory::create_material(const yli::ontology::MaterialStruct& material_struct) const
    {
        yli::ontology::Entity* material_entity = new yli::ontology::Material(
                this->universe,
                material_struct,
                // `Ecosystem` or `Scene` parent.
                ((std::holds_alternative<yli::ontology::Ecosystem*>(material_struct.parent) && std::get<yli::ontology::Ecosystem*>(material_struct.parent) != nullptr) ?
                 &(std::get<yli::ontology::Ecosystem*>(material_struct.parent)->parent_of_materials) :
                 (std::holds_alternative<yli::ontology::Scene*>(material_struct.parent) && std::get<yli::ontology::Scene*>(material_struct.parent) != nullptr) ?
                 &(std::get<yli::ontology::Scene*>(material_struct.parent)->parent_of_materials) :
                 nullptr),
                (material_struct.pipeline == nullptr ? nullptr : material_struct.pipeline->get_master_module()));

        material_entity->set_global_name(material_struct.global_name);
        material_entity->set_local_name(material_struct.local_name);
        return material_entity;
    }

    yli::ontology::Entity* EntityFactory::create_species(const yli::ontology::ModelStruct& model_struct) const
    {
        yli::ontology::Entity* species_entity = new yli::ontology::Species(
                this->universe,
                model_struct,
                // `Ecosystem` or `Scene` parent.
                ((std::holds_alternative<yli::ontology::Ecosystem*>(model_struct.parent) && std::get<yli::ontology::Ecosystem*>(model_struct.parent) != nullptr) ? &(std::get<yli::ontology::Ecosystem*>(model_struct.parent)->parent_of_species) :
                 (std::holds_alternative<yli::ontology::Scene*>(model_struct.parent) && std::get<yli::ontology::Scene*>(model_struct.parent) != nullptr) ? &(std::get<yli::ontology::Scene*>(model_struct.parent)->parent_of_species) :
                 nullptr),
                (model_struct.material == nullptr ? nullptr : &model_struct.material->master_of_species));

        species_entity->set_global_name(model_struct.global_name);
        species_entity->set_local_name(model_struct.local_name);
        return species_entity;
    }

    yli::ontology::Entity* EntityFactory::create_object(const yli::ontology::ObjectStruct& object_struct) const
    {
        yli::ontology::Entity* object_entity = new yli::ontology::Object(
                this->universe,
                object_struct,
                // `Scene` parent.
                ((object_struct.parent != nullptr) ?  &object_struct.parent->parent_of_objects : nullptr),
                // mesh master.
                ((std::holds_alternative<yli::ontology::Species*>(object_struct.mesh_master) && std::get<yli::ontology::Species*>(object_struct.mesh_master) != nullptr) ?
                 &(std::get<yli::ontology::Species*>(object_struct.mesh_master)->master_of_objects) :
                 (std::holds_alternative<yli::ontology::ShapeshifterSequence*>(object_struct.mesh_master) && std::get<yli::ontology::ShapeshifterSequence*>(object_struct.mesh_master) != nullptr) ?
                 &(std::get<yli::ontology::ShapeshifterSequence*>(object_struct.mesh_master)->master_of_objects) :
                 (std::holds_alternative<yli::ontology::Text3D*>(object_struct.mesh_master) && std::get<yli::ontology::Text3D*>(object_struct.mesh_master) != nullptr) ?
                 &(std::get<yli::ontology::Text3D*>(object_struct.mesh_master)->master_of_objects) :
                 nullptr),
                // `Brain` master.
                (object_struct.brain == nullptr ? nullptr : object_struct.brain->get_generic_master_module()));

        object_entity->set_global_name(object_struct.global_name);
        object_entity->set_local_name(object_struct.local_name);
        return object_entity;
    }

    yli::ontology::Entity* EntityFactory::create_symbiosis(const yli::ontology::ModelStruct& model_struct) const
    {
        yli::ontology::Entity* symbiosis_entity = new yli::ontology::Symbiosis(
                this->universe,
                model_struct,
                // `Ecosystem` or `Scene` parent.
                ((std::holds_alternative<yli::ontology::Ecosystem*>(model_struct.parent) && std::get<yli::ontology::Ecosystem*>(model_struct.parent) != nullptr) ? &(std::get<yli::ontology::Ecosystem*>(model_struct.parent)->parent_of_species) :
                 (std::holds_alternative<yli::ontology::Scene*>(model_struct.parent) && std::get<yli::ontology::Scene*>(model_struct.parent) != nullptr) ? &(std::get<yli::ontology::Scene*>(model_struct.parent)->parent_of_species) :
                 nullptr),
                (model_struct.pipeline == nullptr ? nullptr : &model_struct.pipeline->master_of_symbioses));

        symbiosis_entity->set_global_name(model_struct.global_name);
        symbiosis_entity->set_local_name(model_struct.local_name);
        return symbiosis_entity;
    }

    yli::ontology::Entity* EntityFactory::create_holobiont(const yli::ontology::HolobiontStruct& holobiont_struct) const
    {
        yli::ontology::Entity* holobiont_entity = new yli::ontology::Holobiont(
                this->universe,
                holobiont_struct,
                (holobiont_struct.parent == nullptr ? nullptr : &holobiont_struct.parent->parent_of_holobionts),
                (holobiont_struct.symbiosis == nullptr ? nullptr : &holobiont_struct.symbiosis->master_of_holobionts),
                (holobiont_struct.brain == nullptr ? nullptr : holobiont_struct.brain->get_generic_master_module()));

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
        yli::ontology::Entity* text2d_entity = new yli::ontology::Text2D(
                this->universe,
                text_struct,
                (text_struct.parent == nullptr ? nullptr : &text_struct.parent->parent_of_text_2ds));

        text2d_entity->set_global_name(text_struct.global_name);
        text2d_entity->set_local_name(text_struct.local_name);
        return text2d_entity;
    }

    yli::ontology::Entity* EntityFactory::create_text3d(const yli::ontology::Text3DStruct& text_3d_struct) const
    {
        yli::ontology::Entity* text3d_entity = new yli::ontology::Text3D(
                this->universe,
                text_3d_struct,
                (text_3d_struct.parent == nullptr ? nullptr : &text_3d_struct.parent->parent_of_text_3ds),
                (text_3d_struct.brain == nullptr ? nullptr : text_3d_struct.brain->get_generic_master_module()));

        text3d_entity->set_global_name(text_3d_struct.global_name);
        text3d_entity->set_local_name(text_3d_struct.local_name);
        return text3d_entity;
    }

    yli::ontology::Entity* EntityFactory::create_font2d(const yli::ontology::FontStruct& font_struct) const
    {
        yli::ontology::Entity* font2d_entity = new yli::ontology::Font2D(
                this->universe,
                font_struct,
                &this->universe.parent_of_font_2ds);

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
        else if (!font_struct.global_name.empty() && !font_struct.local_name.empty())
        {
            std::cerr << "ERROR: `EntityFactory::create_font2d`: both global and local names given for a `Font2D`\n";
            std::cerr << "which is a child of `Universe`. For children of the `Universe` global and local names\n";
            std::cerr << "are the same and only 1 of them can be given. No name given to this `Font2D`!\n";
        }

        return font2d_entity;
    }

    yli::ontology::Entity* EntityFactory::create_console(const yli::ontology::ConsoleStruct& console_struct) const
    {
        yli::ontology::Entity* console_entity = new yli::ontology::Console(
                this->universe,
                console_struct,
                &this->universe.parent_of_consoles,
                (console_struct.font_2d == nullptr ? nullptr : &console_struct.font_2d->master_of_consoles));

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
        else if (!console_struct.global_name.empty() && !console_struct.local_name.empty())
        {
            std::cerr << "ERROR: `EntityFactory::create_console`: both global and local names given for a `Console`\n";
            std::cerr << "which is a child of `Universe`. For children of the `Universe` global and local names\n";
            std::cerr << "are the same and only 1 of them can be given. No name given to this `Console`!\n";
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
        yli::ontology::Entity* camera_entity = new yli::ontology::Camera(
                this->universe,
                camera_struct,
                (camera_struct.scene == nullptr ? nullptr : &camera_struct.scene->parent_of_cameras),
                (camera_struct.brain == nullptr ? nullptr : camera_struct.brain->get_generic_master_module()));

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
        yli::ontology::Entity* brain_entity = new yli::ontology::Brain(
                this->universe,
                brain_struct,
                (brain_struct.parent == nullptr ? nullptr : &brain_struct.parent->parent_of_brains));

        brain_entity->set_global_name(brain_struct.global_name);
        brain_entity->set_local_name(brain_struct.local_name);
        return brain_entity;
    }
}
