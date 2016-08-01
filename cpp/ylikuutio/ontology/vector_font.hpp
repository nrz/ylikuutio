#ifndef __FONT_HPP_INCLUDED
#define __FONT_HPP_INCLUDED

#include "material.hpp"
#include "render_templates.hpp"
#include "cpp/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "cpp/ylikuutio/common/globals.hpp"

// Include standard headers
#include <iostream>      // std::cout, std::cin, std::cerr
#include <queue>         // std::queue
#include <stdint.h>      // uint32_t etc.
#include <string>        // std::string
#include <vector>        // std::vector
#include <unordered_map> // std::unordered_map

namespace ontology
{
    class Material;
    class Glyph;

    class VectorFont
    {
        public:
            // constructor.
            // TODO: `VectorFont` constructor also creates each `Glyph` and binds them to the `VectorFont`.
            VectorFont(VectorFontStruct vector_font_struct);

            // destructor.
            // Destroying a `VectorFont` destroys also all `Text3D` entities, and after that all `Glyph` entities.
            ~VectorFont();

            // this method sets `Glyph` pointer.
            void set_glyph_pointer(uint32_t childID, ontology::Glyph* child_pointer);

            // this method sets `Text3D` pointer.
            void set_text3D_pointer(uint32_t childID, ontology::Text3D* child_pointer);

            // this method sets pointer to this species to nullptr, sets `parent_pointer` according to the input, and requests a new `childID` from the new material.
            void bind_to_new_parent(ontology::Material* new_material_pointer);

            // The rest fields are created in the constructor.
            uint32_t image_width;
            uint32_t image_height;

            ontology::Material* parent_pointer; // pointer to `Material`.

            friend class Glyph;
            friend class Text3D;
            template<class T1>
                friend void render_children(std::vector<T1>& child_pointer_vector);
            template<class T1>
                friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<uint32_t>& free_childID_queue);
            template<class T1, class T2>
                friend void hierarchy::bind_child_to_new_parent(T1 child_pointer, T2 new_parent_pointer, std::vector<T1>& old_child_pointer_vector, std::queue<uint32_t>& old_free_childID_queue);

        private:
            void bind_to_parent();

            // this method returns a pointer to `Glyph` that matches the given `unicode_value`,
            // and `nullptr` if this `VectorFont` does not contain such a `Glyph`.
            ontology::Glyph* get_glyph_pointer(int32_t unicode_value);

            // this method renders all glyphs of this `VectorFont`.
            void render();

            std::string font_file_format;          // type of the model file, eg. `"bmp"`.
            std::string font_filename;             // filename of the model file.
            GLfloat vertex_scaling_factor;
            uint32_t childID;                      // species ID, returned by `ontology::Material->get_speciesID()`.
            const char* char_font_file_format;
            const char* char_font_filename;

            std::vector<std::vector<std::vector<glm::vec2>>> glyph_vertex_data;
            std::vector<std::vector<glm::vec2>> glyph_UV_data;
            std::vector<std::vector<glm::vec2>> glyph_normal_data;
            std::vector<std::string> glyph_names;
            std::vector<std::string> unicode_strings;

            std::vector<ontology::Glyph*> glyph_pointer_vector;
            std::vector<ontology::Text3D*> text3D_pointer_vector;
            std::queue<uint32_t> free_glyphID_queue;
            std::queue<uint32_t> free_text3D_ID_queue;

            std::unordered_map<int32_t, ontology::Glyph*> unicode_glyph_map;
    };
}

#endif
