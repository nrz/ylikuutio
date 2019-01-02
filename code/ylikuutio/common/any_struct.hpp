#ifndef __ANY_STRUCT_HPP_INCLUDED
#define __ANY_STRUCT_HPP_INCLUDED

// Include standard headers
#include <memory>        // std::make_shared, std::shared_ptr
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

namespace yli
{
    namespace datatypes
    {
        class AnyValue;

        class AnyStruct
        {
            public:
                void enter_data(const std::string& target, std::shared_ptr<yli::datatypes::AnyValue> any_value);
                std::shared_ptr<yli::datatypes::AnyValue> read_data(const std::string& target);
                void erase_data(const std::string& target);
                std::vector<std::string> get_fieldnames() const;

            private:
                std::unordered_map<std::string, std::shared_ptr<yli::datatypes::AnyValue>> values;
        };
    }
}

#endif
