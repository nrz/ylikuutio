#ifndef __SYMBIOSIS_HPP_INCLUDED
#define __SYMBIOSIS_HPP_INCLUDED
// `Symbiosis` consists usually of 2 or more different `SymbiontMaterial`s and 2 or more `SymbiontSpecies` bound to these `SymbiontMaterial`s.
// All `SymbiontSpecies` of the same `Symbiosis` use the same `Shader`.
//
// In the future, a new class `ShaderSymbiosis` may be created should need for such class arise.
// `ShaderSymbiosis` is like `Symbiosis`, but it contains also `SymbiontShader`s in addition to `SymbiontMaterial`s and `SymbiontSpecies`.

#include "entity.hpp"
#include "symbiont_species.hpp"
#include "symbiosis_struct.hpp"
#include "symbiont_species_struct.hpp"
#include "entity_templates.hpp"
#include "code/ylikuutio/loaders/symbiosis_loader.hpp"
#include "code/ylikuutio/loaders/symbiosis_loader_struct.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/file/file_loader.hpp"
#include <ofbx.h>

// OpenFBX wants `u8` == `unsigned char`.
typedef unsigned char u8;

// Include standard headers
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace ontology
{
    class Shader;
    class SymbiontMaterial;

    class Symbiosis: public ontology::Entity
    {
        public:
            void bind(ontology::SymbiontMaterial* const symbiont_material);

            // this method sets pointer to this `Symbiosis` to nullptr, sets `parent` according to the input, and requests a new `childID` from the new `Shader`.
            void bind_to_new_parent(ontology::Shader* const new_shader_pointer);

            // constructor.
            Symbiosis(const SymbiosisStruct& symbiosis_struct)
                : Entity(symbiosis_struct.parent->get_universe())
            {
                // constructor.
                this->universe = symbiosis_struct.parent->get_universe();
                this->parent = symbiosis_struct.parent;

                // get `childID` from `Shader` and set pointer to this `Symbiosis`.
                this->bind_to_parent();

                this->number_of_symbiont_materials = 0;

                SymbiosisLoaderStruct symbiosis_loader_struct;
                symbiosis_loader_struct.model_filename = symbiosis_struct.model_filename;
                symbiosis_loader_struct.model_file_format = symbiosis_struct.model_file_format;
                symbiosis_loader_struct.triangulation_type = symbiosis_struct.triangulation_type;

                bool result = loaders::load_symbiosis(
                        symbiosis_loader_struct,
                        this->vertices,
                        this->UVs,
                        this->normals,
                        this->indices,
                        this->indexed_vertices,
                        this->indexed_UVs,
                        this->indexed_normals);

                // TODO: Compute the graph of each type to enable object vertex modification!

                this->type = "ontology::Symbiosis*";
            }

            // destructor.
            virtual ~Symbiosis();

            // this method renders all `SymbiontMaterial`s belonging to this `Symbiosis`.
            void render();

            int32_t get_number_of_children() const override;

            int32_t get_number_of_descendants() const override;

            void set_symbiont_material_pointer(const int32_t childID, ontology::SymbiontMaterial* const child_pointer);

            void set_name(std::string name);

            template<class T1>
                friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<int32_t>& free_childID_queue, int32_t* number_of_children);
            template<class T1, class T2>
                friend void hierarchy::bind_child_to_new_parent(T1 child_pointer, T2 new_parent, std::vector<T1>& old_child_pointer_vector, std::queue<int32_t>& old_free_childID_queue, int32_t* old_number_of_children);

        private:
            void bind_to_parent();

            ontology::Shader* parent; // pointer to `Shader`.

            std::vector<ontology::SymbiontMaterial*> symbiont_material_pointer_vector;
            std::queue<int32_t> free_symbiont_materialID_queue;
            int32_t number_of_symbiont_materials;

            std::vector<std::vector<glm::vec3>> vertices;         // vertices of the object.
            std::vector<std::vector<glm::vec2>> UVs;              // UVs of the object.
            std::vector<std::vector<glm::vec3>> normals;          // normals of the object.

            std::vector<std::vector<uint32_t>> indices;           // the deleted vertices will be reused (though it is not required, if there's enough memory).
            std::vector<std::vector<glm::vec3>> indexed_vertices;
            std::vector<std::vector<glm::vec2>> indexed_UVs;
            std::vector<std::vector<glm::vec3>> indexed_normals;
    };
}

#endif
