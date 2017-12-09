#ifndef __OBJECT_HPP_INCLUDED
#define __OBJECT_HPP_INCLUDED

#include "movable.hpp"
#include "shader.hpp"
#include "species.hpp"
#include "text3D.hpp"
#include "glyph.hpp"
#include "object_struct.hpp"
#include "render_templates.hpp"
#include "entity_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/common/globals.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

#ifndef __GLM_GTC_MATRIX_TRANSFORM_HPP_INCLUDED
#define __GLM_GTC_MATRIX_TRANSFORM_HPP_INCLUDED
#include <glm/gtc/matrix_transform.hpp>
#endif

#ifndef __GLM_GTC_QUATERNION_HPP_INCLUDED
#define __GLM_GTC_QUATERNION_HPP_INCLUDED
#include <glm/gtc/quaternion.hpp> // glm::quat
#endif

// Include standard headers
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace ontology
{
    class Species;
    class Glyph;

    class Object: public ontology::Movable
    {
        public:
            // constructor.
            Object(ontology::Universe* const universe, const ObjectStruct& object_struct)
                : Movable(universe, object_struct.cartesian_coordinates)
            {
                // constructor.
                this->original_scale_vector = object_struct.original_scale_vector;
                this->rotate_angle          = object_struct.rotate_angle;
                this->rotate_vector         = object_struct.rotate_vector;
                this->translate_vector      = object_struct.translate_vector;
                this->has_entered           = false;

                // enable rendering of a recently entered Object.
                // TODO: enable entering without enabling rendering.
                this->should_ylikuutio_render_this_object = true;

                this->is_character          = object_struct.is_character;
                this->quaternions_in_use    = object_struct.quaternions_in_use;
                this->model_matrix          = glm::mat4(1.0f); // identity matrix (dummy value).
                this->MVP_matrix            = glm::mat4(1.0f); // identity matrix (dummy value).

                if (this->is_character)
                {
                    this->glyph_parent   = object_struct.glyph_parent;
                    this->text3D_parent  = object_struct.text3D_parent;
                    this->species_parent = nullptr;
                }
                else
                {
                    this->species_parent = object_struct.species_parent;
                    this->glyph_parent   = nullptr;
                    this->text3D_parent  = nullptr;
                }

                // get `childID` from `Species` or `Glyph` and set pointer to this `Object`.
                this->bind_to_parent();
                this->type = "ontology::Object*";
            }

            // destructor.
            virtual ~Object();

            ontology::Entity* get_parent() const override;

            // this method sets pointer to this `Object` to nullptr, sets `parent` according to the input,
            // and requests a new `childID` from the new `Species` or from the new `Glyph`.
            void bind_to_new_parent(void* const new_parent);

            void set_name(const std::string& name);

            // Public callbacks (to be called from AI scripts written in
            // Chibi-Scheme). These are the functions that are available
            // for AI scripts. Ylikuutio will support scripting of game
            // agents using Chibi-Scheme. Ylikuutio does not predefine what
            // kind of games can be done with it. However, the callbacks
            // Ylikuutio provides mean these is more support for features
            // needing such callbacks. In particular, Ylikuutio supports
            // simulations of real-life phenomena.
            // TODO: implement public AI callbacks!

            // Command callbacks.

            // Allied-object-centric path and map information callbacks.

            // this method returns `true` if destination is visible, `false` otherwise.
            // destination may be visible directly (line of sight) or eg. by radar (without line of sight).
            static bool is_visible(const float x, const float y, const float z);

            // this method returns `true` if destination is visible with a line of sight for any own `Object`, `false` otherwise.
            static bool is_line_of_sight_for_any(const float x, const float y, const float z);

            // this method returns `true` if destination is visible with a line of sight for any own `Object`, `false` otherwise.
            static bool is_line_of_sight(const ontology::Object* const object, const float x, const float y, const float z);

            // this method returns `true` if there is any known ground path between `Object` and (x, y, z),  `false` otherwise.
            static bool is_ground_path_known(const ontology::Object* const object, const float x, const float y, const float z);

            // this method returns `true` if there is any known rail path between `Object` and (x, y, z),  `false` otherwise.
            static bool is_rail_path_known(const ontology::Object* const object, const float x, const float y, const float z);

            // this method returns `true` if there is known air path between objects, `false` otherwise.
            static bool is_air_path_known(const ontology::Object* const object, const float x, const float y, const float z);

            // this method returns `true` if there is known ballistic path between `Object` and (x, y, z), `false` otherwise.
            static bool is_ballistic_path_known(const ontology::Object* const object, const float x, const float y, const float z);

            // this method returns `true` if there may be ballistic path between objects, `false` otherwise.
            static bool may_have_ballistic_path(const ontology::Object* const object, const float x, const float y, const float z);

            // these functions return the coordinates of the farthest point
            static float get_closest_visible_ground_dest_x_towards(const ontology::Object* const object, const float x, const float y, const float z);
            static float get_closest_visible_ground_dest_y_towards(const ontology::Object* const object, const float x, const float y, const float z);
            static float get_closest_visible_ground_dest_z_towards(const ontology::Object* const object, const float x, const float y, const float z);

            // this method returns `true` if complete path is visible, `false` otherwise.
            static bool is_complete_ground_path_visible(const ontology::Object* const object, const float x, const float y, const float z);
            static bool is_complete_rail_path_visible(const ontology::Object* const object, const float x, const float y, const float z);
            static bool is_complete_air_path_visible(const ontology::Object* const object, const float x, const float y, const float z);
            static bool is_complete_ballistic_path_visible(const ontology::Object* const object, const float x, const float y, const float z);

            // these methods return the coordinates of the point closest to `object` from which there is known ballistic path to (x, y, z).
            static float get_nearest_known_ballistic_launch_site_x(const ontology::Object* const object, const float x, const float y, const float z);
            static float get_nearest_known_ballistic_launch_site_y(const ontology::Object* const object, const float x, const float y, const float z);
            static float get_nearest_known_ballistic_launch_site_z(const ontology::Object* const object, const float x, const float y, const float z);

            // these methods return the coordinates of the point closest to `object` from which there may be a ballistic path to (x, y, z).
            static float get_nearest_possible_ballistic_launch_site_x(const ontology::Object* const object, const float x, const float y, const float z);
            static float get_nearest_possible_ballistic_launch_site_y(const ontology::Object* const object, const float x, const float y, const float z);
            static float get_nearest_possible_ballistic_launch_site_z(const ontology::Object* const object, const float x, const float y, const float z);

            // this method returns `true` if there is known line of sight between (x1, y1, z1) and (x2, y2, z2).

            // Coordinate-centric path and map information callbacks.
            // The conditions for returning `true` match the conditions of the corresponding allied-object-centric callbacks.

            static bool is_line_of_sight_between_from(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
            static bool may_have_line_of_sight_between(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
            static bool is_ground_path_known_between(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
            static bool is_rail_path_known_between(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
            static bool is_air_path_known_between(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
            static bool is_ballistic_path_known(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
            static bool may_have_ballistic_path_between(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);

            static float get_nearest_known_ballistic_launch_site_x(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
            static float get_nearest_known_ballistic_launch_site_y(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
            static float get_nearest_known_ballistic_launch_site_z(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);

            static float get_nearest_possible_ballistic_launch_site_x(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
            static float get_nearest_possible_ballistic_launch_site_y(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
            static float get_nearest_possible_ballistic_launch_site_z(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);

            static float get_closest_visible_dest_x_towards(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
            static float get_closest_visible_dest_y_towards(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
            static float get_closest_visible_dest_z_towards(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);

            // Callbacks for looping through objects.
            static void* get_first_allied_object(ontology::Object* object);       // point `allied_iterator` to the first object, `nullptr` if N/A.
            static void* get_next_allied_object(ontology::Object* object);        // advance `allied_iterator`, `nullptr` if N/A.
            static void* get_first_other_allied_object(ontology::Object* object); // point `allied_other_iterator` to the first other object, `nullptr` if N/A.
            static void* get_next_other_allied_object(ontology::Object* object);  // advance `allied_other_iterator`, `nullptr` if N/A.
            static void* get_first_opponent_object(ontology::Object* object);     // point `opponent_iterator` to the first opponent, `nullptr` if N/A.
            static void* get_next_opponent_object(ontology::Object* object);      // advance `opponent_iterator`, `nullptr` if N/A.

            // Public callbacks end here.

            template<class T1>
                friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<int32_t>& free_childID_queue, int32_t* number_of_children);
            template<class T1, class T2>
                friend void hierarchy::bind_child_to_new_parent(T1 child_pointer, T2 new_parent, std::vector<T1>& old_child_pointer_vector, std::queue<int32_t>& old_free_childID_queue, int32_t* old_number_of_children);
            template<class T1>
                friend void render_children(const std::vector<T1>& child_pointer_vector);
            template<class T1>
                friend void set_name(std::string name, T1 entity);

        private:
            void bind_to_parent();

            // this method renders this `Object`.
            void render();
            void render_this_object(ontology::Shader* shader_pointer);

            int32_t get_number_of_children() const override;
            int32_t get_number_of_descendants() const override;

            // act according to this game/simulation object's programming.
            void act();

            ontology::Species* species_parent; // pointer to `Species`.
            ontology::Glyph* glyph_parent;     // pointer to `Glyph`.
            ontology::Text3D* text3D_parent;   // pointer to `Text3D`.
            bool is_character;
            bool quaternions_in_use;

            bool has_entered;
            bool should_ylikuutio_render_this_object;

            glm::vec3 original_scale_vector;       // original scale vector.
            GLfloat rotate_angle;                  // rotate angle.
            glm::vec3 rotate_vector;               // rotate vector.
            glm::vec3 translate_vector;            // translate vector.

            // The rest fields are created in the constructor.
            glm::mat4 model_matrix;                // model matrix.
            glm::mat4 MVP_matrix;                  // model view projection matrix.
    };
}

#endif
