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

#include "parent_of_pipelines_module.hpp"
#include "generic_parent_module.hpp"
#include "entity.hpp"
#include "pipeline.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <string>   // std::string

namespace yli::memory
{
    class GenericMemoryAllocator;
}

namespace yli::ontology
{
    class Registry;

    bool ParentOfPipelinesModule::bind_child(yli::ontology::Entity& pipeline_child) noexcept
    {
        if (this->GenericParentModule::bind_child(pipeline_child))
        {
            // `pipeline` needs to be added to the priority queue as well.
            this->pipeline_priority_queue.push(static_cast<yli::ontology::Pipeline*>(&pipeline_child));
            return true; // Binding successful.
        }

        return false; // Binding failed.
    }

    void ParentOfPipelinesModule::unbind_child(const std::size_t childID) noexcept
    {
        this->GenericParentModule::unbind_child(childID);

        // `Pipeline` needs to be removed from the priority queue as well.
        this->pipeline_priority_queue.remove(childID);
    }

    ParentOfPipelinesModule::ParentOfPipelinesModule(
            yli::ontology::Entity& entity,
            yli::ontology::Registry& registry,
            yli::memory::GenericMemoryAllocator& memory_allocator,
            const std::string& name) noexcept
        : GenericParentModule(entity, registry, memory_allocator, name)
    {
        // constructor.
    }
}
