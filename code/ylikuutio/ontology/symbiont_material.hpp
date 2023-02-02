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

#ifndef YLIKUUTIO_ONTOLOGY_SYMBIONT_MATERIAL_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_SYMBIONT_MATERIAL_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "generic_parent_module.hpp"
#include "texture_module.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <cstddef>  // std::size_t

namespace yli::ontology
{
    class Universe;
    class Scene;
    class Pipeline;
    struct MaterialStruct;

    class SymbiontMaterial final : public yli::ontology::Entity
    {
        public:
            SymbiontMaterial(
                    yli::ontology::Universe& universe,
                    const yli::ontology::MaterialStruct& material_struct,
                    yli::ontology::GenericParentModule* const symbiosis_parent_module); // Parent is a `Symbiosis`.

            SymbiontMaterial(const SymbiontMaterial&) = delete;            // Delete copy constructor.
            SymbiontMaterial& operator=(const SymbiontMaterial&) = delete; // Delete copy assignment.

            // destructor.
            ~SymbiontMaterial() = default;

            yli::ontology::Scene* get_scene() const override;
            yli::ontology::Entity* get_parent() const override;
            yli::ontology::Pipeline* get_pipeline() const;

            GLint get_openGL_textureID() const;

            yli::ontology::ChildModule child_of_symbiosis;
            yli::ontology::GenericParentModule parent_of_symbiont_species;
            yli::ontology::TextureModule texture;

        protected:
            GLuint opengl_texture_id { 0 }; // Texture ID, returned by `glGetUniformLocation(program_id, "texture_sampler")`. Dummy value.

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;
    };
}

#endif
