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

	//TODO: ���⿡ ��ȯ ������ �����մϴ�.
	//getMatched�� 1�̸� ����� ����Ѵ�.
	//getMatched�� 0�̸� �׸� ����Ѵ�.

	if (card.getMatched())//�������� �ִ� ī��
	{

		SetColor(9);
		gotoxy(card.getX() - 1, card.getY() - 2);
		cout << "��������������������";

		gotoxy(card.getX() - 1, card.getY() - 1);
		cout << "��        ��";

		gotoxy(card.getX() - 1, card.getY());
		cout << "��";
		cout.setf(ios::left);
		cout << setw(8) << card.getShape();
		cout << "��";

		gotoxy(card.getX() - 1, card.getY() + 1);
		cout << "��        ��";;

		gotoxy(card.getX() - 1, card.getY() + 2);
		cout << "��������������������";

		SetColor(8);
	}
	else//���� �������� �ʴ� ī��
	{
		gotoxy(card.getX() - 1, card.getY() - 2);
		cout << "��������������������";

		gotoxy(card.getX() - 1, card.getY() - 1);
		cout << "��        ��";

		gotoxy(card.getX() - 1, card.getY());
		cout << "��        ��";

		gotoxy(card.getX() - 1, card.getY() + 1);
		cout << "��        ��";;

		gotoxy(card.getX() - 1, card.getY() + 2);
		cout << "��������������������";
	}

	return out;
}