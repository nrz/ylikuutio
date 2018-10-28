#include "text2D.hpp"
#include "font2D.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <vector>    // std::vector

namespace yli
{
    namespace ontology
    {
        void Text2D::bind_to_parent()
        {
            // requirements:
            // `this->parent` must not be `nullptr`.
            yli::ontology::Font2D* const font2D = this->parent;

            if (font2D == nullptr)
            {
                std::cerr << "ERROR: `Text2D::bind_to_parent`: `font2D` is `nullptr`!\n";
                return;
            }

            // get `childID` from the `Font2D` and set pointer to this `Text2D`.
            font2D->bind_text2D(this);
        }

        void Text2D::bind_to_new_parent(yli::ontology::Font2D* const new_parent)
        {
            // this method sets pointer to this `Text2D` to `nullptr`, sets `parent` according to the input,
            // and requests a new `childID` from the new `Font2D`.
            //
            // requirements:
            // `this->parent` must not be `nullptr`.
            // `new_parent` must not be `nullptr`.

            yli::ontology::Font2D* const font2D = this->parent;

            if (font2D == nullptr)
            {
                std::cerr << "ERROR: `Text2D::bind_to_new_parent`: `font2D` is `nullptr`!\n";
                return;
            }

            if (new_parent == nullptr)
            {
                std::cerr << "ERROR: `Text2D::bind_to_new_parent`: `new_parent` is `nullptr`!\n";
                return;
            }

            // unbind from the old parent `Font2D`.
            this->parent->unbind_text2D(this->childID);

            // get `childID` from `Font2D` and set pointer to this `Text2D`.
            this->parent = new_parent;
            this->parent->bind_text2D(this);
        }

        Text2D::~Text2D()
        {
            // destructor.
        }

        void Text2D::render()
        {
        }

        yli::ontology::Entity* Text2D::get_parent() const
        {
            return this->parent;
        }

        std::size_t Text2D::get_number_of_children() const
        {
            return 0; // `Text2D` has no children.
        }

        std::size_t Text2D::get_number_of_descendants() const
        {
            return 0; // `Text2D` has no children.
        }
    }
}
