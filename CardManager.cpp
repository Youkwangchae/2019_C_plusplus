#include "CardManager.h"

using namespace std;

CardManager::CardManager()
{
	card_set = new Card *[4];
	level = 0;//����ڰ� ������ ���� 
	assignCard();
}

void CardManager::showCard()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << card_set[i][j];
		}
	}
}

void CardManager::gameStart()
{
	int end = 0;//������ �����ų�� ���, 1�� �� �����Ѵ�.
	remain = remain_try[level];
	Client client;
	client.clientInit();

	
	int count = 0;
	int x1, y1;
	int x2, y2;
	//int cx = 2, cy = 3;
	int cx = plus_x, cy = 2 + plus_y;
	int cnt = 0;
	string str = "0";//����� ������
	string rcv;//��Ʈ���� ����


	intro();
	SetColor(8);
	system("cls");

	setCursor();
	

	system("mode con cols=70 lines=20");


	while (true)
	{
		showCard();

		while (true)
		{
			
			showState();
			SetColor(12);
			gotoxy(cx, cy);
			//cout << "��";

			if (card_set[(cy - 2 - plus_y) / 5][(cx - plus_x) / 10].getMatched() == false) {
				gotoxy(cx, cy - 2);
				cout << "��������������������";

				gotoxy(cx, cy - 1);
				cout << "��        ��";

				gotoxy(cx, cy);
				cout << "��        ��";

				gotoxy(cx, cy + 1);
				cout << "��        ��";

				gotoxy(cx, cy + 2);
				cout << "��������������������";
			}


			if (_kbhit())
			{
				int key = _getch();
				if (key == 224)
				{
					key = _getch();
					switch (key)
					{
					case KEY_LEFT:
					{
						if (!(cx - 10 - plus_x < 0))
						{
							cx = cx - 10;
						}
						else {
							cx = 30 + plus_x;
						}
						break;
					}
					case KEY_RIGHT:
					{
				
						if (cx == 30 + plus_x)
						{
							cx = plus_x;

						}
						else
						{
							cx = cx + 10;

						}
						break;
					}

					case KEY_UP:
					{
						if (cy - 2 - plus_y > 0)
						{
							cy = cy - 5;
						}
						else {
							cy = 17 + plus_y;
						}
						break;
					}

					case KEY_DOWN:
					{
						if (cy < 15 + plus_y)
						{

							cy = cy + 5;

						}
						else {
			
							cy = 2 + plus_y;
						}
						break;

					}
					}

					SetColor(8);
					showCard();
				}
				else if (key == 13)
				{
					SetColor(8);

					
					if (count == 0)
					{

						x1 = cx - plus_x;
						
						y1 = cy - plus_y;

						
						if (card_set[(y1) / 5][(x1) / 10].getMatched() == true)
						{
							SetColor(12);
							showState();
							
							SetColor(8);
							gotoxy(print_x, print_y);
							cout << "     \"�̹� ������ ī���!\"" << endl;
							Sleep(300);
							system("cls");
							showCard();
							continue;
						}

						count++;
						card_set[(y1) / 5][(x1) / 10].setMatched(true);

						system("cls");
						showCard();


					}
					else
					{
						x2 = cx - plus_x;
						y2 = cy - plus_y;

						
						if (card_set[(y2) / 5][(x2) / 10].getMatched() == true)
						{
							SetColor(12);
							showState();
							
							SetColor(8);
							gotoxy(print_x, print_y);
							cout << "     \"�̹� ������ ī���!\"" << endl;
							Sleep(300);
							system("cls");
							showCard();
							continue;
						}
						count++;
					
						card_set[(y2) / 5][(x2) / 10].setMatched(true);

					}
				}
			}

			if (count == 2)
			{
				system("cls");
				showCard();
				
				if (card_set[(y1) / 5][(x1) / 10].getShape() == card_set[(y2) / 5][(x2) / 10].getShape())
				{
					SetColor(12);
					showState();
					
					SetColor(8);
					gotoxy(print_x, print_y);
					cout << "      \"�̷�. �����̾�\"";

					score += 150;
					str = to_string(score);
					
					Sleep(300);
					system("cls");
					showCard();
					cnt++;
					tried++;

				}
				else
				{
					card_set[(y1) / 5][(x1) / 10].setMatched(false);
					card_set[(y2) / 5][(x2) / 10].setMatched(false);
					SetColor(12);
					showState();
					
					SetColor(8);
					gotoxy(print_x, print_y);
					cout << "      \"�K�K��. Ʋ�Ⱦ�.\"";
					str = to_string(score);

					Sleep(300);
					system("cls");
					showCard();
					tried++;
				}
				count = 0;
			}

			client.sendMsg(str, rcv);
			tetrisScore = stoi(rcv);

			if (tetrisScore >= 10000)//��Ʈ���� �׾��� ��
			{
				end = 3;
				break;
			}

			if (tried == remain && cnt != 8)//����ڰ� ������ �� �ִ� Ƚ���� ��� ���
			{
				end = 1;
				tried = 0;
				break;
			}

			if (score + tetrisScore > clearScore[level])//�������������� �Ѿ�� if��
			{
				if (level < 3)
				{
					totalScore += score + tetrisScore;
					level++;
					assignCard();
					score = 0;
					cnt = 0;
					tried = 0;
					remain = remain_try[level];
					end = 0;
					tetrisScore = 0;
					system("cls");
					SetColor(8);
					showCard();
					count = 0;
					str = to_string(score);//������ ���� 0���� �������ش�.
					client.sendMsg(str, rcv);
					tetrisScore = stoi(rcv);
				}
				else//4���� Ŭ����. ����ũ����
				{
					totalScore += (score + tetrisScore);
					end = 2;
					break;
				}
			}
			
			if (cnt == 8)break;

		}

		if (end == 2) break;

		if (end == 3)
		{
			tetrisScore -= 10000;
			totalScore += score + tetrisScore;
			break;
		}

		else if (end == 1)//��Ʈ������ ����ɶ����� ��� ���ȭ�� ���, ��Ʈ�������� ���� ������ �ٽð��� ������ �� �ֵ���.
		{
			showEndState();
			while (true)
			{	
				gotoxy(12, 11);
				cout << "��*      ���� ���� : ";
				cout << setw(4) << score + tetrisScore << "  *��";
				//string str = to_string(score);
				client.sendMsg(str, rcv);
				tetrisScore = stoi(rcv);

				if (tetrisScore >= 10000)
				{
					tetrisScore -= 10000;
					totalScore += score + tetrisScore;
					end = 3;
					break;
				}
				
				if (score + tetrisScore > clearScore[level])
				{
					if (level < 3)//1�ܰ���� 3�ܰ�
					{
						totalScore += (score + tetrisScore);
						level++;
						assignCard();
						score = 0;
						cnt = 0;
						tried = 0;
						remain = remain_try[level];
						end = 0;
						tetrisScore = 0;
						system("cls");
						SetColor(8);
						showCard();
						str = to_string(score);//������ ���� 0���� �������ش�.
						client.sendMsg(str, rcv);
						tetrisScore = stoi(rcv);
						count = 0;
						break;

					}
					else//4���� Ŭ����. ����ũ����
					{
						totalScore += (score + tetrisScore);
						end = 2;
						break;
					}
				}
				
			}
			
			if (end == 3 || end == 2) break;
		}
	}

	//end = 1 : ī����� Ƚ�� �� ���� ��
	//end = 2 : ī����� 4���� Ŭ����(���� Ŭ����)
	//end = 3 : ��Ʈ���� ����
	if (end == 2)
	{
		system("cls");
		SetColor(15);
		showWin();
		outro();

	}
	else if (end == 3)
	{
		system("cls");
		SetColor(15);
		showAllOver();
		youdie();
	}

	SetColor(15);
	return;
}

void CardManager::inputXY(int& x, int& y, int i)
{
	cout << i << " ��° x, y ��ǥ�� �Է��ϼ��� ex) 1 3" << endl;
	cin >> x >> y;
	x--;
	y--;
}

CardManager::~CardManager()
{
	delete[] card_set;
}

void CardManager::showState()
{
	int printX = 44;
	int printY = 1;
	SetColor(15);
	printString("��������", level+1, printX, printY);
	printString("����", score, printX, printY+1);
	printString("������", score + tetrisScore, printX, printY+2);
	printString("���� �õ�Ƚ��", remain - tried, printX, printY+3);

	SetColor(12);
	printAscii("jocker2.txt", 40, 6);
}

void CardManager::showEndState()
{
	int x = 12;
	int y = 7;
	SetColor(12);
	gotoxy(x, y);
	cout << "��������������������������������������������������������" << endl;
	gotoxy(x, y+1);
	cout << "��**************************��";
	gotoxy(x, y+1);
	cout << "��*      Ƚ�� ��λ��     *��";
	gotoxy(x, y + 2);
	cout << "��*    ��� ��ٷ��ּ���.  *��";
	gotoxy(x, y+3);
	cout << "��*      ���� ���� : ";
	cout<<setw(4)<<	score<<"  *��";

	gotoxy(x, y+5);
	cout << "��**************************��";
	gotoxy(x, y+6);
	cout << "��������������������������������������������������������";
	fflush(stdin);
}



void CardManager::assignCard()
{
	for (int i = 0; i < 4; i++)
	{
		card_set[i] = new Card[4];
		for (int j = 0; j < 4; j++)
		{
			int rnd_num2 = rand() % 8;
			if (index_cnt[level][rnd_num2] < 2)
			{
				index_cnt[level][rnd_num2]++;
				card_set[i][j].setShape(shape_arr[level][rnd_num2]);
	;			card_set[i][j].setX(1 + 10 * j + plus_x);
				card_set[i][j].setY(2 + 5 * i + plus_y);
			}
			else
			{
				j--;
				continue;
			}
		}
	}
}

void CardManager::showAllOver()
{
	int x = 13;
	int y = 5;
	SetColor(12);
	gotoxy(x, y);
	cout << "��������������������������������������������������������" << endl;
	gotoxy(x, y + 1);
	cout << "��**************************��";
	gotoxy(x, y + 2);
	cout << "��*        Game Over       *��";
	gotoxy(x, y + 3);
	cout << "��*    ��� ��ٷ��ּ���.  *��";
	gotoxy(x, y + 4);
	cout << "��*      ���� ���� : ";
	cout << setw(4) << score << "  *��";
	gotoxy(x, y+5);
	cout << "��*      ���� ���� : ";
	cout << setw(4) << totalScore  << "  *��";
	gotoxy(x, y + 6);
	cout << "��**************************��";
	gotoxy(x, y + 7);
	cout << "��������������������������������������������������������"<<endl;
	fflush(stdin);

	SetColor(15);
	system("pause");
}

void CardManager::showWin()
{
	int x = 13;
	int y = 5;
	SetColor(9);
	gotoxy(x, y);
	cout << "��������������������������������������������������������" << endl;
	gotoxy(x, y + 1);
	cout << "��**************************��";
	gotoxy(x, y + 2);
	cout << "��*        Game Clear      *��";
	gotoxy(x, y + 3);
	cout << "��*    ���� �մϴ�!!!!!!!  *��";
	gotoxy(x, y + 4);
	cout << "��*      ���� ���� : ";
	cout << setw(4) << score << "  *��";
	gotoxy(x, y + 5);
	cout << "��*      ���� ���� : ";
	cout << setw(4) << totalScore << "  *��";
	gotoxy(x, y + 6);
	cout << "��**************************��";
	gotoxy(x, y + 7);
	cout << "��������������������������������������������������������"<<endl;
	fflush(stdin);

	SetColor(15);
	system("pause");
}


