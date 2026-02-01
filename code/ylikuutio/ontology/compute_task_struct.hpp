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

#ifndef YLIKUUTIO_ONTOLOGY_COMPUTE_TASK_STRUCT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_COMPUTE_TASK_STRUCT_HPP_INCLUDED

#include "entity_struct.hpp"
#include "request.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <cstddef>  // std::size_t
#include <limits>   // std::numeric_limits
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <utility>  // std::move

namespace yli::ontology
{
    class Pipeline;

    struct ComputeTaskStruct : public EntityStruct
    {
        explicit ComputeTaskStruct(Request<Pipeline>&& pipeline_parent)
            : pipeline_parent { std::move(pipeline_parent) }
        {
        }

        Request<Pipeline> pipeline_parent {};
        std::string texture_file_format; // Type of the texture file. supported file formats so far: `"png"`/`"PNG"`, `"csv"`/`"CSV"`.
        std::string texture_filename;    // Filename of the model file.
        std::string output_filename;     // Filename of the output file.
        yli::data::AnyValue left_filler_vector_any_value;
        yli::data::AnyValue right_filler_vector_any_value;
        std::size_t n_max_iterations   { 1 }; // By default execute GLSL pipeline exactly once (do not iterate further).
        std::size_t compute_taskID     { std::numeric_limits<std::size_t>::max() };
        uint32_t texture_width         { 0 };
        uint32_t texture_height        { 0 };
        uint32_t n_index_characters    { 4 }; // For intermediate results' filenames.
        GLenum format                  { GL_RGB };
        GLenum internal_format         { GL_INVALID_ENUM };
        GLenum output_format           { GL_INVALID_ENUM };
        GLenum type                    { GL_UNSIGNED_BYTE };
        bool should_save_intermediate_results    { false };
        bool should_flip_texture                 { true };
    };
}

#endif
