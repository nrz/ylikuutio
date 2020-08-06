// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
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

#ifndef __YLIKUUTIO_ONTOLOGY_ENTITY_FACTORY_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_ENTITY_FACTORY_HPP_INCLUDED

#include "variable_struct.hpp"
#include "world_struct.hpp"
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
#include "console_struct.hpp"
#include "font_struct.hpp"
#include "lisp_function_struct.hpp"
#include "camera_struct.hpp"
#include "compute_task_struct.hpp"
#include "brain_struct.hpp"

// Include standard headers
#include <cstddef>   // std::size_t
#include <memory>    // std::make_shared, std::shared_ptr
#include <string>    // std::string

namespace yli::ontology
{
    class Entity;
    class Variable;
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
    class Brain;

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

            yli::ontology::Entity* create_variable(const yli::ontology::VariableStruct& variable_struct) const;
            yli::ontology::Entity* create_world(const yli::ontology::WorldStruct& world_struct) const;
            yli::ontology::Entity* create_scene(const yli::ontology::SceneStruct& scene_struct) const;
            yli::ontology::Entity* create_shader(const yli::ontology::ShaderStruct& shader_struct) const;
            yli::ontology::Entity* create_material(const yli::ontology::MaterialStruct& material_struct) const;
            yli::ontology::Entity* create_species(const yli::ontology::SpeciesStruct& species_struct) const;
            yli::ontology::Entity* create_object(const yli::ontology::ObjectStruct& object_struct) const;
            yli::ontology::Entity* create_symbiosis(const yli::ontology::SymbiosisStruct& symbiosis_struct) const;
            yli::ontology::Entity* create_holobiont(const yli::ontology::HolobiontStruct& object_struct) const;
            yli::ontology::Entity* create_vector_font(const yli::ontology::VectorFontStruct& vector_font_struct) const;
            yli::ontology::Entity* create_text2d(const yli::ontology::TextStruct& text_struct) const;
            yli::ontology::Entity* create_text3d(const yli::ontology::Text3DStruct& text3D_struct) const;
            yli::ontology::Entity* create_font2d(const yli::ontology::FontStruct& font_struct) const;
            yli::ontology::Entity* create_console(const yli::ontology::ConsoleStruct& console_struct) const;
            yli::ontology::Entity* create_lisp_function(const yli::ontology::LispFunctionStruct& lisp_function_struct) const;
            yli::ontology::Entity* create_camera(const yli::ontology::CameraStruct& camera_struct) const;
            yli::ontology::Entity* create_compute_task(const yli::ontology::ComputeTaskStruct& compute_task_struct) const;
            yli::ontology::Entity* create_brain(const yli::ontology::BrainStruct& brain_struct) const;
            yli::ontology::Entity* create_callback_engine_entity() const;

        private:
            yli::ontology::Universe* universe;
    };
}

#endif
