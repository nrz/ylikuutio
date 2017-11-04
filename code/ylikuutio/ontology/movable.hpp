#ifndef __MOVABLE_HPP_INCLUDED
#define __MOVABLE_HPP_INCLUDED

#include "entity.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <memory> // std::make_shared, std::shared_ptr

// `Movable` is a mixin class, not intended to be instantiated.

namespace ontology
{
    class Movable: public ontology::Entity
    {
        public:
            // constructor.
            Movable(ontology::Universe* const universe, std::shared_ptr<glm::vec3> cartesian_coordinates) 
                : Entity(universe)
            {
                // constructor.
                this->cartesian_coordinates = cartesian_coordinates;
                this->spherical_coordinates = nullptr;
            }

            // constructor.
            Movable(ontology::Universe* const universe, std::shared_ptr<SphericalCoordinatesStruct> spherical_coordinates) 
                : Entity(universe)
            {
                // constructor.
                this->cartesian_coordinates = nullptr;
                this->spherical_coordinates = spherical_coordinates;
            }

            // destructor.
            virtual ~Movable();

            // Public callbacks (to be called from AI scripts written in
            // TinyScheme). These are the functions that are available
            // for AI scripts. Ylikuutio will support scripting of game
            // agents using TinyScheme. Ylikuutio does not predefine what
            // kind of games can be done with it. However, the callbacks
            // Ylikuutio provides mean these is more support for features
            // needing such callbacks. In particular, Ylikuutio supports
            // simulations of real-life phenomena.
            // TODO: implement public AI callbacks!

            // Command callbacks.

            // Set target towards which to move.
            static void set_dest(ontology::Movable* const movable, const float x, const float y, const float z);

            // Set target towards which to move.
            static void set_spherical_dest(ontology::Movable* const movable, const float rho, const float theta, const float phi);

            // Get x coordinate of `object`.
            static float get_x(const ontology::Movable* const movable);

            // Get y coordinate of `object`.
            static float get_y(const ontology::Movable* const movable);

            // Get z destination coordinate of `object`.
            static float get_z(const ontology::Movable* const movable);

            // Get rho coordinate of `object`.
            static float get_rho(const ontology::Movable* const movable);

            // Get theta coordinate of `object`.
            static float get_theta(const ontology::Movable* const movable);

            // Get phi destination coordinate of `object`.
            static float get_phi(const ontology::Movable* const movable);

            // Get x destination coordinate of `object`.
            static float get_dest_x(const ontology::Movable* const movable);

            // Get y destination coordinate of `object`.
            static float get_dest_y(const ontology::Movable* const movable);

            // Get z coordinate of `object`.
            static float get_dest_z(const ontology::Movable* const movable);

            // Get rho destination coordinate of `object`.
            static float get_dest_rho(const ontology::Movable* const movable);

            // Get theta destination coordinate of `object`.
            static float get_dest_theta(const ontology::Movable* const movable);

            // Get phi destination destination coordinate of `object`.
            static float get_dest_phi(const ontology::Movable* const movable);

            // Public callbacks end here.

            std::shared_ptr<glm::vec3> cartesian_coordinates;                  // cartesian coordinates.
            std::shared_ptr<SphericalCoordinatesStruct> spherical_coordinates; // spherical coordinates.

            std::shared_ptr<glm::vec3> dest_cartesian_coordinates;                  // cartesian destination coordinates.
            std::shared_ptr<SphericalCoordinatesStruct> dest_spherical_coordinates; // spherical destination coordinates.
    };
}

#endif
