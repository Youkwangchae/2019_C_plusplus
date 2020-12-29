#include "UserManager.h"
#include<Windows.h>
UserManager::UserManager()
{
	conn = mysql_init(NULL);
	mysql_options(conn, MYSQL_SET_CHARSET_NAME, "euckr"); //한글깨짐
	bool error = mysql_real_connect(conn, "localhost", "root", "java", "mydb", 5306, NULL, 0);
	/*if (!error)
	{
		cout << "디비접속에러" << endl;
	}
	else {
		cout << "접속 성공" << endl;
	}*/
}

void UserManager::printDB()
{
	int query_status = mysql_query(conn, "select * from user");
	if (query_status != 0) {
		cout << "질의문 오류!!" << endl;
		return;
	}
	m_res = mysql_store_result(conn);
	while ((row = mysql_fetch_row(m_res)) != NULL) {
		cout << row[0] << "," << row[1] << "," << row[2] << "," << row[3] << endl;
	}
	mysql_free_result(m_res);
}

bool UserManager::login(string _id, string _pwd)
{
	if (isUserExist(_id, _pwd))
	{
		//cout << row[0] << " " << row[1] << " " << row[2] << " " << row[3] <<endl;
		
		
		char str[3][50];
		//pwd, email;
		int score;
		for (int i = 0; i < 3; i++)
		{
			if (lengths[i] != 0)
			{
				memcpy(buffer, row[i], lengths[i]);
				buffer[lengths[i]] = 0;
				sscanf(row[i], "%s", &(str[i]));
			}
		}
		if (lengths[3] != 0)
		{
			memcpy(buffer, row[3], lengths[3]);
			buffer[lengths[3]] = 0;
			sscanf(row[3], "%d", &score);
		}
		user.setAll(str[0], str[1], str[2], 0);
		//이거 썅 주석 풀면 오류나서 해결하는 중 
		cout << "로그인 성공" << endl;
		return true;
	}
	else
	{
		cout << "로그인 실패" << endl;
		return false;
	}
		
}

void UserManager::join(string _id, string _pwd, string _email, int _score)
{
	if (!isIDExist(_id, _email))
	{
		string query = "insert into user values ('";
		query += _id;
		query += "','" + _pwd;
		query += "','" + _email;
		query += "','" + to_string(_score);
		query += "')";
		//cout << query << endl;
		int query_status = mysql_query(conn, query.c_str());
		if (query_status != 0) {
			cout << "질의 오류" << endl;
			return;
		}
		cout << "회원 가입 성공" << endl;
	}
	else
	{
		cout << "아이디 또는 이메일이 이미 존재합니다." << endl;
	}
}

void UserManager::find()
{

	gotoxy(15, 8);
	//=========================오류 수정=========================
	cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓";
	gotoxy(15, 9);
	cout << "┃*****************************┃";
	gotoxy(15, 10);
	cout << "┃*                           *┃";
	gotoxy(15, 11);
	cout << "┃*                           *┃";
	gotoxy(15, 12);
	cout << "┃*                           *┃";
	gotoxy(15, 13);
	cout << "┃*****************************┃";
	gotoxy(15, 14);
	cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛";
	gotoxy(24, 7);
	cout << "< 회원가입 >" << endl;
	gotoxy(20, 10);
	cout << "아이디 찾기   : 1";
	
	gotoxy(20, 11);
	cout << "비밀번호 찾기 : 2" << endl;
	int input;
	gotoxy(17, 12);
	cout << " 1 또는 2를 입력하세요 : ";
	cin >> input;
	switch (input)
	{
	case 1:
	{
		system("cls");
		gotoxy(15, 8);
		//=========================오류 수정=========================
		cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓";
		gotoxy(15, 9);
		cout << "┃**************************┃";
		gotoxy(15, 10);
		cout << "┃*                        *┃";
		gotoxy(15, 11);
		cout << "┃*                        *┃";
		gotoxy(15, 12);
		cout << "┃**************************┃";
		gotoxy(15, 13);
		cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛";
		gotoxy(23, 7);
		cout << "<아이디 찾기>" << endl;
		gotoxy(19, 10);
		cout << "email을 입력하세요";
		string email;
		gotoxy(18, 11);
		cin >> email;
		
		
		string query = "select * from user where email='" + email + "'";
		int query_status = mysql_query(conn, query.c_str());
		if (query_status != 0) {
			//cout << "질의문 오류!!" << endl;
			return;
		}
		m_res = mysql_store_result(conn);
		row = mysql_fetch_row(m_res);
		lengths = mysql_fetch_lengths(m_res);

		gotoxy(18, 15);
		if (row == NULL)
		{
			mysql_free_result(m_res);
			cout << "등록되지 않은 이메일입니다." << endl;
			return;
		}
		else
		{
			char ID[50];
			if (lengths[0] != 0)
			{
				memcpy(buffer, row[0], lengths[0]);
				buffer[lengths[0]] = 0;
				sscanf(row[0], "%s", &ID);
			}
			mysql_free_result(m_res);
			cout << "사용자의 아이디는 " << ID << "입니다." << endl;

			return;
		}
	}
		return;
	case 2:
		system("cls");
		gotoxy(15, 8);
		//=========================오류 수정=========================
		cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓";
		gotoxy(15, 9);
		cout << "┃**************************┃";
		gotoxy(15, 10);
		cout << "┃*                        *┃";
		gotoxy(15, 11);
		cout << "┃*                        *┃";
		gotoxy(15, 12);
		cout << "┃**************************┃";
		gotoxy(15, 13);
		cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛";
		gotoxy(23, 7);
		cout << "<비밀번호 찾기>" << endl;
		gotoxy(19, 10);
		cout << "아이디를 입력하세요! ";
		string id;
		
		gotoxy(18, 11);
		cin >> id;
		gotoxy(15, 11);
		cout << "┃*                        *┃";
		gotoxy(19, 10);
		cout << "email을 입력하세요!";
		string email;
		gotoxy(18, 11);
		cin >> email;

		string query = "select * from user where id='" + id + "'and email='" + email + "'";
		int query_status = mysql_query(conn, query.c_str());
		if (query_status != 0) {
			cout << "질의문 오류!!" << endl;
			return;
		}
		m_res = mysql_store_result(conn);
		row = mysql_fetch_row(m_res);
		lengths = mysql_fetch_lengths(m_res);

		gotoxy(18, 15);
		if (row == NULL)
		{
			mysql_free_result(m_res);
			cout << "존재하지 않는 사용자 정보입니다." << endl;
			return;
		}
		else
		{
			char PWD[50];
			if (lengths[1] != 0)
			{
				memcpy(buffer, row[1], lengths[1]);
				buffer[lengths[1]] = 0;
				sscanf(row[1], "%s", &PWD);
			}
			mysql_free_result(m_res);
			cout << "사용자의 비밀번호는 " << PWD << "입니다." << endl;

			return;
		}
		return;
	
	}
}

void UserManager::rank()
{
	list<User> userList;
	int query_status = mysql_query(conn, "select * from user");
	if (query_status != 0) {
		cout << "질의문 오류!!" << endl;
		return;
	}
	
	m_res = mysql_store_result(conn);
	while ((row = mysql_fetch_row(m_res)) != NULL) {
		lengths = mysql_fetch_lengths(m_res);
		char str[3][50];
		int score;
		for (int i = 0; i < 3; i++)
		{
			if (lengths[i] != 0)
			{
				memcpy(buffer, row[i], lengths[i]);
				buffer[lengths[i]] = 0;
				sscanf(row[i], "%s", &(str[i]));
			}
		}
		if (lengths[3] != 0)
		{
			memcpy(buffer, row[3], lengths[3]);
			buffer[lengths[3]] = 0;
			sscanf(row[3], "%d", &score);
		}
		userList.push_back(User(str[0], str[1], str[2], score));
	}
	mysql_free_result(m_res);
	userList.sort();
	system("cls");
	gotoxy(7, 8);
	//=========================오류 수정=========================
	cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓";
	gotoxy(7, 9);
	cout << "┃****************************************************┃";
	gotoxy(7, 10);
	cout << "┃*                                                  *┃";
	gotoxy(7, 11);
	cout << "┃*                                                  *┃";
	gotoxy(7, 12);
	cout << "┃*                                                  *┃";
	gotoxy(7, 13);
	cout << "┃*                                                  *┃";
	gotoxy(7, 14);
	cout << "┃*                                                  *┃";
	gotoxy(7, 15);
	cout << "┃****************************************************┃";
	gotoxy(7, 16);
	cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛";
	gotoxy(27, 7);
	cout << "< Top 5 >" << endl;

	int i = 0;
	for (User u : userList)
	{
		gotoxy(10, 10 + i);
		cout.setf(ios::left);
		cout << i+1 << "등 | 아이디 : " << setw(10)<<u.getId() << "\t 점수 : " << u.getScore();
		if (i == 4)	break;
		i++;
	}
	gotoxy(10, 18);
}

void UserManager::setDBScore(int _Tscore)
{
	string email, id, pwd;
	user.getUserInfo(id, pwd, email);
	string query = "update user set score='" + to_string(_Tscore) + "' where id='" + id+"' ";
	
	int query_status = mysql_query(conn, query.c_str());
	/*if (query_status != 0) {
		cout << "질의문 오류!!" << endl;
		return;
	}
	else
	{
		cout << "질의문 성공!!" << endl;
	}*/
}


bool UserManager::isIDExist(string _id, string _email)
{
	string query = "select * from user where id='" + _id + "'or email='" + _email + "'";
	//
	//cout << query << endl;
	int query_status = mysql_query(conn, query.c_str());
	if (query_status != 0) {
		//cout << "질의문 오류!!" << endl;
		return false;
	}
	m_res = mysql_store_result(conn);

	if ((row = mysql_fetch_row(m_res)) == NULL)
	{
		mysql_free_result(m_res);
		return false;
	}
	else
	{
		mysql_free_result(m_res);
		return true;
	}
}

bool UserManager::isUserExist(string _id, string _pwd)
{
	string query = "select * from user where id='" + _id + "'and pwd='"+_pwd+"'";
	//cout << query << endl;
	int query_status = mysql_query(conn, query.c_str());
	if (query_status != 0) {
		//cout << "질의문 오류!!" << endl;
		return false;
	}	
	m_res = mysql_store_result(conn);
	row = mysql_fetch_row(m_res);
	lengths = mysql_fetch_lengths(m_res);
	if (row == NULL)
	{
		mysql_free_result(m_res);
		return false;
	}
	else
	{
		mysql_free_result(m_res);
		return true;
	}
		
	
}

void UserManager::membership()
{
	setCursorView(false);
	int x = 12, y = 8;
	while (true) {

		SetColor(GRAY);
		gotoxy(10, 7);
		cout << ("┏━━━━━━━━━< LOG IN >━━━━━━━━━┓");
		Sleep(10);
		gotoxy(10, 8);
		cout << ("┃ 1. 기존 정보로 로그인하기  ┃");
		Sleep(10);
		gotoxy(10, 9);
		cout << ("┃ 2. 회원 가입하기           ┃");
		Sleep(10);
		gotoxy(10, 10);
		cout << ("┃ 3. ID / PW 찾기            ┃");
		Sleep(10);
		gotoxy(10, 11);
		cout << ("┃ 4. 순위 보기               ┃");
		Sleep(10);
		gotoxy(10, 12);
		cout << ("┃ 5. 게임 나가기             ┃");
		Sleep(10);
		gotoxy(10, 13);
		cout << ("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");


		if (y < 8) //주어진 선택지 외로 빠져나가지 않게 함
			y = 12;
		if (y > 12)
			y = 8;

		gotoxy(x, y);
		SetColor(GRAY);
		cout << "▶";
		switch (_getch()) {
		case 224:
		{
			switch (_getch()) { //13이 엔터
			case 72:y -= 1;
				//cout << "위" << endl;
				break;   //위
			case 80:y += 1;
				///cout << "아래" << endl;
				break;//아래
			}
			cout << "\b" << " ";
			break;
		}
		case 13: //enter;
		   //break; 해도 못나감.         
			switch (y) {
			case 8: {
				system("cls");
				//cout << "1번 메뉴" << endl;
				{
					string id, pwd;
					gotoxy(15, 8);
					//=========================오류 수정=========================
					cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓";
					gotoxy(15, 9);
					cout << "┃**************************┃";
					gotoxy(15, 10);
					cout << "┃*                        *┃";
					gotoxy(15, 11);
					cout << "┃*                        *┃";
					gotoxy(15, 12);
					cout << "┃**************************┃";
					gotoxy(15, 13);
					cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛";
					gotoxy(25, 7);
					cout << "< 로그인 >" << endl;
					gotoxy(22, 10);
					cout << "ID를 입력하세요 ";
					gotoxy(20, 11);
					cin >> id;
					gotoxy(20, 11);
					cout << "             ";
					gotoxy(20, 10);
					cout << "PassWord를 입력하세요";
					gotoxy(20, 11);
					cin >> pwd;
					system("cls");
					if (login(id, pwd))
					{
						Sleep(500);
						system("cls");
						return;
					}
					else
					{
						Sleep(500);
						system("cls");
						break;
					}
				}
			}
			case 9: {
				system("cls");
				{
					string id, pwd, email;
					gotoxy(15, 8);
					//=========================오류 수정=========================
					cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓";
					gotoxy(15, 9);
					cout << "┃**************************┃";
					gotoxy(15, 10);
					cout << "┃*                        *┃";
					gotoxy(15, 11);
					cout << "┃*                        *┃";
					gotoxy(15, 12);
					cout << "┃**************************┃";
					gotoxy(15, 13);
					cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛";
					gotoxy(24, 7);
					cout << "< 회원가입 >" << endl;

					gotoxy(22, 10);
					cout << "ID를 입력하세요 ";
					gotoxy(20, 11);
					cin >> id;
					gotoxy(20, 11);
					cout << "             ";
					gotoxy(20, 10);
					cout << "PassWord를 입력하세요";
					gotoxy(20, 11);
					cin >> pwd;
					gotoxy(20, 11);
					cout << "             ";
					gotoxy(20, 10);
					cout << "이메일을 입력하세요  ";
					gotoxy(20, 11);
					cin >> email;
					system("cls");
					join(id, pwd, email, 0);
					Sleep(500);
					system("cls");
				}
				
				//cout << "2번 메뉴" << endl;
				break;
			}
			case 10: {
				system("cls");

				find();
				gotoxy(18, 16);
				system("pause");
				system("cls");
				//cout << "3번 메뉴" << endl;

				break;
			}
			case 11: {
				system("cls");
				rank();
				system("pause");
				system("cls");
				break;
			}
			case 12: {
				cout << "게임을 종료합니다." << endl;
				exit(0);
			}
			default: {
				cout << "다시 입력해주십시오" << endl;
				break;
			}
			}
		}
	}
}

void UserManager::setCursorView(bool visible)
{
	CONSOLE_CURSOR_INFO cursor = { 1, visible };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}