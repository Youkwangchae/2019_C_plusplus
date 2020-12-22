#include <iostream>
#include "Map.h"
using namespace std;

int main()
{
	Map map;
	map.set();//map의 가로 세로 정보 저장.
	map.makeMap();//map정보 생성.
	map.setBomb();//지뢰 개수 정보 저장.
	map.hidemap();//map에 지뢰 저장.
	map.play();//지뢰 게임 진행
	system("pause");
	return 0;
}