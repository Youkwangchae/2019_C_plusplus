#pragma once
#include <Windows.h>
#include <string>
class Map
{
	int row,col;
	int** map;//map ���� ���� �迭.
	int** open;//map ���� ���� ���� �迭.
	int bomb,num,check;
	int x, y;
	int count;
public:
	Map();
	~Map();
int Check(int num);//������ �ƴ� �Է� ���� ó��
int Check(char ch);//���ڰ� �ƴ� �Է� ����ó��
int range(int a, int b, int c);//���� ���� �Է� ����ó��.
	void set();//map�� ����, ���� ���� ���� ���.
		int** makeMap();//map ���� ���.
		void hidemap();//map�� ���� ���� ���.
		void setBomb();//���� �� ���� ���.
		void showmap();//map ȭ�� ��� ���.
		void endgame();//�¸� �ȳ� ���.
		void play();//����ã�� ���� ���.
		void setColor(short color, short bgcolor);//�¸�, �й�� �۾� ���� �ٲٴ� ���.
		void hint(int x, int y);//3x3 �� ��ġ�� ���.
		void deletemap();//map ����� ���.
		void memo();//memo ���.
};

