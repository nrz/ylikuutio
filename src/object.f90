module object_mod

    use my_kind

    implicit none

    ! Object is a star, planet, moon, asteroid, comet, or any other celestial body.
    type :: object
        real(rk) :: position(3), velocity(3), acceleration(3)
        character(len = :), allocatable :: name
    end type object

end module object_mod
