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

module global_parameters_mod

    use constants

    ! These are needed for C++/Fortran interface used by unit tests implemented in C++.
    use, intrinsic :: iso_c_binding, only: c_double

    implicit none

    type :: global_parameters

        integer :: n_objects
        real(c_double) :: length_of_timestep
        real(c_double) :: total_length_of_simulation
        integer :: print_interval
        integer :: save_interval

    end type

contains

    subroutine print_global_parameters(my_global_parameters)
        implicit none
        type(global_parameters) :: my_global_parameters

        write(stdout, "(A40)", advance = "no") "n_objects                             = "
        write(stdout, "(i0)") my_global_parameters % n_objects

        write(stdout, "(A40)", advance = "no") "length_of_timestep                    = "
        write(stdout, "(g0)") my_global_parameters % length_of_timestep

        write(stdout, "(A40)", advance = "no") "total_length_of_simulation            = "
        write(stdout, "(g0)") my_global_parameters % total_length_of_simulation

        write(stdout, "(A40)", advance = "no") "print_interval                        = "
        write(stdout, "(i0)") my_global_parameters % print_interval

        write(stdout, "(A40)", advance = "no") "save_interval                         = "
        write(stdout, "(i0)") my_global_parameters % save_interval
    end subroutine print_global_parameters

end module global_parameters_mod
