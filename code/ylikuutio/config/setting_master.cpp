#include "setting_master.hpp"
#include "setting.hpp"
#include "code/ylikuutio/console/console.hpp"
#include "code/ylikuutio/ontology/entity.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"
#include "code/ylikuutio/common/any_value.hpp"

// Include standard headers
#include <iostream>      // std::cout, std::cin, std::cerr
#include <memory>        // std::make_shared, std::shared_ptr
#include <string>        // std::string
#include <vector>        // std::vector
#include <unordered_map> // std::unordered_map

namespace ontology
{
    class Entity;
}

namespace config
{
    SettingMaster::SettingMaster(ontology::Entity* const entity)
    {
        // costructor.
        this->parent = entity;
        this->number_of_settings = 0;

        // bind to parent.
        // there can be only 1 `SettingMaster`.
        this->parent->setting_master = this;
    }

    SettingMaster::~SettingMaster()
    {
        // destructor.
    }

    bool SettingMaster::is_setting(const std::string& setting_name)
    {
        std::cout << "Checking if " << setting_name << " is a Setting.\n";
        bool is_setting = (this->setting_pointer_map.count(setting_name) == 1);
        std::cout << "Returning from SettingMaster::is_setting\n";
        return is_setting;
    }

    std::string SettingMaster::help()
    {
        std::string help_string = "TODO: create general helptext";
        return help_string;
    }

    std::string SettingMaster::help(const std::string& setting_name)
    {
        if (this->is_setting(setting_name))
        {
            config::Setting* setting = this->setting_pointer_map[setting_name];

            if (setting != nullptr)
            {
                return setting->help();
            }
        }
        return this->help();
    }

    bool SettingMaster::set(std::string& setting_name, std::shared_ptr<datatypes::AnyValue> setting_new_any_value)
    {
        if (!this->is_setting(setting_name))
        {
            return false;
        }

        // OK, this is a valid variable name.
        // Set the variable value and activate it by
        // calling the corresponding activate callback.
        config::Setting* setting = this->setting_pointer_map[setting_name];

        // create empty `AnyValue` (there is no suitable constructor yet).
        setting_new_any_value->type = setting->setting_value->type;

        setting->setting_value = setting_new_any_value;
        setting->activate_callback(this->parent, this);
        return true;
    }

    config::Setting* SettingMaster::get(std::string& setting_name)
    {
        return this->setting_pointer_map[setting_name];
    }

    // public callbacks.

    std::shared_ptr<datatypes::AnyValue> SettingMaster::set_and_print(
            console::Console* const console,
            ontology::Entity* const entity,
            std::vector<std::string>& command_parameters)
    {
        // Usage:
        // to get variable names: set
        // to get valid values:   set <variable>
        // to set variable:       set <variable> value[s]

        config::SettingMaster* setting_master = entity->setting_master;

        if (command_parameters.size() == 0)
        {
            // No command parameters.
            // Print variable names.
            console->print_text(setting_master->help());
        }
        else if (command_parameters.size() == 1)
        {
            std::string setting_name = command_parameters.at(0);

            // One (1) command parameter.
            // Print current value of the given variable.
            if (setting_master->is_setting(setting_name))
            {
                config::Setting* setting = setting_master->get(setting_name);

                if (setting != nullptr && setting->setting_value != nullptr && setting->read_callback == nullptr)
                {
                    // Print variable value.
                    console->print_text(setting->setting_value->get_string());
                }
                else if (setting != nullptr && setting->setting_value != nullptr)
                {
                    console->print_text(setting->read_callback(entity, setting_master)->get_string());
                }
                else
                {
                    // Invalid variable name.
                    console->print_text("invalid variable name");
                    console->print_text(setting_master->help());
                }
            }
            else
            {
                // Invalid variable name.
                console->print_text("invalid variable name");
                console->print_text(setting_master->help());
            }
        }
        else
        {
            std::string setting_name = command_parameters.at(0);

            // At least 2 variables.
            // Check the validity of the variable name.
            if (setting_master->is_setting(setting_name))
            {
                // OK, this is a valid variable name.
                // Set the variable value and activate it by
                // calling the corresponding activate callback.
                config::Setting* setting = setting_master->setting_pointer_map[setting_name];

                // create empty `AnyValue` (there is no suitable constructor yet).
                std::shared_ptr<datatypes::AnyValue> setting_any_value = std::make_shared<datatypes::AnyValue>();
                setting_any_value->type = setting->setting_value->type;

                // set a new value.
                bool success = setting_any_value->set_value(command_parameters.at(1));

                if (success)
                {
                    setting->setting_value = setting_any_value;

                    if (setting->activate_callback != nullptr)
                    {
                        setting->activate_callback(entity, setting_master);
                    }
                }
            }
            else
            {
                console->print_text(setting_master->help());
            }
        }

        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> SettingMaster::get_and_print(
            console::Console* const console,
            ontology::Entity* const entity,
            std::vector<std::string>& command_parameters)
    {
        // Usage:
        // to get variable names: get
        // to get variable value: get <variable>
        config::SettingMaster* setting_master = entity->setting_master;

        if (command_parameters.size() == 0)
        {
            // No command parameters.
            // Print variable names.
            console->print_text(setting_master->help());
        }
        else if (command_parameters.size() == 1)
        {
            std::string setting_name = command_parameters.at(0);

            // One (1) command parameter.
            // Print valid values of the given variable.
            if (setting_master->is_setting(setting_name))
            {
                config::Setting* setting = setting_master->get(setting_name);

                if (setting != nullptr && setting->setting_value != nullptr && setting->read_callback == nullptr)
                {
                    // Print variable value.
                    console->print_text(setting->setting_value->get_string());
                }
                else if (setting != nullptr && setting->setting_value != nullptr)
                {
                    console->print_text(setting->read_callback(entity, setting_master)->get_string());
                }
                else
                {
                    // Invalid variable name.
                    console->print_text("invalid variable name");
                    console->print_text(setting_master->help());
                }
            }
            else
            {
                // Invalid variable name.
                console->print_text("invalid variable name");
                console->print_text(setting_master->help());
            }
        }
        else
        {
            // More than 1 command parameter.
            // Print variable names.
            console->print_text(setting_master->help());
        }

        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> SettingMaster::activate_planet_radius(ontology::Entity* const entity, config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        if (setting_master->setting_pointer_map.count("planet_radius") != 1)
        {
            return nullptr;
        }

        std::shared_ptr<datatypes::AnyValue> planet_radius_any_value = std::make_shared<datatypes::AnyValue>(*setting_master->setting_pointer_map["planet_radius"]->setting_value);

        if (planet_radius_any_value == nullptr || planet_radius_any_value->type != datatypes::FLOAT)
        {
            return nullptr;
        }

        ontology::Universe* universe = dynamic_cast<ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        universe->set_planet_radius(planet_radius_any_value->float_value);
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> SettingMaster::activate_background_color(ontology::Entity* const entity, config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        if (setting_master->setting_pointer_map.count("red") != 1 ||
                setting_master->setting_pointer_map.count("green") != 1 ||
                setting_master->setting_pointer_map.count("blue") != 1 ||
                setting_master->setting_pointer_map.count("alpha") != 1)
        {
            return nullptr;
        }

        // red.
        std::shared_ptr<datatypes::AnyValue> red_any_value = std::make_shared<datatypes::AnyValue>(*setting_master->setting_pointer_map["red"]->setting_value);

        if (red_any_value == nullptr || red_any_value->type != datatypes::FLOAT)
        {
            return nullptr;
        }

        GLclampf red = static_cast<GLclampf>(red_any_value->float_value);

        // green.
        std::shared_ptr<datatypes::AnyValue> green_any_value = std::make_shared<datatypes::AnyValue>(*setting_master->setting_pointer_map["green"]->setting_value);

        if (green_any_value == nullptr || green_any_value->type != datatypes::FLOAT)
        {
            return nullptr;
        }

        GLclampf green = static_cast<GLclampf>(green_any_value->float_value);

        // blue.
        std::shared_ptr<datatypes::AnyValue> blue_any_value = std::make_shared<datatypes::AnyValue>(*setting_master->setting_pointer_map["blue"]->setting_value);

        if (blue_any_value == nullptr || blue_any_value->type != datatypes::FLOAT)
        {
            return nullptr;
        }

        GLclampf blue = static_cast<GLclampf>(blue_any_value->float_value);

        // alpha.
        std::shared_ptr<datatypes::AnyValue> alpha_any_value = std::make_shared<datatypes::AnyValue>(*setting_master->setting_pointer_map["alpha"]->setting_value);

        if (alpha_any_value == nullptr || alpha_any_value->type != datatypes::FLOAT)
        {
            return nullptr;
        }

        GLclampf alpha = static_cast<GLclampf>(alpha_any_value->float_value);

        ylikuutio::opengl::set_background_color(red, green, blue, alpha);
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> SettingMaster::activate_wireframe(ontology::Entity* const entity, config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        if (setting_master->setting_pointer_map.count("wireframe") != 1)
        {
            return nullptr;
        }

        std::shared_ptr<datatypes::AnyValue> wireframe_any_value = std::make_shared<datatypes::AnyValue>(*setting_master->setting_pointer_map["wireframe"]->setting_value);

        if (wireframe_any_value == nullptr || wireframe_any_value->type != datatypes::BOOL)
        {
            return nullptr;
        }

        ylikuutio::opengl::set_wireframe(wireframe_any_value->bool_value);
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> SettingMaster::activate_spherical_coordinates(ontology::Entity* const entity, config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        if (setting_master->setting_pointer_map.count("spherical_coordinates") != 1)
        {
            return nullptr;
        }

        std::shared_ptr<datatypes::AnyValue> spherical_coordinates_any_value = std::make_shared<datatypes::AnyValue>(*setting_master->setting_pointer_map["spherical_coordinates"]->setting_value);

        if (spherical_coordinates_any_value == nullptr || spherical_coordinates_any_value->type != datatypes::SPHERICAL_COORDINATES_STRUCT_POINTER)
        {
            return nullptr;
        }

        ontology::Universe* universe = dynamic_cast<ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        delete universe->spherical_coordinates; // delete the old `SphericalCoordinatesStruct`.
        universe->spherical_coordinates = spherical_coordinates_any_value->spherical_coordinates_struct_pointer;
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> SettingMaster::activate_rho(ontology::Entity* const entity, config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        ontology::Universe* universe = dynamic_cast<ontology::Universe*>(entity);

        if (universe == nullptr || universe->spherical_coordinates == nullptr)
        {
            return nullptr;
        }

        if (setting_master->setting_pointer_map.count("spherical_coordinates") != 1)
        {
            return nullptr;
        }

        std::shared_ptr<datatypes::AnyValue> rho_any_value = std::make_shared<datatypes::AnyValue>(*setting_master->setting_pointer_map["rho"]->setting_value);

        if (rho_any_value == nullptr || rho_any_value->type != datatypes::FLOAT)
        {
            return nullptr;
        }

        universe->spherical_coordinates->rho = rho_any_value->float_value;
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> SettingMaster::activate_theta(ontology::Entity* const entity, config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        ontology::Universe* universe = dynamic_cast<ontology::Universe*>(entity);

        if (universe == nullptr || universe->spherical_coordinates == nullptr)
        {
            return nullptr;
        }

        if (setting_master->setting_pointer_map.count("spherical_coordinates") != 1)
        {
            return nullptr;
        }

        std::shared_ptr<datatypes::AnyValue> theta_any_value = std::make_shared<datatypes::AnyValue>(*setting_master->setting_pointer_map["theta"]->setting_value);

        if (theta_any_value == nullptr || theta_any_value->type != datatypes::FLOAT)
        {
            return nullptr;
        }

        universe->spherical_coordinates->theta = theta_any_value->float_value;
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> SettingMaster::activate_phi(ontology::Entity* const entity, config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        ontology::Universe* universe = dynamic_cast<ontology::Universe*>(entity);

        if (universe == nullptr || universe->spherical_coordinates == nullptr)
        {
            return nullptr;
        }

        if (setting_master->setting_pointer_map.count("spherical_coordinates") != 1)
        {
            return nullptr;
        }

        std::shared_ptr<datatypes::AnyValue> phi_any_value = std::make_shared<datatypes::AnyValue>(*setting_master->setting_pointer_map["phi"]->setting_value);

        if (phi_any_value == nullptr || phi_any_value->type != datatypes::FLOAT)
        {
            return nullptr;
        }

        universe->spherical_coordinates->phi = phi_any_value->float_value;
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> SettingMaster::activate_cartesian_coordinates(ontology::Entity* const entity, config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        ontology::Universe* universe = dynamic_cast<ontology::Universe*>(entity);

        if (universe == nullptr || setting_master->setting_pointer_map.count("cartesian_coordinates") != 1)
        {
            return nullptr;
        }

        std::shared_ptr<datatypes::AnyValue> cartesian_coordinates_any_value = std::make_shared<datatypes::AnyValue>(*setting_master->setting_pointer_map["cartesian_coordinates"]->setting_value);

        if (cartesian_coordinates_any_value == nullptr || cartesian_coordinates_any_value->type != datatypes::GLM_VEC3_POINTER)
        {
            return nullptr;
        }

        delete universe->cartesian_coordinates; // delete the old `glm::vec3`.
        universe->cartesian_coordinates = cartesian_coordinates_any_value->glm_vec3_pointer;
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> SettingMaster::activate_x(ontology::Entity* const entity, config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        ontology::Universe* universe = dynamic_cast<ontology::Universe*>(entity);

        if (universe == nullptr || universe->cartesian_coordinates == nullptr)
        {
            return nullptr;
        }

        if (setting_master->setting_pointer_map.count("x") != 1)
        {
            return nullptr;
        }

        std::shared_ptr<datatypes::AnyValue> x_any_value = std::make_shared<datatypes::AnyValue>(*setting_master->setting_pointer_map["x"]->setting_value);

        if (x_any_value == nullptr || x_any_value->type != datatypes::FLOAT)
        {
            return nullptr;
        }

        universe->cartesian_coordinates->x = x_any_value->float_value;
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> SettingMaster::activate_y(ontology::Entity* const entity, config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        ontology::Universe* universe = dynamic_cast<ontology::Universe*>(entity);

        if (universe == nullptr || universe->cartesian_coordinates == nullptr)
        {
            return nullptr;
        }

        if (setting_master->setting_pointer_map.count("y") != 1)
        {
            return nullptr;
        }

        std::shared_ptr<datatypes::AnyValue> y_any_value = std::make_shared<datatypes::AnyValue>(*setting_master->setting_pointer_map["y"]->setting_value);

        if (y_any_value == nullptr || y_any_value->type != datatypes::FLOAT)
        {
            return nullptr;
        }

        universe->cartesian_coordinates->y = y_any_value->float_value;
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> SettingMaster::activate_z(ontology::Entity* const entity, config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        ontology::Universe* universe = dynamic_cast<ontology::Universe*>(entity);

        if (universe == nullptr || universe->cartesian_coordinates == nullptr)
        {
            return nullptr;
        }

        if (setting_master->setting_pointer_map.count("z") != 1)
        {
            return nullptr;
        }

        std::shared_ptr<datatypes::AnyValue> z_any_value = std::make_shared<datatypes::AnyValue>(*setting_master->setting_pointer_map["z"]->setting_value);

        if (z_any_value == nullptr || z_any_value->type != datatypes::FLOAT)
        {
            return nullptr;
        }

        universe->cartesian_coordinates->z = z_any_value->float_value;
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> SettingMaster::activate_horizontal_angle(ontology::Entity* const entity, config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        ontology::Universe* universe = dynamic_cast<ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        if (setting_master->setting_pointer_map.count("horizontal_angle") != 1)
        {
            return nullptr;
        }

        std::shared_ptr<datatypes::AnyValue> horizontal_angle_any_value = std::make_shared<datatypes::AnyValue>(*setting_master->setting_pointer_map["horizontal_angle"]->setting_value);

        if (horizontal_angle_any_value == nullptr || horizontal_angle_any_value->type != datatypes::DOUBLE)
        {
            return nullptr;
        }

        universe->horizontal_angle = horizontal_angle_any_value->double_value;
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> SettingMaster::activate_vertical_angle(ontology::Entity* const entity, config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        ontology::Universe* universe = dynamic_cast<ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        if (setting_master->setting_pointer_map.count("vertical_angle") != 1)
        {
            return nullptr;
        }

        std::shared_ptr<datatypes::AnyValue> vertical_angle_any_value = std::make_shared<datatypes::AnyValue>(*setting_master->setting_pointer_map["vertical_angle"]->setting_value);

        if (vertical_angle_any_value == nullptr || vertical_angle_any_value->type != datatypes::DOUBLE)
        {
            return nullptr;
        }

        universe->vertical_angle = vertical_angle_any_value->double_value;
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> SettingMaster::activate_speed(ontology::Entity* const entity, config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        ontology::Universe* universe = dynamic_cast<ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        if (setting_master->setting_pointer_map.count("speed") != 1)
        {
            return nullptr;
        }

        std::shared_ptr<datatypes::AnyValue> speed_any_value = std::make_shared<datatypes::AnyValue>(*setting_master->setting_pointer_map["speed"]->setting_value);

        if (speed_any_value == nullptr || speed_any_value->type != datatypes::FLOAT)
        {
            return nullptr;
        }

        universe->speed = speed_any_value->float_value;
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> SettingMaster::activate_turbo_factor(ontology::Entity* const entity, config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        ontology::Universe* universe = dynamic_cast<ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        if (setting_master->setting_pointer_map.count("turbo_factor") != 1)
        {
            return nullptr;
        }

        std::shared_ptr<datatypes::AnyValue> turbo_factor_any_value = std::make_shared<datatypes::AnyValue>(*setting_master->setting_pointer_map["turbo_factor"]->setting_value);

        if (turbo_factor_any_value == nullptr || turbo_factor_any_value->type != datatypes::FLOAT)
        {
            return nullptr;
        }

        universe->turbo_factor = turbo_factor_any_value->float_value;
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> SettingMaster::activate_twin_turbo_factor(ontology::Entity* const entity, config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        ontology::Universe* universe = dynamic_cast<ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        if (setting_master->setting_pointer_map.count("twin_turbo_factor") != 1)
        {
            return nullptr;
        }

        std::shared_ptr<datatypes::AnyValue> twin_turbo_factor_any_value = std::make_shared<datatypes::AnyValue>(*setting_master->setting_pointer_map["twin_turbo_factor"]->setting_value);

        if (twin_turbo_factor_any_value == nullptr || twin_turbo_factor_any_value->type != datatypes::FLOAT)
        {
            return nullptr;
        }

        universe->twin_turbo_factor = twin_turbo_factor_any_value->float_value;
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> SettingMaster::activate_mouse_speed(ontology::Entity* const entity, config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        ontology::Universe* universe = dynamic_cast<ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        if (setting_master->setting_pointer_map.count("mouse_speed") != 1)
        {
            return nullptr;
        }

        std::shared_ptr<datatypes::AnyValue> mouse_speed_any_value = std::make_shared<datatypes::AnyValue>(*setting_master->setting_pointer_map["mouse_speed"]->setting_value);

        if (mouse_speed_any_value == nullptr || mouse_speed_any_value->type != datatypes::FLOAT)
        {
            return nullptr;
        }

        universe->mouse_speed = mouse_speed_any_value->float_value;
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> SettingMaster::activate_is_flight_mode_in_use(ontology::Entity* const entity, config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        ontology::Universe* universe = dynamic_cast<ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        if (setting_master->setting_pointer_map.count("is_flight_mode_in_use") != 1)
        {
            return nullptr;
        }

        std::shared_ptr<datatypes::AnyValue> is_flight_mode_in_use_any_value = std::make_shared<datatypes::AnyValue>(*setting_master->setting_pointer_map["is_flight_mode_in_use"]->setting_value);

        if (is_flight_mode_in_use_any_value == nullptr || is_flight_mode_in_use_any_value->type != datatypes::BOOL)
        {
            return nullptr;
        }

        universe->is_flight_mode_in_use = is_flight_mode_in_use_any_value->bool_value;
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> SettingMaster::read_x(ontology::Entity* const entity, config::SettingMaster* const setting_master)
    {
        if (entity == nullptr)
        {
            return nullptr;
        }

        ontology::Universe* universe = dynamic_cast<ontology::Universe*>(entity);

        if (universe == nullptr || universe->cartesian_coordinates == nullptr)
        {
            return nullptr;
        }

        return std::make_shared<datatypes::AnyValue>(universe->cartesian_coordinates->x);
    }

    std::shared_ptr<datatypes::AnyValue> SettingMaster::read_y(ontology::Entity* const entity, config::SettingMaster* const setting_master)
    {
        if (entity == nullptr)
        {
            return nullptr;
        }

        ontology::Universe* universe = dynamic_cast<ontology::Universe*>(entity);

        if (universe == nullptr || universe->cartesian_coordinates == nullptr)
        {
            return nullptr;
        }

        return std::make_shared<datatypes::AnyValue>(universe->cartesian_coordinates->y);
    }

    std::shared_ptr<datatypes::AnyValue> SettingMaster::read_z(ontology::Entity* const entity, config::SettingMaster* const setting_master)
    {
        if (entity == nullptr)
        {
            return nullptr;
        }

        ontology::Universe* universe = dynamic_cast<ontology::Universe*>(entity);

        if (universe == nullptr || universe->cartesian_coordinates == nullptr)
        {
            return nullptr;
        }

        return std::make_shared<datatypes::AnyValue>(universe->cartesian_coordinates->z);
    }

    std::shared_ptr<datatypes::AnyValue> SettingMaster::read_rho(ontology::Entity* const entity, config::SettingMaster* const setting_master)
    {
        if (entity == nullptr)
        {
            return nullptr;
        }

        ontology::Universe* universe = dynamic_cast<ontology::Universe*>(entity);

        if (universe == nullptr || universe->spherical_coordinates == nullptr)
        {
            return nullptr;
        }

        return std::make_shared<datatypes::AnyValue>(universe->spherical_coordinates->rho);
    }

    std::shared_ptr<datatypes::AnyValue> SettingMaster::read_theta(ontology::Entity* const entity, config::SettingMaster* const setting_master)
    {
        if (entity == nullptr)
        {
            return nullptr;
        }

        ontology::Universe* universe = dynamic_cast<ontology::Universe*>(entity);

        if (universe == nullptr || universe->spherical_coordinates == nullptr)
        {
            return nullptr;
        }

        return std::make_shared<datatypes::AnyValue>(universe->spherical_coordinates->theta);
    }

    std::shared_ptr<datatypes::AnyValue> SettingMaster::read_phi(ontology::Entity* const entity, config::SettingMaster* const setting_master)
    {
        if (entity == nullptr)
        {
            return nullptr;
        }

        ontology::Universe* universe = dynamic_cast<ontology::Universe*>(entity);

        if (universe == nullptr || universe->spherical_coordinates == nullptr)
        {
            return nullptr;
        }

        return std::make_shared<datatypes::AnyValue>(universe->spherical_coordinates->phi);
    }

    std::shared_ptr<datatypes::AnyValue> SettingMaster::read_up(ontology::Entity* const entity, config::SettingMaster* const setting_master)
    {
        if (entity == nullptr)
        {
            return nullptr;
        }

        ontology::Universe* universe = dynamic_cast<ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        return std::make_shared<datatypes::AnyValue>(&universe->up);
    }

    std::shared_ptr<datatypes::AnyValue> SettingMaster::read_right(ontology::Entity* const entity, config::SettingMaster* const setting_master)
    {
        if (entity == nullptr)
        {
            return nullptr;
        }

        ontology::Universe* universe = dynamic_cast<ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        return std::make_shared<datatypes::AnyValue>(&universe->right);
    }

    std::shared_ptr<datatypes::AnyValue> SettingMaster::read_horizontal_angle(ontology::Entity* const entity, config::SettingMaster* const setting_master)
    {
        if (entity == nullptr)
        {
            return nullptr;
        }

        ontology::Universe* universe = dynamic_cast<ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        return std::make_shared<datatypes::AnyValue>(universe->horizontal_angle);
    }

    std::shared_ptr<datatypes::AnyValue> SettingMaster::read_vertical_angle(ontology::Entity* const entity, config::SettingMaster* const setting_master)
    {
        if (entity == nullptr)
        {
            return nullptr;
        }

        ontology::Universe* universe = dynamic_cast<ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        return std::make_shared<datatypes::AnyValue>(universe->vertical_angle);
    }

    std::shared_ptr<datatypes::AnyValue> SettingMaster::read_is_flight_mode_in_use(ontology::Entity* const entity, config::SettingMaster* const setting_master)
    {
        if (entity == nullptr)
        {
            return nullptr;
        }

        ontology::Universe* universe = dynamic_cast<ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        return std::make_shared<datatypes::AnyValue>(universe->is_flight_mode_in_use);
    }
}
