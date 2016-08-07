#ifndef __TRIANGULATION_TEMPLATES_HPP_INCLUDED
#define __TRIANGULATION_TEMPLATES_HPP_INCLUDED

// Include standard headers
#include <stdint.h> // uint32_t etc.

namespace geometry
{
    template<class T1>
        T1 get_y(
                T1* vertex_data,
                uint32_t x,
                uint32_t z,
                uint32_t image_width)
        {
            // This function returns the altitude value based on x & z coordinates.
            // This works only for a raw heightmap data (for a 2D array of altitudes).
            T1* vertex_pointer;
            vertex_pointer = vertex_data + z * image_width + x;
            return static_cast<T1>(*vertex_pointer);
        }

    // for bilinear interpolation.
    template<class T1>
        T1 southwest_y(uint32_t x, uint32_t z, T1* input_vertex_pointer, uint32_t image_width)
        {
            return geometry::get_y(input_vertex_pointer, x - 1, z - 1, image_width);
        }
    template<class T1>
        T1 southeast_y(uint32_t x, uint32_t z, T1* input_vertex_pointer, uint32_t image_width)
        {
            return geometry::get_y(input_vertex_pointer, x, z - 1, image_width);
        }
    template<class T1>
        T1 northwest_y(uint32_t x, uint32_t z, T1* input_vertex_pointer, uint32_t image_width)
        {
            return geometry::get_y(input_vertex_pointer, x - 1, z, image_width);
        }
    template<class T1>
        T1 northeast_y(uint32_t x, uint32_t z, T1* input_vertex_pointer, uint32_t image_width)
        {
            return geometry::get_y(input_vertex_pointer, x, z, image_width);
        }
    template<class T1>
        T1 center_y(uint32_t x, uint32_t z, T1* input_vertex_pointer, uint32_t image_width)
        {
            return (southwest_y(x, z, input_vertex_pointer, image_width) +
                    southeast_y(x, z, input_vertex_pointer, image_width) +
                    northwest_y(x, z, input_vertex_pointer, image_width) +
                    northeast_y(x, z, input_vertex_pointer, image_width)) / 4;
        }
}

#endif
