//#include "myDls.h"
//#include<iostream>
//using namespace std;
//
//int main()
//{
//	mysql_init(&m_MySql);
//
//	if (mysql_real_connect(&m_MySql, DB_ADDRESS, DB_ID, DB_PASS, DB_NAME, 3306, NULL, 0) == NULL)
//	{ // 디비 접속
//		cout << "db 접속 실패" << endl;
//		return 0;
//	}
//
//	//strQuery.Format(_T("SELECT id FROM user WHERE id ='%s' "), _T("CL"));
//
//	//if (mysql_query(&m_MySql, CStringA(strQuery))) // 쿼리 요청
//	//{
//	//	AfxMessageBox(_T("쿼리 에러"));
//	//	return;
//	//}
//
//	//if ((m_Res = mysql_store_result(&m_MySql)) == NULL) // 결과를 m_Res에 저장
//	//{
//	//	return;
//	//}
//	//row = mysql_fetch_row(m_Res); //m_Res의 값을 row로 저장해서 하나씩 갖고 오기
//
//
//	//mysql_free_result(m_Res); // m_Res 삭제
//	//mysql_close(&m_MySql); // m_MySql 삭제
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
	cout << "클라이언트 프로그램" << endl;
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
		cout << "서버로 전송할 문자열을 입력하세요 : ";
		cin >> cMsg;
		send(hSocket, cMsg, strlen(cMsg), 0);
		char cBuffer[PACKET_SIZE] = {};

		recv(hSocket, cBuffer, PACKET_SIZE, 0);
		printf("Recv Msg : %s\n", cBuffer);
	}

	closesocket(hSocket);

	WSACleanup();


}