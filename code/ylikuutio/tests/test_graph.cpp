// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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
#include <iostream> // std::cout, std::cerr
#include <limits>   // std::numeric_limits
#include <memory>   // std::shared_ptr
#include <string>   // std::string
#include <vector>   // std::vector

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

    enum RailwayStation
    {
        HPK =  0,
        ILM =  1,
        JNS =  2,
        JY  =  3,
        KE  =  4,
        KV  =  5,
        LH  =  6,
        OV  =  7,
        OL  =  8,
        RI  =  9,
        PSL = 10,
        PM  = 11,
        SK  = 12,
        TPE = 13,
        TL  = 14,
        TKU = 15,
        YV  = 16
    };

    // NOTE: the distances below use Helsinki as zero point (0 km), when applicable.
    // Therefore, the distance between Seinäjoki and Oulu is 333.0 km in either direction.
    // 333.0 km computed from VR timetable 7 in the direction of Helsinki-Kemijärvi. In other direction it is 334 km.
    // Distances from VR timetables for routes which do not begin or end in Helsinki are read from the first listed direction, that is:
    // Joensuu-Turku, Iisalmi-Ylivieska, Tampere-Haapamäki-Seinäjoki, Jyväskylä-Haapamäki-Seinäjoki.

    const float inf { std::numeric_limits<float>::infinity() };

    yli::linear_algebra::Matrix railway_neighbors(17, 17);
    railway_neighbors << std::vector<float> {
//      Hpk,    Ilm,    Jns,     Jy,     Ke,     Kv,     Lh,     Ov,     Ol,     Ri,    Psl,     Pm,     Sk,    Tpe,     Tl,    Tku,     Yv
       0.0f,    inf,    inf,  78.0f,    inf,    inf,    inf,  72.0f,    inf,    inf,    inf,    inf, 118.0f,    inf,    inf,    inf,    inf,   // Hpk
        inf,   0.0f,    inf,    inf,    inf,    inf,    inf,    inf, 275.0f,    inf,    inf, 174.0f,    inf,    inf,    inf,    inf, 154.0f,   // Ilm
        inf,    inf,   0.0f,    inf,    inf, 316.0f,    inf,    inf,    inf,    inf,    inf, 183.0f,    inf,    inf,    inf,    inf,    inf,   // Jns
      78.0f,    inf,    inf,   0.0f,    inf,    inf,    inf, 113.0f,    inf,    inf,    inf,  80.0f,    inf,    inf,    inf,    inf,    inf,   // Jy
        inf,    inf,    inf,    inf,   0.0f,    inf,  75.0f,    inf,    inf,  42.0f,  26.0f,    inf,    inf,    inf,    inf,    inf,    inf,   // Ke
        inf,    inf, 316.0f,    inf,    inf,   0.0f,  62.0f,    inf,    inf,    inf,    inf, 184.0f,    inf,    inf,    inf,    inf,    inf,   // Kv
        inf,    inf,    inf,    inf,  75.0f,  62.0f,   0.0f,    inf,    inf,  59.0f,    inf,    inf,    inf,    inf,    inf,    inf,    inf,   // Lh
      72.0f,    inf,    inf, 113.0f,    inf,    inf,    inf,   0.0f,    inf,    inf,    inf,    inf,    inf,  42.0f,    inf,    inf,    inf,   // Ov
        inf, 275.0f,    inf,    inf,    inf,    inf,    inf,    inf,   0.0f,    inf,    inf,    inf,    inf,    inf,    inf,    inf, 122.0f,   // Ol
        inf,    inf,    inf,    inf,  42.0f,    inf,  59.0f,    inf,    inf,   0.0f,    inf,    inf,    inf,    inf,  76.0f,    inf,    inf,   // Ri
        inf,    inf,    inf,    inf,  26.0f,    inf,    inf,    inf,    inf,    inf,   0.0f,    inf,    inf,    inf,    inf, 191.0f,    inf,   // Psl
        inf, 174.0f, 183.0f,  80.0f,    inf, 184.0f,    inf,    inf,    inf,    inf,    inf,   0.0f,    inf,    inf,    inf,    inf,    inf,   // Pm
     118.0f,    inf,    inf,    inf,    inf,    inf,    inf,    inf,    inf,    inf,    inf,    inf,   0.0f, 160.0f,    inf,    inf, 211.0f,   // Sk
        inf,    inf,    inf,    inf,    inf,    inf,    inf,  42.0f,    inf,    inf,    inf,    inf, 160.0f,   0.0f,  40.0f,    inf,    inf,   // Tpe
        inf,    inf,    inf,    inf,    inf,    inf,    inf,    inf,    inf,  76.0f,    inf,    inf,    inf,  40.0f,   0.0f, 128.0f,    inf,   // Tl
        inf,    inf,    inf,    inf,    inf,    inf,    inf,    inf,    inf,    inf, 191.0f,    inf,    inf,    inf, 128.0f,   0.0f,    inf,   // Tku
        inf, 154.0f,    inf,    inf,    inf,    inf,    inf,    inf, 122.0f,    inf,    inf,    inf, 211.0f,    inf,    inf,    inf,   0.0f }; // Yv

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
    ASSERT_EQ((*distance_matrix)[RailwayStation::HPK][RailwayStation::HPK], 0.0f);
    ASSERT_EQ((*distance_matrix)[RailwayStation::ILM][RailwayStation::ILM], 0.0f);
    ASSERT_EQ((*distance_matrix)[RailwayStation::JNS][RailwayStation::JNS], 0.0f);
    ASSERT_EQ((*distance_matrix)[RailwayStation::JY][RailwayStation::JY], 0.0f);
    ASSERT_EQ((*distance_matrix)[RailwayStation::KE][RailwayStation::KE], 0.0f);
    ASSERT_EQ((*distance_matrix)[RailwayStation::KV][RailwayStation::KV], 0.0f);
    ASSERT_EQ((*distance_matrix)[RailwayStation::LH][RailwayStation::LH], 0.0f);
    ASSERT_EQ((*distance_matrix)[RailwayStation::OV][RailwayStation::OV], 0.0f);
    ASSERT_EQ((*distance_matrix)[RailwayStation::OL][RailwayStation::OL], 0.0f);
    ASSERT_EQ((*distance_matrix)[RailwayStation::RI][RailwayStation::RI], 0.0f);
    ASSERT_EQ((*distance_matrix)[RailwayStation::PSL][RailwayStation::PSL], 0.0f);
    ASSERT_EQ((*distance_matrix)[RailwayStation::PM][RailwayStation::PM], 0.0f);
    ASSERT_EQ((*distance_matrix)[RailwayStation::SK][RailwayStation::SK], 0.0f);
    ASSERT_EQ((*distance_matrix)[RailwayStation::TPE][RailwayStation::TPE], 0.0f);
    ASSERT_EQ((*distance_matrix)[RailwayStation::TL][RailwayStation::TL], 0.0f);
    ASSERT_EQ((*distance_matrix)[RailwayStation::TKU][RailwayStation::TKU], 0.0f);
    ASSERT_EQ((*distance_matrix)[RailwayStation::YV][RailwayStation::YV], 0.0f);

    // timetable 1.

    // Turku-Pasila, 191.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::TKU][RailwayStation::PSL], 191.0f);

    // Pasila-Turku, 191.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::PSL][RailwayStation::TKU], 191.0f);

    // timetable 7.

    // Oulu-Ylivieska, 122.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::OL][RailwayStation::YV], 122.0f);

    // Oulu-Ylivieska, 122.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::YV][RailwayStation::OL], 122.0f);

    // Oulu-Seinäjoki, 333.0 km.
    // NOTE: this is from timetable 7 in the direction of Helsinki-Kemijärvi. In other direction it is 334 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::OL][RailwayStation::SK], 333.0f);

    // Seinäjoki-Oulu, 333.0 km.
    // NOTE: this is from timetable 7 in the direction of Helsinki-Kemijärvi. In other direction it is 334 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::SK][RailwayStation::OL], 333.0f);

    // Oulu-Tampere, 493.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::OL][RailwayStation::TPE], 493.0f);

    // Tampere-Oulu, 493.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::TPE][RailwayStation::OL], 493.0f);

    // Oulu-Pasila, 677.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::OL][RailwayStation::PSL], 677.0f);

    // Pasila-Oulu, 677.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::PSL][RailwayStation::OL], 677.0f);

    // Ylivieska-Tampere, 371.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::YV][RailwayStation::TPE], 371.0f);

    // Tampere-Ylivieska, 371.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::TPE][RailwayStation::YV], 371.0f);

    // Seinäjoki-Tampere, 160.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::SK][RailwayStation::TPE], 160.0f);

    // Tampere-Seinäjoki, 160.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::TPE][RailwayStation::SK], 160.0f);

    // Tampere-Toijala, 40.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::TPE][RailwayStation::TL], 40.0f);

    // Toijala-Tampere, 40.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::TL][RailwayStation::TPE], 40.0f);

    // Tampere-Riihimäki, 116.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::TPE][RailwayStation::RI], 116.0f);

    // Riihimäki-Tampere, 116.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::RI][RailwayStation::TPE], 116.0f);

    // Toijala-Riihimäki, 76.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::TL][RailwayStation::RI], 76.0f);

    // Riihimäki-Toijala, 76.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::RI][RailwayStation::TL], 76.0f);

    // timetable 9.

    // Joensuu-Pieksämäki, 183.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::JNS][RailwayStation::PM], 183.0f);

    // Pieksämäki-Joensuu, 183.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::PM][RailwayStation::JNS], 183.0f);

    // Joensuu-Tampere via Pieksämäki, 418.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::JNS][RailwayStation::TPE], 418.0f);

    // Tampere-Joensuu via Pieksämäki, 418.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::TPE][RailwayStation::JNS], 418.0f);

    // Joensuu-Turku via Pieksämäki, 586.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::JNS][RailwayStation::TKU], 586.0f);

    // Turku-Joensuu via Pieksämäki, 586.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::TKU][RailwayStation::JNS], 586.0f);

    // Pieksämäki-Tampere, 235.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::PM][RailwayStation::TPE], 235.0f);

    // Tampere-Pieksämäki, 235.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::TPE][RailwayStation::PM], 235.0f);

    // Tampere-Turku, 168.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::TPE][RailwayStation::TKU], 168.0f);

    // Turku-Tampere, 168.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::TKU][RailwayStation::TPE], 168.0f);

    // timetable 11.

    // Tampere-Haapamäki via Orivesi, 114.0 km.
    // NOTE: Tampere-Haapamäki via Seinäjoki is 160.0 km + 118.0 km = 278.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::TPE][RailwayStation::HPK], 114.0f);

    // Haapamäki-Tampere via Orivesi, 114.0 km.
    // NOTE: Haapamäki-Tampere via Seinäjoki is 118.0 + 160.0 km km = 278.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::HPK][RailwayStation::TPE], 114.0f);

    // Jyväskylä-Seinäjoki via Haapamäki, 196.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::JY][RailwayStation::SK], 196.0f);

    // Seinäjoki-Jyväskylä via Haapamäki, 196.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::SK][RailwayStation::JY], 196.0f);

    // timetable 12A.

    // Lahti-Riihimäki, 59.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::LH][RailwayStation::RI], 59.0f);

    // Riihimäki-Lahti, 59.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::RI][RailwayStation::LH], 59.0f);

    // timetable 13.

    // Oulu-Iisalmi via Kontiomäki, 275.0 km.
    // NOTE: Oulu-Iisalmi via Ylivieska is 122.0 km + 154.0 km = 276.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::OL][RailwayStation::ILM], 275.0f);

    // Iisalmi-Oulu via Kontiomäki, 275.0 km.
    // NOTE: Iisalmi-Oulu via Ylivieska is 154.0 km + 122.0 km = 276.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::ILM][RailwayStation::OL], 275.0f);

    // Oulu-Pieksämäki via Kontiomäki, 449.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::OL][RailwayStation::PM], 449.0f);

    // Pieksämäki-Oulu via Kontiomäki, 449.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::PM][RailwayStation::OL], 449.0f);

    // Oulu-Kouvola via Kontiomäki, 633.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::OL][RailwayStation::KV], 633.0f);

    // Kouvola-Oulu via Kontiomäki, 633.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::KV][RailwayStation::OL], 633.0f);

    // Iisalmi-Pieksämäki, 174.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::ILM][RailwayStation::PM], 174.0f);

    // Pieksämäki-Iisalmi, 174.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::ILM][RailwayStation::PM], 174.0f);

    // Kouvola-Lahti, 62.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::KV][RailwayStation::LH], 62.0f);

    // Lahti-Kouvola, 62.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::LH][RailwayStation::KV], 62.0f);

    // timetable 14.

    // Joensuu-Lahti, 378.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::JNS][RailwayStation::LH], 378.0f);

    // Lahti-Joensuu, 378.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::LH][RailwayStation::JNS], 378.0f);

    // Joensuu-Pasila, 479.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::JNS][RailwayStation::PSL], 479.0f);

    // Pasila-Joensuu, 479.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::PSL][RailwayStation::JNS], 479.0f);

    // combined timetables.

    // Pieksämäki-Seinäjoki via Jyväskylä and Haapamäki, 276.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::PM][RailwayStation::SK], 276.0f);

    // Seinäjoki-Pieksämäki via Haapamäki and Jyväskylä, 276.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::SK][RailwayStation::PM], 276.0f);

    // Oulu-Joensuu via Kontiomäki and Pieksämäki, 632.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::OL][RailwayStation::JNS], 632.0f);

    // Joensuu-Oulu via Pieksämäki and Kontiomäki, 632.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::JNS][RailwayStation::OL], 632.0f);

    // Iisalmi-Seinäjoki via Ylivieska, 365.0 km.
    // NOTE: Iisalmi-Seinäjoki via Pieksämäki, Jyväskylä, and Haapamäki is 174.0 km + 80.0 km + 196.0 km = 450.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::ILM][RailwayStation::SK], 365.0f);

    // Seinäjoki-Iisalmi via Ylivieska, 365.0 km.
    // NOTE: Seinäjoki-Iisalmi via Haapamäki, Jyväskylä, and Pieksämäki is 196.0 km + 80.0 km + 174.0 km = 450.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::SK][RailwayStation::ILM], 365.0f);

    // Joensuu-Seinäjoki via Pieksämäki and Jyväskylä, 459.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::JNS][RailwayStation::SK], 459.0f);

    // Seinäjoki-Joensuu via Jyväskylä and Pieksämäki, 459.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::SK][RailwayStation::JNS], 459.0f);

    // Iisalmi-Tampere via Pieksämäki, 409.0 km.
    // NOTE: Iisalmi-Tampere via Ylivieska and Seinäjoki is 154.0 km + 371.0 km = 525.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::ILM][RailwayStation::TPE], 409.0f);

    // Tampere-Iisalmi via Pieksämäki, 409.0 km.
    // NOTE: Tampere-Iisalmi via Seinäjoki and Ylivieska is 371.0 km + 154.0 km = 525.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::TPE][RailwayStation::ILM], 409.0f);

    // Iisalmi-Turku via Pieksämäki, 577.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::ILM][RailwayStation::TKU], 577.0f);

    // Turku-Iisalmi via Pieksämäki, 577.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::TKU][RailwayStation::ILM], 577.0f);

    // Joensuu-Riihimäki via Kouvola and Lahti, 437.0 km.
    // NOTE: Joensuu-Riihimäki via Pieksämäki and Tampere is 418.0 km + 116.0 km = 534.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::JNS][RailwayStation::RI], 437.0f);

    // Riihimäki-Joensuu via Lahti and Kouvola, 437.0 km.
    // NOTE: Riihimäki-Joensuu via Tampere and Pieksämäki is 116.0 km + 418.0 km = 534.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::RI][RailwayStation::JNS], 437.0f);

    // Joensuu-Toijala via Kouvola and Lahti, 458.0 km.
    // NOTE: Joensuu-Toijala via Lahti and Riihmäki is 378.0 km + 59.0 km + 76.0 km = 513.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::JNS][RailwayStation::TL], 458.0f);

    // Toijala-Joensuu via Lahti and Kouvola, 458.0 km.
    // NOTE: Toijala-Joensuu via Riihmäki and Lahti is 76.0 km + 59.0 km + 378.0 km = 513.0 km.
    ASSERT_EQ((*distance_matrix)[RailwayStation::JNS][RailwayStation::TL], 458.0f);
}
