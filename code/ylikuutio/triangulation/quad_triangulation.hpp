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

#ifndef YLIKUUTIO_TRIANGULATION_QUAD_TRIANGULATION_HPP_INCLUDED
#define YLIKUUTIO_TRIANGULATION_QUAD_TRIANGULATION_HPP_INCLUDED

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif

#include "triangulate_quads_struct.hpp"
#include "face_normals.hpp"
#include "vertex_normals.hpp"
#include "vertices.hpp"
#include "triangulation_enums.hpp"
#include "triangulation_templates.hpp"
#include "indexing.hpp"
#include "code/ylikuutio/geometry/spherical_terrain_struct.hpp"
#include "code/ylikuutio/geometry/transformation_struct.hpp"
#include "code/ylikuutio/geometry/transformation.hpp"

// Include GLM
#ifndef GLM_GLM_HPP_INCLUDED
#define GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cerr
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::triangulation
{
    template<typename T1>
        bool triangulate_quads(
                const T1* input_vertex_pointer,
                const yli::triangulation::TriangulateQuadsStruct& triangulate_quads_struct,
                std::vector<glm::vec3>& out_vertices,
                std::vector<glm::vec2>& out_uvs,
                std::vector<glm::vec3>& out_normals)
        {
            const std::size_t image_width = triangulate_quads_struct.image_width;
            const std::size_t image_height = triangulate_quads_struct.image_height;
            const std::size_t x_step = triangulate_quads_struct.x_step;
            const std::size_t z_step = triangulate_quads_struct.y_step;

            // Input vertices (`T1* input_vertex_pointer`)
            // can be `float`, `int32_t` or `uint32_t`.

            if (input_vertex_pointer == nullptr)
            {
                std::cerr << "ERROR: `yli::triangulation::triangulate_quads`: `input_vertex_pointer` is `nullptr`.\n";
                return false;
            }

            if (image_width < 2)
            {
                std::cerr << "ERROR: `yli::triangulation::triangulate_quads`: `image_width` is less than 2.\n";
                return false;
            }

            if (image_height < 2)
            {
                std::cerr << "ERROR: `yli::triangulation::triangulate_quads`: `image_height` is less than 2.\n";
                return false;
            }

            if (x_step < 1)
            {
                std::cerr << "ERROR: `yli::triangulation::triangulate_quads`: `x_step` is less than 1.\n";
                return false;
            }

            if (z_step < 1)
            {
                std::cerr << "ERROR: `yli::triangulation::triangulate_quads`: `z_step` is less than 1.\n";
                return false;
            }

            const std::size_t actual_image_width = (image_width - 1) / x_step + 1;
            const std::size_t actual_image_height = (image_height - 1) / z_step + 1;

            if (actual_image_width < 2)
            {
                std::cerr << "ERROR: `yli::triangulation::triangulate_quads`: `actual_image_width` is less than 2.\n";
                return false;
            }

            if (actual_image_height < 2)
            {
                std::cerr << "ERROR: `yli::triangulation::triangulate_quads`: `actual_image_height` is less than 2.\n";
                return false;
            }

            const std::string& triangulation_type = triangulate_quads_struct.triangulation_type;
            const float& sphere_radius = triangulate_quads_struct.sphere_radius;
            const yli::geometry::SphericalTerrainStruct& spherical_terrain_struct = triangulate_quads_struct.spherical_terrain_struct;

            bool is_bilinear_interpolation_in_use = false;
            bool is_southwest_northeast_edges_in_use = false;
            bool is_southeast_northwest_edges_in_use = false;
            std::size_t n_faces_for_each_vertex = 2; // split each quad into 2 triangles.

            std::cout << "Triangulation type in use: " << triangulation_type << "\n";

            if (triangulation_type == "bilinear_interpolation")
            {
                // *---*
                // |\ /|
                // | x |
                // |/ \|
                // *---*
                is_bilinear_interpolation_in_use = true;
                n_faces_for_each_vertex = 4;
            }
            else if (triangulation_type == "southwest_northeast_edges" || triangulation_type == "northeast_southwest_edges")
            {
                // *---*
                // |  /|
                // | / |
                // |/  |
                // *---*
                is_southwest_northeast_edges_in_use = true;
            }
            else if (triangulation_type == "southeast_northwest_edges" || triangulation_type == "northwest_southeast_edges")
            {
                // *---*
                // |\  |
                // | \ |
                // |  \|
                // *---*
                is_southeast_northwest_edges_in_use = true;
            }
            else
            {
                std::cerr << "ERROR: `yli::triangulation::triangulate_quads`: invalid triangulation type: " << triangulation_type << "\n";
                return false;
            }

            std::vector<glm::vec3> temp_vertices;
            std::vector<glm::vec2> temp_uvs;
            std::vector<glm::vec3> temp_normals;

            // Processing stages:
            // 1. Define the (float) vertices for vertices loaded from file, `emplace_back` to `temp_vertices` and `temp_uvs`.
            // 2. Interpolate the (float) vertices between, using bilinear interpolation, `emplace_back` to `temp_vertices` and `temp_uvs`.
            // 3a. Transform spherical coordinates loaded from file (and computed this far as being in horizontal plane) to a curved surface.
            // 3b. For bilinear interpolation: Transform interpolated coordinates (and computed this far as being in horizontal plane) to a curved surface.
            // 4. Compute the face normals, `emplace_back` to `face_normals`.
            // 5. Compute the vertex normals for vertices loaded from file and for interpolated vertices (for `"bilinear_interpolation"`), `emplace_back` to `temp_normals`.
            // 6. Loop through all vertices and `yli::geometry::output_triangle_vertices`.
            //
            // stg. `"bilinear_interpolation"`                                      `"southwest_northeast_edges"`               `"southeast_northwest_edges"`
            // 1.   `define_vertices`                                               `define_vertices`                           `define_vertices`
            // 2.   `interpolate_and_define_vertices_using_bilinear_interpolation`  N/A                                         N/A
            // 3.   `transform_coordinates_to_curved_surface`                       `transform_coordinates_to_curved_surface`   `transform_coordinates_to_curved_surface`
            // 4.   `compute_face_normals`                                          `compute_face_normals`                      `compute_face_normals`
            // 5.   `compute_vertex_normals`                                        `compute_vertex_normals`                    `compute_vertex_normals`
            // 6.   `define_vertices_uvs_and_normals`                               `define_vertices_uvs_and_normals`           `define_vertices_uvs_and_normals`
            //
            // stg. = stage

            // 1. Define the vertices for vertices loaded from file, `emplace_back` to `temp_vertices`.

            if (!yli::triangulation::define_vertices(
                        input_vertex_pointer,
                        image_width,
                        image_height,
                        x_step,
                        z_step,
                        triangulate_quads_struct.use_real_texture_coordinates,
                        temp_vertices,
                        temp_uvs))
            {
                return false;
            }

            std::cout << "Image width: " << image_width << " pixels.\n";
            std::cout << "Image height: " << image_height << " pixels.\n";

            std::cout << "Actual image width: " << actual_image_width << " pixels.\n";
            std::cout << "Actual image height: " << actual_image_height << " pixels.\n";

            const std::size_t n_faces = n_faces_for_each_vertex * (actual_image_width - 1) * (actual_image_height - 1);

            std::cout << "Number of faces: " << n_faces << ".\n";

            if (is_bilinear_interpolation_in_use)
            {
                // 2. Interpolate the vertices between, using bilinear interpolation, `emplace_back` to `temp_vertices`.
                if (!yli::triangulation::interpolate_and_define_vertices_using_bilinear_interpolation(
                            input_vertex_pointer,
                            image_width,
                            image_height,
                            x_step,
                            z_step,
                            triangulate_quads_struct.use_real_texture_coordinates,
                            temp_vertices,
                            temp_uvs))
                {
                    std::cerr << "ERROR: `yli::triangulation::triangulate_quads`: interpolating and defining vertices using bilinear interpolation failed.\n";
                    return false;
                }
            }

            if (!std::isnan(sphere_radius))
            {
                // 3a. Transform spherical coordinates loaded from file (and computed this far as being in horizontal plane) to a curved surface.
                // 3b. For bilinear interpolation: Transform interpolated coordinates (and computed this far as being in horizontal plane) to a curved surface.
                //
                // Wikipedia:
                // https://en.wikipedia.org/wiki/List_of_common_coordinate_transformations#From_spherical_coordinates
                //
                // x = rho * sin(theta) * cos(phi)
                // y = rho * sin(theta) * sin(phi)
                // z = rho * cos(theta)

                yli::geometry::TransformationStruct transformation_struct;
                transformation_struct.image_width = image_width;
                transformation_struct.image_height = image_height;
                transformation_struct.sphere_radius = sphere_radius;
                transformation_struct.is_bilinear_interpolation_in_use = is_bilinear_interpolation_in_use;
                transformation_struct.spherical_terrain_struct = spherical_terrain_struct;
                yli::geometry::transform_coordinates_to_curved_surface(transformation_struct, temp_vertices);
            }
            else
            {
                std::cout << "No coordinate transformation is needed.\n";
            }

            // 4. Compute the face normals, `emplace_back` to `face_normals`.
            // Triangle order: S - W - N - E.
            //
            // First triangle: center, southeast, southwest.
            // Second triangle: center, southwest, northwest.
            // Third triangle: center, northwest, northeast.
            // Fourth triangle: center, northeast, southeast.
            std::cout << "Computing face normals.\n";

            std::vector<glm::vec3> face_normal_vector_vec3;

            if (!yli::triangulation::compute_face_normals(
                        temp_vertices,
                        face_normal_vector_vec3,
                        actual_image_width,
                        actual_image_height,
                        is_bilinear_interpolation_in_use,
                        is_southwest_northeast_edges_in_use,
                        is_southeast_northwest_edges_in_use))
            {
                std::cerr << "ERROR: `yli::triangulation::triangulate_quads`: computing face normals failed.\n";
                return false;
            }

            // 5. Compute the vertex normals for vertices loaded from file, `emplace_back` to `temp_normals`.
            if (!yli::triangulation::compute_vertex_normals(
                        temp_normals,
                        face_normal_vector_vec3,
                        actual_image_width,
                        actual_image_height,
                        is_bilinear_interpolation_in_use,
                        is_southwest_northeast_edges_in_use,
                        is_southeast_northwest_edges_in_use))
            {
                std::cerr << "ERROR: `yli::triangulation::triangulate_quads`: computing vertex normals failed.\n";
                return false;
            }

            // 6. Loop through all vertices and `yli::geometry::output_triangle_vertices`.

            if (!yli::triangulation::define_vertices_uvs_and_normals(
                        triangulate_quads_struct,
                        temp_vertices,
                        temp_uvs,
                        temp_normals,
                        out_vertices,
                        out_uvs,
                        out_normals,
                        actual_image_width,
                        actual_image_height,
                        is_bilinear_interpolation_in_use,
                        is_southwest_northeast_edges_in_use,
                        is_southeast_northwest_edges_in_use))
            {
                std::cerr << "ERROR: `yli::triangulation::triangulate_quads`: defining vertices, UVs, and normals failed.\n";
                return false;
            }

            std::cout << "Number of vertices: " << out_vertices.size() << ".\n";
            std::cout << "Number of UVs: " << out_uvs.size() << ".\n";
            std::cout << "Number of normals: " << out_normals.size() << ".\n";

            return true;
        }
}

#endif
