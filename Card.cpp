#include "Card.h"
#include "my.h"
void Card::setX(int _x)
{
	x = _x;
}

void Card::setY(int _y)
{
	y = _y;
}

int Card::getX()
{
	return x;
}

int Card::getY()
{
	return y;
}

bool Card::getMatched()
{
	return matched;
}

void Card::setMatched(bool _matched)
{
	matched = _matched;
}

string Card::getShape()
{
	return shape;
}

void Card::setShape(string _shape)
{
	shape = _shape;
}

ostream & operator<<(ostream & out, Card & card)
{

	//TODO: 여기에 반환 구문을 삽입합니다.
	//getMatched가 1이면 모양을 출력한다.
	//getMatched가 0이면 네모를 출력한다.

	if (card.getMatched())//뒤집혀져 있는 카드
	{

		SetColor(9);
		gotoxy(card.getX() - 1, card.getY() - 2);
		cout << "┏━━━━━━━━┓";

		gotoxy(card.getX() - 1, card.getY() - 1);
		cout << "┃        ┃";

		gotoxy(card.getX() - 1, card.getY());
		cout << "┃";
		cout.setf(ios::left);
		cout << setw(8) << card.getShape();
		cout << "┃";

		gotoxy(card.getX() - 1, card.getY() + 1);
		cout << "┃        ┃";;

		gotoxy(card.getX() - 1, card.getY() + 2);
		cout << "┗━━━━━━━━┛";

		SetColor(8);
	}
	else//아직 뒤집히지 않는 카드
	{
		gotoxy(card.getX() - 1, card.getY() - 2);
		cout << "┏━━━━━━━━┓";

		gotoxy(card.getX() - 1, card.getY() - 1);
		cout << "┃        ┃";

		gotoxy(card.getX() - 1, card.getY());
		cout << "┃        ┃";

		gotoxy(card.getX() - 1, card.getY() + 1);
		cout << "┃        ┃";;

		gotoxy(card.getX() - 1, card.getY() + 2);
		cout << "┗━━━━━━━━┛";
	}

	return out;
}