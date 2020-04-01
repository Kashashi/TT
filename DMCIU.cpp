#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <winsock2.h>
///需要連結libwsock32.a

#pragma comment(lib, "ws2_32.lib")
/******************
    伺服器終端
******************/

int main(int argc, char *argv[])
{
    WSADATA wsaData;//WSAStartup用來初始化winsock的DLL庫，執行成功後返回0，失敗後則返回socket_error
    WORD sockVersion = MAKEWORD(2,2);//建立兩個位元組的word格式 設定socket版本為2
    if(WSAStartup(sockVersion, &wsaData) != 0)
    {
        return 0;
    }

    SOCKET serSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);//預設2 2 17
    if(serSocket == INVALID_SOCKET)
    {
        printf("連接錯誤!!!");
        return 0;
    }

    sockaddr_in serAddr;//建立連接
    serAddr.sin_family = AF_INET;
    #ifdef DEBUG
    serAddr.sin_port = htons(8888);//使用的連接埠端口
    #else
    printf("輸入要使用的連接埠號碼:");

    u_short port_number;
    std::cin >> port_number;//輸入所需使用的連接埠端口整數號碼
    serAddr.sin_port = htons(port_number);//使用的連接埠端口
    #endif // DEBUG
    serAddr.sin_addr.S_un.S_addr = INADDR_ANY;
    if(bind(serSocket, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
    {
        printf("綑綁錯誤!!!");
        closesocket(serSocket);
        return 0;
    }

    sockaddr_in remoteAddr;
    int nAddrLen = sizeof(remoteAddr);
    while (true)
    {
        char recvData[255];
        int ret = recvfrom(serSocket, recvData, 255, 0, (sockaddr *)&remoteAddr, &nAddrLen);
        if (ret > 0)
        {
            recvData[ret] = 0x00;
            printf("接收到一個連接：%s \r\n", inet_ntoa(remoteAddr.sin_addr));
            printf(recvData);
        }

        const char *sendData = "來自伺服器終端的UDP封包\n";
        sendto(serSocket, sendData, strlen(sendData), 0, (sockaddr *)&remoteAddr, nAddrLen);

    }
    closesocket(serSocket);
    WSACleanup();
    return 0;
}
