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
		cout << endl << "���� ������ ���� �Է����ּ���!" << endl;
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
		cout << "y�� n�߿����� �Է��ϼ���!" << endl;
		system("pause");
		return 100;
	}
	if (ch == 'y' || ch == 'n')
		return 0;
	else
	{
		cout << "y�� n�߿����� �Է��ϼ���!" << endl;
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
		cout << "�Է��� ���� Ȯ���ϼ���!!" << endl;
		system("pause");
		return 100;
	}
}

void Map::set ()
{
	while (true)
	{
		cout << "���� ���� ���� ���̸� �Է��ϼ��� :";
		cin >> x>>y;
		
		check = Check(x);//������ �ƴ� �����͸� �Է��ϴ� ���� ó��
		if (check == 100)
			continue;
		else
		{
			check = range(0, x, 100);//���� ������ �ƴ� �����͸� �Է��ϴ� ���� ó��
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
		{check = range(0, y, 100);//���� ������ �ƴ� �����͸� �Է��ϴ� ���� ó��
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
		cout << "��ź ������ �Է��ϼ��� :";
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
	string icons[] = { "��", "��","��" };
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
	cout << "���ӿ��� �¸��ϼ̽��ϴ�!" << endl;
	cout << "�ڡڡڡڡڡڡڡڡ�" << endl;
	cout << "�ڡڡڡڡڡڡڡڡ�" << endl;
}

void Map::play()
{
	system("cls");
	cout << "�ڡڡڡڡڡڡڡڡڡڡڡڡ�" << endl;
	cout << "�ڡڡ� ����ã����� �ڡڡ�" << endl;
	cout << "�ڡڡڡڡڡڡڡڡڡڡڡڡ�" << endl;
	system("pause");
	do
	{
		count = 100;
		system("cls");
		showmap();
		cout << "��ġ�� �Է��ϼ��� ==> ";
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
			cout << "���ӿ��� ���̳׿�" << endl;
			deletemap();
			return;
		}

		else if (map[x - 1][y - 1] == 0)
		{
			char ch;
			
				cout << "3x3 ��ħ����� ���� �ǰ���??(y/n) : ";
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
				cout << "�޸� ����� ���� �ǰ���??(y/n) : ";
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
			cout << "�̹� ������ ���Դϴ�!" << endl;
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
	cout << "ǥ���ϰ� ���� ���� ��ǥ�� �Է��ϼ���: ";
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
				cout << "���� ������ ���� ���� �������ּ���!"<<endl;
		}
	}	
	}
}
