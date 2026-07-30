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

#ifndef HIRVI_ONTOLOGY_HIRVI_SCENE_HPP_INCLUDED
#define HIRVI_ONTOLOGY_HIRVI_SCENE_HPP_INCLUDED

#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/generic_parent_module.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <vector>  // std::vector

namespace yli::core
{
    class Application;
}

namespace yli::memory
{
    template<typename T1, std::size_t DataSize>
    class MemoryStorage;
}

namespace yli::ontology
{
    class MovableController;
    class Waypoint;
    class Camera;
    class Pipeline;
    class Material;
    class Species;
    class Object;
    class Symbiosis;
    class Holobiont;
    class Shapeshifter;
    class Text3d;
    class GlyphObject;

    template<typename TypeEnumType>
    class EntityFactory;
}

namespace hirvi::core
{
    class HirviCore;
}

namespace hirvi::ontology
{
    class PoliceControlCenter;
    class PoliceCar;
    class PoliceDog;
    class PoliceHelicopter;
    class PoliceHorse;
    class PoliceTrain;
    class PoliceTram;
    struct HirviSceneStruct;
    struct PoliceControlCenterStruct;

    class HirviScene final : public yli::ontology::Scene
    {
    public:
        HirviScene(
            yli::core::Application& application,
            yli::ontology::Universe& universe,
            const HirviSceneStruct& hirvi_scene_struct,
            yli::ontology::GenericParentModule* universe_parent_module,
            const core::HirviCore& hirvi_core);

        ~HirviScene() override = default;

        std::size_t get_number_of_children() const override;

        std::size_t get_number_of_descendants() const override;

        template<typename ChildType>
        yli::ontology::GenericParentModule* get_generic_parent_module() = delete;

        template<typename T1, std::size_t DataSize>
        friend class yli::memory::MemoryStorage;

        template<typename TypeEnumType>
        friend class EntityFactory;

    private:
        void create_police_control_centers(const core::HirviCore& hirvi_core,
                                           const std::vector<PoliceControlCenterStruct>&
                                           police_control_center_structs);

        yli::ontology::GenericParentModule parent_of_police_control_centers;
        yli::ontology::GenericParentModule parent_of_police_cars;
        yli::ontology::GenericParentModule parent_of_police_dogs;
        yli::ontology::GenericParentModule parent_of_police_helicopters;
        yli::ontology::GenericParentModule parent_of_police_horses;
        yli::ontology::GenericParentModule parent_of_police_trains;
        yli::ontology::GenericParentModule parent_of_police_trams;
    };

    template<>
    inline yli::ontology::GenericParentModule* HirviScene::get_generic_parent_module<yli::ontology::MovableController>()
    {
        return &this->parent_of_movable_controllers;
    }

    template<>
    inline yli::ontology::GenericParentModule* HirviScene::get_generic_parent_module<yli::ontology::Waypoint>()
    {
        return &this->parent_of_waypoints;
    }

    template<>
    inline yli::ontology::GenericParentModule* HirviScene::get_generic_parent_module<yli::ontology::Camera>()
    {
        return &this->parent_of_cameras;
    }

    template<>
    inline yli::ontology::GenericParentModule* HirviScene::get_generic_parent_module<yli::ontology::Pipeline>()
    {
        return &this->parent_of_pipelines;
    }

    template<>
    inline yli::ontology::GenericParentModule* HirviScene::get_generic_parent_module<yli::ontology::Material>()
    {
        return &this->parent_of_materials;
    }

    template<>
    inline yli::ontology::GenericParentModule* HirviScene::get_generic_parent_module<yli::ontology::Species>()
    {
        return &this->parent_of_species;
    }

    template<>
    inline yli::ontology::GenericParentModule* HirviScene::get_generic_parent_module<yli::ontology::Object>()
    {
        return &this->parent_of_objects;
    }

    template<>
    inline yli::ontology::GenericParentModule* HirviScene::get_generic_parent_module<yli::ontology::Symbiosis>()
    {
        return &this->parent_of_symbioses;
    }

    template<>
    inline yli::ontology::GenericParentModule* HirviScene::get_generic_parent_module<yli::ontology::Holobiont>()
    {
        return &this->parent_of_holobionts;
    }

    template<>
    inline yli::ontology::GenericParentModule* HirviScene::get_generic_parent_module<yli::ontology::Shapeshifter>()
    {
        return &this->parent_of_shapeshifters;
    }

    template<>
    inline yli::ontology::GenericParentModule* HirviScene::get_generic_parent_module<yli::ontology::Text3d>()
    {
        return &this->parent_of_text_3ds;
    }

    template<>
    inline yli::ontology::GenericParentModule* HirviScene::get_generic_parent_module<yli::ontology::GlyphObject>()
    {
        return &this->parent_of_glyph_objects;
    }

    template<>
    inline yli::ontology::GenericParentModule* HirviScene::get_generic_parent_module<PoliceControlCenter>()
    {
        return &this->parent_of_police_control_centers;
    }

    template<>
    inline yli::ontology::GenericParentModule* HirviScene::get_generic_parent_module<PoliceCar>()
    {
        return &this->parent_of_police_cars;
    }

    template<>
    inline yli::ontology::GenericParentModule* HirviScene::get_generic_parent_module<PoliceDog>()
    {
        return &this->parent_of_police_dogs;
    }

    template<>
    inline yli::ontology::GenericParentModule* HirviScene::get_generic_parent_module<PoliceHelicopter>()
    {
        return &this->parent_of_police_helicopters;
    }

    template<>
    inline yli::ontology::GenericParentModule* HirviScene::get_generic_parent_module<PoliceHorse>()
    {
        return &this->parent_of_police_horses;
    }

    template<>
    inline yli::ontology::GenericParentModule* HirviScene::get_generic_parent_module<PoliceTrain>()
    {
        return &this->parent_of_police_trains;
    }

    template<>
    inline yli::ontology::GenericParentModule* HirviScene::get_generic_parent_module<PoliceTram>()
    {
        return &this->parent_of_police_trams;
    }
}

#endif
