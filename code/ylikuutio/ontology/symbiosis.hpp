#ifndef __SYMBIOSIS_HPP_INCLUDED
#define __SYMBIOSIS_HPP_INCLUDED
// `Symbiosis` consists usually of 2 or more different `Material`s and 2 or more `Species` bound to these `Material`s.
// Symbiont `Species` use the same `Shader`. In the future, a new class `ShaderSymbiosis` may be crated should need for such class arise.
// `ShaderSymbiosis` is like `Symbiosis`, but it contains also `Shader`s in addition to `Material`s and `Species`.

#include "symbiosis_struct.hpp"
#include "entity_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace ontology
{
    class Universe;
    class Shader;
    class Material;
    class Species;

    class Symbiosis
    {
        public:
            // constructor.
            Symbiosis(SymbiosisStruct symbiosis_struct);

            // destructor.
            ~Symbiosis();

            // this method sets pointer to this `Symbiosis` to nullptr, sets `parent_pointer` according to the input, and requests a new `childID` from the new `Shader`.
            void bind_to_new_parent(ontology::Shader* new_shader_pointer);

            void set_name(std::string name);

            template<class T1>
                friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<uint32_t>& free_childID_queue);

        private:
            void bind_to_parent();

            // no `render()` member function in `Symbiosis` because `Symbiosis` is not present in the rendering hierarchy.

            ontology::Universe* universe_pointer; // pointer to `Universe`.
            ontology::Shader* parent_pointer;     // pointer to `Scene`.

            uint32_t childID;                     // symbiosis ID, set by `this->bind_to_parent()`.

            std::vector<void*> child_vector_pointers_vector;

            std::vector<ontology::Material*> material_pointer_vector;
            std::vector<ontology::Species*> species_pointer_vector;
            std::queue<uint32_t> free_materialID_queue;
            std::queue<uint32_t> free_speciesID_queue;

            std::string name;                     // name of this entity.
    };
}
#endif
