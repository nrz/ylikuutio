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

#include "gtest/gtest.h"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/ecosystem.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/shader.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/vector_font.hpp"
#include "code/ylikuutio/ontology/text_3d.hpp"
#include "code/ylikuutio/ontology/universe_struct.hpp"
#include "code/ylikuutio/ontology/ecosystem_struct.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/shader_struct.hpp"
#include "code/ylikuutio/ontology/material_struct.hpp"
#include "code/ylikuutio/ontology/vector_font_struct.hpp"
#include "code/ylikuutio/ontology/text_3d_struct.hpp"
#include "code/ylikuutio/render/graphics_api_backend.hpp"

TEST(text_3d_must_be_initialized_and_must_bind_to_material_appropriately, headless_shader_and_material_are_children_of_an_ecosystem)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = new yli::ontology::Ecosystem(
            *universe,
            ecosystem_struct,
            &universe->parent_of_ecosystems);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = ecosystem;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(*universe, shader_struct, &ecosystem->parent_of_shaders);

    yli::ontology::MaterialStruct material_struct;
    material_struct.parent = ecosystem;
    material_struct.shader = shader;
    yli::ontology::Material* const material = new yli::ontology::Material(
            *universe,
            material_struct,
            &ecosystem->parent_of_materials, &shader->master_of_materials);

    yli::ontology::VectorFontStruct vector_font_struct;
    vector_font_struct.parent = material;
    yli::ontology::VectorFont* const vector_font = new yli::ontology::VectorFont(*universe, vector_font_struct);

    yli::ontology::Text3DStruct text_3d_struct;
    text_3d_struct.parent = vector_font;
    yli::ontology::Text3D* text_3d = new yli::ontology::Text3D(
            *universe,
            text_3d_struct,
            &vector_font->parent_of_text_3ds,
            nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 1);  // `ecosystem`.

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 2); // `shader`, `material`.

    // `Entity` member functions of `Shader`.
    ASSERT_EQ(shader->get_number_of_non_variable_children(), 0);

    // `Entity` member functions of `Material`.
    ASSERT_EQ(material->get_number_of_non_variable_children(), 1); // `vector_font`.

    // `Entity` member functions of `VectorFont`.
    ASSERT_EQ(vector_font->get_number_of_non_variable_children(), 1); // `text_3d`.

    // `Entity` member functions of `Text3D`.
    ASSERT_EQ(text_3d->get_childID(), 0);
    ASSERT_EQ(text_3d->get_type(), "yli::ontology::Text3D*");
    ASSERT_TRUE(text_3d->get_can_be_erased());
    ASSERT_EQ(&(text_3d->get_universe()), universe);
    ASSERT_EQ(text_3d->get_scene(), nullptr);
    ASSERT_EQ(text_3d->get_parent(), vector_font);
    ASSERT_EQ(text_3d->get_number_of_non_variable_children(), 0);
}

TEST(text_3d_must_be_initialized_and_must_bind_to_material_appropriately, headless_shader_and_material_are_children_of_a_scene)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(*universe, shader_struct, &scene->parent_of_shaders);

    yli::ontology::MaterialStruct material_struct;
    material_struct.parent = scene;
    material_struct.shader = shader;
    yli::ontology::Material* const material = new yli::ontology::Material(
            *universe,
            material_struct,
            &scene->parent_of_materials, &shader->master_of_materials);

    yli::ontology::VectorFontStruct vector_font_struct;
    vector_font_struct.parent = material;
    yli::ontology::VectorFont* const vector_font = new yli::ontology::VectorFont(*universe, vector_font_struct);

    yli::ontology::Text3DStruct text_3d_struct;
    text_3d_struct.parent = vector_font;
    yli::ontology::Text3D* text_3d = new yli::ontology::Text3D(
            *universe,
            text_3d_struct,
            &vector_font->parent_of_text_3ds,
            nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 1); // `scene`.

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 3); // Default `Camera`, `shader`, `material`.

    // `Entity` member functions of `Shader`.
    ASSERT_EQ(shader->get_number_of_non_variable_children(), 0);

    // `Entity` member functions of `Material`.
    ASSERT_EQ(material->get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `VectorFont`.
    ASSERT_EQ(vector_font->get_number_of_non_variable_children(), 1); // `text_3d`.

    // `Entity` member functions of `Text3D`.
    ASSERT_EQ(text_3d->get_childID(), 0);
    ASSERT_EQ(text_3d->get_type(), "yli::ontology::Text3D*");
    ASSERT_TRUE(text_3d->get_can_be_erased());
    ASSERT_EQ(&(text_3d->get_universe()), universe);
    ASSERT_EQ(text_3d->get_scene(), scene);
    ASSERT_EQ(text_3d->get_parent(), vector_font);
    ASSERT_EQ(text_3d->get_number_of_non_variable_children(), 0);
}