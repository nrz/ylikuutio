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

// Include standard headers
#include <vector>  // std::vector

namespace yli::ontology
{
    class Universe;
}

namespace yli::render
{
    RenderMaster::RenderMaster(yli::ontology::Universe* const universe)
    {
        // constructor.
        this->universe = universe;
    }

    RenderMaster::~RenderMaster()
    {
        // destructor.
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
