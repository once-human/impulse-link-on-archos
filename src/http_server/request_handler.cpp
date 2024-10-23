#include "request_handler.h"
#include <iostream>
#include <fstream>
#include <boost/asio.hpp>
#include <nlohmann/json.hpp>
#include "../models/notification_model.h"

using boost::asio::ip::tcp;
using json = nlohmann::json;

void handleRequest(tcp::socket socket) {
    try {
        char buffer[1024];
        boost::system::error_code error;
        size_t len = socket.read_some(boost::asio::buffer(buffer), error);

        if (error == boost::asio::error::eof) {
            return; // Connection closed cleanly
        } else if (error) {
            throw boost::system::system_error(error);
        }

        // Create the "My Phone" directory in the Documents folder
        std::string documentsPath = getDocumentsPath();
        std::string myPhoneDir = documentsPath + "/My Phone";
        createDirectory(myPhoneDir);

        // Attempt to parse as JSON for notifications
        try {
            std::string data(buffer, len);
            json j = json::parse(data);
            if (j.contains("notification")) {
                std::string notification = j["notification"];
                displayNotification(notification); // Handle notifications
            } else {
                // Save the file received from the socket
                std::ofstream outFile(myPhoneDir + "/received_file", std::ios::binary);
                outFile.write(buffer, len);
                outFile.close();
            }
        } catch (json::parse_error& e) {
            // Handle as file if JSON parsing fails
            std::ofstream outFile(myPhoneDir + "/received_file", std::ios::binary);
            outFile.write(buffer, len);
            outFile.close();
        }

        // Send response
        std::string response = "HTTP/1.1 200 OK\r\nContent-Length: 0\r\n\r\n";
        boost::asio::write(socket, boost::asio::buffer(response));

    } catch (std::exception& e) {
        std::cerr << "Exception in request handler: " << e.what() << "\n";
    }
}

std::string getDocumentsPath() {
    const char* home = std::getenv("HOME");
    return std::string(home) + "/Documents";
}

void createDirectory(const std::string& path) {
    #ifdef _WIN32
        _mkdir(path.c_str());
    #else
        mkdir(path.c_str(), 0777);
    #endif
}
