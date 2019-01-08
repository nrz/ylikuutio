#include "tcp_server.hpp"

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
        void TcpServer::start_accept()
        {
            std::shared_ptr<TcpConnection> new_connection = TcpConnection::create(acceptor_.get_io_service());
            acceptor_.async_accept(
                    new_connection->socket(),
                    std::bind(&TcpServer::handle_accept, this, new_connection, std::placeholders::_1));
        }

        void TcpServer::handle_accept(std::shared_ptr<TcpConnection> new_connection, const asio::error_code& error)
        {
            if (!error)
            {
                new_connection->start();
            }

            start_accept();
        }
    }
}
