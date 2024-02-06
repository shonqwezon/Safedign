#include "config.h"
#include <boost/asio.hpp>
#include "VolumeOS.h"
#include <iostream>
#include <string>
#include <Windows.h>

using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::endl;

int readData(tcp::socket& socket) {
    boost::asio::streambuf buf;
    boost::asio::read_until(socket, buf, "");
    string data = boost::asio::buffer_cast<const char*>(buf.data());
cout << "Message: " << data << endl;
    return std::stoi(data);
}


int main() {
    //::ShowWindow(::GetConsoleWindow(), SW_HIDE);
    int mode{};
    VolumeOS volumeOS;
    volumeOS.setMinVolume(0.15);
    boost::asio::io_service io_service;
    tcp::socket socket(io_service); //socket creation
    socket.connect(tcp::endpoint(boost::asio::ip::address::from_string(config::host), config::port)); //connection 
cout << "Listened...\n\n";
    for (;;) {
        mode = readData(socket);
        if (mode == config::open) {
            volumeOS.changeVolume(config::OPEN);
cout << "opened\n";
        }
        else if (mode == config::close) {
            volumeOS.changeVolume(config::CLOSED);
cout << "closed\n";
        }
cout << "\n";
    }
    socket.close();
    return 0;
}
