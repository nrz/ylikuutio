! Ylikuutio - A 3D game and simulation engine.
!
! Copyright (C) 2015-2026 Antti Nuortimo.
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

module string_mod

    use constants

    implicit none

contains

    ! Returns the line given as index.
    ! It's up to caller to deallocate the returned line. A valid pointer (`c_ptr`) is returned always.
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

        if (line_sz .eq. -1) then
            ! Allocate memory for the 0 needed for `c_str` (`char*`).
            allocate(character(1) :: temp_string)
        else
            ! Allocate memory according to the line length and the 0 needed for `c_str` (`char*`).
            allocate(character(line_sz + 1) :: temp_string)
        end if

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
            if (line(i) .eq. '#' .or. line(i) .eq. achar(10)) then
                exit
            else if (line(i) .ne. ' ' .and. line(i) .ne. achar(9)) then
                get_has_line_code = .true.
                exit
            end if
        end do
    end function get_has_line_code

    ! Returns the first token of the line.
    ! It's up to caller to deallocate the returned token. A valid pointer (`c_ptr`) is returned always.
    ! If newline or hash (beginning of a comment) is encountered before finding a token, an empty string is returned.
    ! If token is found, `next_i` points to the character right after the end of the token. Otherwise, `next_i` is -1.
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
            if (line(src_i) .eq. ',') then
                ! Comma is a token always by itself (length of 1).
                start_i = src_i
                end_i = src_i
                token_sz = end_i - start_i + 1
                next_i = src_i + 1
                exit
            else if (line(src_i) .eq. achar(10) .or. line(src_i) .eq. '#') then
                exit
            else if (line(src_i) .ne. ' ' .and. line(src_i) .ne. achar(9)) then
                start_i = src_i
                exit
            end if
        end do

        if (start_i .ge. 1) then
            ! The beginning of token was found. Search the end of the token.
            do src_i = start_i, sz
                if (line(src_i) .eq. ',' .or. line(src_i) .eq. ' ' .or. line(src_i) .eq. achar(9) &
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
    ! It's up to caller to deallocate the returned token. A valid pointer (`c_ptr`) is returned always.
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
            ! This line does not have enough tokens!
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

    ! Return the line number of the first line that matches the required tokens.
    ! The tokens must be given in a `tokens` string, separated by spaces.
    integer function get_line_i_with_n_token_statement(string, string_sz, tokens, tokens_sz)
        ! These are needed for C++/Fortran interface used by unit tests implemented in C++.
        use, intrinsic :: iso_c_binding, only: c_f_pointer, c_char, c_int, c_ptr

        implicit none
        character(kind = c_char), dimension(string_sz), intent(in) :: string
        character(kind = c_char), dimension(tokens_sz), intent(in) :: tokens
        integer(kind = c_int), intent(in), value :: string_sz, tokens_sz
        character(kind = c_char, len = :), pointer :: fortran_line
        character(kind = c_char), pointer, dimension(:) :: fortran_expected_token, fortran_received_token
        type(c_ptr) :: line, expected_token, received_token
        integer :: i, line_i, line_sz
        integer :: expected_token_offset, expected_token_sz, next_expected_token_offset
        integer :: received_token_offset, received_token_sz, next_received_token_offset
        logical :: do_tokens_match

        get_line_i_with_n_token_statement = -1

        line_i = 1

        line_loop: do
            line = get_line(string, string_sz, line_i, line_sz)

            ! `line` is `c_ptr`. It needs to be converted into a Fortran pointer.
            call c_f_pointer(line, fortran_line)

            if (line_sz .eq. -1) then
                ! Line was not found. There is no line with the given statement.

                ! Deallocate the line.
                deallocate(fortran_line)

                return
            end if

            ! A line was found.
            expected_token_offset = 1 ! Start processing from the beginning of the expected tokens.
            received_token_offset = 1 ! Start processing from the beginning of the received tokens.
            next_expected_token_offset = -1 ! Some dummy value.
            next_received_token_offset = -1 ! Some dummy value.

            token_loop: do
                ! Check that the tokens of the line match the expected tokens.
                expected_token = get_first_token(tokens(expected_token_offset : tokens_sz), &
                    size(tokens(expected_token_offset : tokens_sz)), &
                    next_expected_token_offset, expected_token_sz)
                received_token = get_first_token(fortran_line(received_token_offset : line_sz), &
                    len(fortran_line(received_token_offset : line_sz)), &
                    next_received_token_offset, received_token_sz)

                ! `expected_token` and received_token` are `c_ptr`. Thy need to be converted into Fortran pointers.
                call c_f_pointer(expected_token, fortran_expected_token, [ expected_token_sz ])
                call c_f_pointer(received_token, fortran_received_token, [ received_token_sz ])

                if (expected_token_sz .lt. 1 .and. received_token_sz .lt. 1) then
                    ! Line matches: No more tokens expected and no more tokens received.
                    deallocate(fortran_line)
                    deallocate(fortran_expected_token)
                    deallocate(fortran_received_token)

                    ! Return the current line number.
                    get_line_i_with_n_token_statement = line_i
                    return
                end if

                ! `next_expected_token_offset` and `next_received_token_offset`
                ! need to be adjusted relative to the difference between
                ! the corresponding start offset and 1
                ! (the offset of the beginning of the string)
                ! because a partial line was passed to `get_first_token`.
                next_expected_token_offset = next_expected_token_offset + (expected_token_offset - 1)
                next_received_token_offset = next_received_token_offset + (received_token_offset - 1)

                if (expected_token_sz .ge. 1 .and. received_token_sz .lt. 1) then
                    ! Expected token found but no token received!
                    ! This line does not match.

                    deallocate(fortran_line)
                    deallocate(fortran_expected_token)
                    deallocate(fortran_received_token)

                    line_i = line_i + 1
                    exit
                else if (expected_token_sz .lt. 1 .and. received_token_sz .ge. 1) then
                    ! Token received but no token expected!
                    ! This line does not match.

                    deallocate(fortran_line)
                    deallocate(fortran_expected_token)
                    deallocate(fortran_received_token)

                    line_i = line_i + 1
                    exit
                else
                    ! Token expected and token received.
                    if (received_token_sz .ne. expected_token_sz) then
                        ! Token sizes do not match!
                        ! This line does not match.

                        deallocate(fortran_line)
                        deallocate(fortran_expected_token)
                        deallocate(fortran_received_token)

                        line_i = line_i + 1
                        exit
                    end if

                    ! Token sizes match.
                    ! Check that tokens are identical.

                    do_tokens_match = .true.

                    do i = 1, expected_token_sz
                        if (fortran_received_token(i) .ne. fortran_expected_token(i)) then
                            do_tokens_match = .false.
                            exit
                        end if
                    end do

                    if (.not. do_tokens_match) then
                        ! This line does not match.

                        deallocate(fortran_line)
                        deallocate(fortran_expected_token)
                        deallocate(fortran_received_token)

                        line_i = line_i + 1
                        exit
                    end if

                    ! Tokens match. Proceed to the next pair of tokens.
                    deallocate(fortran_expected_token)
                    deallocate(fortran_received_token)

                    expected_token_offset = next_expected_token_offset
                    received_token_offset = next_received_token_offset
                end if
            end do token_loop
        end do line_loop
    end function get_line_i_with_n_token_statement

    ! Returns the number of code lines between `begin_line_i` and `end_line_i` (both exclusive).
    ! In case of an error -1 is returned.
    function get_n_of_code_lines_between(string, string_sz, begin_line_i, end_line_i)
        ! These are needed for C++/Fortran interface used by unit tests implemented in C++.
        use, intrinsic :: iso_c_binding, only: c_f_pointer, c_char, c_int, c_ptr

        implicit none
        character(kind = c_char), dimension(string_sz), intent(in) :: string
        integer(kind = c_int), intent(in), value :: string_sz
        integer(kind = c_int), intent(in), value :: begin_line_i, end_line_i
        integer(kind = c_int) :: get_n_of_code_lines_between
        type(c_ptr) :: temp_line
        character(kind = c_char, len = :), pointer :: fortran_temp_line
        integer(kind = c_int) :: temp_line_sz
        integer :: line_i, n_code_lines
        logical :: has_line_code

        get_n_of_code_lines_between = -1
        n_code_lines = 0

        if (begin_line_i .lt. 1) then
            ! Begin line must be greater or equal to 1.
            write(stdout, "(A37)") "Error! Begin line must be at least 1!"
            return
        end if

        if (begin_line_i .ge. end_line_i) then
            ! End line must be after begin line.
            write(stdout, "(A42)") "Error! Begin line must be before end line!"
            return
        end if

        ! Check that `end_line_i` exists in the input string.
        temp_line = get_line(string, string_sz, end_line_i, temp_line_sz)

        if (temp_line_sz .lt. 0) then
            write(stdout, "(A54)") "Error! End line number must exist in the input string!"
            return
        end if

        do line_i = begin_line_i + 1, end_line_i - 1
            temp_line = get_line(string, string_sz, line_i, temp_line_sz)

            ! `temp_line` is `c_ptr`. It needs to be converted into a Fortran pointer.
            call c_f_pointer(temp_line, fortran_temp_line)

            if (temp_line_sz .lt. 0) then
                write(stdout, "(A12)", advance = "no") "Line number "
                write(stdout, "(g0)", advance = "no") line_i
                write(stdout, "(A15)") " was not found!"
                deallocate(fortran_temp_line)
                return
            end if

            has_line_code = get_has_line_code(fortran_temp_line, temp_line_sz)

            if (has_line_code) then
                n_code_lines = n_code_lines + 1
            end if

            deallocate(fortran_temp_line)
        end do

        get_n_of_code_lines_between = n_code_lines
    end function get_n_of_code_lines_between

end module string_mod
