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

#ifndef __YLIKUUTIO_ONTOLOGY_COMPUTE_TASK_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_COMPUTE_TASK_HPP_INCLUDED

#include "entity.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <cstddef>  // std::size_t
#include <memory>   // std::make_shared, std::shared_ptr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

// `yli::ontology::ComputeTask` is a class which contains the data for a single
// computing task. `ComputeTask` does not have the OpenGL shaders used to process
// the data. Instead, the shaders are contained by the parent `Entity` which is
// an `yli::ontology::Shader` instance.
//
// For example, `yli::ontology::Shader` can have vertex and fragment shaders for
// computing the distances between nodes of a graph. Then, each `ComputeTask`
// would contain the graph data, eg. as a distance matrix. Then, rendering a
// `ComputeTask` means computing that task.
//
// Rendering a `ComputeTask` is done by iterating the task until either
// `end_condition_callback_engine->execute(nullptr)` returns `true`, or until
// `n_max_iterations` is reached. If `end_condition_callback_engine` is `nullptr`
// or `end_condition_callback_engine->execute(nullptr)` does not not return an `AnyValue`
// which contains `yli::data::BOOL`, then `end_condition_callback_engine` is ignored
// and `n_max_iterations` is the exact number of iterations to be done. However,
// even if `end_condition_callback_engine->execute(nullptr)` would return an invalid return
// value, that is, not an `AnyValue` which contains `common::BOOL`,
// `end_condition_callback_engine->execute(nullptr)` is still called and taken into account
// in every iteration.

namespace yli::callback
{
    class CallbackEngine;
}

namespace yli::ontology
{
    class Universe;
    class Scene;
    class Shader;
    struct ComputeTaskStruct;

    class ComputeTask: public yli::ontology::Entity
    {
        public:
            ComputeTask(yli::ontology::Universe& universe, const yli::ontology::ComputeTaskStruct& compute_task_struct);

            ComputeTask(const ComputeTask&) = delete;            // Delete copy constructor.
            ComputeTask& operator=(const ComputeTask&) = delete; // Delete copy assignment.

            // destructor.
            ~ComputeTask();

            yli::ontology::Entity* get_parent() const override;

        private:
            void bind_to_parent();

        public:
            yli::ontology::Scene* get_scene() const override;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

        public:
            // This method renders this `ComputeTask`, that is, computes this task.
            void render(const yli::ontology::Scene* const);

        private:
            std::string texture_file_format; // Type of the texture file. Supported file formats so far: `"png"`/`"PNG"`, `"csv"`/`"CSV"`.
            std::string texture_filename;    // Filename of the model file.
            std::string output_filename;     // Filename of the output file.

            yli::ontology::Shader* parent;   // pointer to the `Shader`.

            yli::data::AnyValue left_filler_vector_any_value;
            yli::data::AnyValue right_filler_vector_any_value;

            // End iterating when `end_condition_callback_engine` returns `true`.
            std::shared_ptr<yli::callback::CallbackEngine> end_condition_callback_engine;

            std::shared_ptr<std::vector<uint8_t>> result_vector { nullptr };

            // This is the maximum number of iterations.
            // If `end_condition_callback_engine` is `nullptr`, then this is the number of iterations.
            // If `end_condition_callback_engine` is not `nullptr`, then this is the maximum number of iterations.
            std::size_t n_max_iterations;

            std::size_t compute_taskID;

            uint32_t texture_width;
            uint32_t texture_height;
            uint32_t texture_size { 0 }; // Some dummy value.

            uint32_t n_index_characters; // For intermediate results' filenames.

            uint32_t vertices_size { 0 };
            uint32_t uvs_size      { 0 };

            // variables related to the framebuffer.
            GLuint framebuffer              { 0 }; // Some dummy value.
            GLuint source_texture           { 0 }; // Some dummy value.
            GLuint target_texture           { 0 }; // Some dummy value.
            GLint opengl_texture_id         { 0 }; // Some dummy value.
            bool is_texture_loaded          { false };
            bool is_framebuffer_initialized { false };
            bool is_ready                   { false };

            GLint vertex_position_modelspace_id { 0 }; // Some dummy value.
            GLint vertex_uv_id                  { 0 }; // Some dummy value.
            GLint screen_width_uniform_id       { 0 }; // Some dummy value. Location of the program's window width uniform.
            GLint screen_height_uniform_id      { 0 }; // Some dummy value. Location of the program's window height uniform.
            GLint iteration_i_uniform_id        { 0 }; // Some dummy value. Location of the program's iteration index uniform.

            GLuint vao           { 0 }; // Some dummy value.
            GLuint vertexbuffer  { 0 }; // Some dummy value.
            GLuint uvbuffer      { 0 }; // Some dummy value.
            GLuint elementbuffer { 0 }; // Some dummy value.

            GLenum format;
            GLenum internal_format;
            GLenum output_format;
            GLenum type;

            bool should_save_intermediate_results;
            bool should_flip_texture;
    };
}

#endif
