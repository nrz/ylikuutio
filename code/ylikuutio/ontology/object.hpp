#ifndef __OBJECT_HPP_INCLUDED
#define __OBJECT_HPP_INCLUDED

#include "entity.hpp"
#include "movable.hpp"
#include "shader.hpp"
#include "species.hpp"
#include "text3D.hpp"
#include "glyph.hpp"
#include "object_struct.hpp"
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
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace ontology
    {
        class Species;
        class Glyph;

        class Object: public yli::ontology::Movable
        {
            public:
                // this method sets pointer to this `Object` to nullptr, sets `parent` according to the input,
                // and requests a new `childID` from the new `Species` or from the new `Glyph`.
                void bind_to_new_parent(void* const new_parent);

                // constructor.
                Object(yli::ontology::Universe* const universe, ObjectStruct& object_struct)
                    : Movable(universe, object_struct.cartesian_coordinates)
                {
                    // constructor.
                    this->original_scale_vector = object_struct.original_scale_vector;
                    this->rotate_angle          = object_struct.rotate_angle;
                    this->rotate_vector         = object_struct.rotate_vector;
                    this->initial_rotate_angle  = object_struct.initial_rotate_angle;
                    this->initial_rotate_vector = object_struct.initial_rotate_vector;
                    this->translate_vector      = object_struct.translate_vector;
                    this->has_entered           = false;

                    // enable rendering of a recently entered Object.
                    // TODO: enable entering without enabling rendering.
                    this->should_ylikuutio_render_this_object = true;

                    this->is_character          = object_struct.is_character;
                    this->quaternions_in_use    = object_struct.quaternions_in_use;

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
                    this->type = "yli::ontology::Object*";
                }

                // destructor.
                virtual ~Object();

                yli::ontology::Entity* get_parent() const override;

                template<class T1>
                    friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<int32_t>& free_childID_queue, int32_t* number_of_children);
                template<class T1, class T2>
                    friend void hierarchy::bind_child_to_new_parent(T1 child_pointer, T2 new_parent, std::vector<T1>& old_child_pointer_vector, std::queue<int32_t>& old_free_childID_queue, int32_t* old_number_of_children);
                template<class T1>
                    friend void render_children(const std::vector<T1>& child_pointer_vector);

            private:
                void bind_to_parent();

                // this method renders this `Object`.
                void render();
                void render_this_object(yli::ontology::Shader* const shader_pointer);

                int32_t get_number_of_children() const override;
                int32_t get_number_of_descendants() const override;

                yli::ontology::Species* species_parent; // pointer to `Species`.
                yli::ontology::Glyph* glyph_parent;     // pointer to `Glyph`.
                yli::ontology::Text3D* text3D_parent;   // pointer to `Text3D`.
                bool is_character;
                bool quaternions_in_use;

                bool has_entered;
                bool should_ylikuutio_render_this_object;

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
