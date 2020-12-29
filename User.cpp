#include "User.h"




User::User()
{
	pwd = "";
	id = "";
	score = 0;
	email = "";
}

User::User(string _id, string _pwd, string _email, int _score)
{
	id = _id;
	pwd = _pwd;
	email = _email;
	score = _score;
	

}

string User::getId()
{
	return id;
}

string User::getPwd()
{
	return pwd;
}

string User::getEmail()
{
	return email;
}

int User::getScore()
{
	return score;
}

void User::getUserInfo(string& _id, string& _pwd, string& _email)
{
	_id = id;
	_pwd = pwd;
	_email = email;
}

void User::getUserInfo()
{
	cout << id << pwd << email << score << endl;
}

void User::setID(string _id)
{
	id = _id;
}

void User::setPwd(string _pwd)
{
	pwd = _pwd;
}

void User::setEmail(string _email)
{
	email = _email;
}

void User::setScore(int _score)
{
	score = _score;
}



void User::setAll(string _id, string _pwd, string _email, int _score)
{
	id = _id;
	pwd = _pwd;
	email = _email;
	score = _score;
}

bool User::operator<(User& copy)
{
	return this->getScore()>copy.getScore();
}



