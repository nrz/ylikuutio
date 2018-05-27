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
#include <iostream> // std::cout, std::cin, std::cerr
#include <string>   // std::string
#include <vector>   // std::vector

namespace loaders
{
    bool load_FBX(
            const std::string& filename,
            const int32_t mesh_i,
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
        std::vector<unsigned char> data_vector = file::binary_slurp(filename);

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

        int32_t mesh_count = static_cast<int32_t>(ofbx_iscene->getMeshCount()); // `getMeshCount()` returns `int`.

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

        // TODO: finalize the implementation of `ontology::Symbiosis`
        // to be able to support for different materials!
        int material_count = mesh->getMaterialCount(); // TODO: use this in  `ontology::Symbiosis` entities!

        if (is_debug_mode)
        {
            std::cout << filename << ": mesh " << mesh_i << ": getMaterialCount(): " << material_count << "\n";
        }

        int vertex_count = geometry->getVertexCount();

        if (is_debug_mode)
        {
            std::cout << filename << ": mesh " << mesh_i << ": getVertexCount(): " << vertex_count << "\n";
        }

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

        const ofbx::Vec2* uvs = geometry->getUVs();

        if (uvs == nullptr)
        {
            std::cerr << "Error: uvs is nullptr!\n";
            return false;
        }

        for (int i = 0; i < vertex_count; i++)
        {
            // vertices.
            glm::vec3 vertex = { vertices[i].x, vertices[i].y, vertices[i].z };
            out_vertices.push_back(vertex);
        }

        for (int i = 0; i < vertex_count; i++)
        {
            // UVs.
            glm::vec2 uv = { uvs[i].x, uvs[i].y };
            out_UVs.push_back(uv);
        }

        for (int i = 0; i < vertex_count; i++)
        {
            // Normals.
            glm::vec3 normal = { normals[i].x, normals[i].y, normals[i].z };
            out_normals.push_back(normal);
        }

        return true;
    }
}
