#include "Block.h"
char Block::block_frame[7][4][4][4] = {		//[블록 종류][회전][행][렬]
	//막대모양
	1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,   1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,   1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,   1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,

	//네모모양
	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,

	//'ㅓ' 모양
	0,1,0,0,1,1,0,0,0,1,0,0,0,0,0,0,	1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,	0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,

	//'ㄱ'모양
	1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,	1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,	0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,

	//'ㄴ' 모양
	1,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,	1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,0,	1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,

	//'Z' 모양
	1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,	1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,

	//'S' 모양
	0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,	0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0
};
Block::Block()
{
	this->shape = rand() % 7;
	this->angle = 0;
	this->x = 5;
	this->y = -3;
}

Block::Block(int _x, int _y)
{
	this->shape = rand() % 7;
	this->angle = 0;
	this->x = _x;
	this->y = _y;
}


Block::~Block()
{
}

void Block::changeCurBlock(Block& next)
{
	this->shape = next.shape;
	this->angle = 0;
	this->x = 5;
	this->y = -3;
}
void Block::makeNewBlock(int _rate)
{
	int i;
	i = rand() % 100;
	if (i <= _rate)
	{
		this->shape = 0;
	}
	else
		this->shape = (rand() % 6) + 1;

	this->angle = 0;
	this->x = 15;
	this->y = 1;
}
void Block::printBlock()
{
	int i, j;

	switch (shape)
	{
	case 0:
		SetColor(RED);
		break;
	case 1:
		SetColor(BLUE);
		break;
	case 2:
		SetColor(SKY_BLUE);
		break;
	case 3:
		SetColor(WHITE);
		break;
	case 4:
		SetColor(YELLOW);
		break;
	case 5:
		SetColor(VOILET);
		break;
	case 6:
		SetColor(GREEN);
		break;
	}

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if ((j + y) < 0)
				continue;

			if (block_frame[shape][angle][j][i] == 1)
			{
				gotoxy((i + x) * 2 + 5, j + y + 1);
				printf("■");

			}
		}
	}
	SetColor(BLACK);
	gotoxy(77, 23);

}

void Block::removeBlock()
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (block_frame[shape][angle][j][i] == 1)
			{
				gotoxy((i + x) * 2 + 5, j + y + 1);
				printf("  ");
				//break;

			}
		}
	}
}

void Block::moveRight()
{
	x++;
}

void Block::moveLeft()
{
	x--;
}

void Block::rotate()
{
	angle = (angle + 1) % 4;
}

void Block::moveUp()
{
	y--;
}

void Block::moveDown()
{
	y++;
}

int Block::getShape()
{
	return this->shape;
}

int Block::getAngle()
{
	return this->angle;
}

int Block::getX()
{
	return this->x;
}

int Block::getY()
{
	return this->y;
}

void Block::setShape(int _shape)
{
	shape = _shape;
}

void Block::setAngle(int _angle)
{
	angle = _angle;
}

void Block::setX(int _x)
{
	x = _x;
}

void Block::setY(int _y)
{
	y = _y;
}

Block Block::operator=(Block& next)
{
	delete this;
	Block temp;
	temp.shape = next.shape;
	return temp;
}
