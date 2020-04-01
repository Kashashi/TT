#include <stdio.h>
#include <windows.h>
#include <winsock2.h>
///需要連結libwsock32.a

#pragma comment(lib, "ws2_32.lib")
/******************
    使用者終端
******************/

int main(int argc, char* argv[])
{
    WORD socketVersion = MAKEWORD(2,2);//建立兩個位元組的word格式 設定socket版本為2
    WSADATA wsaData;//WSAStartup用來初始化winsock的DLL庫，執行成功後返回0，失敗後則返回socket_error
    if(WSAStartup(socketVersion, &wsaData) != 0)
    {
        return 0;
    }
    SOCKET sclient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(8888);
    sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    int len = sizeof(sin);

    const char * sendData = "來自使用者終端的封包.\n";//要傳送的的資料
    sendto(sclient, sendData, strlen(sendData), 0, (sockaddr *)&sin, len);

    char recvData[255];
    int ret = recvfrom(sclient, recvData, 255, 0, (sockaddr *)&sin, &len);
    if(ret > 0)
    {
        recvData[ret] = 0x00;
        printf(recvData);
    }

    closesocket(sclient);
    WSACleanup();
    return 0;
}
