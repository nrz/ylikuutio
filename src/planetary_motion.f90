program planetary_motion

    use constants
    use planetary_system_mod
    use file_mod
    use string_mod
    use parser_mod

    ! These are needed for C++/Fortran interface used by unit tests implemented in C++.
    use, intrinsic :: iso_c_binding, only: c_char, c_f_pointer, c_ptr

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
    integer :: objects_header_line_i
    integer :: n_of_global_parameters_code_lines
    integer :: n_of_objects_code_lines
    logical :: parsing_success
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
        begin_objects_line_i, end_objects_line_i, &
        global_parameters_header_line_i, &
        objects_header_line_i)

    if (parsing_success) then
        write(stdout, "(A27)") "Initial parsing successful."
    else
        write(stdout, "(A15)") "Parsing failed!"
        return
    end if

    n_of_global_parameters_code_lines = get_n_of_code_lines_between(fortran_file_content, file_sz, &
        global_parameters_header_line_i, end_global_parameters_line_i)

    n_of_objects_code_lines = get_n_of_code_lines_between(fortran_file_content, file_sz, &
        objects_header_line_i, end_objects_line_i)

    write(stdout, "(A41)", advance = "no") "Number of global parameters' code lines: "
    write(stdout, "(g0)") n_of_global_parameters_code_lines

    write(stdout, "(A41)", advance = "no") "Number of objects' code lines:           "
    write(stdout, "(g0)") n_of_objects_code_lines

    if (n_of_global_parameters_code_lines .ne. 1) then
        write(stdout, "(A65)") "ERROR: Number of global parameters' code lines must be exactly 1!"
        return
    end if

    call simulate(my_planetary_system)

contains

    ! Simulate the planetary system according to the given input.
    subroutine simulate(my_planetary_system)
        implicit none

        type(planetary_system) :: my_planetary_system

        write(stdout, "(A20)") "Hello from simulate!"

    end subroutine simulate

end program planetary_motion
