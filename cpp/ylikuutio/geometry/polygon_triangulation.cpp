#include "polygon_triangulation.hpp"
#include "cpp/ylikuutio/common/globals.hpp"

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
            TriangulatePolygonsStruct triangulate_polygons_struct,
            std::vector<glm::vec3>& out_vertices,
            std::vector<glm::vec2>& out_UVs,
            std::vector<glm::vec3>& out_normals)
    {
        // TODO: implement this function!
        return false;
    }

    bool triangulate_polygons(
            TriangulatePolygonsStruct triangulate_polygons_struct,
            std::vector<glm::vec3>& out_vertices,
            std::vector<glm::vec2>& out_UVs,
            std::vector<glm::vec3>& out_normals)
    {
        // TODO: implement this function!

        // Find hidden vertices using `get_intersection_point(geometry::LineSegment2D* line_segment1, geometry::LineSegment2D* line_segment2)`.
        std::vector<std::vector<glm::vec2>>* vertex_data = triangulate_polygons_struct.input_vertices;

        // Each edge may have intersections with any other intersections
        // except immediately previous and immediately next intersections.
        // TODO: write the code!

        for (uint32_t vertex_i = 0; vertex_i < vertex_data->size(); vertex_i++)
        {
        }

        // All vertices (3D, explicitly defined and hidden) should be known now.

        // Divide complex polygons into simple polygons. Each vertex belongs to 1 or more simple polygons.
        // TODO: write the code!
        std::vector<std::vector<glm::vec3>> simple_polygons;

        for (uint32_t vertex_i = 0; vertex_i < vertex_data->size(); vertex_i++)
        {
        }

        // Loop through simple polygons and triangulate them.
        // TODO: write the code!

        return false;
    }
}
