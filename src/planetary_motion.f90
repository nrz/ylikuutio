program planetary_motion

    use my_kind
    use constants
    use string_mod
    use object_mod
    use planetary_system_mod
    use file_mod

    ! These are needed for C++/Fortran interface used by unit tests implemented in C++.
    use, intrinsic :: iso_c_binding, only: c_char, c_f_pointer, c_ptr

    implicit none

    character(len = :), allocatable :: filename
    character(len = :), allocatable :: begin_global_parameters_string
    character(len = :), allocatable :: end_global_parameters_string
    character(len = :), allocatable :: begin_objects_string
    character(len = :), allocatable :: end_objects_string
    character(len = :), allocatable :: begin_string, end_string
    character(len = :), allocatable :: global_parameters_string, objects_string
    type(c_ptr) :: file_content
    integer :: file_sz
    character(kind = c_char), pointer, dimension(:) :: fortran_file_content
    integer :: begin_global_parameters_line_i, end_global_parameters_line_i
    integer :: begin_objects_line_i, end_objects_line_i
    type(planetary_system) :: my_planetary_system ! Objects are stored in the a vector of objects.

    begin_global_parameters_string = "begin global_parameters"
    end_global_parameters_string = "end global_parameters"
    begin_objects_string = "begin objects"
    end_objects_string = "end objects"

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

    begin_global_parameters_line_i = get_line_i_with_n_token_statement(fortran_file_content, file_sz, &
        begin_global_parameters_string, len(begin_global_parameters_string))

    if (begin_global_parameters_line_i .ge. 1) then
        write(stdout, "(A40)", advance = "no") "`begin global_parameters` found on line "
        write(stdout, "(g0)") begin_global_parameters_line_i
    else
        write(stdout, "(A86)") &
            "`begin global_parameters` not found! Please check provided `input.dat` for an example!"
        return
    end if

    end_global_parameters_line_i = get_line_i_with_n_token_statement(fortran_file_content, file_sz, &
        end_global_parameters_string, len(end_global_parameters_string))

    if (end_global_parameters_line_i .ge. 1) then
        write(stdout, "(A40)", advance = "no") "`end global_parameters` found on line   "
        write(stdout, "(g0)") end_global_parameters_line_i
    else
        write(stdout, "(A84)") &
            "`end global_parameters` not found! Please check provided `input.dat` for an example!"
        return
    end if

    begin_objects_line_i = get_line_i_with_n_token_statement(fortran_file_content, file_sz, &
        begin_objects_string, len(begin_objects_string))

    if (begin_objects_line_i .ge. 1) then
        write(stdout, "(A40)", advance = "no") "`begin objects` found on line           "
        write(stdout, "(g0)") begin_objects_line_i
    else
        write(stdout, "(A76)") &
            "`begin objects` not found! Please check provided `input.dat` for an example!"
        return
    end if

    end_objects_line_i = get_line_i_with_n_token_statement(fortran_file_content, file_sz, &
        end_objects_string, len(end_objects_string))

    if (end_objects_line_i .ge. 1) then
        write(stdout, "(A40)", advance = "no") "`end objects` found on line             "
        write(stdout, "(g0)") end_objects_line_i
    else
        write(stdout, "(A74)") &
            "`end objects` not found! Please check provided `input.dat` for an example!"
        return
    end if

    ! Check that the statements of the input file are in correct order.

    if (.not. (begin_global_parameters_line_i < end_global_parameters_line_i .and. &
        end_global_parameters_line_i < begin_objects_line_i .and. &
        begin_objects_line_i < end_objects_line_i)) then
        write(stdout, "(A48)") "`begin` and `end` statements are in wrong order!"
        write(stdout, "(A49)") "Please check provided `input.dat` for an example!"
        return
    end if

    ! The data blocks of the input file are valid and in correct order.

    ! Process `global_parameters` block.
    ! TODO

    ! Process `objects` block.
    ! TODO

    call simulate(my_planetary_system)

contains

    ! Simulate the planetary system according to the given input.
    subroutine simulate(my_planetary_system)
        implicit none

        type(planetary_system) :: my_planetary_system

        write(stdout, "(A20)") "Hello from simulate!"

    end subroutine simulate

end program planetary_motion
