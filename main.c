#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>

#define WIDTH 128
#define HEIGHT 32
#define SIZE 6
#define TIME_LIMIT 5

void gotoxy(int, int);
void show_string(char *);
void ShowBox();
void ShowHealth(int);
void setColor(unsigned short, unsigned short);

int main() {
	char word[SIZE], ch, input[SIZE];
	int s_time, j = 0;
	int health = 10;


	system("mode con cols=128 lines=32");
	srand(time(0));
	ShowHealth(health);
	show_string(word);
	s_time = time(0);
	while (1)
	{
		
		if (time(0) == s_time + TIME_LIMIT)
		{
			system("cls");
			health -= 2;
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
			if (j > 0)
			{
				if (ch == 8)
				{
					printf("\b \b");
					input[j] = 0;
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
				health--;

			system("cls");
			ShowHealth(health);
			show_string(word);
			s_time = time(0);
			j = 0;
		}
	}

	return 0;
}

void gotoxy(int x, int y)
{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void show_string(char* w)
{
	int i, x=15;
	
	ShowBox();
	for (i = 0; i <= 4; i++)
		w[i] = 'a' + (rand() % 26);
	w[i] = 0;
	gotoxy(127/2 - 5/2, 10);
	printf("%s\n", w);
	gotoxy(127/2 - 5/2, 19);
}

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

void ShowHealth(int health)					// 색깔 버그 고치기
{
	int i;
	
	gotoxy(WIDTH - 30, 5);
	printf("                    ");
	gotoxy(WIDTH - 35, 5);
	printf("HP : ");
	setColor(12,0);
	for (i = 0; i < health; i++)
		printf("\u2665");
	setColor(15, 0);
}

void setColor(unsigned short text, unsigned short back)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}