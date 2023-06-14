// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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


#include <asio.hpp>

// Include standard headers
#include <memory> // std::shared_ptr
#include <string> // std::string

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

namespace yli::network
{
    // class TcpConnection: public std::shared_ptr<TcpConnection>
    class TcpConnection final
    {
        public:
            explicit TcpConnection(asio::io_context& io_context)
                : socket_(io_context)
            {
                // constructor.
            }

            static std::shared_ptr<TcpConnection> create(asio::io_context& io_context);
            asio::ip::tcp::socket& socket();
            void start();

        private:
            void handle_write(const asio::error_code&, size_t);
            std::string make_daytime_string();
            asio::ip::tcp::socket socket_;
            std::string message_;
    };

}
