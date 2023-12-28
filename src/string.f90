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
            else if (line(i) .ne. ' ' .and. line(i) .ne. '\t') then
                get_has_line_code = .true.
                exit
            end if
        end do

    end function get_has_line_code

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
