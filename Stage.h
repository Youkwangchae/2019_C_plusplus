#pragma once
#include"totalHead.h"
#include"Block.h"

class Stage
{
private:
	int speed;   //숫자가 낮을수록 속도가 빠르다
	int stick_rate;      //막대가 나오는 확률 0~99 , 99면 막대기만 나옴

	
	int clear_score;// 목표점수
	int level;//생성자에서 입력받음. show_gamestat에서 사용됨.
	static int Tscore;//score관리하는 것도 생각해야 될듯
	int score;
	int card_score;

public:
	char total_block[21][14];
	Stage();
	Stage(int level);
	Stage(int level, int _speed, int _stick_rate, int _clear_score);
	~Stage();
	void resetTotalBlock();
	int showTotalBlock();
	int showGameStat();
	int checkFullLine();
	int mergeBlock(Block& block);

	int getSpeed();
	int getStickRate();
	int getLevel();
	int getClearScore();
	int getScore();
	int getCardScore();
	int getTScore();

	void setSpeed(int _speed);
	void setStickRate(int _stick_rate);
	void setLevel(int _level);
	void setScore(int _score);
	void setTScore(int _score);
	void setCardScore(int _card_score);
	void plusTScore();
};