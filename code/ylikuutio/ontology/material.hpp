#ifndef __MATERIAL_HPP_INCLUDED
#define __MATERIAL_HPP_INCLUDED

#include "entity.hpp"
#include "shader.hpp"
#include "material_struct.hpp"
#include "render_templates.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/load/texture_loader.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/common/globals.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <cstring>  // std::memcmp, std::strcmp, std::strlen, std::strncmp
#include <iostream> // std::cout, std::cin, std::cerr
#include <queue>    // std::queue
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace ontology
    {
        class Universe;
        class Species;
        class Object;
        class VectorFont;
        class ChunkMaster;

        class Material: public yli::ontology::Entity
        {
            public:
                void bind_species(yli::ontology::Species* const species);
                void bind_vector_font(yli::ontology::VectorFont* const vector_font);
                void bind_chunk_master(ontology::ChunkMaster* const chunk_master);

                void unbind_species(const std::size_t childID);
                void unbind_vector_font(const std::size_t childID);
                void unbind_chunk_master(const std::size_t childID);

                // constructor.
                Material(yli::ontology::Universe* const universe, const MaterialStruct& material_struct)
                    : Entity(universe)
                {
                    // constructor.
                    this->parent                   = material_struct.shader;
                    this->is_symbiont_material     = material_struct.is_symbiont_material;
                    this->texture_file_format      = material_struct.texture_file_format;
                    this->texture_filename         = material_struct.texture_filename;
                    this->number_of_species        = 0;
                    this->number_of_vector_fonts   = 0;
                    this->number_of_chunk_masters  = 0;
                    this->texture                  = 0; // some dummy value.
                    this->openGL_textureID         = 0; // some dummy value.

                    if (!this->is_symbiont_material)
                    {
                        // get `childID` from the `Shader` and set pointer to this `Material`.
                        this->bind_to_parent();

                        // Load the texture.
                        if (this->texture_file_format == "bmp" || this->texture_file_format == "BMP")
                        {
                            if (!yli::load::load_BMP_texture(this->texture_filename, this->image_width, this->image_height, this->image_size, this->texture))
                            {
                                std::cerr << "ERROR: loading BMP texture failed!\n";
                            }
                        }
                        else if (this->texture_file_format == "dds" || this->texture_file_format == "DDS")
                        {
                            if (!yli::load::load_DDS_texture(this->texture_filename, this->image_width, this->image_height, this->image_size, this->texture))
                            {
                                std::cerr << "ERROR: loading DDS texture failed!\n";
                            }
                        }
                        else
                        {
                            std::cerr << "no texture was loaded!\n";
                            std::cerr << "texture file format: " << this->texture_file_format << "\n";
                        }

                        // requirements for further actions:
                        // `this->parent` must not be `nullptr`.
                        yli::ontology::Shader* const shader = this->parent;

                        if (shader == nullptr)
                        {
                            std::cerr << "ERROR: `Material::Material`: `shader` is `nullptr`!\n";
                            return;
                        }

                        // Get a handle for our "myTextureSampler" uniform.
                        this->openGL_textureID = glGetUniformLocation(shader->get_programID(), "myTextureSampler");

                        // `yli::ontology::Entity` member variables begin here.
                        this->child_vector_pointers_vector.push_back(&this->species_pointer_vector);
                        this->child_vector_pointers_vector.push_back(&this->vector_font_pointer_vector);
                        this->child_vector_pointers_vector.push_back(&this->chunk_master_pointer_vector);
                        this->type_string = "yli::ontology::Material*";
                        this->can_be_erased = true;
                    }
                }

                // destructor.
                virtual ~Material();

                // this method sets pointer to this `Material` to `nullptr`, sets `parent` according to the input, and requests a new `childID` from the new `Shader`.
                void bind_to_new_parent(yli::ontology::Shader* const new_parent);

                yli::ontology::Entity* get_parent() const override;

                // set terrain `Species` pointers in `Scene` and `Universe` so that they point to the chosen terrain `Species`.
                // currently there can be only one terrain `Species` in each `Scene` (used in collision detection).
                void set_terrain_species(yli::ontology::Species* const terrain_species);

                const std::string& get_texture_file_format() const;
                const std::string& get_texture_filename() const;
                std::size_t get_image_width() const;
                std::size_t get_image_height() const;
                std::size_t get_image_size() const;

                template<class T1>
                    friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);
                template <class T1>
                    friend void yli::hierarchy::unbind_child_from_parent(const std::size_t childID, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);
                template<class T1>
                    friend std::size_t yli::ontology::get_number_of_descendants(const std::vector<T1>& child_pointer_vector);
                template<class T1>
                    friend void yli::ontology::render_children(const std::vector<T1>& child_pointer_vector);

            protected:
                std::size_t image_width;
                std::size_t image_height;
                std::size_t image_size;

            private:
                void bind_to_parent();

                // this method renders all `Species` using this `Material`.
                void render();

                std::size_t get_number_of_children() const override;
                std::size_t get_number_of_descendants() const override;

                yli::ontology::Shader* parent;      // pointer to `Shader`.

                bool is_symbiont_material;

                GLuint texture;                        // Texture of this `Material`, returned by `load_BMP_texture` or `load_DDS_texture` (used for `glGenTextures` etc.).
                GLuint openGL_textureID;               // texture ID, returned by `glGetUniformLocation(programID, "myTextureSampler");`.

                std::vector<yli::ontology::Species*> species_pointer_vector;
                std::vector<yli::ontology::VectorFont*> vector_font_pointer_vector;
                std::vector<ontology::ChunkMaster*> chunk_master_pointer_vector;
                std::queue<std::size_t> free_speciesID_queue;
                std::queue<std::size_t> free_vector_fontID_queue;
                std::queue<std::size_t> free_chunk_masterID_queue;
                std::size_t number_of_species;
                std::size_t number_of_vector_fonts;
                std::size_t number_of_chunk_masters;

                std::string texture_file_format;       // type of the model file, eg. `"bmp"`.
                std::string texture_filename;          // filename of the model file.
        };
    }
}

#endif
