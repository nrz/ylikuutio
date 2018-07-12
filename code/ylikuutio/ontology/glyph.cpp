#include "glyph.hpp"
#include "vector_font.hpp"
#include "species_or_glyph.hpp"
#include "object.hpp"
#include "glyph_struct.hpp"
#include "render_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <iostream> // std::cout, std::cin, std::cerr

namespace yli
{
    namespace ontology
    {
        void Glyph::bind_to_parent()
        {
            // get `childID` from `VectorFont` and set pointer to this `Glyph`.
            this->parent->bind_glyph(this);
        }

        Glyph::~Glyph()
        {
            // destructor.
            std::string glyph_name_string = this->glyph_name_pointer;
            std::string unicode_string = this->unicode_char_pointer;
            std::cout << "This glyph (\"" << glyph_name_string << "\", Unicode: \"" << std::dec << unicode_string << "\") will be destroyed.\n";

            // TODO: Cleanup VBO, shader and texture (copy these from `Species::~Species()`).

            // set pointer to this `Glyph` to nullptr.
            this->parent->set_glyph_pointer(this->childID, nullptr);
        }

        yli::ontology::Entity* Glyph::get_parent() const
        {
            return this->parent;
        }

        void Glyph::render()
        {
            this->prerender();

            // render this `Glyph`.
            yli::ontology::render_species_or_glyph<yli::ontology::Glyph*>(this);

            this->postrender();
        }

        void Glyph::set_object_pointer(const int32_t childID, yli::ontology::Object* const child_pointer)
        {
            yli::hierarchy::set_child_pointer(childID, child_pointer, this->object_pointer_vector, this->free_objectID_queue, &this->number_of_objects);
        }

        const char* Glyph::get_unicode_char_pointer()
        {
            return this->unicode_char_pointer;
        }
    }
}
