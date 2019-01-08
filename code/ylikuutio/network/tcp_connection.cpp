#include "tcp_connection.hpp"

#include <asio.hpp>

// Include standard headers
#include <memory>        // std::make_shared, std::shared_ptr

// based on http://think-async.com/Asio/asio-1.10.6/doc/asio/tutorial/tutdaytime3.html
//
// server.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2015 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// This file has been modified by Antti Nuortimo.

namespace yli
{
    namespace network
    {
        std::shared_ptr<TcpConnection> TcpConnection::create(asio::io_context& io_context)
        {
            return std::make_shared<TcpConnection>(io_context);
        }

        asio::ip::tcp::socket& TcpConnection::socket()
        {
            return socket_;
        }

        void TcpConnection::start()
        {
            message_ = make_daytime_string();
            // asio::async_write(socket_, asio::buffer(message_),
        }

        std::string TcpConnection::make_daytime_string()
        {
            return "test_daytime_string";
        }
    }
}
