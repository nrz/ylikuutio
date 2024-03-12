// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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
#include "ecosystem.hpp"
#include "scene.hpp"
#include "pipeline.hpp"
#include "material_struct.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/core/application.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/data/datatype.hpp"
#include "code/ylikuutio/load/image_loader_struct.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.
#include "code/ylikuutio/render/render_system.hpp"
#include "code/ylikuutio/render/render_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cerr
#include <optional> // std::optional
#include <stdexcept> // std::runtime_error
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

namespace yli::ontology
{
    class Entity;

    std::optional<yli::data::AnyValue> Material::bind_to_new_ecosystem_parent(
            yli::ontology::Material& material,
            yli::ontology::Ecosystem& new_parent)
    {
        // Set pointer to `Material` to `nullptr`, set parent according to the input,
        // and request a new childID from `new_parent`.

        const yli::ontology::Entity* const old_parent = material.get_parent();

        if (old_parent == nullptr)
        {
            throw std::runtime_error("ERROR: `Material::bind_to_new_ecosystem_parent`: `old_parent` is `nullptr`!");
        }

        if (&new_parent == old_parent)
        {
            // Setting current parent as the new parent. Nothing to do.
            return std::nullopt;
        }

        if (new_parent.has_child(material.local_name))
        {
            std::cerr << "ERROR: `Material::bind_to_new_ecosystem_parent`: local name is already in use!\n";
            return std::nullopt;
        }

        // `Ecosystem`s do not care in which `Ecosystem`s their apprentices reside,
        // so binding to an `Ecosystem` does not unbind any apprentices.
        material.child_of_scene_or_ecosystem.unbind_and_bind_to_new_parent(
                &new_parent.parent_of_materials);

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Material::bind_to_new_scene_parent(
            yli::ontology::Material& material,
            yli::ontology::Scene& new_parent)
    {
        // Set pointer to `material` to `nullptr`, set parent according to the input,
        // and request a new childID from `new_parent`.

        const yli::ontology::Scene* const scene = static_cast<yli::ontology::Scene*>(material.get_parent());

        if (scene == nullptr)
        {
            throw std::runtime_error("ERROR: `Material::bind_to_new_scene_parent`: `scene` is `nullptr`!");
        }

        if (&new_parent == scene)
        {
            // Setting current parent as the new parent. Nothing to do.
            return std::nullopt;
        }

        if (new_parent.has_child(material.local_name))
        {
            std::cerr << "ERROR: `Material::bind_to_new_scene_parent`: local name is already in use!\n";
            return std::nullopt;
        }

        material.master_of_species.unbind_all_apprentice_modules_belonging_to_other_scenes(&new_parent);
        material.apprentice_of_pipeline.unbind_from_any_master_belonging_to_other_scene(new_parent);
        material.child_of_scene_or_ecosystem.unbind_and_bind_to_new_parent(
                &new_parent.parent_of_materials);

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Material::bind_to_new_pipeline(
            yli::ontology::Material& material,
            yli::ontology::Pipeline& new_pipeline) noexcept
    {
        // Set pointer to `material` to `nullptr`, set pipeline according to the input,
        // and request a new apprenticeID from `new_parent`.

        // All apprentices of a master must belong to the same `Scene`
        // as the master if the master belongs to some `Scene`.
        if (material.get_scene() == new_pipeline.get_scene() ||
                (new_pipeline.get_scene() == nullptr))
        {
            material.apprentice_of_pipeline.unbind_and_bind_to_new_generic_master_module(
                    &new_pipeline.master_of_materials);
        }
        else
        {
            std::cerr << "ERROR: `Material::bind_to_new_pipeline`: master and apprentice can not belong to different `Scene`s!\n";
        }

        return std::nullopt;
    }

    Material::Material(
            yli::core::Application& application,
            yli::ontology::Universe& universe,
            const yli::ontology::MaterialStruct& material_struct,
            yli::ontology::GenericParentModule* const scene_or_ecosystem_parent_module,
            yli::ontology::MasterModule<yli::ontology::Pipeline*>* pipeline_master_module)
        : Entity(application, universe, material_struct),
        child_of_scene_or_ecosystem(scene_or_ecosystem_parent_module, *this),
        parent_of_shapeshifter_transformations(
                *this,
                this->registry,
                application.get_memory_allocator(yli::data::Datatype::SHAPESHIFTER_TRANSFORMATION),
                "shapeshifter_transformations"),
        parent_of_vector_fonts(
                *this,
                this->registry,
                application.get_memory_allocator(yli::data::Datatype::VECTOR_FONT),
                "vector_fonts"),
        apprentice_of_pipeline(static_cast<yli::ontology::GenericMasterModule*>(pipeline_master_module), this),
        master_of_species(this, &this->registry, "species"),
        texture(
                universe,
                &this->registry,
                material_struct.texture_filename,
                material_struct.texture_file_format,
                yli::load::ImageLoaderStruct(),
                "texture")
    {
        // constructor.

        if (this->texture.get_is_texture_loaded() && this->get_pipeline() != nullptr)
        {
            // Get a handle for our "texture_sampler" uniform.
            yli::ontology::Pipeline* const pipeline = this->get_pipeline();
            this->opengl_texture_id = glGetUniformLocation(pipeline->get_program_id(), "texture_sampler");
        }

        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "yli::ontology::Material*";
        this->can_be_erased = true;
    }

    void Material::render(const yli::ontology::Scene* const target_scene)
    {
        if (!this->texture.get_is_texture_loaded() || !this->should_be_rendered)
        {
            return;
        }

        yli::ontology::Scene* const scene = this->get_scene();

        if (target_scene != nullptr && scene != nullptr && scene != target_scene)
        {
            // Different `Scene`s, do not render.
            return;
        }

        const yli::ontology::Scene* const new_target_scene = (target_scene != nullptr ? target_scene : scene);

        yli::render::RenderSystem* const render_system = this->universe.get_render_system();

        if (render_system == nullptr)
        {
            std::cerr << "ERROR: `Material::render`: `render_system` is `nullptr`!\n";
            return;
        }

        // Bind our texture in Texture Unit 0.
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->texture.get_texture());

        // Set our "texture_sampler" sampler to use Texture Unit 0.
        yli::opengl::uniform_1i(this->opengl_texture_id, 0);

        render_system->render_species(this->master_of_species, new_target_scene);
        render_system->render_vector_fonts(this->parent_of_vector_fonts, new_target_scene);
    }

    yli::ontology::Entity* Material::get_parent() const
    {
        return this->child_of_scene_or_ecosystem.get_parent();
    }

    yli::ontology::Pipeline* Material::get_pipeline() const
    {
        return static_cast<yli::ontology::Pipeline*>(this->apprentice_of_pipeline.get_master());
    }

    yli::ontology::Scene* Material::get_scene() const
    {
        return this->child_of_scene_or_ecosystem.get_scene();
    }

    std::size_t Material::get_number_of_children() const
    {
        return this->parent_of_shapeshifter_transformations.get_number_of_children() +
            this->parent_of_vector_fonts.get_number_of_children();
    }

    std::size_t Material::get_number_of_descendants() const
    {
        return yli::ontology::get_number_of_descendants(this->parent_of_shapeshifter_transformations.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_vector_fonts.child_pointer_vector);
    }

    std::size_t Material::get_number_of_apprentices() const
    {
        return this->master_of_species.get_number_of_apprentices();
    }

    const std::string& Material::get_texture_file_format() const
    {
        return this->texture.get_texture_file_format();
    }

    const std::string& Material::get_texture_filename() const
    {
        return this->texture.get_texture_filename();
    }

    uint32_t Material::get_image_width() const
    {
        return this->texture.get_image_width();
    }

    uint32_t Material::get_image_height() const
    {
        return this->texture.get_image_height();
    }

    uint32_t Material::get_image_size() const
    {
        return this->texture.get_image_size();
    }
}
