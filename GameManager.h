#pragma once
#include"Block.h"
#include"Stage.h"
#include"totalHead.h"
#include"User.h"
#include"Server.h"
#include"UserManager.h"
#include <MMSystem.h>
#pragma comment(lib,"Winmm.lib")

class GameManager
{
private:
	int cur_level;
	int game_over;
	Block cur_block;
	Block next_block;
	Stage** stage;	//stage[10]
	
public:
	GameManager();
	~GameManager();
	void init();
	void gameStart();
	int strikeCheck();
	void input_data();
	void showNextBlock();
	int isGameOver();
	void showGameOver();
	void showGameClear();
	void show_logo();
	void youdie();
	void outro();

	void printAscii(string fname, int x, int y);
	
	void setCursorView(bool visible)
	{
		CONSOLE_CURSOR_INFO cursor = { 1, visible };
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);

	}
	void SetColor(int color)

	{
		static HANDLE std_output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(std_output_handle, color);

	}
	void intro();

	
};

