#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<unistd.h>
#include<iostream>
#include<cstring>
using namespace std;
int main()
{
    struct addrinfo hints, *res;
    int server_fd, new_socket;
    char buffer[1024];
    memset(&hints, 0, sizeof(hints));
    hints.ai_family=AF_INET;
    hints.ai_socktype=SOCK_STREAM;
    hints.ai_flags=AI_PASSIVE;

    if(getaddrinfo(NULL, "8080", &hints, &res)!=0)
    {
        perror("failed");
        return -1;
    }
    server_fd = socket(res-> ai_family, res->ai_socktype, res-> ai_protocol);
    if(server_fd<0)
    {
        perror("Socket failed");
        return -1;
    }
    if(bind(server_fd, res->ai_addr, res->ai_addrlen)<0)
    {
        perror("Bind failed");
        return -1;
    }
    if(listen(server_fd, 5)<0)
    {
        perror("Listen failed");
    }
    cout<<"Listening\n";
    struct sockaddr_storage client_addr;
    socklen_t addr_size = sizeof(client_addr);
    new_socket=accept(server_fd, (struct sockaddr*)&client_addr, &addr_size);
    if(new_socket < 0 )
    {
        perror("accept failed");
        return -1;
    }
    cout<<"connected\n";
    memset(buffer, 0 , sizeof(buffer));
    int bytes = recv(new_socket, buffer ,sizeof(buffer), 0 );
    cout<<"Message recieved is :" << buffer << "\n";
    close(new_socket);
    close(server_fd);
    freeaddrinfo(res);
}
