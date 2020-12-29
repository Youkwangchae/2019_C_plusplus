#include"my.h"

void gotoxy(int _x, int _y) {

	COORD pos = { _x, _y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

}

void setCursor()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void SetColor(int color)
{
	static HANDLE std_output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(std_output_handle, color);

}

void printAscii(string fname , int x, int y)
{
	ifstream File(fname);

	if (File)                      //Check if everything is good
	{
		while (File.good())
		{
			gotoxy(x, y);
			std::string line;                  //Temp line
			std::getline(File, line);        //Get temp line
			//TempLine += "\n";                      //Add newline character
			cout << line;
			y++;                //Add newline
		}
	}
	else                           //Return error
	{
		cout << "파일 읽기 오류" << endl;
	}

	File.close();
}

void printString(string sname, int score, int x, int y)
{
	gotoxy(x, y);
	cout << sname << " : " << score << endl;
}

void setCursorView(bool visible)
{
	CONSOLE_CURSOR_INFO cursor = { 1, visible };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);

}

void intro() {
	setCursorView(false);
	system("mode con cols=180 lines=45");

	PlaySound(TEXT("공포16.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	int k = 1;
	int i = 0;
	while (k) { //눈동자 출력 >> 가둔 사람의 메세지 출력.
		printAscii("Intro_1.txt", 25, 0);
		Sleep(200);
		printAscii("Intro_2.txt", 25, 0);
		Sleep(200);
		printAscii("Intro_3.txt", 25, 0);
		Sleep(200);
		printAscii("Intro_4.txt", 25, 0);
		Sleep(200);
		printAscii("Intro_5.txt", 25, 0);
		Sleep(200);
		printAscii("Intro_3.txt", 25, 0);
		Sleep(200);
		printAscii("Intro_2.txt", 25, 0);
		Sleep(200);
		printAscii("Intro_1.txt", 25, 0);
		Sleep(200);

		if (_kbhit())
			k = 0;
		i++;
		if (i == 3 || i == 4 || i == 5)
		{
			SetColor(4);
			//system("cls");
			printAscii("script1.txt", 33, 25);
			Sleep(200);
			SetColor(15);
			//system("pause");

			//break;
			if (i == 5) system("cls");
		}

		if (i == 6 || i == 7 || i == 8)
		{
			SetColor(4);
			printAscii("script2.txt", 20, 25);
			Sleep(200);
			if (i == 8) system("cls");
			SetColor(15);
			//system("pause");
			//break;
		}

		if (i == 9 || i == 10 || i == 11)
		{
			SetColor(4);
			printAscii("script3.txt", 18, 25);
			Sleep(100);
			if (i == 11) system("cls");
			SetColor(15);
		}

		if (i == 12 || i == 13 || i == 14)
		{
			SetColor(4);
			printAscii("script4.txt", 18, 25);
			Sleep(100);
			if (i == 14) system("cls");
			SetColor(15);
		}

		if (i == 15 || i == 16 || i == 17)
		{
			SetColor(4);
			printAscii("script5.txt", 18, 25);
			Sleep(100);
			if (i == 17) system("cls");
			SetColor(15);
		}

		if (i == 18 || i == 19 || i == 20)
		{
			SetColor(4);
			printAscii("script6.txt", 18, 25);
			Sleep(100);
			if (i == 20) {
				system("cls");
				SetColor(15);
				break;
			}
		}

	}

	system("pause");
	system("cls");


	SetColor(15);
	gotoxy(10, 7);
	cout << ("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━< STORY >━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	gotoxy(10, 8);
	cout << "┃  중간고사 시험에서 부정행위를 저지른 죄로 시한 폭탄이 가득 찬 방에┃" << endl;
	gotoxy(10, 9);
	cout << "┃  공대생 두 명이 갇히게 되었다.                                    ┃" << endl;
	gotoxy(10, 10);
	cout << "┃  깨어난 학생들에게 누군가가 이곳을 탈출할 유일한 방법을 제시한다. ┃" << endl;
	gotoxy(10, 11);
	cout << "┃  준비된 게임들에서 얻은 점수 합이 일정 점수이상을                 ┃" << endl;
	gotoxy(10, 12);
	cout << "┃  넘겨야만 하는 것이다.                                            ┃" << endl;
	gotoxy(10, 13);
	cout << "┃ * 스테이지가 진행될수록 게임의 난이도는 급증한다.                 ┃" << endl;
	gotoxy(10, 14);
	cout << "┃ * 두 명의 점수 합으로 통과여부를 판단한다.                        ┃" << endl;
	gotoxy(10, 15);
	cout << ("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛") << endl;
	system("pause"); //이후 게임 시작.
	system("cls");

}

void outro() {

	system("cls");
	system("mode con cols=180 lines=45");

	PlaySound(TEXT("공포효과음13.wav"), NULL, SND_FILENAME | SND_ASYNC);

	printAscii("ending1.txt", 0, 0);
	Sleep(600);
	printAscii("ending2.txt", 0, 0);
	Sleep(600);
	printAscii("ending3.txt", 0, 0);
	Sleep(600);
	printAscii("ending5.txt", 0, 0);
	Sleep(600);
	system("cls");

	SetColor(RED);
	printAscii("script7.txt", 10, 10);
	Sleep(600);
	system("cls");

	printAscii("Script8.txt", 10, 10);
	Sleep(600);
	system("cls");

	printAscii("script9.txt", 10, 10);
	Sleep(3500);
	system("cls");

	return;
}

void youdie() {

	system("cls");
	system("mode con cols=90 lines=45");
	PlaySound(TEXT("남-비명.wav"), NULL, SND_FILENAME | SND_ASYNC);
	SetColor(RED);
	printAscii("Text.txt", 0, 0);
	Sleep(5000);


}

