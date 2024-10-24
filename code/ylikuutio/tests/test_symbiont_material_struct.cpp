// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
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
#include "code/ylikuutio/ontology/ecosystem.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/pipeline.hpp"
#include "code/ylikuutio/ontology/symbiosis.hpp"
#include "code/ylikuutio/ontology/symbiont_material_struct.hpp"

TEST(symbiont_material_struct_must_be_initialized_appropriately, symbiont_material_struct_symbiosis_parent_nullptr_pipeline)
{
    mock::MockApplication application;
    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    yli::ontology::SymbiosisStruct symbiosis_struct(ecosystem, nullptr);
    yli::ontology::Symbiosis* const symbiosis = application.get_generic_entity_factory().create_symbiosis(
            symbiosis_struct);

    const yli::ontology::SymbiontMaterialStruct test_symbiont_material_struct(symbiosis, nullptr);

    ASSERT_EQ(test_symbiont_material_struct.symbiosis_parent, symbiosis);

    ASSERT_EQ(test_symbiont_material_struct.pipeline_master, nullptr);
}

TEST(symbiont_material_struct_must_be_initialized_appropriately, symbiont_material_struct_symbiosis_parent_valid_pipeline)
{
    mock::MockApplication application;
    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    yli::ontology::PipelineStruct pipeline_struct(ecosystem);
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::SymbiosisStruct symbiosis_struct(ecosystem, pipeline);
    yli::ontology::Symbiosis* const symbiosis = application.get_generic_entity_factory().create_symbiosis(
            symbiosis_struct);

    const yli::ontology::SymbiontMaterialStruct test_symbiont_material_struct(symbiosis, pipeline);

    ASSERT_EQ(test_symbiont_material_struct.symbiosis_parent, symbiosis);

    ASSERT_EQ(test_symbiont_material_struct.pipeline_master, pipeline);
}
