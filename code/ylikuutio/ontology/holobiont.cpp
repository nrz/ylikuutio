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

#include "holobiont.hpp"
#include "orientation_module.hpp"
#include "universe.hpp"
#include "scene.hpp"
#include "symbiosis.hpp"
#include "symbiont_species.hpp"
#include "biont.hpp"
#include "cartesian_coordinates_module.hpp"
#include "generic_entity_factory.hpp"
#include "holobiont_struct.hpp"
#include "biont_struct.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/core/application.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/data/datatype.hpp"
#include "code/ylikuutio/render/render_system.hpp"
#include "code/ylikuutio/render/render_templates.hpp"

// Include standard headers
#include <cstdint>   // std::uintptr_t
#include <cstddef>   // std::size_t
#include <ios>       // std::hex
#include <iostream>  // std::cout, std::cerr
#include <optional>  // std::optional
#include <sstream>   // std::stringstream
#include <stdexcept> // std::runtime_error
#include <string>    // std::string
#include <vector>    // std::vector

namespace yli::ontology
{
    class GenericParentModule;
    class GenericMasterModule;
    class Entity;

    Holobiont::Holobiont(
            yli::core::Application& application,
            yli::ontology::Universe& universe,
            const yli::ontology::HolobiontStruct& holobiont_struct,
            yli::ontology::GenericParentModule* const scene_parent_module,
            yli::ontology::GenericMasterModule* const symbiosis_master_module,
            yli::ontology::GenericMasterModule* const brain_master_module)
        : Movable(
                application,
                universe,
                holobiont_struct,
                brain_master_module),
        child_of_scene(scene_parent_module, *this),
        parent_of_bionts(
                *this,
                this->registry,
                "bionts"),
        apprentice_of_symbiosis(symbiosis_master_module, this)
    {
        if (this->Holobiont::get_parent() != nullptr && this->Holobiont::get_symbiosis() != nullptr)
        {
            Holobiont::create_bionts(*this, holobiont_struct.should_render_bionts_vector);
        }

        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "yli::ontology::Holobiont*";
        this->can_be_erased = true;
    }

    yli::ontology::Entity* Holobiont::get_parent() const
    {
        return this->child_of_scene.get_parent();
    }

    void Holobiont::render(const yli::ontology::Scene* const target_scene)
    {
        if (!this->should_render)
        {
            return;
        }

        yli::ontology::Scene* const scene = this->get_scene();

        if (target_scene != nullptr && scene != nullptr && scene != target_scene)
        {
            // Different `Scene`s, do not render.
            return;
        }

        yli::render::RenderSystem* const render_system = this->universe.get_render_system();

        if (render_system == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Holobiont::render`: `render_system` is `nullptr`!");
        }

        // Every `Biont` is a child of a `Holobiont`, so they reside in the same `Scene`.
        render_system->render_bionts(this->parent_of_bionts);
    }

    void Holobiont::create_bionts(yli::ontology::Holobiont& holobiont, const std::vector<bool>& should_render_bionts_vector)
    {
        // requirements:
        // `scene` must not be `nullptr`.
        // `this->symbiosis_parent` must not be `nullptr`.

        yli::ontology::Scene* const scene = holobiont.get_scene();

        if (scene == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Holobiont::create_bionts`: `scene` is `nullptr`!");
        }

        const yli::ontology::Symbiosis* const symbiosis = holobiont.get_symbiosis();

        if (symbiosis == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Holobiont::create_bionts`: `symbiosis` is `nullptr`!");
        }

        const std::uintptr_t memory_address = reinterpret_cast<std::uintptr_t>(&holobiont);
        std::stringstream memory_address_stringstream;
        memory_address_stringstream << "0x" << std::hex << memory_address;

        std::cout << "Creating `Biont`s for `Holobiont` located at 0x" << memory_address_stringstream.str() << " ...\n";

        // Create `Biont` entities so that they bind to this `Holobiont`.
        const std::size_t correct_number_of_bionts = symbiosis->get_number_of_ofbx_meshes();
        std::cout << "Number of bionts to be created: " << correct_number_of_bionts << "\n";

        for (std::size_t biontID = 0; biontID < correct_number_of_bionts; biontID++)
        {
            if (!symbiosis->has_texture(biontID))
            {
                std::cerr << "ERROR: `Holobiont::create_bionts`: There is no texture for biont with biontID " << biontID << "\n";
                continue;
            }

            yli::ontology::SymbiontSpecies* const symbiont_species = symbiosis->get_symbiont_species(biontID);

            if (symbiont_species == nullptr)
            {
                continue;
            }

            yli::ontology::BiontStruct biont_struct;
            biont_struct.biontID                = biontID;
            biont_struct.scene                  = scene;
            biont_struct.parent                 = &holobiont;
            biont_struct.symbiont_species       = symbiont_species;
            biont_struct.initial_rotate_vectors = holobiont.initial_rotate_vectors;
            biont_struct.initial_rotate_angles  = holobiont.initial_rotate_angles;
            biont_struct.original_scale_vector  = holobiont.original_scale_vector;
            biont_struct.cartesian_coordinates  = holobiont.location;
            biont_struct.should_render          = (should_render_bionts_vector.size() > biontID ? should_render_bionts_vector.at(biontID) : true);

            std::cout << "Creating biont with biontID " << biontID << " ...\n";

            yli::ontology::GenericEntityFactory& entity_factory = holobiont.get_application().get_generic_entity_factory();
            entity_factory.create_biont(biont_struct);
        }
    }

    void Holobiont::update_x(const float x)
    {
        this->location.set_x(x);
        this->model_matrix[3][0] = x;

        for (yli::ontology::Entity* const biont_entity : this->parent_of_bionts.child_pointer_vector)
        {
            yli::ontology::Biont* const biont = static_cast<yli::ontology::Biont*>(biont_entity);

            if (biont != nullptr)
            {
                biont->location.set_x(x);
                biont->model_matrix[3][0] = x;
            }
        }
    }

    void Holobiont::update_y(const float y)
    {
        this->location.set_y(y);
        this->model_matrix[3][1] = y;

        for (yli::ontology::Entity* const biont_entity : this->parent_of_bionts.child_pointer_vector)
        {
            yli::ontology::Biont* const biont = static_cast<yli::ontology::Biont*>(biont_entity);

            if (biont != nullptr)
            {
                biont->location.set_y(y);
                biont->model_matrix[3][1] = y;
            }
        }
    }

    void Holobiont::update_z(const float z)
    {
        this->location.set_z(z);
        this->model_matrix[3][2] = z;

        for (yli::ontology::Entity* const biont_entity : this->parent_of_bionts.child_pointer_vector)
        {
            yli::ontology::Biont* const biont = static_cast<yli::ontology::Biont*>(biont_entity);

            if (biont != nullptr)
            {
                biont->location.set_z(z);
                biont->model_matrix[3][2] = z;
            }
        }
    }

    yli::ontology::GenericParentModule* Holobiont::get_generic_parent_module(const int type)
    {
        if (type == yli::data::Datatype::BIONT)
        {
            return &this->parent_of_bionts;
        }

        return nullptr;
    }

    yli::ontology::Scene* Holobiont::get_scene() const
    {
        return this->child_of_scene.get_scene();
    }

    yli::ontology::Symbiosis* Holobiont::get_symbiosis() const
    {
        return static_cast<yli::ontology::Symbiosis*>(this->apprentice_of_symbiosis.get_master());
    }

    std::size_t Holobiont::get_number_of_children() const
    {
        return this->parent_of_bionts.get_number_of_children();
    }

    std::size_t Holobiont::get_number_of_descendants() const
    {
        return yli::ontology::get_number_of_descendants(this->parent_of_bionts.child_pointer_vector);
    }

    // Public callbacks.

    std::optional<yli::data::AnyValue> Holobiont::create_holobiont_with_parent_name_x_y_z(
            yli::ontology::Scene& parent,
            yli::ontology::Symbiosis& symbiosis,
            const std::string& holobiont_name,
            const std::string& x,
            const std::string& y,
            const std::string& z)
    {
        return yli::ontology::Holobiont::create_holobiont_with_parent_name_x_y_z_yaw_pitch(parent, symbiosis, holobiont_name, x, y, z, "0.0", "0.0");
    }

    std::optional<yli::data::AnyValue> Holobiont::create_holobiont_with_parent_name_x_y_z_yaw_pitch(
            yli::ontology::Scene& parent,
            yli::ontology::Symbiosis& symbiosis,
            const std::string& holobiont_name,
            const std::string& x,
            const std::string& y,
            const std::string& z,
            const std::string& yaw,
            const std::string& pitch)
    {
        return yli::ontology::Holobiont::create_holobiont_with_parent_name_x_y_z_roll_yaw_pitch(parent, symbiosis, holobiont_name, x, y, z, "0.0", yaw, pitch);
    }

    std::optional<yli::data::AnyValue> Holobiont::create_holobiont_with_parent_name_x_y_z_roll_yaw_pitch(
            yli::ontology::Scene& parent,
            yli::ontology::Symbiosis& symbiosis,
            const std::string& holobiont_name,
            const std::string& x,
            const std::string& y,
            const std::string& z,
            const std::string& roll,
            const std::string& yaw,
            const std::string& pitch)
    {
        const yli::ontology::GenericEntityFactory& entity_factory = parent.get_application().get_generic_entity_factory();

        yli::data::AnyValue x_any_value("float", x);
        yli::data::AnyValue y_any_value("float", y);
        yli::data::AnyValue z_any_value("float", z);
        yli::data::AnyValue roll_any_value("float", roll);
        yli::data::AnyValue yaw_any_value("float", yaw);
        yli::data::AnyValue pitch_any_value("float", pitch);

        if (!std::holds_alternative<float>(x_any_value.data))
        {
            std::cerr << "ERROR: `Holobiont::create_holobiont_with_parent_name_x_y_z_yaw_pitch`: invalid value for `x`!\n";
            return std::nullopt;
        }

        if (!std::holds_alternative<float>(y_any_value.data))
        {
            std::cerr << "ERROR: `Holobiont::create_holobiont_with_parent_name_x_y_z_yaw_pitch`: invalid value for `y`!\n";
            return std::nullopt;
        }

        if (!std::holds_alternative<float>(z_any_value.data))
        {
            std::cerr << "ERROR: `Holobiont::create_holobiont_with_parent_name_x_y_z_yaw_pitch`: invalid value for `z`!\n";
            return std::nullopt;
        }

        if (!std::holds_alternative<float>(roll_any_value.data))
        {
            std::cerr << "ERROR: `Holobiont::create_holobiont_with_parent_name_x_y_z_roll_pitch`: invalid value for `roll`!\n";
            return std::nullopt;
        }

        if (!std::holds_alternative<float>(yaw_any_value.data))
        {
            std::cerr << "ERROR: `Holobiont::create_holobiont_with_parent_name_x_y_z_yaw_pitch`: invalid value for `yaw`!\n";
            return std::nullopt;
        }

        if (!std::holds_alternative<float>(pitch_any_value.data))
        {
            std::cerr << "ERROR: `Holobiont::create_holobiont_with_parent_name_x_y_z_yaw_pitch`: invalid value for `pitch`!\n";
            return std::nullopt;
        }

        const float float_x = std::get<float>(x_any_value.data);
        const float float_y = std::get<float>(y_any_value.data);
        const float float_z = std::get<float>(z_any_value.data);
        const float float_roll = std::get<float>(roll_any_value.data);
        const float float_yaw = std::get<float>(yaw_any_value.data);
        const float float_pitch = std::get<float>(pitch_any_value.data);

        yli::ontology::HolobiontStruct holobiont_struct(parent, symbiosis);
        holobiont_struct.cartesian_coordinates = yli::ontology::CartesianCoordinatesModule(float_x, float_y, float_z);
        holobiont_struct.orientation = yli::ontology::OrientationModule(float_roll, float_yaw, float_pitch);
        holobiont_struct.local_name = holobiont_name;
        entity_factory.create_holobiont(holobiont_struct);
        return std::nullopt;
    }

    // Public callbacks end here.
}
