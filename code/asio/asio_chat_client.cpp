#include <asio.hpp>
#include <asio/error_code.hpp>

// Include standard headers
#include <chrono>   // std::chrono::nanoseconds/microseconds/milliseconds/seconds/minutes/hours
#include <iostream> // std::cout, std::cin, std::cerr
#include <string>   // std::string
#include <vector>   // std::vector

// based on http://think-async.com/Asio/asio-1.10.6/doc/asio/tutorial/tutdaytime1.html

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
            std::cout << "usage: asio_chat_client <server> <port>\n";
            return -1;
        }
        else if (argc == 2)
        {
            std::cout << "only 1 command line argument.\n";
            std::cout << "usage: asio_chat_client <server> <port>\n";
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

        // Create the `asio::io_service`.
        asio::io_service my_io_service;

        // Resolve a domain name.
        asio::ip::tcp::resolver resolver(my_io_service);
        asio::ip::tcp::resolver::query query(arg_vector[0], arg_vector[1]);
        asio::ip::tcp::resolver::iterator it = resolver.resolve(query);
        asio::ip::tcp::resolver::iterator end;

        // OK, domain name is now resolved, try connecting to each endpoint one by one.
        asio::ip::tcp::socket my_socket(my_io_service);
        asio::error_code my_error_code = asio::error::host_not_found;

        while (my_error_code && it != end)
        {
            asio::ip::tcp::endpoint my_endpoint = *it++;
            std::cout << "Endpoint: " << my_endpoint << "\n";

            my_socket.close();
            my_socket.connect(my_endpoint);
        }

        if (my_error_code)
        {
            std::cerr << "Error: " << my_error_code.message() << "\n";
        }

        while (true)
        {
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
