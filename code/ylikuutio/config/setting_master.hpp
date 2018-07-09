#ifndef __SETTING_MASTER_HPP_INCLUDED
#define __SETTING_MASTER_HPP_INCLUDED

// Include standard headers
#include <memory>        // std::make_shared, std::shared_ptr
#include <queue>         // std::queue
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

namespace ylikuutio
{
    namespace console
    {
        class Console;
    }
}

namespace datatypes
{
    class AnyValue;
}

namespace ylikuutio
{
    namespace ontology
    {
        class Entity;
    }
}

namespace ylikuutio
{
    namespace config
    {
        class Setting;

        class SettingMaster
        {
            public:
                // constructor.
                SettingMaster(ylikuutio::ontology::Entity* const entity);

                // destructor.
                ~SettingMaster();

                // does setting `setting` exist?
                bool is_setting(const std::string& setting_name);

                // this function returns general help.
                std::string help();

                // this function returns help string for setting `setting`.
                std::string help(const std::string& setting_name);

                bool set(std::string& setting_name, std::shared_ptr<datatypes::AnyValue> setting_new_any_value);

                ylikuutio::config::Setting* get(std::string& setting_name);

                // Public callbacks.

                static std::shared_ptr<datatypes::AnyValue> set_and_print(
                        ylikuutio::console::Console* console,
                        ylikuutio::ontology::Entity* entity,
                        std::vector<std::string>& command_parameters);

                static std::shared_ptr<datatypes::AnyValue> get_and_print(
                        ylikuutio::console::Console* console,
                        ylikuutio::ontology::Entity* entity,
                        std::vector<std::string>& command_parameters);

                static std::shared_ptr<datatypes::AnyValue> activate_planet_radius(ylikuutio::ontology::Entity* const entity, ylikuutio::config::SettingMaster* const setting_master);

                static std::shared_ptr<datatypes::AnyValue> activate_background_color(ylikuutio::ontology::Entity* const entity, ylikuutio::config::SettingMaster* const setting_master);

                static std::shared_ptr<datatypes::AnyValue> activate_wireframe(ylikuutio::ontology::Entity* const entity, ylikuutio::config::SettingMaster* const setting_master);

                static std::shared_ptr<datatypes::AnyValue> activate_spherical_coordinates(ylikuutio::ontology::Entity* const entity, ylikuutio::config::SettingMaster* const setting_master);
                static std::shared_ptr<datatypes::AnyValue> activate_rho(ylikuutio::ontology::Entity* const entity, ylikuutio::config::SettingMaster* const setting_master);
                static std::shared_ptr<datatypes::AnyValue> activate_theta(ylikuutio::ontology::Entity* const entity, ylikuutio::config::SettingMaster* const setting_master);
                static std::shared_ptr<datatypes::AnyValue> activate_phi(ylikuutio::ontology::Entity* const entity, ylikuutio::config::SettingMaster* const setting_master);

                static std::shared_ptr<datatypes::AnyValue> activate_cartesian_coordinates(ylikuutio::ontology::Entity* const entity, ylikuutio::config::SettingMaster* const setting_master);
                static std::shared_ptr<datatypes::AnyValue> activate_x(ylikuutio::ontology::Entity* const entity, ylikuutio::config::SettingMaster* const setting_master);
                static std::shared_ptr<datatypes::AnyValue> activate_y(ylikuutio::ontology::Entity* const entity, ylikuutio::config::SettingMaster* const setting_master);
                static std::shared_ptr<datatypes::AnyValue> activate_z(ylikuutio::ontology::Entity* const entity, ylikuutio::config::SettingMaster* const setting_master);

                static std::shared_ptr<datatypes::AnyValue> activate_horizontal_angle(ylikuutio::ontology::Entity* const entity, ylikuutio::config::SettingMaster* const setting_master);

                static std::shared_ptr<datatypes::AnyValue> activate_vertical_angle(ylikuutio::ontology::Entity* const entity, ylikuutio::config::SettingMaster* const setting_master);

                static std::shared_ptr<datatypes::AnyValue> activate_speed(ylikuutio::ontology::Entity* const entity, ylikuutio::config::SettingMaster* const setting_master);

                static std::shared_ptr<datatypes::AnyValue> activate_turbo_factor(ylikuutio::ontology::Entity* const entity, ylikuutio::config::SettingMaster* const setting_master);

                static std::shared_ptr<datatypes::AnyValue> activate_twin_turbo_factor(ylikuutio::ontology::Entity* const entity, ylikuutio::config::SettingMaster* const setting_master);

                static std::shared_ptr<datatypes::AnyValue> activate_mouse_speed(ylikuutio::ontology::Entity* const entity, ylikuutio::config::SettingMaster* const setting_master);

                static std::shared_ptr<datatypes::AnyValue> activate_is_flight_mode_in_use(ylikuutio::ontology::Entity* const entity, ylikuutio::config::SettingMaster* const setting_master);

                static std::shared_ptr<datatypes::AnyValue> read_cartesian_coordinates(ylikuutio::ontology::Entity* const entity, ylikuutio::config::SettingMaster* const setting_master);
                static std::shared_ptr<datatypes::AnyValue> read_x(ylikuutio::ontology::Entity* const entity, ylikuutio::config::SettingMaster* const setting_master);
                static std::shared_ptr<datatypes::AnyValue> read_y(ylikuutio::ontology::Entity* const entity, ylikuutio::config::SettingMaster* const setting_master);
                static std::shared_ptr<datatypes::AnyValue> read_z(ylikuutio::ontology::Entity* const entity, ylikuutio::config::SettingMaster* const setting_master);

                static std::shared_ptr<datatypes::AnyValue> read_rho(ylikuutio::ontology::Entity* const entity, ylikuutio::config::SettingMaster* const setting_master);
                static std::shared_ptr<datatypes::AnyValue> read_theta(ylikuutio::ontology::Entity* const entity, ylikuutio::config::SettingMaster* const setting_master);
                static std::shared_ptr<datatypes::AnyValue> read_phi(ylikuutio::ontology::Entity* const entity, ylikuutio::config::SettingMaster* const setting_master);

                static std::shared_ptr<datatypes::AnyValue> read_up(ylikuutio::ontology::Entity* const entity, ylikuutio::config::SettingMaster* const setting_master);
                static std::shared_ptr<datatypes::AnyValue> read_right(ylikuutio::ontology::Entity* const entity, ylikuutio::config::SettingMaster* const setting_master);

                static std::shared_ptr<datatypes::AnyValue> read_horizontal_angle(ylikuutio::ontology::Entity* const entity, ylikuutio::config::SettingMaster* const setting_master);
                static std::shared_ptr<datatypes::AnyValue> read_vertical_angle(ylikuutio::ontology::Entity* const entity, ylikuutio::config::SettingMaster* const setting_master);

                static std::shared_ptr<datatypes::AnyValue> read_is_flight_mode_in_use(ylikuutio::ontology::Entity* const entity, ylikuutio::config::SettingMaster* const setting_master);

                // Public callbacks end here.

                friend class Setting;
                friend class ylikuutio::ontology::Entity;
                friend class ylikuutio::console::Console;

            private:
                ylikuutio::ontology::Entity* parent;

                std::vector<ylikuutio::config::Setting*> setting_pointer_vector;
                std::queue<int32_t> free_settingID_queue;
                int32_t number_of_settings;

                std::unordered_map<std::string, ylikuutio::config::Setting*> setting_pointer_map;
        };
    }
}

#endif
