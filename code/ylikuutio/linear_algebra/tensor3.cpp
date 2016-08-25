#include "tensor3.hpp"
#include "matrix.hpp"

// Include standard headers
#include <stdint.h> // uint32_t etc.

namespace linear_algebra
{
    Tensor3::Tensor3(uint32_t height, uint32_t width, uint32_t depth)
    {
        // constructor.
        this->width = width;
        this->height = height;
        this->depth = depth;
    }

    Tensor3::Tensor3(Tensor3& old_tensor3)
    {
        // copy constructor.
        this->width = old_tensor3.width;
        this->height = old_tensor3.height;
        this->depth = old_tensor3.depth;
        this->array_of_arrays_of_arrays = new float**[this->height];

        for (uint32_t y = 0; y < this->height; y++)
        {
            this->array_of_arrays_of_arrays[y] = new float*[this->width];

            for (uint32_t x = 0; x < this->width; x++)
            {
                this->array_of_arrays_of_arrays[y][x] = new float[this->depth];
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

    Tensor3::Tensor3(Matrix& old_matrix)
    {
        // constructor.

        this->width = old_matrix.width;
        this->height = old_matrix.height;
        this->depth = 1;
        this->array_of_arrays_of_arrays = new float**[this->height];

        for (uint32_t y = 0; y < this->height; y++)
        {
            this->array_of_arrays_of_arrays[y] = new float*[this->width];

            for (uint32_t x = 0; x < this->width; x++)
            {
                this->array_of_arrays_of_arrays[y][x] = new float[this->depth];
            }
        }

        this->next_x_to_populate = 0;
        this->next_y_to_populate = 0;
        this->next_z_to_populate = 0;
        this->is_fully_populated = false;

        this->is_cube = false;
    }

    Tensor3::~Tensor3()
    {
    }

    void Tensor3::operator<<(const float rhs)
    {
        if (this->is_fully_populated)
        {
            // Array is already fully populated. Nothing to do.
            return;
        }

        // First, get the slice.
        float** my_array_of_arrays = this->array_of_arrays_of_arrays[this->next_y_to_populate];
        float* my_array = my_array_of_arrays[this->next_x_to_populate];

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

        if (this->is_fully_populated && rhs_i < rhs.size())
        {
            // Array is already fully populated. Nothing to do.
            return;
        }

        // First, get the slice.
        float** my_array_of_arrays = this->array_of_arrays_of_arrays[this->next_y_to_populate];
        float* my_array = my_array_of_arrays[this->next_x_to_populate];

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
