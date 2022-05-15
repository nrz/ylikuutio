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
#include "symbiosis.hpp"
#include "symbiont_species.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/load/fbx_texture_loader.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.
#include "code/ylikuutio/render/render_system.hpp"
#include "code/ylikuutio/render/render_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <ios>      // std::defaultfloat, std::dec, std::fixed, std::hex, std::ios
#include <iostream> // std::cout, std::cin, std::cerr

namespace yli::ontology
{
    class Entity;
    class Scene;

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

    void SymbiontMaterial::render()
    {
        if (!this->should_be_rendered)
        {
            return;
        }

        yli::render::RenderSystem* const render_system = this->universe.get_render_system();

        if (render_system == nullptr)
        {
            std::cerr << "ERROR: `SymbiontMaterial::render`: `render_system` is `nullptr`!\n";
            return;
        }

        if (this->universe.get_is_opengl_in_use())
        {
            // Bind our texture in Texture Unit 0.
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, this->texture.get_texture());
            // Set our "texture_sampler" sampler to user Texture Unit 0.
            yli::opengl::uniform_1i(this->opengl_texture_id, 0);
        }

        render_system->render_symbiont_species(this->parent_of_symbiont_species.child_pointer_vector);
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
