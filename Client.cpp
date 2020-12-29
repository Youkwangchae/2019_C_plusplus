#include "Client.h"
#include<string>
Client::Client()
{
}

void Client::clientInit()
{
	cout << "서버의 IP 주소를 입력하세요 : ";
	string ip;
	cin >> ip;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	hSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	tAddr.sin_family = AF_INET;
	tAddr.sin_port = htons(PORT);
	tAddr.sin_addr.s_addr = inet_addr(ip.c_str());
	int temp;
	cout << "서버 연결 대기중";
	int count = 0;
	do {		  
		temp = connect(hSocket, (SOCKADDR*)& tAddr, sizeof(tAddr));
		count++;
		if (count == 40)
			break;
	} while (temp == -1);
	system("cls");
	if (temp == -1)
	{
		cout << "서버 연결 안됨" << endl;
		exit(0);
	}
}

void Client::sendMsg(string cMsg, string& rcv)
{
	//cout << "서버로 전송할 문자열을 입력하세요 : ";
	send(hSocket, cMsg.c_str(), strlen(cMsg.c_str()), 0);
	char cBuffer[PACKET_SIZE] = {};

	int temp = recv(hSocket, cBuffer, PACKET_SIZE, 0);
	if (temp == -1)
	{
		clientClose();
		exit(0);
	}
	rcv = string(cBuffer);
	if(rcv == "-1")
		system("cls");
	//printf("Recv Msg : %s\n", cBuffer);
}

void Client::clientClose()
{
	closesocket(hSocket);
	WSACleanup();
}

string Client::convertToString(char * a, int size)
{

	int i;
	string s = "";
	for (i = 0; i < size; i++) {
		s = s + a[i];
	}
	return s;
}
