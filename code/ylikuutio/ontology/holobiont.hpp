#ifndef __HOLOBIONT_HPP_INCLUDED
#define __HOLOBIONT_HPP_INCLUDED

#include "movable.hpp"
#include "symbiosis.hpp"
#include "holobiont_struct.hpp"
#include "render_templates.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/common/globals.hpp"

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
                void unbind_biont(const std::size_t childID);

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
                    this->rotate_vector         = holobiont_struct.rotate_vector;
                    this->translate_vector      = holobiont_struct.translate_vector;
                    this->initial_rotate_vector = holobiont_struct.initial_rotate_vector;

                    this->number_of_bionts = 0;

                    this->rotate_angle          = holobiont_struct.rotate_angle;
                    this->initial_rotate_angle  = holobiont_struct.initial_rotate_angle;

                    this->should_ylikuutio_render_this_holobiont = true;
                    this->has_entered           = false;
                    this->quaternions_in_use    = holobiont_struct.quaternions_in_use;

                    this->cartesian_coordinates = holobiont_struct.cartesian_coordinates;

                    // get `childID` from `Symbiosis` and set pointer to this `Holobiont`.
                    this->bind_to_parent();

                    this->create_bionts();

                    // `ontology::Entity` member variables begin here.
                    this->type = "yli::ontology::Holobiont*";
                    this->can_be_erased = true;
                }

                // destructor.
                virtual ~Holobiont();

                void update_x(float x);
                void update_y(float y);
                void update_z(float z);

                yli::ontology::Entity* get_parent() const override;

                void set_biont_pointer(const std::size_t childID, yli::ontology::Biont* const child_pointer);

                template<class T1>
                    friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);
                template<class T1>
                    friend std::size_t yli::ontology::get_number_of_descendants(const std::vector<T1>& child_pointer_vector);
                template<class T1>
                    friend void yli::ontology::render_children(const std::vector<T1>& child_pointer_vector);

            private:
                void bind_to_parent();

                // this method renders this `Holobiont`.
                void render();

                void create_bionts();

                std::size_t get_number_of_children() const override;
                std::size_t get_number_of_descendants() const override;

                yli::ontology::Symbiosis* symbiosis_parent; // pointer to `Symbiosis`.

                std::vector<yli::ontology::Biont*> biont_pointer_vector;
                std::queue<std::size_t> free_biontID_queue;

                glm::vec3 original_scale_vector;       // original scale vector.
                glm::vec3 rotate_vector;               // rotate vector.
                glm::vec3 translate_vector;            // translate vector.
                glm::vec3 initial_rotate_vector;       // initial rotate vector.

                std::size_t number_of_bionts;

                float rotate_angle;                    // rotate angle.
                float initial_rotate_angle;            // initial rotate angle.

                bool should_ylikuutio_render_this_holobiont;
                bool has_entered;
                bool quaternions_in_use;
        };
    }
}

#endif
