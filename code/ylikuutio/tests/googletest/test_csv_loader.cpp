#include "gtest/gtest.h"
#include "code/ylikuutio/load/csv_loader.hpp"
#include "code/ylikuutio/load/csv_loader.cpp"
#include "code/ylikuutio/linear_algebra/matrix.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <limits>  // std::numeric_limits
#include <memory>  // std::make_shared, std::shared_ptr
#include <string>  // std::string
#include <vector>  // std::vector

TEST(csv_file_must_be_loaded_appropriately, some_finnish_railway_stations)
{
    const std::string some_finnish_railway_stations_csv_filename = "some_finnish_railway_stations_float.csv";
    std::size_t data_width;
    std::size_t data_height;
    std::size_t data_size;
    std::shared_ptr<std::vector<float>> data_vector = yli::load::load_CSV_file(some_finnish_railway_stations_csv_filename, data_width, data_height, data_size);
    ASSERT_NE(data_vector, nullptr);

    ASSERT_EQ(data_width, 17);
    ASSERT_EQ(data_height, 17);
    ASSERT_EQ(data_size, 17 * 17);

    yli::linear_algebra::Matrix railway_neighbors_from_csv_file(17, 17);
    ASSERT_TRUE(railway_neighbors_from_csv_file.get_is_square());
    ASSERT_EQ(railway_neighbors_from_csv_file.get_height(), 17);
    ASSERT_EQ(railway_neighbors_from_csv_file.get_height(), 17);

    railway_neighbors_from_csv_file << *data_vector;

#define INF std::numeric_limits<float>::infinity()

    yli::linear_algebra::Matrix railway_neighbors(17, 17);
    railway_neighbors << std::vector<float> {
//      Hpk,    Ilm,    Jns,     Jy,     Ke,     Kv,     Lh,     Ov,     Ol,     Ri,    Psl,     Pm,     Sk,    Tpe,     Tl,    Tku,     Yv
       0.0f,    INF,    INF,  78.0f,    INF,    INF,    INF,  72.0f,    INF,    INF,    INF,    INF, 118.0f,    INF,    INF,    INF,    INF,   // Hpk
        INF,   0.0f,    INF,    INF,    INF,    INF,    INF,    INF, 275.0f,    INF,    INF, 174.0f,    INF,    INF,    INF,    INF, 154.0f,   // Ilm
        INF,    INF,   0.0f,    INF,    INF, 316.0f,    INF,    INF,    INF,    INF,    INF, 183.0f,    INF,    INF,    INF,    INF,    INF,   // Jns
      78.0f,    INF,    INF,   0.0f,    INF,    INF,    INF, 113.0f,    INF,    INF,    INF,  80.0f,    INF,    INF,    INF,    INF,    INF,   // Jy
        INF,    INF,    INF,    INF,   0.0f,    INF,  75.0f,    INF,    INF,  42.0f,  26.0f,    INF,    INF,    INF,    INF,    INF,    INF,   // Ke
        INF,    INF, 316.0f,    INF,    INF,   0.0f,  62.0f,    INF,    INF,    INF,    INF, 184.0f,    INF,    INF,    INF,    INF,    INF,   // Kv
        INF,    INF,    INF,    INF,  75.0f,  62.0f,   0.0f,    INF,    INF,  59.0f,    INF,    INF,    INF,    INF,    INF,    INF,    INF,   // Lh
      72.0f,    INF,    INF, 113.0f,    INF,    INF,    INF,   0.0f,    INF,    INF,    INF,    INF,    INF,  42.0f,    INF,    INF,    INF,   // Ov
        INF, 275.0f,    INF,    INF,    INF,    INF,    INF,    INF,   0.0f,    INF,    INF,    INF,    INF,    INF,    INF,    INF, 122.0f,   // Ol
        INF,    INF,    INF,    INF,  42.0f,    INF,  59.0f,    INF,    INF,   0.0f,    INF,    INF,    INF,    INF,  76.0f,    INF,    INF,   // Ri
        INF,    INF,    INF,    INF,  26.0f,    INF,    INF,    INF,    INF,    INF,   0.0f,    INF,    INF,    INF,    INF, 191.0f,    INF,   // Psl
        INF, 174.0f, 183.0f,  80.0f,    INF, 184.0f,    INF,    INF,    INF,    INF,    INF,   0.0f,    INF,    INF,    INF,    INF,    INF,   // Pm
     118.0f,    INF,    INF,    INF,    INF,    INF,    INF,    INF,    INF,    INF,    INF,    INF,   0.0f, 160.0f,    INF,    INF, 211.0f,   // Sk
        INF,    INF,    INF,    INF,    INF,    INF,    INF,  42.0f,    INF,    INF,    INF,    INF, 160.0f,   0.0f,  40.0f,    INF,    INF,   // Tpe
        INF,    INF,    INF,    INF,    INF,    INF,    INF,    INF,    INF,  76.0f,    INF,    INF,    INF,  40.0f,   0.0f, 128.0f,    INF,   // Tl
        INF,    INF,    INF,    INF,    INF,    INF,    INF,    INF,    INF,    INF, 191.0f,    INF,    INF,    INF, 128.0f,   0.0f,    INF,   // Tku
        INF, 154.0f,    INF,    INF,    INF,    INF,    INF,    INF, 122.0f,    INF,    INF,    INF, 211.0f,    INF,    INF,    INF,   0.0f }; // Yv

#undef INF

    ASSERT_EQ(railway_neighbors_from_csv_file, railway_neighbors);
}
