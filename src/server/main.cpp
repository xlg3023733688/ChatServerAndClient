#include "chatserver.hpp"
#include "chatservice.hpp"
#include <iostream>
#include <signal.h>
using namespace std;

void resetHandler(int)
{
    ChatService::instance()->reset();
    exit(0);
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0]
                  << " <ip> <port>" << std::endl;
        return -1;
    }

    signal(SIGINT, resetHandler);

    std::string ip = argv[1];
    uint16_t port = static_cast<uint16_t>(atoi(argv[2]));

    EventLoop loop;
    InetAddress addr(ip, port);

    ChatServer server(&loop, addr, "ChatServer");

    server.start();

    std::cout << "ChatServer started at "
              << ip << ":" << port << std::endl;

    loop.loop();

    return 0;
}