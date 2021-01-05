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

#ifndef __YLIKUUTIO_ONTOLOGY_MATERIAL_STRUCT_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_MATERIAL_STRUCT_HPP_INCLUDED

#include "entity_struct.hpp"

// Include standard headers
#include <string>   // std::string

namespace ofbx
{
    // OpenFBX.
    struct Texture;
}

namespace yli::ontology
{
    class Shader;
    class Symbiosis;

    struct MaterialStruct: public yli::ontology::EntityStruct
    {
        MaterialStruct()
            : shader(nullptr),
            symbiosis(nullptr),
            ofbx_texture(nullptr),
            is_symbiont_material(false)
        {
            // constructor.
        }

        std::string texture_file_format;     // Type of the texture file. supported file formats so far: `"bmp"`/`"BMP"`/`"png"`/`"PNG"`.
        std::string texture_filename;        // Filename of the model file.
        yli::ontology::Shader* shader;       // Pointer to `Shader`.
        yli::ontology::Symbiosis* symbiosis; // Pointer to `Symbiosis`.
        const ofbx::Texture* ofbx_texture;   // For `SymbiontMaterial`s.
        bool is_symbiont_material;
    };
}

#endif
