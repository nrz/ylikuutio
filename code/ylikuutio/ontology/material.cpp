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

#include "material.hpp"
#include "universe.hpp"
#include "shader.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.
#include "code/ylikuutio/render/render_master.hpp"
#include "code/ylikuutio/render/render_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <ios>      // std::defaultfloat, std::dec, std::fixed, std::hex, std::ios
#include <iostream> // std::cout, std::cin, std::cerr
#include <string>   // std::string

namespace yli::ontology
{
    class Species;

    Material::~Material()
    {
        if (!this->is_symbiont_material)
        {
            // destructor.
            std::cout << "`Material` with childID " << std::dec << this->childID << " will be destroyed.\n";

            glDeleteTextures(1, &this->texture);
        }
    }

    void Material::render()
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

        // Set our "texture_sampler" sampler to use Texture Unit 0.
        yli::opengl::uniform_1i(this->opengl_texture_id, 0);

        render_master->render_species(this->parent_of_species.child_pointer_vector);
        render_master->render_vector_fonts(this->parent_of_vector_fonts.child_pointer_vector);
        render_master->render_chunk_masters(this->parent_of_chunk_masters.child_pointer_vector);

        this->postrender();
    }

    yli::ontology::Entity* Material::get_parent() const
    {
        return this->child_of_shader_or_symbiosis.get_parent();
    }

    std::size_t Material::get_number_of_children() const
    {
        return this->parent_of_species.get_number_of_children() +
            this->parent_of_shapeshifter_transformations.get_number_of_children() +
            this->parent_of_vector_fonts.get_number_of_children() +
            this->parent_of_chunk_masters.get_number_of_children();
    }

    std::size_t Material::get_number_of_descendants() const
    {
        return yli::ontology::get_number_of_descendants(this->parent_of_species.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_shapeshifter_transformations.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_vector_fonts.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_chunk_masters.child_pointer_vector);
    }

    void Material::bind_to_new_shader_parent(yli::ontology::Shader* const new_parent)
    {
        // Requirements:
        // `this->is_symbiont_material` must be `false`.
        // `this->parent` must not be `nullptr`.
        // `new_parent` must not be `nullptr`.

        if (this->is_symbiont_material)
        {
            return;
        }

        yli::ontology::Shader* const shader = static_cast<yli::ontology::Shader*>(this->child_of_shader_or_symbiosis.get_parent());

        if (shader == nullptr)
        {
            std::cerr << "ERROR: `Material::bind_to_new_shader_parent`: `shader` is `nullptr`!\n";
            return;
        }

        if (new_parent == nullptr)
        {
            std::cerr << "ERROR: `Material::bind_to_new_shader_parent`: `new_parent` is `nullptr`!\n";
            return;
        }

        if (new_parent->has_child(this->local_name))
        {
            std::cerr << "ERROR: `Material::bind_to_new_shader_parent`: local name is already in use!\n";
            return;
        }

        // Unbind from the old parent `Shader`.
        shader->parent_of_materials.unbind_child(this->childID);

        // Get `childID` from `Shader` and set pointer to this `Material`.
        this->child_of_shader_or_symbiosis.set_parent_module_and_bind_to_new_parent(&new_parent->parent_of_materials);
    }

    void Material::bind_to_new_parent(yli::ontology::Entity* const new_parent)
    {
        // this method sets pointer to this `Material` to `nullptr`, sets `parent` according to the input,
        // and requests a new `childID` from the new `Shader`.
        //
        // requirements:
        // `new_parent` must not be `nullptr`.

        yli::ontology::Shader* const shader = dynamic_cast<yli::ontology::Shader*>(new_parent);

        if (shader != nullptr)
        {
            this->bind_to_new_shader_parent(shader);
            return;
        }

        std::cerr << "ERROR: `Material::bind_to_new_parent`: `new_parent` is not `yli::ontology::Shader*`!\n";
    }

    void Material::set_terrain_species(yli::ontology::Species* const terrain_species)
    {
        // Requirements:
        // `this->is_symbiont_material` must be `false`.

        if (this->is_symbiont_material)
        {
            return;
        }

        yli::ontology::Shader* const shader_parent = static_cast<yli::ontology::Shader*>(this->child_of_shader_or_symbiosis.get_parent());

        if (shader_parent != nullptr)
        {
            shader_parent->set_terrain_species(terrain_species);
        }
    }

    const std::string& Material::get_texture_file_format() const
    {
        return this->texture_file_format;
    }

    const std::string& Material::get_texture_filename() const
    {
        return this->texture_filename;
    }

    std::size_t Material::get_image_width() const
    {
        return this->image_width;
    }

    std::size_t Material::get_image_height() const
    {
        return this->image_height;
    }

    std::size_t Material::get_image_size() const
    {
        return this->image_size;
    }
}
