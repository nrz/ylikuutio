! Ylikuutio - A 3D game and simulation engine.
!
! Copyright (C) 2015-2024 Antti Nuortimo.
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

module object_mod

    use my_kind

    implicit none

    ! Object is a star, planet, moon, asteroid, comet, or any other celestial body.
    type :: object
        real(rk) :: mass
        real(rk) :: position(3), velocity(3), acceleration(3), new_acceleration(3)

        ! The rest of the object's variables are only for visualization purposes.
        character(len = :), allocatable :: name
        real(rk) :: apparent_size
        real(rk) :: red
        real(rk) :: green
        real(rk) :: blue
    end type object

end module object_mod
