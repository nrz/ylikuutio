#include "code/ylikuutio/ontology/symbiosis.hpp"
#include "code/ylikuutio/ontology/symbiosis_struct.hpp"
#include "code/ylikuutio/command_line/command_line_master.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"

// Include standard headers
#include <algorithm>     // std::transform
#include <cstdlib>       // EXIT_FAILURE, EXIT_SUCCESS
#include <iostream>      // std::cout, std::cin, std::cerr
#include <string>        // std::string
#include <vector>        // std::vector

// `yli_convert` is a command-line tool to load and export 3D data between different formats.
//
// parameters:
// required:
// `--in=foo`  load 3D data from file `foo`.
// `--out=bar` export 3D data into file `bar`.
//
// optional:
// `--informat=baz` assume file format `baz` (if `--informat` is left out, file format is deduced from the filename extension).
// `--outformat=qux` export 3D data into file `qux` (if `--outformat` is left out, file format is deduced from the filename extension).

namespace yli
{
    namespace ontology
    {
        class Universe;
    }
}

int main(const int argc, const char* argv[])
{
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    command_line_master.print_keys_and_values();

    if (!command_line_master.is_key("--in"))
    {
        std::cerr << "--in parameter is required!\n\nexample:\n\nyli_convert --in=foo --out=bar\n";
        exit(EXIT_FAILURE);
    }

    if (!command_line_master.is_key("--out"))
    {
        std::cerr << "--out parameter is required!\n\nexample:\n\nyli_convert --in=foo --out=bar\n";
        exit(EXIT_FAILURE);
    }

    const std::string in_file = command_line_master.get_value("--in");
    const std::string out_file = command_line_master.get_value("--out");

    std::string in_file_format = ""; // dummy value.

    if (command_line_master.is_key("--informat"))
    {
        in_file_format = command_line_master.get_value("--informat");
    }
    else
    {
        const char separator = '.';
        yli::string::extract_last_part_of_string(in_file, in_file_format, separator);
    }

    if (in_file_format.empty())
    {
        std::cerr << "--informat is empty!\n";
        exit(EXIT_FAILURE);
    }

    std::cout << "in file format is " << in_file_format << "\n";

    std::string out_file_format = ""; // dummy value.

    if (command_line_master.is_key("--outformat"))
    {
        out_file_format = command_line_master.get_value("--outformat");
    }
    else
    {
        const char separator = '.';
        yli::string::extract_last_part_of_string(out_file, out_file_format, separator);
    }

    if (out_file_format.empty())
    {
        std::cerr << "--outformat is empty!\n";
        exit(EXIT_FAILURE);
    }

    std::cout << "out file format is " << out_file_format << "\n";

    // OK, all required input is given in the correct format.

    // convert in file format & out file format into lowercase.
    std::transform(in_file_format.begin(), in_file_format.end(), in_file_format.begin(), ::tolower);
    std::transform(out_file_format.begin(), out_file_format.end(), out_file_format.begin(), ::tolower);

    if (in_file_format != "obj" && in_file_format != "fbx")
    {
        std::cerr << "unsupported in file format: " << in_file_format << "\n";
        exit(EXIT_FAILURE);
    }

    // Always load the 3D object into a `yli::ontology::Symbiosis`.
    SymbiosisStruct symbiosis_struct;
    symbiosis_struct.model_filename = in_file;
    symbiosis_struct.model_file_format = in_file_format;
    symbiosis_struct.triangulation_type = "bilinear_interpolation";
    symbiosis_struct.parent = nullptr;           // no parent.
    symbiosis_struct.vram_buffer_in_use = false; // do not use VRAM buffer.
    yli::ontology::Universe* const universe = nullptr;
    yli::ontology::Symbiosis* const symbiosis = new yli::ontology::Symbiosis(universe, symbiosis_struct);

    // TODO: Export 3D model file.
    if (out_file_format == "obj")
    {
    }
    else if (out_file_format == "fbx")
    {
    }
    else
    {
        std::cerr << "unsupported out file format: " << out_file_format << "\n";
        exit(EXIT_FAILURE);
    }
}
