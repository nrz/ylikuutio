#ifndef __MODEL_HPP_INCLUDED
#define __MODEL_HPP_INCLUDED

#include "entity.hpp"
#include "species_or_glyph.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

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
#include <cstddef>  // std::size_t
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace space_partition
{
    class Chunk;
}

namespace yli
{
    namespace ontology
    {
        class Universe;
        class Object;

        class Model: public yli::ontology::Entity
        {
            public:
                void bind(yli::ontology::Object* const object);
                void unbind(const int32_t childID);

                // constructor.
                Model(yli::ontology::Universe* const universe)
                    : Entity(universe)
                {
                    // constructor.

                    // Initialize class members with some dummy values.
                    this->childID = -1;
                    this->lightID = 0;
                    this->vertex_position_modelspaceID = 0;
                    this->vertexUVID = 0;
                    this->vertex_normal_modelspaceID = 0;
                    this->vertexbuffer = 0;
                    this->uvbuffer = 0;
                    this->normalbuffer = 0;
                    this->elementbuffer = 0;
                    this->initial_rotate_angle = 0.0f;
                    this->initial_rotate_vector = glm::vec3(0.0f, 1.0f, 1.0f);

                    this->number_of_objects = 0;
                    this->child_vector_pointers_vector.push_back(&this->object_pointer_vector);
                }

                // destructor.
                virtual ~Model();

                std::size_t get_number_of_children() const override;
                std::size_t get_number_of_descendants() const override;

                const std::vector<glm::vec3>& get_vertices() const;
                const std::vector<uint32_t>& get_indices() const;

                GLuint get_vertex_position_modelspaceID() const;
                GLuint get_vertexUVID() const;
                GLuint get_vertex_normal_modelspaceID() const;

                GLuint get_vertexbuffer() const;
                GLuint get_uvbuffer() const;
                GLuint get_normalbuffer() const;
                GLuint get_elementbuffer() const;

                void store_vertex_position_modelspaceID(const GLuint vertex_position_modelspaceID);
                void store_vertexUVID(const GLuint vertexUVID);
                void store_vertex_normal_modelspaceID(const GLuint vertex_normal_modelspaceID);

                template<class T1>
                    friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<int32_t>& free_childID_queue, std::size_t* number_of_children);
                template<class T1, class T2>
                    friend void yli::hierarchy::bind_child_to_new_parent(T1 child_pointer, T2 new_parent, std::vector<T1>& old_child_pointer_vector, std::queue<int32_t>& old_free_childID_queue, std::size_t* old_number_of_children);
                template<class T1>
                    friend void render_species_or_glyph(T1 species_or_glyph_pointer);

            protected:
                // this method sets a object pointer.
                void set_object_pointer(const int32_t childID, yli::ontology::Object* const child_pointer);

                GLfloat initial_rotate_angle;            // initial rotate angle.
                glm::vec3 initial_rotate_vector;         // initial rotate vector.

                std::string color_channel;               // color channel in use: `"red"`, `"green"`, `"blue"`, `"mean"` or `"all"`.
                glm::vec3 light_position;                // light position.

                GLuint lightID;                          // light ID, returned by `glGetUniformLocation(programID, "LightPosition_worldspace");`.

                std::vector<yli::ontology::Object*> object_pointer_vector;
                std::queue<int32_t> free_objectID_queue;
                std::size_t number_of_objects;

                std::string triangulation_type;

                GLuint vertex_position_modelspaceID;
                GLuint vertexUVID;
                GLuint vertex_normal_modelspaceID;

                std::vector<glm::vec3> vertices;         // vertices of the `Model`.
                std::vector<glm::vec2> uvs;              // UVs of the `Model`.
                std::vector<glm::vec3> normals;          // normals of the `Model`.

                std::vector<uint32_t> indices;           // the deleted vertices will be reused (though it is not required, if there's enough memory).
                std::vector<glm::vec3> indexed_vertices;
                std::vector<glm::vec2> indexed_uvs;
                std::vector<glm::vec3> indexed_normals;

                GLuint vertexbuffer;
                GLuint uvbuffer;
                GLuint normalbuffer;
                GLuint elementbuffer;
        };
    }
}

#endif
