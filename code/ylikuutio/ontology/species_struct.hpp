// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
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

#ifndef __YLIKUUTIO_ONTOLOGY_SPECIES_STRUCT_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_SPECIES_STRUCT_HPP_INCLUDED

#include "model_struct.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>   // NAN, std::isnan, std::pow
#include <cstddef> // std::size_t
#include <limits>  // std::numeric_limits
#include <string>  // std::string
#include <vector>  // std::vector

namespace yli::ontology
{
    class Scene;
    class Shader;
    class Material;
    class SymbiontMaterial;
    class ShapeshifterTransformation;

    struct SpeciesStruct: public yli::ontology::ModelStruct
    {
        SpeciesStruct()
        {
            // constructor.
        }

        std::string model_filename;                         // filename of the model file.
        std::string model_file_format;                      // type of the model file. supported file formats so far:
                                                            // `"bmp"`/`"BMP"` - BMP heightmap.
                                                            // `"fbx"`/`"FBX"` - FBX model.
                                                            // `"obj"`/`"OBJ"` - OBJ model.
                                                            // `"srtm"`/`"SRTM"` - SRTM heightmap.
                                                            // `"asc"`/`"ascii_grid"`/`"ASCII_grid"` - ASCII grid.
        std::string color_channel;                          // color channel to use for altitude data, for BMP model files.
        std::string triangulation_type { "bilinear_interpolation" }; // `"bilinear_interpolation"`, `"southwest_northeast_edges"`, `"southeast_northwest_edges"`.
        std::vector<glm::vec3> vertices;                    // for `SymbiontSpecies`.
        std::vector<glm::vec2> uvs;                         // for `SymbiontSpecies`.
        std::vector<glm::vec3> normals;                     // for `SymbiontSpecies`.
        glm::vec3 light_position { glm::vec3(0.0f, 0.0f, 0.0f) }; // light position.
        yli::ontology::Scene* scene                                            { nullptr }; // Pointer to `Scene` object.
        yli::ontology::Shader* shader                                          { nullptr }; // Pointer to `Shader` object.
        yli::ontology::Material* material                                      { nullptr }; // Pointer to `Material` object.
        yli::ontology::SymbiontMaterial* symbiont_material                     { nullptr }; // Pointer to `SymbiontMaterial` object.
        yli::ontology::ShapeshifterTransformation* shapeshifter_transformation { nullptr }; // Pointer to `ShapeshifterTransformation` object.
        std::size_t vertex_count { std::numeric_limits<std::size_t>::max() };               // For `SymbiontSpecies`.
        std::size_t mesh_i  { 0 };    // for FBX.
        std::size_t x_step  { 1 };    // step in x-dimension for input data (set to 1 to load all data points/measurements).
        std::size_t z_step  { 1 };    // step in z-dimension for input data (set to 1 to load all data points/measurements).
        float latitude      { 0.0f }; // in degrees, for SRTM model files.
        float longitude     { 0.0f }; // in degrees, for SRTM model files.
        float planet_radius { NAN };  // radius of sea level in kilometers. used only for terrains (planets and moons). `6371.0f` for Earth.
        float divisor       { 1.0f }; // value by which SRTM values are divided to convert them to kilometers.
        float water_level   { -1.0f * std::numeric_limits<float>::infinity() }; // water level in meters. used only for terrains (planets and moons).
        bool is_terrain                   { false };                          // Terrains (planets and moons) currently neither rotate nor translate.
        bool is_symbiont_species          { false };                          // By default `Species` are not `SymbiontSpecies`.
        bool opengl_in_use                { true };                           // If `opengl_in_use` is `false`, then no OpenGL-specific code shall be executed.
        bool use_real_texture_coordinates { true };
    };
}

#endif
