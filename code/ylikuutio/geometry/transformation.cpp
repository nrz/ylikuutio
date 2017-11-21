#ifndef PI
#define PI 3.14159265359f
#endif

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

#include "transformation.hpp"
#include "code/ylikuutio/geometry/spherical_terrain_struct.hpp"
#include "code/ylikuutio/common/spherical_coordinates_struct.hpp"
#include "code/ylikuutio/common/pi.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <vector>   // std::vector
#include <stdint.h> // uint32_t etc.

namespace geometry
{
    glm::vec3 transform_planar_world_vertex_into_cartesian_vertex(
            glm::vec3 planar_world_vertex,
            const double sphere_radius)
    {
        SphericalCoordinatesStruct spherical_vertex;
        spherical_vertex.rho = planar_world_vertex.y + sphere_radius;       // rho is altitude.
        spherical_vertex.theta = DEGREES_TO_RADIANS(planar_world_vertex.x); // theta is longitude, the azimuthal angle.
        spherical_vertex.phi = DEGREES_TO_RADIANS(-planar_world_vertex.z);  // phi is latitude, the polar angle.

        glm::vec3 cartesian_vertex;
        cartesian_vertex.x = (GLfloat) (spherical_vertex.rho * sin(spherical_vertex.theta) * cos(spherical_vertex.phi));
        cartesian_vertex.y = (GLfloat) (spherical_vertex.rho * sin(spherical_vertex.theta) * sin(spherical_vertex.phi));
        cartesian_vertex.z = (GLfloat) (spherical_vertex.rho * cos(spherical_vertex.theta));

        return cartesian_vertex;
    }

    void transform_coordinates_to_curved_surface(
            const TransformationStruct transformation_struct,
            std::vector<glm::vec3>& temp_vertices)
    {
        uint32_t image_width = transformation_struct.image_width;
        uint32_t image_height = transformation_struct.image_height;
        double sphere_radius = transformation_struct.sphere_radius;
        bool is_bilinear_interpolation_in_use = transformation_struct.is_bilinear_interpolation_in_use;
        geometry::SphericalTerrainStruct spherical_terrain_struct = transformation_struct.spherical_terrain_struct;

        // 3a. Transform spherical coordinates loaded from file (and computed this far as being in horizontal plane) to a curved surface.
        //
        // Wikipedia:
        // https://en.wikipedia.org/wiki/List_of_common_coordinate_transformations#From_spherical_coordinates
        //
        // x = rho * sin(theta) * cos(phi)
        // y = rho * sin(theta) * sin(phi)
        // z = rho * cos(theta)

        std::cout << "transforming spherical coordinates loaded from file to cartesian coordinates.\n";
        std::cout << "radius: " << sphere_radius << "\n";

        double latitude_step_in_degrees = spherical_terrain_struct.SRTM_latitude_step_in_degrees;
        // double latitude_step_in_degrees = (360.0f / image_height); // for testing, creates a sphere always.
        std::cout << "latitude step in degrees: " << latitude_step_in_degrees << "\n";

        double longitude_step_in_degrees = spherical_terrain_struct.SRTM_longitude_step_in_degrees;
        // double longitude_step_in_degrees = (360.0f / image_width); // for testing, creates a sphere always.
        std::cout << "longitude step in degrees: " << longitude_step_in_degrees << "\n";

        double current_latitude_in_degrees = spherical_terrain_struct.southern_latitude;

        GLuint temp_vertices_i = 0;

        // Loop through `temp_vertices` and transform all vertices from spherical coordinates to cartesian coordinates.
        for (uint32_t z = 0; z < image_height; z++)
        {
            // loop through all latitudes.

            double current_longitude_in_degrees = spherical_terrain_struct.western_longitude;

            for (uint32_t x = 0; x < image_width; x++)
            {
                glm::vec3 spherical_terrain_vertex = temp_vertices[temp_vertices_i];
                spherical_terrain_vertex.x = (GLfloat) current_longitude_in_degrees;
                spherical_terrain_vertex.z = (GLfloat) current_latitude_in_degrees;
                temp_vertices[temp_vertices_i++] = geometry::transform_planar_world_vertex_into_cartesian_vertex(spherical_terrain_vertex, sphere_radius);

                current_longitude_in_degrees += longitude_step_in_degrees;
            }
            current_latitude_in_degrees += latitude_step_in_degrees;
        }

        if (is_bilinear_interpolation_in_use)
        {
            // 3b. For bilinear interpolation: Transform interpolated coordinates (and computed this far as being in horizontal plane) to a curved surface.
            //
            // Wikipedia:
            // https://en.wikipedia.org/wiki/List_of_common_coordinate_transformations#From_spherical_coordinates
            //
            // x = rho * sin(theta) * cos(phi)
            // y = rho * sin(theta) * sin(phi)
            // z = rho * cos(theta)

            std::cout << "transforming interpolated spherical coordinates to cartesian coordinates.\n";
            std::cout << "radius: " << sphere_radius << "\n";

            double current_latitude_in_degrees = spherical_terrain_struct.southern_latitude;

            for (uint32_t z = 1; z < image_height; z++)
            {
                // loop through all latitudes.

                double current_longitude_in_degrees = spherical_terrain_struct.western_longitude;

                for (uint32_t x = 1; x < image_width; x++)
                {
                    glm::vec3 spherical_terrain_vertex = temp_vertices[temp_vertices_i];
                    spherical_terrain_vertex.x = (GLfloat) current_longitude_in_degrees;
                    spherical_terrain_vertex.z = (GLfloat) current_latitude_in_degrees;
                    temp_vertices[temp_vertices_i++] = geometry::transform_planar_world_vertex_into_cartesian_vertex(spherical_terrain_vertex, sphere_radius);

                    current_longitude_in_degrees += longitude_step_in_degrees;
                }
                current_latitude_in_degrees += latitude_step_in_degrees;
            }
        }
    }
}
