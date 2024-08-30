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

#include "render_system.hpp"
#include "render_model.hpp"
#include "render_templates.hpp"
#include "render_system_struct.hpp"
#include "render_struct.hpp"
#include "code/ylikuutio/ontology/generic_master_module.hpp"
#include "code/ylikuutio/ontology/generic_parent_module.hpp"
#include "code/ylikuutio/ontology/parent_of_pipelines_module.hpp"
#include "code/ylikuutio/ontology/entity.hpp"
#include "code/ylikuutio/ontology/ecosystem.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/pipeline.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/symbiosis.hpp"
#include "code/ylikuutio/ontology/symbiont_species.hpp"
#include "code/ylikuutio/ontology/holobiont.hpp"
#include "code/ylikuutio/ontology/biont.hpp"
#include "code/ylikuutio/ontology/shapeshifter_sequence.hpp"
#include "code/ylikuutio/ontology/font_2d.hpp"
#include "code/ylikuutio/ontology/text_2d.hpp"
#include "code/ylikuutio/ontology/vector_font.hpp"
#include "code/ylikuutio/ontology/glyph.hpp"
#include "code/ylikuutio/ontology/console.hpp"
#include "code/ylikuutio/ontology/compute_task.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.
#include "code/ylikuutio/sdl/ylikuutio_sdl.hpp"

// Include standard headers
#include <iostream> // std::cout, std::cerr
#include <stdint.h> // uint32_t etc.

namespace yli::ontology
{
    class Universe;
}

namespace yli::render
{
    RenderSystem::RenderSystem(yli::ontology::Universe* const universe, const yli::render::RenderSystemStruct& render_system_struct)
        : universe { universe },
        hidden_window_title { render_system_struct.hidden_window_title },
        hidden_window_width { render_system_struct.hidden_window_width },
        hidden_window_height { render_system_struct.hidden_window_height },
        is_hidden_window_fullscreen { render_system_struct.is_hidden_window_fullscreen }
    {
        // Open a window and create its OpenGL context.
        std::cout << "Opening a window and creating its OpenGL context...\n";

        this->hidden_sdl_window = yli::sdl::create_hidden_window(
                static_cast<int>(this->hidden_window_width),
                static_cast<int>(this->hidden_window_height),
                this->hidden_window_title.c_str(),
                this->is_hidden_window_fullscreen);

        if (this->hidden_sdl_window != nullptr)
        {
            std::cout << "Hidden SDL window created.\n";

            this->create_context_and_make_it_current();

            // Disable vertical sync.
            // TODO: add option to enable/disable vsync in the console.
            this->set_swap_interval(0);

            // Initialize GLEW.
            yli::opengl::init_glew();

            yli::input::disable_cursor();
            yli::input::enable_relative_mouse_mode();

            // Enable depth test.
            yli::opengl::enable_depth_test();
            // Accept fragment if it is closer to the camera than the former one.
            yli::opengl::set_depth_func_to_less();

            // Cull triangles whose normal is not towards the camera.
            yli::opengl::cull_triangles();
        }
        else
        {
            std::cerr << "Hidden SDL window could not be created!\n";
        }
    }

    void RenderSystem::create_context_and_make_it_current()
    {
        std::cout << "Creating OpenGL context and making it current...\n";
        this->context = yli::sdl::create_context(this->hidden_sdl_window);
    }

    [[nodiscard]] bool RenderSystem::setup_context(SDL_Window* window)
    {
        if (this->context != nullptr)
        {
            if (yli::sdl::make_context_current(window, this->context))
            {
                std::cout << "OpenGL context set up successfully.\n";
                return true; // Success.
            }
            else
            {
                std::cerr << "ERROR: `RenderSystem::setup_context`: setting context failed!\n";
                return false; // Fail.
            }
        }

        return false; // Fail.
    }

    [[nodiscard]] bool RenderSystem::setup_context()
    {
        if (this->context != nullptr)
        {
            return yli::sdl::make_context_current(this->hidden_sdl_window, this->context);
        }

        return false; // Fail.
    }

    void RenderSystem::set_swap_interval(const int32_t interval)
    {
        if (!yli::sdl::set_swap_interval(static_cast<int>(interval)))
        {
            std::cerr << "ERROR: `RenderSystem::set_swap_interval`: setting swap interval failed!\n";
        }
    }

    void RenderSystem::restore_onscreen_rendering(const uint32_t window_width, const uint32_t window_height) const
    {
        // Bind the default framebuffer for on-screen rendering.
        yli::opengl::bind_gl_framebuffer(0);

        // Set background color for the default framebuffer.
        this->set_opengl_background_color();

        // Clear the default framebuffer.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Adjust viewport for the default framebuffer.
        this->adjust_opengl_viewport(window_width, window_height);
    }

    void RenderSystem::set_opengl_background_color() const
    {
        yli::opengl::set_background_color(
                this->background_red,
                this->background_green,
                this->background_blue,
                this->background_alpha);
    }

    void RenderSystem::adjust_opengl_viewport(const uint32_t window_width, const uint32_t window_height) const
    {
        if (window_width <= std::numeric_limits<GLsizei>::max() &&
                window_height <= std::numeric_limits<GLsizei>::max()) [[likely]]
        {
            glViewport(0, 0, window_width, window_height);
        }
    }

    void RenderSystem::render(const yli::render::RenderStruct& render_struct) const
    {
        if (render_struct.scene != nullptr) [[likely]]
        {
            render_struct.scene->render();
        }

        if (render_struct.should_change_depth_test) [[likely]]
        {
            yli::opengl::disable_depth_test();
        }

        if (render_struct.parent_of_font_2ds != nullptr) [[likely]]
        {
            yli::render::render_children<yli::ontology::GenericParentModule&, yli::ontology::Font2d*>(*render_struct.parent_of_font_2ds);
        }

        if (render_struct.should_change_depth_test) [[likely]]
        {
            yli::opengl::enable_depth_test();
        }

        // Swap buffers.
        SDL_GL_SwapWindow(render_struct.window);
    }

    void RenderSystem::render_pipelines_of_ecosystems(yli::ontology::GenericParentModule& parent, const yli::ontology::Scene* const scene) const
    {
        for (auto it = parent.begin(); it != parent.end(); ++it)
        {
            yli::ontology::Ecosystem* ecosystem = static_cast<yli::ontology::Ecosystem*>(*it);

            if (ecosystem != nullptr && ecosystem->should_render) [[likely]]
            {
                this->render_pipelines_of_an_ecosystem(ecosystem->parent_of_pipelines, scene);
            }
        }
    }

    void RenderSystem::render_pipelines_of_an_ecosystem(yli::ontology::ParentOfPipelinesModule& parent, const yli::ontology::Scene* const scene) const
    {
        yli::render::render_children_of_given_scene_or_of_all_scenes<
            yli::ontology::ParentOfPipelinesModule&,
            yli::ontology::Pipeline*>(
                parent,
                scene);
    }

    void RenderSystem::render_pipelines(yli::ontology::ParentOfPipelinesModule& parent, const yli::ontology::Scene* const scene) const
    {
        yli::render::render_children_of_given_scene_or_of_all_scenes<yli::ontology::ParentOfPipelinesModule&, yli::ontology::Pipeline*>(
                parent,
                scene);
    }

    void RenderSystem::render_materials(
            yli::ontology::GenericMasterModule& master,
            const yli::ontology::Scene* const scene) const
    {
        yli::render::render_apprentices<yli::ontology::GenericMasterModule&, yli::ontology::Material*>(master, scene);
    }

    void RenderSystem::render_species(
            yli::ontology::GenericMasterModule& master,
            const yli::ontology::Scene* const scene) const
    {
        yli::render::render_apprentices<yli::ontology::GenericMasterModule&, yli::ontology::Species*>(master, scene);
    }

    void RenderSystem::render_symbioses(
            yli::ontology::GenericMasterModule& master,
            const yli::ontology::Scene* const scene) const
    {
        yli::render::render_apprentices<yli::ontology::GenericMasterModule&, yli::ontology::Symbiosis*>(master, scene);
    }

    void RenderSystem::render_holobionts(
            yli::ontology::GenericMasterModule& master,
            const yli::ontology::Scene* const scene) const
    {
        yli::render::render_apprentices<yli::ontology::GenericMasterModule&, yli::ontology::Holobiont*>(
                master,
                scene);
    }

    void RenderSystem::render_bionts(yli::ontology::GenericParentModule& parent) const
    {
        yli::render::render_children<yli::ontology::GenericParentModule&, yli::ontology::Biont*>(parent);
    }

    void RenderSystem::render_shapeshifter_sequences(
            yli::ontology::GenericParentModule& parent,
            const yli::ontology::Scene* const scene) const
    {
        yli::render::render_children_of_given_scene_or_of_all_scenes<yli::ontology::GenericParentModule&, yli::ontology::ShapeshifterSequence*>(
                parent,
                scene);
    }

    void RenderSystem::render_text_2ds(yli::ontology::GenericParentModule& parent) const
    {
        yli::render::render_children<yli::ontology::GenericParentModule&, yli::ontology::Text2d*>(parent);
    }

    void RenderSystem::render_consoles(yli::ontology::GenericMasterModule& master) const
    {
        yli::render::render_apprentices<yli::ontology::GenericMasterModule&, yli::ontology::Console*>(
                master,
                nullptr); // `Console`s are rendered in all `Scene`s.
    }

    void RenderSystem::render_vector_fonts(
            yli::ontology::GenericParentModule& parent,
            const yli::ontology::Scene* const scene) const
    {
        yli::render::render_children_of_given_scene_or_of_all_scenes<yli::ontology::GenericParentModule&, yli::ontology::VectorFont*>(
                parent,
                scene);
    }

    void RenderSystem::render_glyph(
            yli::ontology::Glyph* const glyph,
            const yli::ontology::Scene* const scene) const
    {
        yli::render::render_model<yli::ontology::GenericMasterModule&, yli::ontology::Object*>(
                glyph->mesh,
                *(glyph->get_renderables_container()),
                scene);
    }

    void RenderSystem::render_glyphs(
            yli::ontology::GenericParentModule& parent,
            const yli::ontology::Scene* const scene) const
    {
        yli::render::render_children_of_given_scene_or_of_all_scenes<yli::ontology::GenericParentModule&, yli::ontology::Glyph*>(
                parent,
                scene);
    }

    void RenderSystem::render_compute_tasks(
            yli::ontology::GenericParentModule& parent,
            const yli::ontology::Scene* const scene) const
    {
        yli::render::render_children_of_given_scene_or_of_all_scenes<yli::ontology::GenericParentModule&, yli::ontology::ComputeTask*>(
                parent,
                scene);
    }
}
