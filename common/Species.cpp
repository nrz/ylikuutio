#include <string>

#include "globals.hpp"
#include "Species.hpp"

namespace model
{
    Species::Species(SpeciesStruct species_struct)
    {
        Species::vertex_shader = species_struct.vertex_shader;
        Species::fragment_shader = species_struct.fragment_shader;

        Species::char_vertex_shader = Species::vertex_shader.c_str();
        Species::char_fragment_shader = Species::fragment_shader.c_str();
    }
}
