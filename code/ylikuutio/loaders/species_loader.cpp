#include "species_loader.hpp"
#include "species_loader_struct.hpp"
#include "obj_loader.hpp"
#include "fbx_species_loader.hpp"
#include "ascii_grid_loader.hpp"
#include "bmp_heightmap_loader.hpp"
#include "srtm_heightmap_loader.hpp"
#include "code/ylikuutio/ontology/vboindexer.hpp"

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
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace loaders
{
    bool load_species(
            SpeciesLoaderStruct& species_loader_struct,
            std::vector<glm::vec3>& out_vertices,
            std::vector<glm::vec2>& out_UVs,
            std::vector<glm::vec3>& out_normals,
            std::vector<GLuint>& indices,
            std::vector<glm::vec3>& indexed_vertices,
            std::vector<glm::vec2>& indexed_UVs,
            std::vector<glm::vec3>& indexed_normals,
            GLuint* vertexbuffer,
            GLuint* uvbuffer,
            GLuint* normalbuffer,
            GLuint* elementbuffer,
            const bool is_debug_mode)
    {
        bool model_loading_result = false;

        if (species_loader_struct.model_file_format.compare("obj") == 0 || species_loader_struct.model_file_format.compare("OBJ") == 0)
        {
            model_loading_result = loaders::load_OBJ(
                    species_loader_struct.model_filename.c_str(),
                    out_vertices,
                    out_UVs,
                    out_normals);
        }
        else if (species_loader_struct.model_file_format.compare("fbx") == 0 || species_loader_struct.model_file_format.compare("FBX") == 0)
        {
            model_loading_result = loaders::load_FBX(
                    species_loader_struct.model_filename,
                    species_loader_struct.mesh_i,
                    out_vertices,
                    out_UVs,
                    out_normals,
                    is_debug_mode);

            std::cout << species_loader_struct.model_filename << " loaded successfully.\n";
        }
        else if (species_loader_struct.model_file_format.compare("srtm") == 0 || species_loader_struct.model_file_format.compare("SRTM") == 0)
        {
            model_loading_result = loaders::load_SRTM_terrain(
                    species_loader_struct.model_filename,
                    species_loader_struct.latitude,
                    species_loader_struct.longitude,
                    species_loader_struct.planet_radius,
                    species_loader_struct.divisor,
                    out_vertices,
                    out_UVs,
                    out_normals,
                    species_loader_struct.x_step,
                    species_loader_struct.z_step,
                    species_loader_struct.triangulation_type);
        }
        else if (species_loader_struct.model_file_format.compare("bmp") == 0 || species_loader_struct.model_file_format.compare("BMP") == 0)
        {
            model_loading_result = loaders::load_BMP_terrain(
                    species_loader_struct.model_filename,
                    out_vertices,
                    out_UVs,
                    out_normals,
                    species_loader_struct.image_width_pointer,
                    species_loader_struct.image_height_pointer,
                    species_loader_struct.color_channel,
                    species_loader_struct.x_step,
                    species_loader_struct.z_step,
                    species_loader_struct.triangulation_type);
        }
        else if (species_loader_struct.model_file_format.compare("ascii_grid") == 0 || species_loader_struct.model_file_format.compare("ASCII_grid") == 0)
        {
            model_loading_result = loaders::load_ASCII_grid(
                    species_loader_struct.model_filename,
                    out_vertices,
                    out_UVs,
                    out_normals,
                    species_loader_struct.x_step,
                    species_loader_struct.z_step,
                    species_loader_struct.triangulation_type);
        }
        else
        {
            std::cerr << "no model was loaded!\n";
            std::cerr << "model file format: " << species_loader_struct.model_file_format << "\n";
            return false;
        }

        std::cout << "Indexing...\n";

        // Fill the index buffer.
        ontology::indexVBO(
                out_vertices,
                out_UVs,
                out_normals,
                indices,
                indexed_vertices,
                indexed_UVs,
                indexed_normals);

        std::cout << "Indexing completed successfully.\n";

        // Load it into a VBO.
        glGenBuffers(1, vertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, *vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);

        glGenBuffers(1, uvbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, *uvbuffer);
        glBufferData(GL_ARRAY_BUFFER, indexed_UVs.size() * sizeof(glm::vec2), &indexed_UVs[0], GL_STATIC_DRAW);

        glGenBuffers(1, normalbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, *normalbuffer);
        glBufferData(GL_ARRAY_BUFFER, indexed_normals.size() * sizeof(glm::vec3), &indexed_normals[0], GL_STATIC_DRAW);

        glGenBuffers(1, elementbuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *elementbuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0] , GL_STATIC_DRAW);

        // TODO: Compute the graph of this object type to enable object vertex modification!
        return model_loading_result;
    }
}
