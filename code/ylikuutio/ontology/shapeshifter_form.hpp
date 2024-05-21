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

#ifndef YLIKUUTIO_ONTOLOGY_SHAPESHIFTER_FORM_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_SHAPESHIFTER_FORM_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "mesh_module.hpp"

// Include standard headers
#include <cstddef>  // std::size_t

// `ShapeshifterForm` is a `Model` and a part of `ShapeshifterTransformation`.

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
    class GenericParentModule;
    class Universe;
    class Scene;
    class ShapeshifterTransformation;
    struct ModelStruct;

    class ShapeshifterForm final : public yli::ontology::Entity
    {
        private:
            ShapeshifterForm(
                    yli::core::Application& application,
                    yli::ontology::Universe& universe,
                    const yli::ontology::ModelStruct& model_struct,
                    yli::ontology::GenericParentModule* const shapeshifter_transformation_parent_module);

            ~ShapeshifterForm() = default;

        public:
            yli::ontology::Entity* get_parent() const override;

            template<typename T1, std::size_t DataSize>
                friend class yli::memory::MemoryStorage;

        private:
            yli::ontology::ChildModule child_of_shapeshifter_transformation;
            yli::ontology::MeshModule mesh;

        public:
            yli::ontology::Scene* get_scene() const override;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            void render();
    };
}

#endif
