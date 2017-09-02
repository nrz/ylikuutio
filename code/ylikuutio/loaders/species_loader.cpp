#include "species_loader.hpp"
#include "species_loader_struct.hpp"
#include "obj_loader.hpp"
#include "ascii_grid_loader.hpp"
#include "bmp_heightmap_loader.hpp"
#include "srtm_heightmap_loader.hpp"

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
            SpeciesLoaderStruct species_loader_struct,
            std::vector<glm::vec3>& out_vertices,
            std::vector<glm::vec2>& out_UVs,
            std::vector<glm::vec3>& out_normals,
            int32_t& image_width,
            int32_t& image_height)
    {
        if (species_loader_struct.model_file_format.compare("obj") == 0 || species_loader_struct.model_file_format.compare("OBJ") == 0)
        {
            return loaders::load_OBJ(
                    species_loader_struct.model_filename.c_str(),
                    out_vertices,
                    out_UVs,
                    out_normals);
        }
        else if (species_loader_struct.model_file_format.compare("srtm") == 0 || species_loader_struct.model_file_format.compare("SRTM") == 0)
        {
            species_loader_struct.latitude = -16.50f; // in degrees.
            species_loader_struct.longitude = -68.15f; // in degrees.

            return loaders::load_SRTM_world(
                    species_loader_struct.model_filename,
                    species_loader_struct.latitude,
                    species_loader_struct.longitude,
                    species_loader_struct.world_radius,
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
            return loaders::load_BMP_world(
                    species_loader_struct.model_filename,
                    out_vertices,
                    out_UVs,
                    out_normals,
                    image_width,
                    image_height,
                    species_loader_struct.color_channel,
                    species_loader_struct.x_step,
                    species_loader_struct.z_step,
                    species_loader_struct.triangulation_type);
        }
        else if (species_loader_struct.model_file_format.compare("ascii_grid") == 0 || species_loader_struct.model_file_format.compare("ASCII_grid") == 0)
        {
            return loaders::load_ASCII_grid(
                    species_loader_struct.model_filename,
                    out_vertices,
                    out_UVs,
                    out_normals,
                    species_loader_struct.x_step,
                    species_loader_struct.z_step,
                    species_loader_struct.triangulation_type);
        }

        std::cerr << "no model was loaded!\n";
        std::cerr << "model file format: " << species_loader_struct.model_file_format << "\n";
        return false;
    }
}
