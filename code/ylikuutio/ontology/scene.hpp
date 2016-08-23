#ifndef __SCENE_HPP_INCLUDED
#define __SCENE_HPP_INCLUDED

#include "universe.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace ontology
{
    class Shader;
    class Species;

    class Scene
    {
        public:
            // constructor.
            Scene(ontology::Universe* universe_pointer);

            // destructor.
            ~Scene();

            // this method sets pointer to this `Scene` to nullptr, sets `parent_pointer` according to the input, and requests a new `childID` from the new `Universe`.
            void bind_to_new_parent(ontology::Universe* new_universe_pointer);

            friend class Shader;
            friend class Species;
            template<class T1>
                friend void render_children(std::vector<T1>& child_pointer_vector);
            template<class T1>
                friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<uint32_t>& free_childID_queue);
            template<class T1, class T2>
                friend void hierarchy::bind_child_to_new_parent(T1 child_pointer, T2 new_parent_pointer, std::vector<T1>& old_child_pointer_vector, std::queue<uint32_t>& old_free_childID_queue);

        private:
            // this method renders all shaders of this scene.
            void render();

            // this method sets a shader pointer.
            void set_shader_pointer(uint32_t childID, ontology::Shader* child_pointer);

            ontology::Universe* parent_pointer;         // pointer to the world.

            void bind_to_parent();

            uint32_t childID;                     // scene ID, returned by `ontology::Universe->get_sceneID()`.

            std::vector<ontology::Shader*> shader_pointer_vector;
            std::queue<uint32_t> free_shaderID_queue;
    };
}

#endif
