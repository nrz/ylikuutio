module parser_mod
    use constants
    use string_mod
    use planetary_system_mod

    implicit none

    character(len = *), parameter :: begin_global_parameters_string = "begin global_parameters"
    character(len = *), parameter :: end_global_parameters_string = "end global_parameters"
    character(len = *), parameter :: begin_objects_string = "begin objects"
    character(len = *), parameter :: end_objects_string = "end objects"
    character(len = *), parameter :: global_parameters_header_string = &
        "number_of_objects, length_of_timestep, total_length_of_simulation, print_interval"
    character(len = *), parameter :: objects_header_string = &
        "mass, x, y, z, vx, vy, vz, name, apparent_size, red, green, blue"

contains

    logical function parse(file_content, file_sz, &
            begin_global_parameters_line_i, end_global_parameters_line_i, &
            begin_objects_line_i, end_objects_line_i, &
            global_parameters_header_line_i, &
            objects_header_line_i)
        ! These are needed for C++/Fortran interface used by unit tests implemented in C++.
        use, intrinsic :: iso_c_binding, only: c_f_pointer, c_char, c_int, c_ptr

        implicit none
        character(kind = c_char), dimension(file_sz), intent(in) :: file_content
        integer(kind = c_int), intent(in), value :: file_sz
        integer(kind = c_int), intent(out) :: begin_global_parameters_line_i
        integer(kind = c_int), intent(out) :: end_global_parameters_line_i
        integer(kind = c_int), intent(out) :: begin_objects_line_i
        integer(kind = c_int), intent(out) :: end_objects_line_i
        integer(kind = c_int), intent(out) :: global_parameters_header_line_i
        integer(kind = c_int), intent(out) :: objects_header_line_i
        character(kind = c_char), pointer, dimension(:) :: fortran_temp_line
        type(c_ptr) :: temp_line
        integer :: line_i, line_sz
        logical :: has_line_code

        ! Parse correctly by default, set to `.false.` on any parse error.
        parse = .true.

        begin_global_parameters_line_i = -1
        end_global_parameters_line_i = -1
        begin_objects_line_i = -1
        end_objects_line_i = -1
        global_parameters_header_line_i = -1
        objects_header_line_i = -1

        begin_global_parameters_line_i = get_line_i_with_n_token_statement(file_content, file_sz, &
            begin_global_parameters_string, len(begin_global_parameters_string))

        if (begin_global_parameters_line_i .ge. 1) then
            write(stdout, "(A40)", advance = "no") "`begin global_parameters` found on line "
            write(stdout, "(g0)") begin_global_parameters_line_i
        else
            write(stdout, "(A86)") &
                "`begin global_parameters` not found! Please check provided `input.dat` for an example!"
            parse = .false.
            return
        end if

        end_global_parameters_line_i = get_line_i_with_n_token_statement(file_content, file_sz, &
            end_global_parameters_string, len(end_global_parameters_string))

        if (end_global_parameters_line_i .ge. 1) then
            write(stdout, "(A40)", advance = "no") "`end global_parameters` found on line   "
            write(stdout, "(g0)") end_global_parameters_line_i
        else
            write(stdout, "(A84)") &
                "`end global_parameters` not found! Please check provided `input.dat` for an example!"
            parse = .false.
            return
        end if

        begin_objects_line_i = get_line_i_with_n_token_statement(file_content, file_sz, &
            begin_objects_string, len(begin_objects_string))

        if (begin_objects_line_i .ge. 1) then
            write(stdout, "(A40)", advance = "no") "`begin objects` found on line           "
            write(stdout, "(g0)") begin_objects_line_i
        else
            write(stdout, "(A76)") &
                "`begin objects` not found! Please check provided `input.dat` for an example!"
            parse = .false.
            return
        end if

        end_objects_line_i = get_line_i_with_n_token_statement(file_content, file_sz, &
            end_objects_string, len(end_objects_string))

        if (end_objects_line_i .ge. 1) then
            write(stdout, "(A40)", advance = "no") "`end objects` found on line             "
            write(stdout, "(g0)") end_objects_line_i
        else
            write(stdout, "(A74)") &
                "`end objects` not found! Please check provided `input.dat` for an example!"
            parse = .false.
            return
        end if

        ! Check that the statements of the input file are in correct order.

        if (.not. (begin_global_parameters_line_i < end_global_parameters_line_i .and. &
            end_global_parameters_line_i < begin_objects_line_i .and. &
            begin_objects_line_i < end_objects_line_i)) then
            write(stdout, "(A48)") "`begin` and `end` statements are in wrong order!"
            write(stdout, "(A49)") "Please check provided `input.dat` for an example!"
            parse = .false.
            return
        end if

        ! The data blocks of the input file are valid and in correct order.

        ! Process `global_parameters` block.
        global_parameters_header_line_i = get_line_i_with_n_token_statement(file_content, file_sz, &
            global_parameters_header_string, len(global_parameters_header_string))

        if (global_parameters_header_line_i .ge. 1) then
            write(stdout, "(A40)", advance = "no") "Global parameters' header found on line "
            write(stdout, "(g0)") global_parameters_header_line_i
        else
            write(stdout, "(A86)") &
                "Global parameters' header not found! Please check provided `input.dat` for an example!"
            parse = .false.
            return
        end if

        ! Process `objects` block.

        objects_header_line_i = get_line_i_with_n_token_statement(file_content, file_sz, &
            objects_header_string, len(objects_header_string))

        if (objects_header_line_i .ge. 1) then
            write(stdout, "(A40)", advance = "no") "Objects' header found on line           "
            write(stdout, "(g0)") objects_header_line_i
        else
            write(stdout, "(A76)") &
                "Objects' header not found! Please check provided `input.dat` for an example!"
            parse = .false.
            return
        end if

        ! Check that the header statement of global parameters is inside the block.

        if (.not.(global_parameters_header_line_i .gt. begin_global_parameters_line_i .and. &
            global_parameters_header_line_i .lt. end_global_parameters_line_i)) then
            write(stdout, "(A63)") "Global parameters' header is outside `global_parameters` block!"
            write(stdout, "(A49)") "Please check provided `input.dat` for an example!"
            parse = .false.
            return
        end if

        ! Check that the header statement of global parameters is inside the block.

        if (.not.(objects_header_line_i .gt. begin_objects_line_i .and. &
            objects_header_line_i .lt. end_objects_line_i)) then
            write(stdout, "(A43)") "Objects' header is outside `objects` block!"
            write(stdout, "(A49)") "Please check provided `input.dat` for an example!"
            parse = .false.
            return
        end if

        ! Check that there are no junk lines between `begin global_parameters` line and the header line.

        do line_i = begin_global_parameters_line_i + 1, global_parameters_header_line_i - 1
            temp_line = get_line(file_content, file_sz, line_i, line_sz)

            if (line_sz .lt. 0) then
                write(stdout, "(A97)") &
                    "Parse error in `begin global_parameters` block! This should never happen! The line was not found!"
                parse = .false.
                return
            end if

            ! `temp_line` is `c_ptr`. It needs to be converted into a Fortran pointer.
            call c_f_pointer(temp_line, fortran_temp_line, [ line_sz ])

            has_line_code = get_has_line_code(fortran_temp_line, line_sz)
            deallocate(fortran_temp_line)

            if (has_line_code) then
                write(stdout, "(A78)", advance = "no") &
                    "Junk found between `begin global_parameters` line and the header line on line "
                write(stdout, "(g0)") line_i
                write(stdout, "(A49)") "Please check provided `input.dat` for an example!"
                parse = .false.
                return
            end if
        end do

        ! Check that there are no junk lines between `begin objects` line and the header line.

        do line_i = begin_objects_line_i + 1, objects_header_line_i - 1
            temp_line = get_line(file_content, file_sz, line_i, line_sz)

            if (line_sz .lt. 0) then
                write(stdout, "(A87)") &
                    "Parse error in `begin objects` block! This should never happen! The line was not found!"
                parse = .false.
                return
            end if

            ! `temp_line` is `c_ptr`. It needs to be converted into a Fortran pointer.
            call c_f_pointer(temp_line, fortran_temp_line, [ line_sz ])

            has_line_code = get_has_line_code(fortran_temp_line, line_sz)
            deallocate(fortran_temp_line)

            if (has_line_code) then
                write(stdout, "(A68)", advance = "no") &
                    "Junk found between `begin objects` line and the header line on line "
                write(stdout, "(g0)") line_i
                write(stdout, "(A49)") "Please check provided `input.dat` for an example!"
                parse = .false.
                return
            end if
        end do
    end function parse

end module parser_mod
