// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2026 Antti Nuortimo.
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
#include "code/ylikuutio/ontology/symbiont_species.hpp"
#include "code/ylikuutio/ontology/request.hpp"
#include "code/ylikuutio/ontology/symbiont_species_struct.hpp"

// Include standard headers
#include <cstddef> // uintptr_t
#include <limits>  // std::numeric_limits

namespace yli::ontology
{
    class Ecosystem;
    class Pipeline;
    class Symbiosis;
    class Biont;
}

TEST(symbiont_species_must_be_initialized_appropriately, symbiont_material_provided_as_valid_pointer)
{
    mock::MockApplication application;
    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    yli::ontology::PipelineStruct pipeline_struct { yli::ontology::Request(ecosystem) };
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::SymbiosisStruct symbiosis_struct {
        yli::ontology::Request(ecosystem),
        yli::ontology::Request(pipeline) };
    yli::ontology::Symbiosis* const symbiosis = application.get_generic_entity_factory().create_symbiosis(
            symbiosis_struct);

    yli::ontology::SymbiontMaterialStruct symbiont_material_struct { yli::ontology::Request(symbiosis) };
    yli::ontology::SymbiontMaterial* const symbiont_material = application.get_generic_entity_factory().create_symbiont_material(
            symbiont_material_struct);
    yli::ontology::SymbiontSpeciesStruct symbiont_species_struct { yli::ontology::Request(symbiont_material) };
    yli::ontology::SymbiontSpecies* const symbiont_species = application.get_generic_entity_factory().create_symbiont_species(
            symbiont_species_struct);
    ASSERT_NE(symbiont_species, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(symbiont_species) % alignof(yli::ontology::SymbiontSpecies), 0);

    ASSERT_NE(symbiont_species->get_generic_master_module<yli::ontology::Biont>(), nullptr);

    // `Entity` member functions of `SymbiontMaterial`.
    ASSERT_EQ(symbiont_material->get_number_of_non_variable_children(), 1);

    // `Entity` member functions.
    ASSERT_EQ(symbiont_species->get_childID(), 0);
    ASSERT_EQ(symbiont_species->get_type(), "yli::ontology::SymbiontSpecies*");
    ASSERT_FALSE(symbiont_species->get_can_be_erased());
    ASSERT_EQ(symbiont_species->get_parent(), symbiont_material);
    ASSERT_EQ(symbiont_species->get_number_of_non_variable_children(), 0);
}

TEST(symbiont_species_must_be_initialized_appropriately, symbiont_material_provided_as_nullptr)
{
    mock::MockApplication application;
    yli::ontology::SymbiontSpeciesStruct symbiont_species_struct { yli::ontology::Request<yli::ontology::SymbiontMaterial>(nullptr) };
    yli::ontology::SymbiontSpecies* const symbiont_species = application.get_generic_entity_factory().create_symbiont_species(
            symbiont_species_struct);
    ASSERT_NE(symbiont_species, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(symbiont_species) % alignof(yli::ontology::SymbiontSpecies), 0);

    // `Entity` member functions.
    ASSERT_EQ(symbiont_species->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(symbiont_species->get_type(), "yli::ontology::SymbiontSpecies*");
    ASSERT_FALSE(symbiont_species->get_can_be_erased());
    ASSERT_EQ(symbiont_species->get_parent(), nullptr);
    ASSERT_EQ(symbiont_species->get_number_of_non_variable_children(), 0);
}
