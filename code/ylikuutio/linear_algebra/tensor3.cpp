#include "tensor3.hpp"
#include "matrix.hpp"

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace linear_algebra
{
    // `class Tensor3` uses the same coordinate order as MATLAB,
    // to make testing easier. So: y, x, z.
    // y = 0 is the uppermost slice
    // x = 0 is the leftmost slice.
    // z = 0 is the front slice.

    Tensor3::Tensor3(uint32_t height, uint32_t width, uint32_t depth)
    {
        // constructor.
        this->width = width;
        this->height = height;
        this->depth = depth;
        this->array_of_arrays_of_arrays.resize(this->height);

        for (uint32_t y = 0; y < this->height; y++)
        {
            this->array_of_arrays_of_arrays.at(y).resize(this->width);

            for (uint32_t x = 0; x < this->width; x++)
            {
                this->array_of_arrays_of_arrays.at(y).at(x).resize(this->depth);
            }
        }

        this->next_x_to_populate = 0;
        this->next_y_to_populate = 0;
        this->next_z_to_populate = 0;
        this->is_fully_populated = false;

        if (this->width == this->height && this->height == this->depth)
        {
            this->is_cube = true;
        }
        else
        {
            this->is_cube = false;
        }
    }

    Tensor3::Tensor3(linear_algebra::Tensor3& old_tensor3)
    {
        // copy constructor.
        this->width = old_tensor3.width;
        this->height = old_tensor3.height;
        this->depth = old_tensor3.depth;
        this->array_of_arrays_of_arrays.resize(this->height);

        for (uint32_t y = 0; y < this->height; y++)
        {
            this->array_of_arrays_of_arrays.at(y).resize(this->width);

            for (uint32_t x = 0; x < this->width; x++)
            {
                this->array_of_arrays_of_arrays.at(y).at(x).resize(this->depth);
            }
        }

        this->next_x_to_populate = 0;
        this->next_y_to_populate = 0;
        this->next_z_to_populate = 0;
        this->is_fully_populated = false;

        if (this->width == this->height && this->height == this->depth)
        {
            this->is_cube = true;
        }
        else
        {
            this->is_cube = false;
        }
    }

    Tensor3::Tensor3(linear_algebra::Matrix& old_matrix)
    {
        // constructor.

        this->width = old_matrix.width;
        this->height = old_matrix.height;
        this->depth = 1;
        this->array_of_arrays_of_arrays.resize(this->height);

        for (uint32_t y = 0; y < this->height; y++)
        {
            this->array_of_arrays_of_arrays.at(y).resize(this->width);

            for (uint32_t x = 0; x < this->width; x++)
            {
                this->array_of_arrays_of_arrays.at(y).at(x).resize(this->depth);
            }
        }

        this->next_x_to_populate = 0;
        this->next_y_to_populate = 0;
        this->next_z_to_populate = 0;
        this->is_fully_populated = false;

        this->is_cube = false;
    }

    void Tensor3::operator<<(const float rhs)
    {
        if (this->is_fully_populated)
        {
            // Array is already fully populated. Nothing to do.
            return;
        }

        // First, get the slice.
        std::vector<std::vector<float>>& my_array_of_arrays = this->array_of_arrays_of_arrays[this->next_y_to_populate];
        std::vector<float>& my_array = my_array_of_arrays[this->next_x_to_populate];

        // Then store the value.
        my_array[this->next_z_to_populate] = rhs;

        if (++this->next_x_to_populate >= this->width)
        {
            this->next_x_to_populate = 0;

            if (++this->next_y_to_populate >= this->height)
            {
                this->next_y_to_populate = 0;

                if (++this->next_z_to_populate >= this->depth)
                {
                    this->is_fully_populated = true;
                }
            }
        }
    }

    void Tensor3::operator<<(const std::vector<float>& rhs)
    {
        uint32_t rhs_i = 0;

        while (!this->is_fully_populated && rhs_i < rhs.size())
        {
            // First, get the slice.
            std::vector<std::vector<float>>& my_array_of_arrays = this->array_of_arrays_of_arrays[this->next_y_to_populate];
            std::vector<float>& my_array = my_array_of_arrays[this->next_x_to_populate];

            // Then store the value.
            my_array[this->next_z_to_populate] = rhs.at(rhs_i++);

            if (++this->next_x_to_populate >= this->width)
            {
                this->next_x_to_populate = 0;

                if (++this->next_y_to_populate >= this->height)
                {
                    this->next_y_to_populate = 0;

                    if (++this->next_z_to_populate >= this->depth)
                    {
                        this->is_fully_populated = true;
                    }
                }
            }
        }
    }

    bool Tensor3::operator==(linear_algebra::Tensor3& rhs)
    {
        // compare if tensors are equal.
        if (this->width != rhs.width ||
                this->height != rhs.height ||
                this->depth != rhs.depth)
        {
            // Tensors are not equal, if they have different sizes.
            return false;
        }

        for (uint32_t y = 0; y < this->height; y++)
        {
            // Get the slices of both arrays.
            std::vector<std::vector<float>>& my_array_of_arrays = this->array_of_arrays_of_arrays[y];
            std::vector<std::vector<float>>& other_array_of_arrays = rhs.array_of_arrays_of_arrays[y];

            for (uint32_t x = 0; x < this->width; x++)
            {
                std::vector<float>& my_array = my_array_of_arrays[x];
                std::vector<float>& other_array = other_array_of_arrays[x];

                for (uint32_t z = 0; z < this->depth; z++)
                {
                    if (my_array[z] != other_array[z])
                    {
                        // Arrays are not identical.
                        return false;
                    }
                }
            }
        }
        // Everything matches. Arrays are identical.
        return true;
    }

    bool Tensor3::operator!=(linear_algebra::Tensor3& rhs)
    {
        // compare if tensors are equal.
        if (this->width != rhs.width ||
                this->height != rhs.height ||
                this->depth != rhs.depth)
        {
            // Tensors are not equal, if they have different sizes.
            return true;
        }

        for (uint32_t y = 0; y < this->height; y++)
        {
            // Get the slices of both arrays.
            std::vector<std::vector<float>>& my_array_of_arrays = this->array_of_arrays_of_arrays[y];
            std::vector<std::vector<float>>& other_array_of_arrays = rhs.array_of_arrays_of_arrays[y];

            for (uint32_t x = 0; x < this->width; x++)
            {
                std::vector<float>& my_array = my_array_of_arrays[x];
                std::vector<float>& other_array = other_array_of_arrays[x];

                for (uint32_t z = 0; z < this->depth; z++)
                {
                    if (my_array[z] != other_array[z])
                    {
                        // Arrays are not identical.
                        return true;
                    }
                }
            }
        }
        // Everything matches. Arrays are identical.
        return false;
    }
}
