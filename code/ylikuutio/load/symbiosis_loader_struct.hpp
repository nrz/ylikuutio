// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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

#ifndef YLIKUUTIO_ONTOLOGY_SYMBIOSIS_LOADER_STRUCT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_SYMBIOSIS_LOADER_STRUCT_HPP_INCLUDED

// Include standard headers
#include <string> // std::string

namespace yli::load
{
    class Pipeline;

    struct SymbiosisLoaderStruct
    {
        SymbiosisLoaderStruct(const std::string& model_filename, const std::string& model_file_format)
            : model_filename  { model_filename },
            model_file_format { model_file_format }
        {
        }

        const std::string model_filename;    // Filename of the model file.
        const std::string model_file_format; // Type of the model file. Supported file formats so far:
                                             // `"fbx"`/`"FBX"` - FBX model.
    };
}

#endif
