#include "Map.h"
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
using namespace std;

Map::Map()
{
}


Map::~Map()
{
}


int Map::Check(int num)
{
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << endl << "양의 정수로 값을 입력해주세요!" << endl;
		system("pause");
		return 100;
	}
	
}

int Map::Check(char ch)
{
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "y와 n중에서만 입력하세요!" << endl;
		system("pause");
		return 100;
	}
	if (ch == 'y' || ch == 'n')
		return 0;
	else
	{
		cout << "y와 n중에서만 입력하세요!" << endl;
		system("pause");
		return 100;
	}
}

int Map::range(int a, int b, int c)
{
	if (a < b&&b < c)
		return 0;
	else
	{
		cout << "입력한 값을 확인하세요!!" << endl;
		system("pause");
		return 100;
	}
}

void Map::set ()
{
	while (true)
	{
		cout << "맵의 가로 세로 길이를 입력하세요 :";
		cin >> x>>y;
		
		check = Check(x);//정수가 아닌 데이터를 입력하는 예외 처리
		if (check == 100)
			continue;
		else
		{
			check = range(0, x, 100);//양의 정수가 아닌 데이터를 입력하는 예외 처리
			if (check == 100)
				continue;
			else
			{
				this->col = x;
			}
		}
		check = Check(y);
		if (check == 100)
			continue;
		else
		{check = range(0, y, 100);//양의 정수가 아닌 데이터를 입력하는 예외 처리
			if (check == 100)
				continue;
			else
			{
			this->row = y;
			break;
			}
		}
		
	}
}

int** Map::makeMap()
{
	
	for (int i = 0; i < row; i++)
	{
		map = new int*[row];
		open = new int*[row];
		for (int i = 0; i < row; i++)
		{
			map[i] = new int[col];
			open[i] = new int[col];
			for (int j = 0; j < col; j++)
			{
				map[i][j] = 0;
				open[i][j] = 0;
			}
		}
	}
	return map;
}

void Map::hidemap()
{
	int count = 0;
	while (count != bomb)
	{
		srand((unsigned)time(NULL));
		int x = rand() % row;
		int y = rand() % col;
		if (map[x][y] != 1)
		{map[x][y] = 1;
		count++;
	}
		else
			continue;
	}

}

void Map::setBomb()
{
	while (true)
	{
		cout << "폭탄 개수를 입력하세요 :";
		cin >> num;
		check = Check(num);
		if (check == 100)
			continue;
		else
		{
			if (check == 100)
				continue;
			else
			{
				check = range(0, num, row*col);
				if (check == 100)
					continue;
				else
			{
			this->bomb = num;
			break;
			}
			}
			
		}
	}
}

void Map::showmap()
{
	cout << ' '<<' ';
	for (int i = 1; i < col + 1; i++)
	{
		if (i < 10)
cout << i << ' ';
		else cout << i;
	}
	cout << endl;
	string icons[] = { "□", "♣","■" };
	for (int i = 0; i < row; i++)
	{
		if (i < 9)
			cout << (i + 1) << " ";
		else cout << (i + 1);
		for (int j = 0; j < col; j++)
		{
			if (open[i][j] == 2)
				cout << icons[1];
			else {
				if (map[i][j] == 2)
					cout << icons[2];
				else
					cout << icons[0];
			}
		}
		cout << endl;
	}
}

void Map::endgame()
{
	setColor(3, 0);
	system("pause");
	cout << "게임에서 승리하셨습니다!" << endl;
	cout << "★★★★★★★★★" << endl;
	cout << "★★★★★★★★★" << endl;
}

void Map::play()
{
	system("cls");
	cout << "★★★★★★★★★★★★★" << endl;
	cout << "★★★ 지뢰찾기게임 ★★★" << endl;
	cout << "★★★★★★★★★★★★★" << endl;
	system("pause");
	do
	{
		count = 100;
		system("cls");
		showmap();
		cout << "위치를 입력하세요 ==> ";
		cin >> x >> y;
		check = Check(x);
		if (check == 100)
			continue;
		else
		{
			check = range(0, x, row + 1);
			if (check == 100)
				continue;}
		check = Check(y);
		{if (check == 100)
			continue;
		else
		{
			check = range(0, y, col + 1);
			if (check == 100)
				continue;}
		}
		if (map[x - 1][y - 1] == 1)
		{
			setColor(4, 0);
			cout << "게임에서 지셨네요" << endl;
			deletemap();
			return;
		}

		else if (map[x - 1][y - 1] == 0)
		{
			char ch;
			
				cout << "3x3 펼침기능을 쓰실 건가요??(y/n) : ";
				cin >> ch;
				check = Check(ch);
				if (check == 100)
					continue;
				else
				{
					switch (ch){
					case 'y':
						hint(x, y);
						break;
					case 'n':
						map[x - 1][y - 1] = 2;
						open[x - 1][y - 1] = 1;
						break;
					}
				}system("cls");
				showmap();
				cout << "메모 기능을 쓰실 건가요??(y/n) : ";
				cin >> ch;
				check = Check(ch);
				if (check == 100)
					continue;
				else
				{
					if(ch=='y')
					{memo();
					}
				}
				count = 0;
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < col; j++)
				{
					if (map[i][j]==0 )
						count++;}
			}
		}
		else
		{
			cout << "이미 선택한 곳입니다!" << endl;
			system("pause");
		}
	} while (count !=0);
	showmap();
	endgame();
	deletemap();
}
void Map::setColor(short color, short bgcolor)
{
	color &= 0xf;
	bgcolor &= 0xf;
	static HANDLE std_output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(std_output_handle, bgcolor << 4 | color);
}

void Map::hint(int x, int y)
{
	if (x >= 1 && y >= 1 && x <= row && y <= col)
	{
		{
			map[x - 1][y - 1] = 2;
			open[x - 1][y - 1] = 1;
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if ((x - 2 + i >= 0 && x - 2 + i < row) && (y - 2 + j >= 0 && y - 2 + j < col))
					{
						if (map[x - 2 + i][y - 2 + j] == 0)
						{
							map[x - 2 + i][y - 2 + j] = 2;
							open[x - 2 + i][y - 2 + j] = 1;
						}
					}
				}
			}
		}
	}
	else
		return;
}

void Map::deletemap()
{
	for (int i = 0; i < row; i++)
	{
			delete[] map[i];
	}	delete map;
}

void Map::memo()
{
	cout << "표시하고 싶은 곳의 좌표를 입력하세요: ";
	cin >> x >> y;
	check = Check(x);
	if (check != 100)
	{check = range(0, x, row + 1);
		if (check != 100)
			check = Check(y);
		{if (check != 100)
			check = range(0, y, col + 1);
		if (check != 100)
		{
			if (open[x - 1][y - 1] == 0)
				open[x - 1][y - 1] = 2;
			else
				cout << "아직 열리지 않은 곳을 선택해주세요!"<<endl;
		}
	}	
	}
}
