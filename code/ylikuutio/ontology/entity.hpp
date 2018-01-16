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
            Entity(ontology::Universe* universe);

            // destructor.
            virtual ~Entity();

            std::string get_type() const;

            virtual ontology::Universe* get_universe();
            config::SettingMaster* get_setting_master();
            void set_setting_master(config::SettingMaster* setting_master);

            virtual ontology::Entity* get_parent() const = 0;
            virtual int32_t get_number_of_children() const = 0;
            virtual int32_t get_number_of_descendants() const = 0;

            template<class T1>
                friend void set_name(const std::string& name, T1 entity);

        protected:
            void prerender() const;
            void postrender() const;

            ontology::Universe* universe;          // pointer to `Universe`.
            config::SettingMaster* setting_master; // pointer to `SettingMaster`.
            std::vector<void*> child_vector_pointers_vector;
            int32_t childID;

            std::string type;

            std::string name; // name of this entity.

            PreRenderCallback prerender_callback;
            PostRenderCallback postrender_callback;
    };
}
#endif
