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
        "number_of_objects , length_of_timestep , total_length_of_simulation , print_interval , save_interval"
    character(len = *), parameter :: objects_header_string = &
        "mass , x , y , z , vx , vy , vz , name , apparent_size , red , green , blue"

contains

    logical function parse(file_content, file_sz, &
            begin_global_parameters_line_i, end_global_parameters_line_i, &
            begin_objects_line_i, end_objects_line_i)
        ! These are needed for C++/Fortran interface used by unit tests implemented in C++.
        use, intrinsic :: iso_c_binding, only: c_f_pointer, c_char, c_int, c_ptr

        implicit none
        character(kind = c_char), dimension(file_sz), intent(in) :: file_content
        integer(kind = c_int), intent(in), value :: file_sz
        integer(kind = c_int), intent(out) :: begin_global_parameters_line_i
        integer(kind = c_int), intent(out) :: end_global_parameters_line_i
        integer(kind = c_int), intent(out) :: begin_objects_line_i
        integer(kind = c_int), intent(out) :: end_objects_line_i
        character(kind = c_char), pointer, dimension(:) :: fortran_temp_line

        ! Parse correctly by default, set to `.false.` on any parse error.
        parse = .true.

        begin_global_parameters_line_i = -1
        end_global_parameters_line_i = -1
        begin_objects_line_i = -1
        end_objects_line_i = -1

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
        parse = .true.

    end function parse

    ! Parse `global_parameters` block.
    logical function parse_global_parameters(file_content, file_sz, &
            begin_global_parameters_line_i, end_global_parameters_line_i, &
            global_parameters_header_line_i, global_parameters_value_line_i, &
            n_objects, length_of_timestep, total_length_of_simulation, print_interval, save_interval)
        ! These are needed for C++/Fortran interface used by unit tests implemented in C++.
        use, intrinsic :: iso_c_binding, only: c_f_pointer, c_char, c_int, c_double, c_ptr

        implicit none
        character(kind = c_char), dimension(file_sz), intent(in) :: file_content
        integer(kind = c_int), intent(in), value :: file_sz
        integer(kind = c_int), intent(in), value :: begin_global_parameters_line_i
        integer(kind = c_int), intent(in), value :: end_global_parameters_line_i
        integer(kind = c_int), intent(out) :: global_parameters_header_line_i
        integer(kind = c_int), intent(out) :: global_parameters_value_line_i
        integer(kind = c_int), intent(out) :: n_objects
        real(kind = c_double), intent(out) :: length_of_timestep
        real(kind = c_double), intent(out) :: total_length_of_simulation
        integer(kind = c_int), intent(out) :: print_interval
        integer(kind = c_int), intent(out) :: save_interval
        character(kind = c_char), pointer, dimension(:) :: fortran_file_content
        character(kind = c_char), pointer, dimension(:) :: fortran_temp_line
        character(kind = c_char), pointer, dimension(:) :: fortran_temp_token
        integer(kind = c_int) :: i, line_i, line_sz, value_line_i, column_i, next_offset, token_sz
        logical :: has_line_code
        type(c_ptr) :: temp_line, temp_token
        integer(kind = c_int) :: n_of_global_parameters_code_lines
        integer :: ios
        character(len = :), allocatable :: field

        parse_global_parameters = .false.
        global_parameters_header_line_i = -1
        global_parameters_value_line_i = -1

        ! Process `global_parameters` block.
        global_parameters_header_line_i = get_line_i_with_n_token_statement(file_content, file_sz, &
            global_parameters_header_string, len(global_parameters_header_string))

        if (global_parameters_header_line_i .ge. 1) then
            write(stdout, "(A40)", advance = "no") "Global parameters' header found on line "
            write(stdout, "(g0)") global_parameters_header_line_i
        else
            write(stdout, "(A86)") &
                "Global parameters' header not found! Please check provided `input.dat` for an example!"
            return
        end if

        ! Check that the header statement of global parameters is inside the block.

        if (.not.(global_parameters_header_line_i .gt. begin_global_parameters_line_i .and. &
            global_parameters_header_line_i .lt. end_global_parameters_line_i)) then
            write(stdout, "(A63)") "Global parameters' header is outside `global_parameters` block!"
            write(stdout, "(A49)") "Please check provided `input.dat` for an example!"
            return
        end if

        ! Check that there are no junk lines between `begin global_parameters` line and the header line.

        do line_i = begin_global_parameters_line_i + 1, global_parameters_header_line_i - 1
            temp_line = get_line(file_content, file_sz, line_i, line_sz)

            ! `temp_line` is `c_ptr`. It needs to be converted into a Fortran pointer.
            call c_f_pointer(temp_line, fortran_temp_line, [ line_sz ])

            if (line_sz .lt. 0) then
                write(stdout, "(A91)") &
                    "Parse error in `global_parameters` block! This should never happen! The line was not found!"
                deallocate(fortran_temp_line)
                return
            end if

            has_line_code = get_has_line_code(fortran_temp_line, line_sz)
            deallocate(fortran_temp_line)

            if (has_line_code) then
                write(stdout, "(A78)", advance = "no") &
                    "Junk found between `begin global_parameters` line and the header line on line "
                write(stdout, "(g0)") line_i
                write(stdout, "(A49)") "Please check provided `input.dat` for an example!"
                return
            end if
        end do

        n_of_global_parameters_code_lines = get_n_of_code_lines_between(file_content, file_sz, &
            global_parameters_header_line_i, end_global_parameters_line_i)

        write(stdout, "(A41)", advance = "no") "Number of global parameters' code lines: "
        write(stdout, "(g0)") n_of_global_parameters_code_lines

        if (n_of_global_parameters_code_lines .ne. 1) then
            write(stdout, "(A65)") "ERROR: Number of global parameters' code lines must be exactly 1!"
            return
        end if

        do line_i = global_parameters_header_line_i + 1, end_global_parameters_line_i - 1
            temp_line = get_line(file_content, file_sz, line_i, line_sz)

            ! `temp_line` is `c_ptr`. It needs to be converted into a Fortran pointer.
            call c_f_pointer(temp_line, fortran_temp_line, [ line_sz ])

            if (line_sz .lt. 0) then
                write(stdout, "(A81)") &
                    "Parse error in `objects` block! This should never happen! The line was not found!"
                deallocate(fortran_temp_line)
                return
            end if

            has_line_code = get_has_line_code(fortran_temp_line, line_sz)

            global_parameters_value_line_i = line_i

            if (has_line_code) then
                write(stdout, "(A40)", advance = "no") "Global parameters' values found on line "
                write(stdout, "(g0)") global_parameters_value_line_i

                column_i = 1     ! Start from the 1st byte.
                next_offset = -1 ! The value will be overwritten by `get_nth_token`.

                temp_token = get_nth_token(fortran_temp_line, line_sz, column_i, next_offset, token_sz)

                ! `temp_token` is `c_ptr`. It needs to be converted into a Fortran pointer.
                call c_f_pointer(temp_token, fortran_temp_token, [ token_sz ])

                allocate(character(token_sz) :: field)
                do i = 1, token_sz
                    field(i:i) = fortran_temp_token(i)
                end do

                read(field, *, iostat = ios) n_objects
                deallocate(field)

                if (ios < 0) then
                    write(stdout, "(A26)") "Error reading `n_objects`!"
                end if
                deallocate(fortran_temp_token)

                column_i = column_i + 2
                temp_token = get_nth_token(fortran_temp_line, line_sz, column_i, next_offset, token_sz)

                ! `temp_token` is `c_ptr`. It needs to be converted into a Fortran pointer.
                call c_f_pointer(temp_token, fortran_temp_token, [ token_sz ])

                allocate(character(token_sz) :: field)
                do i = 1, token_sz
                    field(i:i) = fortran_temp_token(i)
                end do

                read(field, *, iostat = ios) length_of_timestep
                deallocate(field)
                if (ios < 0) then
                    write(stdout, "(A35)") "Error reading `length_of_timestep`!"
                end if
                deallocate(fortran_temp_token)

                column_i = column_i + 2
                temp_token = get_nth_token(fortran_temp_line, line_sz, column_i, next_offset, token_sz)

                ! `temp_token` is `c_ptr`. It needs to be converted into a Fortran pointer.
                call c_f_pointer(temp_token, fortran_temp_token, [ token_sz ])

                allocate(character(token_sz) :: field)
                do i = 1, token_sz
                    field(i:i) = fortran_temp_token(i)
                end do

                read(field, *, iostat = ios) total_length_of_simulation
                deallocate(field)
                if (ios < 0) then
                    write(stdout, "(A43)") "Error reading `total_length_of_simulation`!"
                end if
                deallocate(fortran_temp_token)

                column_i = column_i + 2
                temp_token = get_nth_token(fortran_temp_line, line_sz, column_i, next_offset, token_sz)

                ! `temp_token` is `c_ptr`. It needs to be converted into a Fortran pointer.
                call c_f_pointer(temp_token, fortran_temp_token, [ token_sz ])

                allocate(character(token_sz) :: field)
                do i = 1, token_sz
                    field(i:i) = fortran_temp_token(i)
                end do

                read(field, *, iostat = ios) print_interval
                deallocate(field)
                if (ios < 0) then
                    write(stdout, "(A31)") "Error reading `print_interval`!"
                end if
                deallocate(fortran_temp_token)

                column_i = column_i + 2
                temp_token = get_nth_token(fortran_temp_line, line_sz, column_i, next_offset, token_sz)

                ! `temp_token` is `c_ptr`. It needs to be converted into a Fortran pointer.
                call c_f_pointer(temp_token, fortran_temp_token, [ token_sz ])

                ! No comma after the last field!
                allocate(character(token_sz) :: field)
                do i = 1, token_sz
                    field(i:i) = fortran_temp_token(i)
                end do

                read(field, *, iostat = ios) save_interval
                deallocate(field)
                if (ios < 0) then
                    write(stdout, "(A30)") "Error reading `save_interval`!"
                end if
                deallocate(fortran_temp_token)

                deallocate(fortran_temp_line)
                parse_global_parameters = .true.
                return
            end if

            deallocate(fortran_temp_line)
        end do
    end function parse_global_parameters

    ! Parse `objects` block.
    logical function parse_objects(file_content, file_sz, n_objects, &
            begin_objects_line_i, end_objects_line_i, objects_header_line_i, &
            my_planetary_system)
        ! These are needed for C++/Fortran interface used by unit tests implemented in C++.
        use, intrinsic :: iso_c_binding, only: c_f_pointer, c_char, c_int, c_ptr

        implicit none
        character(kind = c_char), dimension(file_sz), intent(in) :: file_content
        integer(kind = c_int), intent(in), value :: file_sz
        integer(kind = c_int), intent(in), value :: n_objects
        integer(kind = c_int), intent(in), value :: begin_objects_line_i
        integer(kind = c_int), intent(in), value :: end_objects_line_i
        integer(kind = c_int), intent(out) :: objects_header_line_i
        type(planetary_system), intent(out) :: my_planetary_system
        character(kind = c_char), pointer, dimension(:) :: fortran_file_content
        character(kind = c_char), pointer, dimension(:) :: fortran_temp_line
        character(kind = c_char), pointer, dimension(:) :: fortran_temp_token
        integer(kind = c_int) :: i, object_i, column_i, next_offset, token_sz
        integer :: line_i, line_sz
        logical :: has_line_code
        type(c_ptr) :: temp_line, temp_token
        integer :: n_of_objects_code_lines, n_objects_read
        integer :: ios
        character(len = :), allocatable :: field
        type(object) :: object

        parse_objects = .false.
        objects_header_line_i = -1

        objects_header_line_i = get_line_i_with_n_token_statement(file_content, file_sz, &
            objects_header_string, len(objects_header_string))

        if (objects_header_line_i .ge. 1) then
            write(stdout, "(A40)", advance = "no") "Objects' header found on line           "
            write(stdout, "(g0)") objects_header_line_i
        else
            write(stdout, "(A76)") &
                "Objects' header not found! Please check provided `input.dat` for an example!"
            return
        end if

        ! Check that the header statement of objects is inside the block.

        if (.not.(objects_header_line_i .gt. begin_objects_line_i .and. &
            objects_header_line_i .lt. end_objects_line_i)) then
            write(stdout, "(A43)") "Objects' header is outside `objects` block!"
            write(stdout, "(A49)") "Please check provided `input.dat` for an example!"
            return
        end if

        ! Check that there are no junk lines between `begin objects` line and the header line.

        do line_i = begin_objects_line_i + 1, objects_header_line_i - 1
            temp_line = get_line(file_content, file_sz, line_i, line_sz)

            ! `temp_line` is `c_ptr`. It needs to be converted into a Fortran pointer.
            call c_f_pointer(temp_line, fortran_temp_line, [ line_sz ])

            if (line_sz .lt. 0) then
                write(stdout, "(A81)") &
                    "Parse error in `objects` block! This should never happen! The line was not found!"
                deallocate(fortran_temp_line)
                return
            end if

            has_line_code = get_has_line_code(fortran_temp_line, line_sz)
            deallocate(fortran_temp_line)

            if (has_line_code) then
                write(stdout, "(A68)", advance = "no") &
                    "Junk found between `begin objects` line and the header line on line "
                write(stdout, "(g0)") line_i
                write(stdout, "(A49)") "Please check provided `input.dat` for an example!"
                return
            end if
        end do

        n_of_objects_code_lines = get_n_of_code_lines_between(file_content, file_sz, &
            objects_header_line_i, end_objects_line_i)

        write(stdout, "(A40)", advance = "no") "Number of objects' code lines:          "
        write(stdout, "(g0)") n_of_objects_code_lines

        if (n_of_objects_code_lines .lt. n_objects) then
            write(stdout, "(A40)") "Less objects' code lines than n_objects!"
            my_planetary_system % n_objects = n_of_objects_code_lines
        else
            my_planetary_system % n_objects = n_objects
        end if

        allocate(my_planetary_system % objects(n_of_objects_code_lines))

        ! The count of actual read objects so far.
        n_objects_read = 0

        object_i = 1

        objects_loop: do line_i = objects_header_line_i + 1, end_objects_line_i
            if (n_objects_read .ge. my_planetary_system % n_objects) then
                ! Enough objects read!
                exit
            end if

            ! Find the next line with code.
            temp_line = get_line(file_content, file_sz, line_i, line_sz)

            ! `temp_line` is `c_ptr`. It needs to be converted into a Fortran pointer.
            call c_f_pointer(temp_line, fortran_temp_line, [ line_sz ])

            if (line_sz .lt. 0) then
                write(stdout, "(A81)") &
                    "Parse error in `objects` block! This should never happen! The line was not found!"
                deallocate(fortran_temp_line)
                return
            end if

            has_line_code = get_has_line_code(fortran_temp_line, line_sz)

            if (.not.(has_line_code)) then
                ! No code on this line, cycle to the next line.
                deallocate(fortran_temp_line)
                cycle
            end if

            ! Read an object.

            column_i = 1     ! Start from the 1st byte.
            next_offset = -1 ! The value will be overwritten by `get_nth_token`.

            temp_token = get_nth_token(fortran_temp_line, line_sz, column_i, next_offset, token_sz)

            ! `temp_token` is `c_ptr`. It needs to be converted into a Fortran pointer.
            call c_f_pointer(temp_token, fortran_temp_token, [ token_sz ])

            allocate(character(token_sz) :: field)
            do i = 1, token_sz
                field(i:i) = fortran_temp_token(i)
            end do

            read(field, *, iostat = ios) object % mass
            deallocate(field)

            if (ios < 0) then
                write(stdout, "(A21)") "Error reading `mass`!"
                deallocate(fortran_temp_token)
                deallocate(fortran_temp_line)
                return
            end if
            deallocate(fortran_temp_token)

            column_i = column_i + 2
            temp_token = get_nth_token(fortran_temp_line, line_sz, column_i, next_offset, token_sz)

            ! `temp_token` is `c_ptr`. It needs to be converted into a Fortran pointer.
            call c_f_pointer(temp_token, fortran_temp_token, [ token_sz ])

            allocate(character(token_sz) :: field)
            do i = 1, token_sz
                field(i:i) = fortran_temp_token(i)
            end do

            read(field, *, iostat = ios) object % position(1)
            deallocate(field)
            if (ios < 0) then
                write(stdout, "(A18)") "Error reading `x`!"
                deallocate(fortran_temp_token)
                deallocate(fortran_temp_line)
                return
            end if
            deallocate(fortran_temp_token)

            column_i = column_i + 2
            temp_token = get_nth_token(fortran_temp_line, line_sz, column_i, next_offset, token_sz)

            ! `temp_token` is `c_ptr`. It needs to be converted into a Fortran pointer.
            call c_f_pointer(temp_token, fortran_temp_token, [ token_sz ])

            allocate(character(token_sz) :: field)
            do i = 1, token_sz
                field(i:i) = fortran_temp_token(i)
            end do

            read(field, *, iostat = ios) object % position(2)
            deallocate(field)
            if (ios < 0) then
                write(stdout, "(A18)") "Error reading `y`!"
                deallocate(fortran_temp_token)
                deallocate(fortran_temp_line)
                return
            end if
            deallocate(fortran_temp_token)

            column_i = column_i + 2
            temp_token = get_nth_token(fortran_temp_line, line_sz, column_i, next_offset, token_sz)

            ! `temp_token` is `c_ptr`. It needs to be converted into a Fortran pointer.
            call c_f_pointer(temp_token, fortran_temp_token, [ token_sz ])

            allocate(character(token_sz) :: field)
            do i = 1, token_sz
                field(i:i) = fortran_temp_token(i)
            end do

            read(field, *, iostat = ios) object % position(3)
            deallocate(field)
            if (ios < 0) then
                write(stdout, "(A18)") "Error reading `z`!"
                deallocate(fortran_temp_token)
                deallocate(fortran_temp_line)
                return
            end if
            deallocate(fortran_temp_token)

            column_i = column_i + 2
            temp_token = get_nth_token(fortran_temp_line, line_sz, column_i, next_offset, token_sz)

            ! `temp_token` is `c_ptr`. It needs to be converted into a Fortran pointer.
            call c_f_pointer(temp_token, fortran_temp_token, [ token_sz ])

            allocate(character(token_sz) :: field)
            do i = 1, token_sz
                field(i:i) = fortran_temp_token(i)
            end do

            read(field, *, iostat = ios) object % velocity(1)
            deallocate(field)
            if (ios < 0) then
                write(stdout, "(A19)") "Error reading `vx`!"
                deallocate(fortran_temp_token)
                deallocate(fortran_temp_line)
                return
            end if
            deallocate(fortran_temp_token)

            column_i = column_i + 2
            temp_token = get_nth_token(fortran_temp_line, line_sz, column_i, next_offset, token_sz)

            ! `temp_token` is `c_ptr`. It needs to be converted into a Fortran pointer.
            call c_f_pointer(temp_token, fortran_temp_token, [ token_sz ])

            allocate(character(token_sz) :: field)
            do i = 1, token_sz
                field(i:i) = fortran_temp_token(i)
            end do

            read(field, *, iostat = ios) object % velocity(2)
            deallocate(field)
            if (ios < 0) then
                write(stdout, "(A19)") "Error reading `vy`!"
                deallocate(fortran_temp_token)
                deallocate(fortran_temp_line)
                return
            end if
            deallocate(fortran_temp_token)

            column_i = column_i + 2
            temp_token = get_nth_token(fortran_temp_line, line_sz, column_i, next_offset, token_sz)

            ! `temp_token` is `c_ptr`. It needs to be converted into a Fortran pointer.
            call c_f_pointer(temp_token, fortran_temp_token, [ token_sz ])

            allocate(character(token_sz) :: field)
            do i = 1, token_sz
                field(i:i) = fortran_temp_token(i)
            end do

            read(field, *, iostat = ios) object % velocity(3)
            deallocate(field)
            if (ios < 0) then
                write(stdout, "(A19)") "Error reading `vz`!"
                deallocate(fortran_temp_token)
                deallocate(fortran_temp_line)
                return
            end if
            deallocate(fortran_temp_token)

            column_i = column_i + 2
            temp_token = get_nth_token(fortran_temp_line, line_sz, column_i, next_offset, token_sz)

            ! `temp_token` is `c_ptr`. It needs to be converted into a Fortran pointer.
            call c_f_pointer(temp_token, fortran_temp_token, [ token_sz ])

            if (fortran_temp_token(1) .ne. '"' .or. fortran_temp_token(token_sz) .ne. '"') then
                write(stdout, "(A45)") "Object's name must be given in double quotes!"
                deallocate(fortran_temp_token)
                deallocate(fortran_temp_line)
                return
            else
                allocate(character(token_sz) :: object % name)
                do i = 1, token_sz
                    object % name(i:i) = fortran_temp_token(i)
                end do
            end if
            deallocate(fortran_temp_token)

            column_i = column_i + 2
            temp_token = get_nth_token(fortran_temp_line, line_sz, column_i, next_offset, token_sz)

            ! `temp_token` is `c_ptr`. It needs to be converted into a Fortran pointer.
            call c_f_pointer(temp_token, fortran_temp_token, [ token_sz ])

            allocate(character(token_sz) :: field)
            do i = 1, token_sz
                field(i:i) = fortran_temp_token(i)
            end do

            read(field, *, iostat = ios) object % apparent_size
            deallocate(field)
            if (ios < 0) then
                write(stdout, "(A30)") "Error reading `apparent_size`!"
                deallocate(fortran_temp_token)
                deallocate(fortran_temp_line)
                return
            end if
            deallocate(fortran_temp_token)

            column_i = column_i + 2
            temp_token = get_nth_token(fortran_temp_line, line_sz, column_i, next_offset, token_sz)

            ! `temp_token` is `c_ptr`. It needs to be converted into a Fortran pointer.
            call c_f_pointer(temp_token, fortran_temp_token, [ token_sz ])

            allocate(character(token_sz) :: field)
            do i = 1, token_sz
                field(i:i) = fortran_temp_token(i)
            end do

            read(field, *, iostat = ios) object % red
            deallocate(field)
            if (ios < 0) then
                write(stdout, "(A20)") "Error reading `red`!"
                deallocate(fortran_temp_token)
                deallocate(fortran_temp_line)
                return
            end if
            deallocate(fortran_temp_token)

            column_i = column_i + 2
            temp_token = get_nth_token(fortran_temp_line, line_sz, column_i, next_offset, token_sz)

            ! `temp_token` is `c_ptr`. It needs to be converted into a Fortran pointer.
            call c_f_pointer(temp_token, fortran_temp_token, [ token_sz ])

            allocate(character(token_sz) :: field)
            do i = 1, token_sz
                field(i:i) = fortran_temp_token(i)
            end do

            read(field, *, iostat = ios) object % green
            deallocate(field)
            if (ios < 0) then
                write(stdout, "(A22)") "Error reading `green`!"
                deallocate(fortran_temp_token)
                deallocate(fortran_temp_line)
                return
            end if
            deallocate(fortran_temp_token)

            column_i = column_i + 2
            temp_token = get_nth_token(fortran_temp_line, line_sz, column_i, next_offset, token_sz)

            ! `temp_token` is `c_ptr`. It needs to be converted into a Fortran pointer.
            call c_f_pointer(temp_token, fortran_temp_token, [ token_sz ])

            allocate(character(token_sz) :: field)
            do i = 1, token_sz
                field(i:i) = fortran_temp_token(i)
            end do

            read(field, *, iostat = ios) object % blue
            deallocate(field)
            if (ios < 0) then
                write(stdout, "(A21)") "Error reading `blue`!"
                deallocate(fortran_temp_token)
                deallocate(fortran_temp_line)
                return
            end if
            deallocate(fortran_temp_token)

            deallocate(fortran_temp_line)

            ! Store the object.
            my_planetary_system % objects(object_i) = object

            deallocate(object % name)

            object_i = object_i + 1
            n_objects_read = n_objects_read + 1
        end do objects_loop

        parse_objects = .true.
    end function parse_objects

end module parser_mod
