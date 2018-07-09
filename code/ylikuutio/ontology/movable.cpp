#include "movable.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// `Movable` is a mixin class, not intended to be instantiated.

namespace yli
{
    namespace ontology
    {
        Movable::~Movable()
        {
            // destructor.
        }

        glm::vec3& Movable::get_cartesian_coordinates()
        {
            return this->cartesian_coordinates;
        }

        // Public callbacks (to be called from AI scripts written in Chibi-Scheme).

        void Movable::set_dest(yli::ontology::Movable* const movable, const float x, const float y, const float z)
        {
            // Set target towards which to move.
            movable->cartesian_coordinates = glm::vec3(x, y, z);
        }

        float Movable::get_x(const yli::ontology::Movable* const movable)
        {
            // Get x coordinate of `movable`.
            return movable->cartesian_coordinates.x;
        }

        float Movable::get_y(const yli::ontology::Movable* const movable)
        {
            // Get y coordinate of `movable`.
            return movable->cartesian_coordinates.y;
        }

        float Movable::get_z(const yli::ontology::Movable* const movable)
        {
            // Get z coordinate of `movable`.
            return movable->cartesian_coordinates.z;
        }

        float Movable::get_dest_x(const yli::ontology::Movable* const movable)
        {
            // Get x destination coordinate of `movable`.
            return movable->dest_cartesian_coordinates.x;
        }

        float Movable::get_dest_y(const yli::ontology::Movable* const movable)
        {
            // Get y destination coordinate of `movable`.
            return movable->dest_cartesian_coordinates.y;
        }

        float Movable::get_dest_z(const yli::ontology::Movable* const movable)
        {
            // Get z destination coordinate of `movable`.
            return movable->dest_cartesian_coordinates.z;
        }

        // Public callbacks end here.
    }
}
