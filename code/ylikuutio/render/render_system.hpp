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

#ifndef YLIKUUTIO_RENDER_RENDER_SYSTEM_HPP_INCLUDED
#define YLIKUUTIO_RENDER_RENDER_SYSTEM_HPP_INCLUDED

#include "code/ylikuutio/sdl/ylikuutio_sdl.hpp"

// Include standard headers
#include <cstdint>  // std::int32_t, std::uint32_t
#include <string>   // std::string

struct SDL_Window;

namespace yli::ontology
{
        class Entity;
        class Universe;
        class Scene;
        class SymbiontSpecies;
        class Glyph;
        class GenericParentModule;
        class ParentOfPipelinesModule;
        class GenericMasterModule;
        class ApprenticeModule;
}

namespace yli::render
{
        struct RenderSystemStruct;
        struct RenderStruct;

        class RenderSystem final
        {
        public:
                RenderSystem(ontology::Universe& universe, const RenderSystemStruct& render_system_struct);

                RenderSystem(const RenderSystem&) = delete; // Delete copy constructor.
                RenderSystem& operator=(const RenderSystem&) = delete; // Delete copy assignment.

                ~RenderSystem() = default;

                void create_context_and_make_it_current();

                [[nodiscard]] bool setup_context(SDL_Window* window) const;

                [[nodiscard]] bool setup_context() const;

                static void set_swap_interval(std::int32_t interval);

                static void clear_color_and_depth_buffers();

                void restore_onscreen_rendering(std::uint32_t window_width, std::uint32_t window_height) const;

                void set_opengl_background_color() const;

                static void adjust_opengl_viewport(std::uint32_t window_width, std::uint32_t window_height);

                // This function renders everything.
                static void render(const RenderStruct& render_struct);

                void render_pipelines_of_ecosystems(ontology::GenericParentModule& parent,
                                                    const ontology::Scene* scene) const;

                static void render_pipelines_of_an_ecosystem(ontology::ParentOfPipelinesModule& parent,
                                                             const ontology::Scene* scene);

                static void render_pipelines(ontology::ParentOfPipelinesModule& parent, const ontology::Scene* scene);

                static void render_materials(
                        ontology::GenericMasterModule& master,
                        const ontology::Scene* scene);

                static void render_species(
                        ontology::GenericMasterModule& master,
                        const ontology::Scene* scene);

                static void render_symbioses(
                        ontology::GenericMasterModule& master,
                        const ontology::Scene* scene);

                static void render_holobionts(
                        yli::ontology::GenericMasterModule& master,
                        const yli::ontology::Scene* scene);

                static void render_bionts(ontology::GenericParentModule& parent);

                static void render_shapeshifter_sequences(
                        ontology::GenericParentModule& parent,
                        const ontology::Scene* scene);

                static void render_text_2ds(ontology::GenericParentModule& parent);

                static void render_consoles(ontology::GenericMasterModule& master);

                static void render_vector_fonts(
                        ontology::GenericParentModule& parent,
                        const ontology::Scene* scene);

                static void render_glyph(
                        ontology::Glyph* glyph,
                        const ontology::Scene* scene);

                static void render_glyphs(
                        ontology::GenericParentModule& parent,
                        const ontology::Scene* scene);

                static void render_compute_tasks(
                        ontology::GenericParentModule& parent,
                        const ontology::Scene* scene);

        private:
                ontology::Universe& universe;

                SDL_GLContext context { nullptr };
                SDL_Window* hidden_sdl_window { nullptr };
                std::string hidden_window_title;
                std::uint32_t hidden_window_width { 0 };
                std::uint32_t hidden_window_height { 0 };
                bool is_hidden_window_fullscreen { false };

                float background_red { 0.0f };
                float background_green { 0.0f };
                float background_blue { 0.0f };
                float background_alpha { 0.0f };
        };
}

#endif
