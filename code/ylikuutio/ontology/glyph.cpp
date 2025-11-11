// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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

#include "glyph.hpp"
#include "universe.hpp"
#include "material.hpp"
#include "glyph_struct.hpp"
#include "gl_attrib_locations.hpp"
#include "code/ylikuutio/render/render_system.hpp"

// Include standard headers
#include <cstddef>   // std::size_t
#include <stdexcept> // std::runtime_error

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class GenericParentModule;
    class GenericMasterModule;
    class Entity;
    class Scene;
    class Pipeline;

    Glyph::Glyph(
            yli::core::Application& application,
            Universe& universe,
            const GlyphStruct& glyph_struct,
            GenericParentModule* const vector_font_parent_module,
            GenericMasterModule* const material_master_module)
        : Entity(application, universe, glyph_struct),
        child_of_vector_font(vector_font_parent_module, *this),
        apprentice_of_material(material_master_module, this),
        master_of_glyph_objects(*this, &this->registry, "glyph_objects"),
        mesh(universe, glyph_struct, this->get_pipeline()),
        glyph_vertex_data    { glyph_struct.glyph_vertex_data },
        glyph_name_pointer   { glyph_struct.glyph_name_pointer },
        unicode_char_pointer { glyph_struct.unicode_char_pointer }
    {
        // If software rendering is in use, the vertices and UVs can not be loaded into GPU memory,
        // but they can still be loaded into CPU memory to be used by the software rendering.
        const bool should_load_texture =
            this->universe.get_is_opengl_in_use() ||
            this->universe.get_is_vulkan_in_use() ||
            this->universe.get_is_software_rendering_in_use();

        // FIXME: implement mesh loading!

        // `Entity` member variables begin here.
        this->type_string = "yli::ontology::Glyph*";
    }

    Entity* Glyph::get_parent() const
    {
        return this->child_of_vector_font.get_parent();
    }

    Scene* Glyph::get_scene() const
    {
        const Entity* const vector_font_parent = this->get_parent();

        if (vector_font_parent == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Glyph::get_scene`: `vector_font_parent` is `nullptr`!");
        }

        return vector_font_parent->get_scene();
    }

    Pipeline* Glyph::get_pipeline() const
    {
        Material* const material = static_cast<Material*>(
                this->apprentice_of_material.get_master());

        if (material != nullptr)
        {
            return material->get_pipeline();
        }

        return nullptr;
    }

    std::size_t Glyph::get_number_of_children() const
    {
        return 0; // `Glyph` has no children.
    }

    std::size_t Glyph::get_number_of_descendants() const
    {
        return 0; // `Glyph` has no children.
    }

    void Glyph::render(const Scene* const target_scene)
    {
        if (!this->should_render || this->universe.get_is_headless())
        {
            return;
        }

        Scene* const scene = this->get_scene();

        if (target_scene != nullptr && scene != nullptr && scene != target_scene)
        {
            // Different `Scene`s, do not render.
            return;
        }

        const Scene* const new_target_scene = (target_scene != nullptr ? target_scene : scene);

        yli::render::RenderSystem& render_system = this->universe.get_render_system();

        render_system.render_glyph(this, new_target_scene);
    }

    GenericMasterModule* Glyph::get_renderables_container()
    {
        return &this->master_of_glyph_objects;
    }

    const char* Glyph::get_unicode_char_pointer() const
    {
        return this->unicode_char_pointer;
    }
}
