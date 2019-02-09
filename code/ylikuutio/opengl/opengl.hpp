#ifndef __OPENGL_HPP_INCLUDED
#define __OPENGL_HPP_INCLUDED

#include "SDL.h"

namespace yli
{
    namespace opengl
    {
        bool init_glew();
        void enable_depth_test();
        void disable_depth_test();
        void set_depth_func_to_less();
        void cull_triangles();
        void set_background_color(const float red, const float green, const float blue, const float alpha);
        void set_filtering_parameters();
        void set_wireframe(const bool wireframe);
        bool has_ext_framebuffer_object();
        bool has_arb_shader_objects();
        bool has_arb_vertex_shader();
        bool has_arb_fragment_shader();
    }
}

#endif
