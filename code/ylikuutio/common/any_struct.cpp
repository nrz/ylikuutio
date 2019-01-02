#include "any_struct.hpp"
#include "code/ylikuutio/map/ylikuutio_map.hpp"

// Include standard headers
#include <memory>        // std::make_shared, std::shared_ptr
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

// `yli::datatypes::AnyStruct` is a `class` which functions as a generic replacement for `struct`s.
// Further, it provides direct access to `AnyStruct`s which are children of current `AnyStruct`.
// This is implemented using recursion.
//
// `yli::datatypes::AnyStruct` uses a notation also used by MATLAB and GNU Octave:
// `"foo.bar"` refers to `AnyStruct` named `"bar"`, which is a child of `AnyStruct` named `"foo"`.
// `"foo.bar.baz"` refers to `AnyStruct` named `"baz"`, which is a child of `"baz"`, which is a child of `"foo"`.
//
// All links are created using `std::shared_ptr`.

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

        std::vector<std::string> AnyStruct::get_fieldnames() const
        {
            return yli::map::get_keys(&this->values);
        }
    }
}

