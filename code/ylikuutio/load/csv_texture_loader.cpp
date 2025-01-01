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

#include "csv_texture_loader.hpp"
#include "csv_loader.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/linear_algebra/vector_functions.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <functional> // std::reference_wrapper
#include <iostream> // std::cout, std::cerr
#include <optional> // std::optional
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <variant>  // std::holds_alternative, std::variant
#include <vector>   // std::vector

namespace yli::load
{
    bool load_csv_texture(
            const std::string& filename,
            const GLenum format,
            const GLenum internal_format,
            const GLenum type,
            const yli::data::AnyValue* const left_filler_vector_any_value,
            const yli::data::AnyValue* const right_filler_vector_any_value,
            uint32_t& image_width,
            uint32_t& image_height,
            uint32_t& image_size,
            GLuint& textureID)
    {
        GLvoid* image_data_ptr = nullptr;

        std::variant<
            std::vector<int8_t>,
            std::vector<uint8_t>,
            std::vector<int16_t>,
            std::vector<uint16_t>,
            std::vector<int32_t>,
            std::vector<uint32_t>,
            std::vector<float>> image_data;

        if (type == GL_BYTE)
        {
            std::optional<std::vector<int8_t>> csv_image_data = load_csv_file<int8_t>(filename, image_width, image_height, image_size);

            if (!csv_image_data)
            {
                std::cerr << "ERROR: `yli::load::load_csv_texture`: CSV file " << filename << " not loaded successfully!\n";
                return false;
            }

            image_data = *csv_image_data;

            if (left_filler_vector_any_value != nullptr &&
                    right_filler_vector_any_value != nullptr &&
                    std::holds_alternative<std::reference_wrapper<std::vector<int8_t>>>(left_filler_vector_any_value->data) &&
                    std::holds_alternative<std::reference_wrapper<std::vector<int8_t>>>(right_filler_vector_any_value->data))
            {
                image_data = yli::linear_algebra::insert_elements<int8_t>(
                        *csv_image_data,
                        std::get<std::reference_wrapper<std::vector<int8_t>>>(left_filler_vector_any_value->data),
                        std::get<std::reference_wrapper<std::vector<int8_t>>>(right_filler_vector_any_value->data));
            }

            image_data_ptr = std::get<std::vector<int8_t>>(image_data).data();
        }
        else if (type == GL_UNSIGNED_BYTE)
        {
            std::optional<std::vector<uint8_t>> csv_image_data = load_csv_file<uint8_t>(filename, image_width, image_height, image_size);

            if (!csv_image_data)
            {
                std::cerr << "ERROR: `yli::load::load_csv_texture`: CSV file " << filename << " not loaded successfully!\n";
                return false;
            }

            image_data = *csv_image_data;

            if (left_filler_vector_any_value != nullptr &&
                    right_filler_vector_any_value != nullptr &&
                    std::holds_alternative<std::reference_wrapper<std::vector<uint8_t>>>(left_filler_vector_any_value->data) &&
                    std::holds_alternative<std::reference_wrapper<std::vector<uint8_t>>>(right_filler_vector_any_value->data))
            {
                image_data = yli::linear_algebra::insert_elements<uint8_t>(
                        *csv_image_data,
                        std::get<std::reference_wrapper<std::vector<uint8_t>>>(left_filler_vector_any_value->data),
                        std::get<std::reference_wrapper<std::vector<uint8_t>>>(right_filler_vector_any_value->data));
            }

            image_data_ptr = std::get<std::vector<uint8_t>>(image_data).data();
        }
        else if (type == GL_SHORT)
        {
            std::optional<std::vector<int16_t>> csv_image_data = load_csv_file<int16_t>(filename, image_width, image_height, image_size);

            if (!csv_image_data)
            {
                std::cerr << "ERROR: `yli::load::load_csv_texture`: CSV file " << filename << " not loaded successfully!\n";
                return false;
            }

            image_data = *csv_image_data;

            if (left_filler_vector_any_value != nullptr &&
                    right_filler_vector_any_value != nullptr &&
                    std::holds_alternative<std::reference_wrapper<std::vector<int16_t>>>(left_filler_vector_any_value->data) &&
                    std::holds_alternative<std::reference_wrapper<std::vector<int16_t>>>(right_filler_vector_any_value->data))
            {
                image_data = yli::linear_algebra::insert_elements<int16_t>(
                        *csv_image_data,
                        std::get<std::reference_wrapper<std::vector<int16_t>>>(left_filler_vector_any_value->data),
                        std::get<std::reference_wrapper<std::vector<int16_t>>>(right_filler_vector_any_value->data));
            }

            image_data_ptr = std::get<std::vector<int16_t>>(image_data).data();
        }
        else if (type == GL_UNSIGNED_SHORT)
        {
            std::optional<std::vector<uint16_t>> csv_image_data = load_csv_file<uint16_t>(filename, image_width, image_height, image_size);

            if (!csv_image_data)
            {
                std::cerr << "ERROR: `yli::load::load_csv_texture`: CSV file " << filename << " not loaded successfully!\n";
                return false;
            }

            image_data = *csv_image_data;

            if (left_filler_vector_any_value != nullptr &&
                    right_filler_vector_any_value != nullptr &&
                    std::holds_alternative<std::reference_wrapper<std::vector<uint16_t>>>(left_filler_vector_any_value->data) &&
                    std::holds_alternative<std::reference_wrapper<std::vector<uint16_t>>>(right_filler_vector_any_value->data))
            {
                image_data = yli::linear_algebra::insert_elements<uint16_t>(
                        *csv_image_data,
                        std::get<std::reference_wrapper<std::vector<uint16_t>>>(left_filler_vector_any_value->data),
                        std::get<std::reference_wrapper<std::vector<uint16_t>>>(right_filler_vector_any_value->data));
            }

            image_data_ptr = std::get<std::vector<uint16_t>>(image_data).data();
        }
        else if (type == GL_INT)
        {
            std::optional<std::vector<int32_t>> csv_image_data = load_csv_file<int32_t>(filename, image_width, image_height, image_size);

            if (!csv_image_data)
            {
                std::cerr << "ERROR: `yli::load::load_csv_texture`: CSV file " << filename << " not loaded successfully!\n";
                return false;
            }

            image_data = *csv_image_data;

            if (left_filler_vector_any_value != nullptr &&
                    right_filler_vector_any_value != nullptr &&
                    std::holds_alternative<std::reference_wrapper<std::vector<int32_t>>>(left_filler_vector_any_value->data) &&
                    std::holds_alternative<std::reference_wrapper<std::vector<int32_t>>>(right_filler_vector_any_value->data))
            {
                image_data = yli::linear_algebra::insert_elements<int32_t>(
                        *csv_image_data,
                        std::get<std::reference_wrapper<std::vector<int32_t>>>(left_filler_vector_any_value->data),
                        std::get<std::reference_wrapper<std::vector<int32_t>>>(right_filler_vector_any_value->data));
            }

            image_data_ptr = std::get<std::vector<int32_t>>(image_data).data();
        }
        else if (type == GL_UNSIGNED_INT)
        {
            std::optional<std::vector<uint32_t>> csv_image_data = load_csv_file<uint32_t>(filename, image_width, image_height, image_size);

            if (!csv_image_data)
            {
                std::cerr << "ERROR: `yli::load::load_csv_texture`: CSV file " << filename << " not loaded successfully!\n";
                return false;
            }

            image_data = *csv_image_data;

            if (left_filler_vector_any_value != nullptr &&
                    right_filler_vector_any_value != nullptr &&
                    std::holds_alternative<std::reference_wrapper<std::vector<uint32_t>>>(left_filler_vector_any_value->data) &&
                    std::holds_alternative<std::reference_wrapper<std::vector<uint32_t>>>(right_filler_vector_any_value->data))
            {
                image_data = yli::linear_algebra::insert_elements<uint32_t>(
                        *csv_image_data,
                        std::get<std::reference_wrapper<std::vector<uint32_t>>>(left_filler_vector_any_value->data),
                        std::get<std::reference_wrapper<std::vector<uint32_t>>>(right_filler_vector_any_value->data));
            }

            image_data_ptr = std::get<std::vector<uint32_t>>(image_data).data();
        }
        else if (type == GL_FIXED)
        {
            return false; // TODO: add support for `GL_FIXED`!
        }
        else if (type == GL_HALF_FLOAT)
        {
            return false; // TODO: add support for `GL_HALF_FLOAT`!
        }
        else if (type == GL_FLOAT)
        {
            std::optional<std::vector<float>> csv_image_data = load_csv_file<float>(filename, image_width, image_height, image_size);

            if (!csv_image_data)
            {
                std::cerr << "ERROR: `yli::load::load_csv_texture`: CSV file " << filename << " not loaded successfully!\n";
                return false;
            }

            image_data = *csv_image_data;

            if (left_filler_vector_any_value != nullptr &&
                    right_filler_vector_any_value != nullptr &&
                    std::holds_alternative<std::reference_wrapper<std::vector<float>>>(left_filler_vector_any_value->data) &&
                    std::holds_alternative<std::reference_wrapper<std::vector<float>>>(right_filler_vector_any_value->data))
            {
                image_data = yli::linear_algebra::insert_elements<float>(
                        *csv_image_data,
                        std::get<std::reference_wrapper<std::vector<float>>>(left_filler_vector_any_value->data),
                        std::get<std::reference_wrapper<std::vector<float>>>(right_filler_vector_any_value->data));
            }

            image_data_ptr = std::get<std::vector<float>>(image_data).data();
        }
        else if (type == GL_DOUBLE)
        {
            return false; // TODO: add support for `GL_DOUBLE`!
        }
        else
        {
            // Unknown or unsupported type.
            return false;
        }

        if (image_data_ptr == nullptr)
        {
            std::cerr << "ERROR: `image_data` is `nullptr`!\n";
            return false;
        }

        // Create one OpenGL texture.
        glGenTextures(1, &textureID);

        // Bind the newly created texture: all future texture functions will modify this texture.
        glBindTexture(GL_TEXTURE_2D, textureID);

        // Give the image to OpenGL.
        if (internal_format == GL_INVALID_ENUM)
        {
            // Internal format not defined, use format as internal format.
            glTexImage2D(GL_TEXTURE_2D, 0, format, image_width, image_height, 0, format, type, image_data_ptr);
        }
        else
        {
            // Internal format is defined.
            glTexImage2D(GL_TEXTURE_2D, 0, internal_format, image_width, image_height, 0, format, type, image_data_ptr);
        }

        yli::opengl::set_nearest_filtering_parameters();

        return true;
    }

    bool load_csv_texture(
            const std::string& filename,
            const GLenum format,
            const GLenum internal_format,
            const GLenum type,
            uint32_t& image_width,
            uint32_t& image_height,
            uint32_t& image_size,
            uint32_t& textureID)
    {
        return yli::load::load_csv_texture(
                filename,
                format,
                internal_format,
                type,
                nullptr,
                nullptr,
                image_width,
                image_height,
                image_size,
                textureID);
    }
}
