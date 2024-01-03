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
        type(object) :: object
        integer :: object_i

        object_loop: do object_i = 1, my_planetary_system % n_objects

            object = my_planetary_system % objects(object_i)

            write(stdout, "(A7)", advance = "no") "name = "
            print *, object % name
            write(stdout, "(G10.2)", advance = "no") "mass = "
            print *, object % mass
            write(stdout, "(G10.2)", advance = "no") "x    = "
            print *, object % position(1)
            write(stdout, "(G10.2)", advance = "no") "y    = "
            print *, object % position(2)
            write(stdout, "(G10.2)", advance = "no") "z    = "
            print *, object % position(3)
            write(stdout, "(G10.2)", advance = "no") "vx   = "
            print *, object % velocity(1)
            write(stdout, "(G10.2)", advance = "no") "vy   = "
            print *, object % velocity(2)
            write(stdout, "(G10.2)", advance = "no") "vz   = "
            print *, object % velocity(3)
        end do object_loop

    end subroutine print_objects

end module planetary_system_mod
