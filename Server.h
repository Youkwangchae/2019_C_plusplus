#pragma once
#include<WinSock2.h>
#include"totalHead.h"
#include<string>
#include<iostream>
#define PORT 4578
#define PACKET_SIZE 1024
#pragma comment(lib, "ws2_32")
#pragma warning(disable:4996)
using namespace std;
class Server
{
private:
	WSADATA wsaData;
	SOCKET hListen;
	SOCKADDR_IN tListenAddr = {};
	SOCKADDR_IN tClntAddr = {};
	SOCKET hClient;
public:

	Server();

	void serverInit();
	void recvMsg(string& str, string msg);
	void serverClose();
};

