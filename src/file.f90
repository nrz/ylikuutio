module file_mod

    use my_kind
    use constants
    use string_mod
    use object_mod
    use planetary_system_mod

    implicit none

contains

    ! Read file and return its contents as a `char*`.
    ! `filename_sz` is needed as input parameter due to ISO C binding used by unit tests written in C++.
    function read_file(filename, filename_sz, file_status)
        ! These are needed for C++/Fortran interface used by unit tests implemented in C++.
        use, intrinsic :: iso_c_binding, only: c_char, c_int, c_null_char, c_loc, c_ptr

        implicit none
        character(kind = c_char), dimension(filename_sz), intent(in) :: filename
        integer(kind = c_int), intent(in), value :: filename_sz
        integer(kind = c_int), intent(out) :: file_status
        type(c_ptr) :: read_file
        integer, parameter :: unit_number = 1
        character(kind = c_char, len = filename_sz) :: filename_scalar
        character(kind = c_char, len = :), pointer, save :: temp_string
        integer :: ios, i, file_sz
        logical :: are_inputs_valid

        are_inputs_valid = .true.
        file_sz = 0

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

            ! Set file status output variable to -1 to signal an error.
            file_status = -1

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

            ! Set file status output variable to -1 to signal an error.
            file_status = -1

            return
        else
            write(stdout, "(A19)", advance = "no") "Successfully opened"
            print *, filename

            inquire(file = filename_scalar, size = file_sz)

            write(stdout, "(A11)", advance = "no") "File size: "
            write(stdout, "(g0)", advance = "no") file_sz
            write(stdout, "(A6)") " bytes"

            file_status = 1
        end if

        ! Allocate memory according to the file length and the 0 needed for `c_str` (`char*`).
        allocate(character(file_sz + 1) :: temp_string)

        if (file_sz .gt. 0) then
            ! Read the entire file into the string.
            read(unit = unit_number, iostat = ios) temp_string

            if (ios > 0) then
                write(stdout, "(A18)", advance = "no") "Error reading file"
                print *, filename

                ! Allocate memory for the 0 needed for `c_str` (`char*`).
                allocate(character(1) :: temp_string)

                ! End the empty `c_str` with the necessary null character.
                temp_string = c_null_char

                ! Get a C pointer (in this case `char*`) to the temporary string.
                ! It is up to the caller to deallocate the memory allocated by this function.
                read_file = c_loc(temp_string)

                ! Set file status output variable to -1 to signal an error.
                file_status = -1

                return
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

end module file_mod
