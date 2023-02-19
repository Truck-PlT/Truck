
// Impelemnting UDP Server System

#include <iostream>
#include <ws2tcpip.h>
#include <omp.h>

using namespace std;

#pragma comment(lib, "Ws2_32.lib")

int main()
{

    // Initialize Winsock

    WSADATA wsaData;
    WORD version = MAKEWORD(2, 2);

    int wsok = WSAStartup(version, &wsaData);
    if (wsok != 0)
    {
        cout << "Can't Start Winsock " << wsok << endl;
        return 0;
    }

    // Bind socket to ip address and port

    SOCKET in = socket(AF_INET, SOCK_DGRAM, 0);
    sockaddr_in serverHint;
    serverHint.sin_addr.S_un.S_addr = ADDR_ANY;
    serverHint.sin_family = AF_INET;
    serverHint.sin_port = htons(54000); // port

    if (bind(in, (sockaddr *)&serverHint, sizeof(serverHint)) == SOCKET_ERROR)
    {
        cout << "Can't bind socket " << WSAGetLastError() << endl;
        return 0;
    }

    sockaddr_in client;
    int clientLenght = sizeof(client);
    ZeroMemory(&client, clientLenght);

    char buf[1024];

    // Enter a loop
    while (true)
    {

        ZeroMemory(buf, 1024);

        // Wait for message

        int bytesIn = recvfrom(in, buf, 1024, 0, (sockaddr *)&client, &clientLenght);
        if (bytesIn == SOCKET_ERROR)
        {
            cout << "Error from client " << WSAGetLastError << endl;
            continue;
        }

        // Display message

        char clientIp[256];
        ZeroMemory(clientIp, 256);

        inet_ntop(AF_INET, &client.sin_addr, clientIp, 256);

        cout << "Message received from " << clientIp << " : " << buf << endl;

        if (bytesIn == 0)
        {
            cout << "Brake!" << endl;
        }
    }

    // Close socket

    closesocket(in);

    // Shutdown Winsock

    WSACleanup();
}