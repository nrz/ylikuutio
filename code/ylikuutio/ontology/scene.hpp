#ifndef __SCENE_HPP_INCLUDED
#define __SCENE_HPP_INCLUDED

#include "entity_templates.hpp"
#include "universe.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <unordered_map> // std::unordered_map
#include <vector>   // std::vector

namespace ontology
{
    class Universe;
    class Shader;
    class Species;
    class Object;

    class Scene
    {
        public:
            // constructor.
            Scene(ontology::Universe* universe_pointer);

            // destructor.
            ~Scene();

            // this method returns a pointer to an `Object` using the name as key.
            ontology::Object* get_object(std::string);

            void set_name(std::string name);

            friend class Shader;
            friend class Species;
            template<class T1>
                friend void render_children(std::vector<T1>& child_pointer_vector);
            template<class T1>
                friend void set_name(std::string name, T1 entity);
            template<class T1>
                friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<uint32_t>& free_childID_queue);
            template<class T1, class T2>
                friend void hierarchy::bind_child_to_new_parent(T1 child_pointer, T2 new_parent_pointer, std::vector<T1>& old_child_pointer_vector, std::queue<uint32_t>& old_free_childID_queue);

        private:
            // this method renders all `Shader`s of this `Scene`.
            void render();

            // this method sets a `Shader` pointer.
            void set_shader_pointer(uint32_t childID, ontology::Shader* child_pointer);

            ontology::Universe* parent_pointer;         // pointer to the `Universe`.

            void bind_to_parent();

            uint32_t childID;                     // scene ID, returned by `ontology::Universe->get_sceneID()`.

            std::vector<ontology::Shader*> shader_pointer_vector;
            std::queue<uint32_t> free_shaderID_queue;

            // For finding any `Object`s of this `Scene` by using its name.
            std::unordered_map<std::string, ontology::Object*> name_map;

            ontology::Universe* universe_pointer;
            std::string name;
    };
}

#endif
