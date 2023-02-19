
// Implementing UDP Client System

#include <iostream>
#include <ws2tcpip.h>
#include <string>
#include <omp.h>

using namespace std;

#pragma comment(lib, "Ws2_32.lib")

int main(int argc, char *argv[])
{

    // Initialize Winsock

    WSADATA wsaData;
    WORD version = MAKEWORD(2, 2);

    int wsok = WSAStartup(version, &wsaData);
    if (wsok != 0)
    {
        cout << "Can't Start Winsock " << wsok << endl;
    }

    // Create a hint structure for server

    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(54000);

    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    // Create socket

    SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);

    // Wait out to the socket

    string v(argv[1]); // get the velocity
    int sendOk = sendto(out, v.c_str(), v.size() + 1, 0, (sockaddr *)&server, sizeof(server));

    if (sendOk == SOCKET_ERROR)
    {
        cout << "Didn't work " << WSAGetLastError() << endl;
    }

    // Close socket

    closesocket(out);

    // Shutdown Winsock

    WSACleanup();
}