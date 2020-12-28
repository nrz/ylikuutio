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

#ifndef __YLIKUUTIO_ONTOLOGY_MATERIAL_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_MATERIAL_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "parent_module.hpp"
#include "universe.hpp"
#include "shader.hpp"
#include "material_struct.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/load/common_texture_loader.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.
#include "code/ylikuutio/render/render_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::ontology
{
    class Species;

    class Material: public yli::ontology::Entity
    {
        public:
            Material(yli::ontology::Universe* const universe, const yli::ontology::MaterialStruct& material_struct, yli::ontology::ParentModule* const parent_module)
                : Entity(universe, material_struct),
                child_of_shader_or_symbiosis(parent_module, this),
                parent_of_species(this),
                parent_of_shapeshifter_transformations(this),
                parent_of_vector_fonts(this),
                parent_of_chunk_masters(this)
            {
                // constructor.
                this->is_symbiont_material     = material_struct.is_symbiont_material;
                this->texture_file_format      = material_struct.texture_file_format;
                this->texture_filename         = material_struct.texture_filename;
                this->texture                  = 0; // some dummy value.
                this->opengl_texture_id        = 0; // some dummy value.
                this->image_width              = 0;
                this->image_height             = 0;
                this->image_size               = 0;

                const bool is_headless = (this->universe == nullptr ? true : this->universe->get_is_headless());

                if (!this->is_symbiont_material)
                {
                    // Load the texture.
                    if (this->texture_file_format == "bmp" ||
                            this->texture_file_format == "BMP" ||
                            this->texture_file_format == "png" ||
                            this->texture_file_format == "PNG")
                    {
                        if (!yli::load::load_common_texture(
                                    this->texture_filename,
                                    this->image_width,
                                    this->image_height,
                                    this->image_size,
                                    this->texture,
                                    is_headless))
                        {
                            std::cerr << "ERROR: loading " << this->texture_file_format << " texture failed!\n";
                        }
                    }
                    else
                    {
                        std::cerr << "no texture was loaded!\n";
                        std::cerr << "texture file format: " << this->texture_file_format << "\n";
                    }

                    // Get a handle for our "texture_sampler" uniform.
                    if (this->universe != nullptr && !this->universe->get_is_headless() && this->child_of_shader_or_symbiosis.get_parent() != nullptr)
                    {
                        yli::ontology::Shader* const shader = static_cast<yli::ontology::Shader*>(this->child_of_shader_or_symbiosis.get_parent());
                        this->opengl_texture_id = glGetUniformLocation(shader->get_program_id(), "texture_sampler");
                    }

                    // `yli::ontology::Entity` member variables begin here.
                    this->type_string = "yli::ontology::Material*";
                    this->can_be_erased = true;
                }
            }

            Material(const Material&) = delete;            // Delete copy constructor.
            Material& operator=(const Material&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~Material();

            // This method sets pointer to this `Material` to `nullptr`, sets `parent` according to the input, and requests a new `childID` from the new `Shader`.
            void bind_to_new_parent(yli::ontology::Shader* const new_parent);
            void bind_to_new_parent(yli::ontology::Entity* const new_parent) override;

            yli::ontology::Entity* get_parent() const override;

            // Set terrain `Species` pointers in `Scene` and `Universe` so that they point to the chosen terrain `Species`.
            // Currently there can be only one terrain `Species` in each `Scene` (used in collision detection).
            void set_terrain_species(yli::ontology::Species* const terrain_species);

            const std::string& get_texture_file_format() const;
            const std::string& get_texture_filename() const;
            std::size_t get_image_width() const;
            std::size_t get_image_height() const;
            std::size_t get_image_size() const;

            template<class T1, class T2>
                friend void yli::render::render_children(const std::vector<T1>& child_pointer_vector);

            yli::ontology::ChildModule child_of_shader_or_symbiosis;
            yli::ontology::ParentModule parent_of_species;
            yli::ontology::ParentModule parent_of_shapeshifter_transformations;
            yli::ontology::ParentModule parent_of_vector_fonts;
            yli::ontology::ParentModule parent_of_chunk_masters;

        protected:
            std::size_t image_width;
            std::size_t image_height;
            std::size_t image_size;

            uint32_t texture;                    // Texture of this `Material`, returned by `load_common_texture` (used for `glGenTextures` etc.).
            GLuint opengl_texture_id;             // Texture ID, returned by `glGetUniformLocation(program_id, "texture_sampler")`.

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            // This method renders all `Species` using this `Material`.
            void render();

            bool is_symbiont_material;

            std::string texture_file_format;     // Type of the model file, eg. `"bmp"`.
            std::string texture_filename;        // Filename of the model file.
    };
}

#endif
