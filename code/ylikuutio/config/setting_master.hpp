#ifndef __SETTING_MASTER_HPP_INCLUDED
#define __SETTING_MASTER_HPP_INCLUDED

// Include standard headers
#include <memory>        // std::make_shared, std::shared_ptr
#include <queue>         // std::queue
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

namespace console
{
    class Console;
}

namespace datatypes
{
    class AnyValue;
}

namespace ontology
{
    class Entity;
}

namespace config
{
    class Setting;

    class SettingMaster
    {
        public:
            // constructor.
            SettingMaster(ontology::Entity* const entity);

            // destructor.
            ~SettingMaster();

            // does setting `setting` exist?
            bool is_setting(const std::string& setting_name);

            // this function returns general help.
            std::string help();

            // this function returns help string for setting `setting`.
            std::string help(const std::string& setting_name);

            bool set(std::string& setting_name, std::shared_ptr<datatypes::AnyValue> setting_new_any_value);

            config::Setting* get(std::string& setting_name);

            // Public callbacks.

            static std::shared_ptr<datatypes::AnyValue> set_and_print(
                    console::Console* console,
                    ontology::Entity* entity,
                    std::vector<std::string>& command_parameters);

            static std::shared_ptr<datatypes::AnyValue> get_and_print(
                    console::Console* console,
                    ontology::Entity* entity,
                    std::vector<std::string>& command_parameters);

            static std::shared_ptr<datatypes::AnyValue> activate_planet_radius(ontology::Entity* const entity, config::SettingMaster* const setting_master);

            static std::shared_ptr<datatypes::AnyValue> activate_background_color(ontology::Entity* const entity, config::SettingMaster* const setting_master);

            static std::shared_ptr<datatypes::AnyValue> activate_wireframe(ontology::Entity* const entity, config::SettingMaster* const setting_master);

            static std::shared_ptr<datatypes::AnyValue> activate_spherical_coordinates(ontology::Entity* const entity, config::SettingMaster* const setting_master);
            static std::shared_ptr<datatypes::AnyValue> activate_rho(ontology::Entity* const entity, config::SettingMaster* const setting_master);
            static std::shared_ptr<datatypes::AnyValue> activate_theta(ontology::Entity* const entity, config::SettingMaster* const setting_master);
            static std::shared_ptr<datatypes::AnyValue> activate_phi(ontology::Entity* const entity, config::SettingMaster* const setting_master);

            static std::shared_ptr<datatypes::AnyValue> activate_cartesian_coordinates(ontology::Entity* const entity, config::SettingMaster* const setting_master);
            static std::shared_ptr<datatypes::AnyValue> activate_x(ontology::Entity* const entity, config::SettingMaster* const setting_master);
            static std::shared_ptr<datatypes::AnyValue> activate_y(ontology::Entity* const entity, config::SettingMaster* const setting_master);
            static std::shared_ptr<datatypes::AnyValue> activate_z(ontology::Entity* const entity, config::SettingMaster* const setting_master);

            static std::shared_ptr<datatypes::AnyValue> activate_horizontal_angle(ontology::Entity* const entity, config::SettingMaster* const setting_master);

            static std::shared_ptr<datatypes::AnyValue> activate_vertical_angle(ontology::Entity* const entity, config::SettingMaster* const setting_master);

            static std::shared_ptr<datatypes::AnyValue> activate_speed(ontology::Entity* const entity, config::SettingMaster* const setting_master);

            static std::shared_ptr<datatypes::AnyValue> activate_turbo_factor(ontology::Entity* const entity, config::SettingMaster* const setting_master);

            static std::shared_ptr<datatypes::AnyValue> activate_twin_turbo_factor(ontology::Entity* const entity, config::SettingMaster* const setting_master);

            static std::shared_ptr<datatypes::AnyValue> activate_mouse_speed(ontology::Entity* const entity, config::SettingMaster* const setting_master);

            static std::shared_ptr<datatypes::AnyValue> activate_is_flight_mode_in_use(ontology::Entity* const entity, config::SettingMaster* const setting_master);

            static std::shared_ptr<datatypes::AnyValue> read_cartesian_coordinates(ontology::Entity* const entity, config::SettingMaster* const setting_master);
            static std::shared_ptr<datatypes::AnyValue> read_x(ontology::Entity* const entity, config::SettingMaster* const setting_master);
            static std::shared_ptr<datatypes::AnyValue> read_y(ontology::Entity* const entity, config::SettingMaster* const setting_master);
            static std::shared_ptr<datatypes::AnyValue> read_z(ontology::Entity* const entity, config::SettingMaster* const setting_master);

            static std::shared_ptr<datatypes::AnyValue> read_rho(ontology::Entity* const entity, config::SettingMaster* const setting_master);
            static std::shared_ptr<datatypes::AnyValue> read_theta(ontology::Entity* const entity, config::SettingMaster* const setting_master);
            static std::shared_ptr<datatypes::AnyValue> read_phi(ontology::Entity* const entity, config::SettingMaster* const setting_master);

            static std::shared_ptr<datatypes::AnyValue> read_up(ontology::Entity* const entity, config::SettingMaster* const setting_master);
            static std::shared_ptr<datatypes::AnyValue> read_right(ontology::Entity* const entity, config::SettingMaster* const setting_master);

            static std::shared_ptr<datatypes::AnyValue> read_horizontal_angle(ontology::Entity* const entity, config::SettingMaster* const setting_master);
            static std::shared_ptr<datatypes::AnyValue> read_vertical_angle(ontology::Entity* const entity, config::SettingMaster* const setting_master);

            static std::shared_ptr<datatypes::AnyValue> read_is_flight_mode_in_use(ontology::Entity* const entity, config::SettingMaster* const setting_master);

            // Public callbacks end here.

            friend class Setting;
            friend class ontology::Entity;
            friend class console::Console;

        private:
            ontology::Entity* parent;

            std::vector<config::Setting*> setting_pointer_vector;
            std::queue<int32_t> free_settingID_queue;
            int32_t number_of_settings;

            std::unordered_map<std::string, config::Setting*> setting_pointer_map;
    };
}

#endif
