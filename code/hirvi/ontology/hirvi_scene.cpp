// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2026 Antti Nuortimo.
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

#include "hirvi_scene.hpp"
#include "police_control_center.hpp"
#include "hirvi_scene_struct.hpp"
#include "police_control_center_struct.hpp"
#include "code/hirvi/hirvi.hpp"
#include "code/hirvi/data/datatype.hpp"
#include "code/ylikuutio/ontology/get_number_of_descendants.hpp"

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class GenericParentModule;
    class Universe;
}

namespace hirvi::ontology
{
    using namespace yli::core;
    using namespace yli::ontology;

    HirviScene::HirviScene(
        Application& application,
        Universe& universe,
        const HirviSceneStruct& hirvi_scene_struct,
        GenericParentModule* const universe_parent_module,
        const core::HirviCore& hirvi_core)
        : Scene(application, universe, hirvi_scene_struct, universe_parent_module),
          parent_of_police_control_centers(
              *this,
              this->registry,
              "police_control_centers"),
          parent_of_elks(
              *this,
              this->registry,
              "elks"),
          parent_of_police_bears(
              *this,
              this->registry,
              "police_bears"),
          parent_of_police_cars(
              *this,
              this->registry,
              "police_cars"),
          parent_of_police_dogs(
              *this,
              this->registry,
              "police_dogs"),
          parent_of_police_helicopters(
              *this,
              this->registry,
              "police_helicopters"),
          parent_of_police_horses(
              *this,
              this->registry,
              "police_horses"),
          parent_of_police_trains(
              *this,
              this->registry,
              "police_trains"),
          parent_of_police_trams(
              *this,
              this->registry,
              "police_trams")
    {
        this->create_police_control_centers(hirvi_core, hirvi_scene_struct.police_control_center_structs);

        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "hirvi::ontology::HirviScene*";
    }

    std::size_t HirviScene::get_number_of_children() const
    {
        return this->Scene::get_number_of_children() +
               this->parent_of_police_control_centers.get_number_of_children() +
               this->parent_of_elks.get_number_of_children() +
               this->parent_of_police_bears.get_number_of_children() +
               this->parent_of_police_cars.get_number_of_children() +
               this->parent_of_police_dogs.get_number_of_children() +
               this->parent_of_police_helicopters.get_number_of_children() +
               this->parent_of_police_horses.get_number_of_children() +
               this->parent_of_police_trains.get_number_of_children() +
               this->parent_of_police_trams.get_number_of_children();
    }

    std::size_t HirviScene::get_number_of_descendants() const
    {
        return this->Scene::get_number_of_descendants() +
               ontology::get_number_of_descendants(this->parent_of_police_control_centers.child_pointer_vector) +
               ontology::get_number_of_descendants(this->parent_of_elks.child_pointer_vector) +
               ontology::get_number_of_descendants(this->parent_of_police_bears.child_pointer_vector) +
               ontology::get_number_of_descendants(this->parent_of_police_cars.child_pointer_vector) +
               ontology::get_number_of_descendants(this->parent_of_police_dogs.child_pointer_vector) +
               ontology::get_number_of_descendants(this->parent_of_police_helicopters.child_pointer_vector) +
               ontology::get_number_of_descendants(this->parent_of_police_horses.child_pointer_vector) +
               ontology::get_number_of_descendants(this->parent_of_police_trains.child_pointer_vector) +
               ontology::get_number_of_descendants(this->parent_of_police_trams.child_pointer_vector);
    }

    void HirviScene::create_police_control_centers(const core::HirviCore& hirvi_core,
                                                   const std::vector<PoliceControlCenterStruct>&
                                                   police_control_center_structs)
    {
        // Create `PoliceControlCenter`s.
        for (const PoliceControlCenterStruct& police_control_center_struct : police_control_center_structs)
        {
            hirvi_core.entity_factory.create_custom_entity_derivative<
                PoliceControlCenter, core::PoliceControlCenterMemoryAllocator, PoliceControlCenterStruct>(
                data::Datatype::POLICE_CONTROL_CENTER,
                police_control_center_struct,
                &this->parent_of_police_control_centers);
        }
    }
}
