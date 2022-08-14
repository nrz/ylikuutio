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

#ifndef __YLIKUUTIO_ONTOLOGY_FRAMEBUFFER_MODULE_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_FRAMEBUFFER_MODULE_HPP_INCLUDED

#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <stdint.h> // uint32_t etc.

namespace yli::ontology
{
    struct FramebufferModuleStruct;

    class FramebufferModule final
    {
        public:
            // constructor.
            explicit FramebufferModule(const yli::ontology::FramebufferModuleStruct& framebuffer_module_struct);

            FramebufferModule(const FramebufferModule&) = delete;            // Delete copy constructor.
            FramebufferModule &operator=(const FramebufferModule&) = delete; // Delete copy assignment.

            // destructor.
            ~FramebufferModule();

            void create_framebuffer_object();
            void bind() const;
            bool get_is_initialized() const;
            void initialize(const float red, const float green, const float blue, const float alpha);

            // This method returns current `texture_width`.
            uint32_t get_texture_width() const;

            // This method sets `texture_width`.
            void set_texture_width(const uint32_t texture_width);

            // This method returns current `texture_height`.
            uint32_t get_texture_height() const;

            // This method sets `texture_height`.
            void set_texture_height(const uint32_t texture_height);

            bool get_in_use() const;

        private:
            uint32_t texture_width;
            uint32_t texture_height;

            GLuint framebuffer  { 0 };
            GLuint texture      { 0 };
            GLuint renderbuffer { 0 };

            bool in_use;
            bool is_initialized { false };
    };
}

#endif
