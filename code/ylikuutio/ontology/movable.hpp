#ifndef __MOVABLE_HPP_INCLUDED
#define __MOVABLE_HPP_INCLUDED

#include "entity.hpp"
#include "code/ylikuutio/common/spherical_coordinates_struct.hpp"
#include "code/ylikuutio/config/setting.hpp"
#include "code/ylikuutio/config/setting_master.hpp"
#include "code/ylikuutio/config/setting_struct.hpp"
#include "code/ylikuutio/common/any_value.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>  // NAN, std::isnan, std::pow
#include <memory> // std::make_shared, std::shared_ptr

// `Movable` is a mixin class, not intended to be instantiated.

namespace yli
{
    namespace ontology
    {
        class Universe;

        class Movable: public yli::ontology::Entity
        {
            public:
                // constructor.
                Movable(yli::ontology::Universe* const universe, const glm::vec3& cartesian_coordinates)
                    : Entity(universe)
                {
                    // constructor.
                    this->cartesian_coordinates.x     = cartesian_coordinates.x;
                    this->cartesian_coordinates.y     = cartesian_coordinates.y;
                    this->cartesian_coordinates.z     = cartesian_coordinates.z;
                    this->spherical_coordinates.rho   = NAN;
                    this->spherical_coordinates.theta = NAN;
                    this->spherical_coordinates.phi   = NAN;
                    this->horizontal_angle            = 0.0f;
                    this->vertical_angle              = 0.0f;

                    this->model_matrix                = glm::mat4(1.0f); // identity matrix (dummy value).
                    this->MVP_matrix                  = glm::mat4(1.0f); // identity matrix (dummy value).

                    float float_x                     = cartesian_coordinates.x;
                    float float_y                     = cartesian_coordinates.y;
                    float float_z                     = cartesian_coordinates.z;

                    SettingStruct cartesian_coordinates_setting_struct(std::make_shared<yli::datatypes::AnyValue>(new glm::vec3(float_x, float_y, float_z)));
                    cartesian_coordinates_setting_struct.name = "cartesian_coordinates";
                    cartesian_coordinates_setting_struct.setting_master = this->get_setting_master();
                    cartesian_coordinates_setting_struct.activate_callback = &yli::config::SettingMaster::activate_cartesian_coordinates;
                    cartesian_coordinates_setting_struct.read_callback = &yli::config::SettingMaster::read_cartesian_coordinates;
                    cartesian_coordinates_setting_struct.should_ylikuutio_call_activate_callback_now = true;
                    std::cout << "Executing `new yli::config::Setting(cartesian_coordinates_setting_struct);` ...\n";
                    new yli::config::Setting(cartesian_coordinates_setting_struct);

                    SettingStruct x_setting_struct(std::make_shared<yli::datatypes::AnyValue>(float_x));
                    x_setting_struct.name = "x";
                    x_setting_struct.setting_master = this->get_setting_master();
                    x_setting_struct.activate_callback = &yli::config::SettingMaster::activate_x;
                    x_setting_struct.read_callback = &yli::config::SettingMaster::read_x;
                    x_setting_struct.should_ylikuutio_call_activate_callback_now = true;
                    std::cout << "Executing `new yli::config::Setting(x_setting_struct);` ...\n";
                    new yli::config::Setting(x_setting_struct);

                    SettingStruct y_setting_struct(std::make_shared<yli::datatypes::AnyValue>(float_y));
                    y_setting_struct.name = "y";
                    y_setting_struct.setting_master = this->get_setting_master();
                    y_setting_struct.activate_callback = &yli::config::SettingMaster::activate_y;
                    y_setting_struct.read_callback = &yli::config::SettingMaster::read_y;
                    y_setting_struct.should_ylikuutio_call_activate_callback_now = true;
                    std::cout << "Executing `new yli::config::Setting(y_setting_struct);` ...\n";
                    new yli::config::Setting(y_setting_struct);

                    SettingStruct z_setting_struct(std::make_shared<yli::datatypes::AnyValue>(float_z));
                    z_setting_struct.name = "z";
                    z_setting_struct.setting_master = this->get_setting_master();
                    z_setting_struct.activate_callback = &yli::config::SettingMaster::activate_z;
                    z_setting_struct.read_callback = &yli::config::SettingMaster::read_z;
                    z_setting_struct.should_ylikuutio_call_activate_callback_now = true;
                    std::cout << "Executing `new yli::config::Setting(z_setting_struct);` ...\n";
                    new yli::config::Setting(z_setting_struct);

                    // `yli::ontology::Entity` member variables begin here.
                    this->type_string = "yli::ontology::Movable*";
                    this->can_be_erased = true;
                }

                // constructor.
                Movable(yli::ontology::Universe* const universe, const SphericalCoordinatesStruct& spherical_coordinates)
                    : Entity(universe)
                {
                    // constructor.
                    this->cartesian_coordinates = glm::vec3(NAN, NAN, NAN);
                    this->spherical_coordinates = spherical_coordinates;
                }

                Movable(const Movable&) = delete;            // Delete copy constructor.
                Movable &operator=(const Movable&) = delete; // Delete copy assignment.

                // destructor.
                virtual ~Movable();

                const glm::vec3& get_cartesian_coordinates();

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
                static void set_dest(yli::ontology::Movable* const movable, const float x, const float y, const float z);

                // Set target towards which to move.
                static void set_spherical_dest(yli::ontology::Movable* const movable, const float rho, const float theta, const float phi);

                // Get x coordinate of `object`.
                static float get_x(const yli::ontology::Movable* const movable);

                // Get y coordinate of `object`.
                static float get_y(const yli::ontology::Movable* const movable);

                // Get z destination coordinate of `object`.
                static float get_z(const yli::ontology::Movable* const movable);

                // Get rho coordinate of `object`.
                static float get_rho(const yli::ontology::Movable* const movable);

                // Get theta coordinate of `object`.
                static float get_theta(const yli::ontology::Movable* const movable);

                // Get phi destination coordinate of `object`.
                static float get_phi(const yli::ontology::Movable* const movable);

                // Get x destination coordinate of `object`.
                static float get_dest_x(const yli::ontology::Movable* const movable);

                // Get y destination coordinate of `object`.
                static float get_dest_y(const yli::ontology::Movable* const movable);

                // Get z coordinate of `object`.
                static float get_dest_z(const yli::ontology::Movable* const movable);

                // Get rho destination coordinate of `object`.
                static float get_dest_rho(const yli::ontology::Movable* const movable);

                // Get theta destination coordinate of `object`.
                static float get_dest_theta(const yli::ontology::Movable* const movable);

                // Get phi destination destination coordinate of `object`.
                static float get_dest_phi(const yli::ontology::Movable* const movable);

                // Public callbacks end here.

                // `cartesian_coordinates` can be accessed as a vector or as single coordinates `x`, `y`, `z`.
                glm::vec3 cartesian_coordinates;                       // cartesian coordinates.

                // `spherical_coordinates` can be accessed as a vector or as single coordinates `rho`, `theta`, `phi`.
                SphericalCoordinatesStruct spherical_coordinates;      // spherical coordinates.

                glm::vec3 dest_cartesian_coordinates;                  // cartesian destination coordinates.
                SphericalCoordinatesStruct dest_spherical_coordinates; // spherical destination coordinates.

                // `direction` can be accessed as a vector or as single coordinates `pitch`, `roll`, `yaw`.
                glm::vec3 direction;

                glm::vec3 right;                                       // note: can not be set directly using console.
                glm::vec3 up;                                          // note: can not be set directly using console.

                double horizontal_angle;
                double vertical_angle;

                // The rest fields are created in the constructor.
                glm::mat4 model_matrix;                                // model matrix.
                glm::mat4 MVP_matrix;                                  // model view projection matrix.
        };
    }
}

#endif
