// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
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

#ifndef __YLIKUUTIO_RENDER_RENDER_MASTER_HPP_INCLUDED
#define __YLIKUUTIO_RENDER_RENDER_MASTER_HPP_INCLUDED

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

struct SDL_Window;

typedef void* SDL_GLContext;

namespace yli::ontology
{
    class Entity;
    class Universe;
    class Shader;
    class SymbiontSpecies;
    class Glyph;
    class ParentModule;
    class ApprenticeModule;
}

namespace yli::render
{
    struct RenderMasterStruct;
    struct RenderStruct;

    class RenderMaster
    {
        public:
            // constructor.
            RenderMaster(yli::ontology::Universe* const universe, const yli::render::RenderMasterStruct& render_master_struct);

            RenderMaster(const RenderMaster&) = delete;            // Delete copy constructor.
            RenderMaster& operator=(const RenderMaster&) = delete; // Delete copy assignment.

            // destructor.
            ~RenderMaster();

            void create_context_and_make_it_current();
            void setup_context(SDL_Window* window);
            void setup_context();
            void set_swap_interval(const int32_t interval);
            void restore_onscreen_rendering(const float window_width, const float window_height) const;
            void set_opengl_background_color() const;
            void adjust_opengl_viewport(const float window_width, const float window_height) const;

            // This function renders everything.
            void render(const yli::render::RenderStruct& render_struct) const;

            void render_shaders(std::vector<yli::ontology::Shader*>& shader_pointer_vector) const;
            void render_materials(std::vector<yli::ontology::ApprenticeModule*>& material_apprentices_pointer_vector) const;
            void render_species(std::vector<yli::ontology::ApprenticeModule*>& species_apprentice_pointer_vector) const;
            void render_symbioses(yli::ontology::ParentModule& parent) const;
            void render_symbiont_species(yli::ontology::SymbiontSpecies* const symbiont_species) const;
            void render_symbiont_species(std::vector<yli::ontology::Entity*>& symbiont_species_pointer_vector) const;
            void render_holobionts(std::vector<yli::ontology::Entity*>& holobiont_pointer_vector) const;
            void render_bionts(std::vector<yli::ontology::Entity*>& biont_pointer_vector) const;
            void render_shapeshifter_sequences(std::vector<yli::ontology::Entity*>& shapeshifter_sequence_pointer_vector) const;
            void render_chunk_masters(yli::ontology::ParentModule& parent) const;
            void render_chunks(std::vector<yli::ontology::Entity*>& chunk_pointer_vector) const;
            void render_text_2ds(std::vector<yli::ontology::Entity*>& text_2d_pointer_vector) const;
            void render_vector_fonts(yli::ontology::ParentModule& parent) const;
            void render_glyph(yli::ontology::Glyph* const glyph) const;
            void render_glyphs(std::vector<yli::ontology::Entity*>& glyph_pointer_vector) const;
            void render_compute_tasks(yli::ontology::ParentModule& parent) const;

        private:
            yli::ontology::Universe* const universe { nullptr };

            SDL_GLContext context { nullptr };
            SDL_Window* hidden_sdl_window { nullptr };
            std::string hidden_window_title;
            uint32_t hidden_window_width     { 0 };
            uint32_t hidden_window_height    { 0 };
            bool is_hidden_window_fullscreen { false };

            float background_red   { 0.0f };
            float background_green { 0.0f };
            float background_blue  { 0.0f };
            float background_alpha { 0.0f };
    };
}

#endif
