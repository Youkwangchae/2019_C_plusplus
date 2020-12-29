#include "CardManager.h"

using namespace std;

CardManager::CardManager()
{
	card_set = new Card *[4];
	level = 0;//사용자가 선택한 레벨 
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
	int end = 0;//게임을 종료시킬때 사용, 1일 때 종료한다.
	remain = remain_try[level];
	Client client;
	client.clientInit();

	
	int count = 0;
	int x1, y1;
	int x2, y2;
	//int cx = 2, cy = 3;
	int cx = plus_x, cy = 2 + plus_y;
	int cnt = 0;
	string str = "0";//통신할 데이터
	string rcv;//테트리스 점수


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
			//cout << "↑";

			if (card_set[(cy - 2 - plus_y) / 5][(cx - plus_x) / 10].getMatched() == false) {
				gotoxy(cx, cy - 2);
				cout << "┏━━━━━━━━┓";

				gotoxy(cx, cy - 1);
				cout << "┃        ┃";

				gotoxy(cx, cy);
				cout << "┃        ┃";

				gotoxy(cx, cy + 1);
				cout << "┃        ┃";

				gotoxy(cx, cy + 2);
				cout << "┗━━━━━━━━┛";
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
							cout << "     \"이미 선택한 카드다!\"" << endl;
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
							cout << "     \"이미 선택한 카드다!\"" << endl;
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
					cout << "      \"이런. 정답이야\"";

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
					cout << "      \"핳핳하. 틀렸어.\"";
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

			if (tetrisScore >= 10000)//테트리스 죽었을 때
			{
				end = 3;
				break;
			}

			if (tried == remain && cnt != 8)//사용자가 뒤집을 수 있는 횟수를 모두 사용
			{
				end = 1;
				tried = 0;
				break;
			}

			if (score + tetrisScore > clearScore[level])//다음스테이지로 넘어가는 if문
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
					str = to_string(score);//보내는 값을 0으로 설정해준다.
					client.sendMsg(str, rcv);
					tetrisScore = stoi(rcv);
				}
				else//4레벨 클리어. 엔딩크레딧
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

		else if (end == 1)//테트리스가 종료될때까지 계속 대기화면 출력, 테트리스에서 총점 넘으면 다시게임 진행할 수 있도록.
		{
			showEndState();
			while (true)
			{	
				gotoxy(12, 11);
				cout << "┃*      협동 점수 : ";
				cout << setw(4) << score + tetrisScore << "  *┃";
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
					if (level < 3)//1단계부터 3단계
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
						str = to_string(score);//보내는 값을 0으로 설정해준다.
						client.sendMsg(str, rcv);
						tetrisScore = stoi(rcv);
						count = 0;
						break;

					}
					else//4레벨 클리어. 엔딩크레딧
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

	//end = 1 : 카드게임 횟수 다 썼을 때
	//end = 2 : 카드게임 4레벨 클리어(게임 클리어)
	//end = 3 : 테트리스 터짐
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
	cout << i << " 번째 x, y 좌표를 입력하세요 ex) 1 3" << endl;
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
	printString("스테이지", level+1, printX, printY);
	printString("점수", score, printX, printY+1);
	printString("총점수", score + tetrisScore, printX, printY+2);
	printString("남은 시도횟수", remain - tried, printX, printY+3);

	SetColor(12);
	printAscii("jocker2.txt", 40, 6);
}

void CardManager::showEndState()
{
	int x = 12;
	int y = 7;
	SetColor(12);
	gotoxy(x, y);
	cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
	gotoxy(x, y+1);
	cout << "┃**************************┃";
	gotoxy(x, y+1);
	cout << "┃*      횟수 모두사용     *┃";
	gotoxy(x, y + 2);
	cout << "┃*    잠시 기다려주세요.  *┃";
	gotoxy(x, y+3);
	cout << "┃*      게임 점수 : ";
	cout<<setw(4)<<	score<<"  *┃";

	gotoxy(x, y+5);
	cout << "┃**************************┃";
	gotoxy(x, y+6);
	cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛";
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
	cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
	gotoxy(x, y + 1);
	cout << "┃**************************┃";
	gotoxy(x, y + 2);
	cout << "┃*        Game Over       *┃";
	gotoxy(x, y + 3);
	cout << "┃*    잠시 기다려주세요.  *┃";
	gotoxy(x, y + 4);
	cout << "┃*      게임 점수 : ";
	cout << setw(4) << score << "  *┃";
	gotoxy(x, y+5);
	cout << "┃*      총합 점수 : ";
	cout << setw(4) << totalScore  << "  *┃";
	gotoxy(x, y + 6);
	cout << "┃**************************┃";
	gotoxy(x, y + 7);
	cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛"<<endl;
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
	cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
	gotoxy(x, y + 1);
	cout << "┃**************************┃";
	gotoxy(x, y + 2);
	cout << "┃*        Game Clear      *┃";
	gotoxy(x, y + 3);
	cout << "┃*    축하 합니다!!!!!!!  *┃";
	gotoxy(x, y + 4);
	cout << "┃*      게임 점수 : ";
	cout << setw(4) << score << "  *┃";
	gotoxy(x, y + 5);
	cout << "┃*      총합 점수 : ";
	cout << setw(4) << totalScore << "  *┃";
	gotoxy(x, y + 6);
	cout << "┃**************************┃";
	gotoxy(x, y + 7);
	cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛"<<endl;
	fflush(stdin);

	SetColor(15);
	system("pause");
}


