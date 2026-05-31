// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2026 Antti Nuortimo.
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
#include "code/ylikuutio/ontology/universe.hpp"
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
#include <cstdint>  // std::int32_t, std::uint32_t
#include <iostream> // std::cout, std::cerr

namespace yli::render
{
    RenderSystem::RenderSystem(ontology::Universe* const universe, const RenderSystemStruct& render_system_struct)
        : universe { universe },
          hidden_window_title { render_system_struct.hidden_window_title },
          hidden_window_width { universe != nullptr ? universe->get_window_width() : 0 },
          hidden_window_height { universe != nullptr ? universe->get_window_height() : 0 },
          is_hidden_window_fullscreen { render_system_struct.is_hidden_window_fullscreen }
    {
        // Open a window and create its OpenGL context.
        std::cout << "Opening a window and creating its OpenGL context...\n";

        if (universe == nullptr)
        {
            std::cerr << "ERROR: `RenderSystem::RenderSystem`: `universe` is `nullptr`!\n";
            return;
        }

        if (!universe->display_mode)
        {
            std::cerr << "ERROR: `RenderSystem::RenderSystem`: `!universe->display_mode` is `std::nullopt`!\n";
            return;
        }

        this->hidden_sdl_window = sdl::create_hidden_window(
            universe->display_mode->displayID,
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
            set_swap_interval(0);

            // Initialize GLEW.
            opengl::init_glew();

            input::disable_cursor();

            // Enable depth test.
            opengl::enable_depth_test();
            // Accept fragment if it is closer to the camera than the former one.
            opengl::set_depth_func_to_less();

            // Cull triangles whose normal is not towards the camera.
            opengl::cull_triangles();
        }
        else
        {
            std::cerr << "Hidden SDL window could not be created!\n";
        }
    }

    void RenderSystem::create_context_and_make_it_current()
    {
        std::cout << "Creating OpenGL context and making it current...\n";
        this->context = sdl::create_context(this->hidden_sdl_window);
    }

    [[nodiscard]] bool RenderSystem::setup_context(SDL_Window* window) const
    {
        if (this->context != nullptr)
        {
            if (sdl::make_context_current(window, this->context))
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

    [[nodiscard]] bool RenderSystem::setup_context() const
    {
        if (this->context != nullptr)
        {
            return sdl::make_context_current(this->hidden_sdl_window, this->context);
        }

        return false; // Fail.
    }

    void RenderSystem::set_swap_interval(const std::int32_t interval)
    {
        if (!sdl::set_swap_interval(static_cast<int>(interval)))
        {
            std::cerr << "ERROR: `RenderSystem::set_swap_interval`: setting swap interval failed!\n";
        }
    }

    void RenderSystem::clear_color_and_depth_buffers()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RenderSystem::restore_onscreen_rendering(const std::uint32_t window_width,
                                                  const std::uint32_t window_height) const
    {
        // Bind the default framebuffer for on-screen rendering.
        opengl::bind_gl_framebuffer(0);

        // Set background color for the default framebuffer.
        this->set_opengl_background_color();

        // Clear the default framebuffer.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Adjust viewport for the default framebuffer.
        adjust_opengl_viewport(window_width, window_height);
    }

    void RenderSystem::set_opengl_background_color() const
    {
        opengl::set_background_color(
            this->background_red,
            this->background_green,
            this->background_blue,
            this->background_alpha);
    }

    void RenderSystem::adjust_opengl_viewport(const std::uint32_t window_width, const std::uint32_t window_height)
    {
        if (window_width <= std::numeric_limits<GLsizei>::max() &&
            window_height <= std::numeric_limits<GLsizei>::max()) [[likely]]
        {
            glViewport(0, 0, window_width, window_height);
        }
    }

    void RenderSystem::render(const RenderStruct& render_struct)
    {
        if (render_struct.scene != nullptr) [[likely]]
        {
            render_struct.scene->render();
        }

        if (render_struct.should_change_depth_test) [[likely]]
        {
            opengl::disable_depth_test();
        }

        if (render_struct.parent_of_font_2ds != nullptr) [[likely]]
        {
            render_children<ontology::GenericParentModule&, ontology::Font2d*>(*render_struct.parent_of_font_2ds);
        }

        if (render_struct.should_change_depth_test) [[likely]]
        {
            opengl::enable_depth_test();
        }

        // Swap buffers.
        SDL_GL_SwapWindow(render_struct.window);
    }

    void RenderSystem::render_pipelines_of_ecosystems(ontology::GenericParentModule& parent,
                                                      const ontology::Scene* const scene) const
    {
        for (auto it = parent.begin(); it != parent.end(); ++it)
        {
            ontology::Ecosystem* ecosystem = static_cast<ontology::Ecosystem*>(*it);

            if (ecosystem != nullptr && ecosystem->should_render) [[likely]]
            {
                render_pipelines_of_an_ecosystem(ecosystem->parent_of_pipelines, scene);
            }
        }
    }

    void RenderSystem::render_pipelines_of_an_ecosystem(ontology::ParentOfPipelinesModule& parent,
                                                        const ontology::Scene* const scene)
    {
        render_children_of_given_scene_or_of_all_scenes<
            ontology::ParentOfPipelinesModule&,
            ontology::Pipeline*>(
            parent,
            scene);
    }

    void RenderSystem::render_pipelines(ontology::ParentOfPipelinesModule& parent, const ontology::Scene* const scene)
    {
        render_children_of_given_scene_or_of_all_scenes<ontology::ParentOfPipelinesModule&, ontology::Pipeline*>(
            parent,
            scene);
    }

    void RenderSystem::render_materials(
        ontology::GenericMasterModule& master,
        const ontology::Scene* const scene)
    {
        render_apprentices<ontology::GenericMasterModule&, ontology::Material*>(master, scene);
    }

    void RenderSystem::render_species(
        ontology::GenericMasterModule& master,
        const ontology::Scene* const scene)
    {
        render_apprentices<ontology::GenericMasterModule&, ontology::Species*>(master, scene);
    }

    void RenderSystem::render_symbioses(
        ontology::GenericMasterModule& master,
        const ontology::Scene* const scene)
    {
        render_apprentices<ontology::GenericMasterModule&, ontology::Symbiosis*>(master, scene);
    }

    void RenderSystem::render_holobionts(
        ontology::GenericMasterModule& master,
        const ontology::Scene* const scene)
    {
        render_apprentices<ontology::GenericMasterModule&, ontology::Holobiont*>(
            master,
            scene);
    }

    void RenderSystem::render_bionts(ontology::GenericParentModule& parent)
    {
        render_children<ontology::GenericParentModule&, ontology::Biont*>(parent);
    }

    void RenderSystem::render_shapeshifter_sequences(
        ontology::GenericParentModule& parent,
        const ontology::Scene* const scene)
    {
        render_children_of_given_scene_or_of_all_scenes<
            ontology::GenericParentModule&,
            ontology::ShapeshifterSequence*>(
            parent,
            scene);
    }

    void RenderSystem::render_text_2ds(ontology::GenericParentModule& parent)
    {
        render_children<ontology::GenericParentModule&, ontology::Text2d*>(parent);
    }

    void RenderSystem::render_consoles(ontology::GenericMasterModule& master)
    {
        render_apprentices<ontology::GenericMasterModule&, ontology::Console*>(
            master,
            nullptr); // `Console`s are rendered in all `Scene`s.
    }

    void RenderSystem::render_vector_fonts(
        ontology::GenericParentModule& parent,
        const ontology::Scene* const scene)
    {
        render_children_of_given_scene_or_of_all_scenes<ontology::GenericParentModule&, ontology::VectorFont*>(
            parent,
            scene);
    }

    void RenderSystem::render_glyph(
        ontology::Glyph* const glyph,
        const ontology::Scene* const scene)
    {
        render_model<ontology::GenericMasterModule&, ontology::Object*>(
            glyph->mesh,
            *(glyph->get_renderables_container()),
            scene);
    }

    void RenderSystem::render_glyphs(
        ontology::GenericParentModule& parent,
        const ontology::Scene* const scene)
    {
        render_children_of_given_scene_or_of_all_scenes<ontology::GenericParentModule&, ontology::Glyph*>(
            parent,
            scene);
    }

    void RenderSystem::render_compute_tasks(
        ontology::GenericParentModule& parent,
        const ontology::Scene* const scene)
    {
        render_children_of_given_scene_or_of_all_scenes<ontology::GenericParentModule&, ontology::ComputeTask*>(
            parent,
            scene);
    }
}
