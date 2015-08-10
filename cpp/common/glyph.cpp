#include "glyph.hpp"
#include "object.hpp"

namespace model
{
    Glyph::Glyph(GlyphStruct glyph_struct)
    {
        // constructor.
    }

    Glyph::~Glyph()
    {
        // destructor.
        std::cout << "This glyph will be destroyed.\n";

        // destroy all objects of this glyph.
        std::cout << "All objects of this glyph will be destroyed.\n";
        model::delete_children<model::Object*>(this->object_pointer_vector);
    }

    void Glyph::render()
    {
        model::render_species_or_glyph<model::Glyph*>(this);
    }

    void Glyph::set_object_pointer(GLuint childID, void* parent_pointer)
    {
        set_child_pointer(childID, parent_pointer, this->object_pointer_vector, this->free_objectID_queue);
    }
}
