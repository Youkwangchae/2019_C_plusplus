#include "Server.h"

Server::Server()
{

}

void Server::serverInit()
{
	WSAStartup(MAKEWORD(2, 2), &wsaData);	//������ ����
	hListen = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);	//IPV4 Ÿ���� ���,  ���������� ����, TCP
	tListenAddr.sin_family = AF_INET;
	tListenAddr.sin_port = htons(PORT);	//htons : host to network short
	tListenAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(hListen, (SOCKADDR*)& tListenAddr, sizeof(tListenAddr));
	cout << "Ŭ���̾�Ʈ ���� �����" << endl;
	listen(hListen, SOMAXCONN);	//Ŭ���̾�Ʈ ���� ��û �޴� ť ����
	int iClntSize = sizeof(tClntAddr);
	hClient = accept(hListen, (SOCKADDR*)& tClntAddr, &iClntSize);	//ť���� ��û �����鼭 ����
}

void Server::recvMsg(string& str, string msg)
{
	char cBuffer[PACKET_SIZE] = {};
	char cMsg[PACKET_SIZE];
	int error = recv(hClient, cBuffer, PACKET_SIZE, 0);
	//Ŭ���̾�Ʈ�κ��� ���� �޾� cBuffer�� ����
	//cout << error << endl;
	//printf("Recv Msg : %s\n", cBuffer);
	if (error == -1)
	{
		system("cls");
		gotoxy(0, 0);
		SetColor(WHITE);
		cout << "client ���� ����" << endl;
		exit(0);
	}
	str = string(cBuffer);
	strcpy(cMsg, msg.c_str());
	send(hClient, cMsg, strlen(cMsg), 0);
	//Ŭ���̾�Ʈ���� ���� ������ ���ڿ��� ���·� Ȯ������
}

void Server::serverClose()
{
	closesocket(hClient);
	closesocket(hListen);



	WSACleanup();	//�Ҹ���
}
