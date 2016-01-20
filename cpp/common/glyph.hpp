#ifndef __GLYPH_HPP_INCLUDED
#define __GLYPH_HPP_INCLUDED

#include "font.hpp"
#include "hierarchy.hpp"
#include "model_templates.hpp"
#include "species_or_glyph.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

namespace model
{
    class Object;

    class Glyph
    {
        public:
            // constructor.
            Glyph(GlyphStruct glyph_struct);

            // destructor.
            ~Glyph();

            // this method sets a object pointer.
            void set_object_pointer(GLuint childID, void* parent_pointer);

            // this method gets a object ID and removes it from the `free_objectID_queue` if it was popped from the queue.
            GLuint get_objectID();

            glm::vec3 light_position;                    // light position.

            // The rest fields are created in the constructor.
            GLuint image_width;
            GLuint image_height;

            GLuint vertexPosition_modelspaceID;
            GLuint vertexUVID;
            GLuint vertexNormal_modelspaceID;

            std::vector<glm::vec3> vertices;       // vertices of the object.
            std::vector<glm::vec2> UVs;            // UVs of the object.
            std::vector<glm::vec3> normals;        // normals of the object.

            std::vector<GLuint> indices;           // the deleted vertices will be reused (though it is not required, if there's enough memory).
            std::vector<glm::vec3> indexed_vertices;
            std::vector<glm::vec2> indexed_UVs;
            std::vector<glm::vec3> indexed_normals;

            GLuint vertexbuffer;
            GLuint uvbuffer;
            GLuint normalbuffer;
            GLuint elementbuffer;

            model::Font *parent_pointer;             // pointer to the font.

            friend class Object;
            template<class T1>
                friend void render_children(std::vector<void*> &child_pointer_vector);
            template<class T1>
                friend void bind_child_to_parent(T1 child_pointer, std::vector<void*> &child_pointer_vector, std::queue<GLuint> &free_childID_queue);
            template<class T1>
                friend void render_species_or_glyph(T1 species_or_glyph_pointer);

        private:
            void bind_to_parent();

            // this method renders all objects of this species.
            void render();

            GLuint childID;                        // glyph ID, returned by `model::Font->get_glyphID()`.
            GLuint lightID;                        // light ID, returned by `glGetUniformLocation(programID, "LightPosition_worldspace");`.

            std::vector<void*> object_pointer_vector;
            std::queue<GLuint> free_objectID_queue;
    };
}

#endif
