#include "mysql.h"
#include <WinSock2.h>
#pragma comment(lib,"libmysql.lib")
#pragma comment(lib,"ws2_32.lib")

#define DB_ADDRESS "localhost"
#define DB_ID "root"
#define DB_PASS "계정비번"
#define DB_NAME "디비명"

/****  mysql 변수를 추가한다.  ****/
extern MYSQL_ROW row;  // mysql 의 행을 맡는다.
extern MYSQL_RES *m_res; // mysql의 결과를 받아온다
extern MYSQL mysql;  // mysql의 전체적인 연동을 담당한다.

MYSQL m_MySql;
MYSQL_RES* m_Res;
MYSQL_ROW row;







