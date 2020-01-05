// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "any_struct.hpp"
#include "code/ylikuutio/map/ylikuutio_map.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"

// Include standard headers
#include <cstddef>       // std::size_t
#include <memory>        // std::make_shared, std::shared_ptr
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

// `yli::common::AnyStruct` is a `class` which functions as a generic replacement for `struct`s.
// Further, it provides direct access to `AnyStruct`s which are children of current `AnyStruct`.
// This is implemented using recursion.
//
// `yli::common::AnyStruct` uses a notation also used by MATLAB and GNU Octave:
// `"foo.bar"` refers to `AnyStruct` named `"bar"`, which is a child of `AnyStruct` named `"foo"`.
// `"foo.bar.baz"` refers to `AnyStruct` named `"baz"`, which is a child of `"baz"`, which is a child of `"foo"`.
//
// All links are created using `std::shared_ptr`.

namespace yli
{
    namespace common
    {
        class AnyValue;

        AnyStruct::AnyStruct()
        {
            // constructor.
        }

        AnyStruct::~AnyStruct()
        {
            // destructor.
        }

        bool AnyStruct::enter_data(const std::string& target, std::shared_ptr<yli::common::AnyValue> any_value)
        {
            std::string first_part;
            std::size_t data_index = 0;
            return this->enter_data(target, data_index, any_value, first_part);
        }

        bool AnyStruct::erase_data(const std::string& target)
        {
            std::string first_part;
            std::size_t data_index = 0;
            return this->erase_data(target, data_index, first_part);
        }

        bool AnyStruct::check_if_exist(const std::string& target) const
        {
            std::string first_part;
            std::size_t data_index = 0;
            return this->check_if_exist(target, data_index, first_part);
        }

        std::shared_ptr<yli::common::AnyValue> AnyStruct::read_data(const std::string& target) const
        {
            std::string first_part;
            std::size_t data_index = 0;
            return this->read_data(target, data_index, first_part);
        }

        std::vector<std::string> AnyStruct::get_fieldnames() const
        {
            return yli::map::get_keys(this->values);
        }

        // The `private` functions begin here.

        bool AnyStruct::enter_data(
                const std::string& target,
                std::size_t& data_index,
                const std::shared_ptr<yli::common::AnyValue> any_value,
                std::string& first_part)
        {
            // Possible cases:
            // 1. `target` is an empty `std::string`.
            //     -> fail.
            // 2. `first_part` is a simple string (no special characters) and child with the name of `first_part` exists.
            //    -> insert into existing `first_part` child.
            //    -> success.
            // 3. `first_part` is a simple string (no special characters) and
            //    there is no child with the name of `first_part`.
            //    -> create a new `first_part` child.
            //    -> insert into the newly created child.
            //    -> success.
            // 4. `target` is a complex string, and `first_part` does not exist.
            //    -> create a new `first_part` child.
            //    -> call `enter_data` recursively.
            // 5. `target` is a complex string, and
            //     child with the name of `first_part` exists, and
            //     it is not `ANY_STRUCT_SHARED_PTR`.
            //    -> replace existing child with a `first_part` child.
            //    -> insert into the newly created child.
            //    -> call `enter_data` recursively.
            // 6. `target` is a complex string, and
            //     child with the name of `first_part` exists, and
            //     and it is `ANY_STRUCT_SHARED_PTR`.
            //    -> insert into existing `first_part` child.
            //    -> call `enter_data` recursively.
            const char separator = '.';
            const std::size_t current_data_index = data_index;
            yli::string::extract_string(target, data_index, first_part, separator);

            if (first_part.size() == 0)
            {
                // 1. `target` is an empty `std::string`.
                //     -> fail.
                return false;
            }

            if (current_data_index + first_part.size() == target.size())
            {
                if (this->values.count(first_part) == 1)
                {
                    // 2. `first_part` is a simple string (no special characters) and child with the name of `first_part` exists.
                    //    -> insert into existing `first_part` child.
                    //    -> success.
                    this->values[first_part] = any_value;
                    return true;
                }

                // 3. `first_part` is a simple string (no special characters) and
                //    there is no child with the name of `first_part`.
                //    -> create a new `first_part` child.
                //    -> insert into the newly created child.
                //    -> success.
                this->values[first_part] = any_value;
                return true;
            }

            // OK, this is a reference to a 'substruct'.
            // Advance data index by 1 past the comma `'.'` 'field' separator.
            data_index++;
            std::string last_part = target.substr(data_index);

            if (this->values.count(first_part) != 1)
            {
                // 4. `target` is a complex string, and `first_part` does not exist.
                //    -> create a new `first_part` child.
                //    -> call `enter_data` recursively.
                std::shared_ptr<yli::common::AnyStruct> child_any_struct_shared_ptr =
                    std::make_shared<yli::common::AnyStruct>();
                this->values[first_part] =
                    std::make_shared<yli::common::AnyValue>(child_any_struct_shared_ptr);
                return child_any_struct_shared_ptr->enter_data(target, data_index, any_value, last_part);
            }

            std::shared_ptr<yli::common::AnyValue> any_value_shared_ptr = this->values[first_part];

            if (any_value_shared_ptr->get_datatype() != "std::shared_ptr<yli::common::AnyStruct>")
            {
                // 5. `target` is a complex string, and
                //     child with the name of `first_part` exists, and
                //     it is not `ANY_STRUCT_SHARED_PTR`.
                //    -> replace existing child with a `first_part` child.
                //    -> insert into the newly created child.
                //    -> call `enter_data` recursively.
                std::shared_ptr<yli::common::AnyStruct> child_any_struct_shared_ptr =
                    std::make_shared<yli::common::AnyStruct>();
                this->values[first_part] =
                    std::make_shared<yli::common::AnyValue>(child_any_struct_shared_ptr);
                return child_any_struct_shared_ptr->enter_data(target, data_index, any_value, last_part);
            }

            // 6. `target` is a complex string, and
            //     child with the name of `first_part` exists, and
            //     and it is `ANY_STRUCT_SHARED_PTR`.
            //    -> insert into existing `first_part` child.
            //    -> call `enter_data` recursively.
            std::shared_ptr<yli::common::AnyStruct> child_any_struct_shared_ptr =
                any_value_shared_ptr->any_struct_shared_ptr;
            return child_any_struct_shared_ptr->enter_data(target, data_index, any_value, last_part);
        }

        bool AnyStruct::erase_data(
                const std::string& target,
                std::size_t& data_index,
                std::string& first_part)
        {
            // Possible cases:
            // 1. `target` is an empty `std::string`.
            //     -> fail.
            // 2. `first_part` does not exist.
            //    -> fail.
            // 3. `target` is a simple string (no special characters) and child with the name of `first_part` exists.
            //    -> erase the `first_part` child.
            //    -> success.
            // 4. `target` is a complex string, and
            //    child with the name of `first_part` exists, but
            //    it is not `ANY_STRUCT_SHARED_PTR`.
            //    -> fail.
            // 5. `target` is a complex string, and
            //    child with the name of `first_part` exists, and
            //    and it is `ANY_STRUCT_SHARED_PTR`.
            //    -> call `erase_data` recursively.

            const char separator = '.';
            std::size_t current_data_index = data_index;
            yli::string::extract_string(target, data_index, first_part, separator);

            if (first_part.size() == 0)
            {
                // 1. `target` is an empty `std::string`.
                //     -> fail.
                return false;
            }

            if (this->values.count(first_part) != 1)
            {
                // 2. `first_part` does not exist.
                //    -> fail.
                return false;
            }

            // OK, there is a matching 'field'.
            std::shared_ptr<yli::common::AnyValue> any_value_shared_ptr = this->values.at(first_part);

            if (current_data_index + first_part.size() == target.size())
            {
                // 3. `target` is a simple string (no special characters) and child with the name of `first_part` exists.
                //    -> erase the `first_part` child.
                //    -> success.
                this->values.erase(first_part);
                return true;
            }

            // OK, this is a reference to a 'substruct'.
            // Advance data index by 1 past the comma `'.'` 'field' separator.
            data_index++;

            std::shared_ptr<yli::common::AnyValue> any_value = this->values.at(first_part);

            if (any_value->get_datatype() != "std::shared_ptr<yli::common::AnyStruct>")
            {
                // 4. `target` is a complex string, and
                //    child with the name of `first_part` exists, but
                //    it is not `ANY_STRUCT_SHARED_PTR`.
                //    -> fail.
                return false;
            }

            // 5. `target` is a complex string, and
            //    child with the name of `first_part` exists, and
            //    and it is `ANY_STRUCT_SHARED_PTR`.
            //    -> call `erase_data` recursively.
            std::shared_ptr<yli::common::AnyStruct> child_any_struct = any_value->any_struct_shared_ptr;
            return child_any_struct->erase_data(target, data_index, first_part); // tail recursion.
        }

        bool AnyStruct::check_if_exist(
                const std::string& target,
                std::size_t& data_index,
                std::string& first_part) const
        {
            // Possible cases:
            // 1. `target` is an empty `std::string`.
            //     -> false.
            // 2. `first_part` does not exist.
            //    -> false.
            // 3. `target` is a simple string (no special characters) and child with the name of `target` exists.
            //    -> true.
            // 4. `target` is a complex string, and
            //    child with the name of `first_part` exists, and
            //    it is not `ANY_STRUCT_SHARED_PTR`.
            //    -> false.
            // 5. `target` is a complex string, and
            //    child with the name of `first_part` exists, and
            //    and it is `ANY_STRUCT_SHARED_PTR`.
            //    -> call `check_if_exist` recursively.
            const char separator = '.';
            std::size_t current_data_index = data_index;
            yli::string::extract_string(target, data_index, first_part, separator);

            if (first_part.size() == 0)
            {
                // 1. `target` is an empty `std::string`.
                //     -> fail.
                return false;
            }

            if (this->values.count(first_part) != 1)
            {
                // 2. `first_part` does not exist.
                //    -> false.
                return false;
            }

            // OK, there is a matching 'field'.
            std::shared_ptr<yli::common::AnyValue> any_value_shared_ptr = this->values.at(first_part);

            if (current_data_index + first_part.size() == target.size())
            {
                // 3. `target` is a simple string (no special characters) and child with the name of `target` exists.
                //    -> true.
                return true;
            }

            // OK, this is a reference to a 'substruct'.
            // Advance data index by 1 past the comma `'.'` 'field' separator.
            data_index++;

            std::shared_ptr<yli::common::AnyValue> any_value = this->values.at(first_part);

            if (any_value->get_datatype() != "std::shared_ptr<yli::common::AnyStruct>")
            {
                // 4. `target` is a complex string, and
                // child with the name of `first_part` exists, and
                // it is not `ANY_STRUCT_SHARED_PTR`.
                //    -> false.
                return false;
            }

            // 5. `target` is a complex string, and
            //    child with the name of `first_part` exists, and
            //    and it is `ANY_STRUCT_SHARED_PTR`.
            //    -> call `check_if_exist` recursively.
            std::shared_ptr<yli::common::AnyStruct> child_any_struct = any_value->any_struct_shared_ptr;
            return child_any_struct->check_if_exist(target, data_index, first_part); // tail recursion.
        }

        std::shared_ptr<yli::common::AnyValue> AnyStruct::read_data(
                const std::string& target,
                std::size_t& data_index,
                std::string& first_part) const
        {
            // Possible cases:
            // 1. `target` is an empty `std::string`.
            //     -> fail.
            // 2. `first_part` does not exist.
            //    -> fail.
            // 3. `target` is a simple string (no special characters) and child with the name of `target` exists.
            //    -> success.
            // 4. `target` is a complex string, and
            //    child with the name of `first_part` exists, and
            //    it is not `ANY_STRUCT_SHARED_PTR`.
            //    -> fail.
            // 5. `target` is a complex string, and
            //    child with the name of `first_part` exists, and
            //    and it is `ANY_STRUCT_SHARED_PTR`.
            //    -> call `read_data` recursively.
            const char separator = '.';
            std::size_t current_data_index = data_index;
            yli::string::extract_string(target, data_index, first_part, separator);

            if (first_part.size() == 0)
            {
                // 1. `target` is an empty `std::string`.
                //     -> fail.
                return nullptr;
            }

            if (this->values.count(first_part) != 1)
            {
                // 2. `first_part` does not exist.
                //    -> fail.
                return nullptr;
            }

            // OK, there is a matching 'field'.
            std::shared_ptr<yli::common::AnyValue> any_value_shared_ptr = this->values.at(first_part);

            if (current_data_index + first_part.size() == target.size())
            {
                // 3. `target` is a simple string (no special characters) and child with the name of `target` exists.
                //    -> success.
                return any_value_shared_ptr;
            }

            // OK, this is a reference to a 'substruct'.
            // Advance data index by 1 past the comma `'.'` 'field' separator.
            data_index++;

            std::shared_ptr<yli::common::AnyValue> any_value = this->values.at(first_part);

            if (any_value->get_datatype() != "std::shared_ptr<yli::common::AnyStruct>")
            {
                // 4. `target` is a complex string, and
                //    child with the name of `first_part` exists, and
                //    it is not `ANY_STRUCT_SHARED_PTR`.
                //    -> fail.
                return nullptr;
            }

            // 5. `target` is a complex string, and
            //    child with the name of `first_part` exists, and
            //    and it is `ANY_STRUCT_SHARED_PTR`.
            //    -> call `read_data` recursively.
            std::shared_ptr<yli::common::AnyStruct> child_any_struct = any_value->any_struct_shared_ptr;
            return child_any_struct->read_data(target, data_index, first_part); // tail recursion.
        }
    }
}
