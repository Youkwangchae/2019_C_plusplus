#include "mysql.h"
#include <WinSock2.h>
#pragma comment(lib,"libmysql.lib")
#pragma comment(lib,"ws2_32.lib")

#define DB_ADDRESS "localhost"
#define DB_ID "root"
#define DB_PASS "�������"
#define DB_NAME "����"

/****  mysql ������ �߰��Ѵ�.  ****/
extern MYSQL_ROW row;  // mysql �� ���� �ô´�.
extern MYSQL_RES *m_res; // mysql�� ����� �޾ƿ´�
extern MYSQL mysql;  // mysql�� ��ü���� ������ ����Ѵ�.

MYSQL m_MySql;
MYSQL_RES* m_Res;
MYSQL_ROW row;







