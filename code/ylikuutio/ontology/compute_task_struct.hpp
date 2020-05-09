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

#ifndef __COMPUTE_TASK_STRUCT_HPP_INCLUDED
#define __COMPUTE_TASK_STRUCT_HPP_INCLUDED

#include "pre_iterate_callback.hpp"
#include "post_iterate_callback.hpp"
#include "code/ylikuutio/common/any_value.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <cstddef>  // std::size_t
#include <limits>   // std::numeric_limits
#include <memory>   // std::make_shared, std::shared_ptr
#include <string>   // std::string

namespace yli::callback
{
    class CallbackEngine;
}

namespace yli::ontology
{
    class Shader;

    struct ComputeTaskStruct
    {
        ComputeTaskStruct()
            : parent(nullptr),
            left_filler_vector_any_value(nullptr),
            right_filler_vector_any_value(nullptr),
            end_condition_callback_engine(nullptr),
            n_max_iterations(1),                                     // By default execute GLSL shader exactly once (do not iterate further).
            compute_taskID(std::numeric_limits<std::size_t>::max()), // `std::numeric_limits<std::size_t>::max()` means that `compute_taskID` is not defined.
            texture_width(0),
            texture_height(0),
            n_index_characters(4),
            format(GL_RGB),
            internal_format(GL_INVALID_ENUM), // If `internal_format` is left to `GL_INVALID_ENUM`, `format` is used as the internal format.
            output_format(GL_INVALID_ENUM),   // If `output_format` is left to `GL_INVALID_ENUM`, `format` is used as the output format.
            type(GL_UNSIGNED_BYTE),
            should_ylikuutio_save_intermediate_results(false),
            should_ylikuutio_flip_texture(true),
            preiterate_callback(nullptr),
            postiterate_callback(nullptr)
        {
            // constructor.
        }

        std::string texture_file_format; // Type of the texture file. supported file formats so far: `"bmp"`/`"BMP"`, `"csv"`/`"CSV"`.
        std::string texture_filename;    // Filename of the model file.
        std::string output_filename;     // Filename of the output file.
        yli::ontology::Shader* parent;   // Pointer to the `Shader`.
        std::shared_ptr<yli::common::AnyValue> left_filler_vector_any_value;
        std::shared_ptr<yli::common::AnyValue> right_filler_vector_any_value;
        std::shared_ptr<yli::callback::CallbackEngine> end_condition_callback_engine;
        std::size_t n_max_iterations;
        std::size_t compute_taskID;
        std::size_t texture_width;
        std::size_t texture_height;
        std::size_t n_index_characters;  // For intermediate results' filenames.
        GLenum format;
        GLenum internal_format;
        GLenum output_format;
        GLenum type;
        bool should_ylikuutio_save_intermediate_results;
        bool should_ylikuutio_flip_texture;
        PreIterateCallback preiterate_callback;
        PostIterateCallback postiterate_callback;
    };
}

#endif
