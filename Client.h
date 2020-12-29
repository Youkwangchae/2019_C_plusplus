#pragma once
#include<stdio.h>
#include<WinSock.h>
#include<iostream>
using namespace std;
#define PACKET_SIZE 1024
#define SERVER_IP "192.168.67.192"
#define PORT 4578



#pragma comment(lib, "ws2_32")

class Client
{

private:
	WSADATA wsaData;
	SOCKET hSocket;
	SOCKADDR_IN tAddr = {};
public:
	Client();
	void clientInit();
	void sendMsg(string cMsg, string& rcv);
	void clientClose();
	string convertToString(char* a, int size);
};
