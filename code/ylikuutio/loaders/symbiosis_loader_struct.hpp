#ifndef __SYMBIOSIS_LOADER_STRUCT_HPP_INCLUDED
#define __SYMBIOSIS_LOADER_STRUCT_HPP_INCLUDED

// Include standard headers
#include <string>   // std::string

typedef struct SymbiosisLoaderStruct
{
    SymbiosisLoaderStruct()
        : triangulation_type("bilinear_interpolation")
    {
        // constructor.
    }
    std::string model_filename;
    std::string model_file_format;
    std::string triangulation_type; // for all.
} SymbiosisLoaderStruct;

#endif
