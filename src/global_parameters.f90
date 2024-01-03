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
        write(stdout, "(G10.2)") my_global_parameters % length_of_timestep

        write(stdout, "(A40)", advance = "no") "total_length_of_simulation            = "
        write(stdout, "(G10.2)") my_global_parameters % total_length_of_simulation

        write(stdout, "(A40)", advance = "no") "print_interval                        = "
        write(stdout, "(i0)") my_global_parameters % print_interval

        write(stdout, "(A40)", advance = "no") "save_interval                         = "
        write(stdout, "(i0)") my_global_parameters % save_interval
    end subroutine print_global_parameters

end module global_parameters_mod
