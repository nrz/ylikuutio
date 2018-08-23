#include "symbiosis_loader.hpp"
#include "symbiosis_loader_struct.hpp"
#include "fbx_symbiosis_loader.hpp"
#include <ofbx.h>

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
#include <cstddef>       // std::size_t
#include <iostream>      // std::cout, std::cin, std::cerr
#include <stdint.h>      // uint32_t etc.
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

namespace yli
{
    namespace load
    {
        bool load_symbiosis(
                SymbiosisLoaderStruct& symbiosis_loader_struct,
                std::vector<std::vector<glm::vec3>>& out_vertices,
                std::vector<std::vector<glm::vec2>>& out_UVs,
                std::vector<std::vector<glm::vec3>>& out_normals,
                std::vector<std::vector<GLuint>>& indices,
                std::vector<std::vector<glm::vec3>>& indexed_vertices,
                std::vector<std::vector<glm::vec2>>& indexed_UVs,
                std::vector<std::vector<glm::vec3>>& indexed_normals,
                std::unordered_map<const ofbx::Texture*, std::vector<int32_t>>& ofbx_diffuse_texture_mesh_map,
                std::vector<const ofbx::Mesh*>& ofbx_meshes,
                std::vector<const ofbx::Texture*>& ofbx_diffuse_texture_vector,
                std::vector<const ofbx::Texture*>& ofbx_normal_texture_vector,
                std::vector<const ofbx::Texture*>& ofbx_count_texture_vector,
                std::size_t& mesh_count,
                bool& vram_buffer_in_use,
                const bool is_debug_mode)
        {
            bool model_loading_result = false;

            if (symbiosis_loader_struct.model_file_format == "fbx" || symbiosis_loader_struct.model_file_format == "FBX")
            {
                model_loading_result = yli::load::load_FBX(
                        symbiosis_loader_struct.model_filename,
                        out_vertices,
                        out_UVs,
                        out_normals,
                        ofbx_diffuse_texture_mesh_map,
                        ofbx_meshes,
                        ofbx_diffuse_texture_vector,
                        ofbx_normal_texture_vector,
                        ofbx_count_texture_vector,
                        mesh_count,
                        is_debug_mode);
            }
            else
            {
                std::cerr << "no model was loaded!\n";
                std::cerr << "model file format: " << symbiosis_loader_struct.model_file_format << "\n";
                return false;
            }

            // TODO: Compute the graph of this object type to enable object vertex modification!
            return model_loading_result;
        }
    }
}
