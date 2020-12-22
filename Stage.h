#pragma once
#include"totalHead.h"
#include"Block.h"

class Stage
{
private:
	int speed;   //���ڰ� �������� �ӵ��� ������
	int stick_rate;      //���밡 ������ Ȯ�� 0~99 , 99�� ����⸸ ����
	int clear_line;

	int lines;//���� �������� �˷��ִ� ����
	int level;//�����ڿ��� �Է¹���. show_gamestat���� ����.
	static int score;//score�����ϴ� �͵� �����ؾ� �ɵ�

public:
	char total_block[21][14];
	Stage();
	Stage(int level);
	Stage(int level, int _speed, int _stick_rate, int _clear_line);
	~Stage();
	void resetTotalBlock();
	int showTotalBlock();
	int showGameStat();
	int checkFullLine();
	int mergeBlock(Block& block);

	int getSpeed();
	int getStickRate();
	int getClearLine();
	int getLines();
	int getLevel();
	int getScore();

	void setSpeed(int _speed);
	void setStickRate(int _stick_rate);
	void setClearLine(int _clear_line);
	void setLines(int _lines);
	void setLevel(int _level);
	void setScore(int _score);

};