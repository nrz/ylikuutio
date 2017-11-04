#ifndef __SYMBIONT_MATERIAL_HPP_INCLUDED
#define __SYMBIONT_MATERIAL_HPP_INCLUDED

#include "entity.hpp"
#include "symbiosis.hpp"
#include "symbiont_material_struct.hpp"
#include "render_templates.hpp"
#include "entity_templates.hpp"
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

namespace ontology
{
    class SymbiontSpecies;
    class Object;

    class SymbiontMaterial: public ontology::Entity
    {
        public:
            // constructor.
            SymbiontMaterial(const SymbiontMaterialStruct& symbiont_material_struct)
                : Entity(symbiont_material_struct.universe)
            {
                // constructor.
                this->parent = symbiont_material_struct.parent;
                this->universe = symbiont_material_struct.universe;

                this->texture_file_format = symbiont_material_struct.texture_file_format;
                this->texture_filename    = symbiont_material_struct.texture_filename;

                this->char_texture_file_format = this->texture_file_format.c_str();
                this->char_texture_filename    = this->texture_filename.c_str();

                this->number_of_symbiont_species = 0;

                // get `childID` from the `Symbiosis` and set pointer to this `SymbiontMaterial`.
                this->bind_to_parent();

                // Load the texture.
                // TODO: load the texture into `this->texture`.
                // See `material.hpp` for details.

                this->child_vector_pointers_vector.push_back(&this->symbiont_species_pointer_vector);
                this->type = "ontology::SymbiontMaterial*";
            }

            // destructor.
            virtual ~SymbiontMaterial();

            // this method sets pointer to this `SymbiontMaterial` to nullptr, sets `parent` according to the input, and requests a new `childID` from the new `Symbiosis`.
            void set_name(const std::string& name);

            friend class Symbiosis;
            friend class SymbiontSpecies;
            friend class Object;
            template<class T1>
                friend void render_children(std::vector<T1>& child_pointer_vector);
            template<class T1>
                friend void set_name(std::string name, T1 entity);
            template<class T1>
                friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<int32_t>& free_childID_queue, int32_t* number_of_children);

        private:
            void bind_to_parent();

            // this method renders all `SymbiontSpecies` using this `SymbiontMaterial`.
            void render();

            ontology::Entity* get_parent() override;
            int32_t get_number_of_children() override;
            int32_t get_number_of_descendants() override;

            // this method sets `SymbiontSpecies` pointer.
            void set_symbiont_species_pointer(const int32_t childID, ontology::SymbiontSpecies* const child_pointer);

            ontology::Symbiosis* parent;           // pointer to `Symbiosis`.

            GLuint texture;                        // Texture of this `SymbiontMaterial`, returned by `load_BMP_texture` or `load_DDS_texture` (used for `glGenTextures` etc.).
            GLuint openGL_textureID;               // texture ID, returned by `glGetUniformLocation(programID, "myTextureSampler");`.

            std::vector<ontology::SymbiontSpecies*> symbiont_species_pointer_vector;
            std::queue<int32_t> free_symbiont_speciesID_queue;
            int32_t number_of_symbiont_species;

            std::string texture_file_format;       // type of the model file, eg. `"bmp"`.
            std::string texture_filename;          // filename of the model file.
            const char* char_texture_file_format;
            const char* char_texture_filename;
    };
}

#endif
