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

#ifndef __YLIKUUTIO_ONTOLOGY_MATERIAL_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_MATERIAL_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "generic_parent_module.hpp"
#include "apprentice_module.hpp"
#include "generic_master_module.hpp"
#include "master_module.hpp"
#include "universe.hpp"
#include "shader.hpp"
#include "material_struct.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/load/common_texture_loader.hpp"
#include "code/ylikuutio/load/image_loader_struct.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.
#include "code/ylikuutio/render/render_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::ontology
{
    class Scene;

    class Material: public yli::ontology::Entity
    {
        public:
            // This method sets pointer to this `Material` to `nullptr`, sets `parent` according to the input, and requests a new `childID` from the new `Scene`.
            void bind_to_new_scene_parent(yli::ontology::Scene* const new_parent);
            void bind_to_new_parent(yli::ontology::Entity* const new_parent) override;

            void bind_to_new_shader(yli::ontology::Shader* const new_shader);

            Material(
                    yli::ontology::Universe* const universe,
                    const yli::ontology::MaterialStruct& material_struct,
                    yli::ontology::GenericParentModule* const scene_parent_module, // Parent is a `Scene`.
                    yli::ontology::MasterModule<yli::ontology::Shader*>* shader_master_module)
                : Entity(universe, material_struct),
                child_of_scene(scene_parent_module, this),
                parent_of_shapeshifter_transformations(this, &this->registry, "shapeshifter_transformations"),
                parent_of_vector_fonts(this, &this->registry, "vector_fonts"),
                parent_of_chunk_masters(this, &this->registry, "chunk_masters"),
                apprentice_of_shader(static_cast<yli::ontology::GenericMasterModule*>(shader_master_module), this),
                master_of_species(this, &this->registry, "species"),
                texture_file_format  { material_struct.texture_file_format },
                texture_filename     { material_struct.texture_filename }
            {
                // constructor.

                const bool is_headless = (this->universe == nullptr ? true : this->universe->get_is_headless());

                if (this->universe != nullptr &&
                        !this->universe->get_is_headless() &&
                        this->get_shader() != nullptr)
                {
                    // Load the texture.
                    if (this->texture_file_format == "png" ||
                            this->texture_file_format == "PNG")
                    {
                        uint32_t n_color_channels = 0;

                        if (yli::load::load_common_texture(
                                    this->texture_filename,
                                    yli::load::ImageLoaderStruct(),
                                    this->image_width,
                                    this->image_height,
                                    this->image_size,
                                    n_color_channels,
                                    this->texture,
                                    is_headless))
                        {
                            this->is_texture_loaded = true;
                        }
                        else
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
                    yli::ontology::Shader* const shader = this->get_shader();
                    this->opengl_texture_id = glGetUniformLocation(shader->get_program_id(), "texture_sampler");
                }

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::Material*";
                this->can_be_erased = true;
            }

            Material(const Material&) = delete;            // Delete copy constructor.
            Material& operator=(const Material&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~Material();

            yli::ontology::Entity* get_parent() const override;

            yli::ontology::GenericMasterModule* get_generic_master_module() const;

            std::size_t get_number_of_apprentices() const;

            yli::ontology::Shader* get_shader() const;

            const std::string& get_texture_file_format() const;
            const std::string& get_texture_filename() const;
            uint32_t get_image_width() const;
            uint32_t get_image_height() const;
            uint32_t get_image_size() const;

            template<typename T1>
                friend void yli::render::render_apprentices(const std::vector<yli::ontology::ApprenticeModule*>& apprentice_pointer_vector);

            yli::ontology::ChildModule child_of_scene;
            yli::ontology::GenericParentModule parent_of_shapeshifter_transformations;
            yli::ontology::GenericParentModule parent_of_vector_fonts;
            yli::ontology::GenericParentModule parent_of_chunk_masters;
            yli::ontology::ApprenticeModule apprentice_of_shader;
            yli::ontology::GenericMasterModule master_of_species;

        protected:
            uint32_t image_width  { 0 };
            uint32_t image_height { 0 };
            uint32_t image_size   { 0 };

            GLuint texture           { 0 }; // Texture of this `Material`, returned by `load_common_texture` (used for `glGenTextures` etc.). Dummy value.
            GLuint opengl_texture_id { 0 }; // Texture ID, returned by `glGetUniformLocation(program_id, "texture_sampler")`. Dummy value.

        public:
            yli::ontology::Scene* get_scene() const override;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            // This method renders all `Species` using this `Material`.
            void render();

            std::string texture_file_format;     // Type of the model file, eg. `"png"`.
            std::string texture_filename;        // Filename of the model file.
            bool is_texture_loaded { false };
    };
}

#endif
