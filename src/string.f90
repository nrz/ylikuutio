module string_mod

    use my_kind

    implicit none

contains

    ! Returns the line given as index.
    ! `line_sz` has the length of the line (including possible trailing newline) if line was found, otherwise -1 if was not found.
    ! `line_sz` also makes it easier to process of lines (of type `c_ptr`) returned by `get_line` in Fortran.
    ! `string_sz` is needed as input parameter due to ISO C binding used by unit tests written in C++.
    function get_line(string, string_sz, line_i, line_sz)
        ! These are needed for C++/Fortran interface used by unit tests implemented in C++.
        use, intrinsic :: iso_c_binding, only: c_char, c_int, c_null_char, c_loc, c_ptr

        implicit none
        character(kind = c_char), dimension(string_sz), intent(in) :: string
        integer(kind = c_int), intent(in), value :: string_sz, line_i
        integer(kind = c_int), intent(out) :: line_sz
        type(c_ptr) :: get_line
        character(kind = c_char, len = :), pointer, save :: temp_string
        integer :: i, newlines_found, src_i, dest_i, start_i, end_i

        line_sz = -1       ! Line has not been found yet.
        newlines_found = 0 ! No newlines found yet.
        start_i = -1       ! Start of line not found yet.
        end_i = -1         ! End of line not found yet.

        if (line_i .le. 0 .or. string_sz .lt. 1) then
            ! Allocate memory for the 0 needed for `c_str` (`char*`).
            allocate(character(1) :: temp_string)

            ! End the empty `c_str` with the necessary null character.
            temp_string = c_null_char

            ! Get a C pointer (in this case `char*`) to the temporary string.
            ! It is up to the caller to deallocate the memory allocated by this function.
            get_line = c_loc(temp_string)

            return
        end if

        ! Loop through the string to find `line_i` - 1 newlines.

        do i = 1, string_sz
            if (newlines_found .eq. line_i - 1) then
                ! This is the beginning of the target line!
                start_i = i

                ! The line is definitely found.
                line_sz = 1
                exit
            end if

            if (string(i) .eq. achar(10)) then
                newlines_found = newlines_found + 1
            end if
        end do

        if (start_i .ge. 1) then
            ! Line was found.
            ! Search for the end of line. Possible newline is included in the end of the line.

            do i = start_i, string_sz
                end_i = i
                line_sz = end_i - start_i + 1

                if (string(i) .eq. achar(10)) then
                    ! Newline found. This is the last character of the target line.
                    exit
                end if
            end do
        end if

        ! Allocate memory according to the line length and the 0 needed for `c_str` (`char*`).
        allocate(character(line_sz + 1) :: temp_string)

        if (line_sz .gt. 0) then
            ! Copy line and null character to the allocated memory.

            dest_i = 1

            do src_i = start_i, end_i
                temp_string(dest_i : dest_i) = string(src_i)
                dest_i = dest_i + 1
            end do
            temp_string(line_sz + 1 : line_sz + 1) = c_null_char
        else
            temp_string = c_null_char
        end if

        ! Get a C pointer (in this case `char*`) to the temporary string.
        ! It is up to the caller to deallocate the memory allocated by this function.
        get_line = c_loc(temp_string)
    end function get_line

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
    function get_first_token(line, sz, next_i, token_sz)
        ! These are needed for C++/Fortran interface used by unit tests implemented in C++.
        use, intrinsic :: iso_c_binding, only: c_char, c_int, c_null_char, c_loc, c_ptr

        implicit none
        character(kind = c_char), dimension(sz), intent(in) :: line
        integer(kind = c_int), intent(in), value :: sz
        integer(kind = c_int), intent(out) :: next_i, token_sz
        type(c_ptr) :: get_first_token
        character(kind = c_char, len = :), pointer, save :: temp_string
        integer :: src_i, dest_i, start_i, end_i

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

    ! Returns the nth token of the line (n given as `token_i`).
    ! If newline or hash (beginning of a comment) is encountered before finding the nth token, an empty string is returned.
    ! `sz` is needed as input parameter due to ISO C binding used by unit tests written in C++.
    function get_nth_token(line, sz, token_i, next_i, token_sz)
        ! These are needed for C++/Fortran interface used by unit tests implemented in C++.
        use, intrinsic :: iso_c_binding, only: c_char, c_int, c_null_char, c_loc, c_ptr

        implicit none
        character(kind = c_char), dimension(sz), intent(in) :: line
        integer(kind = c_int), intent(in), value :: sz, token_i
        integer(kind = c_int), intent(out) :: next_i, token_sz
        type(c_ptr) :: get_nth_token
        type(c_ptr) :: temp_line
        character(kind = c_char, len = :), pointer, save :: temp_string
        integer :: i, tokens_found

        tokens_found = 0 ! No tokens found yet.
        next_i = -1
        token_sz = 0

        if (token_i .le. 0 .or. sz .lt. 1) then
            ! Allocate memory for the 0 needed for `c_str` (`char*`).
            allocate(character(1) :: temp_string)

            ! End the empty `c_str` with the necessary null character.
            temp_string = c_null_char

            ! Get a C pointer (in this case `char*`) to the temporary string.
            ! It is up to the caller to deallocate the memory allocated by this function.
            get_nth_token = c_loc(temp_string)

            return
        end if

        i = 1

        do
            temp_line = get_first_token(line(i : sz), size(line(i : sz)), next_i, token_sz)

            if (next_i .eq. -1) then
                ! Token not found.
                get_nth_token = temp_line
                return
            else
                ! `next_i` needs to be adjusted relative to the difference between
                ! `i` and 1 (the offset of the beginning of the string)
                ! because a partial line was passed to `get_first_token`.
                next_i = next_i + (i - 1)
                i = next_i
                tokens_found = tokens_found + 1

                if (tokens_found .eq. token_i) then
                    ! This is the token with right index.
                    exit
                end if
            end if
        end do

        if (tokens_found .lt. token_i) then
            next_i = -1

            ! Allocate memory for the 0 needed for `c_str` (`char*`).
            allocate(character(1) :: temp_string)

            ! End the empty `c_str` with the necessary null character.
            temp_string = c_null_char

            ! Get a C pointer (in this case `char*`) to the temporary string.
            ! It is up to the caller to deallocate the memory allocated by this function.
            get_nth_token = c_loc(temp_string)
        else
            ! The token was found!

            ! Return a C pointer (in this case `char*`) to the temporary string.
            ! It is up to the caller to deallocate the memory allocated by this function.
            get_nth_token = temp_line
        end if
    end function get_nth_token

    integer function get_line_i_with_2_token_statement(string, string_sz, token1, token1_sz, token2, token2_sz)
        ! These are needed for C++/Fortran interface used by unit tests implemented in C++.
        use, intrinsic :: iso_c_binding, only: c_f_pointer, c_char, c_int, c_ptr

        implicit none
        character(kind = c_char), dimension(string_sz), intent(in) :: string
        character(kind = c_char), dimension(token1_sz), intent(in) :: token1
        character(kind = c_char), dimension(token2_sz), intent(in) :: token2
        integer(kind = c_int), intent(in), value :: string_sz, token1_sz, token2_sz
        character(kind = c_char, len = :), pointer :: fortran_line
        character(kind = c_char), pointer, dimension(:) :: fortran_temp_token
        type(c_ptr) :: line, temp_token
        integer :: line_i, i, line_sz, next_i, temp_token_sz
        logical :: do_tokens_match

        get_line_i_with_2_token_statement = -1

        line_i = 1

        do
            line = get_line(string, string_sz, line_i, line_sz)

            if (line_sz .eq. -1) then
                ! Line was not found. There is no line with the given statement.
                return
            end if

            ! `line` is `c_ptr`. It needs to be converted into a Fortran pointer.
            call c_f_pointer(line, fortran_line)

            temp_token = get_nth_token(fortran_line, line_sz, 1, next_i, temp_token_sz)

            ! `temp_token` is `c_ptr`. It needs to be converted into a Fortran pointer.
            call c_f_pointer(temp_token, fortran_temp_token, [ temp_token_sz ])

            if (next_i .eq. -1 .or. temp_token_sz .ne. token1_sz) then
                ! Token 1 sizes do not match. There is no desired statement on this line.
                ! Proceed to the next line.
                line_i = line_i + 1
                cycle
            end if

            do_tokens_match = .true.

            do i = 1, token1_sz
                if (fortran_temp_token(i) .ne. token1(i)) then
                    do_tokens_match = .false.
                    exit
                end if
            end do

            if (.not. do_tokens_match) then
                line_i = line_i + 1
                cycle
            end if

            temp_token = get_nth_token(fortran_line, line_sz, 2, next_i, temp_token_sz)

            ! `temp_token` is `c_ptr`. It needs to be converted into a Fortran pointer.
            call c_f_pointer(temp_token, fortran_temp_token, [ temp_token_sz ])

            if (next_i .eq. -1 .or. temp_token_sz .ne. token2_sz) then
                ! Token 2 sizes do not match. There is no desired statement on this line.
                ! Proceed to the next line.
                line_i = line_i + 1
                cycle
            end if

            do_tokens_match = .true.

            do i = 1, token2_sz
                if (fortran_temp_token(i) .ne. token2(i)) then
                    do_tokens_match = .false.
                    exit
                end if
            end do

            if (.not. do_tokens_match) then
                line_i = line_i + 1
                cycle
            end if

            temp_token = get_nth_token(fortran_line, line_sz, 3, next_i, temp_token_sz)

            if (next_i .ne. -1 .or. temp_token_sz .ne. 0) then
                ! The line has 2 matching tokens but also junk. Junk is not accepted.
                line_i = line_i + 1
                cycle
            end if

            get_line_i_with_2_token_statement = line_i
            return
        end do
    end function get_line_i_with_2_token_statement

end module string_mod
