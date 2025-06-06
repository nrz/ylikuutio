! Ylikuutio - A 3D game and simulation engine.
!
! Copyright (C) 2015-2025 Antti Nuortimo.
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

module planetary_system_mod

    use constants
    use object_mod

    implicit none

    type :: planetary_system 

        ! Number of objects is stored here just in case
        ! more objects were expected than delivered in the input file.
        integer :: n_objects
        
        type(object), allocatable :: objects(:)

    end type planetary_system

contains

    subroutine print_objects(my_planetary_system)
        implicit none

        type(planetary_system), intent(in) :: my_planetary_system
        type(object) :: my_object
        integer :: object_i
        character(len = 100) :: name_length_string

        object_loop: do object_i = 1, my_planetary_system % n_objects

            my_object = my_planetary_system % objects(object_i)

            ! Write the length of the name into `name_length_string`.
            write(name_length_string, "(g0)") len(my_object % name)

            write(stdout, "(A7)", advance = "no") "name = "
            write(stdout, "(A" // name_length_string // ")") my_object % name
            write(stdout, "(A7)", advance = "no") "mass = "
            write(stdout, "(g0)") my_object % mass
            write(stdout, "(A7)", advance = "no") "x    = "
            write(stdout, "(g0)") my_object % position(1)
            write(stdout, "(A7)", advance = "no") "y    = "
            write(stdout, "(g0)") my_object % position(2)
            write(stdout, "(A7)", advance = "no") "z    = "
            write(stdout, "(g0)") my_object % position(3)
            write(stdout, "(A7)", advance = "no") "vx   = "
            write(stdout, "(g0)") my_object % velocity(1)
            write(stdout, "(A7)", advance = "no") "vy   = "
            write(stdout, "(g0)") my_object % velocity(2)
            write(stdout, "(A7)", advance = "no") "vz   = "
            write(stdout, "(g0)") my_object % velocity(3)
        end do object_loop

    end subroutine print_objects

end module planetary_system_mod
