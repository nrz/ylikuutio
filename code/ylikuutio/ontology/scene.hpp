#ifndef __SCENE_HPP_INCLUDED
#define __SCENE_HPP_INCLUDED

#include "entity.hpp"
#include "universe.hpp"
#include "entity_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <memory>   // std::make_shared, std::shared_ptr
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
    class Symbiosis;
    class Object;

    class Scene: public ontology::Entity
    {
        public:
            // constructor.
            Scene(ontology::Universe* const universe_pointer, const float water_level);

            // destructor.
            virtual ~Scene();

            // this method returns a pointer to an `Object` using the name as key.
            ontology::Object* get_object(const std::string);

            void set_name(std::string name);

            // this method returns a pointer to `datatypes::AnyValue` corresponding to the given `key`.
            std::shared_ptr<datatypes::AnyValue> get_variable(std::string key);

            friend class Universe;
            friend class Shader;
            friend class Species;
            template<class T1>
                friend void render_children(std::vector<T1>& child_pointer_vector);
            template<class T1>
                friend void set_name(std::string name, T1 entity);
            template<class T1>
                friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<int32_t>& free_childID_queue, int32_t* number_of_children);
            template<class T1, class T2>
                friend void hierarchy::bind_child_to_new_parent(T1 child_pointer, T2 new_parent_pointer, std::vector<T1>& old_child_pointer_vector, std::queue<int32_t>& old_free_childID_queue, int32_t* old_number_of_children);

        private:
            void bind_to_parent();

            // this method renders all `Shader`s of this `Scene`.
            void render();

            ontology::Entity* get_parent() override;
            int32_t get_number_of_children() override;
            int32_t get_number_of_descendants() override;

            // this method sets a `Shader` pointer.
            void set_shader_pointer(const int32_t childID, ontology::Shader* const child_pointer);

            // this method sets a `Symbiosis` pointer.
            void set_symbiosis_pointer(const int32_t childID, ontology::Symbiosis* const child_pointer);

            ontology::Universe* parent_pointer;   // pointer to the `Universe`.

            std::vector<ontology::Shader*> shader_pointer_vector;
            std::queue<int32_t> free_shaderID_queue;
            int32_t number_of_shaders;

            // For finding any `Object`s of this `Scene` by using its name.
            std::unordered_map<std::string, ontology::Object*> name_map;

            // Variables related to location and orientation.

            // `cartesian_coordinates` can be accessed as a vector or as single coordinates `x`, `y`, `z`.
            glm::vec3* cartesian_coordinates;

            // `direction` can be accessed as a vector or as single coordinates `pitch`, `roll`, `yaw`.
            glm::vec3 direction;

            glm::vec3 right; // note: `right` can not be set directly using console.
            glm::vec3 up;    // note: `up` can not be set directly using console.

            // `spherical_coordinates` can be accessed as a vector or as single coordinates `rho`, `theta`, `phi`.
            SphericalCoordinatesStruct* spherical_coordinates;

            double horizontal_angle;
            double vertical_angle;

            // Variables related to physics.
            float gravity;
            float fall_speed;

            GLfloat water_level;
    };
}

#endif
