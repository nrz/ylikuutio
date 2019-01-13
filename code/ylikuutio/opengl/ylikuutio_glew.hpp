#ifndef __YLIKUUTIO_GLEW_HPP_INCLUDED
#define __YLIKUUTIO_GLEW_HPP_INCLUDED

#ifndef __ANDROID__ // do not `#include <GL/glew.h>` for Android.
// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif
#else
#include "SDL.h"
#include "SDL_opengles2.h"
#endif

#endif
