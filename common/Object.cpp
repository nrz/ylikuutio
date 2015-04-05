#include <iostream>
#include <string>
#include <string.h>
#include <vector>

#include "Object.hpp"
#include "globals.hpp"
#include "bmploader.hpp"
#include "objloader.hpp"

Object::Object(ObjectStruct object_struct)
{
    // constructor.
    Object::model_file_format        = object_struct.model_file_format;
    Object::model_filename           = object_struct.model_filename;
    Object::texture_file_format      = object_struct.texture_file_format;
    Object::texture_filename         = object_struct.texture_filename;
    Object::vertex_shader            = object_struct.vertex_shader;
    Object::fragment_shader          = object_struct.fragment_shader;
    Object::model_matrix             = object_struct.model_matrix;
    Object::translate_vector         = object_struct.translate_vector;
    Object::MVP_matrix               = object_struct.MVP_matrix;
    Object::color_channel            = object_struct.color_channel;

    Object::char_model_file_format   = Object::model_file_format.c_str();
    Object::char_model_filename      = Object::model_filename.c_str();
    Object::char_texture_file_format = Object::texture_file_format.c_str();
    Object::char_texture_filename    = Object::texture_filename.c_str();
    Object::char_vertex_shader       = Object::vertex_shader.c_str();
    Object::char_fragment_shader     = Object::fragment_shader.c_str();

    bool model_loading_result = false;

    if ((strcmp(char_model_file_format, "obj") == 0) || (strcmp(char_model_file_format, "OBJ") == 0))
    {
        model_loading_result = model::load_OBJ(Object::char_model_filename, Object::vertices, Object::UVs, Object::normals);
    }
    else if ((strcmp(char_model_file_format, "bmp") == 0) || (strcmp(char_model_file_format, "BMP") == 0))
    {
        model_loading_result = model::load_BMP_world(Object::char_model_filename, Object::vertices, Object::UVs, Object::normals, Object::color_channel);
    }
    else
    {
        std::cerr << "no model was loaded!\n";
        std::cerr << "model file format: " << Object::model_file_format << "\n";
    }

    // define vertices.
    // define UVs.
    // define normals.
    // define programID.
    // define lightID.
    // define textureID.
}
