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

#ifndef YLIKUUTIO_ONTOLOGY_SYMBIONT_MATERIAL_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_SYMBIONT_MATERIAL_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "generic_parent_module.hpp"
#include "texture_module.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <cstddef>  // std::size_t

namespace yli::core
{
    class Application;
}

namespace yli::memory
{
    template<typename T1, std::size_t DataSize>
        class MemoryStorage;
}

namespace yli::ontology
{
    class Universe;
    class Scene;
    class Pipeline;
    struct SymbiontMaterialStruct;

    class SymbiontMaterial final : public Entity
    {
        private:
            SymbiontMaterial(
                    yli::core::Application& application,
                    Universe& universe,
                    const SymbiontMaterialStruct& symbiont_material_struct,
                    GenericParentModule* const symbiosis_parent_module); // Parent is a `Symbiosis`.

            ~SymbiontMaterial() = default;

        public:
            SymbiontMaterial(const SymbiontMaterial&) = delete;            // Delete copy constructor.
            SymbiontMaterial& operator=(const SymbiontMaterial&) = delete; // Delete copy assignment.

            Scene* get_scene() const override;
            Entity* get_parent() const override;
            Pipeline* get_pipeline() const;

            GLint get_openGL_textureID() const;

            template<typename T1, std::size_t DataSize>
                friend class yli::memory::MemoryStorage;

            ChildModule child_of_symbiosis;
            GenericParentModule parent_of_symbiont_species;
            TextureModule texture;

        protected:
            GLuint opengl_texture_id { 0 }; // Texture ID, returned by `glGetUniformLocation(program_id, "texture_sampler")`. Dummy value.

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;
    };
}

#endif
