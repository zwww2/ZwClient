// Подключение библиотек
#include <stdio.h>
#include <WS2tcpip.h>
#include <iostream>

// Указываем библиотеку линкеру
#pragma comment(lib, "Ws2_32.lib")



// Точка входа в приложение (здесь начинается выполнение программы)
int main(void)
{


	// Инициализация библиотеки сокетов


	WSADATA wData;
	int result = WSAStartup(MAKEWORD(2, 2), &wData);
	if (result == SOCKET_ERROR) return -1;

	// Инициализация сокета
	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);

	sockaddr_in socketInfo;
	RtlZeroMemory(&socketInfo, sizeof(socketInfo));

	socketInfo.sin_family = AF_INET;
	socketInfo.sin_port = htons(8737);
	in_addr ip;
	result = inet_pton(AF_INET, "127.0.0.1", &ip);
	if (result == SOCKET_ERROR) return -1;
	socketInfo.sin_addr = ip;


	result = connect(clientSocket, (const sockaddr*)&socketInfo, sizeof(socketInfo));
	if (result == SOCKET_ERROR) return -1;

	char buffersend[512]; 
	char bufferrecv[512];
	while (1)
	{
		std::cout << "\n";
		RtlZeroMemory(buffersend, 512);
		std::cin >> buffersend;

		send(clientSocket, buffersend, 512, 0);

		RtlZeroMemory(bufferrecv, 512);

		recv(clientSocket, bufferrecv, 512, 0);
		std::cout << "Server send: " << bufferrecv;
	}

}