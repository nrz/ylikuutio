#include <asio.hpp>

// Include standard headers
#include <iostream> // std::cout, std::cerr
#include <string>   // std::string
#include <vector>   // std::vector

int main(int argc, char* argv[])
{
    std::vector<std::string> arg_vector;

    if (argc > 1)
    {
        arg_vector.assign(argv + 1, argv + argc);

        // Print command line arguments (without the executable name string).
        for (std::string argument : arg_vector)
        {
            std::cout << argument << "\n";
        }
    }
    else
    {
        std::cout << "no command line arguments.\n";
        std::cout << "usage: asio_nslookup <server>:<port>\n";
        std::cout << "or\n";
        std::cout << "usage: asio_nslookup <server> <port>\n";
        return -1;
    }

    // Create the `asio::io_service`.
    asio::io_service my_io_service;

    // Resolve a domain name.
    asio::ip::tcp::resolver resolver(my_io_service);
    asio::ip::tcp::resolver::query query(arg_vector[0], "http");
    asio::ip::tcp::resolver::iterator it = resolver.resolve(query);
    asio::ip::tcp::resolver::iterator end;

    while (it != end)
    {
        asio::ip::tcp::endpoint my_endpoint = *it++;
        std::cout << my_endpoint << "\n";
    }

    return 0;
}
