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

#ifndef YLIKUUTIO_ONTOLOGY_LISP_FUNCTION_ARG_EXTRACTOR_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_LISP_FUNCTION_ARG_EXTRACTOR_HPP_INCLUDED

#include "function_arg_extractor.hpp"
#include "code/ylikuutio/data/wrap.hpp"

// Include standard headers
#include <tuple>      // std::tuple

namespace yli::lisp
{
    template<typename F>
        struct FunctionArgExtractor;

    template<typename R, typename... Args>
        struct FunctionArgExtractor<R(Args...)>
        {
            using ArgTuple = std::tuple<typename yli::data::Wrap<Args>::type...>;
        };
}

#endif
