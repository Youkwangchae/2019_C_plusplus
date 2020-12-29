#include "Stage.h"
#include<Windows.h>
int Stage::Tscore = 0;
Stage::Stage()//default 생성자
{

}


Stage::Stage(int level)//생성자에서 total_block을 초기화 시켜준다.
{
	this->level = level;
	int i, j;

	score = 0;
	card_score = 0;

	srand((unsigned)time(NULL));//이거는 나중에 게임매니저나 메인으로 옮겨야 할듯.

	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 14; j++)
		{
			if ((j == 0) || (j == 13))
			{
				total_block[i][j] = 1;
			}
			else {
				total_block[i][j] = 0;
			}
		}
	}

	for (j = 0; j < 14; j++)         //화면의 제일 밑의 줄은 1로 채운다.
		total_block[20][j] = 1;
}

Stage::Stage(int _level, int _speed, int _stick_rate, int _clear_score)
{
	level = _level;
	speed = _speed;
	stick_rate = _stick_rate;
	clear_score = _clear_score;
	score = 0;
	card_score = 0;
	int i, j;

	srand((unsigned)time(NULL));//이거는 나중에 게임매니저나 메인으로 옮겨야 할듯.

	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 14; j++)
		{
			if ((j == 0) || (j == 13))
			{
				total_block[i][j] = 1;
			}
			else {
				total_block[i][j] = 0;
			}
		}
	}

	for (j = 0; j < 14; j++)         //화면의 제일 밑의 줄은 1로 채운다.
		total_block[20][j] = 1;
}

Stage::~Stage()
{

}

void Stage::resetTotalBlock()//total_block을 원상태로 초기화 시켜주는 함수
{
	int i, j;

	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 14; j++)
		{
			if ((j == 0) || (j == 13))
			{
				total_block[i][j] = 1;
			}
			else {
				total_block[i][j] = 0;
			}
		}
	}

	for (j = 0; j < 14; j++)         //화면의 제일 밑의 줄은 1로 채운다.
		total_block[20][j] = 1;
}

int Stage::showTotalBlock()
{


	int i, j;
	SetColor(DARK_GRAY);
	for (i = 0; i < 21; i++)
	{
		for (j = 0; j < 14; j++)
		{
			if (j == 0 || j == 13 || i == 20)      //레벨에 따라 외벽 색이 변함
			{
				// 수정 level에 이상한 값이 들어갔을 경우 처리
				SetColor((level % 6) + 1);

			}
			else {
				SetColor(DARK_GRAY);
			}
			gotoxy((j * 2) + ab_x, i + ab_y);//일단 여기서 지역변수로
			if (total_block[i][j] == 1)
			{
				cout << "■";
			}
			else {
				cout << "  ";
			}

		}
	}
	SetColor(BLACK);
	gotoxy(77, 23);
	return 0;
}

int Stage::showGameStat()
{
	static int printed_text = 0;
	SetColor(GRAY);
	if (printed_text == 0)
	{
		gotoxy(35, 7);
		cout << "STAGE" << endl;

		gotoxy(35, 9);
		cout << "SCORE" << endl;

		gotoxy(35, 12);
		cout << "협동 점수" << endl;
	}
	gotoxy(41, 7);
	printf("%d", this->level);
	gotoxy(35, 10);
	printf("%10d", this->score);
	gotoxy(35, 13);
	printf("%10d", this->card_score+this->score);
	return 0;
}



int Stage::checkFullLine()
{
	int i, j, k;
	for (i = 0; i < 20; i++)
	{
		for (j = 1; j < 13; j++)
		{
			if (total_block[i][j] == 0)
				break;
		}
		if (j == 13)   //한줄이 다 채워졌음
		{
			showTotalBlock();
			SetColor(BLUE);
			gotoxy(1 * 2 + ab_x, i + ab_y);
			for (j = 1; j < 13; j++)
			{
				cout << "□";
				Sleep(10);
			}
			gotoxy(1 * 2 + ab_x, i + ab_y);
			for (j = 1; j < 13; j++)
			{
				cout << "  ";
				Sleep(10);
			}

			for (k = i; k > 0; k--)
			{
				for (j = 1; j < 13; j++)
					total_block[k][j] = total_block[k - 1][j];
			}
			for (j = 1; j < 13; j++)
				total_block[0][j] = 0;
			score += 100 + (level * 10) + (rand() % 10);
			showGameStat();
		}
	}
	return 0;
}


int Stage::mergeBlock(Block& block)
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			total_block[block.getY() + i][block.getX() + j] |= block.block_frame[block.getShape()][block.getAngle()][i][j];
		}
	}
	checkFullLine();
	showTotalBlock();

	return 0;
}

int Stage::getSpeed()
{
	return this->speed;
}

int Stage::getStickRate()
{
	return this->stick_rate;
}

int Stage::getLevel()
{
	return this->level;
}

int Stage::getClearScore()
{
	return clear_score;
}

int Stage::getScore()
{
	return this->score;
}

int Stage::getCardScore()
{
	return card_score;
}

int Stage::getTScore()
{
	return Tscore;
}

void Stage::setSpeed(int _speed)
{
	this->speed = _speed;
}

void Stage::setStickRate(int _stick_rate)
{
	this->stick_rate = _stick_rate;
}

void Stage::setLevel(int _level)
{
	this->level = _level;
}

void Stage::setScore(int _score)
{
	this->score = _score;
}

void Stage::setTScore(int _score)
{
	Tscore = _score;
}

void Stage::setCardScore(int _card_score)
{
	card_score = _card_score;
}


void Stage::plusTScore()
{
	Tscore += score + card_score;
}
