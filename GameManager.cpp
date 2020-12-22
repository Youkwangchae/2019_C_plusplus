#include "GameManager.h"

GameManager::GameManager()
{
	game_over = 0;
	stage = new Stage*[10];
}

GameManager::~GameManager()
{
	delete[] stage;
}

void GameManager::init()
{
	srand((unsigned)time(NULL));
	game_over = 0;

	stage[0] = new Stage(1, 40, 20, 2);
	stage[1] = new Stage(2, 38, 19, 2);
	stage[2] = new Stage(3, 35, 18, 10);
	stage[3] = new Stage(4, 30, 17, 10);
	stage[4] = new Stage(5, 25, 16, 10);
	stage[5] = new Stage(6, 20, 15, 10);
	stage[6] = new Stage(7, 15, 14, 20);
	stage[7] = new Stage(8, 10, 13, 20);
	stage[8] = new Stage(9, 6, 12, 20);
	stage[9] = new Stage(10, 4, 11, 20);

}


void GameManager::gameStart()
{
	char keytemp;
	while (1)
	{
		init();
	
		cur_level = input_data();
		system("cls");

		stage[cur_level]->showTotalBlock();
		stage[cur_level]->showGameStat();
		next_block.makeNewBlock(stage[cur_level]->getStickRate());
		cur_block.changeCurBlock(next_block);
		next_block.makeNewBlock(stage[cur_level]->getStickRate());
		showNextBlock();

		for (int i = 1; 1; i++)
		{
			if (_kbhit())
			{

				keytemp = _getch();
				if (keytemp == EXT_KEY)
				{
					keytemp = _getch();
					switch (keytemp)
					{
					case KEY_UP:		//회전하기
						cur_block.removeBlock();
						cur_block.rotate();

						if (strikeCheck() == 1)
						{
							cur_block.rotate();
							cur_block.rotate();
							cur_block.rotate();
						}


						if (strikeCheck() == 2)
						{
							if (cur_block.getShape() != 0)
							{
								if (cur_block.getX() == 11)
								{
									cur_block.moveLeft();
								}
							}
							else
							{
								cur_block.moveLeft();
								cur_block.moveLeft();
								cur_block.moveLeft();
							}

						}
						cur_block.printBlock();
						break;

					case KEY_LEFT:		//왼쪽으로 이동
					{
						cur_block.removeBlock();
						cur_block.moveLeft();
						if (strikeCheck() == 1)
							cur_block.moveRight();
						cur_block.printBlock();
					}
					break;
					case KEY_RIGHT:		//오른쪽으로 이동
					{
						cur_block.removeBlock();

						cur_block.moveRight();
						if (strikeCheck() == 1 || strikeCheck() == 2)
							cur_block.moveLeft();
						cur_block.printBlock();
					}
					break;
					case KEY_DOWN:		//아래로 이동
						cur_block.removeBlock();
						cur_block.moveDown();
						game_over = isGameOver();
						if (game_over != 1)
							cur_block.printBlock();
						else
							stage[cur_level]->mergeBlock(cur_block);


						break;
					}
				}
				if (keytemp == 32)	//스페이스바를 눌렀을 때
				{
					while (game_over == 0)
					{
						cur_block.removeBlock();
						cur_block.moveDown();
						game_over = isGameOver();
					}

					if (game_over != 1)
						cur_block.printBlock();
					else
						stage[cur_level]->mergeBlock(cur_block);

				}
			}

			if (i % stage[cur_level]->getSpeed() == 0)
			{
				cur_block.removeBlock();
				cur_block.moveDown();
				game_over = isGameOver();
				if (game_over != 1)
					cur_block.printBlock();
				else
					stage[cur_level]->mergeBlock(cur_block);
			}
			string str;
			if (str == "1")
			{
				stage[cur_level]->setLines(stage[cur_level]->getLines() + 1);
				stage[cur_level]->showGameStat();
			}
			if (game_over == 1)
			{
				showGameOver();
				stage[cur_level]->setScore(0);
				SetColor(GRAY);
				break;
			}
			if (stage[cur_level]->getClearLine() <= stage[cur_level]->getLines())   //클리어 스테이지
			{
				if (cur_level == 9)
				{
					showGameClear();
					break;
				}

				stage[cur_level]->setLines(0);
				cur_level++;

				next_block.makeNewBlock(stage[cur_level]->getStickRate());
				cur_block.changeCurBlock(next_block);
				next_block.makeNewBlock(stage[cur_level]->getStickRate());
				showNextBlock();


				stage[cur_level]->showTotalBlock();
				stage[cur_level]->showGameStat();
				// 수정
				// 화면에 제대로 출력되지 않음

				showNextBlock();

			}

			gotoxy(77, 23);
			Sleep(20);
		}

	}

}

int GameManager::strikeCheck()
{
	int i, j;
	int block_dat;
	int x = cur_block.getX();
	int y = cur_block.getY();
	int shape = cur_block.getShape();
	int angle = cur_block.getAngle();
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (((x + j) == 0))
				block_dat = 1;
			//수정함
			else if ((x + j) == 13)
				block_dat = 2;
			else
			{
				//수정 
				//조건을 추가함
				//배열의 인덱스가 음수를 참조하는 경우가 발생함
				if ((y + i) >= 0)
					block_dat = stage[cur_level]->total_block[y + i][x + j];
				else
					block_dat = 0;
			}


			if ((block_dat == 1) && (cur_block.block_frame[shape][angle][i][j] == 1))         //좌측벽의 좌표를 빼기위함
			{
				return 1;
			}
			if ((block_dat == 2) && (cur_block.block_frame[shape][angle][i][j] == 1))
				return 2;
		}
	}
	return 0;
}

int GameManager::input_data()
{
	int i = 0;
	SetColor(GRAY);
	//=========================오류 수정=========================
	gotoxy(10, 7);
	cout << ("┏━━━━━━━━━<GAME KEY>━━━━━━━━━┓");
	Sleep(10);
	gotoxy(10, 8);
	cout << ("┃ UP   : Rotate Block        ┃");
	Sleep(10);
	gotoxy(10, 9);
	cout << ("┃ DOWN : Move One-Step Down  ┃");
	Sleep(10);
	gotoxy(10, 10);
	cout << ("┃ SPACE: Move Bottom Down    ┃");
	Sleep(10);
	gotoxy(10, 11);
	cout << ("┃ LEFT : Move Left           ┃");
	Sleep(10);
	gotoxy(10, 12);
	cout << ("┃ RIGHT: Move Right          ┃");
	Sleep(10);
	gotoxy(10, 13);
	cout << ("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");

	//=========================오류 수정=========================

	while (i < 1 || i>10)
	{
		gotoxy(10, 3);
		cout << ("Select Start level[1-10]:");
		while (true) {
			cin >> i;
			if (cin.fail())
			{
				gotoxy(10, 3);
				cout << "                                                             ";
				gotoxy(10, 3);
				cout << ("Select Start level[1-10]:");
				cin.clear(); // clears error flags
				cin.ignore(1000, '\n');
			}
			else
			{
				break;
			}
		}

	}



	cur_level = i - 1;
	system("cls");
	return cur_level;
}

void GameManager::showNextBlock()
{
	int i, j;
	SetColor((cur_level + 1) % 6 + 1);
	for (i = 1; i < 7; i++)
	{
		gotoxy(33, i);
		for (j = 0; j < 6; j++)
		{
			if (i == 1 || i == 6 || j == 0 || j == 5)
			{
				cout << ("■");
			}
			else {
				cout << ("  ");
			}

		}
	}

	next_block.printBlock();

}

int GameManager::isGameOver()
{

	if (strikeCheck() == 1)
	{
		cur_block.moveUp();

		if (cur_block.getY() <= 0)	//게임 오버
		{
			return 1;
		}

		stage[cur_level]->mergeBlock(cur_block);
		cur_block.changeCurBlock(next_block);

		next_block.removeBlock();
		next_block.makeNewBlock(stage[cur_level]->getStickRate());
		next_block.printBlock();

		return 2;

	}
	return 0;
}

void GameManager::showGameOver()
{
	SetColor(RED);
	gotoxy(15, 8);
	//=========================오류 수정=========================
	cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
	gotoxy(15, 9);
	cout << "┃**************************┃";
	gotoxy(15, 10);
	cout << "┃*        GAME OVER       *┃";
	gotoxy(15, 11);
	cout << "┃**************************┃";
	gotoxy(15, 12);
	cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛";
	fflush(stdin);
	Sleep(1000);

	_getch();
	system("cls");
}

void GameManager::showGameClear()
{
	SetColor(RED);
	gotoxy(15, 8);
	//=========================오류 수정=========================
	cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓";
	gotoxy(15, 9);
	cout << "┃**************************┃";
	gotoxy(15, 10);
	cout << "┃*        GAME CLEAR      *┃";
	gotoxy(15, 11);
	cout << "┃**************************┃";
	gotoxy(15, 12);
	cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛";
	fflush(stdin);
	Sleep(1000);

	_getch();
	system("cls");
}


void GameManager::show_logo()
{
	int i, j;
	gotoxy(13, 3);
	//=========================오류 수정=========================
	cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓";
	Sleep(100);
	gotoxy(13, 4);
	cout << "┃◆◆◆  ◆◆◆  ◆◆◆   ◆◆     ◆   ◆  ◆ ┃";
	Sleep(100);
	gotoxy(13, 5);
	cout << "┃  ◆    ◆        ◆     ◆ ◆    ◆    ◆◆  ┃";
	Sleep(100);
	gotoxy(13, 6);
	cout << "┃  ◆    ◆◆◆    ◆     ◆◆     ◆     ◆   ┃";
	Sleep(100);
	gotoxy(13, 7);
	cout << "┃  ◆    ◆        ◆     ◆ ◆    ◆    ◆◆  ┃";
	Sleep(100);
	gotoxy(13, 8);
	cout << "┃  ◆    ◆◆◆    ◆     ◆  ◆   ◆   ◆  ◆ ┃";
	Sleep(100);
	gotoxy(13, 9);
	cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛";


	gotoxy(28, 20);
	cout << "Please Press Any Key~!";

	for (i = 0; i >= 0; i++)
	{
		if (i % 40 == 0)
		{


			for (j = 0; j < 5; j++)
			{
				gotoxy(18, 14 + j);
				cout << ("                                                          ");


			}
			//=========================오류 수정=========================
			for (j = 0; j < 5; j++)
			{
				gotoxy(6, 14 + j);
				cout << ("                                                          ");
			}
			Block* temp[4] = { new Block(6, 14), new Block(12, 14) , new Block(19, 14) , new Block(24, 14) };
			for (int i = 0; i < 4; i++)
			{
				temp[i]->printBlock();
			}
		}
		if (_kbhit())
			break;
		Sleep(30);
	}

	_getch();
	system("cls");
}



