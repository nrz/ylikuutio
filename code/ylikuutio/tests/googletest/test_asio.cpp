// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
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
#include <asio.hpp>

TEST(nslookup_must_function_correctly_for_127_0_0_1, nslookup)
{
    // Create the `asio::io_service`.
    asio::io_service my_io_service;

    // Resolve a domain name.
    asio::ip::tcp::resolver resolver(my_io_service);
    asio::ip::tcp::resolver::query query("127.0.0.1", "http");
    asio::ip::tcp::resolver::iterator it = resolver.resolve(query);
    asio::ip::tcp::resolver::iterator end;

    ASSERT_NE(it, end);
    asio::ip::tcp::endpoint my_endpoint = *it++;
    asio::ip::address my_address = my_endpoint.address();
    ASSERT_TRUE(my_address.is_v4());
    ASSERT_FALSE(my_address.is_v6());
    ASSERT_EQ(my_address.to_string(), "127.0.0.1");
    ASSERT_EQ(it, end);
}

TEST(nslookup_must_function_correctly_for_colon_colon_1, nslookup)
{
    // Create the `asio::io_service`.
    asio::io_service my_io_service;

    // Resolve a domain name.
    asio::ip::tcp::resolver resolver(my_io_service);
    asio::ip::tcp::resolver::query query("::1", "http");
    asio::ip::tcp::resolver::iterator it = resolver.resolve(query);
    asio::ip::tcp::resolver::iterator end;

    ASSERT_NE(it, end);
    asio::ip::tcp::endpoint my_endpoint = *it++;
    asio::ip::address my_address = my_endpoint.address();
    ASSERT_TRUE(my_address.is_v6());
    ASSERT_FALSE(my_address.is_v4());
    ASSERT_EQ(my_address.to_string(), "::1");
    ASSERT_EQ(it, end);
}

TEST(nslookup_must_function_correctly_for_localhost, nslookup)
{
    // Create the `asio::io_service`.
    asio::io_service my_io_service;

    // Resolve a domain name.
    asio::ip::tcp::resolver resolver(my_io_service);
    asio::ip::tcp::resolver::query query("localhost", "http");
    asio::ip::tcp::resolver::iterator it = resolver.resolve(query);
    asio::ip::tcp::resolver::iterator end;

    ASSERT_NE(it, end);

    // IPv6 endpoint is `::1`.
    asio::ip::tcp::endpoint ipv6_endpoint = *it++;
    asio::ip::address ipv6_address = ipv6_endpoint.address();
    ASSERT_TRUE(ipv6_address.is_v6());
    ASSERT_FALSE(ipv6_address.is_v4());
    ASSERT_EQ(ipv6_address.to_string(), "::1");

    ASSERT_NE(it, end);

    // IPv4 endpoint is `127.0.0.1`.
    asio::ip::tcp::endpoint ipv4_endpoint = *it++;
    asio::ip::address ipv4_address = ipv4_endpoint.address();
    ASSERT_TRUE(ipv4_address.is_v4());
    ASSERT_FALSE(ipv4_address.is_v6());
    ASSERT_EQ(ipv4_address.to_string(), "127.0.0.1");

    ASSERT_EQ(it, end);
}
