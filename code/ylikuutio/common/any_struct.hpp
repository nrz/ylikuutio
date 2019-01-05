#ifndef __ANY_STRUCT_HPP_INCLUDED
#define __ANY_STRUCT_HPP_INCLUDED

// Include standard headers
#include <cstddef>       // std::size_t
#include <memory>        // std::make_shared, std::shared_ptr
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

// The hierachical 'struct' tree of Ylikuutio are based on classes
// `yli::datatypes::AnyStruct` and `yli::datatypes::AnyValue`.
//
// The root of this tree is always `yli::datatypes::AnyStruct`.
// Each `yli::datatypes::AnyStruct` has 0 or more `yli::datatypes::AnyValue`s as its named child nodes,
// stored in `std::unordered_map` called `values`.  The name of the child node is stored as a key.
//
// Each child can therefore have any `datatype` supported by `yli::datatypes::AnyValue`.
// If the `datatype` of a child is `ANY_STRUCT_SHARED_PTR`,
// then the child itself contains `yli::datatypes::AnyStruct`.

namespace yli
{
    namespace datatypes
    {
        class AnyValue;

        class AnyStruct
        {
            public:
                // constructor.
                AnyStruct();

                // destructor.
                ~AnyStruct();

                bool enter_data(const std::string& target, std::shared_ptr<yli::datatypes::AnyValue> any_value);
                bool erase_data(const std::string& target);
                bool check_if_exist(const std::string& target) const;
                std::shared_ptr<yli::datatypes::AnyValue> read_data(const std::string& target) const;
                std::vector<std::string> get_fieldnames() const;

            private:
                bool enter_data(
                        const std::string& target,
                        std::size_t& data_index,
                        std::shared_ptr<yli::datatypes::AnyValue> any_value,
                        std::string& first_part);

                bool erase_data(
                        const std::string& target,
                        std::size_t& data_index,
                        std::string& first_part);

                bool check_if_exist(
                        const std::string& target,
                        std::size_t& data_index,
                        std::string& first_part) const;

                std::shared_ptr<yli::datatypes::AnyValue> read_data(
                        const std::string& target,
                        std::size_t& data_index,
                        std::string& first_part) const;

                std::unordered_map<std::string, std::shared_ptr<yli::datatypes::AnyValue>> values;
        };
    }
}

#endif
