#pragma warning(disable: 4996)
#include"totalHead.h"
#include"Block.h"
#include"Stage.h"
#include"GameManager.h"
#include"Server.h"
#include"UserManager.h"

using namespace std;
int gotoxy(int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.Y = y;
	pos.X = x;
	SetConsoleCursorPosition(hConsole, pos);
	return 0;
}

void SetColor(int color)

{
	static HANDLE std_output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(std_output_handle, color);
}

int main()
{
	GameManager game;
	game.show_logo();
	game.gameStart();
	serverClose();
	
	return 0;
}
