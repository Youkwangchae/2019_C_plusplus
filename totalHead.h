#pragma once

#include<iostream>
#include<ctime>
#include<conio.h>
#include<cstdlib>
#include<iomanip>
#include"Color.h"
#include<fstream>
#pragma warning(disable:4996)
using namespace std;
#define EXT_KEY         0xffffffe0   //확장키 인식값 
#define KEY_LEFT      0x4b
#define KEY_RIGHT      0x4d
#define KEY_UP         0x48
#define KEY_DOWN      0x50
int gotoxy(int x, int y);//나중에 함수 본문도 옮기는게 좋을 듯
void SetColor(int color);

const int ab_x = 5;
const int ab_y = 1;
//void printAscii(string fname, int x, int y)
//{
//	ifstream File(fname);
//
//	if (File)                      //Check if everything is good
//	{
//		while (File.good())
//		{
//			gotoxy(x, y);
//			std::string line;                  //Temp line
//			std::getline(File, line);        //Get temp line
//			//TempLine += "\n";                      //Add newline character
//			cout << line;
//			y++;                //Add newline
//		}
//	}
//	else                           //Return error
//	{
//		cout << "파일 읽기 오류" << endl;
//	}
//
//	File.close();
//}