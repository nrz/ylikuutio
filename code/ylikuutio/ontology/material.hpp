#ifndef __MATERIAL_HPP_INCLUDED
#define __MATERIAL_HPP_INCLUDED

#include "entity.hpp"
#include "shader.hpp"
#include "material_struct.hpp"
#include "render_templates.hpp"
#include "code/ylikuutio/loaders/texture_loader.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/common/globals.hpp"

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
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace space_partition
{
    class ChunkMaster;
}

namespace ontology
{
    class Universe;
    class Species;
    class Object;
    class VectorFont;

    class Material: public ontology::Entity
    {
        public:
            void bind_species(ontology::Species* const species);
            void bind_vector_font(ontology::VectorFont* const vector_font);
            void bind_chunk_master(space_partition::ChunkMaster* const chunk_master);

            void unbind_species(const int32_t childID);
            void unbind_vector_font(const int32_t childID);
            void unbind_chunk_master(const int32_t childID);

            // constructor.
            Material(ontology::Universe* const universe, const MaterialStruct& material_struct)
                : Entity(universe)
            {
                // constructor.
                this->parent = material_struct.shader;

                this->is_symbiont_material = material_struct.is_symbiont_material;

                this->terrain_species = nullptr;

                this->texture_file_format = material_struct.texture_file_format;
                this->texture_filename    = material_struct.texture_filename;

                this->char_texture_file_format = this->texture_file_format.c_str();
                this->char_texture_filename    = this->texture_filename.c_str();

                this->number_of_species = 0;
                this->number_of_vector_fonts = 0;
                this->number_of_chunk_masters = 0;

                this->texture = 0; // some dummy value.
                this->openGL_textureID = 0; // some dummy value.

                if (!this->is_symbiont_material)
                {
                    // get `childID` from the `Shader` and set pointer to this `Material`.
                    this->bind_to_parent();

                    // Load the texture.
                    if ((std::strcmp(this->char_texture_file_format, "bmp") == 0) || (std::strcmp(this->char_texture_file_format, "BMP") == 0))
                    {
                        this->texture = loaders::load_BMP_texture(this->texture_filename);
                    }
                    else if ((std::strcmp(this->char_texture_file_format, "dds") == 0) || (std::strcmp(this->char_texture_file_format, "DDS") == 0))
                    {
                        this->texture = loaders::load_DDS_texture(this->texture_filename);
                    }
                    else
                    {
                        std::cerr << "no texture was loaded!\n";
                        std::cerr << "texture file format: " << this->texture_file_format << "\n";
                    }

                    // Get a handle for our "myTextureSampler" uniform.
                    this->openGL_textureID = glGetUniformLocation(this->parent->get_programID(), "myTextureSampler");

                    this->child_vector_pointers_vector.push_back(&this->species_pointer_vector);
                    this->child_vector_pointers_vector.push_back(&this->vector_font_pointer_vector);
                    this->child_vector_pointers_vector.push_back(&this->chunk_master_pointer_vector);
                    this->type = "ontology::Material*";

                    this->can_be_erased = true;
                }
            }

            // destructor.
            virtual ~Material();

            // this method sets pointer to this `Material` to nullptr, sets `parent` according to the input, and requests a new `childID` from the new `Shader`.
            void bind_to_new_parent(ontology::Shader* const new_shader_pointer);

            ontology::Entity* get_parent() const override;

            // this method sets `Species` pointer.
            void set_species_pointer(const int32_t childID, ontology::Species* const child_pointer);

            // this method sets `VectorFont` pointer.
            void set_vector_font_pointer(const int32_t childID, ontology::VectorFont* const child_pointer);

            // this method sets `ChunkMaster` pointer.
            void set_chunk_master_pointer(const int32_t childID, space_partition::ChunkMaster* const child_pointer);

            // this method sets a terrain `Species` pointer.
            void set_terrain_species(ontology::Species* const terrain_species);

            template<class T1>
                friend void render_children(const std::vector<T1>& child_pointer_vector);
            template<class T1>
                friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<int32_t>& free_childID_queue, int32_t* number_of_children);
            template<class T1, class T2>
                friend void hierarchy::bind_child_to_new_parent(T1 child_pointer, T2 new_parent, std::vector<T1>& old_child_pointer_vector, std::queue<int32_t>& old_free_childID_queue, int32_t* old_number_of_children);

        private:
            void bind_to_parent();

            // this method renders all `Species` using this `Material`.
            void render();

            int32_t get_number_of_children() const override;
            int32_t get_number_of_descendants() const override;

            ontology::Shader* parent;      // pointer to `Shader`.

            bool is_symbiont_material;

            ontology::Species* terrain_species;    // pointer to terrain `Species` (used in collision detection).

            GLuint texture;                        // Texture of this `Material`, returned by `load_BMP_texture` or `load_DDS_texture` (used for `glGenTextures` etc.).
            GLuint openGL_textureID;               // texture ID, returned by `glGetUniformLocation(programID, "myTextureSampler");`.

            std::vector<ontology::Species*> species_pointer_vector;
            std::vector<ontology::VectorFont*> vector_font_pointer_vector;
            std::vector<space_partition::ChunkMaster*> chunk_master_pointer_vector;
            std::queue<int32_t> free_speciesID_queue;
            std::queue<int32_t> free_vector_fontID_queue;
            std::queue<int32_t> free_chunk_masterID_queue;
            int32_t number_of_species;
            int32_t number_of_vector_fonts;
            int32_t number_of_chunk_masters;

            std::string texture_file_format;       // type of the model file, eg. `"bmp"`.
            std::string texture_filename;          // filename of the model file.
            const char* char_texture_file_format;
            const char* char_texture_filename;
    };
}

#endif
