#include "symbiosis_loader.hpp"
#include "symbiosis_loader_struct.hpp"
#include "fbx_symbiosis_loader.hpp"

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

namespace loaders
{
    bool load_symbiosis(
            SymbiosisLoaderStruct& symbiosis_loader_struct,
            std::vector<std::vector<glm::vec3>>& out_vertices,
            std::vector<std::vector<glm::vec2>>& out_UVs,
            std::vector<std::vector<glm::vec3>>& out_normals,
            std::vector<std::vector<GLuint>>& indices,
            std::vector<std::vector<glm::vec3>>& indexed_vertices,
            std::vector<std::vector<glm::vec2>>& indexed_UVs,
            std::vector<std::vector<glm::vec3>>& indexed_normals)
    {
        bool model_loading_result = false;

        if (symbiosis_loader_struct.model_file_format.compare("fbx") == 0 || symbiosis_loader_struct.model_file_format.compare("FBX") == 0)
        {
            model_loading_result = loaders::load_FBX(
                    symbiosis_loader_struct.model_filename,
                    out_vertices,
                    out_UVs,
                    out_normals);
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
