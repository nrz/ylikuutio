#ifndef __TRANSFORMATION_HPP_INCLUDED
#define __TRANSFORMATION_HPP_INCLUDED

#include "code/ylikuutio/geometry/transformation_struct.hpp"

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
        glm::vec3 transform_planar_world_vertex_into_cartesian_vertex(
                const glm::vec3& planar_world_vertex,
                const double sphere_radius);

        void transform_coordinates_to_curved_surface(
                const yli::geometry::TransformationStruct& transformation_struct,
                std::vector<glm::vec3>& temp_vertices);
    }
}

#endif
