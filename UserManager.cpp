#include "UserManager.h"
#include<Windows.h>
UserManager::UserManager()
{
	conn = mysql_init(NULL);
	mysql_options(conn, MYSQL_SET_CHARSET_NAME, "euckr"); //�ѱ۱���
	bool error = mysql_real_connect(conn, "localhost", "root", "java", "mydb", 5306, NULL, 0);
	/*if (!error)
	{
		cout << "������ӿ���" << endl;
	}
	else {
		cout << "���� ����" << endl;
	}*/
}

void UserManager::printDB()
{
	int query_status = mysql_query(conn, "select * from user");
	if (query_status != 0) {
		cout << "���ǹ� ����!!" << endl;
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
		//�̰� �� �ּ� Ǯ�� �������� �ذ��ϴ� �� 
		cout << "�α��� ����" << endl;
		return true;
	}
	else
	{
		cout << "�α��� ����" << endl;
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
			cout << "���� ����" << endl;
			return;
		}
		cout << "ȸ�� ���� ����" << endl;
	}
	else
	{
		cout << "���̵� �Ǵ� �̸����� �̹� �����մϴ�." << endl;
	}
}

void UserManager::find()
{

	gotoxy(15, 8);
	//=========================���� ����=========================
	cout << "��������������������������������������������������������������";
	gotoxy(15, 9);
	cout << "��*****************************��";
	gotoxy(15, 10);
	cout << "��*                           *��";
	gotoxy(15, 11);
	cout << "��*                           *��";
	gotoxy(15, 12);
	cout << "��*                           *��";
	gotoxy(15, 13);
	cout << "��*****************************��";
	gotoxy(15, 14);
	cout << "��������������������������������������������������������������";
	gotoxy(24, 7);
	cout << "< ȸ������ >" << endl;
	gotoxy(20, 10);
	cout << "���̵� ã��   : 1";
	
	gotoxy(20, 11);
	cout << "��й�ȣ ã�� : 2" << endl;
	int input;
	gotoxy(17, 12);
	cout << " 1 �Ǵ� 2�� �Է��ϼ��� : ";
	cin >> input;
	switch (input)
	{
	case 1:
	{
		system("cls");
		gotoxy(15, 8);
		//=========================���� ����=========================
		cout << "��������������������������������������������������������";
		gotoxy(15, 9);
		cout << "��**************************��";
		gotoxy(15, 10);
		cout << "��*                        *��";
		gotoxy(15, 11);
		cout << "��*                        *��";
		gotoxy(15, 12);
		cout << "��**************************��";
		gotoxy(15, 13);
		cout << "��������������������������������������������������������";
		gotoxy(23, 7);
		cout << "<���̵� ã��>" << endl;
		gotoxy(19, 10);
		cout << "email�� �Է��ϼ���";
		string email;
		gotoxy(18, 11);
		cin >> email;
		
		
		string query = "select * from user where email='" + email + "'";
		int query_status = mysql_query(conn, query.c_str());
		if (query_status != 0) {
			//cout << "���ǹ� ����!!" << endl;
			return;
		}
		m_res = mysql_store_result(conn);
		row = mysql_fetch_row(m_res);
		lengths = mysql_fetch_lengths(m_res);

		gotoxy(18, 15);
		if (row == NULL)
		{
			mysql_free_result(m_res);
			cout << "��ϵ��� ���� �̸����Դϴ�." << endl;
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
			cout << "������� ���̵�� " << ID << "�Դϴ�." << endl;

			return;
		}
	}
		return;
	case 2:
		system("cls");
		gotoxy(15, 8);
		//=========================���� ����=========================
		cout << "��������������������������������������������������������";
		gotoxy(15, 9);
		cout << "��**************************��";
		gotoxy(15, 10);
		cout << "��*                        *��";
		gotoxy(15, 11);
		cout << "��*                        *��";
		gotoxy(15, 12);
		cout << "��**************************��";
		gotoxy(15, 13);
		cout << "��������������������������������������������������������";
		gotoxy(23, 7);
		cout << "<��й�ȣ ã��>" << endl;
		gotoxy(19, 10);
		cout << "���̵� �Է��ϼ���! ";
		string id;
		
		gotoxy(18, 11);
		cin >> id;
		gotoxy(15, 11);
		cout << "��*                        *��";
		gotoxy(19, 10);
		cout << "email�� �Է��ϼ���!";
		string email;
		gotoxy(18, 11);
		cin >> email;

		string query = "select * from user where id='" + id + "'and email='" + email + "'";
		int query_status = mysql_query(conn, query.c_str());
		if (query_status != 0) {
			cout << "���ǹ� ����!!" << endl;
			return;
		}
		m_res = mysql_store_result(conn);
		row = mysql_fetch_row(m_res);
		lengths = mysql_fetch_lengths(m_res);

		gotoxy(18, 15);
		if (row == NULL)
		{
			mysql_free_result(m_res);
			cout << "�������� �ʴ� ����� �����Դϴ�." << endl;
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
			cout << "������� ��й�ȣ�� " << PWD << "�Դϴ�." << endl;

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
		cout << "���ǹ� ����!!" << endl;
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
	//=========================���� ����=========================
	cout << "������������������������������������������������������������������������������������������������������������";
	gotoxy(7, 9);
	cout << "��****************************************************��";
	gotoxy(7, 10);
	cout << "��*                                                  *��";
	gotoxy(7, 11);
	cout << "��*                                                  *��";
	gotoxy(7, 12);
	cout << "��*                                                  *��";
	gotoxy(7, 13);
	cout << "��*                                                  *��";
	gotoxy(7, 14);
	cout << "��*                                                  *��";
	gotoxy(7, 15);
	cout << "��****************************************************��";
	gotoxy(7, 16);
	cout << "������������������������������������������������������������������������������������������������������������";
	gotoxy(27, 7);
	cout << "< Top 5 >" << endl;

	int i = 0;
	for (User u : userList)
	{
		gotoxy(10, 10 + i);
		cout.setf(ios::left);
		cout << i+1 << "�� | ���̵� : " << setw(10)<<u.getId() << "\t ���� : " << u.getScore();
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
		cout << "���ǹ� ����!!" << endl;
		return;
	}
	else
	{
		cout << "���ǹ� ����!!" << endl;
	}*/
}


bool UserManager::isIDExist(string _id, string _email)
{
	string query = "select * from user where id='" + _id + "'or email='" + _email + "'";
	//
	//cout << query << endl;
	int query_status = mysql_query(conn, query.c_str());
	if (query_status != 0) {
		//cout << "���ǹ� ����!!" << endl;
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
		//cout << "���ǹ� ����!!" << endl;
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
		cout << ("��������������������< LOG IN >��������������������");
		Sleep(10);
		gotoxy(10, 8);
		cout << ("�� 1. ���� ������ �α����ϱ�  ��");
		Sleep(10);
		gotoxy(10, 9);
		cout << ("�� 2. ȸ�� �����ϱ�           ��");
		Sleep(10);
		gotoxy(10, 10);
		cout << ("�� 3. ID / PW ã��            ��");
		Sleep(10);
		gotoxy(10, 11);
		cout << ("�� 4. ���� ����               ��");
		Sleep(10);
		gotoxy(10, 12);
		cout << ("�� 5. ���� ������             ��");
		Sleep(10);
		gotoxy(10, 13);
		cout << ("������������������������������������������������������������");


		if (y < 8) //�־��� ������ �ܷ� ���������� �ʰ� ��
			y = 12;
		if (y > 12)
			y = 8;

		gotoxy(x, y);
		SetColor(GRAY);
		cout << "��";
		switch (_getch()) {
		case 224:
		{
			switch (_getch()) { //13�� ����
			case 72:y -= 1;
				//cout << "��" << endl;
				break;   //��
			case 80:y += 1;
				///cout << "�Ʒ�" << endl;
				break;//�Ʒ�
			}
			cout << "\b" << " ";
			break;
		}
		case 13: //enter;
		   //break; �ص� ������.         
			switch (y) {
			case 8: {
				system("cls");
				//cout << "1�� �޴�" << endl;
				{
					string id, pwd;
					gotoxy(15, 8);
					//=========================���� ����=========================
					cout << "��������������������������������������������������������";
					gotoxy(15, 9);
					cout << "��**************************��";
					gotoxy(15, 10);
					cout << "��*                        *��";
					gotoxy(15, 11);
					cout << "��*                        *��";
					gotoxy(15, 12);
					cout << "��**************************��";
					gotoxy(15, 13);
					cout << "��������������������������������������������������������";
					gotoxy(25, 7);
					cout << "< �α��� >" << endl;
					gotoxy(22, 10);
					cout << "ID�� �Է��ϼ��� ";
					gotoxy(20, 11);
					cin >> id;
					gotoxy(20, 11);
					cout << "             ";
					gotoxy(20, 10);
					cout << "PassWord�� �Է��ϼ���";
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
					//=========================���� ����=========================
					cout << "��������������������������������������������������������";
					gotoxy(15, 9);
					cout << "��**************************��";
					gotoxy(15, 10);
					cout << "��*                        *��";
					gotoxy(15, 11);
					cout << "��*                        *��";
					gotoxy(15, 12);
					cout << "��**************************��";
					gotoxy(15, 13);
					cout << "��������������������������������������������������������";
					gotoxy(24, 7);
					cout << "< ȸ������ >" << endl;

					gotoxy(22, 10);
					cout << "ID�� �Է��ϼ��� ";
					gotoxy(20, 11);
					cin >> id;
					gotoxy(20, 11);
					cout << "             ";
					gotoxy(20, 10);
					cout << "PassWord�� �Է��ϼ���";
					gotoxy(20, 11);
					cin >> pwd;
					gotoxy(20, 11);
					cout << "             ";
					gotoxy(20, 10);
					cout << "�̸����� �Է��ϼ���  ";
					gotoxy(20, 11);
					cin >> email;
					system("cls");
					join(id, pwd, email, 0);
					Sleep(500);
					system("cls");
				}
				
				//cout << "2�� �޴�" << endl;
				break;
			}
			case 10: {
				system("cls");

				find();
				gotoxy(18, 16);
				system("pause");
				system("cls");
				//cout << "3�� �޴�" << endl;

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
				cout << "������ �����մϴ�." << endl;
				exit(0);
			}
			default: {
				cout << "�ٽ� �Է����ֽʽÿ�" << endl;
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