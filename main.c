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
void ShowScreen();

int main() {
	char word[SIZE], ch, input[SIZE];
	int s_time, j = 0;
	int health = 0;

	system("mode con cols=128 lines=32");
	srand(time(0));
	show_string(word);
	s_time = time(0);
	while (1)
	{
		
		if (time(0) == s_time + TIME_LIMIT)
		{
			system("cls");
			show_string(word);
			s_time = time(0);
			j = 0;
		}

		if (_kbhit())
		{
			ch = _getch();
			if (ch == 27)
				break;
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

			system("cls");
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
	ShowScreen();
	for (i = 0; i <= 4; i++)
		w[i] = 'a' + (rand() % 26);
	w[i] = 0;
	gotoxy(127/2 - 5/2, 10);
	printf("%s\n", w);
	gotoxy(127/2 - 5/2, 19);
}

void ShowScreen()
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