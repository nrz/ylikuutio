#include "shader.hpp"
#include "scene.hpp"
#include "world.hpp"
#include "universe.hpp"
#include "material.hpp"
#include "glyph.hpp"
#include "symbiosis.hpp"
#include "render_templates.hpp"
#include "shader_struct.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

namespace ontology
{
    void Shader::bind_material(ontology::Material* const material)
    {
        // get `childID` from `Shader` and set pointer to `material`.
        hierarchy::bind_child_to_parent<ontology::Material*>(
                material,
                this->material_pointer_vector,
                this->free_materialID_queue,
                &this->number_of_materials);
    }

    void Shader::bind_symbiosis(ontology::Symbiosis* const symbiosis)
    {
        // get `childID` from `Shader` and set pointer to `symbiosis`.
        hierarchy::bind_child_to_parent<ontology::Symbiosis*>(
                symbiosis,
                this->symbiosis_pointer_vector,
                this->free_symbiosisID_queue,
                &this->number_of_symbioses);
    }

    void Shader::unbind_material(const int32_t childID)
    {
        ontology::Material* dummy_child_pointer = nullptr;
        hierarchy::set_child_pointer(
                childID,
                dummy_child_pointer,
                this->material_pointer_vector,
                this->free_materialID_queue,
                &this->number_of_materials);
    }

    void Shader::unbind_symbiosis(const int32_t childID)
    {
        ontology::Symbiosis* dummy_child_pointer = nullptr;
        hierarchy::set_child_pointer(
                childID,
                dummy_child_pointer,
                this->symbiosis_pointer_vector,
                this->free_symbiosisID_queue,
                &this->number_of_symbioses);
    }

    void Shader::bind_to_parent()
    {
        // get `childID` from `Scene` and set pointer to this `Shader`.
        this->parent->bind_shader(this);
    }

    void Shader::bind_to_new_parent(ontology::Scene* const new_scene_pointer)
    {
        // unbind from the old parent `Scene`.
        this->parent->unbind_shader(this->childID);

        // get `childID` from `Scene` and set pointer to this `Shader`.
        this->parent = new_scene_pointer;
        this->parent->bind_shader(this);
    }

    Shader::~Shader()
    {
        // destructor.
        std::cout << "Shader with childID " << std::dec << this->childID << " will be destroyed.\n";

        // destroy all materials of this shader.
        std::cout << "All materials of this shader will be destroyed.\n";
        hierarchy::delete_children<ontology::Material*>(this->material_pointer_vector, &this->number_of_materials);

        // destroy all symbioses of this shader.
        std::cout << "All symbioses of this shader will be destroyed.\n";
        hierarchy::delete_children<ontology::Symbiosis*>(this->symbiosis_pointer_vector, &this->number_of_symbioses);

        // set pointer to this shader to nullptr.
        this->parent->set_shader_pointer(this->childID, nullptr);

        glDeleteProgram(this->programID);
    }

    void Shader::render()
    {
        this->prerender();

        // [re]bind `programID` shader.
        glUseProgram(this->programID);

        glUniformMatrix4fv(this->view_matrixID, 1, GL_FALSE, &this->universe->get_view_matrix()[0][0]); // This one doesn't change between objects, so this can be done once for all objects that use "programID"

        // render this `Shader` by calling `render()` function of each `Material` and of each `Symbiosis`.
        ontology::render_children<ontology::Material*>(this->material_pointer_vector);
        ontology::render_children<ontology::Symbiosis*>(this->symbiosis_pointer_vector);

        this->postrender();
    }

    ontology::Entity* Shader::get_parent() const
    {
        return this->parent;
    }

    int32_t Shader::get_number_of_children() const
    {
        return this->number_of_materials + this->number_of_symbioses;
    }

    int32_t Shader::get_number_of_descendants() const
    {
        return -1;
    }

    void Shader::set_material_pointer(const int32_t childID, ontology::Material* const child_pointer)
    {
        hierarchy::set_child_pointer(childID, child_pointer, this->material_pointer_vector, this->free_materialID_queue, &this->number_of_materials);
    }

    void Shader::set_symbiosis_pointer(const int32_t childID, ontology::Symbiosis* const child_pointer)
    {
        hierarchy::set_child_pointer(childID, child_pointer, this->symbiosis_pointer_vector, this->free_symbiosisID_queue, &this->number_of_symbioses);
    }

    GLuint Shader::get_programID() const
    {
        return this->programID;
    }

    GLuint Shader::get_matrixID() const
    {
        return this->MatrixID;
    }

    GLuint Shader::get_model_matrixID() const
    {
        return this->model_matrixID;
    }

    void Shader::set_terrain_species(ontology::Species* const terrain_species)
    {
        this->terrain_species = terrain_species;
        this->universe->set_terrain_species(this->terrain_species);
    }
}
