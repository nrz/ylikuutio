#include "entity_factory.hpp"
#include "entity.hpp"
#include "universe.hpp"
#include "world.hpp"
#include "scene.hpp"
#include "shader.hpp"
#include "material.hpp"
#include "species.hpp"
#include "object.hpp"
#include "symbiosis.hpp"
#include "holobiont.hpp"
#include "vector_font.hpp"
#include "text3D.hpp"
#include "font2D.hpp"
#include "camera.hpp"
#include "shader_struct.hpp"
#include "material_struct.hpp"
#include "species_struct.hpp"
#include "object_struct.hpp"
#include "symbiosis_struct.hpp"
#include "holobiont_struct.hpp"
#include "vector_font_struct.hpp"
#include "text3D_struct.hpp"
#include "camera_struct.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include standard headers
#include <memory>    // std::make_shared, std::shared_ptr
#include <string>    // std::string

namespace ontology
{
    EntityFactory::EntityFactory(ontology::Universe* const universe)
    {
        // constructor.
        this->universe = universe;
    }

    EntityFactory::~EntityFactory()
    {
        // destructor.
    }

    ontology::Universe* EntityFactory::get_universe() const
    {
        return this->universe;
    }

    ontology::Entity* EntityFactory::create_World()
    {
        return new ontology::World(this->universe);
    }

    ontology::Entity* EntityFactory::create_Scene(ontology::World* const world, const float water_level)
    {
        return new ontology::Scene(this->universe, world, water_level);
    }

    ontology::Entity* EntityFactory::create_Shader(const ShaderStruct& shader_struct)
    {
        return new ontology::Shader(this->universe, shader_struct);
    }

    ontology::Entity* EntityFactory::create_Material(const MaterialStruct& material_struct)
    {
        return new ontology::Material(this->universe, material_struct);
    }

    ontology::Entity* EntityFactory::create_Species(const SpeciesStruct& species_struct)
    {
        return new ontology::Species(this->universe, species_struct);
    }

    ontology::Entity* EntityFactory::create_Object(ObjectStruct& object_struct)
    {
        return new ontology::Object(this->universe, object_struct);
    }

    ontology::Entity* EntityFactory::create_Symbiosis(const SymbiosisStruct& symbiosis_struct)
    {
        return new ontology::Symbiosis(this->universe, symbiosis_struct);
    }

    ontology::Entity* EntityFactory::create_Holobiont(HolobiontStruct& holobiont_struct)
    {
        return new ontology::Holobiont(this->universe, holobiont_struct);
    }

    ontology::Entity* EntityFactory::create_VectorFont(const VectorFontStruct& vector_font_struct)
    {
        return new ontology::VectorFont(this->universe, vector_font_struct);
    }

    ontology::Entity* EntityFactory::create_Text3D(Text3DStruct& text3D_struct)
    {
        return new ontology::Text3D(this->universe, text3D_struct);
    }

    ontology::Entity* EntityFactory::create_Font2D(
            GLuint screen_width,
            GLuint screen_height,
            const std::string& texture_filename,
            const std::string& font_texture_file_format)
    {
        return new ontology::Font2D(
                this->universe,
                universe->get_window_width(),
                universe->get_window_height(),
                texture_filename.c_str(),
                font_texture_file_format.c_str());
    }

    ontology::Entity* EntityFactory::create_Camera(CameraStruct& camera_struct)
    {
        return new ontology::Camera(this->universe, camera_struct);
    }
}
