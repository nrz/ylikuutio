#ifndef __SCENE_HPP_INCLUDED
#define __SCENE_HPP_INCLUDED

#include "entity.hpp"
#include "universe.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <cstddef>  // std::size_t
#include <memory>   // std::make_shared, std::shared_ptr
#include <queue>    // std::queue
#include <string>   // std::string
#include <unordered_map> // std::unordered_map
#include <vector>   // std::vector

namespace yli
{
    namespace ontology
    {
        class Universe;
        class World;
        class Shader;
        class Symbiosis;
        class Camera;

        class Scene: public yli::ontology::Entity
        {
            public:
                void bind_shader(yli::ontology::Shader* const shader);
                void bind_camera(yli::ontology::Camera* const camera);

                void unbind_shader(const std::size_t childID);
                void unbind_camera(const std::size_t childID);

                // constructor.
                Scene(yli::ontology::Universe* const universe, yli::ontology::World* const world, const float water_level)
                    : Entity(universe)
                {
                    // constructor.
                    this->gravity = 9.81f / 60.0f;
                    this->fall_speed = this->gravity;
                    this->water_level = water_level;

                    this->parent = world;

                    this->cartesian_coordinates = nullptr;
                    this->spherical_coordinates = nullptr;
                    this->horizontal_angle = NAN;
                    this->vertical_angle = NAN;
                    this->turbo_factor = 1.0f;
                    this->twin_turbo_factor = 1.0f;

                    this->number_of_shaders = 0;
                    this->number_of_cameras = 0;
                    this->active_camera = nullptr;

                    // get `childID` from `World` and set pointer to this `Scene`.
                    this->bind_to_parent();

                    this->child_vector_pointers_vector.push_back(&this->shader_pointer_vector);
                    this->type = "yli::ontology::Scene*";

                    this->can_be_erased = true;
                }

                // destructor.
                virtual ~Scene();

                // this method renders all `Shader`s of this `Scene`.
                void render();

                yli::ontology::Camera* get_active_camera();
                void set_active_camera(yli::ontology::Camera* camera);

                // this method returns a pointer to an `Entity` using the name as key.
                yli::ontology::Entity* get_entity(const std::string) const;

                // this method returns a pointer to `yli::datatypes::AnyValue` corresponding to the given `key`.
                std::shared_ptr<yli::datatypes::AnyValue> get_variable(const std::string& key) const;
                float get_turbo_factor() const;
                void set_turbo_factor(float turbo_factor);
                float get_twin_turbo_factor() const;
                void set_twin_turbo_factor(float turbo_factor);

                float get_water_level() const;

                // this method sets a `Shader` pointer.
                void set_shader_pointer(const std::size_t childID, yli::ontology::Shader* const child_pointer);

                // this method sets a `Camera` pointer.
                void set_camera_pointer(const std::size_t childID, yli::ontology::Camera* const child_pointer);

                template<class T1>
                    friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t* number_of_children);
                template<class T1, class T2>
                    friend void yli::hierarchy::bind_child_to_new_parent(T1 child_pointer, T2 new_parent, std::vector<T1>& old_child_pointer_vector, std::queue<std::size_t>& old_free_childID_queue, std::size_t* old_number_of_children);

            private:
                void bind_to_parent();

                yli::ontology::Entity* get_parent() const override;
                std::size_t get_number_of_children() const override;
                std::size_t get_number_of_descendants() const override;

                // this method sets a `Symbiosis` pointer.
                void set_symbiosis_pointer(const std::size_t childID, yli::ontology::Symbiosis* const child_pointer);

                yli::ontology::World* parent;   // pointer to the `World`.

                std::vector<yli::ontology::Shader*> shader_pointer_vector;
                std::queue<std::size_t> free_shaderID_queue;
                std::size_t number_of_shaders;

                std::vector<yli::ontology::Camera*> camera_pointer_vector;
                std::queue<std::size_t> free_cameraID_queue;
                std::size_t number_of_cameras;

                yli::ontology::Camera* active_camera;

                // For finding any `Entity`s of this `Scene` by using its name.
                std::unordered_map<std::string, yli::ontology::Entity*> name_map;

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

                float water_level;
        };
    }
}

#endif
