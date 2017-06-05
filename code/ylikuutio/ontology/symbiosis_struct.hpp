#ifndef __SYMBIOSIS_STRUCT_HPP_INCLUDED
#define __SYMBIOSIS_STRUCT_HPP_INCLUDED

// Include standard headers
#include <string>   // std::string

namespace ontology
{
    class Shader;
}

typedef struct SymbiosisStruct
{
    SymbiosisStruct()
        : parent_pointer(nullptr)
    {
        // constructor.
    }
    ontology::Shader* parent_pointer; // pointer to the `Scene` object.

    std::string model_file_format;    // type of the symbiosis model file.
    std::string model_filename;       // filename of the symbiosis model file.
} SymbiosisStruct;

#endif
