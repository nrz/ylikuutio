#ifndef __HOLOBIONT_HPP_INCLUDED
#define __HOLOBIONT_HPP_INCLUDED

#include "movable.hpp"
#include "shader.hpp"
#include "symbiosis.hpp"
#include "holobiont_struct.hpp"
#include "render_templates.hpp"
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
#include <cstddef>  // std::size_t
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace ontology
    {
        class Biont;

        class Holobiont: public yli::ontology::Movable
        {
            public:
                void bind_biont(yli::ontology::Biont* const biont);
                void unbind_biont(const int32_t childID);

                // this method sets pointer to this `Object` to nullptr, sets `parent` according to the input,
                // and requests a new `childID` from the new `Species` or from the new `Glyph`.
                void bind_to_new_parent(yli::ontology::Symbiosis* const new_parent);

                // constructor.
                Holobiont(yli::ontology::Universe* const universe, HolobiontStruct& holobiont_struct)
                    : Movable(universe, holobiont_struct.cartesian_coordinates)
                {
                    // constructor.
                    this->symbiosis_parent      = holobiont_struct.symbiosis_parent;

                    this->original_scale_vector = holobiont_struct.original_scale_vector;
                    this->rotate_angle          = holobiont_struct.rotate_angle;
                    this->rotate_vector         = holobiont_struct.rotate_vector;
                    this->initial_rotate_angle  = holobiont_struct.initial_rotate_angle;
                    this->initial_rotate_vector = holobiont_struct.initial_rotate_vector;
                    this->quaternions_in_use    = holobiont_struct.quaternions_in_use;
                    this->cartesian_coordinates = holobiont_struct.cartesian_coordinates;
                    this->translate_vector      = holobiont_struct.translate_vector;
                    this->has_entered           = false;

                    this->should_ylikuutio_render_this_holobiont = true;
                    this->number_of_bionts = 0;

                    // get `childID` from `Symbiosis` and set pointer to this `Holobiont`.
                    this->bind_to_parent();
                    this->type = "yli::ontology::Holobiont*";

                    this->create_bionts();

                    this->can_be_erased = true;
                }

                // destructor.
                virtual ~Holobiont();

                void update_x(float x);
                void update_y(float y);
                void update_z(float z);

                yli::ontology::Entity* get_parent() const override;

                void set_biont_pointer(const int32_t childID, yli::ontology::Biont* const child_pointer);

                template<class T1>
                    friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<int32_t>& free_childID_queue, std::size_t* number_of_children);
                template<class T1, class T2>
                    friend void hierarchy::bind_child_to_new_parent(T1 child_pointer, T2 new_parent, std::vector<T1>& old_child_pointer_vector, std::queue<int32_t>& old_free_childID_queue, std::size_t* old_number_of_children);
                template<class T1>
                    friend void render_children(const std::vector<T1>& child_pointer_vector);

            private:
                void bind_to_parent();

                // this method renders this `Holobiont`.
                void render();

                void create_bionts();

                std::size_t get_number_of_children() const override;
                std::size_t get_number_of_descendants() const override;

                std::vector<yli::ontology::Biont*> biont_pointer_vector;
                std::queue<int32_t> free_biontID_queue;
                std::size_t number_of_bionts;

                yli::ontology::Symbiosis* symbiosis_parent; // pointer to `Symbiosis`.

                bool quaternions_in_use;

                bool has_entered;
                bool should_ylikuutio_render_this_holobiont;

                glm::vec3 original_scale_vector;       // original scale vector.
                GLfloat rotate_angle;                  // rotate angle.
                glm::vec3 rotate_vector;               // rotate vector.
                glm::vec3 translate_vector;            // translate vector.
                GLfloat initial_rotate_angle;          // initial rotate angle.
                glm::vec3 initial_rotate_vector;       // initial rotate vector.
        };
    }
}

#endif
