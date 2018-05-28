#ifndef __ENTITY_HPP_INCLUDED
#define __ENTITY_HPP_INCLUDED

#include "code/ylikuutio/common/globals.hpp"

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace config
{
    class SettingMaster;
}

namespace ontology
{
    class Universe;

    class Entity
    {
        public:
            // constructor.
            Entity(ontology::Universe* const universe);

            // destructor.
            virtual ~Entity();

            std::string get_type() const;

            bool get_can_be_erased() const;

            ontology::Universe* get_universe() const;
            config::SettingMaster* get_setting_master() const;
            void set_setting_master(config::SettingMaster* const setting_master);

            virtual ontology::Entity* get_parent() const = 0;
            virtual int32_t get_number_of_children() const = 0;
            virtual int32_t get_number_of_descendants() const = 0;

            void set_name(const std::string& name);

        protected:
            void prerender() const;
            void postrender() const;

            ontology::Universe* universe;          // pointer to `Universe`.
            config::SettingMaster* setting_master; // pointer to `SettingMaster`.
            std::vector<void*> child_vector_pointers_vector;
            int32_t childID;

            std::string type;

            std::string name; // name of this entity.

            bool can_be_erased;

            PreRenderCallback prerender_callback;
            PostRenderCallback postrender_callback;
    };
}
#endif
