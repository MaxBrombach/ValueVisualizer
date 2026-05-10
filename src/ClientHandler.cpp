#include <netinet/in.h>
#include <unistd.h>
#include <array>
#include "ClientHandler.hpp"


void ClientHandler::handleClient(int iClientfd)
{
    std::array<char, MESSAGE_SIZE> acMessage; 
    while (true)
    {
        int iBytes = recv(iClientfd, acMessage.data(), acMessage.size(), 0);
       
        if (iBytes > 0)
        {

        }
        else if(iBytes == 0)
        {
            //Disconnect
        }
    }
    
}