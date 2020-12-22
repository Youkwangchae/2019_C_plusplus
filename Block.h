#pragma once
#include"totalHead.h"
class Block
{

private:
	int shape;
	int angle;
	int x;
	int y;

public:
	static char block_frame[7][4][4][4];
	Block();
	Block(int _x, int _y);
	~Block();

	void changeCurBlock(Block& next);
	void makeNewBlock(int _rate);

	void printBlock();
	void removeBlock();
	void moveRight();
	void moveLeft();
	void rotate();
	void moveUp();
	void moveDown();
	int getShape();
	int getAngle();
	int getX();
	int getY();
	void setShape(int _shape);
	void setAngle(int _angle);
	void setX(int _x);
	void setY(int _y);

	Block operator=(Block& next);
};

