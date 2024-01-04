module physics_mod

    use my_kind
    use constants
    use global_parameters_mod
    use planetary_system_mod
    use object_mod
    use file_mod

    implicit none

contains

    ! Process one timestep for an object or multiple objects.
    elemental subroutine timestep(my_object)
        implicit none

        type(object), intent(inout) :: my_object

    end subroutine timestep

    pure real(rk) function distance_squared(object1, object2)
        implicit none
        type(object), intent(in) :: object1, object2

        distance_squared = (object1 % position(1) - object2 % position(1)) ** 2 + &
            (object1 % position(2) - object2 % position(2)) ** 2 + &
            (object1 % position(3) - object2 % position(3)) ** 2
    end function distance_squared

    ! Return the gravitational force of `object1` to `object2`.
    pure real(rk) function compute_gravity(object1, object2)
        implicit none
        type(object), intent(in) :: object1, object2

        ! Distances in kilometers.
        ! Note: G has been adjusted accordingly.
        compute_gravity = G * object1 % mass * object2 % mass / &
            distance_squared(object1, object2)
    end function compute_gravity

    ! This function computes and updates the positions of the objects.
    subroutine compute_positions(my_global_parameters, my_planetary_system)
        implicit none
        type(global_parameters), intent(in) :: my_global_parameters
        type(planetary_system), intent(inout) :: my_planetary_system
        integer :: object_i
        real(rk) :: effect_of_acceleration(3)
        real(rk) :: effect_of_velocity(3)
        real(rk) :: timestep_s
        real(rk) :: acceleration_m_s2(3)

        ! Length of timestep is in hours.
        timestep_s = my_global_parameters % length_of_timestep * 3600.0

        position_loop: do object_i = 1, my_planetary_system % n_objects
            ! Position is in kilometers.
            ! Use km and s as the computation units.
            effect_of_velocity = timestep_s * (my_planetary_system % objects(object_i) % velocity)
            effect_of_acceleration = 0.5 * (my_planetary_system % objects(object_i) % acceleration) * timestep_s ** 2
            my_planetary_system % objects(object_i) % position = &
                my_planetary_system % objects(object_i) % position + effect_of_velocity + effect_of_acceleration
        end do position_loop

    end subroutine compute_positions

    subroutine compute_accelerations(my_planetary_system)
        implicit none
        type(planetary_system), intent(inout) :: my_planetary_system
        integer :: i, j
        real(rk) :: gravity_scalar
        real(rk) :: distance
        real(rk) :: unit_direction_from_2_to_1(3)

        outer_object_loop: do i = 1, my_planetary_system % n_objects

            inner_object_loop: do j = 1, my_planetary_system % n_objects
                if (i .eq. j) then
                    cycle
                end if

                ! Process the forces of caused by gravity.
                gravity_scalar = compute_gravity( &
                    my_planetary_system % objects(i), &
                    my_planetary_system % objects(j))

                distance = sqrt(distance_squared( &
                    my_planetary_system % objects(i), &
                    my_planetary_system % objects(j)))

                ! Object 2 gets force towards object 1.
                unit_direction_from_2_to_1 = (my_planetary_system % objects(i) % position - &
                    my_planetary_system % objects(j) % position) / distance

                ! Note: `new_acceleration` is acceleration in the a_(n+1) step!
                my_planetary_system % objects(j) % new_acceleration = (gravity_scalar * unit_direction_from_2_to_1) / &
                    my_planetary_system % objects(j) % mass
            end do inner_object_loop
        end do outer_object_loop
    end subroutine compute_accelerations

    subroutine compute_velocities(my_global_parameters, my_planetary_system)
        implicit none
        type(global_parameters), intent(in) :: my_global_parameters
        type(planetary_system), intent(inout) :: my_planetary_system
        real(rk) :: timestep_s
        integer :: i

        ! Velocity unit is km/s.

        ! Time step unit is h. It needs to be converted into seconds.
        timestep_s = my_global_parameters % length_of_timestep * 3600.0

        object_loop: do i = 1, my_planetary_system % n_objects
            my_planetary_system % objects(i) % velocity = &
                my_planetary_system % objects(i) % velocity + &
                0.5 * timestep_s * (my_planetary_system % objects(i) % acceleration + &
                my_planetary_system % objects(i) % new_acceleration)
        end do object_loop
    end subroutine compute_velocities

    logical function write_to_file(unit_number, my_planetary_system, iteration_i)
        implicit none
        integer, intent(in) :: unit_number
        type(planetary_system), intent(in) :: my_planetary_system
        integer, intent(in) :: iteration_i
        type(object) :: my_object
        integer :: ios, i
        character(len = 100) :: name_length_string

        write(unit_number, "(A20)", advance = "no") "Number of objects = "
        write(unit_number, "(g0)") my_planetary_system % n_objects
        write(unit_number, "(A20)", advance = "no") "Iteration index   = "
        write(unit_number, "(g0)") iteration_i

        object_loop: do i = 1, my_planetary_system % n_objects
            my_object = my_planetary_system % objects(i)

            ! Write the length of the name into `name_length_string`.
            write(name_length_string, "(g0)") len(my_object % name)

            write(unit_number, "(A7)", advance = "no") "name = "

            write(unit_number, "(A" // name_length_string // ")") my_object % name
            write(unit_number, "(A7)", advance = "no") "mass = "
            write(unit_number, "(g0)") my_object % mass
            write(unit_number, "(A7)", advance = "no") "x    = "
            write(unit_number, "(g0)") my_object % position(1)
            write(unit_number, "(A7)", advance = "no") "y    = "
            write(unit_number, "(g0)") my_object % position(2)
            write(unit_number, "(A7)", advance = "no") "z    = "
            write(unit_number, "(g0)") my_object % position(3)
            write(unit_number, "(A7)", advance = "no") "vx   = "
            write(unit_number, "(g0)") my_object % velocity(1)
            write(unit_number, "(A7)", advance = "no") "vy   = "
            write(unit_number, "(g0)") my_object % velocity(2)
            write(unit_number, "(A7)", advance = "no") "vz   = "
            write(unit_number, "(g0)") my_object % velocity(3)
            if (ios .ne. 0) then
                write(stdout, "(A23)") "Writing to file failed!"
            end if
        end do object_loop
    end function write_to_file

    subroutine update_accelerations(my_planetary_system)
        implicit none
        type(planetary_system), intent(inout) :: my_planetary_system
        integer :: i

        update_loop: do i = 1, my_planetary_system % n_objects
            my_planetary_system % objects(i) % acceleration = &
                my_planetary_system % objects(i) % new_acceleration
        end do update_loop
    end subroutine update_accelerations

    ! Simulate the planetary system according to the given input.
    logical function simulate(my_global_parameters, my_planetary_system)
        implicit none
        type(global_parameters), intent(in) :: my_global_parameters
        type(planetary_system), intent(inout) :: my_planetary_system
        character(len = :), allocatable :: filename
        integer, parameter :: unit_number = 1
        integer :: iteration_i, last_iteration_i, file_write_count
        real(rk) :: total_length_of_simulation_in_h
        logical :: file_open_success, file_write_success, file_close_success

        simulate = .false.

        file_write_count = 0

        write(stdout, "(A20)") "Hello from simulate!"

        ! Convert days into hours by multiplying by 24.
        total_length_of_simulation_in_h = 24.0 * my_global_parameters % total_length_of_simulation

        ! Length of timestep is provided in hours.
        last_iteration_i = total_length_of_simulation_in_h / my_global_parameters % length_of_timestep

        filename = "output.dat"

        file_open_success = open_file_for_writing(filename, unit_number)

        if (file_open_success) then
            write(stdout, "(A41)") "File was opened successfully for writing."
        else
            write(stdout, "(A20)") "File opening failed!"
        end if

        iteration_loop: do iteration_i = 1, last_iteration_i
            call compute_positions(my_global_parameters, my_planetary_system)

            call compute_accelerations(my_planetary_system)

            call compute_velocities(my_global_parameters, my_planetary_system)

            call update_accelerations(my_planetary_system)

            if (iteration_i .eq. 1 .or. &
                iteration_i .eq. last_iteration_i .or. &
                mod(iteration_i, my_global_parameters % save_interval) .eq. 0) then
                file_write_success = write_to_file(unit_number, my_planetary_system, iteration_i)
                file_write_count = file_write_count + 1
            end if

            if (iteration_i .eq. 1 .or. &
                iteration_i .eq. last_iteration_i .or. &
                mod(iteration_i, my_global_parameters % print_interval) .eq. 0) then
                write(stdout, "(A20)", advance = "no") "Number of objects = "
                write(stdout, "(g0)") my_planetary_system % n_objects
                write(stdout, "(A20)", advance = "no") "Iteration index   = "
                write(stdout, "(g0)") iteration_i
                write(stdout, "(A20)", advance = "no") "File write count  = "
                write(stdout, "(g0)") file_write_count

                if (iteration_i .eq. 1) then
                    write(stdout, "(A35)") "This is end of the first iteration."
                end if
                if (iteration_i .eq. last_iteration_i) then
                    write(stdout, "(A38)") "This is the end of the last iteration."
                end if

                call print_objects(my_planetary_system)
            end if

        end do iteration_loop

        file_close_success = close_file(unit_number)

        if (file_close_success) then
            write(stdout, "(A29)") "File was closed successfully."
        else
            write(stdout, "(A20)") "File closing failed!"
        end if

        ! Simulation ended successfully.
        simulate = .true.
    end function simulate

end module physics_mod
