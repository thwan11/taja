/*
	Bug Report
	SetColor ��� �� ó�� �ڽ� ��� ���� - �ذ�
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>

//========================== ��ó����
// ����ȯ
#define WIDTH 128
#define HEIGHT 32
#define SIZE 6
#define TIME_LIMIT 5

// ���¿�
#define CHILD_CLEAR 150         /*���Ʊ� Ŭ���� ����*/
#define ADOLESENT_CLEAR 300      /*û��� Ŭ���� ����*/
#define OLD_CLEAR 450         /*���� Ŭ���� ����*/
#define LIMIT_TIME 15         /*�ܾ��ϳ��� �־��� �ð�*/

// ������


// ������


//========================== �Լ� ����
// ����ȯ
void gotoxy(int, int);							// Ŀ�� �̵�	
void show_string(char *);						// ���ڿ� ���
void ShowBox();									// �ڽ� ���
void ShowHealth(int);							// ü�� ���
void SetColor(unsigned short, unsigned short);	// �� ����

// ���¿�
void time_score();            //���� �ð��� ���� ����
void show_score_CHILD();      //���Ʊ� ���� ����ϰ� ����ϴ� �Լ�
void show_score_ADOLESENT();   //û��� ���� ����ϰ� ����ϴ� �Լ�
void show_score_OLD();         //���� ���� ����ϰ� ����ϴ� �Լ�
int update_correct();         //���� ���� +1�ϰ� �����ϴ� �Լ�
int update_difficult();         //Ʋ�� ���� +1�ϰ� �����ϴ� �Լ� <=== Ʋ�� ������ �ƴ϶� ����� �� ���� ����??

// ������


// ������


//========================== ���� ����
// ����ȯ


// ���¿�
int score = 0;               //���� ���� ����, 0���� �ʱ�ȭ
int correct = 0, difficult = 0;//correct: ���� �⺻�ܾ� ����, difficult: ���� ����� �ܾ� ����
int timescore;               //���� �ð��� ���� �߰� ����
int remain_time;            //Ÿ���� �� ���� �ð�

// ������


// ������

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
			health -= 2;	// �ð� �ʰ� ü�� -2
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
				printf("\n�����մϴ�.\n");
				Sleep(1000);
			}
			else
				health--;	// ��Ÿ ü�� -1

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



// Ŀ�� �̵�
void gotoxy(int x, int y)
{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
// ���ڿ� ���
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
// �ڽ� ���
void ShowBox()
{
	int x = 9, y = 8, i;

	gotoxy(x, y);
	printf("��");
	for (i = 0; i < 106; i++)
		printf("��");
	printf("��");
	for (i = 0; i < 3; i++)
	{
		x = 9;
		y++;
		gotoxy(x, y);
		printf("��");
		x = 116;
		gotoxy(x, y);
		printf("��");
	}
	x = 9;
	y = 12;
	gotoxy(x, y);
	printf("��");
	for (i = 0; i < 106; i++)
		printf("��");
	printf("��");

	
	x = 9;
	y = 17;
	gotoxy(x, y);
	printf("��");
	for (i = 0; i < 106; i++)
		printf("��");
	printf("��");
	for (i = 0; i < 3; i++)
	{
		x = 9;
		y++;
		gotoxy(x, y);
		printf("��");
		x = 116;
		gotoxy(x, y);
		printf("��");
	}
	x = 9;
	y = 21;
	gotoxy(x, y);
	printf("��");
	for (i = 0; i < 106; i++)
		printf("��");
	printf("��");
}
// ü�� ���
void ShowHealth(int health)
{
	int i;
	
	gotoxy(WIDTH - 30, 5);
	printf("                    ");	// ��Ʈ ����
	gotoxy(WIDTH - 37, 5);
	SetColor(15, 4);	// ���� �Ͼ�, ��� ���� ����
	printf(" HP ");
	SetColor(15, 0);	// ���� �Ͼ�, ��� ����
	printf(" : ");
	SetColor(12,0);		// ���� ����, ��� ����
	for (i = 0; i < health; i++)
		printf("\u2665");	// ��Ʈ ���
	SetColor(15, 0);	// ���� �Ͼ�, ��� ����
}
// �� ����
void SetColor(unsigned short text, unsigned short back)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}


// ���¿�
// ���� �ð��� ���� ����
void time_score()
{
	timescore = 150 * (remain_time / LIMIT_TIME);
	score += timescore;
}
// ���Ʊ� ���� ���
void show_score_CHILD()
{
	score += 50 * update_correct() + 80 * update_difficult() + CHILD_CLEAR;
	printf("������ %d �� �Դϴ�.", score);
}
// û��� ���� ���
void show_score_ADOLESENT()
{
	score += 50 * update_correct() + 80 * update_difficult() + ADOLESENT_CLEAR;
	printf("������ %d �� �Դϴ�.", score);
}
// ���� ���� ���
void show_score_OLD()
{
	score += 50 * update_correct() + 80 * update_difficult() + OLD_CLEAR;
	printf("������ %d �� �Դϴ�.", score);
}
// ���� ���� +1
int update_correct()
{
	correct++;         //�⺻ �ܾ� ���� ���� +1
	return correct;
}
// Ʋ�� ���� +1
int update_difficult()
{
	difficult++;      //�����ܾ� ���� ���� +1
	return difficult;
}