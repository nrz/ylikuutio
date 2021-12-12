// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
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
#include "code/ylikuutio/render/render_master.hpp"
#include "code/ylikuutio/render/render_templates.hpp"
#include <ofbx.h>

// Include standard headers
#include <cstddef>  // std::size_t
#include <ios>      // std::defaultfloat, std::dec, std::fixed, std::hex, std::ios
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.

namespace yli::ontology
{
    class Entity;
    class Scene;

    SymbiontMaterial::~SymbiontMaterial()
    {
        // destructor.
        std::cout << "`SymbiontMaterial` with childID " << std::dec << this->childID << " will be destroyed.\n";

        glDeleteTextures(1, &this->texture);
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

    void SymbiontMaterial::render()
    {
        if (!this->should_be_rendered || this->universe == nullptr)
        {
            return;
        }

        yli::render::RenderMaster* const render_master = this->universe->get_render_master();

        if (render_master == nullptr)
        {
            return;
        }

        this->prerender();

        // Bind our texture in Texture Unit 0.
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->texture);
        // Set our "texture_sampler" sampler to user Texture Unit 0.
        yli::opengl::uniform_1i(this->opengl_texture_id, 0);

        render_master->render_symbiont_species(this->parent_of_symbiont_species.child_pointer_vector);

        this->postrender();
    }

    std::size_t SymbiontMaterial::get_number_of_children() const
    {
        return this->parent_of_symbiont_species.get_number_of_children();
    }

    std::size_t SymbiontMaterial::get_number_of_descendants() const
    {
        return yli::ontology::get_number_of_descendants(this->parent_of_symbiont_species.child_pointer_vector);
    }

    void SymbiontMaterial::load_texture()
    {
        // requirements:
        // `this->ofbx_texture` must not be `nullptr`.
        // `this->parent` must not be `nullptr`.
        // `this->parent->get_parent()` must not be `nullptr`.

        const ofbx::Texture* const texture = this->ofbx_texture;

        if (texture == nullptr)
        {
            std::cerr << "ERROR: `SymbiontMaterial::load_texture`: `texture` is `nullptr`!\n";
            return;
        }

        const yli::ontology::Symbiosis* const symbiosis = static_cast<yli::ontology::Symbiosis*>(this->get_parent());

        if (symbiosis == nullptr)
        {
            std::cerr << "ERROR: `SymbiontMaterial::load_texture`: `symbiosis` is `nullptr`!\n";
            return;
        }

        const yli::ontology::Shader* const shader = static_cast<yli::ontology::Shader*>(symbiosis->apprentice_of_shader.get_master());

        if (shader == nullptr)
        {
            std::cerr << "ERROR: `SymbiontMaterial::load_texture`: `shader` is `nullptr`!\n";
            return;
        }

        // If software rendering is in use, the texture can not be loaded into GPU memory,
        // but it can still be loaded into CPU memory to be used by the software rendering.
        const bool should_load_texture = (this->universe != nullptr &&
                (this->universe->get_is_opengl_in_use() ||
                 this->universe->get_is_vulkan_in_use() ||
                 this->universe->get_is_software_rendering_in_use()));

        uint32_t n_color_channels = 0;

        if (should_load_texture)
        {
            if (!yli::load::load_fbx_texture(
                        texture,
                        this->image_width,
                        this->image_height,
                        this->image_size,
                        n_color_channels,
                        this->texture,
                        this->universe->get_graphics_api_backend()))
            {
                std::cerr << "ERROR: loading FBX texture failed!\n";
            }

            if (this->universe->get_is_opengl_in_use())
            {
                // Get a handle for our "texture_sampler" uniform.
                this->opengl_texture_id = glGetUniformLocation(shader->get_program_id(), "texture_sampler");
            }
        }
    }

    uint32_t SymbiontMaterial::get_texture() const
    {
        return this->texture;
    }

    GLint SymbiontMaterial::get_openGL_textureID() const
    {
        return this->opengl_texture_id;
    }
}
