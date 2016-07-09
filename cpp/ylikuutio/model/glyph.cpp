#include "glyph.hpp"
#include "species_or_glyph.hpp"
#include "object.hpp"
#include "render_templates.hpp"
#include "cpp/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <iostream> // std::cout, std::cin, std::cerr

namespace model
{
    void Glyph::bind_to_parent()
    {
        hierarchy::bind_child_to_parent<model::Glyph*>(this, this->parent_pointer->glyph_pointer_vector, this->parent_pointer->free_glyphID_queue);
    }

    Glyph::Glyph(GlyphStruct glyph_struct)
    {
        // constructor.
        this->glyph_vertex_data = glyph_struct.glyph_vertex_data;
        this->glyph_name_pointer = glyph_struct.glyph_name_pointer;
        this->unicode_string_pointer = glyph_struct.unicode_string_pointer;
        this->light_position = glyph_struct.light_position;

        // get childID from the Material and set pointer to this Species.
        this->bind_to_parent();

        // Get a handle for our buffers.
        this->vertexPosition_modelspaceID = glGetAttribLocation(this->parent_pointer->parent_pointer->parent_pointer->programID, "vertexPosition_modelspace");
        this->vertexUVID = glGetAttribLocation(this->parent_pointer->parent_pointer->parent_pointer->programID, "vertexUV");
        this->vertexNormal_modelspaceID = glGetAttribLocation(this->parent_pointer->parent_pointer->parent_pointer->programID, "vertexNormal_modelspace");
    }

    Glyph::~Glyph()
    {
        // destructor.
        std::cout << "This glyph will be destroyed.\n";

        // destroy all objects of this glyph.
        std::cout << "All objects of this glyph will be destroyed.\n";
        hierarchy::delete_children<model::Object*>(this->object_pointer_vector);
    }

    void Glyph::render()
    {
        model::render_species_or_glyph<model::Glyph*>(this);
    }

    void Glyph::set_object_pointer(uint32_t childID, void* parent_pointer)
    {
        hierarchy::set_child_pointer(childID, parent_pointer, this->object_pointer_vector, this->free_objectID_queue);
    }
}
