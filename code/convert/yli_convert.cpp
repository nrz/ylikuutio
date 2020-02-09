// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
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

#include "code/ylikuutio/ontology/symbiosis.hpp"
#include "code/ylikuutio/ontology/symbiont_species.hpp"
#include "code/ylikuutio/ontology/symbiosis_struct.hpp"
#include "code/ylikuutio/command_line/command_line_master.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"

#include "assimp/scene.h"
#include "assimp/Exporter.hpp"
#include "assimp/types.h"

#define SDL_main main

#include "SDL.h"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <algorithm>     // std::transform
#include <cstddef>       // std::size_t
#include <cstdlib>       // EXIT_FAILURE, EXIT_SUCCESS
#include <iostream>      // std::cout, std::cin, std::cerr
#include <limits>        // std::numeric_limits
#include <string>        // std::string
#include <vector>        // std::vector

// `yli_convert` is a command-line tool to load and export 3D data between different formats.
//
// parameters:
// required:
// `--in=foo`  load 3D data from file `foo`.
// `--in foo`  load 3D data from file `foo`.
// `--out=bar` export 3D data into file `bar`.
// `--out bar` export 3D data into file `bar`.
//
// optional:
// `--informat=baz` assume file format `baz` (if `--informat` is left out, file format is deduced from the filename extension).
// `--informat baz` assume file format `baz` (if `--informat` is left out, file format is deduced from the filename extension).
// `--outformat=qux` export 3D data into file `qux` (if `--outformat` is left out, file format is deduced from the filename extension).
// `--outformat qux` export 3D data into file `qux` (if `--outformat` is left out, file format is deduced from the filename extension).
// `--intexture=quux` use texture data into file `quux` as the material for all meshes (eg. `.obj` input file).
// `--intexture quux` use texture data into file `quux` as the material for all meshes (eg. `.obj` input file).

namespace yli
{
    namespace ontology
    {
        class Universe;
    }
}

int main(const int argc, const char* argv[])
{
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    command_line_master.print_keys_and_values();

    if (!command_line_master.is_key("in"))
    {
        std::cerr << "ERROR: --in parameter is required!\n\nexample:\n\nyli_convert --in=foo --out=bar\n";
        exit(EXIT_FAILURE);
    }

    if (!command_line_master.is_key("out"))
    {
        std::cerr << "ERROR: --out parameter is required!\n\nexample:\n\nyli_convert --in=foo --out=bar\n";
        exit(EXIT_FAILURE);
    }

    const std::string& in_file = command_line_master.get_value("in");
    const std::string& out_file = command_line_master.get_value("out");

    std::string in_file_format = ""; // dummy value.

    if (command_line_master.is_key("informat"))
    {
        in_file_format = command_line_master.get_value("informat");
    }
    else
    {
        const char separator = '.';
        yli::string::extract_last_part_of_string(in_file, in_file_format, separator);
    }

    if (in_file_format.empty())
    {
        std::cerr << "ERROR: --informat is empty!\n";
        exit(EXIT_FAILURE);
    }

    std::cout << "in file format is " << in_file_format << "\n";

    std::string out_file_format = ""; // dummy value.

    if (command_line_master.is_key("outformat"))
    {
        out_file_format = command_line_master.get_value("outformat");
    }
    else
    {
        const char separator = '.';
        yli::string::extract_last_part_of_string(out_file, out_file_format, separator);
    }

    if (out_file_format.empty())
    {
        std::cerr << "ERROR: --outformat is empty!\n";
        exit(EXIT_FAILURE);
    }

    std::cout << "out file format is " << out_file_format << "\n";

    // OK, all required input is given in the correct format.

    // convert in file format & out file format into lowercase.
    std::transform(in_file_format.begin(), in_file_format.end(), in_file_format.begin(), ::tolower);
    std::transform(out_file_format.begin(), out_file_format.end(), out_file_format.begin(), ::tolower);

    if (in_file_format != "obj" && in_file_format != "fbx")
    {
        std::cerr << "ERROR: unsupported in file format: " << in_file_format << "\n";
        exit(EXIT_FAILURE);
    }

    // Always load the 3D object into a `yli::ontology::Symbiosis`.
    yli::ontology::SymbiosisStruct symbiosis_struct;
    symbiosis_struct.model_filename = in_file;
    symbiosis_struct.model_file_format = in_file_format;
    symbiosis_struct.triangulation_type = "bilinear_interpolation";
    symbiosis_struct.parent = nullptr;           // no parent.
    symbiosis_struct.opengl_in_use = false; // do not use VRAM buffer.
    yli::ontology::Universe* const universe = nullptr;
    const yli::ontology::Symbiosis symbiosis(universe, symbiosis_struct, nullptr);

    // Assimp usage example:
    // https://github.com/assimp/assimp/issues/203

    aiScene ai_scene;
    ai_scene.mRootNode = new aiNode();
    ai_scene.mNumMaterials = symbiosis.get_number_of_symbiont_materials();
    ai_scene.mMaterials = new aiMaterial*[ai_scene.mNumMaterials];
    ai_scene.mNumAnimations = 0;    // yli_convert does not yet support animations.
    ai_scene.mAnimations = nullptr; // yli_convert does not yet support animations.
    ai_scene.mNumTextures = symbiosis.get_number_of_symbiont_materials();
    ai_scene.mTextures = new aiTexture*[ai_scene.mNumMaterials];
    ai_scene.mNumLights = 0;        // yli_convert does not yet support lights.
    ai_scene.mLights = nullptr;     // yli_convert does not yet support lights.
    ai_scene.mNumCameras = 0;       // yli_convert does not yet support cameras.
    ai_scene.mCameras = nullptr;    // yli_convert does not yet support cameras.
    ai_scene.mMetaData = nullptr;   // yli_convert does not yet support metadata.
    ai_scene.mNumMeshes = symbiosis.get_number_of_symbiont_species();
    ai_scene.mMeshes = new aiMesh*[ai_scene.mNumMeshes];
    ai_scene.mRootNode->mNumMeshes = symbiosis.get_number_of_symbiont_species();
    ai_scene.mRootNode->mMeshes = new unsigned int[symbiosis.get_number_of_symbiont_species()];

    std::cout << "Number of `SymbiontMaterial`s: " << symbiosis.get_number_of_symbiont_materials() << "\n";

    for (std::size_t symbiont_material_i = 0; symbiont_material_i < symbiosis.get_number_of_symbiont_materials(); symbiont_material_i++)
    {
        std::cout << "Processing `SymbiontMaterial` " << symbiont_material_i << "\n";
        const yli::ontology::SymbiontMaterial* const symbiont_material = symbiosis.get_symbiont_material(symbiont_material_i);

        ai_scene.mMaterials[symbiont_material_i] = new aiMaterial();
        ai_scene.mTextures[symbiont_material_i] = new aiTexture();

        if (symbiont_material == nullptr)
        {
            std::cerr << "ERROR: `yli_convert`: `symbiont_material` is `nullptr`!\n";
            continue;
        }

        ai_scene.mTextures[symbiont_material_i]->mWidth = static_cast<unsigned int>(symbiont_material->get_image_width());
        ai_scene.mTextures[symbiont_material_i]->mHeight = static_cast<unsigned int>(symbiont_material->get_image_height());

        if (symbiont_material->get_childID() == std::numeric_limits<std::size_t>::max())
        {
            // childID is the default (invalid) value, not a real childID!
            std::cerr << "ERROR: `yli_convert`: `childID` is `std::numeric_limits<std::size_t>::max()`!\n";
            continue;
        }
    }

    for (std::size_t symbiont_species_i = 0; symbiont_species_i < symbiosis.get_number_of_symbiont_species(); symbiont_species_i++)
    {
        ai_scene.mRootNode->mMeshes[symbiont_species_i] = symbiont_species_i;
        ai_scene.mMeshes[symbiont_species_i] = new aiMesh();

        const yli::ontology::SymbiontSpecies* const symbiont_species = symbiosis.get_symbiont_species(symbiont_species_i);

        if (symbiont_species == nullptr)
        {
            std::cerr << "ERROR: `yli_convert`: `symbiont_species` is `nullptr`!\n";
            continue;
        }

        const yli::ontology::SymbiontMaterial* const symbiont_material = static_cast<yli::ontology::SymbiontMaterial*>(symbiont_species->get_parent());

        if (symbiont_material == nullptr)
        {
            std::cerr << "ERROR: `yli_convert`: `symbiont_material` is `nullptr`!\n";
            continue;
        }

        ai_scene.mMeshes[symbiont_species_i]->mMaterialIndex = symbiont_material->get_childID();

        const std::vector<glm::vec3>& vertices = symbiont_species->get_vertices();
        const std::vector<glm::vec3>& normals = symbiont_species->get_normals();
        const std::vector<glm::vec2>& uvs = symbiont_species->get_uvs();

        const std::size_t number_of_vertices = vertices.size();

        ai_scene.mMeshes[symbiont_species_i]->mNumVertices = number_of_vertices;
        ai_scene.mMeshes[symbiont_species_i]->mVertices = new aiVector3D[number_of_vertices];
        ai_scene.mMeshes[symbiont_species_i]->mNormals = new aiVector3D[number_of_vertices];
        ai_scene.mMeshes[symbiont_species_i]->mTextureCoords[0] = new aiVector3D[number_of_vertices];
        ai_scene.mMeshes[symbiont_species_i]->mNumUVComponents[0] = number_of_vertices;

        for (std::size_t vertex_i = 0; vertex_i < number_of_vertices; vertex_i++)
        {
            ai_scene.mMeshes[symbiont_species_i]->mVertices[vertex_i] = aiVector3D(vertices[vertex_i].x, vertices[vertex_i].y, vertices[vertex_i].z);
            ai_scene.mMeshes[symbiont_species_i]->mNormals[vertex_i] = aiVector3D(normals[vertex_i].x, normals[vertex_i].y, normals[vertex_i].z);
            ai_scene.mMeshes[symbiont_species_i]->mTextureCoords[0][vertex_i] = aiVector3D(uvs[vertex_i].x, uvs[vertex_i].y, 0);
        }

        const std::size_t number_of_faces = number_of_vertices / 3;
        std::cout << "Number of faces: " << number_of_faces << "\n";

        ai_scene.mMeshes[symbiont_species_i]->mFaces = new aiFace[number_of_faces];
        ai_scene.mMeshes[symbiont_species_i]->mNumFaces = number_of_faces;

        for (std::size_t face_i = 0; face_i < number_of_faces; face_i++)
        {
            ai_scene.mMeshes[symbiont_species_i]->mFaces[face_i].mIndices = new unsigned int[3];
            ai_scene.mMeshes[symbiont_species_i]->mFaces[face_i].mNumIndices = 3;
            ai_scene.mMeshes[symbiont_species_i]->mFaces[face_i].mIndices[0] = 3 * face_i;
            ai_scene.mMeshes[symbiont_species_i]->mFaces[face_i].mIndices[1] = 3 * face_i + 1;
            ai_scene.mMeshes[symbiont_species_i]->mFaces[face_i].mIndices[2] = 3 * face_i + 2;
        }
    }

    std::cout << "Creating Assimp::Exporter ...\n";
    Assimp::Exporter assimp_exporter = Assimp::Exporter();
    std::cout << "Exporting to " << out_file << " ...\n";
    const aiReturn export_ai_return = assimp_exporter.Export(&ai_scene, out_file_format, out_file);

    if (export_ai_return == aiReturn_SUCCESS)
    {
        std::cout << "Export to " << out_file << " successful.\n";
    }
    else if (export_ai_return == aiReturn_FAILURE)
    {
        std::cerr << "ERROR: Export to " << out_file << " failed.\n";
    }
    else if (export_ai_return == aiReturn_OUTOFMEMORY)
    {
        std::cerr << "ERROR: Export to " << out_file << " failed: out of memory.\n";
    }
    else if (export_ai_return == _AI_ENFORCE_ENUM_SIZE)
    {
        std::cerr << "ERROR: Export to " << out_file << " failed: _AI_ENFORCE_ENUM_SIZE.\n";
    }
    else
    {
        std::cerr << "ERROR: Export to " << out_file << " failed: unknown error.\n";
    }
}
