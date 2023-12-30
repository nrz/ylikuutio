module file_mod

    use my_kind
    use constants
    use string_mod
    use object_mod
    use planetary_system_mod

    implicit none

contains

    ! Read file and return its contents as a `char*`.
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

            ! Copy file and null character to the allocated memory.

            temp_string(file_sz + 1 : file_sz + 1) = c_null_char
        else
            temp_string = c_null_char
        end if

        ! Get a C pointer (in this case `char*`) to the temporary string.
        ! It is up to the caller to deallocate the memory allocated by this function.
        read_file = c_loc(temp_string)
    end function read_file

    ! Read and process a file and return a `planetary_system`.
    function load_file(filename)
        implicit none
        character(len = *), intent(in) :: filename
        type(object) :: my_object
        character(len = 250) :: line
        character(len = :), allocatable :: dynamically_allocated_line
        integer :: n_lines, n_objects
        type(planetary_system) :: load_file
        integer :: filename_length 
        integer, parameter :: unit_number = 1
        integer :: line_i, ios
        logical :: does_line_need_processing
        logical, allocatable :: has_line_begin_global_parameters(:), has_line_begin_objects(:)

        filename_length = len(filename)

        write(stdout, "(A27)", advance = "no") "Planetary motion data file:"
        print *, trim(filename)

        write(stdout, "(A7)", advance = "no") "Opening"
        print *, trim(filename)
        open(unit = unit_number, action = "read", file = filename, iostat = ios, status = 'old')

        if (ios < 0) then
            write(stdout, "(A18)", advance = "no") "Error opening file"
            print *, trim(filename)
        else
            write(stdout, "(A19)", advance = "no") "Successfully opened"
            print *, trim(filename)
        end if

        n_lines = 0
        n_objects = 0

        ! Count lines.
        write(stdout, "(A17)", advance = "no") "Counting lines of"
        print *, trim(filename)

        do
            read(unit = unit_number, fmt = "(A)", iostat = ios) line

            if (ios < 0) then
                exit
            end if

            n_lines = n_lines + 1
        end do

        write(stdout, "(A21)", advance = "no") "Number of lines read:"
        write(stdout, "(g0)") n_lines

        allocate(has_line_begin_global_parameters(n_lines))
        allocate(has_line_begin_objects(n_lines))

        ! Start processing again from the beginning of the file.
        rewind(unit = unit_number)

        write(stdout, "(A18)") "Processing lines."

        do line_i = 1, n_lines
            read(unit = unit_number, fmt = "(A)", iostat = ios) line

            if (ios < 0) then
                exit
            end if

            write(stdout, "(g0)", advance = "no") line_i

            allocate(character(len(trim(line))) :: dynamically_allocated_line)
            dynamically_allocated_line(:) = trim(line(:))

            if (get_has_line_code(dynamically_allocated_line, len(dynamically_allocated_line))) then
                write(stdout, "(A10)") " has code."

                has_line_begin_global_parameters(line_i) = get_has_line_begin_global_parameters(dynamically_allocated_line)
            else
                write(stdout, "(A13)") " has no code."
            end if

            deallocate(dynamically_allocated_line)
        end do

        do line_i = 1, n_lines
            if (has_line_begin_global_parameters(line_i)) then
                write(stdout, "(A36)", advance = "no") "Reading global parameters from line "
                write(stdout, "(g0)") line_i
            end if
        end do

        ! Start processing again from the beginning of the file.
        rewind(unit = unit_number)

        do line_i = 1, n_lines
            ! write(stdout, "(A26)", advance = "no") "Reading objects from line "
            ! write(stdout, "(g0)") line_i
        end do


            ! does_line_need_processing = has_line_code(line)

            ! if (does_line_need_processing) then
                ! write(stdout, "(A15)", advance = "no") "Processing line"
                ! print *, line_i
            ! end if
            ! print *, does_line_need_processing

        deallocate(has_line_begin_global_parameters)
        deallocate(has_line_begin_objects)

        write(stdout, "(A7)", advance = "no") "Closing"
        print *, trim(filename)
        close(unit = unit_number)

    end function load_file

    ! Read a single line from the the given 'unit number' (an integer identifier of an open file).
    function read_object_line(unit_number)
        implicit none
        integer :: unit_number, ios
        type(object) :: read_object_line
        real(rk) :: mass, x, y, z, vx, vy, vz, nan
        character(len = 250) :: name

        print *, "Hello from read_object_line!"

        nan = get_nan()

        ! Read one line of file.
        read(unit = unit_number, fmt = *, iostat = ios) mass, x, y, z, vx, vy, vz, name

        if (ios < 0) then
            read_object_line = object( nan, [ nan, nan, nan ], [ nan, nan, nan ], "invalid")
        else
            read_object_line = object(mass, [ x, y, z ], [ vx, vy, vz ], name)
        end if

    end function read_object_line

end module file_mod
