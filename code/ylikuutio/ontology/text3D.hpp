#ifndef TEXT3D_HPP
#define TEXT3D_HPP

#include "text3D_struct.hpp"
#include "entity_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/common/globals.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <queue>    // std::queue
#include <string>   // std::string
#include <vector>   // std::vector

namespace ontology
{
    class Universe;

    class Text3D
    {
        public:
            // constructor.
            // TODO: `Text3D` constructor also creates each `Object`,
            // and binds each to its corresponding `Glyph` for rendering hierarchy,
            // and also binds each to this `Text3D` for ontological hierarchy.
            Text3D(Text3DStruct text3D_struct);

            // destructor.
            ~Text3D();

            // this method deletes all glyph Objects of this `Text3D`,
            // sets pointer to this `Text3D` to nullptr,
            // sets `parent_pointer` according to the input (the new `VectorFont`),
            // requests a new `childID` from the new `VectorFont`,
            // and creates all glyph Objects of this `Text3D` with the font data.
            // Note: different fonts may provide glyphs for different Unicodes!
            void bind_to_new_parent(ontology::VectorFont* new_vector_font_pointer);

            // this method sets a object pointer.
            void set_object_pointer(uint32_t childID, ontology::Object* child_pointer);

            void set_name(std::string name);

            friend class Object;
            template<class T1>
                friend void set_name(std::string name, T1 entity);
            template<class T1>
                friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<uint32_t>& free_childID_queue);

        private:
            void bind_to_parent();

            std::string text_string;

            ontology::Universe* universe_pointer; // pointer to `Universe`.
            ontology::VectorFont* parent_pointer; // pointer to `VectorFont`.

            uint32_t childID;                     // text3D ID, set by `this->bind_to_parent()`.

            glm::vec3 original_scale_vector;      // original scale vector.
            GLfloat rotate_angle;                 // rotate angle.
            glm::vec3 coordinate_vector;          // coordinate vector.
            glm::vec3 rotate_vector;              // rotate vector.
            glm::vec3 translate_vector;           // translate vector.

            std::vector<void*> child_vector_pointers_vector;

            std::vector<ontology::Object*> object_pointer_vector;
            std::queue<uint32_t> free_objectID_queue;

            std::string name;                     // name of this entity.
    };
}

#endif
