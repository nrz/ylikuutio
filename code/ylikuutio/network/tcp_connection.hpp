
#include <asio.hpp>

// Include standard headers
#include <memory> // std::make_shared, std::shared_ptr
#include <string> // std::string

// based on http://think-async.com/Asio/asio-1.10.6/doc/asio/tutorial/tutdaytime3.html

namespace network
{
    // class TcpConnection: public std::shared_ptr<TcpConnection>
    class TcpConnection
    {
        public:
            TcpConnection(asio::io_context& io_context)
                : socket_(io_context)
            {
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
