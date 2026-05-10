#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int iServerSocket = socket(AF_INET, SOCK_STREAM,0);
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET; //address familiy
    serverAddress.sin_port = htons(8080); // Port
    serverAddress.sin_addr.s_addr = INADDR_ANY; // adress
    
    bind(iServerSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    listen(iServerSocket, 5);

    while(true)
    {
        int client_fd = accept(iServerSocket, nullptr, nullptr);
        close(client_fd);
    }
    
    return 0;
}
