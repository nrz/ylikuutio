program planetary_motion

    use my_kind
    use constants
    use string_mod
    use object_mod
    use planetary_system_mod
    use file_mod

    implicit none

    character(len = :), allocatable :: filename

    ! Objects are stored in the a vector of objects.
    type(planetary_system) :: my_planetary_system

    filename = "input.dat"

    print *, "Hello from planetary motion!"

    ! Read the simulation data from a file into a `planetary_system` record.
    my_planetary_system = load_file(filename)

    call simulate(my_planetary_system)

contains

    ! Simulate the planetary system according to the given input.
    subroutine simulate(my_planetary_system)
        implicit none

        type(planetary_system) :: my_planetary_system

        print *, "Hello from simulate!"

    end subroutine simulate

end program planetary_motion
