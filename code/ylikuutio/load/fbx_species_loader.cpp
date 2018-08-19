#include "fbx_species_loader.hpp"
#include "code/ylikuutio/file/file_loader.hpp"
#include <ofbx.h>

// OpenFBX wants `u8` == `unsigned char`.
typedef unsigned char u8;

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace load
    {
        bool load_FBX(
                const std::string& filename,
                const std::size_t mesh_i,
                std::vector<glm::vec3>& out_vertices,
                std::vector<glm::vec2>& out_UVs,
                std::vector<glm::vec3>& out_normals,
                const bool is_debug_mode)
        {
            // Functions and data of interest in OpenFBX:
            // struct TakeInfo
            // {
            //     DataView name;
            //     DataView filename;
            //     double local_time_from;
            //     double local_time_to;
            //     double reference_time_from;
            //     double reference_time_to;
            // };
            //
            // IScene* load(const u8* data, int size)
            std::vector<unsigned char> data_vector = yli::file::binary_slurp(filename);

            // OpenFBX wants `u8` == `unsigned char`.
            const u8* data = reinterpret_cast<const u8*>(data_vector.data());
            int size = data_vector.size();

            if (is_debug_mode)
            {
                std::cout << "loaded FBX data vector size: " << size << "\n";
            }

            ofbx::IScene* ofbx_iscene = ofbx::load(data, size);

            if (ofbx_iscene == nullptr)
            {
                std::cerr << "Error: ofbx_iscene is nullptr!\n";
                return false;
            }

            const int temp_mesh_count = ofbx_iscene->getMeshCount(); // `getMeshCount()` returns `int`.

            if (temp_mesh_count < 0)
            {
                std::cerr << "Error: mesh count is negative!\n";
                return false;
            }

            const std::size_t mesh_count = static_cast<std::size_t>(temp_mesh_count);

            if (mesh_i >= mesh_count)
            {
                std::cerr << "Error: mesh_i >= mesh_count\n";
                return false;
            }

            const ofbx::Mesh* mesh = ofbx_iscene->getMesh(mesh_i);

            if (mesh == nullptr)
            {
                std::cerr << "Error: mesh is nullptr!\n";
                return false;
            }

            const ofbx::Geometry* geometry = mesh->getGeometry();

            if (geometry == nullptr)
            {
                std::cerr << "Error: geometry is nullptr!\n";
                return false;
            }

            const int material_count = mesh->getMaterialCount();

            if (is_debug_mode)
            {
                std::cout << filename << ": mesh " << mesh_i << ": getMaterialCount(): " << material_count << "\n";
            }

            const int temp_vertex_count = geometry->getVertexCount();

            if (is_debug_mode)
            {
                std::cout << filename << ": mesh " << mesh_i << ": getVertexCount(): " << temp_vertex_count << "\n";
            }

            if (temp_vertex_count < 0)
            {
                std::cerr << "vertex count is negative!\n";
                return false;
            }

            const std::size_t vertex_count = static_cast<std::size_t>(temp_vertex_count);

            const ofbx::Vec3* vertices = geometry->getVertices();

            if (vertices == nullptr)
            {
                std::cerr << "Error: vertices is nullptr!\n";
                return false;
            }

            const ofbx::Vec3* normals = geometry->getNormals();

            if (normals == nullptr)
            {
                std::cerr << "Error: normals is nullptr!\n";
                return false;
            }

            for (std::size_t i = 0; i < vertex_count; i++)
            {
                // vertices.
                glm::vec3 vertex = { vertices[i].x, vertices[i].y, vertices[i].z };
                out_vertices.push_back(vertex);
            }

            const ofbx::Vec2* uvs = geometry->getUVs();

            if (uvs == nullptr)
            {
                // `uvs` should not be `nullptr`.
                std::cerr << "Error: uvs is nullptr!\n";
            }
            else
            {
                for (std::size_t vertex_i = 0; vertex_i < vertex_count; vertex_i++)
                {
                    // UVs.
                    glm::vec2 uv = { uvs[vertex_i].x, uvs[vertex_i].y };
                    out_UVs.push_back(uv);
                }
            }

            for (std::size_t i = 0; i < vertex_count; i++)
            {
                // Normals.
                glm::vec3 normal = { normals[i].x, normals[i].y, normals[i].z };
                out_normals.push_back(normal);
            }

            return true;
        }
    }
}
