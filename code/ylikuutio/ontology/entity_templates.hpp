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
    class Scene;
    class Shader;
    class Material;
    class Species;
    class Object;
    class VectorFont;
    class Glyph;
    class Text3D;

    template<class T1>
        InfoStruct* get_info(const T1 entity)
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
