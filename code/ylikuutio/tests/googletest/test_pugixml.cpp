#include "gtest/gtest.h"

// Include pugixml
#include "pugixml.hpp"
#include "pugixml.cpp"

// Include standard headers
#include <cstring>  // std::memcmp, std::strcmp, std::strlen, std::strncmp
#include <iostream> // std::cout, std::cin, std::cerr

TEST(xml_must_be_loaded_as_expected, exactum_and_physicum)
{
    const char* const exactum_physicum_osm_char = "Exactum_Physicum_Helsinki_Finland.osm";
    pugi::xml_document doc;
    const pugi::xml_parse_result result = doc.load_file(exactum_physicum_osm_char);
    const pugi::xml_node osm = doc.child("osm");

    const pugi::xpath_node_set restaurants = doc.select_nodes("/osm/node/tag[@v='Unicafe']");

    uint32_t n_restaurants = 0;
    for (pugi::xpath_node_set::const_iterator it = restaurants.begin(); it != restaurants.end(); ++it)
    {
        n_restaurants++;
    }

    std::cout << "Number of restaurants: " << n_restaurants << "\n";
    ASSERT_EQ(n_restaurants, 2);

    pugi::xpath_node exactum_tag = doc.select_node("/osm/way/tag[@k='name' and @v='Exactum']");
    ASSERT_TRUE(exactum_tag != nullptr);
    const pugi::xml_node exactum_way = exactum_tag.parent();
    ASSERT_TRUE(exactum_way != nullptr);
    ASSERT_EQ(strcmp(exactum_way.attribute("id").value(), "16790295"), 0);
}

TEST(xml_must_be_loaded_as_expected, hofinkatu_and_isafjordinkatu)
{
    const char* hofinkatu_and_isafjordinkatu_osm_char = "Hofinkatu_Isafjordinkatu_Joensuu_Finland.osm";
    pugi::xml_document doc;
    const pugi::xml_parse_result result = doc.load_file(hofinkatu_and_isafjordinkatu_osm_char);

    const pugi::xpath_node_set buildings = doc.select_nodes("/osm/way/tag[@k='building']");

    uint32_t n_buildings = 0;
    for (pugi::xpath_node_set::const_iterator it = buildings.begin(); it != buildings.end(); ++it)
    {
        n_buildings++;
    }

    std::cout << "Number of buildings: " << n_buildings << "\n";
    ASSERT_EQ(n_buildings, 85);

    const pugi::xpath_node playground_tag = doc.select_node("/osm/way/tag[@k='leisure' and @v='playground']");
    ASSERT_TRUE(playground_tag != nullptr);
    const pugi::xml_node playground_way = playground_tag.parent();
    ASSERT_TRUE(playground_way != nullptr);
    ASSERT_EQ(strcmp(playground_way.attribute("id").value(), "435869079"), 0);
}
