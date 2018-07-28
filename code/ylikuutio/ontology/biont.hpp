#ifndef __BIONT_HPP_INCLUDED
#define __BIONT_HPP_INCLUDED

#include "movable.hpp"
#include "shader.hpp"
#include "symbiont_species.hpp"
#include "biont_struct.hpp"
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
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace ontology
    {
        class Holobiont;

        class Biont: public yli::ontology::Movable
        {
            public:
                // this method sets pointer to this `Biont` to nullptr, sets `parent` according to the input,
                // and requests a new `childID` from the new `Species` or from the new `Glyph`.
                void bind_to_new_parent(yli::ontology::Holobiont* const new_holobiont_parent);

                // constructor.
                Biont(yli::ontology::Universe* const universe, BiontStruct& biont_struct)
                    : Movable(universe, biont_struct.cartesian_coordinates)
                {
                    // constructor.
                    this->holobiont_parent      = biont_struct.holobiont_parent;
                    this->biontID               = biont_struct.biontID;
                    this->original_scale_vector = biont_struct.original_scale_vector;
                    this->rotate_angle          = biont_struct.rotate_angle;
                    this->rotate_vector         = biont_struct.rotate_vector;
                    this->initial_rotate_angle  = biont_struct.initial_rotate_angle;
                    this->initial_rotate_vector = biont_struct.initial_rotate_vector;
                    this->translate_vector      = biont_struct.translate_vector;
                    this->has_entered           = false;

                    // enable rendering of a recently entered Biont.
                    // TODO: enable entering without enabling rendering.
                    this->should_ylikuutio_render_this_biont = true;

                    this->quaternions_in_use    = biont_struct.quaternions_in_use;
                    this->cartesian_coordinates = biont_struct.cartesian_coordinates;
                    this->symbiont_species      = nullptr;         // dummy value.
                    this->model_matrix          = glm::mat4(1.0f); // identity matrix (dummy value).
                    this->MVP_matrix            = glm::mat4(1.0f); // identity matrix (dummy value).

                    // get `childID` from `Holobiont` and set pointer to this `Biont`.
                    this->bind_to_parent();
                    // get `childID` from `SymbiontSpecies` and set pointer to this `Biont`.
                    this->bind_to_symbiont_species();
                    this->type = "yli::ontology::Biont*";
                }

                // destructor.
                virtual ~Biont();

                yli::ontology::Entity* get_parent() const override;

                template<class T1>
                    friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t* number_of_children);
                template<class T1, class T2>
                    friend void yli::hierarchy::bind_child_to_new_parent(T1 child_pointer, T2 new_parent, std::vector<T1>& old_child_pointer_vector, std::queue<std::size_t>& old_free_childID_queue, std::size_t* old_number_of_children);
                template<class T1>
                    friend void render_children(const std::vector<T1>& child_pointer_vector);

            protected:
                void bind_to_parent();
                void bind_to_symbiont_species();

                // this method renders this `Biont`.
                void render();
                void render_this_biont(yli::ontology::Shader* const shader_pointer);

                std::size_t get_number_of_children() const override;
                std::size_t get_number_of_descendants() const override;

                yli::ontology::Holobiont* holobiont_parent; // pointer to `Holobiont`.
                std::size_t biontID;
                bool quaternions_in_use;

                yli::ontology::SymbiontSpecies* symbiont_species; // pointer to `SymbiontSpecies`.

                bool has_entered;
                bool should_ylikuutio_render_this_biont;

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
