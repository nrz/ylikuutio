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
#include "code/mock/mock_application.hpp"
#include "code/ylikuutio/data/datatype.hpp"
#include "code/ylikuutio/ontology/registry.hpp"
#include "code/ylikuutio/ontology/generic_parent_module.hpp"
#include "code/ylikuutio/ontology/generic_master_module.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/entity_factory.hpp"

// Include standard headers
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

TEST(uninitialized_registry_must_not_have_names, registry)
{
    const yli::ontology::Registry registry;
    ASSERT_FALSE(registry.is_name(""));
    ASSERT_FALSE(registry.is_name("foo"));
}

TEST(uninitialized_registry_must_have_0_completions, registry)
{
    const yli::ontology::Registry registry;
    ASSERT_EQ(registry.get_number_of_completions(""), 0);
    ASSERT_EQ(registry.get_number_of_completions("foo"), 0);
}

TEST(uninitialized_registry_must_complete_by_returning_the_input, registry)
{
    const yli::ontology::Registry registry;
    ASSERT_EQ(registry.complete(""), "");
    ASSERT_EQ(registry.complete("foo"), "foo");
}

TEST(uninitialized_registry_must_return_empty_completions_vector, registry)
{
    const yli::ontology::Registry registry;
    const std::vector<std::string> empty_vector;
    ASSERT_EQ(registry.get_completions(""), empty_vector);
    ASSERT_EQ(registry.get_completions("foo"), empty_vector);
}

TEST(uninitialized_registry_must_not_have_indexables, registry)
{
    const yli::ontology::Registry registry;
    ASSERT_FALSE(registry.is_indexable(""));
    ASSERT_FALSE(registry.is_indexable("foo"));
}

TEST(uninitialized_registry_must_not_have_entities, registry)
{
    const yli::ontology::Registry registry;
    ASSERT_FALSE(registry.is_entity(""));
    ASSERT_FALSE(registry.is_entity("foo"));
}

TEST(uninitialized_registry_must_return_an_empty_string_as_entity_names, registry)
{
    const yli::ontology::Registry registry;
    ASSERT_EQ(registry.get_entity_names(), "");
}

TEST(uninitialized_registry_must_return_an_empty_indexable_map, registry)
{
    const yli::ontology::Registry registry;
    const std::unordered_map<std::string, yli::ontology::Indexable*>& indexable_map = registry.get_indexable_map();
    ASSERT_TRUE(indexable_map.empty());
    ASSERT_EQ(indexable_map.size(), 0);
}

TEST(uninitialized_registry_must_return_an_empty_entity_map, registry)
{
    const yli::ontology::Registry registry;
    const std::unordered_map<std::string, yli::ontology::Entity*>& entity_map = registry.get_entity_map();
    ASSERT_TRUE(entity_map.empty());
    ASSERT_EQ(entity_map.size(), 0);
}

TEST(generic_parent_module_must_bind_to_registry_appropriately, generic_parent_module_foo)
{
    mock::MockApplication application;

    yli::ontology::Registry registry;
    yli::ontology::GenericParentModule generic_parent_module(application.get_universe(), &registry, application.get_memory_allocator(yli::data::Datatype::UNIVERSE), "foo");

    ASSERT_TRUE(registry.is_name("foo"));
    ASSERT_FALSE(registry.is_name("bar"));

    ASSERT_TRUE(registry.is_indexable("foo"));
    ASSERT_FALSE(registry.is_indexable("bar"));

    ASSERT_FALSE(registry.is_entity("foo"));
    ASSERT_FALSE(registry.is_entity("bar"));

    ASSERT_EQ(registry.get_number_of_completions(""), 1);
    ASSERT_EQ(registry.get_number_of_completions("f"), 1);
    ASSERT_EQ(registry.get_number_of_completions("fo"), 1);
    ASSERT_EQ(registry.get_number_of_completions("foo"), 1);
    ASSERT_EQ(registry.get_number_of_completions("a"), 0);
    ASSERT_EQ(registry.get_number_of_completions("fooz"), 0);

    ASSERT_EQ(registry.complete(""), "foo");
    ASSERT_EQ(registry.complete("f"), "foo");
    ASSERT_EQ(registry.complete("fo"), "foo");
    ASSERT_EQ(registry.complete("foo"), "foo");
    ASSERT_EQ(registry.complete("a"), "a");
    ASSERT_EQ(registry.complete("fooz"), "fooz");

    const std::vector<std::string> expected_completions_vector { "foo" };
    const std::vector<std::string> empty_completions_vector;
    ASSERT_EQ(registry.get_completions(""), expected_completions_vector);
    ASSERT_EQ(registry.get_completions("f"), expected_completions_vector);
    ASSERT_EQ(registry.get_completions("fo"), expected_completions_vector);
    ASSERT_EQ(registry.get_completions("foo"), expected_completions_vector);
    ASSERT_EQ(registry.get_completions("a"), empty_completions_vector);
    ASSERT_EQ(registry.get_completions("fooz"), empty_completions_vector);
}

TEST(generic_master_module_must_bind_to_registry_appropriately, generic_master_module_foo)
{
    yli::ontology::Registry registry;
    yli::ontology::GenericMasterModule generic_master_module(nullptr, &registry, "foo");

    ASSERT_TRUE(registry.is_name("foo"));
    ASSERT_FALSE(registry.is_name("bar"));

    ASSERT_TRUE(registry.is_indexable("foo"));
    ASSERT_FALSE(registry.is_indexable("bar"));

    ASSERT_FALSE(registry.is_entity("foo"));
    ASSERT_FALSE(registry.is_entity("bar"));

    ASSERT_EQ(registry.get_number_of_completions(""), 1);
    ASSERT_EQ(registry.get_number_of_completions("f"), 1);
    ASSERT_EQ(registry.get_number_of_completions("fo"), 1);
    ASSERT_EQ(registry.get_number_of_completions("foo"), 1);
    ASSERT_EQ(registry.get_number_of_completions("a"), 0);
    ASSERT_EQ(registry.get_number_of_completions("fooz"), 0);

    ASSERT_EQ(registry.complete(""), "foo");
    ASSERT_EQ(registry.complete("f"), "foo");
    ASSERT_EQ(registry.complete("fo"), "foo");
    ASSERT_EQ(registry.complete("foo"), "foo");
    ASSERT_EQ(registry.complete("a"), "a");
    ASSERT_EQ(registry.complete("fooz"), "fooz");

    const std::vector<std::string> expected_completions_vector { "foo" };
    const std::vector<std::string> empty_completions_vector;
    ASSERT_EQ(registry.get_completions(""), expected_completions_vector);
    ASSERT_EQ(registry.get_completions("f"), expected_completions_vector);
    ASSERT_EQ(registry.get_completions("fo"), expected_completions_vector);
    ASSERT_EQ(registry.get_completions("foo"), expected_completions_vector);
    ASSERT_EQ(registry.get_completions("a"), empty_completions_vector);
    ASSERT_EQ(registry.get_completions("fooz"), empty_completions_vector);
}

TEST(two_generic_parent_modules_must_bind_to_registry_appropriately, generic_parent_modules_foo1_foo2)
{
    mock::MockApplication application;

    yli::ontology::Registry registry;
    yli::ontology::GenericParentModule generic_parent_module_1(application.get_universe(), &registry, application.get_memory_allocator(yli::data::Datatype::UNIVERSE), "foo1");
    yli::ontology::GenericParentModule generic_parent_module_2(application.get_universe(), &registry, application.get_memory_allocator(yli::data::Datatype::UNIVERSE), "foo2");

    ASSERT_FALSE(registry.is_name("foo"));
    ASSERT_TRUE(registry.is_name("foo1"));
    ASSERT_TRUE(registry.is_name("foo2"));
    ASSERT_FALSE(registry.is_name("bar"));

    ASSERT_FALSE(registry.is_indexable("foo"));
    ASSERT_TRUE(registry.is_indexable("foo1"));
    ASSERT_TRUE(registry.is_indexable("foo2"));
    ASSERT_FALSE(registry.is_indexable("bar"));

    ASSERT_FALSE(registry.is_entity("foo"));
    ASSERT_FALSE(registry.is_entity("foo1"));
    ASSERT_FALSE(registry.is_entity("foo2"));
    ASSERT_FALSE(registry.is_entity("bar"));

    ASSERT_EQ(registry.get_number_of_completions(""), 2);
    ASSERT_EQ(registry.get_number_of_completions("f"), 2);
    ASSERT_EQ(registry.get_number_of_completions("fo"), 2);
    ASSERT_EQ(registry.get_number_of_completions("foo"), 2);
    ASSERT_EQ(registry.get_number_of_completions("foo1"), 1);
    ASSERT_EQ(registry.get_number_of_completions("foo2"), 1);
    ASSERT_EQ(registry.get_number_of_completions("a"), 0);
    ASSERT_EQ(registry.get_number_of_completions("fooz"), 0);

    ASSERT_EQ(registry.complete(""), "foo");
    ASSERT_EQ(registry.complete("f"), "foo");
    ASSERT_EQ(registry.complete("fo"), "foo");
    ASSERT_EQ(registry.complete("foo"), "foo");
    ASSERT_EQ(registry.complete("foo1"), "foo1");
    ASSERT_EQ(registry.complete("foo2"), "foo2");
    ASSERT_EQ(registry.complete("a"), "a");
    ASSERT_EQ(registry.complete("fooz"), "fooz");

    const std::vector<std::string> expected_completions_vector_foo1_foo2 { "foo1", "foo2" };
    ASSERT_EQ(registry.get_completions(""), expected_completions_vector_foo1_foo2);
    ASSERT_EQ(registry.get_completions("f"), expected_completions_vector_foo1_foo2);
    ASSERT_EQ(registry.get_completions("fo"), expected_completions_vector_foo1_foo2);
    ASSERT_EQ(registry.get_completions("foo"), expected_completions_vector_foo1_foo2);

    const std::vector<std::string> expected_completions_vector_foo1 { "foo1" };
    ASSERT_EQ(registry.get_completions("foo1"), expected_completions_vector_foo1);

    const std::vector<std::string> expected_completions_vector_foo2 { "foo2" };
    ASSERT_EQ(registry.get_completions("foo2"), expected_completions_vector_foo2);

    const std::vector<std::string> empty_completions_vector;
    ASSERT_EQ(registry.get_completions("a"), empty_completions_vector);
    ASSERT_EQ(registry.get_completions("fooz"), empty_completions_vector);
}

TEST(two_generic_parent_modules_must_bind_to_registry_appropriately, generic_parent_modules_foo_foo1)
{
    mock::MockApplication application;

    yli::ontology::Registry registry;
    yli::ontology::GenericParentModule generic_parent_module_1(application.get_universe(), &registry, application.get_memory_allocator(yli::data::Datatype::UNIVERSE), "foo");
    yli::ontology::GenericParentModule generic_parent_module_2(application.get_universe(), &registry, application.get_memory_allocator(yli::data::Datatype::UNIVERSE), "foo1");

    ASSERT_TRUE(registry.is_name("foo"));
    ASSERT_TRUE(registry.is_name("foo1"));
    ASSERT_FALSE(registry.is_name("foo2"));
    ASSERT_FALSE(registry.is_name("bar"));

    ASSERT_TRUE(registry.is_indexable("foo"));
    ASSERT_TRUE(registry.is_indexable("foo1"));
    ASSERT_FALSE(registry.is_indexable("foo2"));
    ASSERT_FALSE(registry.is_indexable("bar"));

    ASSERT_FALSE(registry.is_entity("foo"));
    ASSERT_FALSE(registry.is_entity("foo1"));
    ASSERT_FALSE(registry.is_entity("foo2"));
    ASSERT_FALSE(registry.is_entity("bar"));

    ASSERT_EQ(registry.get_number_of_completions(""), 2);
    ASSERT_EQ(registry.get_number_of_completions("f"), 2);
    ASSERT_EQ(registry.get_number_of_completions("fo"), 2);
    ASSERT_EQ(registry.get_number_of_completions("foo"), 2);
    ASSERT_EQ(registry.get_number_of_completions("foo1"), 1);
    ASSERT_EQ(registry.get_number_of_completions("foo2"), 0);
    ASSERT_EQ(registry.get_number_of_completions("a"), 0);
    ASSERT_EQ(registry.get_number_of_completions("fooz"), 0);

    ASSERT_EQ(registry.complete(""), "foo");
    ASSERT_EQ(registry.complete("f"), "foo");
    ASSERT_EQ(registry.complete("fo"), "foo");
    ASSERT_EQ(registry.complete("foo"), "foo");
    ASSERT_EQ(registry.complete("foo1"), "foo1");
    ASSERT_EQ(registry.complete("foo2"), "foo2");
    ASSERT_EQ(registry.complete("a"), "a");
    ASSERT_EQ(registry.complete("fooz"), "fooz");

    const std::vector<std::string> expected_completions_vector_foo1_foo2 { "foo", "foo1" };
    ASSERT_EQ(registry.get_completions(""), expected_completions_vector_foo1_foo2);
    ASSERT_EQ(registry.get_completions("f"), expected_completions_vector_foo1_foo2);
    ASSERT_EQ(registry.get_completions("fo"), expected_completions_vector_foo1_foo2);
    ASSERT_EQ(registry.get_completions("foo"), expected_completions_vector_foo1_foo2);

    const std::vector<std::string> expected_completions_vector_foo1 { "foo1" };
    ASSERT_EQ(registry.get_completions("foo1"), expected_completions_vector_foo1);

    const std::vector<std::string> empty_completions_vector;
    ASSERT_EQ(registry.get_completions("a"), empty_completions_vector);
    ASSERT_EQ(registry.get_completions("foo2"), empty_completions_vector);
    ASSERT_EQ(registry.get_completions("fooz"), empty_completions_vector);
}

TEST(two_generic_parent_modules_must_bind_to_registry_appropriately, generic_parent_modules_ab_ac)
{
    mock::MockApplication application;

    yli::ontology::Registry registry;
    yli::ontology::GenericParentModule generic_parent_module_1(application.get_universe(), &registry, application.get_memory_allocator(yli::data::Datatype::UNIVERSE), "ab");
    yli::ontology::GenericParentModule generic_parent_module_2(application.get_universe(), &registry, application.get_memory_allocator(yli::data::Datatype::UNIVERSE), "ac");

    ASSERT_FALSE(registry.is_name("foo"));
    ASSERT_FALSE(registry.is_name("a"));
    ASSERT_TRUE(registry.is_name("ab"));
    ASSERT_TRUE(registry.is_name("ac"));

    ASSERT_FALSE(registry.is_indexable("foo"));
    ASSERT_FALSE(registry.is_indexable("a"));
    ASSERT_TRUE(registry.is_indexable("ab"));
    ASSERT_TRUE(registry.is_indexable("ac"));

    ASSERT_FALSE(registry.is_entity("foo"));
    ASSERT_FALSE(registry.is_entity("a"));
    ASSERT_FALSE(registry.is_entity("ab"));
    ASSERT_FALSE(registry.is_entity("ac"));

    ASSERT_EQ(registry.get_number_of_completions(""), 2);
    ASSERT_EQ(registry.get_number_of_completions("a"), 2);
    ASSERT_EQ(registry.get_number_of_completions("aa"), 0);
    ASSERT_EQ(registry.get_number_of_completions("ab"), 1);
    ASSERT_EQ(registry.get_number_of_completions("ac"), 1);
    ASSERT_EQ(registry.get_number_of_completions("ad"), 0);
    ASSERT_EQ(registry.get_number_of_completions("foo"), 0);

    ASSERT_EQ(registry.complete(""), "a");
    ASSERT_EQ(registry.complete("a"), "a");
    ASSERT_EQ(registry.complete("aa"), "aa");
    ASSERT_EQ(registry.complete("ab"), "ab");
    ASSERT_EQ(registry.complete("ac"), "ac");
    ASSERT_EQ(registry.complete("ad"), "ad");
    ASSERT_EQ(registry.complete("foo"), "foo");

    const std::vector<std::string> expected_completions_vector_ab_ac { "ab", "ac" };
    ASSERT_EQ(registry.get_completions(""), expected_completions_vector_ab_ac);
    ASSERT_EQ(registry.get_completions("a"), expected_completions_vector_ab_ac);

    const std::vector<std::string> expected_completions_vector_ab { "ab" };
    ASSERT_EQ(registry.get_completions("ab"), expected_completions_vector_ab);

    const std::vector<std::string> expected_completions_vector_ac { "ac" };
    ASSERT_EQ(registry.get_completions("ac"), expected_completions_vector_ac);

    const std::vector<std::string> empty_completions_vector;
    ASSERT_EQ(registry.get_completions("foo"), empty_completions_vector);
}

TEST(two_generic_parent_modules_must_bind_to_registry_appropriately, generic_parent_modules_aba_aca)
{
    mock::MockApplication application;

    yli::ontology::Registry registry;
    yli::ontology::GenericParentModule generic_parent_module_1(application.get_universe(), &registry, application.get_memory_allocator(yli::data::Datatype::UNIVERSE), "aba");
    yli::ontology::GenericParentModule generic_parent_module_2(application.get_universe(), &registry, application.get_memory_allocator(yli::data::Datatype::UNIVERSE), "aca");

    ASSERT_FALSE(registry.is_name("foo"));
    ASSERT_FALSE(registry.is_name("a"));
    ASSERT_TRUE(registry.is_name("aba"));
    ASSERT_TRUE(registry.is_name("aca"));

    ASSERT_FALSE(registry.is_indexable("foo"));
    ASSERT_FALSE(registry.is_indexable("a"));
    ASSERT_TRUE(registry.is_indexable("aba"));
    ASSERT_TRUE(registry.is_indexable("aca"));

    ASSERT_FALSE(registry.is_entity("foo"));
    ASSERT_FALSE(registry.is_entity("a"));
    ASSERT_FALSE(registry.is_entity("aba"));
    ASSERT_FALSE(registry.is_entity("aca"));

    ASSERT_EQ(registry.get_number_of_completions(""), 2);
    ASSERT_EQ(registry.get_number_of_completions("a"), 2);
    ASSERT_EQ(registry.get_number_of_completions("aa"), 0);
    ASSERT_EQ(registry.get_number_of_completions("ab"), 1);
    ASSERT_EQ(registry.get_number_of_completions("ac"), 1);
    ASSERT_EQ(registry.get_number_of_completions("aba"), 1);
    ASSERT_EQ(registry.get_number_of_completions("aca"), 1);
    ASSERT_EQ(registry.get_number_of_completions("ad"), 0);
    ASSERT_EQ(registry.get_number_of_completions("foo"), 0);

    ASSERT_EQ(registry.complete(""), "a");
    ASSERT_EQ(registry.complete("a"), "a");
    ASSERT_EQ(registry.complete("aa"), "aa");
    ASSERT_EQ(registry.complete("aba"), "aba");
    ASSERT_EQ(registry.complete("aca"), "aca");
    ASSERT_EQ(registry.complete("ad"), "ad");
    ASSERT_EQ(registry.complete("foo"), "foo");

    const std::vector<std::string> expected_completions_vector_aba_aca { "aba", "aca" };
    ASSERT_EQ(registry.get_completions(""), expected_completions_vector_aba_aca);
    ASSERT_EQ(registry.get_completions("a"), expected_completions_vector_aba_aca);

    const std::vector<std::string> expected_completions_vector_aba { "aba" };
    ASSERT_EQ(registry.get_completions("ab"), expected_completions_vector_aba);
    ASSERT_EQ(registry.get_completions("aba"), expected_completions_vector_aba);

    const std::vector<std::string> expected_completions_vector_aca { "aca" };
    ASSERT_EQ(registry.get_completions("ac"), expected_completions_vector_aca);
    ASSERT_EQ(registry.get_completions("aca"), expected_completions_vector_aca);

    const std::vector<std::string> empty_completions_vector;
    ASSERT_EQ(registry.get_completions("foo"), empty_completions_vector);
}
