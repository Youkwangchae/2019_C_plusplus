#include <iostream>
#include "Map.h"
using namespace std;

int main()
{
	Map map;
	map.set();//map�� ���� ���� ���� ����.
	map.makeMap();//map���� ����.
	map.setBomb();//���� ���� ���� ����.
	map.hidemap();//map�� ���� ����.
	map.play();//���� ���� ����
	system("pause");
	return 0;
}