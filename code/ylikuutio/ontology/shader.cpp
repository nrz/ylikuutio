#include "shader.hpp"
#include "scene.hpp"
#include "universe.hpp"
#include "material.hpp"
#include "render_templates.hpp"
#include "shader_struct.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/common/global_variables.hpp"

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

namespace ontology
{
    void Shader::bind_to_parent()
    {
        // get `childID` from the `Scene` and set pointer to this `Shader`.
        hierarchy::bind_child_to_parent<ontology::Shader*>(this, this->parent_pointer->shader_pointer_vector, this->parent_pointer->free_shaderID_queue);
    }

    Shader::Shader(ShaderStruct shader_struct)
    {
        // constructor.

        this->vertex_shader        = shader_struct.vertex_shader;
        this->fragment_shader      = shader_struct.fragment_shader;

        this->char_vertex_shader   = this->vertex_shader.c_str();
        this->char_fragment_shader = this->fragment_shader.c_str();
        this->parent_pointer       = shader_struct.parent_pointer;
        this->universe_pointer     = this->parent_pointer->universe_pointer;

        // get `childID` from the `Scene` and set pointer to this `Shader`.
        this->bind_to_parent();

        // Create and compile our GLSL program from the shaders.
        this->programID = loaders::load_shaders(this->char_vertex_shader, this->char_fragment_shader);

        // Get a handle for our "MVP" uniform.
        this->MatrixID = glGetUniformLocation(this->programID, "MVP");
        this->ViewMatrixID = glGetUniformLocation(this->programID, "V");
        this->ModelMatrixID = glGetUniformLocation(this->programID, "M");
    }

    Shader::~Shader()
    {
        // destructor.
        std::cout << "Shader with childID " << std::dec << this->childID << " will be destroyed.\n";

        // destroy all materials of this shader.
        std::cout << "All materials of this shader will be destroyed.\n";
        hierarchy::delete_children<ontology::Material*>(this->material_pointer_vector);

        // set pointer to this shader to nullptr.
        this->parent_pointer->set_shader_pointer(this->childID, nullptr);

        glDeleteProgram(this->programID);

        if (!this->name.empty() && this->universe_pointer != nullptr)
        {
            delete this->universe_pointer->entity_anyvalue_map[this->name];
            this->universe_pointer->entity_anyvalue_map[this->name] = nullptr;
        }
    }

    void Shader::render()
    {
        // [re]bind `programID` shader.
        glUseProgram(this->programID);

        glUniformMatrix4fv(this->ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]); // This one doesn't change between objects, so this can be done once for all objects that use "programID"

        // render Shader by calling `render()` function of each Material.
        ontology::render_children<ontology::Material*>(this->material_pointer_vector);
    }

    void Shader::set_material_pointer(uint32_t childID, ontology::Material* child_pointer)
    {
        hierarchy::set_child_pointer(childID, child_pointer, this->material_pointer_vector, this->free_materialID_queue);
    }

    void Shader::bind_to_new_parent(ontology::Scene* new_scene_pointer)
    {
        // this method sets pointer to this `Shader` to nullptr, sets `parent_pointer` according to the input, and requests a new `childID` from the new `Scene`.
        hierarchy::bind_child_to_new_parent<ontology::Shader*, ontology::Scene*>(this, new_scene_pointer, this->parent_pointer->shader_pointer_vector, this->parent_pointer->free_shaderID_queue);
    }

    void Shader::set_name(std::string name)
    {
        ontology::set_name(name, this);
    }

    void Shader::set_terrain_species_pointer(ontology::Species* terrain_species_pointer)
    {
        this->terrain_species_pointer = terrain_species_pointer;
        this->parent_pointer->parent_pointer->set_terrain_species_pointer(this->terrain_species_pointer);
    }
}
