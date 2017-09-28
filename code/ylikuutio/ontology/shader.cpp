#include "shader.hpp"
#include "scene.hpp"
#include "universe.hpp"
#include "material.hpp"
#include "render_templates.hpp"
#include "shader_struct.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include GLFW
#ifndef __GLFW3_H_INCLUDED
#define __GLFW3_H_INCLUDED
#include <GLFW/glfw3.h>
#endif

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

namespace ontology
{
    void Shader::bind_to_parent()
    {
        // get `childID` from `Scene` and set pointer to this `Shader`.
        hierarchy::bind_child_to_parent<ontology::Shader*>(this, this->parent_pointer->shader_pointer_vector, this->parent_pointer->free_shaderID_queue, &this->parent_pointer->number_of_shaders);
    }

    Shader::Shader(const ShaderStruct shader_struct)
    {
        // constructor.

        this->vertex_shader        = shader_struct.vertex_shader;
        this->fragment_shader      = shader_struct.fragment_shader;

        this->char_vertex_shader   = this->vertex_shader.c_str();
        this->char_fragment_shader = this->fragment_shader.c_str();
        this->parent_pointer       = shader_struct.parent_pointer;
        this->universe_pointer     = this->parent_pointer->universe_pointer;

        this->number_of_materials = 0;
        this->number_of_symbioses = 0;

        // get `childID` from `Scene` and set pointer to this `Shader`.
        this->bind_to_parent();

        // Create and compile our GLSL program from the shaders.
        this->programID = loaders::load_shaders(this->char_vertex_shader, this->char_fragment_shader);

        // Get a handle for our "MVP" uniform.
        this->MatrixID = glGetUniformLocation(this->programID, "MVP");
        this->ViewMatrixID = glGetUniformLocation(this->programID, "V");
        this->ModelMatrixID = glGetUniformLocation(this->programID, "M");

        this->child_vector_pointers_vector.push_back(&this->material_pointer_vector);
        this->child_vector_pointers_vector.push_back(&this->symbiosis_pointer_vector);
        this->type = "ontology::Shader*";
    }

    Shader::~Shader()
    {
        // destructor.
        std::cout << "Shader with childID " << std::dec << this->childID << " will be destroyed.\n";

        // destroy all materials of this shader.
        std::cout << "All materials of this shader will be destroyed.\n";
        hierarchy::delete_children<ontology::Material*>(this->material_pointer_vector, &this->number_of_materials);

        // set pointer to this shader to nullptr.
        this->parent_pointer->set_shader_pointer(this->childID, nullptr);

        glDeleteProgram(this->programID);
    }

    void Shader::render()
    {
        this->prerender();

        // [re]bind `programID` shader.
        glUseProgram(this->programID);

        glUniformMatrix4fv(this->ViewMatrixID, 1, GL_FALSE, &this->universe_pointer->ViewMatrix[0][0]); // This one doesn't change between objects, so this can be done once for all objects that use "programID"

        // render this `Shader` by calling `render()` function of each `Material`.
        ontology::render_children<ontology::Material*>(this->material_pointer_vector);

        this->postrender();
    }

    int32_t Shader::get_number_of_children()
    {
        return this->number_of_materials + this->number_of_symbioses;
    }

    int32_t Shader::get_number_of_descendants()
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

    void Shader::bind_to_new_parent(ontology::Scene* const new_scene_pointer)
    {
        // this method sets pointer to this `Shader` to nullptr, sets `parent_pointer` according to the input, and requests a new `childID` from the new `Scene`.
        hierarchy::bind_child_to_new_parent<ontology::Shader*, ontology::Scene*>(this, new_scene_pointer, this->parent_pointer->shader_pointer_vector, this->parent_pointer->free_shaderID_queue, &this->parent_pointer->number_of_shaders);
    }

    void Shader::set_name(std::string name)
    {
        ontology::set_name(name, this);
    }

    void Shader::set_terrain_species_pointer(ontology::Species* const terrain_species_pointer)
    {
        this->terrain_species_pointer = terrain_species_pointer;
        this->parent_pointer->parent_pointer->set_terrain_species_pointer(this->terrain_species_pointer);
    }
}
