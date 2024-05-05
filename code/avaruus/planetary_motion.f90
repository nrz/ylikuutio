! Ylikuutio - A 3D game and simulation engine.
!
! Copyright (C) 2015-2024 Antti Nuortimo.
!
! This program is free software: you can redistribute it and/or modify
! it under the terms of the GNU Affero General Public License as
! published by the Free Software Foundation, either version 3 of the
! License, or (at your option) any later version.
!
! This program is distributed in the hope that it will be useful,
! but WITHOUT ANY WARRANTY; without even the implied warranty of
! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
! GNU Affero General Public License for more details.
!
! You should have received a copy of the GNU Affero General Public License
! along with this program.  If not, see <https://www.gnu.org/licenses/>.

program planetary_motion

    use constants
    use global_parameters_mod
    use planetary_system_mod
    use file_mod
    use parser_mod
    use physics_mod

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
    logical :: simulation_success
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

    simulation_success = simulate(my_global_parameters, my_planetary_system)

    if (simulation_success) then
        write(stdout, "(A39)") "Planetary motion simulation successful."
    else
        write(stdout, "(A35)") "Planetary motion simulation failed."
    end if

end program planetary_motion
