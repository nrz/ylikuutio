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

#ifndef __YLIKUUTIO_ONTOLOGY_COMPUTE_TASK_STRUCT_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_COMPUTE_TASK_STRUCT_HPP_INCLUDED

#include "entity_struct.hpp"
#include "pre_iterate_callback.hpp"
#include "post_iterate_callback.hpp"
#include "code/ylikuutio/data/any_value.hpp"
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

    struct ComputeTaskStruct: public yli::ontology::EntityStruct
    {
        std::string texture_file_format; // Type of the texture file. supported file formats so far: `"png"`/`"PNG"`, `"csv"`/`"CSV"`.
        std::string texture_filename;    // Filename of the model file.
        std::string output_filename;     // Filename of the output file.
        yli::ontology::Shader* parent { nullptr };   // Pointer to the `Shader`.
        std::shared_ptr<yli::data::AnyValue> left_filler_vector_any_value            { nullptr };
        std::shared_ptr<yli::data::AnyValue> right_filler_vector_any_value           { nullptr };
        std::shared_ptr<yli::callback::CallbackEngine> end_condition_callback_engine { nullptr };
        std::size_t n_max_iterations   { 1 }; // By default execute GLSL shader exactly once (do not iterate further).
        std::size_t compute_taskID     { std::numeric_limits<std::size_t>::max() };
        std::size_t texture_width      { 0 };
        std::size_t texture_height     { 0 };
        std::size_t n_index_characters { 4 }; // For intermediate results' filenames.
        GLenum format                  { GL_RGB };
        GLenum internal_format         { GL_INVALID_ENUM };
        GLenum output_format           { GL_INVALID_ENUM };
        GLenum type                    { GL_UNSIGNED_BYTE };
        bool should_save_intermediate_results    { false };
        bool should_flip_texture                 { true };
        PreIterateCallback preiterate_callback   { nullptr };
        PostIterateCallback postiterate_callback { nullptr };
    };
}

#endif
