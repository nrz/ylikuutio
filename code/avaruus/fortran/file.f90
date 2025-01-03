! Ylikuutio - A 3D game and simulation engine.
!
! Copyright (C) 2015-2025 Antti Nuortimo.
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

module file_mod

    use constants

    implicit none

contains

    ! Read file and return its contents as a `char*`.
    ! It's up to caller to deallocate the returned file content. A valid pointer (`c_ptr`) is returned always.
    ! `filename_sz` is needed as input parameter due to ISO C binding used by unit tests written in C++.
    function read_file(filename, filename_sz, file_sz)
        ! These are needed for C++/Fortran interface used by unit tests implemented in C++.
        use, intrinsic :: iso_c_binding, only: c_char, c_int, c_null_char, c_loc, c_ptr

        implicit none
        character(kind = c_char), dimension(filename_sz), intent(in) :: filename
        integer(kind = c_int), intent(in), value :: filename_sz
        integer(kind = c_int), intent(out) :: file_sz
        type(c_ptr) :: read_file
        integer, parameter :: unit_number = 1
        character(kind = c_char, len = filename_sz) :: filename_scalar
        character(kind = c_char, len = :), pointer, save :: temp_string
        integer :: ios, i
        logical :: are_inputs_valid

        are_inputs_valid = .true.
        file_sz = -1

        if (len(filename) .eq. 0) then
            print *, "Filename must not be an empty string!"
            are_inputs_valid = .false.
        else if (filename_sz .le. 0) then
            print *, "Given size of filename must be a positive integer!"
            are_inputs_valid = .false.
        end if

        if (.not. are_inputs_valid) then
            ! Allocate memory for the 0 needed for `c_str` (`char*`).
            allocate(character(1) :: temp_string)

            ! End the empty `c_str` with the necessary null character.
            temp_string = c_null_char

            ! Get a C pointer (in this case `char*`) to the temporary string.
            ! It is up to the caller to deallocate the memory allocated by this function.
            read_file = c_loc(temp_string)

            return
        end if

        write(stdout, "(A27)", advance = "no") "Planetary motion data file:"
        print *, filename

        ! Copy filename from filename string to filename scalar.
        do i = 1, filename_sz
            filename_scalar(i:i) = filename(i)
        end do

        write(stdout, "(A7)", advance = "no") "Opening"
        print *, filename
        open(unit = unit_number, file = filename_scalar, action = "read", &
            form = "unformatted", access = "stream", iostat = ios)

        if (ios < 0) then
            write(stdout, "(A18)", advance = "no") "Error opening file"
            print *, filename

            ! Allocate memory for the 0 needed for `c_str` (`char*`).
            allocate(character(1) :: temp_string)

            ! End the empty `c_str` with the necessary null character.
            temp_string = c_null_char

            ! Get a C pointer (in this case `char*`) to the temporary string.
            ! It is up to the caller to deallocate the memory allocated by this function.
            read_file = c_loc(temp_string)

            return
        else
            write(stdout, "(A19)", advance = "no") "Successfully opened"
            print *, filename

            inquire(file = filename_scalar, size = file_sz)

            write(stdout, "(A11)", advance = "no") "File size: "
            write(stdout, "(g0)", advance = "no") file_sz
            write(stdout, "(A6)") " bytes"
        end if

        ! Allocate memory according to the file length and the 0 needed for `c_str` (`char*`).
        allocate(character(file_sz + 1) :: temp_string)

        if (file_sz .gt. 0) then
            ! Read the entire file into the string.
            read(unit = unit_number, iostat = ios) temp_string

            if (ios > 0) then
                write(stdout, "(A18)", advance = "no") "Error reading file"
                print *, filename

                close(unit = unit_number, iostat = ios)
                if (ios .ne. 0) then
                    write(stdout, "(A18)", advance = "no") "Error closing file"
                end if

                ! Deallocate the previous allocation (needed for the next allocation).
                deallocate(temp_string)

                ! Allocate memory for the 0 needed for `c_str` (`char*`).
                allocate(character(1) :: temp_string)

                ! End the empty `c_str` with the necessary null character.
                temp_string = c_null_char

                ! Get a C pointer (in this case `char*`) to the temporary string.
                ! It is up to the caller to deallocate the memory allocated by this function.
                read_file = c_loc(temp_string)

                ! Set file size output variable to -1 to signal an error.
                file_sz = -1

                return
            end if

            ! Close file. If file is not closed, opening and reading it again
            ! e.g. in unit tests may fail in surprising ways. I have experience of this.
            close(unit = unit_number, iostat = ios)
            if (ios .ne. 0) then
                write(stdout, "(A18)", advance = "no") "Error closing file"
            end if

            ! Copy file and null character to the allocated memory.

            temp_string(file_sz + 1 : file_sz + 1) = c_null_char
        else
            temp_string = c_null_char
        end if

        ! Get a C pointer (in this case `char*`) to the temporary string.
        ! It is up to the caller to deallocate the memory allocated by this function.
        read_file = c_loc(temp_string)
    end function read_file

    logical function open_file_for_writing(filename_scalar, unit_number)
        implicit none
        character(len = *) :: filename_scalar
        integer, intent(in) :: unit_number
        integer :: ios

        open_file_for_writing = .false.

        open(unit = unit_number, file = filename_scalar, iostat = ios, status = "replace")

        if (ios < 0) then
            write(stdout, "(A18)", advance = "no") "Error opening file"
            print *, filename_scalar
            return
        end if

        open_file_for_writing = .true.
    end function open_file_for_writing

    logical function close_file(unit_number)
        implicit none
        integer :: unit_number, ios

        close_file = .false.

        close(unit = unit_number, iostat = ios)
        if (ios .ne. 0) then
            write(stdout, "(A18)", advance = "no") "Error closing file"
            return
        end if

        close_file = .true.

    end function close_file

end module file_mod
