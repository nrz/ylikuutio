#include <asio.hpp>
#include <asio/error_code.hpp>

// Include standard headers
#include <chrono>   // std::chrono::nanoseconds/microseconds/milliseconds/seconds/minutes/hours
#include <iostream> // std::cout, std::cin, std::cerr
#include <string>   // std::string
#include <thread>   // std::thread, std::this_thread::sleep_for, std::this_thread::sleep_until
#include <vector>   // std::vector

// based on http://think-async.com/Asio/asio-1.10.6/doc/asio/tutorial/tutdaytime2.html

std::string make_string(asio::streambuf& streambuf)
{
    return { asio::buffers_begin(streambuf.data()), asio::buffers_end(streambuf.data()) };
}

int main(int argc, char* argv[])
{
    try
    {
        std::vector<std::string> arg_vector;

        if (argc <= 1)
        {
            std::cout << "no command line arguments.\n";
            std::cout << "usage: asio_chat_server <server> <port>\n";
            return -1;
        }
        else if (argc == 2)
        {
            std::cout << "only 1 command line argument.\n";
            std::cout << "usage: asio_chat_server <server> <port>\n";
            return -1;
        }
        else
        {
            arg_vector.assign(argv + 1, argv + argc);

            // Print command line arguments (without the executable name string).
            for (std::string argument : arg_vector)
            {
                std::cout << argument << "\n";
            }
        }

        int port = std::stoi(arg_vector[1]);
        std::cout << "Port: " << port << "\n";

        // Create the `asio::io_service`.
        asio::io_service my_io_service;
        asio::ip::tcp::acceptor my_acceptor(my_io_service, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port));

        while (true)
        {
            asio::ip::tcp::socket my_socket(my_io_service);
            my_acceptor.accept(my_socket);

            // Read from keyboard.
            std::string my_message;
            std::cout << "Your message: ";
            std::cin >> my_message;

            // Write.
            try
            {
                asio::streambuf write_buffer;
                std::ostream output_stream(&write_buffer);
                output_stream << my_message;
                std::cout << "Your message: ";
                std::cout << "Sent......... " << make_string(write_buffer) << "\n";
                asio::write(my_socket, write_buffer);
            }
            catch (std::exception& my_exception)
            {
                std::cerr << my_exception.what() << "\n";
            }

            // Wait before reading.
            std::chrono::milliseconds default_polling_interval(100);
            std::this_thread::sleep_for(default_polling_interval);

            // Read.
            asio::error_code my_error_code;
            try
            {
                asio::streambuf read_buffer;
                auto bytes_transferred = asio::read_until(my_socket, read_buffer, '\n', my_error_code);
                read_buffer.commit(bytes_transferred);
                std::cout << "Received..... " << make_string(read_buffer) << "\n";
                read_buffer.consume(bytes_transferred); // Flush the buffer.
            }
            catch (std::exception& my_exception)
            {
                std::cerr << my_exception.what() << "\n";
            }

            if (my_error_code == asio::error::eof)
            {
                std::cerr << "Error: EOF\n";
            }
            else if (my_error_code)
            {
                std::cerr << "Error: " << my_error_code.message() << "\n";
            }
        }

        return 0;
    }
    catch (std::exception& my_exception)
    {
        std::cerr << my_exception.what() << "\n";
    }
}
