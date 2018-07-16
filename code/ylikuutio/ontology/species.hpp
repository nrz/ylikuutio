#ifndef __SPECIES_HPP_INCLUDED
#define __SPECIES_HPP_INCLUDED

#include "species_or_glyph.hpp"
#include "model.hpp"
#include "universe.hpp"
#include "scene.hpp"
#include "shader.hpp"
#include "ground_level.hpp"
#include "species_struct.hpp"
#include "render_templates.hpp"
#include "code/ylikuutio/loaders/species_loader.hpp"
#include "code/ylikuutio/loaders/species_loader_struct.hpp"
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
#include <cstddef>  // std::size_t
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace ontology
    {
        class Material;

        class Species: public yli::ontology::Model
        {
            public:
                // this method sets pointer to this `Species` to nullptr, sets `parent` according to the input, and requests a new `childID` from the new `Material`.
                void bind_to_new_parent(yli::ontology::Material* const new_material_pointer);

                // constructor.
                Species(yli::ontology::Universe* const universe, const SpeciesStruct& species_struct)
                    : Model(universe)
                {
                    // constructor.
                    this->is_terrain          = species_struct.is_terrain;
                    this->is_symbiont_species = species_struct.is_symbiont_species;
                    this->planet_radius      = species_struct.planet_radius;
                    this->divisor           = species_struct.divisor;
                    this->model_file_format = species_struct.model_file_format;
                    this->model_filename    = species_struct.model_filename;
                    this->color_channel     = species_struct.color_channel;
                    this->light_position    = species_struct.light_position;
                    this->latitude          = species_struct.latitude;
                    this->longitude         = species_struct.longitude;
                    this->material_parent   = species_struct.material;
                    this->mesh_i            = species_struct.mesh_i;
                    this->x_step            = species_struct.x_step;
                    this->z_step            = species_struct.z_step;
                    this->triangulation_type = species_struct.triangulation_type;

                    this->char_model_file_format = this->model_file_format.c_str();
                    this->char_model_filename    = this->model_filename.c_str();

                    this->image_width = -1;
                    this->image_height = -1;

                    if (!this->is_symbiont_species)
                    {
                        // get `childID` from `Material` and set pointer to this `Species`.
                        this->bind_to_parent();

                        // Get a handle for our buffers.
                        this->vertex_position_modelspaceID = glGetAttribLocation(species_struct.shader->get_programID(), "vertexPosition_modelspace");
                        this->vertexUVID = glGetAttribLocation(species_struct.shader->get_programID(), "vertexUV");
                        this->vertex_normal_modelspaceID = glGetAttribLocation(species_struct.shader->get_programID(), "vertexNormal_modelspace");

                        // Get a handle for our "LightPosition" uniform.
                        glUseProgram(species_struct.shader->get_programID());
                        this->lightID = glGetUniformLocation(species_struct.shader->get_programID(), "LightPosition_worldspace");

                        if (this->is_terrain)
                        {
                            // set world species pointer so that it points to this species.
                            // currently there can be only one world species (used in collision detection).
                            this->universe->set_terrain_species(this);
                        }

                        // water level.
                        GLuint water_level_uniform_location = glGetUniformLocation(species_struct.shader->get_programID(), "water_level");
                        glUniform1f(water_level_uniform_location, species_struct.scene->get_water_level());

                        SpeciesLoaderStruct species_loader_struct;
                        species_loader_struct.model_filename = this->model_filename;
                        species_loader_struct.model_file_format = this->model_file_format;
                        species_loader_struct.latitude = this->latitude;
                        species_loader_struct.longitude = this->longitude;
                        species_loader_struct.planet_radius = this->planet_radius;
                        species_loader_struct.divisor = this->divisor;
                        species_loader_struct.color_channel = this->color_channel;
                        species_loader_struct.mesh_i = this->mesh_i;
                        species_loader_struct.x_step = this->x_step;
                        species_loader_struct.z_step = this->z_step;
                        species_loader_struct.image_width_pointer = &this->image_width;
                        species_loader_struct.image_height_pointer = &this->image_height;
                        species_loader_struct.triangulation_type = this->triangulation_type;

                        const bool is_debug_mode = true;

                        loaders::load_species(
                                species_loader_struct,
                                this->vertices,
                                this->uvs,
                                this->normals,
                                this->indices,
                                this->indexed_vertices,
                                this->indexed_uvs,
                                this->indexed_normals,
                                &this->vertexbuffer,
                                &this->uvbuffer,
                                &this->normalbuffer,
                                &this->elementbuffer,
                                is_debug_mode);

                        // TODO: Compute the graph of this object type to enable object vertex modification!

                        this->child_vector_pointers_vector.push_back(&this->object_pointer_vector);
                        this->type = "yli::ontology::Species*";

                        this->can_be_erased = true;
                    }
                }

                // destructor.
                virtual ~Species();

                yli::ontology::Entity* get_parent() const override;

                // this method sets an `Object` pointer.
                void set_object_pointer(const std::size_t childID, yli::ontology::Object* const child_pointer);

                int32_t get_image_width() const;
                int32_t get_image_height() const;

                const std::string& get_model_file_format() const;

                bool is_terrain;                           // worlds currently do not rotate nor translate.
                float planet_radius;                      // radius of sea level in kilometers. used only for worlds.
                float divisor;                           // value by which SRTM values are divided to convert them to kilometers.

                std::string color_channel;               // color channel in use: `"red"`, `"green"`, `"blue"`, `"mean"` or `"all"`.
                glm::vec3 light_position;                // light position.

                template<class T1>
                    friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t* number_of_children);
                template<class T1, class T2>
                    friend void yli::hierarchy::bind_child_to_new_parent(T1 child_pointer, T2 new_parent, std::vector<T1>& old_child_pointer_vector, std::queue<std::size_t>& old_free_childID_queue, std::size_t* old_number_of_children);
                template<class T1>
                    friend void render_species_or_glyph(T1 species_or_glyph_pointer);
                template<class T1>
                    friend void render_children(const std::vector<T1>& child_pointer_vector);

            private:
                void bind_to_parent();

                // this method renders all `Object`s of this `Species`.
                void render();

                yli::ontology::Material* material_parent;  // pointer to `Material`.

                bool is_symbiont_species;

                std::string model_file_format;        // type of the model file, eg. `"bmp"`.
                std::string model_filename;           // filename of the model file.

                const char* char_model_file_format;
                const char* char_model_filename;

                double latitude;  // for SRTM.
                double longitude; // for SRTM.

                std::size_t mesh_i;

                uint32_t x_step;
                uint32_t z_step;

                std::string triangulation_type;

                int32_t image_width;
                int32_t image_height;
        };
    }
}

#endif
