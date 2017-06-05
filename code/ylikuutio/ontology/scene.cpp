#ifndef PI
#define PI 3.14159265359f
#endif

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

#include "scene.hpp"
#include "ground_level.hpp"
#include "shader.hpp"
#include "render_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <unordered_map> // std::unordered_map

extern GLFWwindow* window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.

namespace ontology
{
    class Object;

    void Scene::bind_to_parent()
    {
        // get `childID` from `Universe` and set pointer to this `Scene`.
        hierarchy::bind_child_to_parent<ontology::Scene*>(this, this->parent_pointer->scene_pointer_vector, this->parent_pointer->free_sceneID_queue);
    }

    Scene::Scene(ontology::Universe* parent_pointer)
    {
        // constructor.
        this->universe_pointer = parent_pointer;
        this->parent_pointer = parent_pointer;

        // get `childID` from `Universe` and set pointer to this `Scene`.
        this->bind_to_parent();

        this->child_vector_pointers_vector.push_back(&this->shader_pointer_vector);
    }

    Scene::~Scene()
    {
        // destructor.
        std::cout << "Scene with childID " << std::dec << this->childID << " will be destroyed.\n";

        // destroy all shaders of this scene.
        std::cout << "All shaders of this scene will be destroyed.\n";
        hierarchy::delete_children<ontology::Shader*>(this->shader_pointer_vector);

        if (!this->name.empty() && this->universe_pointer != nullptr)
        {
            delete this->universe_pointer->entity_anyvalue_map[this->name];
            this->universe_pointer->entity_anyvalue_map[this->name] = nullptr;
        }
    }

    void Scene::render()
    {
        // render this `Scene` by calling `render()` function of each `Shader`.
        ontology::render_children<ontology::Shader*>(this->shader_pointer_vector);
    }

    // this method returns a pointer to an `Object` using the name as key.
    ontology::Object* Scene::get_object(std::string name)
    {
        return this->name_map[name];
    }

    void Scene::set_name(std::string name)
    {
        ontology::set_name(name, this);
    }

    void Scene::set_shader_pointer(uint32_t childID, ontology::Shader* child_pointer)
    {
        hierarchy::set_child_pointer(childID, child_pointer, this->shader_pointer_vector, this->free_shaderID_queue);
    }
}
