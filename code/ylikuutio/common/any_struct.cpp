#include "any_struct.hpp"

// Include standard headers
#include <memory>        // std::make_shared, std::shared_ptr
#include <string>        // std::string
#include <unordered_map> // std::unordered_map

namespace yli
{
    namespace datatypes
    {
        class AnyValue;

        void AnyStruct::enter_data(const std::string& target, std::shared_ptr<yli::datatypes::AnyValue> any_value)
        {
            // TODO: implement this function!
        }

        std::shared_ptr<yli::datatypes::AnyValue> AnyStruct::read_data(const std::string& target)
        {
            // TODO: implement this function!
            return nullptr;
        }

        void AnyStruct::erase_data(const std::string& target)
        {
            // TODO: implement this function!
        }
    }
}

