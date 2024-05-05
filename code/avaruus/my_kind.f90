module my_kind

    implicit none

    ! The real kind used throughout the planetary motion codebase.
    integer, parameter :: rk = selected_real_kind(10, 40)

end module my_kind
