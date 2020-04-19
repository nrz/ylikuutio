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

#ifndef __ANY_STRUCT_HPP_INCLUDED
#define __ANY_STRUCT_HPP_INCLUDED

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
// For example, `set` can be used for setting values and `get` for getting values:
// `set foo.bar.baz 1.0`
// `get foo.bar.baz`
//
// All links are created using `std::shared_ptr`.
//
// The hierachical 'struct' tree of Ylikuutio are based on classes
// `yli::common::AnyStruct` and `yli::common::AnyValue`.
//
// The root of this tree is always `yli::common::AnyStruct`.
// Each `yli::common::AnyStruct` has 0 or more `yli::common::AnyValue`s as its named child nodes,
// stored in `std::unordered_map` called `values`.  The name of the child node is stored as a key.
//
// Each child can therefore have any `datatype` supported by `yli::common::AnyValue`.
// If the `datatype` of a child is `ANY_STRUCT_SHARED_PTR`,
// then the child itself contains `yli::common::AnyStruct`.

namespace yli
{
    namespace common
    {
        class AnyValue;

        class AnyStruct
        {
            public:
                // constructor.
                AnyStruct();

                // destructor.
                ~AnyStruct();

                bool enter_data(const std::string& target, std::shared_ptr<yli::common::AnyValue> any_value);
                bool erase_data(const std::string& target);
                bool check_if_exist(const std::string& target) const;
                std::shared_ptr<yli::common::AnyValue> read_data(const std::string& target) const;
                std::vector<std::string> get_fieldnames() const;

            private:
                bool enter_data(
                        const std::string& target,
                        std::size_t& data_index,
                        const std::shared_ptr<yli::common::AnyValue> any_value,
                        std::string& first_part);

                bool erase_data(
                        const std::string& target,
                        std::size_t& data_index,
                        std::string& first_part);

                bool check_if_exist(
                        const std::string& target,
                        std::size_t& data_index,
                        std::string& first_part) const;

                std::shared_ptr<yli::common::AnyValue> read_data(
                        const std::string& target,
                        std::size_t& data_index,
                        std::string& first_part) const;

                std::unordered_map<std::string, std::shared_ptr<yli::common::AnyValue>> values;
        };
    }
}

#endif
