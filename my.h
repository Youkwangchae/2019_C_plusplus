#pragma once
#include<Windows.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#include<string>
#include<ostream>
#include<conio.h>
#include<iomanip>
#include<iostream>
#include<fstream>
#include<cstdlib>
#include <gdiplus.h>
#include <MMSystem.h>
#include <conio.h>
#include "Color.h"
#pragma comment(lib,"Winmm.lib")
using namespace Gdiplus;
using namespace std;


#define EXT_KEY         0xff   //확장키 인식값 
#define KEY_LEFT      0x4b
#define KEY_RIGHT      0x4d
#define KEY_UP         0x48
#define KEY_DOWN      0x50

const int plus_x = 0;
const int plus_y = 0;

const int print_x = 44;
const int print_y = 21;

void gotoxy(int _x, int _y);
void setCursor();
void SetColor(int color);
void printAscii(string fname, int x, int y);
void printString(string sname, int score, int x, int y);
void setCursorView(bool visible);
void intro();
void outro();
void youdie();

