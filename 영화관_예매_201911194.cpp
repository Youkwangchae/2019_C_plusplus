#include <iostream>
#include <string>
using namespace std;

void welcome()//��ȭ ���� �ʱ� ȭ�� ���
{
	cout << "=================================" << endl;
	cout << "�ڡڡڡ� KU��ä �ó׸� �ڡڡڡ�" << endl;
	cout << "=================================" << endl;
	cout << "1) ��ȭ ���� 2) ���� ��� 3) ���� Ȯ�� 4) ����" << endl;
	cout << "���Ͻô� ����� �����ϼ��� : ";
}

int conduct()//����ڰ� �Է��� ���� ������ �ʴ� Ÿ���� ���� ��� ���۸� ���� 100�� ���.
{
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << endl<<"�Է��� ���� Ȯ���ϼ���!" << endl;
		return 100;
	}
}
int checknum(int movie , int person[])//�¼� �������θ� �˷���.
{
	if (person[movie - 1] == 25)
	{
		cout << "�¼��� �����Ǿ����ϴ�.";
		return 200;
	}
}

void intro(int person[],string movies[], int i)//�� ��ȭ�� �̸��� �¼� ��Ȳ�� ������.
{
	for (int i = 0; i < 3; i++)
	{
		cout << "*" << (i + 1) << "��* " << movies[i] << '\t';
		((person[i] != 25) ? cout << person[i] << "/25" << endl : cout << "����" << endl);
	}
}
void map()//��ȭ�� �¼� �ȳ����� �� ù ���� �����.
{
	for (int i = 0; i < 6; i++)
	{
		if (i != 0)
			cout << i;
		else
			cout << "��";
		cout << '\t';
	}
	cout << endl;
}
void notice(int movie,int num, int person[], int theater[][5][5], int reserve[][25])//movie�� ��ȭ ���� ��, num�� ������ ��� ��
{
	string row[5] = { "A","B","C","D","E" };//���� ���� �Է��� ������ üũ�ϱ� ���� �뵵
	string col[5] = { "1","2","3","4","5" };//���� ���� �Է��� ������ üũ�ϱ� ���� �뵵
	int find = 0;//���� ���� �Է��� ������ üũ�ϱ� ���� �뵵
	map();
	int k = 0;
	int c = 0;
	int d = 0;
	while (k != num)//�Է��� ��� �� ��ŭ ������ �ݺ� ����.
	{
		for (int i = 0; i < 5; i++)//�¼� ������Ȳ�� ������.
		{
			cout << row[i] << '\t';
			for (int j = 0; j < 5; j++)
			{
				cout << ((theater[movie-1][i][j] == 1) ? "��" : "��");//�¼��� ������ ��� "��" , �������� ���� ��� "��" ���.
				cout << '\t';
			}
			cout << endl;
		}
		cout << endl;
		cout << "�¼� �Է� :(ex. A 1�� ���� �� �ڸ��� �Է����ּ���. /����� 0 0) ";
		string x, y;//����ڰ� �Է��� �¼��� ���� �� ������ ����.
		cin >> y >> x;
		if (y.length() > 2 || x.length() > 2)
		{
			cout << "�Է��� ���� Ȯ���Ͻð�, �ٽ� �Է��ϼ���. : " << endl;//����ڰ� �Է��� �¼��� ���� �� ������ ���̰� 1�̾�� ��.
			continue;
		}
		if ((x == "0") && (y == "0"))
		{
			cout << "���� ���α׷� ����\n";//����ڰ� "0 0"�� �Է��ϸ� ��ȭ ���� ����.
			system("pause");
			break;
		}
		for (int i = 0; i < 5; i++)
		{
			if (y == row[i]) {//����ڰ� �Է��� �¼��� �� ������ A���� E������ �빮�� ���ĺ����� Ȯ��
				find++;
				c = i;
			}
		}
		for(int j=0;j<5;j++)
		{	if( x == col[j]){//����ڰ� �Է��� �¼��� �� ������ 1���� 5������ �������� Ȯ��
				find++;
				d = j;
			}
		}
		if (find != 2)//����ڰ� �Է��� �¼��� ���� �� ������ ������ �ʴ� ������ ��� �ٽ� �Է��ϵ��� ��.
		{
			cout << "�Էµ� ���� Ȯ���Ͻð�, �ٽ� �Է��ϼ���. : "<<endl<<endl;
			find = 0;
			continue;
		}
		if ((theater[movie-1][c][d]) == 0)//����ڰ� �Է��� �¼��� ������ �� �Ǿ� �ִ� ��� ����ó��.
		{
			person[movie-1]++;
			theater[movie-1][c][d] = 1;
			cout << "���� �Ϸ��߽��ϴ�. ";
			cout << "�����ȣ : " << (movie-1)*25+c * 5 +d+1;
			reserve[movie-1][c * 5 + d] = (movie - 1) * 25 + c * 5 + d + 1;
			k++;
			find = 0;
		}
		else//����ڰ� �Է��� �¼��� ������ �Ǿ� �ִ� ��� �ٽ� �����ϵ��� ��.
		{
			cout << "�̹� ������ �� �ڸ��Դϴ�."<<endl;
			find = 0;
			continue;
		}
		cout << endl;
		system("pause");
	}
}

void cancel(int SEATS, int person[], int theater[][5][5], int reserve[][25])//����ڰ� ���� ��Ҹ� ������ ��� �۵�.
{
	if (theater[((SEATS-1) / 25)][((SEATS-1)% 25) / 5 ][((SEATS-1) % 25) % 5] == 1)//����ڰ� �Է��� �����ȣ�� �ڸ��� ����� ���
	{
		theater[((SEATS-1) / 25)][((SEATS-1) % 25) / 5 ][((SEATS - 1) % 25) % 5 ] = 0;//�ش� �ڸ��� ���Ÿ� ���.
		cout << "���� ��� �Ϸ�Ǿ����ϴ�." << endl;
		reserve[(SEATS - 1) / 25][SEATS-1 % 25] = 0;
		person[(SEATS-1) / 25]--;
		system("pause");
	}
	else//����ڰ� �Է��� �����ȣ�� �ڸ��� ������� ���� ���
	{
		cout << "�ش� �ڸ��� ����� �ڸ��� �ƴմϴ�." << endl;
		system("pause");
	}
}

int checknum(int a, int b, int c)//����ڰ� �Է��� ���� ���� ���� ������ Ȯ��.
{
	if (a > b || a < c)//�Է� ���� ������ ��� ���
	{
		cout << "�Է��Ͻ� ���� Ȯ���ϼ���!"<<endl;
		return 300;
	}
}

int main()
{
	cout << "==================" << endl;
	cout << "201911194 ����ä"<<endl;
	cout << "==================" << endl;
	int choice = 0;//��ȭ ����-���� ���-���� Ȯ�� �� ������� �Է°��� ����.
	int check = 0;//����ڰ� �Է��� ���� ���� Ÿ�԰� ������ �´����� �Ǵ��� �������� ����ϴ� �Լ����� ��°��� ����.
	int reserve[3][25] = { 0, };//�� ��ȭ�� �� �¼��� �����ȣ�� ����, ����ڰ� ���� Ȯ�ν� �Է��� �����ȣ�� ��. 
	int theater[3][5][5] = { 0, };//�� ��ȭ�� �� �¼��� ���� ���θ� ����.
	int person[3] = { 0, };// �� ��ȭ�� �� ������ ��� ���� ����.
	string movies[3] = { "����", "�������� ������", "Ŭ����Ÿ��" };//��ȭ������ �󿵵Ǵ� ��ȭ��.
	do
	{
		cout << endl;
		welcome();//��ȭ ���� �ʱ� ȭ�� ���
		cin >> choice;
		switch (choice)
		{
		case 1://��ȭ ����
		{
			intro(person, movies, 0);//�� ��ȭ�� �̸��� �¼� ��Ȳ�� ������.

			int movie = 0;
			int num = 0;

			cout << "�����Ͻ� ��ȭ�� �������ּ��� :";
			cin >> movie;
			check = conduct();//���� ������ ��ȭ���� �Է��ߴ��� Ȯ��
			if (check == 100)
				continue;
			check = checknum(movie,3,1);//��ȭ�� �Է� ������ Ȯ��
			if (check == 300)
				continue;

			cout << "�����Ͻ� �ο� ���� �������ּ��� : ";
			cin >> num;
			check = conduct();//���� ������ �ο� ���� �Է��ߴ��� Ȯ��
			if (check == 100)
				continue;
			check = checknum(num, 25, 1);//�ο� �� �Է� ������ Ȯ��
			if (check == 300)
				continue;

			switch (movie)//�Է��� ��ȭ ���� ���� ���� ����
			{
			case 1:
			{
				check = checknum(movie, person);//�Է��� ��ȭ���� �������� Ȯ��.
				if(check ==200)
				break;
				notice(movie, num, person, theater, reserve);//��ȭ���� ���� ����.
				break;
			}
			case 2:
			{
				check = checknum(movie, person);
				if (check == 200)
				break;
				notice(movie, num, person, theater, reserve);
				break;
			}
			case 3:
			{
				check = checknum(movie, person);
				if (check == 200)
				break;
				notice(movie, num, person, theater, reserve);
				break;
			}

			}
			break;
		}
		case 2:
		{//������ ����Ϸ��� �����ȣ�� �Է��ϵ��� ����ڿ��� �ȳ��Ѵ�.
			//����ڰ� �����ȣ�� �Է��ϸ�, �迭 reserve���� �� �����ȣ �ڸ��� 0�� �����ϰ�, �迭 theater���� �� �����ڸ��� 1��� 0�� �����ϵ��� �Ѵ�.
			int SEATS = 0;
			cout << "���Ÿ� ����Ͻ÷��� �����ȣ�� �Է����ּ��� : ";
			cin >> SEATS;
			check =conduct();//�Է��� ���� ��ȣ�� �������� Ȯ��.
			if (check == 100)
				continue;
			check = checknum(SEATS, 75, 1);//���� ��ȣ �Է� ������ Ȯ��
			if (check == 300)
				continue;
			switch ((SEATS / 25)+1)
			{
			case 1:
			{
				cancel(SEATS, person, theater, reserve);
				break;
			}
			case 2:
			{cancel(SEATS, person, theater, reserve);
			break;
			}
			case 3:
			{
				cancel(SEATS, person, theater, reserve);
				break;
			}
			}
			break;
		}
		case 3:
		{//case 1���� ����ڿ��� �����ȣ�� �˷��ְ�, �̸� �迭 reserve�� �����Ѵ�. �� reserve�� ����� ���� ��� �����־�� �Ѵ�.
		//case 3������, ����ڰ� �����ȣ�� �Է��� ���� ���� seat�� �����ϰ�, reserve�� seat�� ���� ���� ��� ����� �ڸ��� �ȳ��Ѵ�.
			int counts = 0;
			int seat = 0;
			cout << "�����ȣ�� �Է����ּ��� :";
			cin >> seat;
			conduct();
			check = checknum(seat, 75, 1);
			if (check== 300)
				continue;

				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 25; j++)
					{
						if (seat == reserve[i][j])//������ �Է¹�ȣ�� ���ſϷ�� �¼��� ��ġ�ϴ��� Ȯ��
							counts++;
					}
				}

			if (counts == 0)//��ġ�ϴ� �¼��� ���� ���
			{
				cout << "���������� ã�� �� �����ϴ�." << endl;
				system("pause");
				system("cls");
				break;
			}
			int theaters = (seat - 1) / 25;
			string name[5] = { "A","B","C","D","E" };
			cout << "================================================================" << endl;
			cout << "==                                                            ==" << endl;
			cout << "================================================================" << endl;
			cout << "			���� ��ȭ >> " << movies[theaters] << "" << endl;
			cout << "			�󿵰� >> " << theaters + 1 << " ��" << endl;
			cout << "			���� �¼� >> " << name[((seat - 1) % 25) / 5] << (seat - 1) % 5 + 1 << endl;
			cout << "================================================================" << endl;
			cout << "================================================================" << endl;
			cout << "================================================================" << endl; 
			cout << "================================================================" << endl;
			cout << "==                                                            ==" << endl;
			cout << "==                �ڡڡڡ� KU��ä �ó׸� �ڡڡڡ�             ==" << endl;
			cout << "==              �ڡڡڡ� ��ſ� ���� �Ǽ���ڡڡڡ�           ==" << endl;
			cout << "==                                                            ==" << endl;
			cout << "================================================================" << endl;
			cout << "================================================================" << endl;
			cout << "================================================================" << endl;
			cout << "================================================================" << endl;
			cout << "================================================================" << endl;
			break;
		}
		default:
		{
			if (choice > 4 || choice < 1)
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "�Է��� ���� Ȯ���ϼ���!" << endl;
				system("pause");
				system("cls");
			}
			continue;
		}
		}
		}while (choice != 4);
}