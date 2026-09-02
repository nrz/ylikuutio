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

#ifndef YLIKUUTIO_LOAD_FBX_MATERIAL_HPP_INCLUDED
#define YLIKUUTIO_LOAD_FBX_MATERIAL_HPP_INCLUDED

#include "fbx_texture.hpp"

namespace yli::load
{
    struct FbxMaterial
    {
        bool has_alpha { false };
        bool has_metallic { false };
        bool has_specular { false };
        bool cast_shadows { false };
        FbxTexture base_factor {};
        FbxTexture base_color {};
        FbxTexture specular_factor {};
        FbxTexture specular_color {};
        FbxTexture roughness {};
        FbxTexture metallic {};
        FbxTexture emission_factor {};
        FbxTexture emission_color {};
    };
}

#endif
