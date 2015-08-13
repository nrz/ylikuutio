#ifndef __OBJECT_HPP_INCLUDED
#define __OBJECT_HPP_INCLUDED

// Include standard headers
#include <vector>    // std::vector
#include <queue>     // std::queue

#include "shader.hpp"
#include "model_common_functions.hpp"
#include "model_templates.hpp"

namespace model
{
    class Object
    {
        public:
            // constructor.
            Object(ObjectStruct object_struct);

            // destructor.
            ~Object();

            // this method sets pointer to this object to NULL, sets `parent_pointer` according to the input, and requests a new `childID` from the new species.
            void bind_to_new_parent(void* new_parent_pointer);
            template<class T1>
                friend void bind_child_to_parent(T1 child_pointer, std::vector<void*> &child_pointer_vector, std::queue<GLuint> &free_childID_queue);
            template<class T1, class T2>
                friend void bind_child_to_new_parent(T1 child_pointer, T2 new_parent_pointer, std::vector<void*> &old_child_pointer_vector, std::queue<GLuint> &old_free_childID_queue);
            template<class T1>
                friend void render_children(std::vector<void*> &child_pointer_vector);
            template<class T1>
                friend void render_this_object(model::Object* object_pointer, model::Shader* shader_pointer);

        private:
            void bind_to_parent();

            // this method renders this object.
            void render();

            void* parent_pointer;                  // pointer to the species or glyph.
            bool is_character;

            GLuint childID;                        // object ID, returned by `model::Species->get_objectID()`.
            bool has_entered;

            glm::vec3 coordinate_vector;           // coordinate vector.
            glm::vec3 original_scale_vector;       // original scale vector.
            GLfloat rotate_angle;                  // rotate angle.
            glm::vec3 rotate_vector;               // rotate vector.
            glm::vec3 translate_vector;            // translate vector.

            // The rest fields are created in the constructor.
            glm::mat4 model_matrix;                // model matrix.
            std::vector<glm::vec3> vertices;       // vertices of the object.
            std::vector<glm::vec2> UVs;            // UVs of the object.
            std::vector<glm::vec3> normals;        // normals of the object. not used at the moment.

            glm::mat4 MVP_matrix;                  // model view projection matrix.
    };

    template<class T1>
        void render_this_object(model::Object* object_pointer, model::Shader* shader_pointer)
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

            T1 parent_pointer = static_cast<T1>(object_pointer->parent_pointer);

            // Send our transformation to the currently bound shader,
            // in the "MVP" uniform.
            // glUniformMatrix4fv(this->parent_pointer->parent_pointer->parent_pointer->MatrixID, 1, GL_FALSE, &this->MVP_matrix[0][0]);
            glUniformMatrix4fv(shader_pointer->MatrixID, 1, GL_FALSE, &object_pointer->MVP_matrix[0][0]);
            // glUniformMatrix4fv(this->parent_pointer->parent_pointer->parent_pointer->ModelMatrixID, 1, GL_FALSE, &this->model_matrix[0][0]);
            glUniformMatrix4fv(shader_pointer->ModelMatrixID, 1, GL_FALSE, &object_pointer->model_matrix[0][0]);

            // 1st attribute buffer : vertices.
            glBindBuffer(GL_ARRAY_BUFFER, parent_pointer->vertexbuffer);
            glVertexAttribPointer(
                    parent_pointer->vertexPosition_modelspaceID, // The attribute we want to configure
                    3,                                           // size
                    GL_FLOAT,                                    // type
                    GL_FALSE,                                    // normalized?
                    0,                                           // stride
                    (void*) 0                                    // array buffer offset
                    );

            // 2nd attribute buffer : UVs.
            glBindBuffer(GL_ARRAY_BUFFER, parent_pointer->uvbuffer);
            glVertexAttribPointer(
                    parent_pointer->vertexUVID, // The attribute we want to configure
                    2,                          // size : U+V => 2
                    GL_FLOAT,                   // type
                    GL_FALSE,                   // normalized?
                    0,                          // stride
                    (void*) 0                   // array buffer offset
                    );

            // 3rd attribute buffer : normals.
            glBindBuffer(GL_ARRAY_BUFFER, parent_pointer->normalbuffer);
            glVertexAttribPointer(
                    parent_pointer->vertexNormal_modelspaceID, // The attribute we want to configure
                    3,                                         // size
                    GL_FLOAT,                                  // type
                    GL_FALSE,                                  // normalized?
                    0,                                         // stride
                    (void*) 0                                  // array buffer offset
                    );

            // Index buffer.
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, parent_pointer->elementbuffer);

            // Draw the triangles!
            glDrawElements(
                    GL_TRIANGLES,                   // mode
                    parent_pointer->indices.size(), // count
                    GL_UNSIGNED_INT,                // type
                    (void*) 0                       // element array buffer offset
                    );
        }
}

#endif
