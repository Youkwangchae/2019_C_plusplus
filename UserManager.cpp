#include "UserManager.h"

UserManager::UserManager()
{
	conn = mysql_init(NULL);
	mysql_options(conn, MYSQL_SET_CHARSET_NAME, "euckr"); //한글깨짐
	bool error = mysql_real_connect(conn, "localhost", "root", "java", "mydb", 5306, NULL, 0);
	if (!error)
	{
		cout << "디비접속에러" << endl;
	}
	else {
		cout << "접속 성공" << endl;
	}
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
		cout << row[0] << " " << row[1] << " " << row[2] << " " << row[3] << endl;


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

		user.setAll(str[0], str[1], str[2], score);
		//이거 주석 풀면 오류나서 해결하는 중 
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
		string query = "insert into user(id, pwd, email, score) values ('";
		query += _id;
		query += "', '" + _pwd;
		query += "', '" + _email;
		query += "', '" + to_string(_score);
		query += "');";
		int query_status = mysql_query(conn,query.c_str());
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
	cout << "아이디 찾기 : 1" << endl;
	cout << "비밀번호 찾기 : 2" << endl;
	int input;
	cin >> input;
	switch (input)
	{
	case 1:
	{
		system("cls");
		cout << "<아이디 찾기>" << endl;
		cout << "email을 입력하세요 : ";
		string email;
		cin >> email;
		string query = "select * from user where email='" + email + "'";
		int query_status = mysql_query(conn, query.c_str());
		if (query_status != 0) {
			return;
		}
		m_res = mysql_store_result(conn);
		row = mysql_fetch_row(m_res);
		lengths = mysql_fetch_lengths(m_res);
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
		cout << "<비밀번호 찾기>" << endl;
		cout << "아이디를 입력하세요 : ";
		string id;
		cin >> id;
		cout << "email을 입력하세요 : ";
		string email;
		cin >> email;
		string query = "select * from user where id='" + id + "'and email='" + email + "'";
		int query_status = mysql_query(conn, query.c_str());
		if (query_status != 0) {
			return;
		}
		m_res = mysql_store_result(conn);
		row = mysql_fetch_row(m_res);
		lengths = mysql_fetch_lengths(m_res);

		if (row == NULL){
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
	for (User u : userList)
	{
		u.getUserInfo();
	}
}

bool UserManager::isIDExist(string _id, string _email)
{
	string query = "select * from user where id='" + _id + "'or email='" + _email + "'";
	int query_status = mysql_query(conn, query.c_str());
	if (query_status != 0) {
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
	string query = "select * from user where id='" + _id + "'and pwd='" + _pwd + "'";
	int query_status = mysql_query(conn, query.c_str());
	if (query_status != 0) {
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
					cout << "<로그인>" << endl;
					cout << "ID를 입력하세요 : ";
					cin >> id;
					cout << "PassWord를 입력하세요 : ";
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
					cout << "<회원 가입>" << endl;
					cout << "ID를 입력하세요 : ";
					cin >> id;
					cout << "PassWord를 입력하세요 : ";
					cin >> pwd;
					cout << "이메일을 입력하세요 : ";
					cin >> email;
					system("cls");
					join(id, pwd, email, 0);
					Sleep(500);
					system("cls");
				}

				break;
			}
			case 10: {
				system("cls");
				find();
				system("pause");
				system("cls");

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