#include "glyph.hpp"
#include "vector_font.hpp"
#include "species_or_glyph.hpp"
#include "object.hpp"
#include "glyph_struct.hpp"
#include "render_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr

namespace yli
{
    namespace ontology
    {
        void Glyph::bind_to_parent()
        {
            // requirements:
            // `this->parent` must not be `nullptr`.

            yli::ontology::VectorFont* const vector_font = this->parent;

            if (vector_font == nullptr)
            {
                std::cerr << "ERROR: `Glyph::bind_to_parent`: `vector_font` is `nullptr`!\n";
                return;
            }

            // get `childID` from `VectorFont` and set pointer to this `Glyph`.
            vector_font->bind_glyph(this);
        }

        Glyph::~Glyph()
        {
            // destructor.
            std::string glyph_name_string = this->glyph_name_pointer;
            std::string unicode_string = this->unicode_char_pointer;
            std::cout << "This glyph (\"" << glyph_name_string << "\", Unicode: \"" << std::dec << unicode_string << "\") will be destroyed.\n";

            // Cleanup VBO, shader and texture.
            glDeleteBuffers(1, &this->vertexbuffer);
            glDeleteBuffers(1, &this->uvbuffer);
            glDeleteBuffers(1, &this->normalbuffer);
            glDeleteBuffers(1, &this->elementbuffer);

            // requirements for further actions:
            // `this->parent` must not be `nullptr`.

            yli::ontology::VectorFont* const vector_font = this->parent;

            if (vector_font == nullptr)
            {
                std::cerr << "ERROR: `Glyph::~Glyph`: `vector_font` is `nullptr`!\n";
                return;
            }

            // set pointer to this `Glyph` to nullptr.
            vector_font->set_glyph_pointer(this->childID, nullptr);
        }

        yli::ontology::Entity* Glyph::get_parent() const
        {
            return this->parent;
        }

        void Glyph::render()
        {
            if (this->vram_buffer_in_use)
            {
                this->prerender();

                // render this `Glyph`.
                yli::ontology::render_species_or_glyph<yli::ontology::Glyph*>(this);

                this->postrender();
            }
        }

        void Glyph::set_object_pointer(const std::size_t childID, yli::ontology::Object* const child_pointer)
        {
            yli::hierarchy::set_child_pointer(childID, child_pointer, this->object_pointer_vector, this->free_objectID_queue, this->number_of_objects);
        }

        const char* Glyph::get_unicode_char_pointer()
        {
            return this->unicode_char_pointer;
        }
    }
}
