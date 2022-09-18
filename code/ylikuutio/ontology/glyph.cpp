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

#include "glyph.hpp"
#include "universe.hpp"
#include "model_struct.hpp"
#include "gl_attrib_locations.hpp"
#include "code/ylikuutio/render/render_system.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr

namespace yli::ontology
{
    class GenericMasterModule;
    class Entity;
    class Scene;

    Glyph::Glyph(
            yli::ontology::Universe& universe,
            const yli::ontology::ModelStruct& model_struct,
            yli::ontology::GenericParentModule* const vector_font_parent_module)
        : Entity(universe, model_struct),
        child_of_vector_font(vector_font_parent_module, this),
        master_of_objects(this, &this->registry, "objects"),
        mesh(universe, model_struct),
        glyph_vertex_data    { model_struct.glyph_vertex_data },
        glyph_name_pointer   { model_struct.glyph_name_pointer },
        unicode_char_pointer { model_struct.unicode_char_pointer }
    {
        // constructor.

        // If software rendering is in use, the vertices and UVs can not be loaded into GPU memory,
        // but they can still be loaded into CPU memory to be used by the software rendering.
        const bool should_load_texture =
            this->universe.get_is_opengl_in_use() ||
            this->universe.get_is_vulkan_in_use() ||
            this->universe.get_is_software_rendering_in_use();

        if (should_load_texture && model_struct.pipeline != nullptr)
        {
            // Get a handle for our buffers.
            yli::ontology::set_gl_attrib_locations(model_struct.pipeline, &this->mesh);
        }

        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "yli::ontology::Glyph*";
    }

    yli::ontology::Entity* Glyph::get_parent() const
    {
        return this->child_of_vector_font.get_parent();
    }

    yli::ontology::Scene* Glyph::get_scene() const
    {
        const yli::ontology::Entity* const parent = this->get_parent();

        if (parent != nullptr)
        {
            return parent->get_scene();
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

    void Glyph::render(const yli::ontology::Scene* const target_scene)
    {
        if (!this->should_be_rendered || this->universe.get_is_headless())
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
            std::cerr << "ERROR: `Glyph::render`: `render_system` is `nullptr`!\n";
            return;
        }

        render_system->render_glyph(this, new_target_scene);
    }

    yli::ontology::GenericMasterModule* Glyph::get_renderables_container()
    {
        return &this->master_of_objects;
    }

    const char* Glyph::get_unicode_char_pointer() const
    {
        return this->unicode_char_pointer;
    }
}
