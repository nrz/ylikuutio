module constants

    use, intrinsic :: ieee_arithmetic, only: ieee_value, ieee_quiet_nan
    use my_kind

    implicit none

    integer, parameter :: stdout = 6      ! Use this instead of hardcoded 6, for readability.

    real(rk), parameter :: G  = 6.674E-11 * 1E-9 ! Gravitational constant (km^3 / kg / s^2)

contains

    function get_nan()

        implicit none
        real(rk) :: get_nan

        get_nan = ieee_value(get_nan, ieee_quiet_nan)

    end function get_nan

end module constants
