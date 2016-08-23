#ifndef __OBJECT_HPP_INCLUDED
#define __OBJECT_HPP_INCLUDED

#include "shader.hpp"
#include "species.hpp"
#include "glyph.hpp"
#include "render_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/common/global_variables.hpp"
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

#ifndef __GLM_GTC_MATRIX_TRANSFORM_HPP_INCLUDED
#define __GLM_GTC_MATRIX_TRANSFORM_HPP_INCLUDED
#include <glm/gtc/matrix_transform.hpp>
#endif

#ifndef __GLM_GTC_QUATERNION_HPP_INCLUDED
#define __GLM_GTC_QUATERNION_HPP_INCLUDED
#include <glm/gtc/quaternion.hpp> // glm::quat
#endif

#ifndef __GLM_GTX_QUATERNION_HPP_INCLUDED
#define __GLM_GTX_QUATERNION_HPP_INCLUDED
#include <glm/gtx/quaternion.hpp> // glm::toMat4
#endif

// Include standard headers
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace ontology
{
    class Species;
    class Glyph;

    class Object
    {
        public:
            // constructor.
            Object(ObjectStruct object_struct);

            // destructor.
            ~Object();

            // this method sets pointer to this `Object` to nullptr, sets `parent_pointer` according to the input,
            // and requests a new `childID` from the new `Species` or from the new `Glyph`.
            void bind_to_new_parent(void* new_parent_pointer);
            template<class T1>
                friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<uint32_t>& free_childID_queue);
            template<class T1, class T2>
                friend void hierarchy::bind_child_to_new_parent(T1 child_pointer, T2 new_parent_pointer, std::vector<T1>& old_child_pointer_vector, std::queue<uint32_t>& old_free_childID_queue);
            template<class T1>
                friend void render_children(std::vector<T1>& child_pointer_vector);
            template<class T1>
                friend void render_this_object(ontology::Object* object_pointer, ontology::Shader* shader_pointer);

        private:
            void bind_to_parent();

            // this method renders this object.
            void render();

            ontology::Species* species_parent_pointer; // pointer to `Species`.
            ontology::Glyph* glyph_parent_pointer;     // pointer to `Glyph`.
            ontology::Text3D* text3D_parent_pointer;   // pointer to `Text3D`.
            bool is_character;

            uint32_t childID;                      // object ID, returned by `ontology::Species->get_objectID()`.
            bool has_entered;

            glm::vec3 coordinate_vector;           // coordinate vector.
            glm::vec3 original_scale_vector;       // original scale vector.
            GLfloat rotate_angle;                  // rotate angle.
            glm::vec3 rotate_vector;               // rotate vector.
            glm::vec3 translate_vector;            // translate vector.

            // The rest fields are created in the constructor.
            glm::mat4 model_matrix;                // model matrix.
            glm::mat4 MVP_matrix;                  // model view projection matrix.
    };

    template<class T1>
        void render_this_object(ontology::Object* object_pointer, ontology::Shader* shader_pointer)
        {
            if (!object_pointer->has_entered)
            {
                object_pointer->model_matrix = glm::translate(glm::mat4(1.0f), object_pointer->coordinate_vector);
                object_pointer->model_matrix = glm::scale(object_pointer->model_matrix, object_pointer->original_scale_vector);

                // store the new coordinates to be used in the next update.
                object_pointer->coordinate_vector = glm::vec3(object_pointer->model_matrix[0][0], object_pointer->model_matrix[1][1], object_pointer->model_matrix[2][2]);
                object_pointer->has_entered = true;
            }
            else
            {
                // create `rotation_matrix` using quaternions.
                glm::quat my_quaternion;
                my_quaternion = glm::quat(DEGREES_TO_RADIANS(object_pointer->rotate_vector));
                glm::mat4 rotation_matrix = glm::toMat4(my_quaternion);

                // rotate.
                // this->model_matrix = rotation_matrix * this->model_matrix;
                if (object_pointer->rotate_vector != glm::vec3(0.0f, 0.0f, 0.0f))
                {
                    object_pointer->model_matrix = glm::rotate(object_pointer->model_matrix, object_pointer->rotate_angle, object_pointer->rotate_vector);
                }

                object_pointer->model_matrix = glm::translate(object_pointer->model_matrix, object_pointer->translate_vector);
                object_pointer->coordinate_vector = glm::vec3(object_pointer->model_matrix[0][0], object_pointer->model_matrix[1][1], object_pointer->model_matrix[2][2]);
            }

            object_pointer->MVP_matrix = ProjectionMatrix * ViewMatrix * object_pointer->model_matrix;

            // Send our transformation to the currently bound shader,
            // in the "MVP" uniform.
            // glUniformMatrix4fv(this->parent_pointer->parent_pointer->parent_pointer->MatrixID, 1, GL_FALSE, &this->MVP_matrix[0][0]);
            glUniformMatrix4fv(shader_pointer->MatrixID, 1, GL_FALSE, &object_pointer->MVP_matrix[0][0]);
            // glUniformMatrix4fv(this->parent_pointer->parent_pointer->parent_pointer->ModelMatrixID, 1, GL_FALSE, &this->model_matrix[0][0]);
            glUniformMatrix4fv(shader_pointer->ModelMatrixID, 1, GL_FALSE, &object_pointer->model_matrix[0][0]);

            GLuint vertexbuffer;
            GLuint vertexPosition_modelspaceID;
            GLuint uvbuffer;
            GLuint vertexUVID;
            GLuint normalbuffer;
            GLuint vertexNormal_modelspaceID;
            GLuint elementbuffer;
            GLuint indices_size;

            if (object_pointer->is_character)
            {
                ontology::Glyph* parent_glyph = object_pointer->glyph_parent_pointer;
                vertexbuffer = parent_glyph->vertexbuffer;
                vertexPosition_modelspaceID = parent_glyph->vertexPosition_modelspaceID;
                uvbuffer = parent_glyph->uvbuffer;
                vertexUVID = parent_glyph->vertexUVID;
                normalbuffer = parent_glyph->normalbuffer;
                vertexNormal_modelspaceID = parent_glyph->vertexNormal_modelspaceID;
                elementbuffer = parent_glyph->elementbuffer;
                indices_size = parent_glyph->indices.size();
            }
            else
            {
                ontology::Species* parent_species = object_pointer->species_parent_pointer;
                vertexbuffer = parent_species->vertexbuffer;
                vertexPosition_modelspaceID = parent_species->vertexPosition_modelspaceID;
                uvbuffer = parent_species->uvbuffer;
                vertexUVID = parent_species->vertexUVID;
                normalbuffer = parent_species->normalbuffer;
                vertexNormal_modelspaceID = parent_species->vertexNormal_modelspaceID;
                elementbuffer = parent_species->elementbuffer;
                indices_size = parent_species->indices.size();
            }

            // 1st attribute buffer : vertices.
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glVertexAttribPointer(
                    vertexPosition_modelspaceID, // The attribute we want to configure
                    3,                           // size
                    GL_FLOAT,                    // type
                    GL_FALSE,                    // normalized?
                    0,                           // stride
                    (void*) 0                    // array buffer offset
                    );

            // 2nd attribute buffer : UVs.
            glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
            glVertexAttribPointer(
                    vertexUVID, // The attribute we want to configure
                    2,          // size : U+V => 2
                    GL_FLOAT,   // type
                    GL_FALSE,   // normalized?
                    0,          // stride
                    (void*) 0   // array buffer offset
                    );

            // 3rd attribute buffer : normals.
            glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
            glVertexAttribPointer(
                    vertexNormal_modelspaceID, // The attribute we want to configure
                    3,                         // size
                    GL_FLOAT,                  // type
                    GL_FALSE,                  // normalized?
                    0,                         // stride
                    (void*) 0                  // array buffer offset
                    );

            // Index buffer.
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

            // Draw the triangles!
            glDrawElements(
                    GL_TRIANGLES,    // mode
                    indices_size,    // count
                    GL_UNSIGNED_INT, // type
                    (void*) 0        // element array buffer offset
                    );
        }
}

#endif
