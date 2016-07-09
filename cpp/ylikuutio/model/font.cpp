#include "font.hpp"
#include "cpp/ylikuutio/hierarchy/hierarchy.hpp"
#include "render_templates.hpp"
#include "cpp/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "font_loader.hpp"
#include "glyph.hpp"

// Include standard headers
#include <cstring>  // std::memcmp, std::strcmp, std::strlen, std::strncmp
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.

namespace model
{
    void VectorFont::bind_to_parent()
    {
        hierarchy::bind_child_to_parent<model::VectorFont*>(this, this->parent_pointer->font_pointer_vector, this->parent_pointer->free_fontID_queue);
    }

    VectorFont::VectorFont(VectorFontStruct vector_font_struct)
    {
        // constructor.
        this->font_file_format      = vector_font_struct.font_file_format;
        this->font_filename         = vector_font_struct.font_filename;
        this->vertex_scaling_factor = vector_font_struct.vertex_scaling_factor;
        this->parent_pointer        = vector_font_struct.parent_pointer;

        this->char_font_file_format = this->font_file_format.c_str();
        this->char_font_filename    = this->font_filename.c_str();

        // get childID from the Graph and set pointer to this font.
        this->bind_to_parent();

        bool font_loading_result = false;

        if ((std::strcmp(this->char_font_file_format, "svg") == 0) || (std::strcmp(this->char_font_file_format, "SVG") == 0))
        {
            // TODO: implement `load_SVG_font`! It should read all necessary data to this VectorFont object.
            font_loading_result = model::load_SVG_font(
                    this->font_filename,
                    this->glyph_vertex_data,
                    this->glyph_names,
                    this->unicode_strings);
        }

        // TODO: `VectorFont` constructor also creates each `Glyph` and binds them to the `VectorFont`.
        // TODO: implement creation of each Glyph!
    }

    VectorFont::~VectorFont()
    {
        // destructor.
        std::cout << "This font will be destroyed.\n";

        // destroy all glyphs of this font.
        std::cout << "All glyphs of this font will be destroyed.\n";
        hierarchy::delete_children<model::Glyph*>(this->glyph_pointer_vector);
    }

    void VectorFont::render()
    {
        // render VectorFont by calling `render()` function of each Glyph.
        model::render_children<model::Glyph*>(this->glyph_pointer_vector);
    }

    void VectorFont::set_glyph_pointer(uint32_t childID, void* parent_pointer)
    {
        hierarchy::set_child_pointer(childID, parent_pointer, this->glyph_pointer_vector, this->free_glyphID_queue);
    }

    void VectorFont::bind_to_new_parent(model::Material *new_material_pointer)
    {
        hierarchy::bind_child_to_new_parent<model::VectorFont*, model::Material*>(this, new_material_pointer, this->parent_pointer->font_pointer_vector, this->parent_pointer->free_fontID_queue);
    }
}
