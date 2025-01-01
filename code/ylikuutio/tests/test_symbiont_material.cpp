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

#include "gtest/gtest.h"
#include "code/mock/mock_application.hpp"
#include "code/ylikuutio/data/datatype.hpp"
#include "code/ylikuutio/ontology/symbiosis.hpp"
#include "code/ylikuutio/ontology/symbiont_material.hpp"
#include "code/ylikuutio/ontology/request.hpp"
#include "code/ylikuutio/ontology/symbiont_material_struct.hpp"

// Include standard headers
#include <cstddef> // uintptr_t
#include <limits>  // std::numeric_limits

namespace yli::ontology
{
    class Ecosystem;
    class Scene;
    class Pipeline;
}

TEST(symbiont_material_must_be_initialized_appropriately, symbiosis_provided_as_valid_pointer)
{
    mock::MockApplication application;
    yli::ontology::SymbiosisStruct symbiosis_struct {
            yli::ontology::Request<yli::ontology::Scene>(nullptr),
            yli::ontology::Request<yli::ontology::Pipeline>(nullptr) };
    yli::ontology::Symbiosis* const symbiosis = application.get_generic_entity_factory().create_symbiosis(
            symbiosis_struct);
    yli::ontology::SymbiontMaterialStruct symbiont_material_struct { yli::ontology::Request(symbiosis) };
    yli::ontology::SymbiontMaterial* const symbiont_material = application.get_generic_entity_factory().create_symbiont_material(
            symbiont_material_struct);
    ASSERT_NE(symbiont_material, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(symbiont_material) % alignof(yli::ontology::SymbiontMaterial), 0);

    for (int datatype = 0; datatype < yli::data::Datatype::MAX_VALUE; datatype++)
    {
        const yli::ontology::GenericParentModule* const generic_parent_module = symbiont_material->get_generic_parent_module(datatype);

        if (datatype == yli::data::Datatype::SYMBIONT_SPECIES)
        {
            ASSERT_NE(generic_parent_module, nullptr);
        }
        else
        {
            ASSERT_EQ(generic_parent_module, nullptr);
        }
    }

    // `Entity` member functions of `Symbiosis`.
    ASSERT_EQ(symbiosis->get_number_of_non_variable_children(), 1);

    // `Entity` member functions.
    ASSERT_EQ(symbiont_material->get_childID(), 0);
    ASSERT_EQ(symbiont_material->get_type(), "yli::ontology::SymbiontMaterial*");
    ASSERT_FALSE(symbiont_material->get_can_be_erased());
    ASSERT_EQ(symbiont_material->get_scene(), symbiosis->get_scene());
    ASSERT_EQ(symbiont_material->get_parent(), symbiosis);
    ASSERT_EQ(symbiont_material->get_number_of_non_variable_children(), 0);
}

TEST(symbiont_material_must_be_initialized_appropriately, symbiosis_provided_as_nullptr)
{
    mock::MockApplication application;
    yli::ontology::SymbiontMaterialStruct symbiont_material_struct { yli::ontology::Request<yli::ontology::Symbiosis>(nullptr) };
    yli::ontology::SymbiontMaterial* const symbiont_material = application.get_generic_entity_factory().create_symbiont_material(
            symbiont_material_struct);
    ASSERT_NE(symbiont_material, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(symbiont_material) % alignof(yli::ontology::SymbiontMaterial), 0);

    // `Entity` member functions.
    ASSERT_EQ(symbiont_material->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(symbiont_material->get_type(), "yli::ontology::SymbiontMaterial*");
    ASSERT_FALSE(symbiont_material->get_can_be_erased());
    ASSERT_EQ(symbiont_material->get_parent(), nullptr);
    ASSERT_EQ(symbiont_material->get_number_of_non_variable_children(), 0);
}

TEST(symbiont_material_must_be_initialized_appropriately, symbiosis_provided_as_valid_global_name)
{
    mock::MockApplication application;
    yli::ontology::SymbiosisStruct symbiosis_struct {
            yli::ontology::Request<yli::ontology::Ecosystem>(nullptr),
            yli::ontology::Request<yli::ontology::Pipeline>(nullptr) };
    symbiosis_struct.global_name = "foo";
    yli::ontology::Symbiosis* const symbiosis = application.get_generic_entity_factory().create_symbiosis(
            symbiosis_struct);
    yli::ontology::SymbiontMaterialStruct symbiont_material_struct { yli::ontology::Request<yli::ontology::Symbiosis>("foo") };
    yli::ontology::SymbiontMaterial* const symbiont_material = application.get_generic_entity_factory().create_symbiont_material(
            symbiont_material_struct);
    ASSERT_NE(symbiont_material, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(symbiont_material) % alignof(yli::ontology::SymbiontMaterial), 0);

    // `Entity` member functions of `Symbiosis`.
    ASSERT_EQ(symbiosis->get_number_of_non_variable_children(), 1);

    // `Entity` member functions.
    ASSERT_EQ(symbiont_material->get_childID(), 0);
    ASSERT_EQ(symbiont_material->get_type(), "yli::ontology::SymbiontMaterial*");
    ASSERT_FALSE(symbiont_material->get_can_be_erased());
    ASSERT_EQ(symbiont_material->get_scene(), symbiosis->get_scene());
    ASSERT_EQ(symbiont_material->get_parent(), symbiosis);
    ASSERT_EQ(symbiont_material->get_number_of_non_variable_children(), 0);
}

TEST(symbiont_material_must_be_initialized_appropriately, symbiosis_provided_as_invalid_global_name)
{
    mock::MockApplication application;
    yli::ontology::SymbiosisStruct symbiosis_struct {
            yli::ontology::Request<yli::ontology::Ecosystem>(nullptr),
            yli::ontology::Request<yli::ontology::Pipeline>(nullptr) };
    symbiosis_struct.global_name = "foo";
    yli::ontology::Symbiosis* const symbiosis = application.get_generic_entity_factory().create_symbiosis(
            symbiosis_struct);
    yli::ontology::SymbiontMaterialStruct symbiont_material_struct { yli::ontology::Request<yli::ontology::Symbiosis>("bar") };
    yli::ontology::SymbiontMaterial* const symbiont_material = application.get_generic_entity_factory().create_symbiont_material(
            symbiont_material_struct);
    ASSERT_NE(symbiont_material, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(symbiont_material) % alignof(yli::ontology::SymbiontMaterial), 0);

    // `Entity` member functions of `Symbiosis`.
    ASSERT_EQ(symbiosis->get_number_of_non_variable_children(), 0);

    // `Entity` member functions.
    ASSERT_EQ(symbiont_material->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(symbiont_material->get_type(), "yli::ontology::SymbiontMaterial*");
    ASSERT_FALSE(symbiont_material->get_can_be_erased());
    ASSERT_EQ(symbiont_material->get_parent(), nullptr);
    ASSERT_EQ(symbiont_material->get_number_of_non_variable_children(), 0);
}
