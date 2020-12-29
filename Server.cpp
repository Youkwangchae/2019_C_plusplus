#include "Server.h"

Server::Server()
{

}

void Server::serverInit()
{
	WSAStartup(MAKEWORD(2, 2), &wsaData);	//생성자 개념
	hListen = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);	//IPV4 타입을 사용,  연결지향형 소켓, TCP
	tListenAddr.sin_family = AF_INET;
	tListenAddr.sin_port = htons(PORT);	//htons : host to network short
	tListenAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(hListen, (SOCKADDR*)& tListenAddr, sizeof(tListenAddr));
	cout << "클라이언트 연결 대기중" << endl;
	listen(hListen, SOMAXCONN);	//클라이언트 접속 요청 받는 큐 생성
	int iClntSize = sizeof(tClntAddr);
	hClient = accept(hListen, (SOCKADDR*)& tClntAddr, &iClntSize);	//큐에서 요청 꺼내면서 수락
}

void Server::recvMsg(string& str, string msg)
{
	char cBuffer[PACKET_SIZE] = {};
	char cMsg[PACKET_SIZE];
	int error = recv(hClient, cBuffer, PACKET_SIZE, 0);
	//클라이언트로부터 값을 받아 cBuffer에 저장
	//cout << error << endl;
	//printf("Recv Msg : %s\n", cBuffer);
	if (error == -1)
	{
		system("cls");
		gotoxy(0, 0);
		SetColor(WHITE);
		cout << "client 연결 종료" << endl;
		exit(0);
	}
	str = string(cBuffer);
	strcpy(cMsg, msg.c_str());
	send(hClient, cMsg, strlen(cMsg), 0);
	//클라이언트에게 나의 점수를 문자열의 형태로 확인응답
}

void Server::serverClose()
{
	closesocket(hClient);
	closesocket(hListen);



	WSACleanup();	//소멸자
}
