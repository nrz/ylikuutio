#ifndef __WORLD_HPP_INCLUDED
#define __WORLD_HPP_INCLUDED

#include "entity.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <queue>    // std::queue
#include <vector>   // std::vector

// `World` is just a collection of `Scene`s which share some common resources,
// like `VectorFont`s.

namespace yli
{
    namespace ontology
    {
        class Universe;
        class Scene;

        class World: public yli::ontology::Entity
        {
            public:
                void bind_scene(yli::ontology::Scene* const scene);
                void unbind_scene(const std::size_t childID);

                World(yli::ontology::Universe* const universe)
                    : Entity(universe)
                {
                    // constructor.

                    this->parent       = universe;
                    this->active_scene = nullptr;

                    this->number_of_scenes = 0;

                    // Get `childID` from `Universe` and set pointer to this `World`.
                    this->bind_to_parent();

                    // `yli::ontology::Entity` member variables begin here.
                    this->child_vector_pointers_vector.push_back(&this->scene_pointer_vector);
                    this->type_string = "yli::ontology::World*";
                    this->can_be_erased = true;
                }

                World(const World&) = delete;            // Delete copy constructor.
                World &operator=(const World&) = delete; // Delete copy assignment.

                // destructor.
                virtual ~World();

                // This method renders the active `Scene` of this `World`.
                void render();

                // This method sets the active `Scene`.
                void set_active_scene(yli::ontology::Scene* const scene);

                yli::ontology::Scene* get_active_scene() const;

                yli::ontology::Entity* get_parent() const override;
                std::size_t get_number_of_children() const override;
                std::size_t get_number_of_descendants() const override;

                template<class T1>
                    friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);

            private:
                void bind_to_parent();

                yli::ontology::Universe* parent; // pointer to the `Universe`.

                std::vector<yli::ontology::Scene*> scene_pointer_vector;
                std::queue<std::size_t> free_sceneID_queue;
                std::size_t number_of_scenes;

                yli::ontology::Scene* active_scene;
        };
    }
}

#endif
