// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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

#include "gtest/gtest.h"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/ecosystem.hpp"
#include "code/ylikuutio/ontology/universe_struct.hpp"
#include "code/ylikuutio/ontology/ecosystem_struct.hpp"
#include "code/ylikuutio/render/graphics_api_backend.hpp"

TEST(ecosystems_must_be_initialized_appropriately, headless)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::EcosystemStruct ecosystem_struct1;
    yli::ontology::Ecosystem* const ecosystem1 = new yli::ontology::Ecosystem(
            *universe,
            ecosystem_struct1,
            &universe->parent_of_ecosystems);

    // `Universe` member functions.
    ASSERT_EQ(universe->get_number_of_ecosystems(), 1);
    ASSERT_EQ(universe->get_active_scene(), nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem1->get_childID(), 0);
    ASSERT_EQ(ecosystem1->get_type(), "yli::ontology::Ecosystem*");
    ASSERT_TRUE(ecosystem1->get_can_be_erased());
    ASSERT_EQ(&(ecosystem1->get_universe()), universe);
    ASSERT_EQ(ecosystem1->get_scene(), nullptr);
    ASSERT_EQ(ecosystem1->get_parent(), universe);
    ASSERT_EQ(ecosystem1->get_number_of_non_variable_children(), 0);

    yli::ontology::EcosystemStruct ecosystem_struct2;
    yli::ontology::Ecosystem* const ecosystem2 = new yli::ontology::Ecosystem(
            *universe,
            ecosystem_struct2,
            &universe->parent_of_ecosystems);

    // `Universe` member functions.
    ASSERT_EQ(universe->get_number_of_ecosystems(), 2);
    ASSERT_EQ(universe->get_active_scene(), nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 2);

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem2->get_childID(), 1);
    ASSERT_EQ(ecosystem2->get_type(), "yli::ontology::Ecosystem*");
    ASSERT_TRUE(ecosystem2->get_can_be_erased());
    ASSERT_EQ(&(ecosystem2->get_universe()), universe);
    ASSERT_EQ(ecosystem2->get_scene(), nullptr);
    ASSERT_EQ(ecosystem2->get_parent(), universe);
    ASSERT_EQ(ecosystem2->get_number_of_non_variable_children(), 0);

    yli::ontology::EcosystemStruct ecosystem_struct3;
    yli::ontology::Ecosystem* const ecosystem3 = new yli::ontology::Ecosystem(
            *universe,
            ecosystem_struct3,
            &universe->parent_of_ecosystems);

    // `Universe` member functions.
    ASSERT_EQ(universe->get_number_of_ecosystems(), 3);
    ASSERT_EQ(universe->get_active_scene(), nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 3);

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem3->get_childID(), 2);
    ASSERT_EQ(ecosystem3->get_type(), "yli::ontology::Ecosystem*");
    ASSERT_TRUE(ecosystem3->get_can_be_erased());
    ASSERT_EQ(&(ecosystem3->get_universe()), universe);
    ASSERT_EQ(ecosystem3->get_scene(), nullptr);
    ASSERT_EQ(ecosystem3->get_parent(), universe);
    ASSERT_EQ(ecosystem3->get_number_of_non_variable_children(), 0);

    yli::ontology::EcosystemStruct ecosystem_struct4;
    yli::ontology::Ecosystem* const ecosystem4 = new yli::ontology::Ecosystem(
            *universe,
            ecosystem_struct4,
            &universe->parent_of_ecosystems);

    // `Universe` member functions.
    ASSERT_EQ(universe->get_number_of_ecosystems(), 4);
    ASSERT_EQ(universe->get_active_scene(), nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 4);

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem4->get_childID(), 3);
    ASSERT_EQ(ecosystem4->get_type(), "yli::ontology::Ecosystem*");
    ASSERT_TRUE(ecosystem4->get_can_be_erased());
    ASSERT_EQ(&(ecosystem4->get_universe()), universe);
    ASSERT_EQ(ecosystem4->get_scene(), nullptr);
    ASSERT_EQ(ecosystem4->get_parent(), universe);
    ASSERT_EQ(ecosystem4->get_number_of_non_variable_children(), 0);
}

TEST(ecosystems_must_be_initialized_appropriately_after_having_deleted_the_earlier_ecosystems, headless)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::EcosystemStruct ecosystem_struct1;
    yli::ontology::Ecosystem* const ecosystem1 = new yli::ontology::Ecosystem(
            *universe,
            ecosystem_struct1,
            &universe->parent_of_ecosystems);

    // `Universe` member functions.
    ASSERT_EQ(universe->get_number_of_ecosystems(), 1);
    ASSERT_EQ(universe->get_active_scene(), nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_scene(), nullptr);
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem1->get_childID(), 0);
    ASSERT_EQ(ecosystem1->get_type(), "yli::ontology::Ecosystem*");
    ASSERT_TRUE(ecosystem1->get_can_be_erased());
    ASSERT_EQ(&(ecosystem1->get_universe()), universe);
    ASSERT_EQ(ecosystem1->get_scene(), nullptr);
    ASSERT_EQ(ecosystem1->get_parent(), universe);
    ASSERT_EQ(ecosystem1->get_number_of_non_variable_children(), 0);

    delete ecosystem1;
    yli::ontology::EcosystemStruct ecosystem_struct2;
    yli::ontology::Ecosystem* const ecosystem2 = new yli::ontology::Ecosystem(
            *universe,
            ecosystem_struct2,
            &universe->parent_of_ecosystems);

    // `Universe` member functions.
    ASSERT_EQ(universe->get_number_of_ecosystems(), 1);
    ASSERT_EQ(universe->get_active_scene(), nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_scene(), nullptr);
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem2->get_childID(), 0);
    ASSERT_EQ(ecosystem2->get_type(), "yli::ontology::Ecosystem*");
    ASSERT_TRUE(ecosystem2->get_can_be_erased());
    ASSERT_EQ(&(ecosystem2->get_universe()), universe);
    ASSERT_EQ(ecosystem2->get_parent(), universe);
    ASSERT_EQ(ecosystem2->get_number_of_non_variable_children(), 0);

    delete ecosystem2;
    yli::ontology::EcosystemStruct ecosystem_struct3;
    yli::ontology::Ecosystem* const ecosystem3 = new yli::ontology::Ecosystem(
            *universe,
            ecosystem_struct3,
            &universe->parent_of_ecosystems);

    // `Universe` member functions.
    ASSERT_EQ(universe->get_number_of_ecosystems(), 1);
    ASSERT_EQ(universe->get_active_scene(), nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_scene(), nullptr);
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem3->get_childID(), 0);
    ASSERT_EQ(ecosystem3->get_type(), "yli::ontology::Ecosystem*");
    ASSERT_TRUE(ecosystem3->get_can_be_erased());
    ASSERT_EQ(&(ecosystem3->get_universe()), universe);
    ASSERT_EQ(ecosystem3->get_scene(), nullptr);
    ASSERT_EQ(ecosystem3->get_parent(), universe);
    ASSERT_EQ(ecosystem3->get_number_of_non_variable_children(), 0);

    delete ecosystem3;
    yli::ontology::EcosystemStruct ecosystem_struct4;
    yli::ontology::Ecosystem* const ecosystem4 = new yli::ontology::Ecosystem(
            *universe,
            ecosystem_struct4,
            &universe->parent_of_ecosystems);

    // `Universe` member functions.
    ASSERT_EQ(universe->get_number_of_ecosystems(), 1);
    ASSERT_EQ(universe->get_active_scene(), nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem4->get_childID(), 0);
    ASSERT_EQ(ecosystem4->get_type(), "yli::ontology::Ecosystem*");
    ASSERT_TRUE(ecosystem4->get_can_be_erased());
    ASSERT_EQ(&(ecosystem4->get_universe()), universe);
    ASSERT_EQ(ecosystem4->get_scene(), nullptr);
    ASSERT_EQ(ecosystem4->get_parent(), universe);
    ASSERT_EQ(ecosystem4->get_number_of_non_variable_children(), 0);
}

TEST(ecosystems_must_be_initialized_appropriately_after_having_deleted_some_earlier_ecosystems, headless)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::EcosystemStruct ecosystem_struct1;
    yli::ontology::Ecosystem* const ecosystem1 = new yli::ontology::Ecosystem(
            *universe,
            ecosystem_struct1,
            &universe->parent_of_ecosystems);

    // `Universe` member functions.
    ASSERT_EQ(universe->get_number_of_ecosystems(), 1);
    ASSERT_EQ(universe->get_active_scene(), nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_scene(), nullptr);
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem1->get_childID(), 0);
    ASSERT_EQ(ecosystem1->get_type(), "yli::ontology::Ecosystem*");
    ASSERT_TRUE(ecosystem1->get_can_be_erased());
    ASSERT_EQ(&(ecosystem1->get_universe()), universe);
    ASSERT_EQ(ecosystem1->get_scene(), nullptr);
    ASSERT_EQ(ecosystem1->get_parent(), universe);
    ASSERT_EQ(ecosystem1->get_number_of_non_variable_children(), 0);

    yli::ontology::EcosystemStruct ecosystem_struct2;
    yli::ontology::Ecosystem* const ecosystem2 = new yli::ontology::Ecosystem(
            *universe,
            ecosystem_struct2,
            &universe->parent_of_ecosystems);

    // `Universe` member functions.
    ASSERT_EQ(universe->get_number_of_ecosystems(), 2);
    ASSERT_EQ(universe->get_active_scene(), nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_scene(), nullptr);
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 2);

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem2->get_childID(), 1);
    ASSERT_EQ(ecosystem2->get_type(), "yli::ontology::Ecosystem*");
    ASSERT_TRUE(ecosystem2->get_can_be_erased());
    ASSERT_EQ(&(ecosystem2->get_universe()), universe);
    ASSERT_EQ(ecosystem2->get_scene(), nullptr);
    ASSERT_EQ(ecosystem2->get_parent(), universe);
    ASSERT_EQ(ecosystem2->get_number_of_non_variable_children(), 0);

    delete ecosystem1;
    yli::ontology::EcosystemStruct ecosystem_struct3;
    yli::ontology::Ecosystem* const ecosystem3 = new yli::ontology::Ecosystem(
            *universe,
            ecosystem_struct3,
            &universe->parent_of_ecosystems);

    // `Universe` member functions.
    ASSERT_EQ(universe->get_number_of_ecosystems(), 2);
    ASSERT_EQ(universe->get_active_scene(), nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_scene(), nullptr);
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 2);

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem3->get_childID(), 0);
    ASSERT_EQ(ecosystem3->get_type(), "yli::ontology::Ecosystem*");
    ASSERT_TRUE(ecosystem3->get_can_be_erased());
    ASSERT_EQ(&(ecosystem3->get_universe()), universe);
    ASSERT_EQ(ecosystem3->get_scene(), nullptr);
    ASSERT_EQ(ecosystem3->get_parent(), universe);
    ASSERT_EQ(ecosystem3->get_number_of_non_variable_children(), 0);

    yli::ontology::EcosystemStruct ecosystem_struct4;
    yli::ontology::Ecosystem* const ecosystem4 = new yli::ontology::Ecosystem(
            *universe,
            ecosystem_struct4,
            &universe->parent_of_ecosystems);

    // `Universe` member functions.
    ASSERT_EQ(universe->get_number_of_ecosystems(), 3);
    ASSERT_EQ(universe->get_active_scene(), nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_scene(), nullptr);
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 3);

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem4->get_childID(), 2);
    ASSERT_EQ(ecosystem4->get_type(), "yli::ontology::Ecosystem*");
    ASSERT_TRUE(ecosystem4->get_can_be_erased());
    ASSERT_EQ(&(ecosystem4->get_universe()), universe);
    ASSERT_EQ(ecosystem4->get_scene(), nullptr);
    ASSERT_EQ(ecosystem4->get_parent(), universe);
    ASSERT_EQ(ecosystem4->get_number_of_non_variable_children(), 0);
}

TEST(ecosystem_must_be_given_a_global_name_appropriately, headless)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = new yli::ontology::Ecosystem(
            *universe,
            ecosystem_struct,
            &universe->parent_of_ecosystems);
    ASSERT_EQ(ecosystem->get_global_name(), "");
    ASSERT_EQ(ecosystem->get_local_name(), "");

    // `Ecosystem`s are children of the `Universe` and thus global name is local name, and vice versa.
    ecosystem->set_global_name("foo");
    ASSERT_EQ(ecosystem->get_global_name(), "foo");
    ASSERT_EQ(ecosystem->get_local_name(), "foo");
    ASSERT_TRUE(universe->has_child("foo"));
    ASSERT_EQ(universe->get_entity("foo"), ecosystem);
}

TEST(ecosystem_must_be_given_a_local_name_appropriately, headless)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = new yli::ontology::Ecosystem(
            *universe,
            ecosystem_struct,
            &universe->parent_of_ecosystems);
    ASSERT_EQ(ecosystem->get_global_name(), "");
    ASSERT_EQ(ecosystem->get_local_name(), "");

    // `Ecosystem`s are children of the `Universe` and thus global name is local name, and vice versa.
    ecosystem->set_local_name("foo");
    ASSERT_EQ(ecosystem->get_global_name(), "foo");
    ASSERT_EQ(ecosystem->get_local_name(), "foo");
    ASSERT_TRUE(universe->has_child("foo"));
    ASSERT_EQ(universe->get_entity("foo"), ecosystem);
}

TEST(ecosystem_must_be_given_a_global_name_appropriately_after_setting_a_global_name, headless)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = new yli::ontology::Ecosystem(
            *universe,
            ecosystem_struct,
            &universe->parent_of_ecosystems);
    ASSERT_EQ(ecosystem->get_global_name(), "");
    ASSERT_EQ(ecosystem->get_local_name(), "");

    // `Ecosystem`s are children of the `Universe` and thus global name is local name, and vice versa.
    ecosystem->set_global_name("foo");
    ecosystem->set_global_name("bar");
    ASSERT_EQ(ecosystem->get_global_name(), "bar");
    ASSERT_EQ(ecosystem->get_local_name(), "bar");
    ASSERT_FALSE(universe->has_child("foo"));
    ASSERT_TRUE(universe->has_child("bar"));
    ASSERT_EQ(universe->get_entity("foo"), nullptr);
    ASSERT_EQ(universe->get_entity("bar"), ecosystem);
}

TEST(ecosystem_must_be_given_a_local_name_appropriately_after_setting_a_local_name, headless)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = new yli::ontology::Ecosystem(
            *universe,
            ecosystem_struct,
            &universe->parent_of_ecosystems);
    ASSERT_EQ(ecosystem->get_global_name(), "");
    ASSERT_EQ(ecosystem->get_local_name(), "");

    // `Ecosystem`s are children of the `Universe` and thus global name is local name, and vice versa.
    ecosystem->set_local_name("foo");
    ecosystem->set_local_name("bar");
    ASSERT_EQ(ecosystem->get_global_name(), "bar");
    ASSERT_EQ(ecosystem->get_local_name(), "bar");
    ASSERT_FALSE(universe->has_child("foo"));
    ASSERT_TRUE(universe->has_child("bar"));
    ASSERT_EQ(universe->get_entity("foo"), nullptr);
    ASSERT_EQ(universe->get_entity("bar"), ecosystem);
}

TEST(ecosystem_must_be_given_a_global_name_appropriately_after_setting_a_local_name, headless)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = new yli::ontology::Ecosystem(
            *universe,
            ecosystem_struct,
            &universe->parent_of_ecosystems);
    ASSERT_EQ(ecosystem->get_global_name(), "");
    ASSERT_EQ(ecosystem->get_local_name(), "");

    // `Ecosystem`s are children of the `Universe` and thus global name is local name, and vice versa.
    ecosystem->set_local_name("foo");
    ecosystem->set_global_name("bar");
    ASSERT_EQ(ecosystem->get_global_name(), "bar");
    ASSERT_EQ(ecosystem->get_local_name(), "bar");
    ASSERT_FALSE(universe->has_child("foo"));
    ASSERT_TRUE(universe->has_child("bar"));
    ASSERT_EQ(universe->get_entity("foo"), nullptr);
    ASSERT_EQ(universe->get_entity("bar"), ecosystem);
}

TEST(ecosystem_must_be_given_a_local_name_appropriately_after_setting_a_global_name, headless)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = new yli::ontology::Ecosystem(
            *universe,
            ecosystem_struct,
            &universe->parent_of_ecosystems);
    ASSERT_EQ(ecosystem->get_global_name(), "");
    ASSERT_EQ(ecosystem->get_local_name(), "");

    // `Ecosystem`s are children of the `Universe` and thus global name is local name, and vice versa.
    ecosystem->set_global_name("foo");
    ecosystem->set_local_name("bar");
    ASSERT_EQ(ecosystem->get_global_name(), "bar");
    ASSERT_EQ(ecosystem->get_local_name(), "bar");
    ASSERT_FALSE(universe->has_child("foo"));
    ASSERT_TRUE(universe->has_child("bar"));
    ASSERT_EQ(universe->get_entity("foo"), nullptr);
    ASSERT_EQ(universe->get_entity("bar"), ecosystem);
}
