#ifndef __FONT_LOADER_HPP_INCLUDED
#define __FONT_LOADER_HPP_INCLUDED

// Include standard headers
#include <string>    // std::string
#include <vector>    // std::vector

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

namespace model
{
    bool load_SVG_font(std::string font_file_path,
            std::vector<std::vector<std::vector<glm::vec3>>> &out_glyph_vertex_data,
            std::vector<std::string> &glyph_names,
            std::vector<std::string> &unicode_strings,
            float vertex_scaling_factor);

    void extract_string_with_several_endings(
            char* dest_mem_pointer,
            char*& src_mem_pointer,
            char* char_end_string);

    int32_t extract_value_from_string(char*& vertex_data_pointer, char* char_end_string, const char* description);

    int32_t extract_value_from_string_with_standard_endings(char*& vertex_data_pointer, const char* description);

    bool find_first_glyph_in_SVG(const char* SVG_base_pointer, char*& SVG_data_pointer);

    void extract_string(
            char* dest_mem_pointer,
            char* &src_mem_pointer,
            char* char_end_string);

    bool load_vertex_data(
            const char* SVG_base_pointer,
            char*& SVG_data_pointer,
            std::vector<std::vector<glm::vec3>> &current_glyph_vertices);

    bool load_SVG_glyph(
            const char* SVG_base_pointer,
            char*& SVG_data_pointer,
            std::vector<std::vector<std::vector<glm::vec3>>> &out_glyph_vertex_data,
            std::vector<std::string> &glyph_names,
            std::vector<std::string> &unicode_strings,
            float vertex_scaling_factor);

    bool load_SVG_font(
            std::string font_file_path,
            std::vector<std::vector<std::vector<glm::vec3>>> &out_glyph_vertex_data,
            std::vector<std::string> &glyph_names,
            std::vector<std::string> &unicode_strings,
            float vertex_scaling_factor);
}

#endif
