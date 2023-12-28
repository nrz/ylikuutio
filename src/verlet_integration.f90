module verlet_integration

    use object_mod

contains

    ! Process one timestep for an object or multiple objects.
    elemental subroutine timestep(my_object)
        implicit none

        type(object), intent(inout) :: my_object

    end subroutine timestep

end module verlet_integration
