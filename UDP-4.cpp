#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 32

int main(int argc, char *argv[])
{
    int server_sockfd;
    int len;
    struct sockaddr_in my_addr;
    char buf[BUFFER_SIZE];
    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = INADDR_ANY;
    my_addr.sin_port = htons(10000);
    if ((server_sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
    {
        std::cout <<"socket error"<<std::endl;
        return 1;
    }
    if (bind(server_sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) < 0)
    {
        std::cout <<"bind error"<<std::endl;
        return 1;
    }
    while (1)
    {
        if ((len = recvfrom(server_sockfd, buf, BUFFER_SIZE, 0, NULL, NULL)) < 0)
        {
            std::cout <<"recvfrom error"<<std::endl;
            return 1;
        }
        buf[len] = '\0';
        std::cout <<"contents: "<<buf<<std::endl;
        if (buf[0] == 'a')
        {
            std::cout <<"auto"<<std::endl;
            //自动
        }
        else if (buf[0] == 'm')
        {
            std::cout <<"manual"<<std::endl;
            //手动
        }
        else if (buf[0] == 'o')
        {
            std::cout <<"open"<<std::endl;
            //开
        }
        else if (buf[0] == 'c')
        {
            std::cout <<"close"<<std::endl;
            //关
        }
    }
    close(server_sockfd);
    return 0;
}
