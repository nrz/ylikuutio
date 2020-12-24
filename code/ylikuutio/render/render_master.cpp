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

#include "render_master.hpp"
#include "render_species_or_glyph.hpp"
#include "render_templates.hpp"
#include "render_master_struct.hpp"
#include "render_struct.hpp"
#include "code/ylikuutio/ontology/entity.hpp"
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
#include "code/ylikuutio/ontology/chunk.hpp"
#include "code/ylikuutio/ontology/font2D.hpp"
#include "code/ylikuutio/ontology/text2D.hpp"
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
    RenderMaster::RenderMaster(yli::ontology::Universe* const universe, const yli::render::RenderMasterStruct& render_master_struct)
        : universe(universe),
        hidden_window_title(render_master_struct.hidden_window_title),
        hidden_window_width(render_master_struct.hidden_window_width),
        hidden_window_height(render_master_struct.hidden_window_height),
        is_hidden_window_fullscreen(render_master_struct.is_hidden_window_fullscreen)
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

    RenderMaster::~RenderMaster()
    {
        // destructor.
    }

    void RenderMaster::create_context_and_make_it_current()
    {
        std::cout << "Creating OpenGL context and making it current...\n";
        this->context = yli::sdl::create_context(this->hidden_sdl_window);
    }

    void RenderMaster::setup_context(SDL_Window* window)
    {
        if (this->context != nullptr)
        {
            yli::sdl::make_context_current(window, this->context);
        }
    }

    void RenderMaster::setup_context()
    {
        if (this->context != nullptr)
        {
            yli::sdl::make_context_current(this->hidden_sdl_window, this->context);
        }
    }

    void RenderMaster::set_swap_interval(const int32_t interval)
    {
        yli::sdl::set_swap_interval(static_cast<int>(interval));
    }

    void RenderMaster::restore_onscreen_rendering(const float window_width, const float window_height) const
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

    void RenderMaster::set_opengl_background_color() const
    {
        yli::opengl::set_background_color(
                this->background_red,
                this->background_green,
                this->background_blue,
                this->background_alpha);
    }

    void RenderMaster::adjust_opengl_viewport(const float window_width, const float window_height) const
    {
        if (window_width <= std::numeric_limits<GLsizei>::max() &&
                window_height <= std::numeric_limits<GLsizei>::max())
        {
            glViewport(0, 0, window_width, window_height);
        }
    }

    void RenderMaster::render(const yli::render::RenderStruct& render_struct) const
    {
        if (render_struct.scene != nullptr)
        {
            render_struct.scene->render();
        }

        if (render_struct.should_ylikuutio_change_depth_test)
        {
            yli::opengl::disable_depth_test();
        }

        if (render_struct.console != nullptr)
        {
            render_struct.console->render();
        }

        if (render_struct.font2D_pointer_vector != nullptr)
        {
            yli::render::render_children<yli::ontology::Entity*, yli::ontology::Font2D*>(*render_struct.font2D_pointer_vector);
        }

        if (render_struct.should_ylikuutio_change_depth_test)
        {
            yli::opengl::enable_depth_test();
        }

        // Swap buffers.
        SDL_GL_SwapWindow(render_struct.window);
    }

    void RenderMaster::render_shaders(std::vector<yli::ontology::Shader*>& shader_pointer_vector) const
    {
        yli::render::render_children<yli::ontology::Shader*, yli::ontology::Shader*>(shader_pointer_vector);
    }

    void RenderMaster::render_materials(std::vector<yli::ontology::Entity*>& material_pointer_vector) const
    {
        yli::render::render_children<yli::ontology::Entity*, yli::ontology::Material*>(material_pointer_vector);
    }

    void RenderMaster::render_species(std::vector<yli::ontology::Entity*>& species_pointer_vector) const
    {
        yli::render::render_children<yli::ontology::Entity*, yli::ontology::Species*>(species_pointer_vector);
    }

    void RenderMaster::render_symbioses(std::vector<yli::ontology::Entity*>& symbiosis_pointer_vector) const
    {
        yli::render::render_children<yli::ontology::Entity*, yli::ontology::Symbiosis*>(symbiosis_pointer_vector);
    }

    void RenderMaster::render_symbiont_species(yli::ontology::SymbiontSpecies* const symbiont_species) const
    {
        yli::render::render_species_or_glyph<yli::ontology::SymbiontSpecies*, yli::ontology::Entity*, yli::ontology::Object*>(symbiont_species);
    }

    void RenderMaster::render_symbiont_species(std::vector<yli::ontology::Entity*>& symbiont_species_pointer_vector) const
    {
        yli::render::render_children<yli::ontology::Entity*, yli::ontology::SymbiontSpecies*>(symbiont_species_pointer_vector);
    }

    void RenderMaster::render_holobionts(std::vector<yli::ontology::Entity*>& holobiont_pointer_vector) const
    {
        yli::render::render_children<yli::ontology::Entity*, yli::ontology::Holobiont*>(holobiont_pointer_vector);
    }

    void RenderMaster::render_bionts(std::vector<yli::ontology::Entity*>& biont_pointer_vector) const
    {
        yli::render::render_children<yli::ontology::Entity*, yli::ontology::Biont*>(biont_pointer_vector);
    }

    void RenderMaster::render_shapeshifter_sequences(std::vector<yli::ontology::Entity*>& shapeshifter_sequence_pointer_vector) const
    {
        yli::render::render_children<yli::ontology::Entity*, yli::ontology::ShapeshifterSequence*>(shapeshifter_sequence_pointer_vector);
    }

    void RenderMaster::render_chunk_masters(std::vector<yli::ontology::Entity*>& chunk_master_pointer_vector) const
    {
        yli::render::render_children<yli::ontology::Entity*, yli::ontology::ChunkMaster*>(chunk_master_pointer_vector);
    }

    void RenderMaster::render_chunks(std::vector<yli::ontology::Entity*>& chunk_pointer_vector) const
    {
        yli::render::render_children<yli::ontology::Entity*, yli::ontology::Chunk*>(chunk_pointer_vector);
    }

    void RenderMaster::render_text2Ds(std::vector<yli::ontology::Entity*>& text2D_pointer_vector) const
    {
        yli::render::render_children<yli::ontology::Entity*, yli::ontology::Text2D*>(text2D_pointer_vector);
        glDisable(GL_BLEND);
    }

    void RenderMaster::render_vector_fonts(std::vector<yli::ontology::Entity*>& vector_font_pointer_vector) const
    {
        yli::render::render_children<yli::ontology::Entity*, yli::ontology::VectorFont*>(vector_font_pointer_vector);
    }

    void RenderMaster::render_glyph(yli::ontology::Glyph* const glyph) const
    {
        yli::render::render_species_or_glyph<yli::ontology::Glyph*, yli::ontology::Entity*, yli::ontology::Object*>(glyph);
    }

    void RenderMaster::render_glyphs(std::vector<yli::ontology::Entity*>& glyph_pointer_vector) const
    {
        yli::render::render_children<yli::ontology::Entity*, yli::ontology::Glyph*>(glyph_pointer_vector);
    }

    void RenderMaster::render_compute_tasks(std::vector<yli::ontology::Entity*>& compute_task_pointer_vector) const
    {
        yli::render::render_children<yli::ontology::Entity*, yli::ontology::ComputeTask*>(compute_task_pointer_vector);
    }
}
