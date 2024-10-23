#include "http_server.h"
#include "request_handler.h"
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

void startServer() {
    try {
        boost::asio::io_context io_context;

        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8080));
        std::cout << "Server running on port 8080..." << std::endl;

        while (true) {
            tcp::socket socket(io_context);
            acceptor.accept(socket);
            handleRequest(std::move(socket));
        }
    } catch (std::exception& e) {
        std::cerr << "Exception in server: " << e.what() << "\n";
    }
}
