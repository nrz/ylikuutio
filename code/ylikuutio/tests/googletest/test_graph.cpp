// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

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

#define RAILWAY_STATION_HPK  0
#define RAILWAY_STATION_ILM  1
#define RAILWAY_STATION_JNS  2
#define RAILWAY_STATION_JY   3
#define RAILWAY_STATION_KE   4
#define RAILWAY_STATION_KV   5
#define RAILWAY_STATION_LH   6
#define RAILWAY_STATION_OV   7
#define RAILWAY_STATION_OL   8
#define RAILWAY_STATION_RI   9
#define RAILWAY_STATION_PSL 10
#define RAILWAY_STATION_PM  11
#define RAILWAY_STATION_SK  12
#define RAILWAY_STATION_TPE 13
#define RAILWAY_STATION_TL  14
#define RAILWAY_STATION_TKU 15
#define RAILWAY_STATION_YV  16

    // NOTE: the distances below use Helsinki as zero point (0 km), when applicable.
    // Therefore, the distance between Seinäjoki and Oulu is 333.0 km in either direction.
    // 333.0 km computed from VR timetable 7 in the direction of Helsinki-Kemijärvi. In other direction it is 334 km.
    // Distances from VR timetables for routes which do not begin or end in Helsinki are read from the first listed direction, that is:
    // Joensuu-Turku, Iisalmi-Ylivieska, Tampere-Haapamäki-Seinäjoki, Jyväskylä-Haapamäki-Seinäjoki.

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

    // Distance from anywhere to the same station is 0.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_HPK][RAILWAY_STATION_HPK], 0.0f);
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_ILM][RAILWAY_STATION_ILM], 0.0f);
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_JNS][RAILWAY_STATION_JNS], 0.0f);
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_JY][RAILWAY_STATION_JY], 0.0f);
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_KE][RAILWAY_STATION_KE], 0.0f);
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_KV][RAILWAY_STATION_KV], 0.0f);
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_LH][RAILWAY_STATION_LH], 0.0f);
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_OV][RAILWAY_STATION_OV], 0.0f);
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_OL][RAILWAY_STATION_OL], 0.0f);
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_RI][RAILWAY_STATION_RI], 0.0f);
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_PSL][RAILWAY_STATION_PSL], 0.0f);
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_PM][RAILWAY_STATION_PM], 0.0f);
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_SK][RAILWAY_STATION_SK], 0.0f);
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_TPE][RAILWAY_STATION_TPE], 0.0f);
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_TL][RAILWAY_STATION_TL], 0.0f);
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_TKU][RAILWAY_STATION_TKU], 0.0f);
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_YV][RAILWAY_STATION_YV], 0.0f);

    // timetable 1.

    // Turku-Pasila, 191.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_TKU][RAILWAY_STATION_PSL], 191.0f);

    // Pasila-Turku, 191.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_PSL][RAILWAY_STATION_TKU], 191.0f);

    // timetable 7.

    // Oulu-Ylivieska, 122.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_OL][RAILWAY_STATION_YV], 122.0f);

    // Oulu-Ylivieska, 122.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_YV][RAILWAY_STATION_OL], 122.0f);

    // Oulu-Seinäjoki, 333.0 km.
    // NOTE: this is from timetable 7 in the direction of Helsinki-Kemijärvi. In other direction it is 334 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_OL][RAILWAY_STATION_SK], 333.0f);

    // Seinäjoki-Oulu, 333.0 km.
    // NOTE: this is from timetable 7 in the direction of Helsinki-Kemijärvi. In other direction it is 334 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_SK][RAILWAY_STATION_OL], 333.0f);

    // Oulu-Tampere, 493.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_OL][RAILWAY_STATION_TPE], 493.0f);

    // Tampere-Oulu, 493.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_TPE][RAILWAY_STATION_OL], 493.0f);

    // Oulu-Pasila, 677.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_OL][RAILWAY_STATION_PSL], 677.0f);

    // Pasila-Oulu, 677.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_PSL][RAILWAY_STATION_OL], 677.0f);

    // Ylivieska-Tampere, 371.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_YV][RAILWAY_STATION_TPE], 371.0f);

    // Tampere-Ylivieska, 371.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_TPE][RAILWAY_STATION_YV], 371.0f);

    // Seinäjoki-Tampere, 160.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_SK][RAILWAY_STATION_TPE], 160.0f);

    // Tampere-Seinäjoki, 160.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_TPE][RAILWAY_STATION_SK], 160.0f);

    // Tampere-Toijala, 40.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_TPE][RAILWAY_STATION_TL], 40.0f);

    // Toijala-Tampere, 40.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_TL][RAILWAY_STATION_TPE], 40.0f);

    // Tampere-Riihimäki, 116.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_TPE][RAILWAY_STATION_RI], 116.0f);

    // Riihimäki-Tampere, 116.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_RI][RAILWAY_STATION_TPE], 116.0f);

    // Toijala-Riihimäki, 76.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_TL][RAILWAY_STATION_RI], 76.0f);

    // Riihimäki-Toijala, 76.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_RI][RAILWAY_STATION_TL], 76.0f);

    // timetable 9.

    // Joensuu-Pieksämäki, 183.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_JNS][RAILWAY_STATION_PM], 183.0f);

    // Pieksämäki-Joensuu, 183.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_PM][RAILWAY_STATION_JNS], 183.0f);

    // Joensuu-Tampere via Pieksämäki, 418.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_JNS][RAILWAY_STATION_TPE], 418.0f);

    // Tampere-Joensuu via Pieksämäki, 418.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_TPE][RAILWAY_STATION_JNS], 418.0f);

    // Joensuu-Turku via Pieksämäki, 586.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_JNS][RAILWAY_STATION_TKU], 586.0f);

    // Turku-Joensuu via Pieksämäki, 586.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_TKU][RAILWAY_STATION_JNS], 586.0f);

    // Pieksämäki-Tampere, 235.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_PM][RAILWAY_STATION_TPE], 235.0f);

    // Tampere-Pieksämäki, 235.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_TPE][RAILWAY_STATION_PM], 235.0f);

    // Tampere-Turku, 168.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_TPE][RAILWAY_STATION_TKU], 168.0f);

    // Turku-Tampere, 168.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_TKU][RAILWAY_STATION_TPE], 168.0f);

    // timetable 11.

    // Tampere-Haapamäki via Orivesi, 114.0 km.
    // NOTE: Tampere-Haapamäki via Seinäjoki is 160.0 km + 118.0 km = 278.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_TPE][RAILWAY_STATION_HPK], 114.0f);

    // Haapamäki-Tampere via Orivesi, 114.0 km.
    // NOTE: Haapamäki-Tampere via Seinäjoki is 118.0 + 160.0 km km = 278.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_HPK][RAILWAY_STATION_TPE], 114.0f);

    // Jyväskylä-Seinäjoki via Haapamäki, 196.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_JY][RAILWAY_STATION_SK], 196.0f);

    // Seinäjoki-Jyväskylä via Haapamäki, 196.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_SK][RAILWAY_STATION_JY], 196.0f);

    // timetable 12A.

    // Lahti-Riihimäki, 59.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_LH][RAILWAY_STATION_RI], 59.0f);

    // Riihimäki-Lahti, 59.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_RI][RAILWAY_STATION_LH], 59.0f);

    // timetable 13.

    // Oulu-Iisalmi via Kontiomäki, 275.0 km.
    // NOTE: Oulu-Iisalmi via Ylivieska is 122.0 km + 154.0 km = 276.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_OL][RAILWAY_STATION_ILM], 275.0f);

    // Iisalmi-Oulu via Kontiomäki, 275.0 km.
    // NOTE: Iisalmi-Oulu via Ylivieska is 154.0 km + 122.0 km = 276.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_ILM][RAILWAY_STATION_OL], 275.0f);

    // Oulu-Pieksämäki via Kontiomäki, 449.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_OL][RAILWAY_STATION_PM], 449.0f);

    // Pieksämäki-Oulu via Kontiomäki, 449.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_PM][RAILWAY_STATION_OL], 449.0f);

    // Oulu-Kouvola via Kontiomäki, 633.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_OL][RAILWAY_STATION_KV], 633.0f);

    // Kouvola-Oulu via Kontiomäki, 633.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_KV][RAILWAY_STATION_OL], 633.0f);

    // Iisalmi-Pieksämäki, 174.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_ILM][RAILWAY_STATION_PM], 174.0f);

    // Pieksämäki-Iisalmi, 174.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_ILM][RAILWAY_STATION_PM], 174.0f);

    // Kouvola-Lahti, 62.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_KV][RAILWAY_STATION_LH], 62.0f);

    // Lahti-Kouvola, 62.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_LH][RAILWAY_STATION_KV], 62.0f);

    // timetable 14.

    // Joensuu-Lahti, 378.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_JNS][RAILWAY_STATION_LH], 378.0f);

    // Lahti-Joensuu, 378.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_LH][RAILWAY_STATION_JNS], 378.0f);

    // Joensuu-Pasila, 479.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_JNS][RAILWAY_STATION_PSL], 479.0f);

    // Pasila-Joensuu, 479.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_PSL][RAILWAY_STATION_JNS], 479.0f);

    // combined timetables.

    // Pieksämäki-Seinäjoki via Jyväskylä and Haapamäki, 276.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_PM][RAILWAY_STATION_SK], 276.0f);

    // Seinäjoki-Pieksämäki via Haapamäki and Jyväskylä, 276.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_SK][RAILWAY_STATION_PM], 276.0f);

    // Oulu-Joensuu via Kontiomäki and Pieksämäki, 632.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_OL][RAILWAY_STATION_JNS], 632.0f);

    // Joensuu-Oulu via Pieksämäki and Kontiomäki, 632.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_JNS][RAILWAY_STATION_OL], 632.0f);

    // Iisalmi-Seinäjoki via Ylivieska, 365.0 km.
    // NOTE: Iisalmi-Seinäjoki via Pieksämäki, Jyväskylä, and Haapamäki is 174.0 km + 80.0 km + 196.0 km = 450.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_ILM][RAILWAY_STATION_SK], 365.0f);

    // Seinäjoki-Iisalmi via Ylivieska, 365.0 km.
    // NOTE: Seinäjoki-Iisalmi via Haapamäki, Jyväskylä, and Pieksämäki is 196.0 km + 80.0 km + 174.0 km = 450.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_SK][RAILWAY_STATION_ILM], 365.0f);

    // Joensuu-Seinäjoki via Pieksämäki and Jyväskylä, 459.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_JNS][RAILWAY_STATION_SK], 459.0f);

    // Seinäjoki-Joensuu via Jyväskylä and Pieksämäki, 459.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_SK][RAILWAY_STATION_JNS], 459.0f);

    // Iisalmi-Tampere via Pieksämäki, 409.0 km.
    // NOTE: Iisalmi-Tampere via Ylivieska and Seinäjoki is 154.0 km + 371.0 km = 525.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_ILM][RAILWAY_STATION_TPE], 409.0f);

    // Tampere-Iisalmi via Pieksämäki, 409.0 km.
    // NOTE: Tampere-Iisalmi via Seinäjoki and Ylivieska is 371.0 km + 154.0 km = 525.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_TPE][RAILWAY_STATION_ILM], 409.0f);

    // Iisalmi-Turku via Pieksämäki, 577.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_ILM][RAILWAY_STATION_TKU], 577.0f);

    // Turku-Iisalmi via Pieksämäki, 577.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_TKU][RAILWAY_STATION_ILM], 577.0f);

    // Joensuu-Riihimäki via Kouvola and Lahti, 437.0 km.
    // NOTE: Joensuu-Riihimäki via Pieksämäki and Tampere is 418.0 km + 116.0 km = 534.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_JNS][RAILWAY_STATION_RI], 437.0f);

    // Riihimäki-Joensuu via Lahti and Kouvola, 437.0 km.
    // NOTE: Riihimäki-Joensuu via Tampere and Pieksämäki is 116.0 km + 418.0 km = 534.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_RI][RAILWAY_STATION_JNS], 437.0f);

    // Joensuu-Toijala via Kouvola and Lahti, 458.0 km.
    // NOTE: Joensuu-Toijala via Lahti and Riihmäki is 378.0 km + 59.0 km + 76.0 km = 513.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_JNS][RAILWAY_STATION_TL], 458.0f);

    // Toijala-Joensuu via Lahti and Kouvola, 458.0 km.
    // NOTE: Toijala-Joensuu via Riihmäki and Lahti is 76.0 km + 59.0 km + 378.0 km = 513.0 km.
    ASSERT_EQ((*distance_matrix)[RAILWAY_STATION_JNS][RAILWAY_STATION_TL], 458.0f);

#undef RAILWAY_STATION_HPK
#undef RAILWAY_STATION_ILM
#undef RAILWAY_STATION_JNS
#undef RAILWAY_STATION_JY
#undef RAILWAY_STATION_KE
#undef RAILWAY_STATION_KV
#undef RAILWAY_STATION_LH
#undef RAILWAY_STATION_OV
#undef RAILWAY_STATION_OL
#undef RAILWAY_STATION_RI
#undef RAILWAY_STATION_PSL
#undef RAILWAY_STATION_PM
#undef RAILWAY_STATION_SK
#undef RAILWAY_STATION_TPE
#undef RAILWAY_STATION_TL
#undef RAILWAY_STATION_TKU
#undef RAILWAY_STATION_YV
}

#undef INF
