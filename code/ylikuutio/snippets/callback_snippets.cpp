// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
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

#include "callback_snippets.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/ontology/generic_parent_module.hpp"
#include "code/ylikuutio/ontology/callback_engine.hpp"
#include "code/ylikuutio/ontology/callback_object.hpp"
#include "code/ylikuutio/ontology/callback_parameter.hpp"

// Include standard headers
#include <cmath>    // std::pow
#include <iostream> // std::cout, std::cerr
#include <optional> // std::optional
#include <stdint.h> // uint32_t etc.
#include <variant>  // std::holds_alternative

namespace yli::ontology
{
    class Universe;
}

namespace yli::snippets
{
    std::optional<yli::data::AnyValue> square(
            yli::ontology::Universe&,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject*,
            yli::ontology::GenericParentModule& input_parameters,
            const yli::data::AnyValue&)
    {
        if (input_parameters.get_number_of_children() != 1)
        {
            std::cout << "The size of input_parameter is " << input_parameters.get_number_of_children() << "\n";
            return std::nullopt;
        }

        const yli::data::AnyValue& any_value = static_cast<yli::ontology::CallbackParameter*>(input_parameters.get(0))->get_any_value();

        if (std::holds_alternative<int32_t>(any_value.data))
        {
            const int32_t factor = std::get<int32_t>(any_value.data);
            const int32_t squared = factor * factor;
            std::cout << "Square of (int32_t) " << factor << " is " << squared << ".\n";
            return yli::data::AnyValue(squared);
        }
        else if (std::holds_alternative<uint32_t>(any_value.data))
        {
            const uint32_t factor = std::get<uint32_t>(any_value.data);
            const uint32_t squared = factor * factor;
            std::cout << "Square of (uint32_t) " << factor << " is " << squared << ".\n";
            return yli::data::AnyValue(squared);
        }
        else if (std::holds_alternative<float>(any_value.data))
        {
            const float factor = std::get<float>(any_value.data);
            const float squared = factor * factor;
            std::cout << "Square of (float) " << factor << " is " << squared << ".\n";
            return yli::data::AnyValue(squared);
        }
        else if (std::holds_alternative<double>(any_value.data))
        {
            const double factor = std::get<double>(any_value.data);
            const double squared = factor * factor;
            std::cout << "Square of (double) " << factor << " is " << squared << ".\n";
            return yli::data::AnyValue(squared);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> square_last(
            yli::ontology::Universe&,
            yli::ontology::CallbackEngine* callback_engine,
            yli::ontology::CallbackObject*,
            yli::ontology::GenericParentModule& input_parameters,
            const yli::data::AnyValue&)
    {
        if (input_parameters.get_number_of_children() != 0)
        {
            std::cout << "The size of input_parameter is " << input_parameters.get_number_of_children() << "\n";
            return std::nullopt;
        }

        std::optional<yli::data::AnyValue> return_value_any_value = callback_engine->get_previous_return_value();

        if (!return_value_any_value)
        {
            std::cerr << "There is no previous return value!\n";
            return std::nullopt;
        }

        if (std::holds_alternative<int32_t>((*return_value_any_value).data))
        {
            const int32_t factor = std::get<int32_t>((*return_value_any_value).data);
            const int32_t squared = factor * factor;
            std::cout << "Square of (int32_t) " << factor << " is " << squared << ".\n";
            return yli::data::AnyValue(squared);
        }
        else if (std::holds_alternative<uint32_t>((*return_value_any_value).data))
        {
            const uint32_t factor = std::get<uint32_t>((*return_value_any_value).data);
            const uint32_t squared = factor * factor;
            std::cout << "Square of (uint32_t) " << factor << " is " << squared << ".\n";
            return yli::data::AnyValue(squared);
        }
        else if (std::holds_alternative<float>((*return_value_any_value).data))
        {
            const float factor = std::get<float>((*return_value_any_value).data);
            const float squared = factor * factor;
            std::cout << "Square of (float) " << factor << " is " << squared << ".\n";
            return yli::data::AnyValue(squared);
        }
        else if (std::holds_alternative<double>((*return_value_any_value).data))
        {
            const double factor = std::get<double>((*return_value_any_value).data);
            const double squared = factor * factor;
            std::cout << "Square of (double) " << factor << " is " << squared << ".\n";
            return yli::data::AnyValue(squared);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> expt(
            yli::ontology::Universe&,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject*,
            yli::ontology::GenericParentModule& input_parameters,
            const yli::data::AnyValue&)
    {
        if (input_parameters.get_number_of_children() != 2)
        {
            std::cout << "The size of input_parameter is " << input_parameters.get_number_of_children() << "\n";
            return std::nullopt;
        }

        const yli::data::AnyValue& base = static_cast<yli::ontology::CallbackParameter*>(input_parameters.get(0))->get_any_value();
        const yli::data::AnyValue& exponent = static_cast<yli::ontology::CallbackParameter*>(input_parameters.get(1))->get_any_value();

        if (std::holds_alternative<int32_t>(base.data) && std::holds_alternative<int32_t>(exponent.data))
        {
            const int32_t power = std::pow(std::get<int32_t>(base.data), std::get<int32_t>(exponent.data));
            std::cout << "(int32_t) " << std::get<int32_t>(base.data) << "^" << std::get<int32_t>(exponent.data) << " is " << power << ".\n";
            return yli::data::AnyValue(power);
        }
        else if (std::holds_alternative<uint32_t>(base.data) && std::holds_alternative<uint32_t>(exponent.data))
        {
            const uint32_t power = std::pow(std::get<uint32_t>(base.data), std::get<uint32_t>(exponent.data));
            std::cout << "(uint32_t) " << std::get<uint32_t>(base.data) << "^" << std::get<uint32_t>(exponent.data) << " is " << power << ".\n";
            return yli::data::AnyValue(power);
        }
        else if (std::holds_alternative<float>(base.data) && std::holds_alternative<float>(exponent.data))
        {
            const float power = std::pow(std::get<float>(base.data), std::get<float>(exponent.data));
            std::cout << "(float) " << std::get<float>(base.data) << "^" << std::get<float>(exponent.data) << " is " << power << ".\n";
            return yli::data::AnyValue(power);
        }
        else if (std::holds_alternative<double>(base.data) && std::holds_alternative<double>(exponent.data))
        {
            const double power = std::pow(std::get<double>(base.data), std::get<double>(exponent.data));
            std::cout << "(double) " << std::get<double>(base.data) << "^" << std::get<double>(exponent.data) << " is " << power << ".\n";
            return yli::data::AnyValue(power);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> expt_with_named_inputs(
            yli::ontology::Universe&,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject* callback_object,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&)
    {
        std::optional<yli::data::AnyValue> base = callback_object->get_any_value("base");
        std::optional<yli::data::AnyValue> exponent = callback_object->get_any_value("exponent");

        if (!base)
        {
            std::cout << "`base` does not contain a value!\n";
        }

        if (!exponent)
        {
            std::cout << "`exponent` does not contain a value!\n";
        }

        if (!base || !exponent)
        {
            return std::nullopt;
        }

        if (std::holds_alternative<int32_t>((*base).data) && std::holds_alternative<int32_t>((*exponent).data))
        {
            const int32_t power = std::pow(std::get<int32_t>((*base).data), std::get<int32_t>((*exponent).data));
            std::cout << "(int32_t) " << std::get<int32_t>((*base).data) << "^" << std::get<int32_t>((*exponent).data) << " is " << power << ".\n";
            return yli::data::AnyValue(power);
        }
        else if (std::holds_alternative<uint32_t>((*base).data) && std::holds_alternative<uint32_t>((*exponent).data))
        {
            const uint32_t power = std::pow(std::get<uint32_t>((*base).data), std::get<uint32_t>((*exponent).data));
            std::cout << "(uint32_t) " << std::get<uint32_t>((*base).data) << "^" << std::get<uint32_t>((*exponent).data) << " is " << power << ".\n";
            return yli::data::AnyValue(power);
        }
        else if (std::holds_alternative<float>((*base).data) && std::holds_alternative<float>((*exponent).data))
        {
            const float power = std::pow(std::get<float>((*base).data), std::get<float>((*exponent).data));
            std::cout << "(float) " << std::get<float>((*base).data) << "^" << std::get<float>((*exponent).data) << " is " << power << ".\n";
            return yli::data::AnyValue(power);
        }
        else if (std::holds_alternative<double>((*base).data) && std::holds_alternative<double>((*exponent).data))
        {
            const double power = std::pow(std::get<double>((*base).data), std::get<double>((*exponent).data));
            std::cout << "(double) " << std::get<double>((*base).data) << "^" << std::get<double>((*exponent).data) << " is " << power << ".\n";
            return yli::data::AnyValue(power);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> neg(
            yli::ontology::Universe&,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject*,
            yli::ontology::GenericParentModule& input_parameters,
            const yli::data::AnyValue&)
    {
        if (input_parameters.get_number_of_children() != 1)
        {
            std::cout << "The size of input_parameter is " << input_parameters.get_number_of_children() << "\n";
            return std::nullopt;
        }

        const yli::data::AnyValue& any_value = static_cast<yli::ontology::CallbackParameter*>(input_parameters.get(0))->get_any_value();

        if (std::holds_alternative<int32_t>(any_value.data))
        {
            const int32_t product = -1 * std::get<int32_t>(any_value.data);
            std::cout << "-1 * (int32_t) " << std::get<int32_t>(any_value.data) << " is " << product << ".\n";
            return yli::data::AnyValue(product);
        }
        else if (std::holds_alternative<float>(any_value.data))
        {
            const float product = -1.0 * std::get<float>(any_value.data);
            std::cout << "-1 * (float) " << std::get<float>(any_value.data) << " is " << product << ".\n";
            return yli::data::AnyValue(product);
        }
        else if (std::holds_alternative<double>(any_value.data))
        {
            const double product = -1.0 * std::get<double>(any_value.data);
            std::cout << "-1 * (double) " << std::get<double>(any_value.data) << " is " << product << ".\n";
            return yli::data::AnyValue(product);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> nop(
            yli::ontology::Universe&,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject*,
            yli::ontology::GenericParentModule& /* input_parameters */,
            const yli::data::AnyValue&)
    {
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> return_uint32_t_deadbeef(
            yli::ontology::Universe&,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject*,
            yli::ontology::GenericParentModule& /* input_parameters */,
            const yli::data::AnyValue&)
    {
        uint32_t deadbeef { 0xdeadbeef };
        return yli::data::AnyValue(deadbeef);
    }
}
