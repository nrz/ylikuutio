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
