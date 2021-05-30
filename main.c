/*
	Bug Report
	SetColor 사용 시 처음 박스 모양 오류 - 해결
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>

//========================== 전처리기
// 김태환
#define WIDTH 128
#define HEIGHT 32
#define SIZE 6
#define TIME_LIMIT 5

// 김태영
#define CHILD_CLEAR 150         /*유아기 클리어 점수*/
#define ADOLESENT_CLEAR 300      /*청년기 클리어 점수*/
#define OLD_CLEAR 450         /*노년기 클리어 점수*/
#define LIMIT_TIME 15         /*단어하나당 주어진 시간*/

// 조현영


// 김재윤


//========================== 함수 선언
// 김태환
void gotoxy(int, int);							// 커서 이동	
void show_string(char *);						// 문자열 출력
void ShowBox();									// 박스 출력
void ShowHealth(int);							// 체력 출력
void SetColor(unsigned short, unsigned short);	// 색 변경

// 김태영
void time_score();            //남은 시간에 따른 점수
void show_score_CHILD();      //유아기 점수 계산하고 출력하는 함수
void show_score_ADOLESENT();   //청년기 점수 계산하고 출력하는 함수
void show_score_OLD();         //노년기 점수 계산하고 출력하는 함수
int update_correct();         //맞은 개수 +1하고 저장하는 함수
int update_difficult();         //틀린 개수 +1하고 저장하는 함수 <=== 틀린 개수가 아니라 어려운 거 맞은 개수??

// 조현영


// 김재윤


//========================== 전역 변수
// 김태환


// 김태영
int score = 0;               //점수 저장 변수, 0으로 초기화
int correct = 0, difficult = 0;//correct: 맞은 기본단어 개수, difficult: 맞은 어려운 단어 개수
int timescore;               //남는 시간에 따른 추가 점수
int remain_time;            //타이핑 후 남은 시간

// 조현영


// 김재윤

int main() {
	char word[SIZE], ch, input[SIZE];
	int s_time, j = 0;
	int health = 10;


	system("mode con cols=128 lines=32");
	srand(time(0));
	
	
	ShowBox();
	ShowHealth(health);
	show_string(word);
	
	s_time = time(0);
	while (1)
	{
		if (time(0) == s_time + TIME_LIMIT)
		{
			system("cls");
			health -= 2;	// 시간 초과 체력 -2
			ShowBox();
			ShowHealth(health);
			show_string(word);
			s_time = time(0);
			j = 0;
		}

		if (_kbhit())
		{
			ch = _getch();
			if (ch == 27)
				break;
			if (ch == 8)
			{
				if (j > 0)
				{
					printf("\b \b");
					j--;
				}
			}
			if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
			{
				printf("%c", ch);
				input[j] = ch;
				j++;
			}
		}
		
		if (j >= SIZE - 1)
		{
			input[SIZE - 1] = 0;
			if (!strcmp(word, input))
			{
				printf("\n축하합니다.\n");
				Sleep(1000);
			}
			else
				health--;	// 오타 체력 -1

			system("cls");
			ShowBox();
			ShowHealth(health);
			show_string(word);
			s_time = time(0);
			j = 0;
		}

		if (health <= 0)
			break;
	}

	return 0;
}



// 커서 이동
void gotoxy(int x, int y)
{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
// 문자열 출력
void show_string(char* w)
{
	int i, x=15;
	
	for (i = 0; i <= 4; i++)
		w[i] = 'a' + (rand() % 26);
	w[i] = 0;
	gotoxy(127/2 - 5/2, 10);
	printf("%s\n", w);
	gotoxy(127/2 - 5/2, 19);
}
// 박스 출력
void ShowBox()
{
	int x = 9, y = 8, i;

	gotoxy(x, y);
	printf("┌");
	for (i = 0; i < 106; i++)
		printf("─");
	printf("┐");
	for (i = 0; i < 3; i++)
	{
		x = 9;
		y++;
		gotoxy(x, y);
		printf("│");
		x = 116;
		gotoxy(x, y);
		printf("│");
	}
	x = 9;
	y = 12;
	gotoxy(x, y);
	printf("└");
	for (i = 0; i < 106; i++)
		printf("─");
	printf("┘");

	
	x = 9;
	y = 17;
	gotoxy(x, y);
	printf("┌");
	for (i = 0; i < 106; i++)
		printf("─");
	printf("┐");
	for (i = 0; i < 3; i++)
	{
		x = 9;
		y++;
		gotoxy(x, y);
		printf("│");
		x = 116;
		gotoxy(x, y);
		printf("│");
	}
	x = 9;
	y = 21;
	gotoxy(x, y);
	printf("└");
	for (i = 0; i < 106; i++)
		printf("─");
	printf("┘");
}
// 체력 출력
void ShowHealth(int health)
{
	int i;
	
	gotoxy(WIDTH - 30, 5);
	printf("                    ");	// 하트 삭제
	gotoxy(WIDTH - 37, 5);
	SetColor(15, 4);	// 글자 하양, 배경 진한 빨강
	printf(" HP ");
	SetColor(15, 0);	// 글자 하양, 배경 검정
	printf(" : ");
	SetColor(12,0);		// 글자 빨강, 배경 검정
	for (i = 0; i < health; i++)
		printf("\u2665");	// 하트 출력
	SetColor(15, 0);	// 글자 하양, 배경 검정
}
// 색 변경
void SetColor(unsigned short text, unsigned short back)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}


// 김태영
// 남은 시간에 따른 점수
void time_score()
{
	timescore = 150 * (remain_time / LIMIT_TIME);
	score += timescore;
}
// 유아기 점수 출력
void show_score_CHILD()
{
	score += 50 * update_correct() + 80 * update_difficult() + CHILD_CLEAR;
	printf("점수는 %d 점 입니다.", score);
}
// 청년기 점수 출력
void show_score_ADOLESENT()
{
	score += 50 * update_correct() + 80 * update_difficult() + ADOLESENT_CLEAR;
	printf("점수는 %d 점 입니다.", score);
}
// 노년기 점수 출력
void show_score_OLD()
{
	score += 50 * update_correct() + 80 * update_difficult() + OLD_CLEAR;
	printf("점수는 %d 점 입니다.", score);
}
// 맞은 개수 +1
int update_correct()
{
	correct++;         //기본 단어 맞은 개수 +1
	return correct;
}
// 틀린 개수 +1
int update_difficult()
{
	difficult++;      //어려운단어 맞은 개수 +1
	return difficult;
}