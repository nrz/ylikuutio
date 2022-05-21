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

#include "render_system.hpp"
#include "render_model.hpp"
#include "render_templates.hpp"
#include "render_system_struct.hpp"
#include "render_struct.hpp"
#include "code/ylikuutio/ontology/generic_parent_module.hpp"
#include "code/ylikuutio/ontology/parent_of_shaders_module.hpp"
#include "code/ylikuutio/ontology/entity.hpp"
#include "code/ylikuutio/ontology/ecosystem.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/shader.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/symbiosis.hpp"
#include "code/ylikuutio/ontology/symbiont_species.hpp"
#include "code/ylikuutio/ontology/holobiont.hpp"
#include "code/ylikuutio/ontology/biont.hpp"
#include "code/ylikuutio/ontology/shapeshifter_sequence.hpp"
#include "code/ylikuutio/ontology/chunk_master.hpp"
#include "code/ylikuutio/ontology/chunk.hpp"
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
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

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
        // constructor.

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
            if (yli::opengl::init_glew())
            {
                std::cout << "GLEW initialization successful.\n";

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
                std::cerr << "GLEW initialization failed!\n";
            }
        }
        else
        {
            std::cerr << "Hidden SDL window could not be created!\n";
        }
    }

    RenderSystem::~RenderSystem()
    {
        // destructor.
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
        yli::sdl::set_swap_interval(static_cast<int>(interval));
    }

    void RenderSystem::restore_onscreen_rendering(const float window_width, const float window_height) const
    {
        // Bind the default framebuffer for on-screen rendering.
        yli::opengl::bind_gl_framebuffer(0);

        // Set background color for the default framebuffer.
        this->set_opengl_background_color();

        // Clear the default framebuffer.
        glClear(GL_COLOR_BUFFER_BIT);

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

    void RenderSystem::adjust_opengl_viewport(const float window_width, const float window_height) const
    {
        if (window_width >= 0 && window_width <= std::numeric_limits<GLsizei>::max() &&
                window_height >= 0 && window_height <= std::numeric_limits<GLsizei>::max())
        {
            glViewport(0, 0, window_width, window_height);
        }
    }

    void RenderSystem::render(const yli::render::RenderStruct& render_struct) const
    {
        if (render_struct.scene != nullptr)
        {
            render_struct.scene->render();
        }

        if (render_struct.should_change_depth_test)
        {
            yli::opengl::disable_depth_test();
        }

        if (render_struct.parent_of_font_2ds != nullptr)
        {
            yli::render::render_children<yli::ontology::GenericParentModule&, yli::ontology::Entity*, yli::ontology::Font2D*>(*render_struct.parent_of_font_2ds);
        }

        if (render_struct.should_change_depth_test)
        {
            yli::opengl::enable_depth_test();
        }

        // Swap buffers.
        SDL_GL_SwapWindow(render_struct.window);
    }

    void RenderSystem::render_shaders_of_ecosystems(yli::ontology::GenericParentModule& parent, const yli::ontology::Scene* const scene) const
    {
        for (auto it = parent.begin(); it != parent.end(); ++it)
        {
            yli::ontology::Ecosystem* ecosystem = static_cast<yli::ontology::Ecosystem*>(*it);

            if (ecosystem != nullptr && ecosystem->should_be_rendered)
            {
                this->render_shaders_of_an_ecosystem(ecosystem->parent_of_shaders, scene);
            }
        }
    }

    void RenderSystem::render_shaders_of_an_ecosystem(yli::ontology::ParentOfShadersModule& parent, const yli::ontology::Scene* const scene) const
    {
        yli::render::render_children_of_given_scene_or_of_all_scenes<
            yli::ontology::ParentOfShadersModule&,
            yli::ontology::Entity*,
            yli::ontology::Shader*>(
                parent,
                scene);
    }

    void RenderSystem::render_shaders(yli::ontology::ParentOfShadersModule& parent) const
    {
        yli::render::render_children<yli::ontology::ParentOfShadersModule&, yli::ontology::Entity*, yli::ontology::Shader*>(parent);
    }

    void RenderSystem::render_materials_of_ecosystems(yli::ontology::GenericParentModule& parent, const yli::ontology::Scene* const scene) const
    {
        for (auto it = parent.begin(); it != parent.end(); ++it)
        {
            yli::ontology::Ecosystem* ecosystem = static_cast<yli::ontology::Ecosystem*>(*it);

            if (ecosystem != nullptr && ecosystem->should_be_rendered)
            {
                this->render_materials_of_an_ecosystem(ecosystem->parent_of_materials, scene);
            }
        }
    }

    void RenderSystem::render_materials_of_an_ecosystem(yli::ontology::GenericParentModule& parent, const yli::ontology::Scene* const scene) const
    {
        yli::render::render_children_of_given_scene_or_of_all_scenes<
            yli::ontology::GenericParentModule&,
            yli::ontology::Entity*,
            yli::ontology::Material*>(
                parent,
                scene);
    }

    void RenderSystem::render_materials(std::vector<yli::ontology::ApprenticeModule*>& material_apprentice_pointer_vector) const
    {
        yli::render::render_apprentices<yli::ontology::Material*>(material_apprentice_pointer_vector);
    }

    void RenderSystem::render_species(std::vector<yli::ontology::ApprenticeModule*>& species_apprentice_pointer_vector) const
    {
        yli::render::render_apprentices<yli::ontology::Species*>(species_apprentice_pointer_vector);
    }

    void RenderSystem::render_symbioses(std::vector<yli::ontology::ApprenticeModule*>& symbiosis_apprentice_pointer_vector) const
    {
        yli::render::render_apprentices<yli::ontology::Symbiosis*>(symbiosis_apprentice_pointer_vector);
    }

    void RenderSystem::render_symbiont_species(yli::ontology::SymbiontSpecies* const symbiont_species) const
    {
        yli::render::render_model<yli::ontology::GenericMasterModule&, yli::ontology::Entity*, yli::ontology::Object*>(symbiont_species->mesh, *(symbiont_species->get_renderables_container()));
    }

    void RenderSystem::render_symbiont_species(std::vector<yli::ontology::Entity*>& symbiont_species_pointer_vector) const
    {
        yli::render::render_children<std::vector<yli::ontology::Entity*>, yli::ontology::Entity*, yli::ontology::SymbiontSpecies*>(symbiont_species_pointer_vector);
    }

    void RenderSystem::render_holobionts(std::vector<yli::ontology::Entity*>& holobiont_pointer_vector) const
    {
        yli::render::render_children<std::vector<yli::ontology::Entity*>, yli::ontology::Entity*, yli::ontology::Holobiont*>(holobiont_pointer_vector);
    }

    void RenderSystem::render_bionts(std::vector<yli::ontology::Entity*>& biont_pointer_vector) const
    {
        yli::render::render_children<std::vector<yli::ontology::Entity*>, yli::ontology::Entity*, yli::ontology::Biont*>(biont_pointer_vector);
    }

    void RenderSystem::render_shapeshifter_sequences(std::vector<yli::ontology::Entity*>& shapeshifter_sequence_pointer_vector) const
    {
        yli::render::render_children<std::vector<yli::ontology::Entity*>, yli::ontology::Entity*, yli::ontology::ShapeshifterSequence*>(shapeshifter_sequence_pointer_vector);
    }

    void RenderSystem::render_chunk_masters(yli::ontology::GenericParentModule& parent) const
    {
        yli::render::render_children<yli::ontology::GenericParentModule&, yli::ontology::Entity*, yli::ontology::ChunkMaster*>(parent);
    }

    void RenderSystem::render_chunks(std::vector<yli::ontology::Entity*>& chunk_pointer_vector) const
    {
        yli::render::render_children<std::vector<yli::ontology::Entity*>, yli::ontology::Entity*, yli::ontology::Chunk*>(chunk_pointer_vector);
        glDisable(GL_BLEND);
    }

    void RenderSystem::render_text_2ds(std::vector<yli::ontology::Entity*>& text_2d_pointer_vector) const
    {
        yli::render::render_children<std::vector<yli::ontology::Entity*>, yli::ontology::Entity*, yli::ontology::Text2D*>(text_2d_pointer_vector);
    }

    void RenderSystem::render_consoles(std::vector<yli::ontology::ApprenticeModule*>& console_apprentice_pointer_vector) const
    {
        yli::render::render_apprentices<yli::ontology::Console*>(console_apprentice_pointer_vector);
    }

    void RenderSystem::render_vector_fonts(yli::ontology::GenericParentModule& parent) const
    {
        yli::render::render_children<yli::ontology::GenericParentModule&, yli::ontology::Entity*, yli::ontology::VectorFont*>(parent);
    }

    void RenderSystem::render_glyph(yli::ontology::Glyph* const glyph) const
    {
        yli::render::render_model<yli::ontology::GenericMasterModule&, yli::ontology::Entity*, yli::ontology::Object*>(glyph->mesh, *(glyph->get_renderables_container()));
    }

    void RenderSystem::render_glyphs(std::vector<yli::ontology::Entity*>& glyph_pointer_vector) const
    {
        yli::render::render_children<std::vector<yli::ontology::Entity*>, yli::ontology::Entity*, yli::ontology::Glyph*>(glyph_pointer_vector);
    }

    void RenderSystem::render_compute_tasks(yli::ontology::GenericParentModule& parent) const
    {
        yli::render::render_children<yli::ontology::GenericParentModule&, yli::ontology::Entity*, yli::ontology::ComputeTask*>(parent);
    }
}
