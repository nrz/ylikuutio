#ifndef __SCENE_HPP_INCLUDED
#define __SCENE_HPP_INCLUDED

#include "world.hpp"
#include "cpp/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace model
{
    class Scene
    {
        public:
            // constructor.
            Scene(model::World* world_pointer);

            // destructor.
            ~Scene();

            // this method sets pointer to this scene to nullptr, sets `parent_pointer` according to the input, and requests a new `childID` from the new world.
            void bind_to_new_parent(model::World* new_world_pointer);

            friend class Shader;
            friend class Species;
            template<class T1>
                friend void render_children(std::vector<void*> &child_pointer_vector);
            template<class T1>
                friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<void*> &child_pointer_vector, std::queue<uint32_t> &free_childID_queue);
            template<class T1, class T2>
                friend void hierarchy::bind_child_to_new_parent(T1 child_pointer, T2 new_parent_pointer, std::vector<void*> &old_child_pointer_vector, std::queue<uint32_t> &old_free_childID_queue);

        private:
            // this method renders all shaders of this scene.
            void render();

            // this method sets a shader pointer.
            void set_shader_pointer(uint32_t childID, void* parent_pointer);

            model::World* parent_pointer;         // pointer to the world.

            void bind_to_parent();

            uint32_t childID;                     // scene ID, returned by `model::World->get_sceneID()`.

            std::vector<void*> shader_pointer_vector;
            std::queue<uint32_t> free_shaderID_queue;
    };
}

#endif
