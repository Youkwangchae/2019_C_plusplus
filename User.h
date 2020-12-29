#pragma once
#include<iostream>
#include<string>
using namespace std;

class User
{
private:
	string pwd, id, email;
	int score;
public:
	User();
	User(string _id, string _pwd, string _email, int _score);
	string getId();
	string getPwd();
	string getEmail();
	int getScore();
	void getUserInfo();
	void setID(string _id);
	void setPwd(string _pwd);
	void setEmail(string _email);
	void setScore(int _score);
	void setAll(string _id, string _pwd, string _email, int _score);
	bool operator<(User& copy);
};

