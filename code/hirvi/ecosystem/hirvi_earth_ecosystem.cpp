// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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

#include "code/hirvi/hirvi.hpp"
#include "code/ylikuutio/ontology/ecosystem.hpp"
#include "code/ylikuutio/ontology/pipeline.hpp"
#include "code/ylikuutio/ontology/symbiosis.hpp"
#include "code/ylikuutio/ontology/request.hpp"
#include "code/ylikuutio/ontology/ecosystem_struct.hpp"
#include "code/ylikuutio/ontology/pipeline_struct.hpp"
#include "code/ylikuutio/ontology/symbiosis_struct.hpp"

// Include standard headers
#include <iostream> // std::cout, std::cerr

namespace yli::ontology
{
    class Entity;
}

namespace hirvi
{
    using namespace yli::ontology;

    Ecosystem* HirviApplication::create_earth_ecosystem()
    {
        // Earth `Ecosystem` begins here.

        std::cout << "Creating Entity* earth_ecosystem and its contents ...\n";
        EcosystemStruct earth_ecosystem_struct;
        earth_ecosystem_struct.global_name = "earth_ecosystem";
        std::cout << "Creating Ecosystem* earth_ecosystem ...\n";
        Ecosystem* const earth_ecosystem = this->entity_factory.create_ecosystem(earth_ecosystem_struct);

        if (earth_ecosystem == nullptr)
        {
            return nullptr;
        }

        // Create the pipeline, store it in `earth_pipeline`.
        PipelineStruct earth_pipeline_struct { Request<Ecosystem>("earth_ecosystem") };
        earth_pipeline_struct.global_name = "earth_pipeline";
        earth_pipeline_struct.local_name = "helsinki_regular_pipeline";
        earth_pipeline_struct.vertex_shader = "standard_shading.vert";
        earth_pipeline_struct.fragment_shader = "standard_shading.frag";

        std::cout << "Creating Pipeline* earth_pipeline ...\n";
        Pipeline* const earth_pipeline = this->entity_factory.create_pipeline(earth_pipeline_struct);

        if (earth_pipeline == nullptr)
        {
            std::cerr << "Failed to create `Pipeline`.\n";
            return nullptr;
        }

        SymbiosisStruct turbo_polizei_png_symbiosis_struct { Request<Ecosystem>("earth_ecosystem"), Request<Pipeline>("earth_pipeline") };
        turbo_polizei_png_symbiosis_struct.model_file_format = "fbx";
        turbo_polizei_png_symbiosis_struct.model_filename = "turbo_polizei_png_textures.fbx";

        std::cout << "Creating Symbiosis* turbo_polizei_png_symbiosis ...\n";
        Symbiosis* const turbo_polizei_png_symbiosis = this->entity_factory.create_symbiosis(turbo_polizei_png_symbiosis_struct);

        if (turbo_polizei_png_symbiosis == nullptr)
        {
            std::cerr << "Failed to create turbo_polizei_png Symbiosis.\n";
            return nullptr;
        }

        turbo_polizei_png_symbiosis->set_global_name("turbo_polizei_png_symbiosis");

        return earth_ecosystem;
    }
}
