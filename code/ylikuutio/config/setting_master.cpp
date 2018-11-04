#include "setting_master.hpp"
#include "setting.hpp"
#include "code/ylikuutio/console/console.hpp"
#include "code/ylikuutio/ontology/entity.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/holobiont.hpp"
#include "code/ylikuutio/ontology/movable.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"
#include "code/ylikuutio/common/any_value.hpp"

// Include standard headers
#include <iostream>      // std::cout, std::cin, std::cerr
#include <memory>        // std::make_shared, std::shared_ptr
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

namespace yli
{
    namespace ontology
    {
        class Entity;
    }

    namespace config
    {
        SettingMaster::SettingMaster(yli::ontology::Entity* const entity)
        {
            // costructor.
            this->parent = entity;
            this->number_of_settings = 0;
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
                yli::config::Setting* setting = this->setting_pointer_map[setting_name];

                if (setting != nullptr)
                {
                    return setting->help();
                }
            }
            return this->help();
        }

        bool SettingMaster::set(std::string& setting_name, std::shared_ptr<yli::datatypes::AnyValue> setting_new_any_value)
        {
            if (!this->is_setting(setting_name))
            {
                return false;
            }

            // OK, this is a valid variable name.
            // Set the variable value and activate it by
            // calling the corresponding activate callback.
            yli::config::Setting* setting = this->setting_pointer_map[setting_name];

            // create empty `AnyValue` (there is no suitable constructor yet).
            setting_new_any_value->type = setting->setting_value->type;

            setting->setting_value = setting_new_any_value;
            setting->activate_callback(this->parent, this);
            return true;
        }

        yli::config::Setting* SettingMaster::get(std::string& setting_name)
        {
            return this->setting_pointer_map[setting_name];
        }

        // public callbacks.

        std::shared_ptr<yli::datatypes::AnyValue> SettingMaster::set_and_print(
                yli::console::Console* const console,
                yli::ontology::Entity* const entity,
                const std::vector<std::string>& command_parameters)
        {
            // Usage:
            // to get variable names: set
            // to get valid values:   set <variable>
            // to set variable:       set <variable> <value>
            // to set variable:       set <entity> <variable> <value>

            yli::config::SettingMaster* setting_master = entity->get_setting_master();

            if (command_parameters.size() == 0)
            {
                // No command parameters.
                // Print variable names.
                console->print_text(setting_master->help());
            }
            else if (command_parameters.size() == 1)
            {
                // Exactly 1 parameter.

                std::string setting_name = command_parameters.at(0);

                // Print current value of the given variable.
                if (setting_master->is_setting(setting_name))
                {
                    yli::config::Setting* setting = setting_master->get(setting_name);

                    if (setting != nullptr && setting->setting_value != nullptr && setting->read_callback == nullptr)
                    {
                        // Print variable value.
                        console->print_text(setting->setting_value->get_string());
                    }
                    else if (setting != nullptr && setting->setting_value != nullptr)
                    {
                        std::shared_ptr<yli::datatypes::AnyValue> any_value_shared_ptr = setting->read_callback(entity, setting_master);

                        if (any_value_shared_ptr != nullptr)
                        {
                            console->print_text(any_value_shared_ptr->get_string());
                        }
                        else
                        {
                            console->print_text("read_callback returned nullptr");
                        }
                    }
                    else
                    {
                        // Invalid variable name.
                        console->print_text("invalid variable name");
                    }
                }
                else
                {
                    // Invalid variable name.
                    console->print_text("invalid variable name");
                }
            }
            else if (command_parameters.size() == 2)
            {
                // Exactly 2 parameters.

                std::string setting_name = command_parameters.at(0);

                // Check the validity of the variable name.
                if (setting_master->is_setting(setting_name))
                {
                    // OK, this is a valid variable name.
                    // Set the variable value and activate it by
                    // calling the corresponding activate callback.
                    yli::config::Setting* setting = setting_master->setting_pointer_map[setting_name];

                    // create empty `AnyValue` (there is no suitable constructor yet).
                    std::shared_ptr<yli::datatypes::AnyValue> setting_any_value = std::make_shared<yli::datatypes::AnyValue>();
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
            else if (command_parameters.size() == 3)
            {
                // Exactly 3 parameters.

                std::string entity_name = command_parameters.at(0);

                // if `set_and_print` is called through `Console::enter_key`,
                // then `entity` is `yli::ontology::Universe`, as
                // `Console::enter_key` passes `yli::ontology::Universe` as
                // the 2nd parameter to any `ConsoleCommandCallback` it calls.
                //
                // But now we want the `Entity` that corresponds `entity_name`
                // in `yli::ontology::Universe` 'namespace' (Ylikuutio namespace, not
                // C++ namespace!), so we need to request it from `yli::ontology::Universe`.
                // We also want the `SettingMaster` of the same `Entity`.

                yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

                if (universe == nullptr)
                {
                    // `entity` is not a `yli::ontology::Universe*`,
                    // can not proceed further.
                    return nullptr;
                }

                // Check the validity of the entity name.
                if (!universe->is_entity(entity_name))
                {
                    // Not a valid `Entity`.
                    return nullptr;
                }

                yli::ontology::Entity* named_entity = universe->get_entity(entity_name);
                setting_master = named_entity->get_setting_master();

                std::string setting_name = command_parameters.at(1);

                // Check the validity of the variable name.
                if (setting_master->is_setting(setting_name))
                {
                    // OK, this is a valid variable name.
                    // Set the variable value and activate it by
                    // calling the corresponding activate callback.
                    yli::config::Setting* setting = setting_master->setting_pointer_map[setting_name];

                    // create empty `AnyValue` (there is no suitable constructor yet).
                    std::shared_ptr<yli::datatypes::AnyValue> setting_any_value = std::make_shared<yli::datatypes::AnyValue>();
                    setting_any_value->type = setting->setting_value->type;

                    // set a new value.
                    bool success = setting_any_value->set_value(command_parameters.at(2));

                    if (success)
                    {
                        setting->setting_value = setting_any_value;

                        if (setting->activate_callback != nullptr)
                        {
                            setting->activate_callback(named_entity, setting_master);
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

        std::shared_ptr<yli::datatypes::AnyValue> SettingMaster::get_and_print(
                yli::console::Console* const console,
                yli::ontology::Entity* const entity,
                const std::vector<std::string>& command_parameters)
        {
            // Usage:
            // to get variable names: get
            // to get variable value: get <variable>
            yli::config::SettingMaster* setting_master = entity->get_setting_master();

            if (command_parameters.size() == 0)
            {
                // No command parameters.
                // Print variable names.
                console->print_text(setting_master->help());
            }
            else if (command_parameters.size() == 1)
            {
                // Exactly 1 parameter.

                std::string setting_name = command_parameters.at(0);

                // Print valid values of the given variable.
                if (setting_master->is_setting(setting_name))
                {
                    yli::config::Setting* setting = setting_master->get(setting_name);

                    if (setting != nullptr && setting->setting_value != nullptr && setting->read_callback == nullptr)
                    {
                        // Print variable value.
                        console->print_text(setting->setting_value->get_string());
                    }
                    else if (setting != nullptr && setting->setting_value != nullptr)
                    {
                        std::shared_ptr<yli::datatypes::AnyValue> any_value_shared_ptr = setting->read_callback(entity, setting_master);

                        if (any_value_shared_ptr != nullptr)
                        {
                            console->print_text(any_value_shared_ptr->get_string());
                        }
                        else
                        {
                            console->print_text("read_callback returned nullptr");
                        }
                    }
                    else
                    {
                        // Invalid variable name.
                        console->print_text("invalid variable name");
                    }
                }
                else
                {
                    // Invalid variable name.
                    console->print_text("invalid variable name");
                }
            }
            else if (command_parameters.size() == 2)
            {
                // Exactly 2 parameters.

                std::string entity_name = command_parameters.at(0);

                // if `get_and_print` is called through `Console::enter_key`,
                // then `entity` is `yli::ontology::Universe`, as
                // `Console::enter_key` passes `yli::ontology::Universe` as
                // the 2nd parameter to any `ConsoleCommandCallback` it calls.
                //
                // But now we want the `Entity` that corresponds `entity_name`
                // in `yli::ontology::Universe` 'namespace' (Ylikuutio namespace, not
                // C++ namespace!), so we need to request it from `yli::ontology::Universe`.
                // We also want the `SettingMaster` of the same `Entity`.

                yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

                if (universe == nullptr)
                {
                    // `entity` is not a `yli::ontology::Universe*`,
                    // can not proceed further.
                    return nullptr;
                }

                // Check the validity of the entity name.
                if (!universe->is_entity(entity_name))
                {
                    // Not a valid `Entity`.
                    return nullptr;
                }

                yli::ontology::Entity* named_entity = universe->get_entity(entity_name);
                setting_master = named_entity->get_setting_master();

                std::string setting_name = command_parameters.at(1);

                // Print valid values of the given variable.
                if (setting_master->is_setting(setting_name))
                {
                    yli::config::Setting* setting = setting_master->get(setting_name);

                    if (setting != nullptr && setting->setting_value != nullptr && setting->read_callback == nullptr)
                    {
                        // Print variable value.
                        console->print_text(setting->setting_value->get_string());
                    }
                    else if (setting != nullptr && setting->setting_value != nullptr)
                    {
                        std::shared_ptr<yli::datatypes::AnyValue> any_value_shared_ptr = setting->read_callback(named_entity, setting_master);

                        if (any_value_shared_ptr != nullptr)
                        {
                            console->print_text(any_value_shared_ptr->get_string());
                        }
                        else
                        {
                            console->print_text("read_callback returned nullptr");
                        }
                    }
                    else
                    {
                        // Invalid variable name.
                        console->print_text("invalid variable name");
                    }
                }
                else
                {
                    // Invalid variable name.
                    console->print_text("invalid variable name");
                }
            }
            else
            {
                // More than 2 command parameters.
                // Print variable names.
                console->print_text(setting_master->help());
            }

            return nullptr;
        }

        std::shared_ptr<yli::datatypes::AnyValue> SettingMaster::activate_planet_radius(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
        {
            if (entity == nullptr || setting_master == nullptr)
            {
                return nullptr;
            }

            if (setting_master->setting_pointer_map.count("planet_radius") != 1)
            {
                return nullptr;
            }

            std::shared_ptr<yli::datatypes::AnyValue> planet_radius_any_value = std::make_shared<yli::datatypes::AnyValue>(*setting_master->setting_pointer_map["planet_radius"]->setting_value);

            if (planet_radius_any_value == nullptr || planet_radius_any_value->type != yli::datatypes::FLOAT)
            {
                return nullptr;
            }

            yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

            if (universe == nullptr)
            {
                return nullptr;
            }

            universe->set_planet_radius(planet_radius_any_value->float_value);
            return nullptr;
        }

        std::shared_ptr<yli::datatypes::AnyValue> SettingMaster::activate_background_color(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
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
            std::shared_ptr<yli::datatypes::AnyValue> red_any_value = std::make_shared<yli::datatypes::AnyValue>(*setting_master->setting_pointer_map["red"]->setting_value);

            if (red_any_value == nullptr || red_any_value->type != yli::datatypes::FLOAT)
            {
                return nullptr;
            }

            GLclampf red = static_cast<GLclampf>(red_any_value->float_value);

            // green.
            std::shared_ptr<yli::datatypes::AnyValue> green_any_value = std::make_shared<yli::datatypes::AnyValue>(*setting_master->setting_pointer_map["green"]->setting_value);

            if (green_any_value == nullptr || green_any_value->type != yli::datatypes::FLOAT)
            {
                return nullptr;
            }

            GLclampf green = static_cast<GLclampf>(green_any_value->float_value);

            // blue.
            std::shared_ptr<yli::datatypes::AnyValue> blue_any_value = std::make_shared<yli::datatypes::AnyValue>(*setting_master->setting_pointer_map["blue"]->setting_value);

            if (blue_any_value == nullptr || blue_any_value->type != yli::datatypes::FLOAT)
            {
                return nullptr;
            }

            GLclampf blue = static_cast<GLclampf>(blue_any_value->float_value);

            // alpha.
            std::shared_ptr<yli::datatypes::AnyValue> alpha_any_value = std::make_shared<yli::datatypes::AnyValue>(*setting_master->setting_pointer_map["alpha"]->setting_value);

            if (alpha_any_value == nullptr || alpha_any_value->type != yli::datatypes::FLOAT)
            {
                return nullptr;
            }

            GLclampf alpha = static_cast<GLclampf>(alpha_any_value->float_value);

            yli::opengl::set_background_color(red, green, blue, alpha);

            yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

            if (universe == nullptr)
            {
                return nullptr;
            }

            universe->background_red = red;
            universe->background_green = green;
            universe->background_blue = blue;
            universe->background_alpha = alpha;

            return nullptr;
        }

        std::shared_ptr<yli::datatypes::AnyValue> SettingMaster::activate_wireframe(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
        {
            if (entity == nullptr || setting_master == nullptr)
            {
                return nullptr;
            }

            if (setting_master->setting_pointer_map.count("wireframe") != 1)
            {
                return nullptr;
            }

            std::shared_ptr<yli::datatypes::AnyValue> wireframe_any_value = std::make_shared<yli::datatypes::AnyValue>(*setting_master->setting_pointer_map["wireframe"]->setting_value);

            if (wireframe_any_value == nullptr || wireframe_any_value->type != yli::datatypes::BOOL)
            {
                return nullptr;
            }

            yli::opengl::set_wireframe(wireframe_any_value->bool_value);
            return nullptr;
        }

        std::shared_ptr<yli::datatypes::AnyValue> SettingMaster::activate_should_be_rendered(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
        {
            if (entity == nullptr || setting_master == nullptr)
            {
                return nullptr;
            }

            if (setting_master->setting_pointer_map.count("should_be_rendered") != 1)
            {
                return nullptr;
            }

            std::shared_ptr<yli::datatypes::AnyValue> should_be_rendered_any_value = std::make_shared<yli::datatypes::AnyValue>(*setting_master->setting_pointer_map["should_be_rendered"]->setting_value);

            if (should_be_rendered_any_value == nullptr || should_be_rendered_any_value->type != yli::datatypes::BOOL)
            {
                return nullptr;
            }

            entity->should_be_rendered = should_be_rendered_any_value->bool_value;
            return nullptr;
        }

        std::shared_ptr<yli::datatypes::AnyValue> SettingMaster::activate_spherical_coordinates(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
        {
            if (entity == nullptr || setting_master == nullptr)
            {
                return nullptr;
            }

            yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

            if (movable != nullptr)
            {
                if (setting_master->setting_pointer_map.count("spherical_coordinates") != 1)
                {
                    return nullptr;
                }

                std::shared_ptr<yli::datatypes::AnyValue> spherical_coordinates_any_value = std::make_shared<yli::datatypes::AnyValue>(*setting_master->setting_pointer_map["spherical_coordinates"]->setting_value);

                if (spherical_coordinates_any_value == nullptr || spherical_coordinates_any_value->type != yli::datatypes::SPHERICAL_COORDINATES_STRUCT_POINTER)
                {
                    return nullptr;
                }

                movable->spherical_coordinates = *spherical_coordinates_any_value->spherical_coordinates_struct_pointer;
                return nullptr;
            }

            yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

            if (universe == nullptr || setting_master->setting_pointer_map.count("spherical_coordinates") != 1)
            {
                return nullptr;
            }

            std::shared_ptr<yli::datatypes::AnyValue> spherical_coordinates_any_value = std::make_shared<yli::datatypes::AnyValue>(*setting_master->setting_pointer_map["spherical_coordinates"]->setting_value);

            if (spherical_coordinates_any_value == nullptr || spherical_coordinates_any_value->type != yli::datatypes::SPHERICAL_COORDINATES_STRUCT_POINTER)
            {
                return nullptr;
            }

            universe->current_camera_spherical_coordinates = *spherical_coordinates_any_value->spherical_coordinates_struct_pointer;
            return nullptr;
        }

        std::shared_ptr<yli::datatypes::AnyValue> SettingMaster::activate_rho(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
        {
            if (entity == nullptr || setting_master == nullptr)
            {
                return nullptr;
            }

            yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

            if (movable != nullptr)
            {
                if (setting_master->setting_pointer_map.count("spherical_coordinates") != 1)
                {
                    return nullptr;
                }

                std::shared_ptr<yli::datatypes::AnyValue> rho_any_value = std::make_shared<yli::datatypes::AnyValue>(*setting_master->setting_pointer_map["rho"]->setting_value);

                if (rho_any_value == nullptr || rho_any_value->type != yli::datatypes::FLOAT)
                {
                    return nullptr;
                }

                movable->spherical_coordinates.rho = rho_any_value->float_value;
                return nullptr;
            }

            yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

            if (universe == nullptr)
            {
                return nullptr;
            }

            if (setting_master->setting_pointer_map.count("spherical_coordinates") != 1)
            {
                return nullptr;
            }

            std::shared_ptr<yli::datatypes::AnyValue> rho_any_value = std::make_shared<yli::datatypes::AnyValue>(*setting_master->setting_pointer_map["rho"]->setting_value);

            if (rho_any_value == nullptr || rho_any_value->type != yli::datatypes::FLOAT)
            {
                return nullptr;
            }

            universe->current_camera_spherical_coordinates.rho = rho_any_value->float_value;
            return nullptr;
        }

        std::shared_ptr<yli::datatypes::AnyValue> SettingMaster::activate_theta(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
        {
            if (entity == nullptr || setting_master == nullptr)
            {
                return nullptr;
            }

            yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

            if (movable != nullptr)
            {
                if (setting_master->setting_pointer_map.count("spherical_coordinates") != 1)
                {
                    return nullptr;
                }

                std::shared_ptr<yli::datatypes::AnyValue> theta_any_value = std::make_shared<yli::datatypes::AnyValue>(*setting_master->setting_pointer_map["theta"]->setting_value);

                if (theta_any_value == nullptr || theta_any_value->type != yli::datatypes::FLOAT)
                {
                    return nullptr;
                }

                movable->spherical_coordinates.theta = theta_any_value->float_value;
                return nullptr;
            }

            yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

            if (universe == nullptr)
            {
                return nullptr;
            }

            if (setting_master->setting_pointer_map.count("spherical_coordinates") != 1)
            {
                return nullptr;
            }

            std::shared_ptr<yli::datatypes::AnyValue> theta_any_value = std::make_shared<yli::datatypes::AnyValue>(*setting_master->setting_pointer_map["theta"]->setting_value);

            if (theta_any_value == nullptr || theta_any_value->type != yli::datatypes::FLOAT)
            {
                return nullptr;
            }

            universe->current_camera_spherical_coordinates.theta = theta_any_value->float_value;
            return nullptr;
        }

        std::shared_ptr<yli::datatypes::AnyValue> SettingMaster::activate_phi(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
        {
            if (entity == nullptr || setting_master == nullptr)
            {
                return nullptr;
            }

            yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

            if (movable != nullptr)
            {
                if (setting_master->setting_pointer_map.count("spherical_coordinates") != 1)
                {
                    return nullptr;
                }

                std::shared_ptr<yli::datatypes::AnyValue> phi_any_value = std::make_shared<yli::datatypes::AnyValue>(*setting_master->setting_pointer_map["phi"]->setting_value);

                if (phi_any_value == nullptr || phi_any_value->type != yli::datatypes::FLOAT)
                {
                    return nullptr;
                }

                movable->spherical_coordinates.phi = phi_any_value->float_value;
                return nullptr;
            }

            yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

            if (universe == nullptr)
            {
                return nullptr;
            }

            if (setting_master->setting_pointer_map.count("spherical_coordinates") != 1)
            {
                return nullptr;
            }

            std::shared_ptr<yli::datatypes::AnyValue> phi_any_value = std::make_shared<yli::datatypes::AnyValue>(*setting_master->setting_pointer_map["phi"]->setting_value);

            if (phi_any_value == nullptr || phi_any_value->type != yli::datatypes::FLOAT)
            {
                return nullptr;
            }

            universe->current_camera_spherical_coordinates.phi = phi_any_value->float_value;
            return nullptr;
        }

        std::shared_ptr<yli::datatypes::AnyValue> SettingMaster::activate_cartesian_coordinates(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
        {
            if (entity == nullptr || setting_master == nullptr)
            {
                return nullptr;
            }

            yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

            if (movable != nullptr)
            {
                if (setting_master->setting_pointer_map.count("cartesian_coordinates") != 1)
                {
                    return nullptr;
                }

                std::shared_ptr<yli::datatypes::AnyValue> cartesian_coordinates_any_value = std::make_shared<yli::datatypes::AnyValue>(*setting_master->setting_pointer_map["cartesian_coordinates"]->setting_value);

                if (cartesian_coordinates_any_value == nullptr || cartesian_coordinates_any_value->type != yli::datatypes::GLM_VEC3_POINTER)
                {
                    return nullptr;
                }

                movable->cartesian_coordinates = glm::vec3(*cartesian_coordinates_any_value->glm_vec3_pointer);
                return nullptr;
            }

            yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

            if (universe == nullptr || setting_master->setting_pointer_map.count("cartesian_coordinates") != 1)
            {
                return nullptr;
            }

            std::shared_ptr<yli::datatypes::AnyValue> cartesian_coordinates_any_value = std::make_shared<yli::datatypes::AnyValue>(*setting_master->setting_pointer_map["cartesian_coordinates"]->setting_value);

            if (cartesian_coordinates_any_value == nullptr || cartesian_coordinates_any_value->type != yli::datatypes::GLM_VEC3_POINTER)
            {
                return nullptr;
            }

            universe->current_camera_cartesian_coordinates = glm::vec3(*cartesian_coordinates_any_value->glm_vec3_pointer);
            return nullptr;
        }

        std::shared_ptr<yli::datatypes::AnyValue> SettingMaster::activate_x(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
        {
            if (entity == nullptr || setting_master == nullptr)
            {
                return nullptr;
            }

            yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

            if (movable != nullptr)
            {
                if (setting_master->setting_pointer_map.count("x") != 1)
                {
                    return nullptr;
                }

                std::shared_ptr<yli::datatypes::AnyValue> x_any_value = std::make_shared<yli::datatypes::AnyValue>(*setting_master->setting_pointer_map["x"]->setting_value);

                if (x_any_value == nullptr || x_any_value->type != yli::datatypes::FLOAT)
                {
                    return nullptr;
                }

                movable->cartesian_coordinates.x = x_any_value->float_value;
                movable->model_matrix[3][0] = x_any_value->float_value;

                yli::ontology::Holobiont* const holobiont = dynamic_cast<yli::ontology::Holobiont*>(movable);

                if (holobiont != nullptr)
                {
                    holobiont->update_x(x_any_value->float_value);
                }

                return nullptr;
            }

            yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

            if (universe == nullptr)
            {
                return nullptr;
            }

            if (setting_master->setting_pointer_map.count("x") != 1)
            {
                return nullptr;
            }

            std::shared_ptr<yli::datatypes::AnyValue> x_any_value = std::make_shared<yli::datatypes::AnyValue>(*setting_master->setting_pointer_map["x"]->setting_value);

            if (x_any_value == nullptr || x_any_value->type != yli::datatypes::FLOAT)
            {
                return nullptr;
            }

            universe->current_camera_cartesian_coordinates.x = x_any_value->float_value;
            return nullptr;
        }

        std::shared_ptr<yli::datatypes::AnyValue> SettingMaster::activate_y(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
        {
            if (entity == nullptr || setting_master == nullptr)
            {
                return nullptr;
            }

            yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

            if (movable != nullptr)
            {
                if (setting_master->setting_pointer_map.count("y") != 1)
                {
                    return nullptr;
                }

                std::shared_ptr<yli::datatypes::AnyValue> y_any_value = std::make_shared<yli::datatypes::AnyValue>(*setting_master->setting_pointer_map["y"]->setting_value);

                if (y_any_value == nullptr || y_any_value->type != yli::datatypes::FLOAT)
                {
                    return nullptr;
                }

                movable->cartesian_coordinates.y = y_any_value->float_value;
                movable->model_matrix[3][1] = y_any_value->float_value;

                yli::ontology::Holobiont* const holobiont = dynamic_cast<yli::ontology::Holobiont*>(movable);

                if (holobiont != nullptr)
                {
                    holobiont->update_y(y_any_value->float_value);
                }

                return nullptr;
            }

            yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

            if (universe == nullptr)
            {
                return nullptr;
            }

            if (setting_master->setting_pointer_map.count("y") != 1)
            {
                return nullptr;
            }

            std::shared_ptr<yli::datatypes::AnyValue> y_any_value = std::make_shared<yli::datatypes::AnyValue>(*setting_master->setting_pointer_map["y"]->setting_value);

            if (y_any_value == nullptr || y_any_value->type != yli::datatypes::FLOAT)
            {
                return nullptr;
            }

            universe->current_camera_cartesian_coordinates.y = y_any_value->float_value;
            return nullptr;
        }

        std::shared_ptr<yli::datatypes::AnyValue> SettingMaster::activate_z(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
        {
            if (entity == nullptr || setting_master == nullptr)
            {
                return nullptr;
            }

            yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

            if (movable != nullptr)
            {
                if (setting_master->setting_pointer_map.count("z") != 1)
                {
                    return nullptr;
                }

                std::shared_ptr<yli::datatypes::AnyValue> z_any_value = std::make_shared<yli::datatypes::AnyValue>(*setting_master->setting_pointer_map["z"]->setting_value);

                if (z_any_value == nullptr || z_any_value->type != yli::datatypes::FLOAT)
                {
                    return nullptr;
                }

                movable->cartesian_coordinates.z = z_any_value->float_value;
                movable->model_matrix[3][2] = z_any_value->float_value;

                yli::ontology::Holobiont* const holobiont = dynamic_cast<yli::ontology::Holobiont*>(movable);

                if (holobiont != nullptr)
                {
                    holobiont->update_z(z_any_value->float_value);
                }

                return nullptr;
            }

            yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

            if (universe == nullptr)
            {
                return nullptr;
            }

            if (setting_master->setting_pointer_map.count("z") != 1)
            {
                return nullptr;
            }

            std::shared_ptr<yli::datatypes::AnyValue> z_any_value = std::make_shared<yli::datatypes::AnyValue>(*setting_master->setting_pointer_map["z"]->setting_value);

            if (z_any_value == nullptr || z_any_value->type != yli::datatypes::FLOAT)
            {
                return nullptr;
            }

            universe->current_camera_cartesian_coordinates.z = z_any_value->float_value;
            return nullptr;
        }

        std::shared_ptr<yli::datatypes::AnyValue> SettingMaster::activate_horizontal_angle(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
        {
            if (entity == nullptr || setting_master == nullptr)
            {
                return nullptr;
            }

            yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

            if (universe == nullptr)
            {
                return nullptr;
            }

            if (setting_master->setting_pointer_map.count("horizontal_angle") != 1)
            {
                return nullptr;
            }

            std::shared_ptr<yli::datatypes::AnyValue> horizontal_angle_any_value = std::make_shared<yli::datatypes::AnyValue>(*setting_master->setting_pointer_map["horizontal_angle"]->setting_value);

            if (horizontal_angle_any_value == nullptr || horizontal_angle_any_value->type != yli::datatypes::DOUBLE)
            {
                return nullptr;
            }

            universe->current_camera_horizontal_angle = horizontal_angle_any_value->double_value;
            return nullptr;
        }

        std::shared_ptr<yli::datatypes::AnyValue> SettingMaster::activate_vertical_angle(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
        {
            if (entity == nullptr || setting_master == nullptr)
            {
                return nullptr;
            }

            yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

            if (universe == nullptr)
            {
                return nullptr;
            }

            if (setting_master->setting_pointer_map.count("vertical_angle") != 1)
            {
                return nullptr;
            }

            std::shared_ptr<yli::datatypes::AnyValue> vertical_angle_any_value = std::make_shared<yli::datatypes::AnyValue>(*setting_master->setting_pointer_map["vertical_angle"]->setting_value);

            if (vertical_angle_any_value == nullptr || vertical_angle_any_value->type != yli::datatypes::DOUBLE)
            {
                return nullptr;
            }

            universe->current_camera_vertical_angle = vertical_angle_any_value->double_value;
            return nullptr;
        }

        std::shared_ptr<yli::datatypes::AnyValue> SettingMaster::activate_speed(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
        {
            if (entity == nullptr || setting_master == nullptr)
            {
                return nullptr;
            }

            yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

            if (universe == nullptr)
            {
                return nullptr;
            }

            if (setting_master->setting_pointer_map.count("speed") != 1)
            {
                return nullptr;
            }

            std::shared_ptr<yli::datatypes::AnyValue> speed_any_value = std::make_shared<yli::datatypes::AnyValue>(*setting_master->setting_pointer_map["speed"]->setting_value);

            if (speed_any_value == nullptr || speed_any_value->type != yli::datatypes::FLOAT)
            {
                return nullptr;
            }

            universe->speed = speed_any_value->float_value;
            return nullptr;
        }

        std::shared_ptr<yli::datatypes::AnyValue> SettingMaster::activate_turbo_factor(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
        {
            if (entity == nullptr || setting_master == nullptr)
            {
                return nullptr;
            }

            yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

            if (universe == nullptr)
            {
                return nullptr;
            }

            if (setting_master->setting_pointer_map.count("turbo_factor") != 1)
            {
                return nullptr;
            }

            std::shared_ptr<yli::datatypes::AnyValue> turbo_factor_any_value = std::make_shared<yli::datatypes::AnyValue>(*setting_master->setting_pointer_map["turbo_factor"]->setting_value);

            if (turbo_factor_any_value == nullptr || turbo_factor_any_value->type != yli::datatypes::FLOAT)
            {
                return nullptr;
            }

            universe->turbo_factor = turbo_factor_any_value->float_value;
            return nullptr;
        }

        std::shared_ptr<yli::datatypes::AnyValue> SettingMaster::activate_twin_turbo_factor(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
        {
            if (entity == nullptr || setting_master == nullptr)
            {
                return nullptr;
            }

            yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

            if (universe == nullptr)
            {
                return nullptr;
            }

            if (setting_master->setting_pointer_map.count("twin_turbo_factor") != 1)
            {
                return nullptr;
            }

            std::shared_ptr<yli::datatypes::AnyValue> twin_turbo_factor_any_value = std::make_shared<yli::datatypes::AnyValue>(*setting_master->setting_pointer_map["twin_turbo_factor"]->setting_value);

            if (twin_turbo_factor_any_value == nullptr || twin_turbo_factor_any_value->type != yli::datatypes::FLOAT)
            {
                return nullptr;
            }

            universe->twin_turbo_factor = twin_turbo_factor_any_value->float_value;
            return nullptr;
        }

        std::shared_ptr<yli::datatypes::AnyValue> SettingMaster::activate_mouse_speed(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
        {
            if (entity == nullptr || setting_master == nullptr)
            {
                return nullptr;
            }

            yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

            if (universe == nullptr)
            {
                return nullptr;
            }

            if (setting_master->setting_pointer_map.count("mouse_speed") != 1)
            {
                return nullptr;
            }

            std::shared_ptr<yli::datatypes::AnyValue> mouse_speed_any_value = std::make_shared<yli::datatypes::AnyValue>(*setting_master->setting_pointer_map["mouse_speed"]->setting_value);

            if (mouse_speed_any_value == nullptr || mouse_speed_any_value->type != yli::datatypes::FLOAT)
            {
                return nullptr;
            }

            universe->mouse_speed = mouse_speed_any_value->float_value;
            return nullptr;
        }

        std::shared_ptr<yli::datatypes::AnyValue> SettingMaster::activate_is_flight_mode_in_use(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
        {
            if (entity == nullptr || setting_master == nullptr)
            {
                return nullptr;
            }

            yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

            if (universe == nullptr)
            {
                return nullptr;
            }

            if (setting_master->setting_pointer_map.count("is_flight_mode_in_use") != 1)
            {
                return nullptr;
            }

            std::shared_ptr<yli::datatypes::AnyValue> is_flight_mode_in_use_any_value = std::make_shared<yli::datatypes::AnyValue>(*setting_master->setting_pointer_map["is_flight_mode_in_use"]->setting_value);

            if (is_flight_mode_in_use_any_value == nullptr || is_flight_mode_in_use_any_value->type != yli::datatypes::BOOL)
            {
                return nullptr;
            }

            universe->is_flight_mode_in_use = is_flight_mode_in_use_any_value->bool_value;
            return nullptr;
        }

        std::shared_ptr<yli::datatypes::AnyValue> SettingMaster::activate_console_top_y(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
        {
            if (entity == nullptr || setting_master == nullptr)
            {
                return nullptr;
            }

            if (setting_master->setting_pointer_map.count("console_top_y") != 1)
            {
                return nullptr;
            }

            std::shared_ptr<yli::datatypes::AnyValue> console_top_y_any_value = std::make_shared<yli::datatypes::AnyValue>(*setting_master->setting_pointer_map["console_top_y"]->setting_value);

            if (console_top_y_any_value == nullptr || console_top_y_any_value->type != yli::datatypes::UINT32_T)
            {
                return nullptr;
            }

            yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

            if (universe == nullptr)
            {
                return nullptr;
            }

            yli::console::Console* const console = universe->get_console();

            if (console == nullptr)
            {
                return nullptr;
            }

            console->set_console_top_y(console_top_y_any_value->uint32_t_value);
            return nullptr;
        }

        std::shared_ptr<yli::datatypes::AnyValue> SettingMaster::activate_console_bottom_y(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
        {
            if (entity == nullptr || setting_master == nullptr)
            {
                return nullptr;
            }

            if (setting_master->setting_pointer_map.count("console_bottom_y") != 1)
            {
                return nullptr;
            }

            std::shared_ptr<yli::datatypes::AnyValue> console_bottom_y_any_value = std::make_shared<yli::datatypes::AnyValue>(*setting_master->setting_pointer_map["console_bottom_y"]->setting_value);

            if (console_bottom_y_any_value == nullptr || console_bottom_y_any_value->type != yli::datatypes::UINT32_T)
            {
                return nullptr;
            }

            yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

            if (universe == nullptr)
            {
                return nullptr;
            }

            yli::console::Console* const console = universe->get_console();

            if (console == nullptr)
            {
                return nullptr;
            }

            console->set_console_bottom_y(console_bottom_y_any_value->uint32_t_value);
            return nullptr;
        }

        std::shared_ptr<yli::datatypes::AnyValue> SettingMaster::activate_console_left_x(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
        {
            if (entity == nullptr || setting_master == nullptr)
            {
                return nullptr;
            }

            if (setting_master->setting_pointer_map.count("console_left_x") != 1)
            {
                return nullptr;
            }

            std::shared_ptr<yli::datatypes::AnyValue> console_left_x_any_value = std::make_shared<yli::datatypes::AnyValue>(*setting_master->setting_pointer_map["console_left_x"]->setting_value);

            if (console_left_x_any_value == nullptr || console_left_x_any_value->type != yli::datatypes::UINT32_T)
            {
                return nullptr;
            }

            yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

            if (universe == nullptr)
            {
                return nullptr;
            }

            yli::console::Console* const console = universe->get_console();

            if (console == nullptr)
            {
                return nullptr;
            }

            console->set_console_left_x(console_left_x_any_value->uint32_t_value);
            return nullptr;
        }

        std::shared_ptr<yli::datatypes::AnyValue> SettingMaster::activate_console_right_x(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
        {
            if (entity == nullptr || setting_master == nullptr)
            {
                return nullptr;
            }

            if (setting_master->setting_pointer_map.count("console_right_x") != 1)
            {
                return nullptr;
            }

            std::shared_ptr<yli::datatypes::AnyValue> console_right_x_any_value = std::make_shared<yli::datatypes::AnyValue>(*setting_master->setting_pointer_map["console_right_x"]->setting_value);

            if (console_right_x_any_value == nullptr || console_right_x_any_value->type != yli::datatypes::UINT32_T)
            {
                return nullptr;
            }

            yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

            if (universe == nullptr)
            {
                return nullptr;
            }

            yli::console::Console* const console = universe->get_console();

            if (console == nullptr)
            {
                return nullptr;
            }

            console->set_console_right_x(console_right_x_any_value->uint32_t_value);
            return nullptr;
        }

        std::shared_ptr<yli::datatypes::AnyValue> SettingMaster::read_should_be_rendered(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
        {
            if (entity == nullptr)
            {
                return nullptr;
            }

            return std::make_shared<yli::datatypes::AnyValue>(entity->should_be_rendered);
        }

        std::shared_ptr<yli::datatypes::AnyValue> SettingMaster::read_cartesian_coordinates(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
        {
            if (entity == nullptr)
            {
                return nullptr;
            }

            yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

            if (movable != nullptr)
            {
                return std::make_shared<yli::datatypes::AnyValue>(&movable->cartesian_coordinates);
            }

            yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

            if (universe == nullptr)
            {
                return nullptr;
            }

            return std::make_shared<yli::datatypes::AnyValue>(&universe->current_camera_cartesian_coordinates);
        }

        std::shared_ptr<yli::datatypes::AnyValue> SettingMaster::read_x(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
        {
            if (entity == nullptr)
            {
                return nullptr;
            }

            yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

            if (movable != nullptr)
            {
                return std::make_shared<yli::datatypes::AnyValue>(movable->cartesian_coordinates.x);
            }

            yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

            if (universe == nullptr)
            {
                return nullptr;
            }

            return std::make_shared<yli::datatypes::AnyValue>(universe->current_camera_cartesian_coordinates.x);
        }

        std::shared_ptr<yli::datatypes::AnyValue> SettingMaster::read_y(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
        {
            if (entity == nullptr)
            {
                return nullptr;
            }

            yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

            if (movable != nullptr)
            {
                return std::make_shared<yli::datatypes::AnyValue>(movable->cartesian_coordinates.y);
            }

            yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

            if (universe == nullptr)
            {
                return nullptr;
            }

            return std::make_shared<yli::datatypes::AnyValue>(universe->current_camera_cartesian_coordinates.y);
        }

        std::shared_ptr<yli::datatypes::AnyValue> SettingMaster::read_z(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
        {
            if (entity == nullptr)
            {
                return nullptr;
            }

            yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

            if (movable != nullptr)
            {
                return std::make_shared<yli::datatypes::AnyValue>(movable->cartesian_coordinates.z);
            }

            yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

            if (universe == nullptr)
            {
                return nullptr;
            }

            return std::make_shared<yli::datatypes::AnyValue>(universe->current_camera_cartesian_coordinates.z);
        }

        std::shared_ptr<yli::datatypes::AnyValue> SettingMaster::read_rho(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
        {
            if (entity == nullptr)
            {
                return nullptr;
            }

            yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

            if (movable != nullptr)
            {
                return std::make_shared<yli::datatypes::AnyValue>(movable->spherical_coordinates.rho);
            }

            yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

            if (universe == nullptr)
            {
                return nullptr;
            }

            return std::make_shared<yli::datatypes::AnyValue>(universe->current_camera_spherical_coordinates.rho);
        }

        std::shared_ptr<yli::datatypes::AnyValue> SettingMaster::read_theta(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
        {
            if (entity == nullptr)
            {
                return nullptr;
            }

            yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

            if (movable != nullptr)
            {
                return std::make_shared<yli::datatypes::AnyValue>(movable->spherical_coordinates.theta);
            }

            yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

            if (universe == nullptr)
            {
                return nullptr;
            }

            return std::make_shared<yli::datatypes::AnyValue>(universe->current_camera_spherical_coordinates.theta);
        }

        std::shared_ptr<yli::datatypes::AnyValue> SettingMaster::read_phi(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
        {
            if (entity == nullptr)
            {
                return nullptr;
            }

            yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

            if (movable != nullptr)
            {
                return std::make_shared<yli::datatypes::AnyValue>(movable->spherical_coordinates.phi);
            }

            yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

            if (universe == nullptr)
            {
                return nullptr;
            }

            return std::make_shared<yli::datatypes::AnyValue>(universe->current_camera_spherical_coordinates.phi);
        }

        std::shared_ptr<yli::datatypes::AnyValue> SettingMaster::read_up(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
        {
            if (entity == nullptr)
            {
                return nullptr;
            }

            yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

            if (universe == nullptr)
            {
                return nullptr;
            }

            return std::make_shared<yli::datatypes::AnyValue>(&universe->current_camera_up);
        }

        std::shared_ptr<yli::datatypes::AnyValue> SettingMaster::read_right(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
        {
            if (entity == nullptr)
            {
                return nullptr;
            }

            yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

            if (universe == nullptr)
            {
                return nullptr;
            }

            return std::make_shared<yli::datatypes::AnyValue>(&universe->current_camera_right);
        }

        std::shared_ptr<yli::datatypes::AnyValue> SettingMaster::read_horizontal_angle(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
        {
            if (entity == nullptr)
            {
                return nullptr;
            }

            yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

            if (universe == nullptr)
            {
                return nullptr;
            }

            return std::make_shared<yli::datatypes::AnyValue>(universe->current_camera_horizontal_angle);
        }

        std::shared_ptr<yli::datatypes::AnyValue> SettingMaster::read_vertical_angle(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
        {
            if (entity == nullptr)
            {
                return nullptr;
            }

            yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

            if (universe == nullptr)
            {
                return nullptr;
            }

            return std::make_shared<yli::datatypes::AnyValue>(universe->current_camera_vertical_angle);
        }

        std::shared_ptr<yli::datatypes::AnyValue> SettingMaster::read_is_flight_mode_in_use(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
        {
            if (entity == nullptr)
            {
                return nullptr;
            }

            yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

            if (universe == nullptr)
            {
                return nullptr;
            }

            return std::make_shared<yli::datatypes::AnyValue>(universe->is_flight_mode_in_use);
        }
    }
}
