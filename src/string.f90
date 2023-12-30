module string_mod

    use my_kind

    implicit none

contains

    ! Return true if line has non-whitespace code before newline and before the # comment character.
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

    ! Return true if first token of the string matches `token`.
    logical function get_is_first_token(line, token)
        implicit none
        character(len = :), allocatable, intent(in) :: line, token
        character(len = :), allocatable :: maybe_token_and_whitespace
        integer :: i, end_of_token_i

        get_is_first_token = .false.

        if (len(line) < len(token)) then
            return
        end if

        allocate(character(len(token) + 1) :: maybe_token_and_whitespace)

        do i = 1, len(line)
            if (line(i:i) .eq. '#') then
                exit
            else if (line(i:i) .ne. ' ' .and. line(i:i) .ne. '\t') then
                maybe_token_and_whitespace(i:i) = line(i:i)

                end_of_token_i = i + len(token) - 1
                if (maybe_token_and_whitespace(i : end_of_token_i) == token) then
                    end_of_token_i = end_of_token_i + 1
                    if (end_of_token_i > len(maybe_token_and_whitespace)) then
                        get_is_first_token = .true.
                        exit
                    else if (maybe_token_and_whitespace(end_of_token_i:end_of_token_i) .eq. ' ' .or. &
                        maybe_token_and_whitespace(end_of_token_i:end_of_token_i) .eq. '\t') then
                        get_is_first_token = .true.
                        exit
                    end if
                else
                    get_is_first_token = .false.
                    exit
                end if
            end if
        end do

        deallocate(maybe_token_and_whitespace)
    end function get_is_first_token

    ! Return index of `begin`.
    integer function get_token_index(line, token)
        implicit none
        character(len = :), allocatable, intent(in) :: line, token
        character(len = :), allocatable :: maybe_token_and_whitespace
        integer :: i

        get_token_index = -1

        if (len(line) < 6) then
            return
        end if

        allocate(character(len(token) + 1) :: maybe_token_and_whitespace)

        do i = 1, len(line) - len(token)
            if (line(i:i) .eq. '#') then
                exit
            else if (line(i:i) .ne. ' ' .and. line(i:i) .ne. '\t') then
                maybe_token_and_whitespace(i : i + len(token)) = line(i : i + len(token))

                if (maybe_token_and_whitespace(1 : len(token)) == token) then
                    get_token_index = i
                    exit
                else
                    get_token_index = -1
                    exit
                end if
            end if
        end do

        deallocate(maybe_token_and_whitespace)
    end function get_token_index

    ! Return true if line has `begin global_parameters`.
    logical function get_has_line_begin_global_parameters(line)
        implicit none
        character(len = :), allocatable, intent(in) :: line
        character(len = :), allocatable :: dynamically_allocated_line
        character(len = :), allocatable :: line_after_begin
        character(len = :), allocatable :: begin_string, global_parameters_string
        integer :: i, j, index_of_begin, index_after_begin

        get_has_line_begin_global_parameters = .false.

        allocate(character(len(trim(line))) :: dynamically_allocated_line)
        dynamically_allocated_line = line

        allocate(character(len("begin")) :: begin_string)
        begin_string = "begin"

        allocate(character(len("global_parameters")) :: global_parameters_string)
        global_parameters_string = "global_parameters"

        do i = 1, len(line)
            if (line(i:i) .eq. '#') then
                exit
            else if (line(i:i) .ne. ' ' .and. line(i:i) .ne. '\t') then
                if (get_is_first_token(dynamically_allocated_line, begin_string)) then
                    ! Check if line has `global_parameters`.
                    index_of_begin = get_token_index(line, begin_string)

                    if (index_of_begin .ge. 0) then
                        index_after_begin = index_of_begin + len(begin_string)
                        line_after_begin = dynamically_allocated_line(index_after_begin : len(dynamically_allocated_line))

                        do j = 1, len(line_after_begin)
                            if (line_after_begin(j:j) .ne. ' ' .and. line_after_begin(j:j) .ne. '\t') then
                                if (get_is_first_token(line_after_begin, global_parameters_string)) then
                                    get_has_line_begin_global_parameters = .true.
                                    exit
                                end if
                            end if
                        end do
                    end if
                end if

                exit
            end if
        end do

        deallocate(dynamically_allocated_line)
        deallocate(begin_string)
        deallocate(global_parameters_string)

    end function get_has_line_begin_global_parameters

    ! Return the index of # comment character, -1 if none.
    integer function get_comment_i(line)
        implicit none
        character(len = *), intent(in) :: line
        integer :: i

        get_comment_i = -1

        do i = 1, len(line(:))
            if (line(i:i) .eq. '#') then
                get_comment_i = i
                exit
            end if
        end do

    end function get_comment_i

end module string_mod
