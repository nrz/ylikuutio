#!/usr/bin/python3

# Ylikuutio - A 3D game and simulation engine.
#
# Copyright (C) 2015-2020 Antti Nuortimo.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

# This script creates `yli::ontology` class files according to
# the given command line parameters.
#
# usage:
# create_yli_ontology_class.py <class name> <parent class name> [optional parameters]
#
# Class name and parent class name are assumed to be in `yli::ontology` namespace.
# Class name and parent class name must be valid C++ class names.

import re, sys

n_command_line_args = len(sys.argv)

usage = \
"usage:\n"\
"create_yli_ontology_class.py <class name> <parent class name> [optional parameters]"

# print usage if too little arguments are given.
if n_command_line_args <= 2:
    print(usage)
    sys.exit()

x = 0
inherited_class_name = "Entity"

for arg in sys.argv:
    if x == 1:
        class_name = arg           # 1st argument: name of the new class.
    elif x == 2:
        parent_class_name = arg    # 2nd argument: name of its compositional parent class (part-of relation).
    elif x == 3:
        inherited_class_name = arg # 3rd argument (optional): inherited class. If not given, then `Entity is inherited`.
    x += 1

copyright_notice = \
"// Ylikuutio - A 3D game and simulation engine.\n"\
"//\n"\
"// Copyright (C) 2015-2020 Antti Nuortimo.\n"\
"//\n"\
"// This program is free software: you can redistribute it and/or modify\n"\
"// it under the terms of the GNU Affero General Public License as\n"\
"// published by the Free Software Foundation, either version 3 of the\n"\
"// License, or (at your option) any later version.\n"\
"//\n"\
"// This program is distributed in the hope that it will be useful,\n"\
"// but WITHOUT ANY WARRANTY; without even the implied warranty of\n"\
"// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"\
"// GNU Affero General Public License for more details.\n"\
"//\n"\
"// You should have received a copy of the GNU Affero General Public License\n"\
"// along with this program.  If not, see <https://www.gnu.org/licenses/>."

namespace = "yli::ontology"
fully_qualified_class_name = namespace + "::" + class_name
fully_qualified_parent_class_name = namespace + "::" + parent_class_name
fully_qualified_inherited_class_name = namespace + "::" + inherited_class_name

# snake_case lowercase names.
snake_case_class_name = re.sub(r'(?<!^)(?=[A-Z])', '_', class_name).lower()
snake_case_parent_class_name = re.sub(r'(?<!^)(?=[A-Z])', '_', parent_class_name).lower()
snake_case_inherited_class_name = re.sub(r'(?<!^)(?=[A-Z])', '_', inherited_class_name).lower()

# include guard generation.
# include guard macro names follow Ylikuutio coding guidelines.
class_include_guard_macro_name = "__YLIKUUTIO_ONTOLOGY_" + re.sub(r'(?<!^)(?=[A-Z])', '_', class_name).upper() + "_HPP_INCLUDED"
struct_include_guard_macro_name = "__YLIKUUTIO_ONTOLOGY_" + re.sub(r'(?<!^)(?=[A-Z])', '_', class_name).upper() + "_STRUCT_HPP_INCLUDED"
class_ifndef_line = "#ifndef " + class_include_guard_macro_name
class_define_line = "#define " + class_include_guard_macro_name
struct_ifndef_line = "#ifndef " + struct_include_guard_macro_name
struct_define_line = "#define " + struct_include_guard_macro_name
entity_struct_include_line = "#include \"entity_struct.hpp\""
endif_line = "#endif"

# class filenames.
class_filename_hpp = snake_case_class_name + ".hpp"
class_filename_cpp = snake_case_class_name + ".cpp"

class_include_line = "#include \"" + class_filename_hpp + "\""

# struct filename.
struct_filename = snake_case_class_name + "_struct.hpp"

# inherited class filename.
# inherited class needs to be #include'd always because it is inherited.
inherited_class_hpp = snake_case_inherited_class_name + ".hpp"
inherited_class_include_line = "#include \"" + inherited_class_hpp + "\""

# include line for `yli::ontology::ChildModule`.
child_module_include_line = "#include \"child_module.hpp\" // TODO: delete this line if `ChildModule` is not needed!"

# child module variable name.
child_module_variable_name = "child_of_" + snake_case_parent_class_name

# struct variable type and name.
struct_variable_type = class_name + "Struct"
const_struct_reference_variable_type = "const " + namespace + "::" + struct_variable_type + "&"
struct_name = snake_case_class_name + "_struct"

# inherited class' variable type and name.
fully_qualified_inherited_class_struct_variable_type = fully_qualified_inherited_class_name + "Struct"

# include line for the corresponding struct file.
struct_include_line = "#include \"" + struct_name + ".hpp\" // TODO: modify or delete this line if there is no `" + namespace + "::" + class_name + "Struct`!"

# standard headers include lines.
standard_headers_include_lines = \
"// Include standard headers\n"\
"#include <cstddef> // std::size_t"

parent_module_type_and_name = "yli::ontology::ParentModule* const parent_module"

# namespace
begin_namespace_lines = \
"namespace yli::ontology\n"\
"{"\

end_namespace_lines = \
"}"

entity_forward_declaration = \
"    class Entity;"

universe_forward_declaration = \
"    class Universe;"

parent_module_forward_declaration = \
"    class ParentModule; // TODO: delete this line if `ParentModule` is not needed!"

begin_class_definition = \
"    class " + class_name + ": public " + fully_qualified_inherited_class_name + "\n"\
"    {"

public_line = \
"        public:"
private_line = \
"        private:"

parent_pointer_line_in_header = \
"            " + fully_qualified_parent_class_name + "* parent;"

end_class_definition = \
"    };"

class_constructor_lines = \
"            " + class_name + "(\n"\
"                    " + namespace + "::Universe* const universe,\n"\
"                    " + const_struct_reference_variable_type + " " + struct_name + ",\n"\
"                    " + parent_module_type_and_name + ") // TODO: other_parameters!\n"\
"                : " + inherited_class_name + "(universe, " + struct_name + "), // TODO: complete the initializer list!\n"\
"                " + child_module_variable_name + "(parent_module, this) // TODO: delete this line if `ChildModule` is not needed!\n"\
"            {\n"\
"                // constructor.\n"\
"                this->parent = " + struct_name + ".parent;\n"\
"\n"\
"                // `yli::ontology::Entity` member variables begin here.\n"\
"                this->type_string = \"" + fully_qualified_class_name + "*\";\n"\
"                // TODO: add other `yli::ontology::Entity` member variables such as `can_be_erased` if needed!\n"\
"            }"

delete_copy_constructor_line = \
"            " + class_name + "(const " + class_name + "&) = delete;            // Delete copy constructor."

delete_copy_assignment_line = \
"            " + class_name + " &operator=(const " + class_name + "&) = delete; // Delete copy assignment."

destructor_declaration_lines = \
"            // destructor.\n"\
"            virtual ~" + class_name + "();"

get_parent_const_override_line = \
"            yli::ontology::Entity* get_parent() const override;"

get_number_of_children_const_override_line = \
"            std::size_t get_number_of_children() const override;"

get_number_of_descendants_const_override_line = \
"            std::size_t get_number_of_descendants() const override;"

child_module_lines = \
"            " + namespace + "::ChildModule " + child_module_variable_name + "; // TODO: delete this line if `ChildModule` is not needed!"

# header file specific lines.
destructor_definition_lines = \
"    " + class_name + "::~" + class_name + "()\n"\
"    {\n"\
"        // destructor.\n"\
"    }"

# struct file specific lines.
begin_struct_definition = \
"    struct " + struct_variable_type + ": public " + fully_qualified_inherited_class_struct_variable_type + "\n"\
"    {"

end_struct_definition = \
"    };"

parent_class_forward_declaration = \
"    class " + parent_class_name + ";"

struct_constructor_lines = \
"        " + struct_variable_type + "()\n"\
"            : parent(nullptr)\n"\
"        {\n"\
"            // constructor.\n"\
"        }"

parent_pointer_lines = \
"        " + fully_qualified_parent_class_name + "* parent;"

with open(class_filename_hpp, 'w') as f:
    print(copyright_notice, file = f)
    print(file = f)
    print(class_ifndef_line, file = f)
    print(class_define_line, file = f)
    print(file = f)
    print(inherited_class_include_line, file = f)
    print(child_module_include_line, file = f)
    print(struct_include_line, file = f)
    print(file = f)
    print(standard_headers_include_lines, file = f)
    print(file = f)
    print(begin_namespace_lines, file = f)
    if inherited_class_name != "Entity":
        print(entity_forward_declaration, file = f)
    print(universe_forward_declaration, file = f)
    print(parent_class_forward_declaration, file = f)
    print(parent_module_forward_declaration, file = f)
    print(file = f)
    print(begin_class_definition, file = f)
    print(public_line, file = f)
    print(class_constructor_lines, file = f)
    print(file = f)
    print(delete_copy_constructor_line, file = f)
    print(delete_copy_assignment_line, file = f)
    print(file = f)
    print(destructor_declaration_lines, file = f)
    print(file = f)
    print(get_parent_const_override_line, file = f)
    print(get_number_of_children_const_override_line, file = f)
    print(get_number_of_descendants_const_override_line, file = f)
    print(file = f)
    print(child_module_lines, file = f)
    print(file = f)
    print(private_line, file = f)
    print(parent_pointer_line_in_header, file = f)
    print(end_class_definition, file = f)
    print(end_namespace_lines, file = f)
    print(file = f)
    print(endif_line, file = f)

with open(class_filename_cpp, 'w') as f:
    print(copyright_notice, file = f)
    print(file = f)
    print(class_include_line, file = f)
    print(file = f)
    print(begin_namespace_lines, file = f)
    print(destructor_definition_lines, file = f)
    print(end_namespace_lines, file = f)

with open(struct_filename, 'w') as f:
    print(copyright_notice, file = f)
    print(file = f)
    print(struct_ifndef_line, file = f)
    print(struct_define_line, file = f)
    print(file = f)
    print(entity_struct_include_line, file = f)
    print(file = f)
    print(begin_namespace_lines, file = f)
    print(parent_class_forward_declaration, file = f)
    print(file = f)
    print(begin_struct_definition, file = f)
    print(struct_constructor_lines, file = f)
    print(file = f)
    print(parent_pointer_lines, file = f)
    print(end_struct_definition, file = f)
    print(end_namespace_lines, file = f)
    print(file = f)
    print(endif_line, file = f)
