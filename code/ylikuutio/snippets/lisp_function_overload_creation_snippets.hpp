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

#ifndef YLIKUUTIO_SNIPPETS_LISP_FUNCTION_OVERLOAD_CREATION_SNIPPETS_HPP_INCLUDED
#define YLIKUUTIO_SNIPPETS_LISP_FUNCTION_OVERLOAD_CREATION_SNIPPETS_HPP_INCLUDED

#include "console_callback_snippets.hpp"
#include "code/ylikuutio/console/console_logic_module.hpp"

// `yli::ontology` files included in the canonical order.
#include "code/ylikuutio/ontology/entity.hpp"
#include "code/ylikuutio/ontology/movable.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/variable.hpp"
#include "code/ylikuutio/ontology/pipeline.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/symbiosis.hpp"
#include "code/ylikuutio/ontology/holobiont.hpp"
#include "code/ylikuutio/ontology/shapeshifter_transformation.hpp"
#include "code/ylikuutio/ontology/text_2d.hpp"
#include "code/ylikuutio/ontology/text_3d.hpp"
#include "code/ylikuutio/ontology/console.hpp"

namespace yli::snippets
{
    using yli::console::ConsoleLogicModule;
    using yli::ontology::Entity;
    using yli::ontology::Movable;
    using yli::ontology::Universe;
    using yli::ontology::Variable;
    using yli::ontology::Pipeline;
    using yli::ontology::Material;
    using yli::ontology::Species;
    using yli::ontology::Object;
    using yli::ontology::Symbiosis;
    using yli::ontology::Holobiont;
    using yli::ontology::ShapeshifterTransformation;
    using yli::ontology::Text2d;
    using yli::ontology::Text3d;
    using yli::ontology::Console;

    template<typename EntityFactoryType>
        void create_lisp_function_overloads_for_variable_callbacks(EntityFactoryType& entity_factory, Console& console)
        {
            // Variable callbacks.
            entity_factory.create_lisp_function_overload("variables", console, &Entity::print_variables0);
            entity_factory.create_lisp_function_overload("variables", console, &Entity::print_variables1);
            entity_factory.create_lisp_function_overload("create-variable", console, &Entity::create_variable_with_parent_name_type_value);
            entity_factory.create_lisp_function_overload("set", console, &Variable::set_variable_const_std_string);
            entity_factory.create_lisp_function_overload("copy", console, &Variable::set_variable_variable);
            entity_factory.create_lisp_function_overload("print", console, &Variable::print_value1);

        }

    template<typename EntityFactoryType>
        void create_lisp_function_overloads_for_object_callbacks(EntityFactoryType& entity_factory, Console& console)
        {
            // Object callbacks.
            entity_factory.create_lisp_function_overload("create-object", console, &Object::with_parent_name_x_y_z);
            entity_factory.create_lisp_function_overload("create-object", console, &Object::with_parent_name_x_y_z_yaw_pitch);
            entity_factory.create_lisp_function_overload("create-object", console, &Object::with_parent_name_x_y_z_roll_yaw_pitch);
        }

    template<typename EntityFactoryType>
        void create_lisp_function_overloads_for_holobiont_callbacks(EntityFactoryType& entity_factory, Console& console)
        {
            // Holobiont callbacks.
            entity_factory.create_lisp_function_overload("create-holobiont", console, &Holobiont::create_holobiont_with_parent_name_x_y_z);
            entity_factory.create_lisp_function_overload("create-holobiont", console, &Holobiont::create_holobiont_with_parent_name_x_y_z_yaw_pitch);
            entity_factory.create_lisp_function_overload("create-holobiont", console, &Holobiont::create_holobiont_with_parent_name_x_y_z_roll_yaw_pitch);
        }

    template<typename EntityFactoryType>
        void create_lisp_function_overloads_for_entity_callbacks(EntityFactoryType& entity_factory, Console& console)
        {
            // `Entity` handling callbacks.
            entity_factory.create_lisp_function_overload("entities", console, &Universe::print_entities);
            entity_factory.create_lisp_function_overload("parent", console, &Universe::print_parent);
            entity_factory.create_lisp_function_overload("children", console, &Entity::print_children);
            entity_factory.create_lisp_function_overload("activate", console, &Universe::activate_entity);
            entity_factory.create_lisp_function_overload("delete", console, &Universe::delete_entity);
            entity_factory.create_lisp_function_overload("info", console, &Universe::info0);
            entity_factory.create_lisp_function_overload("info", console, &Universe::info1);
        }

    template<typename EntityFactoryType>
        void create_lisp_function_overloads_for_entity_binding(EntityFactoryType& entity_factory, Console& console)
        {
            // `Entity` binding callbacks, `Movable`.
            entity_factory.create_lisp_function_overload("bind", console, &Movable::bind_to_new_brain);
            entity_factory.create_lisp_function_overload("unbind-from-brain", console, &Movable::unbind_from_brain);

            // `Entity` binding callbacks, `Pipeline`.
            entity_factory.create_lisp_function_overload("bind", console, &Pipeline::bind_to_new_ecosystem_parent);
            entity_factory.create_lisp_function_overload("bind", console, &Pipeline::bind_to_new_scene_parent);

            // `Entity` binding callbacks, `Material`.
            entity_factory.create_lisp_function_overload("bind", console, &Material::bind_to_new_ecosystem_parent);
            entity_factory.create_lisp_function_overload("bind", console, &Material::bind_to_new_scene_parent);
            entity_factory.create_lisp_function_overload("bind", console, &Material::bind_to_new_pipeline);

            // `Entity` binding callbacks, `Species`.
            entity_factory.create_lisp_function_overload("bind", console, &Species::bind_to_new_ecosystem_parent);
            entity_factory.create_lisp_function_overload("bind", console, &Species::bind_to_new_scene_parent);
            entity_factory.create_lisp_function_overload("bind", console, &Species::bind_to_new_material);

            // `Entity` binding callbacks, `Object`.
            entity_factory.create_lisp_function_overload("bind", console, &Object::bind_to_new_scene_parent);
            entity_factory.create_lisp_function_overload("bind", console, &Object::bind_to_new_species_master);

            // `Entity` binding callbacks, `Symbiosis`.
            entity_factory.create_lisp_function_overload("bind", console, &Symbiosis::bind_to_new_ecosystem_parent);
            entity_factory.create_lisp_function_overload("bind", console, &Symbiosis::bind_to_new_scene_parent);
            entity_factory.create_lisp_function_overload("bind", console, &Symbiosis::bind_to_new_pipeline);

            // `Entity` binding callbacks, `ShapeshifterTransformation`.
            entity_factory.create_lisp_function_overload("bind", console, &ShapeshifterTransformation::bind_to_new_material_parent);

            // `Entity` binding callbacks, `Text2d`.
            entity_factory.create_lisp_function_overload("bind", console, &Text2d::bind_to_new_font_2d_parent);

            // `Entity` binding callbacks, `Text3d`.
            entity_factory.create_lisp_function_overload("bind", console, &Text3d::bind_to_new_scene_parent);
            entity_factory.create_lisp_function_overload("bind", console, &Text3d::bind_to_new_vector_font_master);

            // `Entity` binding callbacks, `Console`.
            entity_factory.create_lisp_function_overload("bind", console, &Console::bind_to_new_font_2d);
        }

    template<typename EntityFactoryType>
        void create_lisp_function_overloads_for_entity_naming(EntityFactoryType& entity_factory, Console& console)
        {
            // `Entity` naming callbacks.
            entity_factory.create_lisp_function_overload("set-global-name", console, &Universe::set_global_name_for_entity);
            entity_factory.create_lisp_function_overload("set-local-name", console, &Universe::set_local_name_for_entity);
        }

    template<typename EntityFactoryType>
        void create_lisp_function_overloads_for_exit_program(EntityFactoryType& entity_factory, Console& console)
        {
            // Exit program callbacks.
            entity_factory.create_lisp_function_overload("bye", console, &yli::snippets::quit);
            entity_factory.create_lisp_function_overload("chau", console, &yli::snippets::quit);
            entity_factory.create_lisp_function_overload("ciao", console, &yli::snippets::quit);
            entity_factory.create_lisp_function_overload("heippa", console, &yli::snippets::quit);
            entity_factory.create_lisp_function_overload("quit", console, &yli::snippets::quit);
            entity_factory.create_lisp_function_overload("sayonara", console, &yli::snippets::quit);
        }

    template<typename EntityFactoryType>
        void create_lisp_function_overloads_for_other_callbacks(EntityFactoryType& entity_factory, Console& console)
        {
            // Other callbacks.
            entity_factory.create_lisp_function_overload("help", console, &yli::snippets::help);
            entity_factory.create_lisp_function_overload("clear", console, &ConsoleLogicModule::clear);
            entity_factory.create_lisp_function_overload("screenshot", console, &Universe::screenshot);
        }

    template<typename EntityFactoryType>
        void create_all_lisp_function_builtin_overloads(EntityFactoryType& entity_factory, Console& console)
        {
            create_lisp_function_overloads_for_variable_callbacks<EntityFactoryType>(entity_factory, console);
            create_lisp_function_overloads_for_object_callbacks<EntityFactoryType>(entity_factory, console);
            create_lisp_function_overloads_for_holobiont_callbacks<EntityFactoryType>(entity_factory, console);
            create_lisp_function_overloads_for_entity_callbacks<EntityFactoryType>(entity_factory, console);
            create_lisp_function_overloads_for_entity_binding<EntityFactoryType>(entity_factory, console);
            create_lisp_function_overloads_for_entity_naming<EntityFactoryType>(entity_factory, console);
            create_lisp_function_overloads_for_exit_program<EntityFactoryType>(entity_factory, console);
            create_lisp_function_overloads_for_other_callbacks<EntityFactoryType>(entity_factory, console);
        }
}

#endif
