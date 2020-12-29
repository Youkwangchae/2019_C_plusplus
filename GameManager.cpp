#include "GameManager.h"


GameManager::GameManager()
{
	game_over = 0;
	stage = new Stage* [10];
}

GameManager::~GameManager()
{
	delete[] stage;
}

void GameManager::init()
{
	srand((unsigned)time(NULL));
	game_over = 0;
	
	stage[0] = new Stage(1, 12, 20, 500);
	stage[1] = new Stage(2, 10, 19, 1000);
	stage[2] = new Stage(3, 8, 18, 1500);
	stage[3] = new Stage(4, 6, 17, 2000);
	for (int i = 0; i < 4; i++)
	{
		stage[i]->setScore(0);
		stage[i]->setCardScore(0);
	}
	stage[0]->setTScore(0);
	
}


void GameManager::gameStart()
{
	char keytemp;
	
	
	
	while (1)
	{
		
		
		Server server;
		server.serverInit();
		//intro();

		init();
		system("mode con cols=70 lines=30");
		UserManager um;
		um.setCursorView(false);
		um.membership();
		
		//input_data();
		
		cur_level = 0;
		
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
					case KEY_UP:		//ȸ���ϱ�
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
						
					case KEY_LEFT:		//�������� �̵�
						{
							cur_block.removeBlock();
							cur_block.moveLeft();
							if (strikeCheck() == 1)
								cur_block.moveRight();
							cur_block.printBlock();
						}
						break;
					case KEY_RIGHT:		//���������� �̵�
						{
							cur_block.removeBlock();
							
							cur_block.moveRight();
							if (strikeCheck() == 1 || strikeCheck() == 2)
								cur_block.moveLeft();
							cur_block.printBlock();
						}
						break;
					case KEY_DOWN:		//�Ʒ��� �̵�
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
				if (keytemp == 32)	//�����̽��ٸ� ������ ��
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
			
			
			if (game_over == 1)
			{
				server.recvMsg(str, to_string(10000 + stage[cur_level]->getScore()));
				stage[cur_level]->plusTScore();
				stage[cur_level]->setScore(0);
				stage[cur_level]->setCardScore(0);
				
				um.setDBScore(stage[cur_level]->getTScore());

				system("mode con cols=120 lines=130");
				showGameOver();
				Sleep(500);
				system("cls");
				
				youdie();
				SetColor(GRAY);

				server.serverClose();
				exit(0);
			}
			else
			{
				server.recvMsg(str, to_string(stage[cur_level]->getScore()));
				int num = stoi(str);
				stage[cur_level]->setCardScore(num);
				stage[cur_level]->showGameStat();
			}
			
			if (stage[cur_level]->getScore()+ stage[cur_level]->getCardScore() >= stage[cur_level]->getClearScore())   //Ŭ���� ��������
			{
				stage[cur_level]->plusTScore();
				stage[cur_level]->setScore(0);
				stage[cur_level]->setCardScore(0);
				if (cur_level == 3)
				{
					um.setDBScore(stage[cur_level]->getTScore());
					showGameClear();
					Sleep(500);
					system("cls");
					system("mode con cols=120 lines=130");
					outro();
					server.serverClose();
					exit(0);
				}
				cur_level++;
				stage[cur_level]->setScore(0);
				stage[cur_level]->setCardScore(0);

				
				next_block.makeNewBlock(stage[cur_level]->getStickRate());
				cur_block.changeCurBlock(next_block);
				next_block.makeNewBlock(stage[cur_level]->getStickRate());
				showNextBlock();


				stage[cur_level]->showTotalBlock();
				stage[cur_level]->showGameStat();
				// ����
				// ȭ�鿡 ����� ��µ��� ����

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
			//������
			else if ((x + j) == 13)
				block_dat = 2;
			else
			{
				//���� 
				//������ �߰���
				//�迭�� �ε����� ������ �����ϴ� rud�찡 �߻���
				if ((y + i) >= 0)
					block_dat = stage[cur_level]->total_block[y + i][x + j];
				else
					block_dat = 0;
			}


			if ((block_dat == 1) && (cur_block.block_frame[shape][angle][i][j] == 1))                                                                     //�������� ��ǥ�� ��������
			{
				return 1;
			}
			if ((block_dat == 2) && (cur_block.block_frame[shape][angle][i][j] == 1))
				return 2;
		}
	}
	return 0;
}

void GameManager::input_data()
{
	int i = 0;
	SetColor(GRAY);
	//=========================���� ����=========================
	gotoxy(10, 7);
	cout<<("��������������������<GAME KEY>��������������������");
	Sleep(10);
	gotoxy(10, 8);
	cout<<("�� UP   : Rotate Block        ��");
	Sleep(10);
	gotoxy(10, 9);
	cout<<("�� DOWN : Move One-Step Down  ��");
	Sleep(10);
	gotoxy(10, 10);
	cout<<("�� SPACE: Move Bottom Down    ��");
	Sleep(10);
	gotoxy(10, 11);
	cout<<("�� LEFT : Move Left           ��");
	Sleep(10);
	gotoxy(10, 12);
	cout<<("�� RIGHT: Move Right          ��");
	Sleep(10);
	gotoxy(10, 13);
	cout<<("������������������������������������������������������������");

	//=========================���� ����=========================

	while (i < 1 || i>10)
	{
		gotoxy(10, 3);
		cout<<("Select Start level[1-10]:");
		while(true){
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
				cout<<("��");
			}
			else {
				cout<<("  ");
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

		if (cur_block.getY() <= 0)	//���� ����
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
	//=========================���� ����=========================
	cout<<"��������������������������������������������������������"<<endl;
	gotoxy(15, 9);
	cout<<"��**************************��";
	gotoxy(15, 10);
	cout<<"��*        GAME OVER       *��";
	gotoxy(15, 11);
	
	cout << "��*        "<<setw(5)<< stage[0]->getTScore() << "           *��";
	gotoxy(15, 12);
	cout<<"��**************************��";
	gotoxy(15, 13);
	cout<<"��������������������������������������������������������";
	fflush(stdin);
	Sleep(1000);

	_getch();
	system("cls");
}

void GameManager::showGameClear()
{
	SetColor(RED);
	gotoxy(15, 8);
	//=========================���� ����=========================
	cout<<"��������������������������������������������������������";
	gotoxy(15, 9);
	cout<<"��**************************��";
	gotoxy(15, 10);
	cout<<"��*        GAME CLEAR      *��";
	gotoxy(15, 11);
	cout<<"��*        "<<setw(10)<<stage[0]->getTScore()<< "      *��";
	gotoxy(15, 12);
	cout<<"��**************************��";
	gotoxy(15, 13);
	cout<<"��������������������������������������������������������";
	fflush(stdin);
	Sleep(1000);

	_getch();
	system("cls");
}


void GameManager::show_logo()
{
	int i, j;
	gotoxy(13, 3);
	//=========================���� ����=========================
	cout<<"������������������������������������������������������������������������������������������������";
	Sleep(100);
	gotoxy(13, 4);
	cout<<"���ߡߡ�  �ߡߡ�  �ߡߡ�   �ߡ�     ��   ��  �� ��";
	Sleep(100);
	gotoxy(13, 5);
	cout<<"��  ��    ��        ��     �� ��    ��    �ߡ�  ��";
	Sleep(100);
	gotoxy(13, 6);
	cout<<"��  ��    �ߡߡ�    ��     �ߡ�     ��     ��   ��";
	Sleep(100);
	gotoxy(13, 7);
	cout<<"��  ��    ��        ��     �� ��    ��    �ߡ�  ��";
	Sleep(100);
	gotoxy(13, 8);
	cout<<"��  ��    �ߡߡ�    ��     ��  ��   ��   ��  �� ��";
	Sleep(100);
	gotoxy(13, 9);
	cout<<"������������������������������������������������������������������������������������������������";


	gotoxy(28, 20);
	cout<<"Please Press Any Key~!";

	for (i = 0; i >= 0; i++)
	{
		if (i % 40 == 0)
		{


			for (j = 0; j < 5; j++)
			{
				gotoxy(18, 14 + j);
				cout<<("                                                          ");


			}
			//=========================���� ����=========================
			for (j = 0; j < 5; j++)
			{
				gotoxy(6, 14 + j);
				cout<<("                                                          ");
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

void GameManager::youdie()
{
	
	SetColor(RED);
	PlaySound(TEXT("��-���.wav"), NULL, SND_FILENAME | SND_ASYNC);
	printAscii("Text.txt", 0, 0);
	
	Sleep(3500);
}

void GameManager::outro()
{
	PlaySound(TEXT("����ȿ����13.wav"), NULL, SND_FILENAME | SND_ASYNC);
	
	SetColor(15);
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

void GameManager::printAscii(string fname, int x, int y)
{
	ifstream File(fname);

	if (File)                      //Check if everything is good
	{
		while (File.good())
		{
			gotoxy(x, y);
			string line;                  //Temp line
			getline(File, line);        //Get temp line
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

void GameManager::intro()
{
	PlaySound(TEXT("����16.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	setCursorView(false);
	system("mode con cols=180 lines=45");

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


