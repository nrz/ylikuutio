#include "ajokki_cleanup_callbacks.hpp"
#include "code/ylikuutio/callback_system/callback_parameter.hpp"
#include "code/ylikuutio/callback_system/callback_object.hpp"
#include "code/ylikuutio/callback_system/callback_engine.hpp"
#include "code/ylikuutio/callback_system/callback_magic_numbers.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/font2D.hpp"
#include "code/ylikuutio/common/any_value.hpp"

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <memory>   // std::make_shared, std::shared_ptr
#include <vector>   // std::vector

namespace ajokki
{
    std::shared_ptr<datatypes::AnyValue> full_cleanup(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>&)
    {
        std::cout << "Cleaning up.\n";

        std::shared_ptr<datatypes::AnyValue> any_value_universe = std::make_shared<datatypes::AnyValue>(*callback_object->get_arg(0));
        std::shared_ptr<datatypes::AnyValue> any_value_font2D_pointer = std::make_shared<datatypes::AnyValue>(*callback_object->get_any_value("font2D_pointer"));

        if (any_value_universe->type == datatypes::UNIVERSE_POINTER)
        {
            delete any_value_universe->universe;
        }
        else
        {
            std::cerr << "Invalid datatype: " << any_value_universe->type << ", should be " << datatypes::UNIVERSE_POINTER << "\n";
        }

        if (any_value_font2D_pointer->type == datatypes::TEXT2D_POINTER)
        {
            // Delete the text's VBO, the shader and the texture
            delete any_value_font2D_pointer->font2D_pointer;
        }
        else
        {
            std::cerr << "Invalid datatype: " << any_value_font2D_pointer->type << ", should be " << datatypes::TEXT2D_POINTER << "\n";
        }

        return nullptr;
    }
}
