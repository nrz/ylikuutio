#ifndef __CALLBACK_PARAMETER_HPP_INCLUDED
#define __CALLBACK_PARAMETER_HPP_INCLUDED

#include "callback_object.hpp"
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>       // std::size_t
#include <memory>        // std::make_shared, std::shared_ptr
#include <string>        // std::string

namespace yli
{
    namespace ontology
    {
        class Universe;
    }

    namespace callback_system
    {
        class CallbackParameter
        {
            public:

                // constructor.
                CallbackParameter(const std::string& name, std::shared_ptr<yli::datatypes::AnyValue> any_value, const bool is_reference, yli::callback_system::CallbackObject* const parent);

                // destructor.
                ~CallbackParameter();

                // getter.
                std::shared_ptr<yli::datatypes::AnyValue> get_any_value() const;

                friend class CallbackObject;

                std::size_t childID;            // callback parameter ID, returned by `yli::callback_system::CallbackObject->get_callback_parameterID()`.

            private:
                void bind_to_parent();

                yli::callback_system::CallbackObject* parent; // pointer to the callback object.

                std::string name;
                std::shared_ptr<yli::datatypes::AnyValue> any_value; // this is `private` to make sure that someone does not overwrite it.
                bool is_reference;              // if true, the value is read from the hashmap. if false, then the value is read from the union.
        };
    }
}

#endif
