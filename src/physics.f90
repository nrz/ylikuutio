module physics_mod

    use global_parameters_mod
    use planetary_system_mod
    use object_mod

contains

    ! Process one timestep for an object or multiple objects.
    elemental subroutine timestep(my_object)
        implicit none

        type(object), intent(inout) :: my_object

    end subroutine timestep

    ! Simulate the planetary system according to the given input.
    logical function simulate(my_global_parameters, my_planetary_system)
        implicit none
        type(global_parameters) :: my_global_parameters
        type(planetary_system) :: my_planetary_system

        simulate = .false.

        write(stdout, "(A20)") "Hello from simulate!"

    end function simulate

end module physics_mod
