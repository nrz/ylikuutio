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

#ifndef __MATERIAL_HPP_INCLUDED
#define __MATERIAL_HPP_INCLUDED

#include "entity.hpp"
#include "parent_module.hpp"
#include "universe.hpp"
#include "shader.hpp"
#include "material_struct.hpp"
#include "render_templates.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/load/bmp_texture_loader.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace ontology
    {
        class Species;
        class Object;
        class ChunkMaster;

        class Material: public yli::ontology::Entity
        {
            public:
                Material(yli::ontology::Universe* const universe, const yli::ontology::MaterialStruct& material_struct)
                    : Entity(universe),
                    parent_of_species(yli::ontology::ParentModule()),
                    parent_of_shapeshifter_transformations(yli::ontology::ParentModule()),
                    parent_of_vector_fonts(yli::ontology::ParentModule()),
                    parent_of_chunk_masters(yli::ontology::ParentModule())
                {
                    // constructor.
                    this->parent                   = material_struct.shader;
                    this->is_symbiont_material     = material_struct.is_symbiont_material;
                    this->texture_file_format      = material_struct.texture_file_format;
                    this->texture_filename         = material_struct.texture_filename;
                    this->texture                  = 0; // some dummy value.
                    this->openGL_textureID         = 0; // some dummy value.
                    this->image_width              = 0;
                    this->image_height             = 0;
                    this->image_size               = 0;

                    const bool is_headless = (this->universe == nullptr ? true : this->universe->get_is_headless());

                    if (!this->is_symbiont_material)
                    {
                        // Get `childID` from the `Shader` and set pointer to this `Material`.
                        this->bind_to_parent();

                        // Load the texture.
                        if (this->texture_file_format == "bmp" || this->texture_file_format == "BMP")
                        {
                            if (!yli::load::load_BMP_texture(
                                        this->texture_filename,
                                        this->image_width,
                                        this->image_height,
                                        this->image_size,
                                        this->texture,
                                        is_headless))
                            {
                                std::cerr << "ERROR: loading BMP texture failed!\n";
                            }
                        }
                        else
                        {
                            std::cerr << "no texture was loaded!\n";
                            std::cerr << "texture file format: " << this->texture_file_format << "\n";
                        }

                        // Get a handle for our "texture_sampler" uniform.
                        if (this->universe != nullptr && !this->universe->get_is_headless() && this->parent != nullptr)
                        {
                            this->openGL_textureID = glGetUniformLocation(this->parent->get_programID(), "texture_sampler");
                        }

                        // `yli::ontology::Entity` member variables begin here.
                        this->type_string = "yli::ontology::Material*";
                        this->can_be_erased = true;
                    }
                }

                Material(const Material&) = delete;            // Delete copy constructor.
                Material &operator=(const Material&) = delete; // Delete copy assignment.

                // destructor.
                virtual ~Material();

                // This method sets pointer to this `Material` to `nullptr`, sets `parent` according to the input, and requests a new `childID` from the new `Shader`.
                void bind_to_new_parent(yli::ontology::Shader* const new_parent);

                yli::ontology::Entity* get_parent() const override;
                std::size_t get_number_of_children() const override;
                std::size_t get_number_of_descendants() const override;

                // Set terrain `Species` pointers in `Scene` and `Universe` so that they point to the chosen terrain `Species`.
                // Currently there can be only one terrain `Species` in each `Scene` (used in collision detection).
                void set_terrain_species(yli::ontology::Species* const terrain_species);

                const std::string& get_texture_file_format() const;
                const std::string& get_texture_filename() const;
                std::size_t get_image_width() const;
                std::size_t get_image_height() const;
                std::size_t get_image_size() const;

                template<class T1>
                    friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);
                template<class T1>
                    friend void yli::ontology::render_children(const std::vector<T1>& child_pointer_vector);

                yli::ontology::ParentModule parent_of_species;
                yli::ontology::ParentModule parent_of_shapeshifter_transformations;
                yli::ontology::ParentModule parent_of_vector_fonts;
                yli::ontology::ParentModule parent_of_chunk_masters;

            protected:
                std::size_t image_width;
                std::size_t image_height;
                std::size_t image_size;

                uint32_t texture;                    // Texture of this `Material`, returned by `load_BMP_texture` (used for `glGenTextures` etc.).
                uint32_t openGL_textureID;           // Texture ID, returned by `glGetUniformLocation(programID, "texture_sampler")`.

            private:
                void bind_to_parent();

                // This method renders all `Species` using this `Material`.
                void render() override;

                yli::ontology::Shader* parent;       // Pointer to the `Shader`.

                bool is_symbiont_material;

                std::string texture_file_format;     // Type of the model file, eg. `"bmp"`.
                std::string texture_filename;        // Filename of the model file.
        };
    }
}

#endif
