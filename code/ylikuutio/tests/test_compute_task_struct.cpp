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

#include "gtest/gtest.h"
#include "code/ylikuutio/ontology/request.hpp"
#include "code/ylikuutio/ontology/compute_task_struct.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <cstddef> // std::size_t
#include <limits>  // std::numeric_limits
#include <variant> // std::holds_alternative

namespace yli::ontology
{
    class Pipeline;
}

TEST(compute_task_struct_must_be_initialized_appropriately, compute_task_struct_parent_provided_as_nullptr)
{
    const yli::ontology::ComputeTaskStruct test_compute_task_struct { yli::ontology::Request<yli::ontology::Pipeline>(nullptr) };
    ASSERT_EQ(test_compute_task_struct.texture_file_format, "");
    ASSERT_EQ(test_compute_task_struct.texture_filename, "");
    ASSERT_EQ(test_compute_task_struct.output_filename, "");

    ASSERT_FALSE(test_compute_task_struct.pipeline_parent.data.valueless_by_exception());
    ASSERT_TRUE(std::holds_alternative<yli::ontology::Pipeline*>(test_compute_task_struct.pipeline_parent.data));
    ASSERT_FALSE(std::holds_alternative<std::string>(test_compute_task_struct.pipeline_parent.data));
    ASSERT_EQ(std::get<yli::ontology::Pipeline*>(test_compute_task_struct.pipeline_parent.data), nullptr);

    ASSERT_EQ(test_compute_task_struct.n_max_iterations, 1);
    ASSERT_EQ(test_compute_task_struct.compute_taskID, std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(test_compute_task_struct.texture_width, 0);
    ASSERT_EQ(test_compute_task_struct.texture_height, 0);
    ASSERT_EQ(test_compute_task_struct.n_index_characters, 4);
    ASSERT_EQ(test_compute_task_struct.format, GL_RGB);
    ASSERT_EQ(test_compute_task_struct.internal_format, GL_INVALID_ENUM);
    ASSERT_EQ(test_compute_task_struct.output_format, GL_INVALID_ENUM);
    ASSERT_EQ(test_compute_task_struct.type, GL_UNSIGNED_BYTE);
    ASSERT_EQ(test_compute_task_struct.should_save_intermediate_results, false);
    ASSERT_EQ(test_compute_task_struct.should_flip_texture, true);
}

TEST(compute_task_struct_must_be_initialized_appropriately, compute_task_struct_parent_provided_as_global_name)
{
    const yli::ontology::ComputeTaskStruct test_compute_task_struct { yli::ontology::Request<yli::ontology::Pipeline>("foo") };
    ASSERT_EQ(test_compute_task_struct.texture_file_format, "");
    ASSERT_EQ(test_compute_task_struct.texture_filename, "");
    ASSERT_EQ(test_compute_task_struct.output_filename, "");

    ASSERT_FALSE(test_compute_task_struct.pipeline_parent.data.valueless_by_exception());
    ASSERT_FALSE(std::holds_alternative<yli::ontology::Pipeline*>(test_compute_task_struct.pipeline_parent.data));
    ASSERT_TRUE(std::holds_alternative<std::string>(test_compute_task_struct.pipeline_parent.data));
    ASSERT_EQ(std::get<std::string>(test_compute_task_struct.pipeline_parent.data), "foo");

    ASSERT_EQ(test_compute_task_struct.n_max_iterations, 1);
    ASSERT_EQ(test_compute_task_struct.compute_taskID, std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(test_compute_task_struct.texture_width, 0);
    ASSERT_EQ(test_compute_task_struct.texture_height, 0);
    ASSERT_EQ(test_compute_task_struct.n_index_characters, 4);
    ASSERT_EQ(test_compute_task_struct.format, GL_RGB);
    ASSERT_EQ(test_compute_task_struct.internal_format, GL_INVALID_ENUM);
    ASSERT_EQ(test_compute_task_struct.output_format, GL_INVALID_ENUM);
    ASSERT_EQ(test_compute_task_struct.type, GL_UNSIGNED_BYTE);
    ASSERT_EQ(test_compute_task_struct.should_save_intermediate_results, false);
    ASSERT_EQ(test_compute_task_struct.should_flip_texture, true);
}
