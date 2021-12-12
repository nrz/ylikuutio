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

#ifndef __YLIKUUTIO_ONTOLOGY_MODEL_STRUCT_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_MODEL_STRUCT_HPP_INCLUDED

#include "entity_struct.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <limits>   // std::numeric_limits
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::ontology
{
    class Scene;
    class Shader;
    class Material;
    class SymbiontMaterial;
    class ShapeshifterTransformation;
    class VectorFont;

    struct ModelStruct: public yli::ontology::EntityStruct
    {
        ModelStruct()
        {
            // constructor.
        }

        std::string model_filename;                         // Filename of the model file.
        std::string model_file_format;                      // Type of the model file. Supported file formats so far:
                                                            // `"png"`/`"PNG"` - PNG heightmap.
                                                            // `"fbx"`/`"FBX"` - FBX model.
                                                            // `"obj"`/`"OBJ"` - OBJ model.
                                                            // `"srtm"`/`"SRTM"` - SRTM heightmap.
                                                            // `"asc"`/`"ascii_grid"`/`"ASCII_grid"` - ASCII grid.
        std::string color_channel;                          // color channel to use for altitude data, for PNG model files.
        std::string triangulation_type { "bilinear_interpolation" }; // `"bilinear_interpolation"`, `"southwest_northeast_edges"`, `"southeast_northwest_edges"`.
        float planet_radius { NAN };  // Radius of sea level in kilometers. Used only for terrains (planets and moons). `6371.0f` for Earth.
        float divisor       { 1.0f }; // Value by which SRTM values are divided to convert them to kilometers.
        float latitude      { 0.0f }; // In degrees, for SRTM model files.
        float longitude     { 0.0f }; // In degrees, for SRTM model files.
        uint32_t mesh_i     { 0 };    // For FBX.
        uint32_t x_step     { 1 };    // Step in x-dimension for input data (set to 1 to load all data points/measurements).
        uint32_t z_step     { 1 };    // Step in z-dimension for input data (set to 1 to load all data points/measurements).
        glm::vec3 light_position { 0.0f, 0.0f, 0.0f };
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec2> uvs;
        std::vector<glm::vec3> normals;
        yli::ontology::Scene* scene                                            { nullptr }; // Pointer to `Scene`.
        yli::ontology::Shader* shader                                          { nullptr }; // Pointer to `Shader`.
        yli::ontology::Material* material                                      { nullptr }; // Pointer to `Material`.
        yli::ontology::SymbiontMaterial* symbiont_material                     { nullptr }; // Pointer to `SymbiontMaterial`.
        yli::ontology::ShapeshifterTransformation* shapeshifter_transformation { nullptr }; // Pointer to `ShapeshifterTransformation`.
        yli::ontology::VectorFont* vector_font                                 { nullptr }; // pointer to `VectorFont`.
        std::vector<std::vector<glm::vec2>>* glyph_vertex_data { nullptr }; // For `Glyph`s.
        const char* glyph_name_pointer         { nullptr }; // We need only a pointer, because `Glyph`s are always created by the `VectorFont` constructor.
        const char* unicode_char_pointer       { nullptr }; // We need only a pointer, because `Glyph`s are always created by the `VectorFont` constructor.
        uint32_t vertex_count { std::numeric_limits<uint32_t>::max() };
        float water_level { -1.0f * std::numeric_limits<float>::infinity() }; // Water level in meters. used only for terrains (planets and moons).
        bool use_real_texture_coordinates { true };
    };
}

#endif
