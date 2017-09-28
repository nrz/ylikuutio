#ifndef __POLYGON_TRIANGULATION_HPP_INCLUDED
#define __POLYGON_TRIANGULATION_HPP_INCLUDED

#include "triangulate_polygons_struct.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <vector>   // std::vector

namespace geometry
{
    bool triangulate_simple_polygon(
            const geometry::TriangulatePolygonsStruct triangulate_polygons_struct,
            std::vector<glm::vec3>& out_vertices,
            std::vector<glm::vec2>& out_UVs,
            std::vector<glm::vec3>& out_normals);

    bool triangulate_polygons(
            const geometry::TriangulatePolygonsStruct triangulate_polygons_struct,
            std::vector<glm::vec3>& out_vertices,
            std::vector<glm::vec2>& out_UVs,
            std::vector<glm::vec3>& out_normals);
}

#endif
