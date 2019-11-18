// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2019 Antti Nuortimo.
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

#ifndef __ENTITY_FACTORY_HPP_INCLUDED
#define __ENTITY_FACTORY_HPP_INCLUDED

#include "scene_struct.hpp"
#include "shader_struct.hpp"
#include "material_struct.hpp"
#include "species_struct.hpp"
#include "object_struct.hpp"
#include "symbiosis_struct.hpp"
#include "holobiont_struct.hpp"
#include "vector_font_struct.hpp"
#include "text_struct.hpp"
#include "text3D_struct.hpp"
#include "camera_struct.hpp"
#include "compute_task_struct.hpp"

// Include standard headers
#include <cstddef>   // std::size_t
#include <memory>    // std::make_shared, std::shared_ptr
#include <string>    // std::string

namespace yli
{
    namespace ontology
    {
        class Entity;
        class Universe;
        class World;
        class Scene;
        class Shader;
        class Material;
        class Species;
        class Object;
        class VectorFont;
        class Text3D;
        class Font2D;
        class Console;
        class ComputeTask;

        class EntityFactory
        {
            public:
                // constructor.
                EntityFactory(yli::ontology::Universe* const universe);

                EntityFactory(const EntityFactory&) = delete;            // Delete copy constructor.
                EntityFactory &operator=(const EntityFactory&) = delete; // Delete copy assignment.

                // destructor.
                ~EntityFactory();

                yli::ontology::Universe* get_universe() const;

                yli::ontology::Entity* create_World() const;
                yli::ontology::Entity* create_Scene(const yli::ontology::SceneStruct& scene_struct) const;
                yli::ontology::Entity* create_Shader(const yli::ontology::ShaderStruct& shader_struct) const;
                yli::ontology::Entity* create_Material(const yli::ontology::MaterialStruct& material_struct) const;
                yli::ontology::Entity* create_Species(const yli::ontology::SpeciesStruct& species_struct) const;
                yli::ontology::Entity* create_Object(const yli::ontology::ObjectStruct& object_struct) const;
                yli::ontology::Entity* create_Symbiosis(const yli::ontology::SymbiosisStruct& symbiosis_struct) const;
                yli::ontology::Entity* create_Holobiont(const yli::ontology::HolobiontStruct& object_struct) const;
                yli::ontology::Entity* create_VectorFont(const yli::ontology::VectorFontStruct& vector_font_struct) const;
                yli::ontology::Entity* create_Text2D(const yli::ontology::TextStruct& text_struct) const;
                yli::ontology::Entity* create_Text3D(const yli::ontology::Text3DStruct& text3D_struct) const;
                yli::ontology::Entity* create_Font2D(
                        const std::size_t screen_width,
                        const std::size_t screen_height,
                        const std::string& texture_filename,
                        const std::string& font_texture_file_format) const;
                yli::ontology::Entity* create_Console() const;
                yli::ontology::Entity* create_Camera(const yli::ontology::CameraStruct& camera_struct) const;
                yli::ontology::Entity* create_ComputeTask(const yli::ontology::ComputeTaskStruct& compute_task_struct) const;
                yli::ontology::Entity* create_AnyValueEntity(const std::shared_ptr<yli::common::AnyValue> any_value_shared_ptr) const;
                yli::ontology::Entity* create_AnyValueEntity(const yli::common::AnyValue& any_value) const;
                yli::ontology::Entity* create_AnyStructEntity() const;
                yli::ontology::Entity* create_AnyStructEntity(const yli::common::AnyStruct& any_struct) const;

                friend class Universe;

            private:
                yli::ontology::Universe* universe;
        };
    }
}

#endif
