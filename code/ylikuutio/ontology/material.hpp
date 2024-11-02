// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
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

namespace yli::memory
{
    template<typename T1, std::size_t DataSize>
        class MemoryStorage;
}

namespace yli::ontology
{
    class Universe;
    class Ecosystem;
    class Scene;
    class Pipeline;
    class Species;
    class SymbiontSpecies;
    class Glyph;
    struct MaterialStruct;

    class Material final : public Entity
    {
        public:
            // Set pointer to `material` to `nullptr`, set parent according to the input,
            // and request a new childID from `new_parent`.
            static std::optional<yli::data::AnyValue> bind_to_new_ecosystem_parent(
                    Material& material,
                    Ecosystem& new_parent);

            // Set pointer to `material` to `nullptr`, set parent according to the input,
            // and request a new childID from `new_parent`.
            static std::optional<yli::data::AnyValue> bind_to_new_scene_parent(
                    Material& material,
                    Scene& new_parent);

            // Set pointer to `material` to `nullptr`, set pipeline according to the input,
            // and request a new apprenticeID from `new_parent`.
            static std::optional<yli::data::AnyValue> bind_to_new_pipeline(
                    Material& material,
                    Pipeline& new_pipeline) noexcept;

        private:
            Material(
                    yli::core::Application& application,
                    Universe& universe,
                    const MaterialStruct& material_struct,
                    GenericParentModule* const ecosystem_or_scene_parent_module,
                    GenericMasterModule* const pipeline_master_module);

            ~Material() = default;

        public:
            Material(const Material&) = delete;            // Delete copy constructor.
            Material& operator=(const Material&) = delete; // Delete copy assignment.

            Entity* get_parent() const override;

            GenericParentModule* get_generic_parent_module(const int type);

            template<typename ApprenticeType>
                GenericMasterModule* get_generic_master_module() = delete;

            std::size_t get_number_of_apprentices() const;

            Pipeline* get_pipeline() const;

            const std::string& get_texture_file_format() const;
            const std::string& get_texture_filename() const;
            uint32_t get_image_width() const;
            uint32_t get_image_height() const;
            uint32_t get_image_size() const;

            template<typename T1, std::size_t DataSize>
                friend class yli::memory::MemoryStorage;

            ChildModule child_of_ecosystem_or_scene;
            GenericParentModule parent_of_shapeshifter_transformations;
            GenericParentModule parent_of_vector_fonts;
            ApprenticeModule apprentice_of_pipeline;
            GenericMasterModule master_of_species;
            GenericMasterModule master_of_symbiont_species;
            GenericMasterModule master_of_glyphs;
            TextureModule texture;

        protected:
            GLuint opengl_texture_id { 0 }; // Texture ID, returned by `glGetUniformLocation(program_id, "texture_sampler")`. Dummy value.

        public:
            Scene* get_scene() const override;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

        public:
            void render(const Scene* const target_scene);
    };

    template<>
        inline GenericMasterModule* Material::get_generic_master_module<Species>()
        {
            return &this->master_of_species;
        }

    template<>
        inline GenericMasterModule* Material::get_generic_master_module<SymbiontSpecies>()
        {
            return &this->master_of_symbiont_species;
        }

    template<>
        inline GenericMasterModule* Material::get_generic_master_module<Glyph>()
        {
            return &this->master_of_glyphs;
        }
}

#endif
