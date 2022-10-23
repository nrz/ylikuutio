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

#ifndef YLIKUUTIO_ONTOLOGY_CUSTOM_ENTITY_FACTORY_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_CUSTOM_ENTITY_FACTORY_HPP_INCLUDED

#include "code/ylikuutio/ontology/entity_factory.hpp"
#include "code/ylikuutio/ontology/entity.hpp"
#include "code/ylikuutio/ontology/brain.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/symbiosis.hpp"
#include "code/ylikuutio/ontology/shapeshifter_sequence.hpp"
#include "code/ylikuutio/ontology/text_3d.hpp"
#include "code/ylikuutio/ontology/object_struct.hpp"
#include "code/ylikuutio/ontology/holobiont_struct.hpp"

namespace yli::ontology
{
    class Entity;
    class Universe;

    class CustomEntityFactory final : public yli::ontology::EntityFactory
    {
        public:
            explicit CustomEntityFactory(yli::ontology::Universe& universe)
                : yli::ontology::EntityFactory(universe)
            {
            }

            template<typename T, typename... ModuleArgs>
                yli::ontology::Entity* create_object_derivative(
                        const yli::ontology::ObjectStruct& object_struct,
                        ModuleArgs... module_args)
                {
                    yli::ontology::Entity* object_entity = new T(
                            this->universe,
                            object_struct,
                            module_args...,
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

            template<typename T, typename... ModuleArgs>
                yli::ontology::Entity* create_holobiont_derivative(
                        const yli::ontology::HolobiontStruct& holobiont_struct,
                        ModuleArgs... module_args)
                {
                    yli::ontology::Entity* holobiont_entity = new T(
                            this->universe,
                            holobiont_struct,
                            module_args...,
                            (holobiont_struct.parent == nullptr ? nullptr : &holobiont_struct.parent->parent_of_holobionts),
                            (holobiont_struct.symbiosis == nullptr ? nullptr : &holobiont_struct.symbiosis->master_of_holobionts),
                            (holobiont_struct.brain == nullptr ? nullptr : holobiont_struct.brain->get_generic_master_module()));

                    holobiont_entity->set_global_name(holobiont_struct.global_name);
                    holobiont_entity->set_local_name(holobiont_struct.local_name);
                    return holobiont_entity;
                }
    };
}

#endif
