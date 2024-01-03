program planetary_motion

    use constants
    use global_parameters_mod
    use planetary_system_mod
    use file_mod
    use parser_mod

    ! These are needed for C++/Fortran interface used by unit tests implemented in C++.
    use, intrinsic :: iso_c_binding, only: c_char, c_double, c_f_pointer, c_ptr

    implicit none

    character(len = :), allocatable :: filename
    type(c_ptr) :: file_content
    integer :: file_sz
    character(kind = c_char), pointer, dimension(:) :: fortran_file_content
    integer :: begin_global_parameters_line_i
    integer :: end_global_parameters_line_i
    integer :: begin_objects_line_i
    integer :: end_objects_line_i
    integer :: global_parameters_header_line_i
    integer :: global_parameters_value_line_i
    integer :: objects_header_line_i
    integer :: n_objects
    logical :: parsing_success
    logical :: global_parameters_parsing_success
    logical :: objects_parsing_success
    type(global_parameters) :: my_global_parameters
    type(planetary_system) :: my_planetary_system ! Objects are stored in the a vector of objects.

    filename = "input.dat"

    write(stdout, "(A28)") "Hello from planetary motion!"

    ! Read the simulation data from a file into a `planetary_system` record.
    file_content = read_file(filename, len(filename), file_sz)

    if (file_sz .ge. 1) then
        write(stdout, "(A27)") "File was read successfully!"
    else if (file_sz .eq. 1) then
        write(stdout, "(A35)") "ERROR: Unknown file reading status!"
    end if

    ! `file_content` is `c_ptr`. It needs to be converted into a Fortran pointer.
    call c_f_pointer(file_content, fortran_file_content, [ file_sz ])

    ! Check that all necessary statements of the input file are found.

    parsing_success = parse(fortran_file_content, file_sz, &
        begin_global_parameters_line_i, end_global_parameters_line_i, &
        begin_objects_line_i, end_objects_line_i)

    if (parsing_success) then
        write(stdout, "(A27)") "Initial parsing successful."
    else
        write(stdout, "(A15)") "Parsing failed!"
        return
    end if

    global_parameters_parsing_success = parse_global_parameters(fortran_file_content, file_sz, &
        begin_global_parameters_line_i, end_global_parameters_line_i, &
        global_parameters_header_line_i, global_parameters_value_line_i, &
        my_global_parameters % n_objects, &
        my_global_parameters % length_of_timestep, &
        my_global_parameters % total_length_of_simulation, &
        my_global_parameters % print_interval, &
        my_global_parameters % save_interval)

    if (global_parameters_parsing_success) then
        write(stdout, "(A43)") "Parsing global parameters block successful."
    else
        write(stdout, "(A39)") "Parsing global parameters block failed!"
        return
    end if

    call print_global_parameters(my_global_parameters)

    objects_parsing_success = parse_objects(fortran_file_content, file_sz, my_global_parameters % n_objects, &
        begin_objects_line_i, end_objects_line_i, objects_header_line_i, &
        my_planetary_system)

    if (objects_parsing_success) then
        write(stdout, "(A33)") "Parsing objects block successful."
    else
        write(stdout, "(A29)") "Parsing objects block failed!"
        return
    end if

    call print_objects(my_planetary_system)

    call simulate(my_planetary_system)

contains

    ! Simulate the planetary system according to the given input.
    subroutine simulate(my_planetary_system)
        implicit none

        type(planetary_system) :: my_planetary_system

        write(stdout, "(A20)") "Hello from simulate!"

    end subroutine simulate

end program planetary_motion
