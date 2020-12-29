#pragma once
#include"totalHead.h"
#include"Block.h"

class Stage
{
private:
	int speed;   //���ڰ� �������� �ӵ��� ������
	int stick_rate;      //���밡 ������ Ȯ�� 0~99 , 99�� ����⸸ ����

	
	int clear_score;// ��ǥ����
	int level;//�����ڿ��� �Է¹���. show_gamestat���� ����.
	static int Tscore;//score�����ϴ� �͵� �����ؾ� �ɵ�
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