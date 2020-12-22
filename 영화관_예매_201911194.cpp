#include <iostream>
#include <string>
using namespace std;

void welcome()//영화 예매 초기 화면 출력
{
	cout << "=================================" << endl;
	cout << "★★★★ KU광채 시네마 ★★★★" << endl;
	cout << "=================================" << endl;
	cout << "1) 영화 예매 2) 예매 취소 3) 예매 확인 4) 종료" << endl;
	cout << "원하시는 기능을 선택하세요 : ";
}

int conduct()//사용자가 입력한 값이 원하지 않는 타입의 값인 경우 버퍼를 비우고 100을 출력.
{
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << endl<<"입력한 값을 확인하세요!" << endl;
		return 100;
	}
}
int checknum(int movie , int person[])//좌석 매진여부를 알려줌.
{
	if (person[movie - 1] == 25)
	{
		cout << "좌석이 매진되었습니다.";
		return 200;
	}
}

void intro(int person[],string movies[], int i)//각 영화의 이름과 좌석 현황을 보여줌.
{
	for (int i = 0; i < 3; i++)
	{
		cout << "*" << (i + 1) << "관* " << movies[i] << '\t';
		((person[i] != 25) ? cout << person[i] << "/25" << endl : cout << "매진" << endl);
	}
}
void map()//영화관 좌석 안내도의 맨 첫 줄을 출력함.
{
	for (int i = 0; i < 6; i++)
	{
		if (i != 0)
			cout << i;
		else
			cout << "※";
		cout << '\t';
	}
	cout << endl;
}
void notice(int movie,int num, int person[], int theater[][5][5], int reserve[][25])//movie는 영화 선택 값, num은 예약한 사람 수
{
	string row[5] = { "A","B","C","D","E" };//범위 내에 입력한 것인지 체크하기 위한 용도
	string col[5] = { "1","2","3","4","5" };//범위 내에 입력한 것인지 체크하기 위한 용도
	int find = 0;//범위 내에 입력한 것인지 체크하기 위한 용도
	map();
	int k = 0;
	int c = 0;
	int d = 0;
	while (k != num)//입력한 사람 수 만큼 예약을 반복 실행.
	{
		for (int i = 0; i < 5; i++)//좌석 예약현황을 보여줌.
		{
			cout << row[i] << '\t';
			for (int j = 0; j < 5; j++)
			{
				cout << ((theater[movie-1][i][j] == 1) ? "●" : "○");//좌석을 예약한 경우 "●" , 예약하지 않은 경우 "○" 출력.
				cout << '\t';
			}
			cout << endl;
		}
		cout << endl;
		cout << "좌석 입력 :(ex. A 1과 같이 한 자리씩 입력해주세요. /종료시 0 0) ";
		string x, y;//사용자가 입력한 좌석의 열과 행 정보를 저장.
		cin >> y >> x;
		if (y.length() > 2 || x.length() > 2)
		{
			cout << "입력한 값을 확인하시고, 다시 입력하세요. : " << endl;//사용자가 입력한 좌석의 열과 행 정보는 길이가 1이어야 함.
			continue;
		}
		if ((x == "0") && (y == "0"))
		{
			cout << "예약 프로그램 종료\n";//사용자가 "0 0"을 입력하면 영화 예매 종료.
			system("pause");
			break;
		}
		for (int i = 0; i < 5; i++)
		{
			if (y == row[i]) {//사용자가 입력한 좌석의 열 정보가 A에서 E사이의 대문자 알파벳인지 확인
				find++;
				c = i;
			}
		}
		for(int j=0;j<5;j++)
		{	if( x == col[j]){//사용자가 입력한 좌석의 행 정보가 1에서 5사이의 숫자인지 확인
				find++;
				d = j;
			}
		}
		if (find != 2)//사용자가 입력한 좌석의 열과 행 정보가 원하지 않는 범위인 경우 다시 입력하도록 함.
		{
			cout << "입력된 값을 확인하시고, 다시 입력하세요. : "<<endl<<endl;
			find = 0;
			continue;
		}
		if ((theater[movie-1][c][d]) == 0)//사용자가 입력한 좌석이 예약이 안 되어 있는 경우 예약처리.
		{
			person[movie-1]++;
			theater[movie-1][c][d] = 1;
			cout << "예약 완료했습니다. ";
			cout << "예약번호 : " << (movie-1)*25+c * 5 +d+1;
			reserve[movie-1][c * 5 + d] = (movie - 1) * 25 + c * 5 + d + 1;
			k++;
			find = 0;
		}
		else//사용자가 입력한 좌석이 예약이 되어 있는 경우 다시 예약하도록 함.
		{
			cout << "이미 예약이 된 자리입니다."<<endl;
			find = 0;
			continue;
		}
		cout << endl;
		system("pause");
	}
}

void cancel(int SEATS, int person[], int theater[][5][5], int reserve[][25])//사용자가 예매 취소를 선택한 경우 작동.
{
	if (theater[((SEATS-1) / 25)][((SEATS-1)% 25) / 5 ][((SEATS-1) % 25) % 5] == 1)//사용자가 입력한 예약번호의 자리가 예약된 경우
	{
		theater[((SEATS-1) / 25)][((SEATS-1) % 25) / 5 ][((SEATS - 1) % 25) % 5 ] = 0;//해당 자리의 예매를 취소.
		cout << "예약 취소 완료되었습니다." << endl;
		reserve[(SEATS - 1) / 25][SEATS-1 % 25] = 0;
		person[(SEATS-1) / 25]--;
		system("pause");
	}
	else//사용자가 입력한 예약번호의 자리가 예약되지 않은 경우
	{
		cout << "해당 자리는 예약된 자리가 아닙니다." << endl;
		system("pause");
	}
}

int checknum(int a, int b, int c)//사용자가 입력한 값이 범위 내의 값인지 확인.
{
	if (a > b || a < c)//입력 값이 범위를 벗어난 경우
	{
		cout << "입력하신 값을 확인하세요!"<<endl;
		return 300;
	}
}

int main()
{
	cout << "==================" << endl;
	cout << "201911194 유광채"<<endl;
	cout << "==================" << endl;
	int choice = 0;//영화 예매-예매 취소-예매 확인 중 사용자의 입력값을 받음.
	int check = 0;//사용자가 입력한 값이 변수 타입과 범위에 맞는지를 판단해 정수값을 출력하는 함수들의 출력값을 받음.
	int reserve[3][25] = { 0, };//각 영화관 별 좌석의 예약번호를 저장, 사용자가 예매 확인시 입력한 예약번호와 비교. 
	int theater[3][5][5] = { 0, };//각 영화관 별 좌석의 예약 여부를 저장.
	int person[3] = { 0, };// 각 영화관 별 예약한 사람 수를 저장.
	string movies[3] = { "리얼", "자전차왕 엄복동", "클레멘타인" };//영화관에서 상영되는 영화들.
	do
	{
		cout << endl;
		welcome();//영화 예매 초기 화면 출력
		cin >> choice;
		switch (choice)
		{
		case 1://영화 예매
		{
			intro(person, movies, 0);//각 영화의 이름과 좌석 현황을 보여줌.

			int movie = 0;
			int num = 0;

			cout << "예매하실 영화를 선택해주세요 :";
			cin >> movie;
			check = conduct();//정수 값으로 영화관을 입력했는지 확인
			if (check == 100)
				continue;
			check = checknum(movie,3,1);//영화관 입력 범위를 확인
			if (check == 300)
				continue;

			cout << "예매하실 인원 수를 선택해주세요 : ";
			cin >> num;
			check = conduct();//정수 값으로 인원 수를 입력했는지 확인
			if (check == 100)
				continue;
			check = checknum(num, 25, 1);//인원 수 입력 범위를 확인
			if (check == 300)
				continue;

			switch (movie)//입력한 영화 값에 따른 예매 진행
			{
			case 1:
			{
				check = checknum(movie, person);//입력한 영화관의 매진여부 확인.
				if(check ==200)
				break;
				notice(movie, num, person, theater, reserve);//영화관의 예매 진행.
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
		{//예약을 취소하려면 예약번호를 입력하도록 사용자에게 안내한다.
			//사용자가 예약번호를 입력하면, 배열 reserve에서 그 예약번호 자리에 0을 저장하고, 배열 theater에도 그 예매자리에 1대신 0을 저장하도록 한다.
			int SEATS = 0;
			cout << "예매를 취소하시려면 예약번호를 입력해주세요 : ";
			cin >> SEATS;
			check =conduct();//입력한 예매 번호가 정수인지 확인.
			if (check == 100)
				continue;
			check = checknum(SEATS, 75, 1);//예매 번호 입력 범위를 확인
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
		{//case 1에서 사용자에게 예약번호를 알려주고, 이를 배열 reserve에 저장한다. 이 reserve에 저장된 값은 계속 남아있어야 한다.
		//case 3시작후, 사용자가 예약번호를 입력한 것을 변수 seat에 저장하고, reserve와 seat가 같은 값인 경우 예약된 자리를 안내한다.
			int counts = 0;
			int seat = 0;
			cout << "예약번호를 입력해주세요 :";
			cin >> seat;
			conduct();
			check = checknum(seat, 75, 1);
			if (check== 300)
				continue;

				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 25; j++)
					{
						if (seat == reserve[i][j])//예약한 입력번호가 예매완료된 좌석과 일치하는지 확인
							counts++;
					}
				}

			if (counts == 0)//일치하는 좌석이 없는 경우
			{
				cout << "예약정보를 찾을 수 없습니다." << endl;
				system("pause");
				system("cls");
				break;
			}
			int theaters = (seat - 1) / 25;
			string name[5] = { "A","B","C","D","E" };
			cout << "================================================================" << endl;
			cout << "==                                                            ==" << endl;
			cout << "================================================================" << endl;
			cout << "			예약 영화 >> " << movies[theaters] << "" << endl;
			cout << "			상영관 >> " << theaters + 1 << " 관" << endl;
			cout << "			예약 좌석 >> " << name[((seat - 1) % 25) / 5] << (seat - 1) % 5 + 1 << endl;
			cout << "================================================================" << endl;
			cout << "================================================================" << endl;
			cout << "================================================================" << endl; 
			cout << "================================================================" << endl;
			cout << "==                                                            ==" << endl;
			cout << "==                ★★★★ KU광채 시네마 ★★★★             ==" << endl;
			cout << "==              ★★★★ 즐거운 관람 되세요★★★★           ==" << endl;
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
				cout << "입력한 값을 확인하세요!" << endl;
				system("pause");
				system("cls");
			}
			continue;
		}
		}
		}while (choice != 4);
}