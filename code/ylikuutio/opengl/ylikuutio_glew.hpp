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

#ifndef YLIKUUTIO_OPENGL_YLIKUUTIO_GLEW_HPP_INCLUDED
#define YLIKUUTIO_OPENGL_YLIKUUTIO_GLEW_HPP_INCLUDED

#ifndef __ANDROID__ // do not `#include <GL/glew.h>` for Android.
// Include GLEW
#ifndef GL_GLEW_H_INCLUDED
#define GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif
#else
#include "SDL.h"
#include "SDL_opengles2.h"
#endif

#endif
