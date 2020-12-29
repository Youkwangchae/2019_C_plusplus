#pragma warning(disable: 4996)
#include"totalHead.h"
#include"Block.h"
#include"Stage.h"
#include"GameManager.h"
#include"Server.h"
#include"UserManager.h"
#include <MMSystem.h>
#pragma comment(lib,"Winmm.lib")
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
	
	//UserManager um;
	//um.user.setAll("123", "123", "123", 0);
	//um.user.getUserInfo();
	//um.setDBScore(500);
	/*printf("아무 키나 입력하시면 소리 재생이 멈춥니다.\n");
	PlaySound(TEXT("music.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	while (!_kbhit());
	PlaySound(NULL, 0, 0);*/



	Server test;
	
	GameManager game;
	game.gameStart();
	
	return 0;
}
