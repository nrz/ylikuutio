#include "vector_font.hpp"
#include "text3D.hpp"
#include "render_templates.hpp"
#include "family_templates.hpp"
#include "vector_font_struct.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include standard headers
#include <cstddef>       // std::size_t
#include <iostream>      // std::cout, std::cin, std::cerr
#include <stdint.h>      // uint32_t etc.

namespace yli
{
    namespace ontology
    {
        class Text3D;
        class Glyph;

        void VectorFont::bind_glyph(yli::ontology::Glyph* const glyph)
        {
            // get `childID` from `VectorFont` and set pointer to `glyph`.
            yli::hierarchy::bind_child_to_parent<yli::ontology::Glyph*>(
                    glyph,
                    this->glyph_pointer_vector,
                    this->free_glyphID_queue,
                    this->number_of_glyphs);
        }

        void VectorFont::bind_text3D(yli::ontology::Text3D* const text3D)
        {
            // get `childID` from `VectorFont` and set pointer to `text3D`.
            yli::hierarchy::bind_child_to_parent<yli::ontology::Text3D*>(
                    text3D,
                    this->text3D_pointer_vector,
                    this->free_text3D_ID_queue,
                    this->number_of_text3Ds);
        }

        void VectorFont::unbind_text3D(const std::size_t childID)
        {
            yli::hierarchy::unbind_child_from_parent<yli::ontology::Text3D*>(
                    childID,
                    this->text3D_pointer_vector,
                    this->free_text3D_ID_queue,
                    this->number_of_text3Ds);
        }

        void VectorFont::bind_to_parent()
        {
            // requirements:
            // `this->parent` must not be `nullptr`.
            yli::ontology::Material* const material = this->parent;

            if (material == nullptr)
            {
                std::cerr << "ERROR: `VectorFont::bind_to_parent`: `material` is `nullptr`!\n";
                return;
            }

            // get `childID` from the `Material` and set pointer to this `VectorFont`.
            material->bind_vector_font(this);
        }

        void VectorFont::bind_to_new_parent(yli::ontology::Material* const new_parent)
        {
            // this method sets pointer to this `Species` to `nullptr`, sets `parent` according to the input,
            // and requests a new `childID` from the new `Material`.
            //
            // requirements:
            // `this->parent` must not be `nullptr`.
            // `new_parent` must not be `nullptr`.

            yli::ontology::Material* const material = this->parent;

            if (material == nullptr)
            {
                std::cerr << "ERROR: `VectorFont::bind_to_new_parent`: `material` is `nullptr`!\n";
                return;
            }

            if (new_parent == nullptr)
            {
                std::cerr << "ERROR: `VectorFont::bind_to_new_parent`: `new_parent` is `nullptr`!\n";
                return;
            }

            // unbind from the old parent `Material`.
            material->unbind_vector_font(this->childID);

            // get `childID` from `Material` and set pointer to this `VectorFont`.
            this->parent = new_parent;
            this->parent->bind_vector_font(this);
        }

        // this method returns a pointer to `Glyph` that matches the given `unicode_value`,
        // and `nullptr` if this `VectorFont` does not contain such a `Glyph`.
        yli::ontology::Glyph* VectorFont::get_glyph_pointer(const int32_t unicode_value) const
        {
            if (this->unicode_glyph_map.count(unicode_value) == 1)
            {
                return this->unicode_glyph_map.at(unicode_value);
            }

            // No matching `Glyph` found!
            return nullptr;
        }

        VectorFont::~VectorFont()
        {
            // destructor.
            // Destroying a `VectorFont` destroys also all `Text3D` entities, and after that all `Glyph` entities.
            std::cout << "Font with childID " << std::dec << this->childID << " will be destroyed.\n";

            // destroy all 3D texts (`Text3D`) of this font.
            std::cout << "All 3D texts of this font will be destroyed.\n";
            yli::hierarchy::delete_children<yli::ontology::Text3D*>(this->text3D_pointer_vector, this->number_of_text3Ds);

            // destroy all `Glyph`s of this font.
            std::cout << "All glyphs of this font will be destroyed.\n";
            yli::hierarchy::delete_children<yli::ontology::Glyph*>(this->glyph_pointer_vector, this->number_of_glyphs);

            // requirements for further actions:
            // `this->parent` must not be `nullptr`.

            yli::ontology::Material* const material = this->parent;

            if (material == nullptr)
            {
                std::cerr << "ERROR: `VectorFont::~VectorFont`: `material` is `nullptr`!\n";
                return;
            }

            // set pointer to this `VectorFont` to nullptr.
            material->unbind_vector_font(this->childID);
        }

        void VectorFont::render()
        {
            this->prerender();

            // render this `VectorFont` by calling `render()` function of each `Glyph`.
            yli::ontology::render_children<yli::ontology::Glyph*>(this->glyph_pointer_vector);

            this->postrender();
        }

        yli::ontology::Entity* VectorFont::get_parent() const
        {
            return this->parent;
        }

        std::size_t VectorFont::get_number_of_children() const
        {
            return this->number_of_glyphs + this->number_of_text3Ds;
        }

        std::size_t VectorFont::get_number_of_descendants() const
        {
            return yli::ontology::get_number_of_descendants(this->glyph_pointer_vector) +
                yli::ontology::get_number_of_descendants(this->text3D_pointer_vector);
        }

        void VectorFont::set_glyph_pointer(const std::size_t childID, yli::ontology::Glyph* const child_pointer)
        {
            yli::hierarchy::set_child_pointer(childID, child_pointer, this->glyph_pointer_vector, this->free_glyphID_queue, this->number_of_glyphs);
        }
    }
}
