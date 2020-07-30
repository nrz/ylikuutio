# Currently implemented console functionality

**command** refers to the command used in Hirvi & Tulevaisuus. Each application defines its own commands.
**function** refers to the function that implements the functionality.
**functionality** is a short description of the functionality provided by the command.

| command                      | function                                                                                            | functionality
|:---------------------------- |:--------------------------------------------------------------------------------------------------- |:---------------------------------
| `Variable` callbacks         |                                                                                                     |
|:---------------------------- |:--------------------------------------------------------------------------------------------------- |:---------------------------------
| `variables`                  | `yli::ontology::Entity::print_variables0`                                                           | Prints the names and memory
|                              |                                                                                                     | addresses of the `Variable`s
|                              |                                                                                                     | of the `Universe`.
| `variables`                  | `yli::ontology::Entity::print_variables1`                                                           | Prints the names and memory
|                              |                                                                                                     | addresses of the `Variable`s
|                              |                                                                                                     | of a named `Entity`.
| `create-variable`            | yli::ontology::Entity::create_variable_with_parent_name_type_value`                                 | Creates a `Variable`.
| `set`                        | `yli::ontology::Variable::set_variable_shared_ptr_string`                                           | Sets the value of a `Variable`.
| `copy`                       | `yli::ontology::Variable::set_variable_variable`                                                    | Does a deep copy of a `Variable`.
| `copy-shallow`               | `yli::ontology::Variable::set_shallow_variable_variable`                                            | Does a shallow copy of
|                              |                                                                                                     | a `Variable`.
| `print`                      | `yli::ontology::Variable::print_value1`                                                             | Prints the value of a `Variable`.
|:---------------------------- |:--------------------------------------------------------------------------------------------------- |:---------------------------------
| `Object` callbacks           |                                                                                                     |
|:---------------------------- |:--------------------------------------------------------------------------------------------------- |:---------------------------------
| `create-object`              | `yli::ontology::Object::create_object_with_parent_name_x_y_z`                                       | Creates an `Object`.
| `create-object`              | `yli::ontology::Object::create_object_with_parent_name_x_y_z_horizontal_angle_vertical_angle`       | Creates an `Object`.
|:---------------------------- |:--------------------------------------------------------------------------------------------------- |:---------------------------------
| `Holobiont` callbacks        |                                                                                                     |
|:---------------------------- |:--------------------------------------------------------------------------------------------------- |:---------------------------------
| `create-holobiont`           | `yli::ontology::Holobiont::create_holobiont_with_parent_name_x_y_z`                                 | Creates a `Holobiont`.
| `create-holobiont`           | `yli::ontology::Holobiont::create_holobiont_with_parent_name_x_y_z_horizontal_angle_vertical_angle` | Creates a `Holobiont`.
|:---------------------------- |:--------------------------------------------------------------------------------------------------- |:---------------------------------
| `Entity` handling callbacks  |                                                                                                     |
|:---------------------------- |:--------------------------------------------------------------------------------------------------- |:---------------------------------
| `entities`                   | `yli::ontology::Universe::print_entities`                                                           | Prints the names and memory
|                              |                                                                                                     | address of all named Entities.
| `parent`                     | `yli::ontology::Universe::print_parent`                                                             | Prints the memory address of
|                              |                                                                                                     | the parent of the named `Entity`.
| `children`                   | `yli::ontology::Entity::print_children`                                                             | Prints the local names of
|                              |                                                                                                     | a named `Entity`.
| `activate`                   | `yli::ontology::Universe::activate_entity`                                                          | Activates a named `Entity`.
| `delete`                     | `yli::ontology::Universe::delete_entity`                                                            | Deletes a named `Entity`,
|                              |                                                                                                     | if it can be deleted.
| `info`                       | `yli::ontology::Universe::info0`                                                                    | Prints info about Entities.
| `info`                       | `yli::ontology::Universe::info1`                                                                    | Prints info about
|                              |                                                                                                     | a named `Entity`.
| `bind`                       | `yli::ontology::Universe::bind`                                                                     | Binds a named `Entity` to
|                              |                                                                                                     | another named `Entity`.
|                              |                                                                                                     | Both parent-child and
|                              |                                                                                                     | master-apprentice are supported.
|                              |                                                                                                     | `bind child parent`
|                              |                                                                                                     | `bind apprentice master`
| `set-global-name             | `yli::ontology::Universe::set_global_name_for_entity`                                               | Sets the global name of
|                              |                                                                                                     | a named `Entity`.
| `set-local-name              | `yli::ontology::Universe::set_local_name_for_entity`                                                | Sets the local name of
|                              |                                                                                                     | a named `Entity`.
|:---------------------------- |:--------------------------------------------------------------------------------------------------- |:---------------------------------
| Exit program callbacks       |                                                                                                     |
|:---------------------------- |:--------------------------------------------------------------------------------------------------- |:---------------------------------
| `bye`                        | `yli::snippets::quit`                                                                               | Quits the application.
| `chau`                       | `yli::snippets::quit`                                                                               | Quits the application.
| `ciao`                       | `yli::snippets::quit`                                                                               | Quits the application.
| `heippa`                     | `yli::snippets::quit`                                                                               | Quits the application.
| `quit`                       | `yli::snippets::quit`                                                                               | Quits the application.
| `sayonara`                   | `yli::snippets::quit`                                                                               | Quits the application.
|:---------------------------- |:--------------------------------------------------------------------------------------------------- |:---------------------------------
| Other callbacks              |                                                                                                     |
|:---------------------------- |:--------------------------------------------------------------------------------------------------- |:---------------------------------
| `help`                       | `yli::snippets::help`                                                                               | Prints help.
| `version`                    | `ajokki::version`                                                                                   | Prints software version.
| `clear`                      | `yli::ontology::Console::clear`                                                                     | Clears the history of
|                              |                                                                                                     | the currently active `Console`.
| `screenshot`                 | `yli::ontology::Universe::screenshot`                                                               | Takes a screenshot.
|:---------------------------- |:--------------------------------------------------------------------------------------------------- |:---------------------------------
| mini-console callbacks       |                                                                                                     |
|:---------------------------- |:--------------------------------------------------------------------------------------------------- |:---------------------------------
| `miniactivate`               | `yli::ontology::Universe::activate_entity`                                                          | Activates a named `Entity`.
| `miniinfo`                   | `yli::ontology::Universe::info0`                                                                    | Prints info about Entities.
| `miniinfo`                   | `yli::ontology::Universe::info1`                                                                    | Prints info about
|                              |                                                                                                     | a named `Entity`.
