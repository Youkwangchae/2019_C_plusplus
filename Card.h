#pragma once
#include"my.h"

class Card
{
private:
	int x;
	int y;
	bool matched = false;
	string shape;
public:
	void setX(int _x);
	void setY(int _y);
	int getX();
	int getY();
	bool getMatched();
	void setMatched(bool _matched);
	string getShape();
	void setShape(string _shape);
	friend ostream& operator<<(ostream& out, Card& card);
};

