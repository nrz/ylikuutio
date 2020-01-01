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

#ifndef __SYMBIOSIS_STRUCT_HPP_INCLUDED
#define __SYMBIOSIS_STRUCT_HPP_INCLUDED

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <string>   // std::string

namespace yli
{
    namespace ontology
    {
        class Shader;

        struct SymbiosisStruct
        {
            SymbiosisStruct()
                : triangulation_type("bilinear_interpolation"),
                light_position(glm::vec3(0.0f, 0.0f, 0.0f)),
                parent(nullptr),
                opengl_in_use(true)
            {
                // constructor.
            }

            std::string model_filename;     // filename of the symbiosis model file.
            std::string model_file_format;  // type of the symbiosis model file.
            std::string triangulation_type; // `"bilinear_interpolation"`, `"southwest_northeast_edges"`, `"southeast_northwest_edges"`.
            glm::vec3 light_position;       // light position.
            yli::ontology::Shader* parent;  // pointer to the `Shader`.
            bool opengl_in_use;             // If `opengl_in_use` is `false, then no OpenGL-specific code shall be executed.
        };
    }
}

#endif
