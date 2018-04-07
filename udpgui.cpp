

#include "udpgui.hpp"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

UdpClient::UdpClient():m_closed(false)
{
#ifdef _WIN32
    WSADATA wsaData;
    WORD version = MAKEWORD(2, 2);
    int ret = WSAStartup(version, &wsaData);//win sock start up
    if ( ret ) {
        std::cerr << "Initilize winsock error !" << std::endl;
    }
    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
    {
        /* Tell the user that we could not find a usable */
        /* WinSock DLL.                                  */
        printf("Could not find a usable version of Winsock.dll\n");
        WSACleanup();
    }
#endif
    if((this->m_sock = socket(AF_INET,SOCK_DGRAM,0)) <= 0)
    {
        printf("error in socket");
        //return -2;
    }
    struct sockaddr_in my_addr;
    int addr_len;
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(4000);
    my_addr.sin_addr.s_addr = inet_addr("10.85.70.200");
    memset(my_addr.sin_zero , 0, 8);
    addr_len = sizeof(struct sockaddr);
}

UdpClient::~UdpClient()
{
    if(!this->m_closed)
    {
        this->Close();
    }
}

int UdpClient::SendMsg(const void *data, unsigned short size,const char *ip, unsigned int port)
{
    struct sockaddr_in send_addr;
    memset((void *)&send_addr, 0, sizeof(struct sockaddr_in));
    send_addr.sin_family=AF_INET;
    send_addr.sin_addr.s_addr=inet_addr(ip);
    send_addr.sin_port=htons(port);
    int sens_addr_len=sizeof(struct sockaddr_in);
    unsigned int n =  sendto(this->m_sock,(char *)data,size,0,(struct sockaddr*)&send_addr,sens_addr_len);
    return n;
}

int UdpClient::RecvMsg(void *recv_msg, unsigned int &recv_len, const char *ip, unsigned int port)
{
    struct sockaddr_in recv_addr;
    memset((void *)&recv_addr, 0, sizeof(struct sockaddr_in));
    recv_addr.sin_family=AF_INET;
    recv_addr.sin_addr.s_addr=inet_addr(ip);
    recv_addr.sin_port=htons(port);
    int sens_addr_len=sizeof(struct sockaddr_in);
    unsigned int n = 0;
    socklen_t len = sizeof(struct sockaddr_in);
    struct timeval tv;
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(this->m_sock,&readfds);
    tv.tv_sec=1;
    tv.tv_usec=0;
    select(this->m_sock+1,&readfds,NULL,NULL,&tv);
    if(FD_ISSET(this->m_sock,&readfds))
    {
        if((n = recvfrom(this->m_sock,syncBuff,BUFFSIZE, 0 ,(struct sockaddr*)&recv_addr,&len))>=0)
        {
            printf("in time ,left time %ld s ,%d usec\n",tv.tv_sec,tv.tv_usec);
            if(n == 0xffffffff)
            {
                recv_len = 0;
            }
            else
            {
                recv_len = n;
                memcpy(recv_msg, (void *)&syncBuff, recv_len);
            }
        }else
        {
            recv_len = 0;
        }
    }
    else
    {
        printf("timeout ,left time %ld s ,%d usec\n",tv.tv_sec,tv.tv_usec);
        recv_len = 0;
        //memcpy(recv_msg, (void *)syncBuff, 0);
    }
    return recv_len;
}

int UdpClient::Close()
{
#ifdef _WIN32
    int ret = closesocket(this->m_sock);
    WSACleanup();
    return ret;
#else
    return close(m_sock);
#endif // WIN32
    this->m_closed = true;
}
