// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif

#include "transformation.hpp"
#include "code/ylikuutio/geometry/degrees_to_radians.hpp"
#include "code/ylikuutio/geometry/spherical_terrain_struct.hpp"
#include "code/ylikuutio/data/spherical_coordinates_struct.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cerr
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace yli::geometry
{
    glm::vec3 transform_planar_world_vertex_into_cartesian_vertex(
            const glm::vec3& planar_world_vertex,
            const float sphere_radius)
    {
        yli::data::SphericalCoordinatesStruct spherical_vertex;
        spherical_vertex.rho = planar_world_vertex.y + sphere_radius;       // rho is altitude.
        spherical_vertex.theta = yli::geometry::degrees_to_radians(planar_world_vertex.x); // theta is longitude, the azimuthal angle.
        spherical_vertex.phi = yli::geometry::degrees_to_radians(-planar_world_vertex.z);  // phi is latitude, the polar angle.

        glm::vec3 cartesian_vertex;
        cartesian_vertex.x = spherical_vertex.rho * sin(spherical_vertex.theta) * cos(spherical_vertex.phi);
        cartesian_vertex.y = spherical_vertex.rho * sin(spherical_vertex.theta) * sin(spherical_vertex.phi);
        cartesian_vertex.z = spherical_vertex.rho * cos(spherical_vertex.theta);

        return cartesian_vertex;
    }

    void transform_coordinates_to_curved_surface(
            const TransformationStruct& transformation_struct,
            std::vector<glm::vec3>& temp_vertices)
    {
        const std::size_t image_width = transformation_struct.image_width;
        const std::size_t image_height = transformation_struct.image_height;
        const float sphere_radius = transformation_struct.sphere_radius;
        const bool is_bilinear_interpolation_in_use = transformation_struct.is_bilinear_interpolation_in_use;
        yli::geometry::SphericalTerrainStruct spherical_terrain_struct = transformation_struct.spherical_terrain_struct;

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

        const float latitude_step_in_degrees = spherical_terrain_struct.SRTM_latitude_step_in_degrees;
        // float latitude_step_in_degrees = (360.0f / image_height); // for testing, creates a sphere always.
        std::cout << "latitude step in degrees: " << latitude_step_in_degrees << "\n";

        const float longitude_step_in_degrees = spherical_terrain_struct.SRTM_longitude_step_in_degrees;
        // float longitude_step_in_degrees = (360.0f / image_width); // for testing, creates a sphere always.
        std::cout << "longitude step in degrees: " << longitude_step_in_degrees << "\n";

        float current_latitude_in_degrees = spherical_terrain_struct.southern_latitude;

        std::size_t temp_vertices_i = 0;

        // Loop through `temp_vertices` and transform all vertices from spherical coordinates to cartesian coordinates.
        for (std::size_t z = 0; z < image_height; z++)
        {
            // loop through all latitudes.

            float current_longitude_in_degrees = spherical_terrain_struct.western_longitude;

            for (uint32_t x = 0; x < image_width; x++)
            {
                glm::vec3 spherical_terrain_vertex = temp_vertices[temp_vertices_i];
                spherical_terrain_vertex.x = static_cast<float>(current_longitude_in_degrees);
                spherical_terrain_vertex.z = static_cast<float>(current_latitude_in_degrees);
                temp_vertices[temp_vertices_i++] = yli::geometry::transform_planar_world_vertex_into_cartesian_vertex(spherical_terrain_vertex, sphere_radius);

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

            float current_latitude_in_degrees = spherical_terrain_struct.southern_latitude;

            for (std::size_t z = 1; z < image_height; z++)
            {
                // loop through all latitudes.

                float current_longitude_in_degrees = spherical_terrain_struct.western_longitude;

                for (std::size_t x = 1; x < image_width; x++)
                {
                    glm::vec3 spherical_terrain_vertex = temp_vertices[temp_vertices_i];
                    spherical_terrain_vertex.x = static_cast<float>(current_longitude_in_degrees);
                    spherical_terrain_vertex.z = static_cast<float>(current_latitude_in_degrees);
                    temp_vertices[temp_vertices_i++] = yli::geometry::transform_planar_world_vertex_into_cartesian_vertex(spherical_terrain_vertex, sphere_radius);

                    current_longitude_in_degrees += longitude_step_in_degrees;
                }
                current_latitude_in_degrees += latitude_step_in_degrees;
            }
        }
    }
}
