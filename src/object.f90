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
