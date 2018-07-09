#ifndef __READ_CALLBACK_HPP_INCLUDED
#define __READ_CALLBACK_HPP_INCLUDED

#include "code/ylikuutio/common/any_value.hpp"

// Include standard headers
#include <memory> // std::make_shared, std::shared_ptr

namespace yli
{
    namespace config
    {
        class SettingMaster;
    }
}

namespace yli
{
    namespace ontology
    {
        class Entity;
    }
}

typedef std::shared_ptr<datatypes::AnyValue> (*ReadCallback) (yli::ontology::Entity* entity, yli::config::SettingMaster* setting_master);

#endif
