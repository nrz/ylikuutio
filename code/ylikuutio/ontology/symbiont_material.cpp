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

#include "symbiont_material.hpp"
#include "pipeline.hpp"
#include "symbiosis.hpp"
#include "symbiont_material_struct.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/data/datatype.hpp"
#include "code/ylikuutio/load/image_loader_struct.hpp"
#include "code/ylikuutio/load/fbx_texture_loader.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <cstddef>   // std::size_t
#include <stdexcept> // std::runtime_error

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class GenericParentModule;
    class Entity;
    class Universe;
    class Scene;

    SymbiontMaterial::SymbiontMaterial(
            yli::core::Application& application,
            Universe& universe,
            const SymbiontMaterialStruct& symbiont_material_struct,
            GenericParentModule* const symbiosis_parent_module) // Parent is a `Symbiosis`.
        : Entity(application, universe, symbiont_material_struct),
        child_of_symbiosis(symbiosis_parent_module, *this),
        parent_of_symbiont_species(
                *this,
                this->registry,
                "symbiont_species"),
        texture(
                universe,
                &this->registry,
                symbiont_material_struct.ofbx_texture,
                yli::load::ImageLoaderStruct(),
                "texture")
    {
        if (this->texture.get_is_texture_loaded())
        {
            Pipeline* const pipeline = this->get_pipeline();

            if (pipeline != nullptr)
            {
                this->opengl_texture_id = glGetUniformLocation(pipeline->get_program_id(), "texture_sampler");
            }
        }

        // `Entity` member variables begin here.
        this->type_string = "yli::ontology::SymbiontMaterial*";
    }

    Scene* SymbiontMaterial::get_scene() const
    {
        const Entity* const symbiosis_parent = this->get_parent();

        if (symbiosis_parent == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `SymbiontMaterial::get_scene`: `symbiosis_parent` is `nullptr`!");
        }

        return symbiosis_parent->get_scene();
    }

    Entity* SymbiontMaterial::get_parent() const
    {
        return this->child_of_symbiosis.get_parent();
    }

    Pipeline* SymbiontMaterial::get_pipeline() const
    {
        const Symbiosis* const symbiosis_parent = static_cast<Symbiosis*>(this->get_parent());

        if (symbiosis_parent == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `SymbiontMaterial::get_pipeline`: `symbiosis_parent` is `nullptr`!");
        }

        return static_cast<Pipeline*>(symbiosis_parent->apprentice_of_pipeline.get_master());
    }

    GenericParentModule* SymbiontMaterial::get_generic_parent_module(const int type)
    {
        if (type == yli::data::Datatype::SYMBIONT_SPECIES)
        {
            return &this->parent_of_symbiont_species;
        }

        return nullptr;
    }

    std::size_t SymbiontMaterial::get_number_of_children() const
    {
        return this->parent_of_symbiont_species.get_number_of_children();
    }

    std::size_t SymbiontMaterial::get_number_of_descendants() const
    {
        return yli::ontology::get_number_of_descendants(this->parent_of_symbiont_species.child_pointer_vector);
    }

    GLint SymbiontMaterial::get_openGL_textureID() const
    {
        return this->opengl_texture_id;
    }
}
