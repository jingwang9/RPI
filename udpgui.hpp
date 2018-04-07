//
//  udpgui.hpp
//  guiudp
//
//  Created by wang jing on 2018/4/7.
//  Copyright © 2018年 wang jing. All rights reserved.
//

#ifndef udpgui_hpp
#define udpgui_hpp

#include <stdio.h>

#define BUFFSIZE 1024

#ifdef _WIN32
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
typedef int socklen_t;
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>

typedef unsigned int SOCKET;
#define INVALID_SOCKET  -1
#define SOCKET_ERROR    -1
#endif

class UdpClient{
public:
    UdpClient();
    ~UdpClient();
    
    int SendMsg(const void *data, unsigned short size,const char *ip, unsigned int port);
    int RecvMsg(void *recv_msg, unsigned int &recv_len,const char *ip, unsigned int port);
    int Close();
private:
    SOCKET m_sock;
    
    char syncBuff[BUFFSIZE];
    bool m_closed;
};

#endif /* udpgui_hpp */
