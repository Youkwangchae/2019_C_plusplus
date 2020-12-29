#include"Server.h"
#include<stdio.h>
#include<WinSock2.h>

#include<iostream>
using namespace std;
#pragma comment(lib, "ws2_32")

#define PORT 4578
#define PACKET_SIZE 1024

WSADATA wsaData;
SOCKET hListen;
SOCKADDR_IN tListenAddr = {};
SOCKADDR_IN tClntAddr = {};
SOCKET hClient;
char cBuffer[PACKET_SIZE] = {};


void serverInit()
{

	WSAStartup(MAKEWORD(2, 2), &wsaData);	//생성자 개념


	hListen = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);	//IPV4 타입을 사용,  연결지향형 소켓, TCP


	tListenAddr.sin_family = AF_INET;
	tListenAddr.sin_port = htons(PORT);	//htons : host to network short
	tListenAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(hListen, (SOCKADDR*)& tListenAddr, sizeof(tListenAddr));

	cout << "클라이언트 연결 대기중" << endl;
	listen(hListen, SOMAXCONN);
	int iClntSize = sizeof(tClntAddr);
	hClient = accept(hListen, (SOCKADDR*)& tClntAddr, &iClntSize);
}
void recvMsg(string& str)
{
	int error = recv(hClient, cBuffer, PACKET_SIZE, 0);
	//printf("Recv Msg : %s\n", cBuffer);
	if (error == -1)
	{
		cout << "client 연결 종료" << endl;
		return;
	}
	str = string(cBuffer);



	char cMsg[] = "Sever Send";
	send(hClient, cMsg, strlen(cMsg), 0);
}
void serverClose()
{
	closesocket(hClient);
	closesocket(hListen);



	WSACleanup();	//소멸자
}