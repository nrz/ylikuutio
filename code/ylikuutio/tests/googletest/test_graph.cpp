#include "gtest/gtest.h"
#include "code/ylikuutio/graph/shortest_paths.hpp"
#include "code/ylikuutio/linear_algebra/matrix.hpp"
#include "code/ylikuutio/linear_algebra/matrix_functions.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iomanip>  // std::setfill, std::setprecision, std::setw
#include <iostream> // std::cout, std::cin, std::cerr
#include <limits>   // std::numeric_limits
#include <memory>   // std::make_shared, std::shared_ptr
#include <string>   // std::string
#include <vector>   // std::vector

#define INF std::numeric_limits<float>::infinity()

TEST(floyd_warshall_must_function_as_expected, finnish_railway_stations)
{
    // Railway distances between some Finnish railway stations.
    // NOTE: stations are ordered in alphabetical order of the station names,
    // not the alphabetical order of the station codes!
    //
    // FIXME: distances to/from Hiekkaharju and Huopalahti are missing,
    // therefore currently Pasila is a neighbor of Kerava and Turku.
    //
    // Haapamäki,   Hpk
    // Iisalmi,     Ilm
    // Joensuu,     Jns
    // Jyväskylä,   Jy
    // Kerava,      Ke
    // Kouvola,     Kv
    // Lahti,       Lh
    // Orivesi,     Ov
    // Oulu,        Ol
    // Riihimäki,   Ri
    // Pasila,      Psl
    // Pieksämäki,  Pm
    // Seinäjoki,   Sk
    // Tampere,     Tpe
    // Toijala,     Tl
    // Turku,       Tku
    // Ylivieska,   Yv
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

    std::shared_ptr<yli::linear_algebra::Matrix> distance_matrix = yli::graph::floyd_warshall(railway_neighbors);

    std::vector<std::string> station_codes { "Hpk", "Ilm", "Jns", "Jy", "Ke", "Kv", "Lh", "Ov", "Ol", "Ri", "Psl", "Pm", "Sk", "Tpe", "Tl", "Tku", "Yv" };
    std::cout << "    ";

    for (std::size_t i = 0; i < station_codes.size(); i++)
    {
        std::cout << std::setfill(' ') << std::setw(3) << station_codes[i] << " ";
    }

    std::cout << "\n";

    for (std::size_t j = 0; j < distance_matrix->get_height(); j++)
    {
        std::cout << std::setfill(' ') << std::setw(3) << station_codes[j] << " ";

        for (std::size_t i = 0; i < distance_matrix->get_width(); i++)
        {
            std::cout << std::setfill(' ') << std::setw(3) << (*distance_matrix)[j][i] << " ";
        }

        std::cout << "\n";
    }
}

#undef INF
