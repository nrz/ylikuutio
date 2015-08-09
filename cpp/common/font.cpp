#include "font.hpp"
#include "glyph.hpp"

namespace model
{
    Font::Font(FontStruct font_struct)
    {
        // constructor.
        //
        // Font constructor also creates each Glyph and binds them to the Font.
        // TODO: implement the constructor!
    }

    Font::~Font()
    {
        // destructor.
        std::cout << "This font will be destroyed.\n";

        // destroy all glyphs of this font.
        std::cout << "All glyphs of this font will be destroyed.\n";
        model::delete_children<model::Glyph*>(this->glyph_pointer_vector);
    }

    void Font::render()
    {
        // render Font by calling `render()` function of each Glyph.
        model::render_children<model::Glyph*>(this->glyph_pointer_vector);
    }

    void Font::set_glyph_pointer(GLuint childID, void* parent_pointer)
    {
        set_child_pointer(childID, parent_pointer, this->glyph_pointer_vector, this->free_glyphID_queue);
    }
}
