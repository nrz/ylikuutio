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

#include "framebuffer_module.hpp"
#include "framebuffer_module_struct.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.

namespace yli::ontology
{
    FramebufferModule::FramebufferModule(const yli::ontology::FramebufferModuleStruct& framebuffer_module_struct)
        : texture_width(framebuffer_module_struct.texture_width),
        texture_height(framebuffer_module_struct.texture_height),
        in_use(framebuffer_module_struct.in_use)
    {
        // constructor.
    }

    FramebufferModule::~FramebufferModule()
    {
        // destructor.

        if (this->is_initialized)
        {
            glDeleteTextures(1, &this->texture);
            glDeleteRenderbuffers(1, &this->renderbuffer);
            glDeleteFramebuffers(1, &this->framebuffer);
        }
    }

    void FramebufferModule::create_framebuffer_object()
    {
        if (this->in_use)
        {
            // Create an FBO (off-screen framebuffer object).
            glGenFramebuffers(1, &this->framebuffer);
        }
    }

    void FramebufferModule::bind() const
    {
        if (this->in_use)
        {
            // Bind the offscreen buffer.
            yli::opengl::bind_gl_framebuffer(this->framebuffer);
        }
    }

    void FramebufferModule::initialize(const float red, const float green, const float blue, const float alpha)
    {
        if (this->in_use && !this->is_initialized)
        {
            // Create a texture.
            glGenTextures(1, &this->texture);
            glBindTexture(GL_TEXTURE_2D, this->texture);

            // Define the texture.
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->texture_width, this->texture_height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

            yli::opengl::set_filtering_parameters();

            // Attach the texture.
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->texture, 0);

            // Create and bind a render buffer with depth and stencil attachments.
            glGenRenderbuffers(1, &this->renderbuffer);
            glBindRenderbuffer(GL_RENDERBUFFER, this->renderbuffer);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, this->texture_width, this->texture_height);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->renderbuffer);

            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            {
                std::cerr << "ERROR: `FramebufferModule::initialize`: framebuffer is not complete!\n";
            }

            // Set background color for the framebuffer.
            yli::opengl::set_background_color(red, green, blue, alpha);

            this->is_initialized = true;
        }
    }

    bool FramebufferModule::get_is_initialized() const
    {
        return this->is_initialized;
    }

    uint32_t FramebufferModule::get_texture_width() const
    {
        return this->texture_width;
    }

    void FramebufferModule::set_texture_width(const uint32_t texture_width)
    {
        this->texture_width = texture_width;
    }

    uint32_t FramebufferModule::get_texture_height() const
    {
        return this->texture_height;
    }

    void FramebufferModule::set_texture_height(const uint32_t texture_height)
    {
        this->texture_height = texture_height;
    }

    bool FramebufferModule::get_in_use() const
    {
        return this->in_use;
    }
}
