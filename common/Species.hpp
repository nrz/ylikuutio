#ifndef __SPECIES_HPP_INCLUDED
#define __SPECIES_HPP_INCLUDED

#include <string>
#include <vector>
#include "globals.hpp"
#include "Object.hpp"

namespace model
{
    class Species
    {
        public:
            // constructor.
            Species(SpeciesStruct species_struct);

            std::string vertex_shader;               // filename of vertex shader.
            std::string fragment_shader;             // filename of fragment shader.
            std::vector<ObjectStruct> object_vector; // vector of individual objects of this species.

        private:
            const char *char_vertex_shader;
            const char *char_fragment_shader;
    };
}

#endif
