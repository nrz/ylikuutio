#include "movable.hpp"

// Include standard headers
#include <memory> // std::make_shared, std::shared_ptr

namespace ontology
{
    Movable::~Movable()
    {
        // destructor.
    }

    // Public callbacks (to be called from AI scripts written in Chibi-Scheme).

    void Movable::set_dest(ontology::Movable* const movable, const float x, const float y, const float z)
    {
        // Set target towards which to move.
        movable->cartesian_coordinates = std::make_shared<glm::vec3>(x, y, z);
    }

    float Movable::get_x(const ontology::Movable* const movable)
    {
        // Get x coordinate of `movable`.
        return movable->cartesian_coordinates->x;
    }

    float Movable::get_y(const ontology::Movable* const movable)
    {
        // Get y coordinate of `movable`.
        return movable->cartesian_coordinates->y;
    }

    float Movable::get_z(const ontology::Movable* const movable)
    {
        // Get z coordinate of `movable`.
        return movable->cartesian_coordinates->z;
    }

    float Movable::get_dest_x(const ontology::Movable* const movable)
    {
        // Get x destination coordinate of `movable`.
        return movable->dest_cartesian_coordinates->x;
    }

    float Movable::get_dest_y(const ontology::Movable* const movable)
    {
        // Get y destination coordinate of `movable`.
        return movable->dest_cartesian_coordinates->y;
    }

    float Movable::get_dest_z(const ontology::Movable* const movable)
    {
        // Get z destination coordinate of `movable`.
        return movable->dest_cartesian_coordinates->z;
    }

    // Public callbacks end here.
}
