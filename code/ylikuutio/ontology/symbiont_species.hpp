#ifndef __SYMBIONT_SPECIES_HPP_INCLUDED
#define __SYMBIONT_SPECIES_HPP_INCLUDED

#include "entity.hpp"
#include "shader.hpp"
#include "species_or_glyph.hpp"
#include "model.hpp"
#include "symbiont_material.hpp"
#include "symbiont_species_struct.hpp"
#include "render_templates.hpp"
#include "entity_templates.hpp"
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
#include <GLFW/glfw3.h>
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

namespace ontology
{
    class Universe;

    class SymbiontSpecies: public ontology::Model
    {
        public:
            // constructor.
            SymbiontSpecies(const SymbiontSpeciesStruct& symbiont_species_struct)
                : Model(symbiont_species_struct.universe)
            {
                // constructor.
                this->light_position = symbiont_species_struct.light_position;
                this->parent   = symbiont_species_struct.parent;
                this->universe = symbiont_species_struct.universe;

                // get `childID` from `Material` and set pointer to this `SymbiontSpecies`.
                this->bind_to_parent();

                // Get a handle for our buffers.
                ontology::Shader* shader = symbiont_species_struct.shader;
                this->vertexPosition_modelspaceID = glGetAttribLocation(shader->get_programID(), "vertexPosition_modelspace");
                this->vertexUVID = glGetAttribLocation(shader->get_programID(), "vertexUV");
                this->vertexNormal_modelspaceID = glGetAttribLocation(shader->get_programID(), "vertexNormal_modelspace");

                // Get a handle for our "LightPosition" uniform.
                glUseProgram(shader->get_programID());
                this->lightID = glGetUniformLocation(shader->get_programID(), "LightPosition_worldspace");

                SpeciesLoaderStruct species_loader_struct;
                species_loader_struct.model_filename = this->model_filename;
                species_loader_struct.model_file_format = this->model_file_format;

                this->image_width = -1;
                this->image_height = -1;

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
                this->type = "ontology::SymbiontSpecies*";
            }

            // destructor.
            virtual ~SymbiontSpecies();

            ontology::Entity* get_parent() const override;

            // this method sets pointer to this `SymbiontSpecies` to nullptr, sets `parent` according to the input, and requests a new `childID` from the new `Material`.
            // this method sets an `Object` pointer.
            void set_object_pointer(const int32_t childID, ontology::Object* const child_pointer);

            void set_name(const std::string& name);

            bool is_terrain;                           // worlds currently do not rotate nor translate.
            float planet_radius;                      // radius of sea level in kilometers. used only for worlds.
            float divisor;                           // value by which SRTM values are divided to convert them to kilometers.

            glm::vec3 light_position;                // light position.

            friend class Object;
            template<class T1>
                friend void render_children(const std::vector<T1>& child_pointer_vector);
            template<class T1>
                friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<int32_t>& free_childID_queue, int32_t* number_of_children);
            template<class T1>
                friend void render_species_or_glyph(T1 species_or_glyph_pointer);
            template<class T1>
                friend void set_name(std::string name, T1 entity);

        private:
            void bind_to_parent();

            // this method renders all `Object`s of this `SymbiontSpecies`.
            void render();

            ontology::SymbiontMaterial* parent; // pointer to `SymbiontMaterial`.

            std::string model_file_format;        // type of the model file, eg. `"bmp"`.
            std::string model_filename;           // filename of the model file.

            const char* char_model_file_format;
            const char* char_model_filename;

            double latitude;  // for SRTM.
            double longitude; // for SRTM.

            uint32_t x_step;
            uint32_t z_step;

            std::string triangulation_type;

            int32_t image_width;
            int32_t image_height;
    };
}

#endif
