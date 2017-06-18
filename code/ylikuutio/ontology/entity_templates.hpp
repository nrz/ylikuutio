#ifndef __ENTITY_TEMPLATES_HPP_INCLUDED
#define __ENTITY_TEMPLATES_HPP_INCLUDED

#include "info_struct.hpp"
#include "universe.hpp"

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <typeinfo> // typeid
#include <vector>   // std::vector

namespace ontology
{
    class Universe;
    class Scene;
    class Shader;
    class Material;
    class Species;
    class Object;
    class VectorFont;
    class Glyph;
    class Text3D;

    template<class T1>
        void set_name(std::string name, T1 entity)
        {
            ontology::Universe* universe = entity->universe_pointer;

            if (universe == nullptr)
            {
                return;
            }

            datatypes::AnyValue* entity_any_value = new datatypes::AnyValue(entity);

            if (entity_any_value == nullptr)
            {
                return;
            }

            if (universe->entity_anyvalue_map[name] != nullptr)
            {
                return;
            }

            entity->name = name;
            universe->entity_anyvalue_map[name] = entity_any_value;
        }

    template<class T1>
        int32_t get_number_of_child_types(T1 entity)
        {
            return entity->child_vector_pointers_vector.size();
        }

    template<class T1>
        int32_t get_number_of_children(T1 entity)
        {
            switch (typeid(entity))
            {
                case typeid(ontology::Universe*):
                    return entity->scene_pointer_vector.size();
                case typeid(ontology::Scene*):
                    return entity->shader_pointer_vector.size();
                case typeid(ontology::Material*):
                    return entity->shader_pointer_vector.size();
                case typeid(ontology::Species*):
                    return entity->shader_pointer_vector.size();
                case typeid(ontology::Object*):
                    return 0;
                case typeid(ontology::VectorFont*):
                    return entity->glyph_pointer_vector.size() + entity->text3D_pointer_vector.size();
                case typeid(ontology::Glyph*):
                    return entity->object_pointer_vector.size();
                case typeid(ontology::Text3D*):
                    return entity->object_pointer_vector.size();
                default:
                    return -1;
            }
        }

    template<class T1>
        uint32_t get_number_of_descendants(std::vector<T1> child_pointer_vector)
        {
            uint32_t number_of_descendants = 0;

            for (uint32_t i = 0; i < child_pointer_vector.size(); i++)
            {
                T1 child = child_pointer_vector.get(i);
                number_of_descendants += get_number_of_descendants_of_entity(child);
            }

            return number_of_descendants;
        }

    template<class T1>
        uint32_t get_number_of_descendants_of_entity(T1 entity)
        {
            switch (typeid(entity))
            {
                case typeid(ontology::Universe*):
                    return get_number_of_descendants(entity->scene_pointer_vector);
                case typeid(ontology::Scene*):
                    return get_number_of_descendants(entity->shader_pointer_vector);
                case typeid(ontology::Shader*):
                    return get_number_of_descendants(entity->material_pointer_vector) + get_number_of_descendants(entity->symbiosis_pointer_vector);
                case typeid(ontology::Material*):
                    return get_number_of_descendants(entity->species_pointer_vector) +
                        get_number_of_descendants(entity->vector_font_pointer_vector) +
                        get_number_of_descendants(entity->chunk_master_pointer_vector);
                case typeid(ontology::Species*):
                    return get_number_of_descendants(entity->object_pointer_vector);
                case typeid(ontology::Object*):
                    return 0;
                case typeid(ontology::VectorFont*):
                    return get_number_of_descendants(entity->glyph_pointer_vector) + get_number_of_descendants(entity->text3D_pointer_vector);
                case typeid(ontology::Glyph*):
                    return get_number_of_descendants(entity->object_pointer_vector);
                case typeid(ontology::Text3D*):
                    return get_number_of_descendants(entity->object_pointer_vector);
                default:
                    return -1;
            }
        }

    template<class T1>
        InfoStruct* get_info(T1 entity)
        {
            InfoStruct* info_struct = new InfoStruct();

            // memory address
            info_struct->memory_address = entity;

            // child ID (within entity class)
            info_struct->childID = entity->childID;

            // name (if any)
            info_struct->name = entity->name;

            // coordinate vector (if applicable)
            if (typeid(entity) == typeid(ontology::Object*))
            {
                // object, so has coordinate vector.
                info_struct->coordinate_vector = entity->coordinate_vector();
            }

            // number of children
            info_struct->number_of_children = get_number_of_children(entity);

            // number of descendant objects

            // number of vertices (in this or in descendants)

            // number of faces (in this or in descendants)

            return info_struct;
        }
}

#endif
