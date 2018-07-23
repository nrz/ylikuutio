#include "code/ylikuutio/command_line/command_line_master.hpp"

// Include standard headers
#include <iostream>      // std::cout, std::cin, std::cerr
#include <string>        // std::string
#include <vector>        // std::vector

// `yli_convert` is a command-line tool to load and export 3D data between different formats.
//
// parameters:
// required:
// `--in foo`  load 3D data from file `foo`.
// `--out bar` export 3D data into file `bar`.
//
// optional:
// `--informat baz` assume file format `baz` (if `--informat` is left out, file format is deduced from the filename extension).
// `--outformat qux` export 3D data into file `qux` (if `--outformat` is left out, file format is deduced from the filename extension).

int main(const int argc, const char* argv[])
{
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    command_line_master.print_keys_and_values();

    std::string file_format;

    // TODO: Load 3D model file.

    // TODO: Export 3D model file.
}
