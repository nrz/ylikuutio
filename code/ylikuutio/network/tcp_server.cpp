// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
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
