// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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

#ifndef __YLIKUUTIO_ONTOLOGY_PARENT_OF_SHADERS_MODULE_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_PARENT_OF_SHADERS_MODULE_HPP_INCLUDED

#include "generic_parent_module.hpp"
#include "shader_priority_queue.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <string>  // std::string

namespace yli::ontology
{
    class Registry;
    class Entity;

    class ParentOfShadersModule: public yli::ontology::GenericParentModule
    {
        public:
            bool bind_child(yli::ontology::Entity* const shader_child) override;
            bool unbind_child(std::size_t childID) override;

            // constructor.
            ParentOfShadersModule(yli::ontology::Entity* const entity, yli::ontology::Registry* const registry, const std::string& name);

            ParentOfShadersModule(const ParentOfShadersModule&) = delete;            // Delete copy constructor.
            ParentOfShadersModule& operator=(const ParentOfShadersModule&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~ParentOfShadersModule();

        private:
            // `yli::ontology::ShaderPriorityQueue` is a priority queue for `Shader`s.
            // `yli::ontology::ShaderPriorityQueue` also has
            // a function `remove(const std::size_t childID)`.
            //
            // A priority queue is needed for `Shader`s in the future so that GPGPU
            // `Shader`s are rendered first so that their output textures can then be
            // used as input textures in other `Shader`s.
            //
            // Note: the output textures of GPGPU `Shader`s may be used as input textures
            // in later GPGPU `Shader`s. The rendering order within GPGPU `Shader`s is
            // according to the `childID` values, the GPGPU `Shader` with the smallest
            // `childID` first.
            yli::ontology::ShaderPriorityQueue shader_priority_queue;
    };
}

#endif
