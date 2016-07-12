#ifndef __GLYPH_HPP_INCLUDED
#define __GLYPH_HPP_INCLUDED

#include "species_or_glyph.hpp"
#include "text3D.hpp"
#include "vector_font.hpp"
#include "render_templates.hpp"
#include "cpp/ylikuutio/hierarchy/hierarchy_templates.hpp"

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
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace model
{
    class Object;

    class Glyph
    {
        public:
            // constructor.
            Glyph(GlyphStruct glyph_struct);

            // destructor.
            // glyphs should be destroyed only by destroying the entire `VectorFont`.
            ~Glyph();

            // this method sets a object pointer.
            void set_object_pointer(uint32_t childID, void* parent_pointer);

            // this method gets a object ID and removes it from the `free_objectID_queue` if it was popped from the queue.
            uint32_t get_objectID();

            glm::vec3 light_position;                    // light position.

            // The rest fields are created in the constructor.
            uint32_t image_width;
            uint32_t image_height;

            GLuint vertexPosition_modelspaceID;
            GLuint vertexUVID;
            GLuint vertexNormal_modelspaceID;

            std::vector<glm::vec3> vertices;       // vertices of the object.
            std::vector<glm::vec2> UVs;            // UVs of the object.
            std::vector<glm::vec3> normals;        // normals of the object.

            std::vector<uint32_t> indices;         // the deleted vertices will be reused (though it is not required, if there's enough memory).
            std::vector<glm::vec3> indexed_vertices;
            std::vector<glm::vec2> indexed_UVs;
            std::vector<glm::vec3> indexed_normals;

            GLuint vertexbuffer;
            GLuint uvbuffer;
            GLuint normalbuffer;
            GLuint elementbuffer;

            model::VectorFont* parent_pointer; // pointer to `VectorFont`.

            friend class Object;
            template<class T1>
                friend void render_children(std::vector<void*> &child_pointer_vector);
            template<class T1>
                friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<void*> &child_pointer_vector, std::queue<uint32_t> &free_childID_queue);
            template<class T1>
                friend void render_species_or_glyph(T1 species_or_glyph_pointer);

        private:
            void bind_to_parent();

            // this method renders all objects of this species.
            void render();

            uint32_t childID;                      // glyph ID, returned by `model::VectorFont->get_glyphID()`.
            GLuint lightID;                        // light ID, returned by `glGetUniformLocation(programID, "LightPosition_worldspace");`.

            std::vector<std::vector<glm::vec2>>* glyph_vertex_data;
            const char* glyph_name_pointer;        // we need only a pointer, because glyphs are always created by the `VectorFont` constructor.
            const char* unicode_string_pointer;    // we need only a pointer, because glyphs are always created by the `VectorFont` constructor.

            std::vector<void*> object_pointer_vector;
            std::queue<uint32_t> free_objectID_queue;
    };
}

#endif
