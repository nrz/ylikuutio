module string_mod

    use my_kind

    implicit none

contains

    ! Return true if line has non-whitespace code before newline and before the # comment character.
    ! `sz` is needed as input parameter due to ISO C binding used by unit tests written in C++.
    logical function get_has_line_code(line, sz)
        ! These are needed for C++/Fortran interface used by unit tests implemented in C++.
        use, intrinsic :: iso_c_binding, only: c_char, c_int

        implicit none
        character(kind = c_char), dimension(sz), intent(in) :: line
        integer(kind = c_int), intent(in), value :: sz
        integer :: i

        get_has_line_code = .false.

        do i = 1, sz
            if (line(i) .eq. '#') then
                exit
            else if (line(i) .ne. ' ' .and. line(i) .ne. achar(9)) then
                get_has_line_code = .true.
                exit
            end if
        end do
    end function get_has_line_code

    ! Returns the first token of the line.
    ! If newline or hash (beginning of a comment) is encountered before finding a token, an empty string is returned.
    ! `sz` is needed as input parameter due to ISO C binding used by unit tests written in C++.
    function get_first_token(line, sz, next_i)
        ! These are needed for C++/Fortran interface used by unit tests implemented in C++.
        use, intrinsic :: iso_c_binding, only: c_char, c_int, c_null_char, c_loc, c_ptr

        implicit none
        character(kind = c_char), dimension(sz), intent(in) :: line
        integer(kind = c_int), intent(in), value :: sz
        integer(kind = c_int), intent(out) :: next_i
        type(c_ptr) :: get_first_token
        character(kind = c_char, len = :), pointer, save :: temp_string
        integer :: src_i, dest_i, start_i, end_i, token_sz

        next_i = -1
        start_i = -1
        end_i = -1
        token_sz = 0

        ! Search the beginning of the token.
        do src_i = 1, sz
            if (line(src_i) .eq. achar(10) .or. line(src_i) .eq. '#') then
                exit
            else if (line(src_i) .ne. ' ' .and. line(src_i) .ne. achar(9)) then
                start_i = src_i
                exit
            end if
        end do

        if (start_i .ge. 1) then
            ! The beginning of token was found. Search the end of the token.
            do src_i = start_i, sz
                if (line(src_i) .eq. ' ' .or. line(src_i) .eq. achar(9) &
                    .or. line(src_i) .eq. achar(10) .or. line(src_i) .eq. '#') then
                    ! Nothing to update. Keep the data of the previous iteration.
                    exit
                else
                    ! Update the data.
                    end_i = src_i
                    token_sz = end_i - start_i + 1
                    next_i = src_i + 1
                end if
            end do
        end if

        ! Allocate memory according to the token length and the 0 needed for `c_str` (`char*`).
        allocate(character(token_sz + 1) :: temp_string)

        if (token_sz .gt. 0) then
            ! Copy token and null character to the allocated memory.

            dest_i = 1

            do src_i = start_i, end_i
                temp_string(dest_i : dest_i) = line(src_i)
                dest_i = dest_i + 1
            end do
            temp_string(token_sz + 1 : token_sz + 1) = c_null_char
        else
            temp_string = c_null_char
        end if

        ! Get a C pointer (in this case `char*`) to the temporary string.
        ! It is up to the caller to deallocate the memory allocated by this function.
        get_first_token = c_loc(temp_string)
    end function get_first_token

end module string_mod
