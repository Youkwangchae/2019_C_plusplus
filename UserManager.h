#pragma once
#include<string>
#include<mysql.h>
#include<iostream>
#include<list>
#include"User.h"
#include"totalHead.h"
using namespace std;
#pragma comment(lib, "libmariadb.lib")
class UserManager
{
private:
	MYSQL* conn;
	MYSQL_RES* m_res;
	MYSQL_ROW row;
	char buffer[20];
	unsigned long* lengths;
public:
	User user;

	UserManager();
	void printDB();
	bool login(string _id, string _pwd);
	void join(string _id, string _pwd, string _email, int _score);
	void find();
	void rank();
	bool greater(User u1, User u2);
	bool isUserExist(string _id, string _pwd);
	bool isIDExist(string _id, string _email);
	void setCursorView(bool visible);
	void membership();
};

