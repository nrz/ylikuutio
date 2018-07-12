#include "biont.hpp"
#include "holobiont.hpp"
#include "symbiont_species.hpp"
#include "biont_struct.hpp"
#include "render_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <string>   // std::string

namespace yli
{
    namespace ontology
    {
        class Entity;

        void Biont::bind_to_parent()
        {
            // get `childID` from `Holobiont` and set pointer to this `Biont`.
            this->holobiont_parent->bind_biont(this);
        }

        void Biont::bind_to_symbiont_species()
        {
            if (this->holobiont_parent == nullptr)
            {
                return;
            }

            yli::ontology::Symbiosis* symbiosis = static_cast<yli::ontology::Symbiosis*>(this->holobiont_parent->get_parent());
            this->symbiont_species = symbiosis->get_symbiont_species(this->biontID);
            this->symbiont_species->bind_biont(this);
        }

        void Biont::bind_to_new_parent(yli::ontology::Holobiont* const new_holobiont_parent)
        {
            // this method sets pointer to this `Biont` to nullptr, sets `parent` according to the input,
            // and requests a new `childID` from the new `Holobiont`.

            // unbind from the old parent `Holobiont`.
            this->holobiont_parent->unbind_biont(this->childID);

            // get `childID` from `Holobiont` and set pointer to this `Biont`.
            this->holobiont_parent = new_holobiont_parent;
            this->holobiont_parent->bind_biont(this);
        }

        Biont::~Biont()
        {
            // destructor.
            std::cout << "Biont with childID " << std::dec << this->childID << " will be destroyed.\n";

            // set pointer to this biont to nullptr.
            this->symbiont_species->unbind_biont(this->childID);
            this->holobiont_parent->set_biont_pointer(this->childID, nullptr);
        }

        void Biont::render()
        {
            // render this `Biont`.

            if (this->should_ylikuutio_render_this_biont)
            {
                this->prerender();

                yli::ontology::Symbiosis* symbiosis = static_cast<yli::ontology::Symbiosis*>(this->holobiont_parent->get_parent());
                yli::ontology::Shader* shader = static_cast<yli::ontology::Shader*>(symbiosis->get_parent());
                this->render_this_biont(shader);

                this->postrender();
            }
        }

        void Biont::render_this_biont(yli::ontology::Shader* const shader_pointer)
        {
            yli::ontology::Holobiont* holobiont = this->holobiont_parent;
            yli::ontology::Symbiosis* symbiosis = static_cast<yli::ontology::Symbiosis*>(holobiont->get_parent());

            if (!this->has_entered)
            {
                this->model_matrix = glm::translate(glm::mat4(1.0f), this->cartesian_coordinates);

                const std::string model_file_format = symbiosis->get_model_file_format();

                if (model_file_format.compare("fbx") == 0 || model_file_format.compare("FBX") == 0)
                {
                    // Only FBX bionts need initial rotation.
                    this->model_matrix = glm::rotate(this->model_matrix, this->initial_rotate_angle, this->initial_rotate_vector);
                }

                this->model_matrix = glm::scale(this->model_matrix, this->original_scale_vector);

                // store the new coordinates to be used in the next update.
                this->cartesian_coordinates = glm::vec3(this->model_matrix[3][0], this->model_matrix[3][1], this->model_matrix[3][2]);
                this->has_entered = true;
            }
            else
            {
                // rotate.
                if (this->rotate_vector != glm::vec3(0.0f, 0.0f, 0.0f))
                {
                    if (this->quaternions_in_use)
                    {
                        // create `rotation_matrix` using quaternions.
                        glm::quat my_quaternion = glm::quat(DEGREES_TO_RADIANS(this->rotate_vector));
                        glm::mat4 rotation_matrix = glm::mat4_cast(my_quaternion);
                        this->model_matrix = rotation_matrix * this->model_matrix;
                    }
                    else
                    {
                        this->model_matrix = glm::rotate(this->model_matrix, this->rotate_angle, this->rotate_vector);
                    }
                }

                this->model_matrix = glm::translate(this->model_matrix, this->translate_vector);
                this->cartesian_coordinates = glm::vec3(this->model_matrix[3][0], this->model_matrix[3][1], this->model_matrix[3][2]);
            }

            this->MVP_matrix = this->universe->get_projection_matrix() * this->universe->get_view_matrix() * this->model_matrix;

            // Bind our texture in Texture Unit 0.
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, symbiosis->get_texture(this->biontID));
            // Set our "myTextureSampler" sampler to user Texture Unit 0.
            glUniform1i(symbiosis->get_openGL_textureID(this->biontID), 0);

            // '`Material`' part ends here.

            // '`Species`' part begins here.

            // Compute the MVP matrix from keyboard and mouse input.
            glm::vec3 light_position = symbiosis->get_light_position(this->biontID);
            glUniform3f(
                    symbiosis->get_lightID(this->biontID),
                    light_position.x,
                    light_position.y,
                    light_position.z);

            yli::ontology::SymbiontSpecies* symbiont_species = symbiosis->get_symbiont_species(this->biontID);

            // 1st attribute buffer : vertices.
            glEnableVertexAttribArray(symbiont_species->get_vertex_position_modelspaceID());

            // 2nd attribute buffer : UVs.
            glEnableVertexAttribArray(symbiont_species->get_vertexUVID());

            // 3rd attribute buffer : normals.
            glEnableVertexAttribArray(symbiont_species->get_vertex_normal_modelspaceID());

            // '`Species`' part ends here.

            // Send our transformation to the currently bound shader,
            // in the "MVP" uniform.
            glUniformMatrix4fv(shader_pointer->get_matrixID(), 1, GL_FALSE, &this->MVP_matrix[0][0]);
            glUniformMatrix4fv(shader_pointer->get_model_matrixID(), 1, GL_FALSE, &this->model_matrix[0][0]);

            GLuint vertexbuffer = symbiont_species->get_vertexbuffer();
            GLuint vertex_position_modelspaceID = symbiont_species->get_vertex_position_modelspaceID();
            GLuint uvbuffer = symbiont_species->get_uvbuffer();
            GLuint vertexUVID = symbiont_species->get_vertexUVID();
            GLuint normalbuffer = symbiont_species->get_normalbuffer();
            GLuint vertex_normal_modelspaceID = symbiont_species->get_vertex_normal_modelspaceID();
            GLuint elementbuffer = symbiont_species->get_elementbuffer();
            GLuint indices_size = symbiont_species->get_indices_size();

            // 1st attribute buffer : vertices.
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glVertexAttribPointer(
                    vertex_position_modelspaceID, // The attribute we want to configure
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
                    vertex_normal_modelspaceID, // The attribute we want to configure
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

        yli::ontology::Entity* Biont::get_parent() const
        {
            return this->holobiont_parent;
        }

        std::size_t Biont::get_number_of_children() const
        {
            return 0; // `Biont` has no children.
        }

        std::size_t Biont::get_number_of_descendants() const
        {
            return 0; // `Biont` has no children.
        }
    }
}
