program planetary_motion

    use my_kind
    use constants
    use string_mod
    use object_mod
    use planetary_system_mod
    use file_mod

    ! These are needed for C++/Fortran interface used by unit tests implemented in C++.
    use, intrinsic :: iso_c_binding, only: c_ptr

    implicit none

    character(len = :), allocatable :: filename
    character(len = :), allocatable :: begin_string, end_string
    character(len = :), allocatable :: global_parameters_string, objects_string
    type(c_ptr) :: file_content
    integer :: file_status

    ! Objects are stored in the a vector of objects.
    type(planetary_system) :: my_planetary_system

    filename = "input.dat"

    write(stdout, "(A28)") "Hello from planetary motion!"

    ! Read the simulation data from a file into a `planetary_system` record.
    file_content = read_file(filename, len(filename), file_status)

    if (file_status .eq. 1) then
        write(stdout, "(A27)") "File was read successfully!"
    else if (file_status .eq. 1) then
        write(stdout, "(A27)") "ERROR: file reading failed!"
    else
        write(stdout, "(A35)") "ERROR: Unknown file reading status!"
    end if

    write(stdout, "(A17)", advance = "no") "File read status: "
    write(stdout, "(g0)") file_status

    begin_string = "begin"
    end_string = "begin"

    global_parameters_string = "global_parameters"
    objects_string = "objects"

    call simulate(my_planetary_system)

contains

    ! Simulate the planetary system according to the given input.
    subroutine simulate(my_planetary_system)
        implicit none

        type(planetary_system) :: my_planetary_system

        write(stdout, "(A20)") "Hello from simulate!"

    end subroutine simulate

end program planetary_motion
