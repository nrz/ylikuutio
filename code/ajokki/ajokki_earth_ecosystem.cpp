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

#include "code/ylikuutio/ontology/ecosystem.hpp"
#include "code/ylikuutio/ontology/shader.hpp"
#include "code/ylikuutio/ontology/symbiosis.hpp"
#include "code/ylikuutio/ontology/ecosystem_struct.hpp"
#include "code/ylikuutio/ontology/shader_struct.hpp"
#include "code/ylikuutio/ontology/model_struct.hpp"
#include "code/ylikuutio/ontology/entity_factory.hpp"

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr

namespace yli::ontology
{
    class Entity;
}

namespace ajokki
{
    yli::ontology::Ecosystem* create_earth_ecosystem(yli::ontology::EntityFactory* const entity_factory)
    {
        // Earth `Ecosystem` begins here.

        std::cout << "Creating yli::ontology::Entity* earth_ecosystem and its contents ...\n";
        yli::ontology::EcosystemStruct earth_ecosystem_struct;
        earth_ecosystem_struct.global_name = "earth_ecosystem";
        yli::ontology::Entity* const earth_ecosystem_entity = entity_factory->create_ecosystem(earth_ecosystem_struct);

        std::cout << "Creating yli::ontology::Ecosystem* earth_ecosystem ...\n";
        yli::ontology::Ecosystem* const earth_ecosystem = dynamic_cast<yli::ontology::Ecosystem*>(earth_ecosystem_entity);

        if (earth_ecosystem == nullptr)
        {
            return nullptr;
        }

        // Create the shader, store it in `earth_shader`.
        yli::ontology::ShaderStruct earth_shader_struct;
        earth_shader_struct.parent = earth_ecosystem;
        earth_shader_struct.global_name = "earth_shader";
        earth_shader_struct.local_name = "helsinki_regular_shader";
        earth_shader_struct.vertex_shader = "standard_shading.vert";
        earth_shader_struct.fragment_shader = "standard_shading.frag";

        std::cout << "Creating yli::ontology::Entity* earth_shader_entity ...\n";
        yli::ontology::Entity* const earth_shader_entity = entity_factory->create_shader(earth_shader_struct);
        std::cout << "Creating yli::ontology::Shader* earth_shader ...\n";
        yli::ontology::Shader* const earth_shader = dynamic_cast<yli::ontology::Shader*>(earth_shader_entity);

        if (earth_shader == nullptr)
        {
            std::cerr << "Failed to create `Shader`.\n";
            return nullptr;
        }

        yli::ontology::ModelStruct turbo_polizei_png_model_struct;
        turbo_polizei_png_model_struct.parent = earth_ecosystem;
        turbo_polizei_png_model_struct.shader = earth_shader;
        turbo_polizei_png_model_struct.model_file_format = "fbx";
        turbo_polizei_png_model_struct.model_filename = "turbo_polizei_png_textures.fbx";

        std::cout << "Creating yli::ontology::Entity* turbo_polizei_png_symbiosis_entity ...\n";
        yli::ontology::Entity* const turbo_polizei_png_symbiosis_entity = entity_factory->create_symbiosis(turbo_polizei_png_model_struct);

        std::cout << "Creating yli::ontology::Symbiosis* turbo_polizei_png_symbiosis ...\n";
        yli::ontology::Symbiosis* const turbo_polizei_png_symbiosis = dynamic_cast<yli::ontology::Symbiosis*>(turbo_polizei_png_symbiosis_entity);

        if (turbo_polizei_png_symbiosis == nullptr)
        {
            std::cerr << "Failed to create turbo_polizei_png Symbiosis.\n";
            return nullptr;
        }

        turbo_polizei_png_symbiosis->set_global_name("turbo_polizei_png_symbiosis");

        return earth_ecosystem;
    }
}
