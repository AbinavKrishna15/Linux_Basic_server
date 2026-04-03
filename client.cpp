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
    int sock_fd;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family=AF_INET;
    hints.ai_socktype=SOCK_STREAM;
    if(getaddrinfo("127.0.0.1", "8080", &hints, &res)!=0)
    {
        perror("failed");
        return -1;
    }
    sock_fd = socket(res-> ai_family, res->ai_socktype, res-> ai_protocol);
    if(sock_fd<0)
    {
        perror("Socket failed");
        return -1;
    }
    if(connect(sock_fd, res-> ai_addr, res-> ai_addrlen )<0)
    {
        perror("Connect failed");
        return -1;
    }
    cout<<"CONNECTED TO SERVER \n";
    const char* message = " Hello Server";
    send(sock_fd, message, strlen(message), 0);
    close(sock_fd);
    freeaddrinfo(res);
    return 0;
}
