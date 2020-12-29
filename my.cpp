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
		cout << "���� �б� ����" << endl;
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

	PlaySound(TEXT("����16.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	int k = 1;
	int i = 0;
	while (k) { //������ ��� >> ���� ����� �޼��� ���.
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
	cout << ("������������������������������������������������������������< STORY >������������������������������������������������������������");
	gotoxy(10, 8);
	cout << "��  �߰���� ���迡�� ���������� ������ �˷� ���� ��ź�� ���� �� �濡��" << endl;
	gotoxy(10, 9);
	cout << "��  ����� �� ���� ������ �Ǿ���.                                    ��" << endl;
	gotoxy(10, 10);
	cout << "��  ��� �л��鿡�� �������� �̰��� Ż���� ������ ����� �����Ѵ�. ��" << endl;
	gotoxy(10, 11);
	cout << "��  �غ�� ���ӵ鿡�� ���� ���� ���� ���� �����̻���                 ��" << endl;
	gotoxy(10, 12);
	cout << "��  �Ѱܾ߸� �ϴ� ���̴�.                                            ��" << endl;
	gotoxy(10, 13);
	cout << "�� * ���������� ����ɼ��� ������ ���̵��� �����Ѵ�.                 ��" << endl;
	gotoxy(10, 14);
	cout << "�� * �� ���� ���� ������ ������θ� �Ǵ��Ѵ�.                        ��" << endl;
	gotoxy(10, 15);
	cout << ("������������������������������������������������������������������������������������������������������������������������������������������") << endl;
	system("pause"); //���� ���� ����.
	system("cls");

}

void outro() {

	system("cls");
	system("mode con cols=180 lines=45");

	PlaySound(TEXT("����ȿ����13.wav"), NULL, SND_FILENAME | SND_ASYNC);

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
	PlaySound(TEXT("��-���.wav"), NULL, SND_FILENAME | SND_ASYNC);
	SetColor(RED);
	printAscii("Text.txt", 0, 0);
	Sleep(5000);


}

