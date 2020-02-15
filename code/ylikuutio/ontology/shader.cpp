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

#include "shader.hpp"
#include "scene.hpp"
#include "universe.hpp"
#include "render_templates.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

namespace yli
{
    namespace ontology
    {
        class Species;

        void Shader::bind_to_parent()
        {
            // Requirements:
            // `this->parent` must not be `nullptr`.
            yli::ontology::Scene* const scene = this->parent;

            if (scene == nullptr)
            {
                std::cerr << "ERROR: `Shader::bind_to_parent`: `scene` is `nullptr`!\n";
                return;
            }

            // Get `childID` from the `Scene` and set pointer to this `Shader`.
            scene->bind_Shader(this);
        }

        void Shader::bind_to_new_parent(yli::ontology::Scene* const new_parent)
        {
            // This method sets pointer to this `Shader` to `nullptr`, sets `parent` according to the input,
            // and requests a new `childID` from the new `Scene`.
            //
            // requirements:
            // `this->parent` must not be `nullptr`.
            // `new_parent` must not be `nullptr`.

            yli::ontology::Scene* const scene = this->parent;

            if (scene == nullptr)
            {
                std::cerr << "ERROR: `Shader::bind_to_new_parent`: `scene` is `nullptr`!\n";
                return;
            }

            if (new_parent == nullptr)
            {
                std::cerr << "ERROR: `Shader::bind_to_new_parent`: `new_parent` is `nullptr`!\n";
                return;
            }

            // Unbind from the old parent `Scene`.
            this->parent->unbind_Shader(this->childID);

            // Get `childID` from `Scene` and set pointer to this `Shader`.
            this->parent = new_parent;
            this->parent->bind_Shader(this);
        }

        void Shader::bind_to_new_parent(yli::ontology::Entity* const new_parent)
        {
            // this method sets pointer to this `Shader` to `nullptr`, sets `parent` according to the input,
            // and requests a new `childID` from the new `Scene`.
            //
            // requirements:
            // `this->parent` must not be `nullptr`.
            // `new_parent` must not be `nullptr`.

            yli::ontology::Scene* const scene = dynamic_cast<yli::ontology::Scene*>(new_parent);

            if (scene == nullptr)
            {
                std::cerr << "ERROR: `Shader::bind_to_new_parent`: `new_parent` is not `yli::ontology::Scene*`!\n";
                return;
            }

            this->bind_to_new_parent(scene);
        }

        Shader::~Shader()
        {
            // destructor.
            std::cout << "`Shader` with childID " << std::dec << this->childID << " will be destroyed.\n";

            // Requirements for further actions (except `glDeleteProgram`):
            // `this->parent` must not be `nullptr`.

            yli::ontology::Scene* const scene = this->parent;

            if (scene == nullptr)
            {
                std::cerr << "ERROR: `Shader::~Shader`: `scene` is `nullptr`!\n";
            }
            else
            {
                // Set pointer to this `Shader` to `nullptr`.
                scene->unbind_Shader(this->childID);
            }

            glDeleteProgram(this->programID);
        }

        void Shader::render()
        {
            if (!this->should_be_rendered)
            {
                return;
            }

            this->prerender();

            // [Re]bind `programID` shader.
            glUseProgram(this->programID);

            // `glUniformMatrix4fv` doesn't change between objects,
            // so this can be done once for all objects that use the same `programID`.
            glUniformMatrix4fv(this->view_matrixID, 1, GL_FALSE, &this->universe->get_view_matrix()[0][0]);

            // Render this `Shader` by calling `render()` function of each `ComputeTask`, each `Material`, and each `Symbiosis`.
            yli::ontology::render_children<yli::ontology::Entity*>(this->parent_of_compute_tasks.child_pointer_vector);
            yli::ontology::render_children<yli::ontology::Entity*>(this->parent_of_materials.child_pointer_vector);
            yli::ontology::render_children<yli::ontology::Entity*>(this->parent_of_symbioses.child_pointer_vector);

            this->postrender();
        }

        yli::ontology::Entity* Shader::get_parent() const
        {
            return this->parent;
        }

        std::size_t Shader::get_number_of_children() const
        {
            return this->parent_of_compute_tasks.get_number_of_children() +
                this->parent_of_materials.get_number_of_children() +
                this->parent_of_symbioses.get_number_of_children();
        }

        std::size_t Shader::get_number_of_descendants() const
        {
            return yli::ontology::get_number_of_descendants(this->parent_of_compute_tasks.child_pointer_vector) +
                yli::ontology::get_number_of_descendants(this->parent_of_materials.child_pointer_vector) +
                yli::ontology::get_number_of_descendants(this->parent_of_symbioses.child_pointer_vector);
        }

        uint32_t Shader::get_programID() const
        {
            return this->programID;
        }

        uint32_t Shader::get_matrixID() const
        {
            return this->matrixID;
        }

        uint32_t Shader::get_model_matrixID() const
        {
            return this->model_matrixID;
        }

        void Shader::set_terrain_species(yli::ontology::Species* const terrain_species)
        {
            yli::ontology::Scene* const scene_parent = this->parent;

            if (scene_parent != nullptr)
            {
                scene_parent->set_terrain_species(terrain_species);
            }
        }
    }
}
