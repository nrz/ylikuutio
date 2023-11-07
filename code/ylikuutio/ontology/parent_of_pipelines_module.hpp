// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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

#ifndef YLIKUUTIO_ONTOLOGY_PARENT_OF_PIPELINES_MODULE_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_PARENT_OF_PIPELINES_MODULE_HPP_INCLUDED

#include "generic_parent_module.hpp"
#include "pipeline_priority_queue.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <string>  // std::string

namespace yli::memory
{
    class GenericMemoryAllocator;
}

namespace yli::ontology
{
    class Registry;
    class Entity;

    class ParentOfPipelinesModule final : public yli::ontology::GenericParentModule
    {
        public:
            bool bind_child(yli::ontology::Entity& pipeline_child) noexcept override;
            void unbind_child(const std::size_t childID) noexcept override;

            // constructor.
            ParentOfPipelinesModule(
                    yli::ontology::Entity& entity,
                    yli::ontology::Registry& registry,
                    yli::memory::GenericMemoryAllocator& memory_allocator,
                    const std::string& name) noexcept;

            ParentOfPipelinesModule(const ParentOfPipelinesModule&) = delete;            // Delete copy constructor.
            ParentOfPipelinesModule& operator=(const ParentOfPipelinesModule&) = delete; // Delete copy assignment.

            // destructor.
            ~ParentOfPipelinesModule() = default;

        private:
            // `yli::ontology::PipelinePriorityQueue` is a priority queue for `Pipeline`s.
            // `yli::ontology::PipelinePriorityQueue` also has
            // a function `remove(const std::size_t childID)`.
            //
            // A priority queue is needed for `Pipeline`s in the future so that GPGPU
            // `Pipeline`s are rendered first so that their output textures can then be
            // used as input textures in other `Pipeline`s.
            //
            // Note: the output textures of GPGPU `Pipeline`s may be used as input textures
            // in later GPGPU `Pipeline`s. The rendering order within GPGPU `Pipeline`s is
            // according to the `childID` values, the GPGPU `Pipeline` with the smallest
            // `childID` first.
            yli::ontology::PipelinePriorityQueue pipeline_priority_queue;
    };
}

#endif
