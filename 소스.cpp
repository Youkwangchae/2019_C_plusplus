//#include "myDls.h"
//#include<iostream>
//using namespace std;
//
//int main()
//{
//	mysql_init(&m_MySql);
//
//	if (mysql_real_connect(&m_MySql, DB_ADDRESS, DB_ID, DB_PASS, DB_NAME, 3306, NULL, 0) == NULL)
//	{ // ��� ����
//		cout << "db ���� ����" << endl;
//		return 0;
//	}
//
//	//strQuery.Format(_T("SELECT id FROM user WHERE id ='%s' "), _T("CL"));
//
//	//if (mysql_query(&m_MySql, CStringA(strQuery))) // ���� ��û
//	//{
//	//	AfxMessageBox(_T("���� ����"));
//	//	return;
//	//}
//
//	//if ((m_Res = mysql_store_result(&m_MySql)) == NULL) // ����� m_Res�� ����
//	//{
//	//	return;
//	//}
//	//row = mysql_fetch_row(m_Res); //m_Res�� ���� row�� �����ؼ� �ϳ��� ���� ����
//
//
//	//mysql_free_result(m_Res); // m_Res ����
//	//mysql_close(&m_MySql); // m_MySql ����
//	return 0;
//}
#pragma warning(disable: 4996)
#include<stdio.h>
#include<WinSock2.h>
#include<iostream>
using namespace std;

#pragma comment(lib, "ws2_32")

#define PORT 4578
#define PACKET_SIZE 1024
#define SERVER_IP "192.168.67.87"

int main()
{
	cout << "Ŭ���̾�Ʈ ���α׷�" << endl;
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET hSocket;
	hSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN tAddr = {};
	tAddr.sin_family = AF_INET;
	tAddr.sin_port = htons(PORT);
	tAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

	connect(hSocket, (SOCKADDR*)& tAddr, sizeof(tAddr));

	while (1)
	{
		char cMsg[] = "Client Send";
		cout << "������ ������ ���ڿ��� �Է��ϼ��� : ";
		cin >> cMsg;
		send(hSocket, cMsg, strlen(cMsg), 0);
		char cBuffer[PACKET_SIZE] = {};

		recv(hSocket, cBuffer, PACKET_SIZE, 0);
		printf("Recv Msg : %s\n", cBuffer);
	}

	closesocket(hSocket);

	WSACleanup();


}