#include "tcp_connection.hpp"

#include <asio.hpp>

// based on http://think-async.com/Asio/asio-1.10.6/doc/asio/tutorial/tutdaytime3.html

namespace yli
{
    namespace network
    {
        class TcpServer
        {
            public:
                TcpServer(asio::io_context& io_context, int port)
                    : acceptor_(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
                {
                    start_accept();
                }

            private:
                void start_accept();
                void handle_accept(std::shared_ptr<TcpConnection> new_connection, const asio::error_code& error);

                asio::ip::tcp::acceptor acceptor_;
        };
    }
}
