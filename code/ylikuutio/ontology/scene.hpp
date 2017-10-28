#ifndef __SCENE_HPP_INCLUDED
#define __SCENE_HPP_INCLUDED

#include "entity.hpp"
#include "universe.hpp"
#include "entity_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
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
            Scene(ontology::Universe* const universe, const float water_level)
                : Entity(universe)
            {
                // constructor.
                this->gravity = 9.81f / 60.0f;
                this->fall_speed = this->gravity;
                this->water_level = static_cast<GLfloat>(water_level);

                this->universe = universe;
                this->parent = universe;

                this->cartesian_coordinates = nullptr;
                this->spherical_coordinates = nullptr;
                this->horizontal_angle = NAN;
                this->vertical_angle = NAN;
                this->turbo_factor = 1.0f;
                this->twin_turbo_factor = 1.0f;

                this->number_of_shaders = 0;

                // get `childID` from `Universe` and set pointer to this `Scene`.
                this->bind_to_parent();

                this->child_vector_pointers_vector.push_back(&this->shader_pointer_vector);
                this->type = "ontology::Scene*";
            }

            // destructor.
            virtual ~Scene();

            // this method returns a pointer to an `Entity` using the name as key.
            ontology::Entity* get_entity(const std::string);

            void set_name(std::string name);

            // this method returns a pointer to `datatypes::AnyValue` corresponding to the given `key`.
            std::shared_ptr<datatypes::AnyValue> get_variable(std::string key);
            void set_turbo_factor(float turbo_factor);
            void set_twin_turbo_factor(float turbo_factor);

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
                friend void hierarchy::bind_child_to_new_parent(T1 child_pointer, T2 new_parent, std::vector<T1>& old_child_pointer_vector, std::queue<int32_t>& old_free_childID_queue, int32_t* old_number_of_children);

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

            ontology::Universe* parent;   // pointer to the `Universe`.

            std::vector<ontology::Shader*> shader_pointer_vector;
            std::queue<int32_t> free_shaderID_queue;
            int32_t number_of_shaders;

            // For finding any `Entity`s of this `Scene` by using its name.
            std::unordered_map<std::string, ontology::Entity*> name_map;

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

            float turbo_factor;
            float twin_turbo_factor;

            // Variables related to physics.
            float gravity;
            float fall_speed;

            GLfloat water_level;
    };
}

#endif
