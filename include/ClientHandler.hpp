#pragma once

#include <netinet/in.h>
#include <unistd.h>
#include <array>

constexpr size_t MESSAGE_SIZE = 1024;

class ClientHandler
{  

public:
    ClientHandler();
    void handleClient(int iClientfd);
};