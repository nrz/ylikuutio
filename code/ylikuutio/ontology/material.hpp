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

#ifndef YLIKUUTIO_ONTOLOGY_MATERIAL_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_MATERIAL_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "generic_parent_module.hpp"
#include "apprentice_module.hpp"
#include "generic_master_module.hpp"
#include "master_module.hpp"
#include "texture_module.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <cstddef>  // std::size_t
#include <optional> // std::optional
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class Ecosystem;
    class Universe;
    class Scene;
    class Pipeline;
    struct MaterialStruct;

    class Material final : public yli::ontology::Entity
    {
        public:
            // Set pointer to `material` to `nullptr`, set parent according to the input,
            // and request a new childID from `new_parent`.
            static std::optional<yli::data::AnyValue> bind_to_new_ecosystem_parent(
                    yli::ontology::Material& material,
                    yli::ontology::Ecosystem& new_parent) noexcept;

            // Set pointer to `material` to `nullptr`, set parent according to the input,
            // and request a new childID from `new_parent`.
            static std::optional<yli::data::AnyValue> bind_to_new_scene_parent(
                    yli::ontology::Material& material,
                    yli::ontology::Scene& new_parent) noexcept;

            // Set pointer to `material` to `nullptr`, set pipeline according to the input,
            // and request a new apprenticeID from `new_parent`.
            static std::optional<yli::data::AnyValue> bind_to_new_pipeline(
                    yli::ontology::Material& material,
                    yli::ontology::Pipeline& new_pipeline) noexcept;

            Material(
                    yli::core::Application& application,
                    yli::ontology::Universe& universe,
                    const yli::ontology::MaterialStruct& material_struct,
                    yli::ontology::GenericParentModule* const scene_or_ecosystem_parent_module,
                    yli::ontology::MasterModule<yli::ontology::Pipeline*>* pipeline_master_module);

            ~Material() = default;

            Material(const Material&) = delete;            // Delete copy constructor.
            Material& operator=(const Material&) = delete; // Delete copy assignment.

            yli::ontology::Entity* get_parent() const override;

            yli::ontology::GenericMasterModule* get_generic_master_module() const;

            std::size_t get_number_of_apprentices() const;

            yli::ontology::Pipeline* get_pipeline() const;

            const std::string& get_texture_file_format() const;
            const std::string& get_texture_filename() const;
            uint32_t get_image_width() const;
            uint32_t get_image_height() const;
            uint32_t get_image_size() const;

            yli::ontology::ChildModule child_of_scene_or_ecosystem;
            yli::ontology::GenericParentModule parent_of_shapeshifter_transformations;
            yli::ontology::GenericParentModule parent_of_vector_fonts;
            yli::ontology::ApprenticeModule apprentice_of_pipeline;
            yli::ontology::GenericMasterModule master_of_species;
            yli::ontology::TextureModule texture;

        protected:
            GLuint opengl_texture_id { 0 }; // Texture ID, returned by `glGetUniformLocation(program_id, "texture_sampler")`. Dummy value.

        public:
            yli::ontology::Scene* get_scene() const override;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

        public:
            void render(const yli::ontology::Scene* const target_scene);
    };
}

#endif
