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

#include "symbiont_material.hpp"
#include "universe.hpp"
#include "shader.hpp"
#include "symbiosis.hpp"
#include "material_struct.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/load/image_loader_struct.hpp"
#include "code/ylikuutio/load/fbx_texture_loader.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <cstddef>  // std::size_t
#include <ios>      // std::defaultfloat, std::dec, std::fixed, std::hex, std::ios
#include <iostream> // std::cout, std::cin, std::cerr

namespace yli::ontology
{
    class GenericParentModule;
    class Entity;
    class Scene;

    SymbiontMaterial::SymbiontMaterial(
            yli::ontology::Universe& universe,
            const yli::ontology::MaterialStruct& material_struct,
            yli::ontology::GenericParentModule* const symbiosis_parent_module) // Parent is a `Symbiosis`.
        : Entity(universe, material_struct),
        child_of_symbiosis(symbiosis_parent_module, this),
        parent_of_symbiont_species(this, &this->registry, "symbiont_species"),
        texture(
                universe,
                &this->registry,
                material_struct.ofbx_texture,
                yli::load::ImageLoaderStruct(),
                "texture")
    {
        // constructor.

        if (this->texture.get_is_texture_loaded())
        {
            yli::ontology::Shader* const shader = this->get_shader();

            if (shader != nullptr)
            {
                this->opengl_texture_id = glGetUniformLocation(shader->get_program_id(), "texture_sampler");
            }
        }

        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "yli::ontology::SymbiontMaterial*";
    }

    SymbiontMaterial::~SymbiontMaterial()
    {
        // destructor.
        std::cout << "`SymbiontMaterial` with childID " << std::dec << this->childID << " will be destroyed.\n";
    }

    yli::ontology::Scene* SymbiontMaterial::get_scene() const
    {
        yli::ontology::Entity* const symbiosis_parent = this->get_parent();

        if (symbiosis_parent != nullptr)
        {
            return symbiosis_parent->get_scene();
        }

        return nullptr;
    }

    yli::ontology::Entity* SymbiontMaterial::get_parent() const
    {
        return this->child_of_symbiosis.get_parent();
    }

    yli::ontology::Shader* SymbiontMaterial::get_shader() const
    {
        const yli::ontology::Symbiosis* const symbiosis = static_cast<yli::ontology::Symbiosis*>(this->get_parent());

        if (symbiosis != nullptr)
        {
            return static_cast<yli::ontology::Shader*>(symbiosis->apprentice_of_shader.get_master());
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
