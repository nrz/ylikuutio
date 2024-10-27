// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
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

#ifndef YLIKUUTIO_ONTOLOGY_MESH_PROVIDER_STRUCT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_MESH_PROVIDER_STRUCT_HPP_INCLUDED

#include "entity_struct.hpp"

// Include GLM
#ifndef GLM_GLM_HPP_INCLUDED
#define GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <limits>   // std::numeric_limits
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <variant>  // std::monostate, std::variant
#include <vector>   // std::vector

namespace yli::ontology
{
    class Ecosystem;
    class Scene;
    class Pipeline;
    class Material;
    class SymbiontMaterial;
    class ShapeshifterTransformation;
    class VectorFont;

    struct MeshProviderStruct : public EntityStruct
    {
        MeshProviderStruct() = default;

        MeshProviderStruct(
                Ecosystem* const ecosystem_parent,
                Pipeline* const pipeline,
                Material* const material_master)
            : parent                      { ecosystem_parent },
            pipeline                      { pipeline },
            material_or_symbiont_material { material_master }
        {
        }

        MeshProviderStruct(
                Scene* const scene_parent,
                Pipeline* const pipeline,
                Material* const material_master)
            : parent                      { scene_parent },
            pipeline                      { pipeline },
            material_or_symbiont_material { material_master }
        {
        }

        MeshProviderStruct(
                ShapeshifterTransformation* const shapeshifter_transformation,
                Pipeline* const pipeline,
                Material* const material_master)
            : parent                      { shapeshifter_transformation },
            pipeline                      { pipeline },
            material_or_symbiont_material { material_master }
        {
        }

        MeshProviderStruct(
                const std::string& parent,
                Pipeline* const pipeline,
                Material* const material_master)
            : parent                      { parent },
            pipeline                      { pipeline },
            material_or_symbiont_material { material_master }
        {
        }

        MeshProviderStruct(
                Pipeline* const pipeline,
                SymbiontMaterial* const symbiont_material)
            : pipeline                    { pipeline },
            material_or_symbiont_material { symbiont_material }
        {
        }

        explicit MeshProviderStruct(
                VectorFont* const vector_font_parent)
            : parent { vector_font_parent }
        {
        }

        explicit MeshProviderStruct(
                const std::string& vector_font_parent)
            : parent { vector_font_parent }
        {
        }

        std::string model_filename;    // Filename of the model file.
        std::string model_file_format; // Type of the model file. Supported file formats so far:
                                       // `"png"`/`"PNG"` - PNG heightmap.
                                       // `"fbx"`/`"FBX"` - FBX model.
                                       // `"obj"`/`"OBJ"` - OBJ model.
                                       // `"srtm"`/`"SRTM"` - SRTM heightmap.
                                       // `"asc"`/`"ascii_grid"`/`"ASCII_grid"` - ASCII grid.
        std::string color_channel;     // color channel to use for altitude data, for PNG model files.
        float divisor       { 1.0f };  // Value by which SRTM values are divided to convert them to kilometers.
        float latitude      { 0.0f };  // In degrees, for SRTM model files.
        float longitude     { 0.0f };  // In degrees, for SRTM model files.
        uint32_t mesh_i     { 0 };     // For FBX.
        uint32_t x_step     { 1 };     // Step in x-dimension for input data (set to 1 to load all data points/measurements).
        uint32_t y_step     { 1 };     // Step in y-dimension for input data (set to 1 to load all data points/measurements).
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec2> uvs;
        std::vector<glm::vec3> normals;
        std::variant<
            std::monostate,
            Ecosystem*,
            Scene*,
            ShapeshifterTransformation*,
            VectorFont*,
            std::string> parent {};
        Pipeline* pipeline                     { nullptr };
        std::variant<std::monostate, Material*, SymbiontMaterial*> material_or_symbiont_material {};
        uint32_t vertex_count { std::numeric_limits<uint32_t>::max() };
        bool use_real_texture_coordinates { true };
    };
}

#endif
