#include "species.hpp"
#include "vboindexer.hpp"
#include "universe.hpp"
#include "scene.hpp"
#include "shader.hpp"
#include "material.hpp"
#include "object.hpp"
#include "species_or_glyph.hpp"
#include "species_struct.hpp"
#include "render_templates.hpp"
#include "code/ylikuutio/loaders/species_loader.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include GLFW
#ifndef __GLFW3_H_INCLUDED
#define __GLFW3_H_INCLUDED
#include <glfw3.h>
#endif

// Include standard headers
#include <cstring>  // std::memcmp, std::strcmp, std::strlen, std::strncmp
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.

namespace ontology
{
    void Species::bind_to_parent()
    {
        // get `childID` from `Material` and set pointer to this `Species`.
        hierarchy::bind_child_to_parent<ontology::Species*>(this, this->parent_pointer->species_pointer_vector, this->parent_pointer->free_speciesID_queue, &this->parent_pointer->number_of_species);
    }

    Species::Species(const SpeciesStruct species_struct)
    {
        // constructor.
        this->is_world          = species_struct.is_world;
        this->world_radius      = species_struct.world_radius;
        this->divisor           = species_struct.divisor;
        this->model_file_format = species_struct.model_file_format;
        this->model_filename    = species_struct.model_filename;
        this->color_channel     = species_struct.color_channel;
        this->light_position    = species_struct.light_position;
        this->latitude          = species_struct.latitude;
        this->longitude         = species_struct.longitude;
        this->parent_pointer    = species_struct.parent_pointer;
        this->universe_pointer  = this->parent_pointer->universe_pointer;
        this->x_step            = species_struct.x_step;
        this->z_step            = species_struct.z_step;
        this->triangulation_type = species_struct.triangulation_type;

        this->char_model_file_format = this->model_file_format.c_str();
        this->char_model_filename    = this->model_filename.c_str();

        // get `childID` from `Material` and set pointer to this `Species`.
        this->bind_to_parent();

        // Get a handle for our buffers.
        this->vertexPosition_modelspaceID = glGetAttribLocation(this->parent_pointer->parent_pointer->programID, "vertexPosition_modelspace");
        this->vertexUVID = glGetAttribLocation(this->parent_pointer->parent_pointer->programID, "vertexUV");
        this->vertexNormal_modelspaceID = glGetAttribLocation(this->parent_pointer->parent_pointer->programID, "vertexNormal_modelspace");

        // Get a handle for our "LightPosition" uniform.
        glUseProgram(this->parent_pointer->parent_pointer->programID);
        this->lightID = glGetUniformLocation(this->parent_pointer->parent_pointer->programID, "LightPosition_worldspace");

        if (this->is_world)
        {
            // set world species pointer so that it points to this species.
            // currently there can be only one world species (used in collision detection).
            this->parent_pointer->parent_pointer->parent_pointer->parent_pointer->set_terrain_species_pointer(this);
        }

        // water level.
        GLuint water_level_uniform_location = glGetUniformLocation(this->parent_pointer->parent_pointer->programID, "water_level");
        glUniform1f(water_level_uniform_location, this->universe_pointer->active_scene->water_level);

        SpeciesLoaderStruct species_loader_struct;
        species_loader_struct.model_filename = this->model_filename;
        species_loader_struct.model_file_format = this->model_file_format;
        species_loader_struct.latitude = this->latitude;
        species_loader_struct.longitude = this->longitude;
        species_loader_struct.world_radius = this->world_radius;
        species_loader_struct.divisor = this->divisor;
        species_loader_struct.color_channel = this->color_channel;
        species_loader_struct.x_step = this->x_step;
        species_loader_struct.z_step = this->z_step;
        species_loader_struct.triangulation_type = this->triangulation_type;

        loaders::load_species(
                species_loader_struct,
                this->vertices,
                this->UVs,
                this->normals,
                this->indices,
                this->indexed_vertices,
                this->indexed_UVs,
                this->indexed_normals,
                &this->vertexbuffer,
                &this->uvbuffer,
                &this->normalbuffer,
                &this->elementbuffer,
                this->image_width,
                this->image_height);

        // TODO: Compute the graph of this object type to enable object vertex modification!

        this->child_vector_pointers_vector.push_back(&this->object_pointer_vector);
        this->type = "ontology::Species*";
    }

    Species::~Species()
    {
        // destructor.
        std::cout << "Species with childID " << std::dec << this->childID << " will be destroyed.\n";

        // destroy all objects of this species.
        std::cout << "All objects of this species will be destroyed.\n";
        hierarchy::delete_children<ontology::Object*>(this->object_pointer_vector, &this->number_of_objects);

        // Cleanup VBO, shader and texture.
        glDeleteBuffers(1, &this->vertexbuffer);
        glDeleteBuffers(1, &this->uvbuffer);
        glDeleteBuffers(1, &this->normalbuffer);
        glDeleteBuffers(1, &this->elementbuffer);

        // set pointer to this species to nullptr.
        this->parent_pointer->set_species_pointer(this->childID, nullptr);
    }

    void Species::render()
    {
        this->prerender();

        // render this `Species`.
        ontology::render_species_or_glyph<ontology::Species*>(this);

        this->postrender();
    }

    void Species::set_object_pointer(const uint32_t childID, ontology::Object* const child_pointer)
    {
        hierarchy::set_child_pointer(childID, child_pointer, this->object_pointer_vector, this->free_objectID_queue, &this->number_of_objects);
    }

    void Species::set_name(const std::string name)
    {
        ontology::set_name(name, this);
    }

    void Species::bind_to_new_parent(ontology::Material* const new_material_pointer)
    {
        // this method sets pointer to this `Species` to nullptr, sets `parent_pointer` according to the input, and requests a new `childID` from the new `Material`.
        hierarchy::bind_child_to_new_parent<ontology::Species*, ontology::Material*>(this, new_material_pointer, this->parent_pointer->species_pointer_vector, this->parent_pointer->free_speciesID_queue, &this->parent_pointer->number_of_species);
    }
}
