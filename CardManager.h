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
	string shape_arr[4][8] = { {"cout", "cin", "std", "리터럴", "const", "변수", "자료형", "배열"},
	{"포인터", "오버로딩", "동적할당", "디폴트", "r-value", "객체", "접근제어", "클래스"},
	{"this", "생성자", "소멸자", "초기화", "static", "다중상속", "접근제어", "상속"},
	{"다형성", "가상함수", "템플릿", "스택", "벡터", "리스트", "큐", "STL"} };


	int score = 0;//카드게임 점수
	int remain_try[4] = { 20, 15, 10, 8 };// 카드짝을 뒤집을 수 있는 횟수
	int tried = 0;//사용자가 뒤집은 카드의 횟수
	int remain;//:remain_try[4]에서 값 하나 받아오는 변수
	int tetrisScore = 0;//테트리스게임에서 받아오는 점수.
	int level;//스테이지 인덱스값 참조위한 변수

	int index_cnt[4][8] = { 0, };//중복체크를 위한 이차원 배열

	int clearScore[4] = { 500, 1000, 1500, 2000 };
	
	int totalScore = 0;//스테이지 총 누적 점수

public:
	CardManager();
	void showCard();
	void gameStart();
	void inputXY(int& x, int& y, int i);
	~CardManager();


	void showState();//카드게임의 실시간 점수를 출력해주는 기능
	void showEndState();//사용자가 카드게임에서 뒤집기를 모두 사용했을때 뜨는 창
	void assignCard();//카드 배열을 레벨에 맞게 배정해주는 함수
	void showAllOver();//게임에서 패배할 경우(1. 테트리스 게임에서 패배 2. 테트리스와 카드게임 모두 패배)
	void showWin();//게임에서 승리할 경우
};
