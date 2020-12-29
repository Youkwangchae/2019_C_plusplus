#pragma once

#include"Block.h"
#include"Stage.h"
#include"totalHead.h"
#include"User.h"
#include <fstream>
class GameManager
{
private:
	int cur_level;
	int game_over;
	Block cur_block;
	Block next_block;
	Stage** stage;	//stage[3]
public:
	GameManager();
	~GameManager();
	void init();

	void gameStart();
	int strikeCheck();
	int input_data();
	void showNextBlock();
	int isGameOver();
	void showGameOver();
	void showGameClear();
	void show_logo();
	void printAscii(string fname, int x, int y);
};

