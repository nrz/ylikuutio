module planetary_system_mod

    use my_kind
    use object_mod

    implicit none

    type :: planetary_system 
        
        real(rk) :: start_time
        real(rk) :: length_of_timestep
        real(rk) :: end_time
        type(object) :: objects

    end type planetary_system

end module planetary_system_mod
