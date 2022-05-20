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

#ifndef __YLIKUUTIO_ONTOLOGY_SHAPESHIFTER_FORM_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_SHAPESHIFTER_FORM_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "mesh_module.hpp"

// Include standard headers
#include <cstddef>  // std::size_t

// `ShapeshifterForm` is a `Model` and a part of `ShapeshifterTransformation`.

namespace yli::ontology
{
    class GenericParentModule;
    class Universe;
    class Scene;
    class ShapeshifterTransformation;
    struct ModelStruct;

    class ShapeshifterForm: public yli::ontology::Entity
    {
        public:
            ShapeshifterForm(
                    yli::ontology::Universe& universe,
                    const yli::ontology::ModelStruct& model_struct,
                    yli::ontology::GenericParentModule* const shapeshifter_transformation_parent_module);

            // destructor.
            virtual ~ShapeshifterForm();

            yli::ontology::Entity* get_parent() const override;

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
