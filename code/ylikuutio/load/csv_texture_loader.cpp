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

#include "csv_texture_loader.hpp"
#include "csv_loader.hpp"
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/linear_algebra/vector_functions.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <memory>   // std::make_shared, std::shared_ptr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <variant>  // std::variant
#include <vector>   // std::vector

namespace yli::load
{
    bool load_csv_texture(
            const std::string& filename,
            const GLenum format,
            const GLenum internal_format,
            const GLenum type,
            const std::shared_ptr<yli::common::AnyValue> left_filler_vector_any_value,
            const std::shared_ptr<yli::common::AnyValue> right_filler_vector_any_value,
            std::size_t& image_width,
            std::size_t& image_height,
            std::size_t& image_size,
            GLuint& textureID)
    {
        GLvoid* image_data = nullptr;

        // Shared pointers are created here so that they stay in scope
        // until `glTexImage2D` call.
        std::shared_ptr<std::vector<int8_t>> image_data_int8_t = nullptr;
        std::shared_ptr<std::vector<uint8_t>> image_data_uint8_t = nullptr;
        std::shared_ptr<std::vector<int16_t>> image_data_int16_t = nullptr;
        std::shared_ptr<std::vector<uint16_t>> image_data_uint16_t = nullptr;
        std::shared_ptr<std::vector<int32_t>> image_data_int32_t = nullptr;
        std::shared_ptr<std::vector<uint32_t>> image_data_uint32_t = nullptr;
        std::shared_ptr<std::vector<float>> image_data_float = nullptr;

        if (type == GL_BYTE)
        {
            image_data_int8_t = load_CSV_file<int8_t>(filename, image_width, image_height, image_size);
            if (image_data_int8_t == nullptr)
            {
                std::cerr << "ERROR: `yli::load::load_csv_texture`: `image_data_int8_t` is `nullptr`!\n";
                return false;
            }
            if (left_filler_vector_any_value != nullptr &&
                    right_filler_vector_any_value != nullptr &&
                    std::holds_alternative<std::shared_ptr<std::vector<int8_t>>>(left_filler_vector_any_value->data) &&
                    std::holds_alternative<std::shared_ptr<std::vector<int8_t>>>(right_filler_vector_any_value->data) &&
                    std::get<std::shared_ptr<std::vector<int8_t>>>(left_filler_vector_any_value->data) != nullptr &&
                    std::get<std::shared_ptr<std::vector<int8_t>>>(right_filler_vector_any_value->data) != nullptr)
            {
                image_data_int8_t = yli::linear_algebra::insert_elements(
                        *image_data_int8_t,
                        *(std::get<std::shared_ptr<std::vector<int8_t>>>(left_filler_vector_any_value->data)),
                        *(std::get<std::shared_ptr<std::vector<int8_t>>>(right_filler_vector_any_value->data)));
                image_data = image_data_int8_t != nullptr ? &(*image_data_int8_t)[0] : nullptr;
            }
            else
            {
                image_data = &(*image_data_int8_t)[0];
            }
        }
        else if (type == GL_UNSIGNED_BYTE)
        {
            image_data_uint8_t = load_CSV_file<uint8_t>(filename, image_width, image_height, image_size);
            if (image_data_uint8_t == nullptr)
            {
                std::cerr << "ERROR: `yli::load::load_csv_texture`: `image_data_uint8_t` is `nullptr`!\n";
                return false;
            }
            if (left_filler_vector_any_value != nullptr &&
                    right_filler_vector_any_value != nullptr &&
                    std::holds_alternative<std::shared_ptr<std::vector<uint8_t>>>(left_filler_vector_any_value->data) &&
                    std::holds_alternative<std::shared_ptr<std::vector<uint8_t>>>(right_filler_vector_any_value->data) &&
                    std::get<std::shared_ptr<std::vector<uint8_t>>>(left_filler_vector_any_value->data) != nullptr &&
                    std::get<std::shared_ptr<std::vector<uint8_t>>>(right_filler_vector_any_value->data) != nullptr)
            {
                image_data_uint8_t = yli::linear_algebra::insert_elements(
                        *image_data_uint8_t,
                        *(std::get<std::shared_ptr<std::vector<uint8_t>>>(left_filler_vector_any_value->data)),
                        *(std::get<std::shared_ptr<std::vector<uint8_t>>>(right_filler_vector_any_value->data)));
                image_data = image_data_uint8_t != nullptr ? &(*image_data_uint8_t)[0] : nullptr;
            }
            else
            {
                image_data = &(*image_data_uint8_t)[0];
            }
        }
        else if (type == GL_SHORT)
        {
            image_data_int16_t = load_CSV_file<int16_t>(filename, image_width, image_height, image_size);
            if (image_data_int16_t == nullptr)
            {
                std::cerr << "ERROR: `yli::load::load_csv_texture`: `image_data_int16_t` is `nullptr`!\n";
                return false;
            }
            if (left_filler_vector_any_value != nullptr &&
                    right_filler_vector_any_value != nullptr &&
                    std::holds_alternative<std::shared_ptr<std::vector<int16_t>>>(left_filler_vector_any_value->data) &&
                    std::holds_alternative<std::shared_ptr<std::vector<int16_t>>>(right_filler_vector_any_value->data) &&
                    std::get<std::shared_ptr<std::vector<int16_t>>>(left_filler_vector_any_value->data) != nullptr &&
                    std::get<std::shared_ptr<std::vector<int16_t>>>(right_filler_vector_any_value->data) != nullptr)
            {
                image_data_int16_t = yli::linear_algebra::insert_elements(
                        *image_data_int16_t,
                        *(std::get<std::shared_ptr<std::vector<int16_t>>>(left_filler_vector_any_value->data)),
                        *(std::get<std::shared_ptr<std::vector<int16_t>>>(right_filler_vector_any_value->data)));
                image_data = image_data_int16_t != nullptr ? &(*image_data_int16_t)[0] : nullptr;
            }
            else
            {
                image_data = &(*image_data_int16_t)[0];
            }
        }
        else if (type == GL_UNSIGNED_SHORT)
        {
            image_data_uint16_t = load_CSV_file<uint16_t>(filename, image_width, image_height, image_size);
            if (image_data_uint16_t == nullptr)
            {
                std::cerr << "ERROR: `yli::load::load_csv_texture`: `image_data_uint16_t` is `nullptr`!\n";
                return false;
            }
            if (left_filler_vector_any_value != nullptr &&
                    right_filler_vector_any_value != nullptr &&
                    std::holds_alternative<std::shared_ptr<std::vector<uint16_t>>>(left_filler_vector_any_value->data) &&
                    std::holds_alternative<std::shared_ptr<std::vector<uint16_t>>>(right_filler_vector_any_value->data) &&
                    std::get<std::shared_ptr<std::vector<uint16_t>>>(left_filler_vector_any_value->data) != nullptr &&
                    std::get<std::shared_ptr<std::vector<uint16_t>>>(right_filler_vector_any_value->data) != nullptr)
            {
                image_data_uint16_t = yli::linear_algebra::insert_elements(
                        *image_data_uint16_t,
                        *(std::get<std::shared_ptr<std::vector<uint16_t>>>(left_filler_vector_any_value->data)),
                        *(std::get<std::shared_ptr<std::vector<uint16_t>>>(right_filler_vector_any_value->data)));
                image_data = image_data_uint16_t != nullptr ? &(*image_data_uint16_t)[0] : nullptr;
            }
            else
            {
                image_data = &(*image_data_uint16_t)[0];
            }
        }
        else if (type == GL_INT)
        {
            image_data_int32_t = load_CSV_file<int32_t>(filename, image_width, image_height, image_size);
            if (image_data_int32_t == nullptr)
            {
                std::cerr << "ERROR: `yli::load::load_csv_texture`: `image_data_int32_t` is `nullptr`!\n";
                return false;
            }
            if (left_filler_vector_any_value != nullptr &&
                    right_filler_vector_any_value != nullptr &&
                    std::holds_alternative<std::shared_ptr<std::vector<int32_t>>>(left_filler_vector_any_value->data) &&
                    std::holds_alternative<std::shared_ptr<std::vector<int32_t>>>(right_filler_vector_any_value->data) &&
                    std::get<std::shared_ptr<std::vector<int32_t>>>(left_filler_vector_any_value->data) != nullptr &&
                    std::get<std::shared_ptr<std::vector<int32_t>>>(right_filler_vector_any_value->data) != nullptr)
            {
                image_data_int32_t = yli::linear_algebra::insert_elements(
                        *image_data_int32_t,
                        *(std::get<std::shared_ptr<std::vector<int32_t>>>(left_filler_vector_any_value->data)),
                        *(std::get<std::shared_ptr<std::vector<int32_t>>>(right_filler_vector_any_value->data)));
                image_data = image_data_int32_t != nullptr ? &(*image_data_int32_t)[0] : nullptr;
            }
            else
            {
                image_data = &(*image_data_int32_t)[0];
            }
        }
        else if (type == GL_UNSIGNED_INT)
        {
            image_data_uint32_t = load_CSV_file<uint32_t>(filename, image_width, image_height, image_size);
            if (image_data_uint32_t == nullptr)
            {
                std::cerr << "ERROR: `yli::load::load_csv_texture`: `image_data_uint32_t` is `nullptr`!\n";
                return false;
            }
            if (left_filler_vector_any_value != nullptr &&
                    right_filler_vector_any_value != nullptr &&
                    std::holds_alternative<std::shared_ptr<std::vector<uint32_t>>>(left_filler_vector_any_value->data) &&
                    std::holds_alternative<std::shared_ptr<std::vector<uint32_t>>>(right_filler_vector_any_value->data) &&
                    std::get<std::shared_ptr<std::vector<uint32_t>>>(left_filler_vector_any_value->data) != nullptr &&
                    std::get<std::shared_ptr<std::vector<uint32_t>>>(right_filler_vector_any_value->data) != nullptr)
            {
                image_data_uint32_t = yli::linear_algebra::insert_elements(
                        *image_data_uint32_t,
                        *(std::get<std::shared_ptr<std::vector<uint32_t>>>(left_filler_vector_any_value->data)),
                        *(std::get<std::shared_ptr<std::vector<uint32_t>>>(right_filler_vector_any_value->data)));
                image_data = image_data_uint32_t != nullptr ? &(*image_data_uint32_t)[0] : nullptr;
            }
            else
            {
                image_data = &(*image_data_uint32_t)[0];
            }
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
            image_data_float = load_CSV_file<float>(filename, image_width, image_height, image_size);
            if (image_data_float == nullptr)
            {
                std::cerr << "ERROR: `yli::load::load_csv_texture`: `image_data_float` is `nullptr`!\n";
                return false;
            }
            if (left_filler_vector_any_value != nullptr &&
                    right_filler_vector_any_value != nullptr &&
                    std::holds_alternative<std::shared_ptr<std::vector<float>>>(left_filler_vector_any_value->data) &&
                    std::holds_alternative<std::shared_ptr<std::vector<float>>>(right_filler_vector_any_value->data) &&
                    std::get<std::shared_ptr<std::vector<float>>>(left_filler_vector_any_value->data) != nullptr &&
                    std::get<std::shared_ptr<std::vector<float>>>(right_filler_vector_any_value->data) != nullptr)
            {
                image_data_float = yli::linear_algebra::insert_elements(
                        *image_data_float,
                        *(std::get<std::shared_ptr<std::vector<float>>>(left_filler_vector_any_value->data)),
                        *(std::get<std::shared_ptr<std::vector<float>>>(right_filler_vector_any_value->data)));
                image_data = image_data_float != nullptr ? &(*image_data_float)[0] : nullptr;
            }
            else
            {
                image_data = &(*image_data_float)[0];
            }
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

        if (image_data == nullptr)
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
            glTexImage2D(GL_TEXTURE_2D, 0, format, image_width, image_height, 0, format, type, image_data);
        }
        else
        {
            // Internal format is defined.
            glTexImage2D(GL_TEXTURE_2D, 0, internal_format, image_width, image_height, 0, format, type, image_data);
        }

        yli::opengl::set_nearest_filtering_parameters();

        return true;
    }

    bool load_csv_texture(
            const std::string& filename,
            const GLenum format,
            const GLenum internal_format,
            const GLenum type,
            std::size_t& image_width,
            std::size_t& image_height,
            std::size_t& image_size,
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
