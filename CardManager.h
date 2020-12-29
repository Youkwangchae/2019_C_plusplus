#pragma once
#include"Card.h"
#include "my.h"
#include "client.h"
using namespace std;

class CardManager : public Card
{
private:
	Card** card_set;
	//char shape_arr[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
	string shape_arr[4][8] = { {"cout", "cin", "std", "���ͷ�", "const", "����", "�ڷ���", "�迭"},
	{"������", "�����ε�", "�����Ҵ�", "����Ʈ", "r-value", "��ü", "��������", "Ŭ����"},
	{"this", "������", "�Ҹ���", "�ʱ�ȭ", "static", "���߻��", "��������", "���"},
	{"������", "�����Լ�", "���ø�", "����", "����", "����Ʈ", "ť", "STL"} };


	int score = 0;//ī����� ����
	int remain_try[4] = { 20, 15, 10, 8 };// ī��¦�� ������ �� �ִ� Ƚ��
	int tried = 0;//����ڰ� ������ ī���� Ƚ��
	int remain;//:remain_try[4]���� �� �ϳ� �޾ƿ��� ����
	int tetrisScore = 0;//��Ʈ�������ӿ��� �޾ƿ��� ����.
	int level;//�������� �ε����� �������� ����

	int index_cnt[4][8] = { 0, };//�ߺ�üũ�� ���� ������ �迭

	int clearScore[4] = { 500, 1000, 1500, 2000 };
	
	int totalScore = 0;//�������� �� ���� ����

public:
	CardManager();
	void showCard();
	void gameStart();
	void inputXY(int& x, int& y, int i);
	~CardManager();


	void showState();//ī������� �ǽð� ������ ������ִ� ���
	void showEndState();//����ڰ� ī����ӿ��� �����⸦ ��� ��������� �ߴ� â
	void assignCard();//ī�� �迭�� ������ �°� �������ִ� �Լ�
	void showAllOver();//���ӿ��� �й��� ���(1. ��Ʈ���� ���ӿ��� �й� 2. ��Ʈ������ ī����� ��� �й�)
	void showWin();//���ӿ��� �¸��� ���
};
