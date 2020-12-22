#pragma once
#include <Windows.h>
#include <string>
class Map
{
	int row,col;
	int** map;//map 정보 저장 배열.
	int** open;//map 오픈 정보 저장 배열.
	int bomb,num,check;
	int x, y;
	int count;
public:
	Map();
	~Map();
int Check(int num);//정수가 아닌 입력 예외 처리
int Check(char ch);//문자가 아닌 입력 예외처리
int range(int a, int b, int c);//범위 외의 입력 예외처리.
	void set();//map의 가로, 세로 길이 설정 기능.
		int** makeMap();//map 생성 기능.
		void hidemap();//map에 지뢰 숨김 기능.
		void setBomb();//지뢰 수 설정 기능.
		void showmap();//map 화면 출력 기능.
		void endgame();//승리 안내 기능.
		void play();//지뢰찾기 진행 기능.
		void setColor(short color, short bgcolor);//승리, 패배시 글씨 색깔 바꾸는 기능.
		void hint(int x, int y);//3x3 맵 펼치는 기능.
		void deletemap();//map 지우는 기능.
		void memo();//memo 기능.
};

