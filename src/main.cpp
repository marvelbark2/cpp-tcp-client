#include <iostream>
#include <unistd.h>

#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

using namespace std;
using namespace asio;

int main(int argc, char const *argv[])
{
    //Getting errors
    asio::error_code ec;

    //Constances
    const string HOST("127.0.0.1");
    const int PORT(8881);

    //Creating context || Asio object or instance
    io_context context;

    // Make a TCP connection
    ip::tcp::endpoint endpoint(ip::make_address(HOST, ec), PORT);

    // connection
    ip::tcp::socket socket(context);

    socket.connect(endpoint, ec);

    // catching erros 

    if(!ec)
    {
        cout << "Connected" << endl;

        if(socket.is_open()) {
            string request = "Hello World";
            socket.write_some(buffer(request.data(), request.size()), ec);
            usleep(2500);
            size_t bytes = socket.available();
            if(bytes > 0) {
                vector<char> dataReceived(bytes);
                socket.read_some(buffer(dataReceived.data(), dataReceived.size()), ec);

                for(char c = std::begin(dataReceived); c != end(dataReceived); ++c) {
                    cout << c;
                }
            }
        }
    }
        
    else {
        cout << "Error: " << ec.message() << endl;
    }
        
    return 0;
}
