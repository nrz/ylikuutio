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

#include "setup_fbx_texture.hpp"
#include "fbx_texture.hpp"

// Include standard headers
#include <iostream> // std::cerr

namespace yli::load
{
    bool setup_fbx_texture(FbxTexture& texture, const ufbx_material_map& map)
    {
        if (map.has_value)
        {
            texture.value = { map.value_vec3.x, map.value_vec3.y, map.value_vec3.z };
        }

        if (map.texture == nullptr)
        {
            std::cout << "ERROR: `yli::load::setup_fbx_texture`: `map.texture` is `nullptr`!\n";
            texture.filename = ""; // Ensure filename is initialized to an empty string.
            return false;
        }

        texture.filename = map.texture->relative_filename.data;

        // TODO: implement the rest of FBX texture setup!

        return true;
    }
}
