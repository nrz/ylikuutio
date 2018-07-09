#ifndef __TRIANGULATE_POLYGONS_STRUCT_HPP_INCLUDED
#define __TRIANGULATE_POLYGONS_STRUCT_HPP_INCLUDED

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <vector>   // std::vector

namespace yli
{
    namespace geometry
    {
        typedef struct TriangulatePolygonsStruct
        {
            TriangulatePolygonsStruct()
                : input_vertices(nullptr), should_ylikuutio_use_real_texture_coordinates(true)
            {
                // constructor.
            }
            std::vector<std::vector<glm::vec2>>* input_vertices;
            bool should_ylikuutio_use_real_texture_coordinates;
        } TriangulatePolygonsStruct;
    }
}

#endif
