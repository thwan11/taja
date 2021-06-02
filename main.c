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
#define SIZE 16
#define TIME_LIMIT 10      //  ���� �ʿ�

// ���¿�
#define CHILD_CLEAR 150         /*���Ʊ� Ŭ���� ����*/
#define ADOLESENT_CLEAR 300      /*û��� Ŭ���� ����*/
#define OLD_CLEAR 450         /*���� Ŭ���� ����*/

#define CURSOR1 40
#define CURSOR2 12
#define CURSOR3 55


//========================== �Լ� ����

void gotoxy(int, int);                     // Ŀ�� �̵�   
void show_string(char*);                  // ���ڿ� ���
void ShowBox();                           // �ڽ� ���
void ShowHealth(int);                     // ü�� ���
void SetColor(unsigned short, unsigned short);   // �� ����
void ShowScore();                        // ���� ���


void time_score();            //���� �ð��� ���� ����
void show_score_CHILD();      //���Ʊ� ���� ����ϰ� ����ϴ� �Լ�
void show_score_ADOLESENT();   //û��� ���� ����ϰ� ����ϴ� �Լ�
void show_score_OLD();         //���� ���� ����ϰ� ����ϴ� �Լ�
int update_correct();         //���� ���� +1�ϰ� �����ϴ� �Լ�
int update_difficult();         //Ʋ�� ���� +1�ϰ� �����ϴ� �Լ� <=== Ʋ�� ������ �ƴ϶� ����� �� ���� ����??

void Level(int);


void timeprint(int, int, int, int); //�����ð� ��� �Լ�

void Menu();
void Show_Box();
void stageEnding(char*); // �������� �߰� ��� �Լ�
void ending(int); //���� ���� ��� �Լ�

//========================== ���� ����

int timeLimit;


int score = 0;               //���� ���� ����, 0���� �ʱ�ȭ
int correct = 0, difficult = 0;//correct: ���� �⺻�ܾ� ����, difficult: ���� ����� �ܾ� ����
int timescore;               //���� �ð��� ���� �߰� ����
int remain_time;            //Ÿ���� �� ���� �ð�




char* word1[SIZE] = { "arrive","bicycle","bring","button",
                        "monkey","nurse","patent","strawberry",
                        "supermarket","tomorrow","yellow","yesterday",
                        "pediatric asthma","autointoxication",
                        "battered child syndrome" };

int main() {
    char word[SIZE], ch, input[SIZE];
    int s_time, j = 0, i = 0;
    int health = 10;
    int level = 3;   // 1, 2, 3 ��

    switch (level) {
    case 1: timeLimit = 15; break;
    case 2: timeLimit = 12; break;
    case 3: timeLimit = 9; break;
    }


    system("mode con cols=128 lines=32");
    srand(time(0));

    Menu();

    ShowBox();
    ShowScore();
    ShowHealth(health);
    show_string(&i);

    s_time = time(0);
    while (i <= 15)
    {
        remain_time = s_time + timeLimit - time(0);
        timeprint(timeLimit, remain_time, i, j, 0);
        if (time(0) == s_time + timeLimit)
        {
            system("cls");
            health -= 2;   // �ð� �ʰ� ü�� -2
            ShowBox();
            ShowScore();
            ShowHealth(health);
            i++;
            show_string(&i);
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

        if (j >= strlen(word1[i]))
        {
            input[strlen(word1[i])] = 0;
            if (!strcmp(word1[i], input))
            {
                i++;
                time_score();
                ShowScore();

                Sleep(1000);
            }
            else
                health--;   // ��Ÿ ü�� -1

            system("cls");
            ShowBox();
            ShowScore();
            ShowHealth(health);
            show_string(&i);
            s_time = time(0);
            j = 0;
            timeprint(timeLimit, remain_time, i, j, 1);
        }

        if (health <= 0)
            break;
    }

    return 0;
}

void Menu()
{
    int a, b;
    char nextStage[] = "���Ʊ�";
    system("cls");
    Show_Box();
    gotoxy(50, 8);
    printf("1.���ӽ���\n");
    gotoxy(50, 12);
    printf("2.��������\n");
    gotoxy(50, 16);
    scanf("%d", &a);
    if (a == 1)
    {
        system("cls");
        Show_Box();
        gotoxy(50, 7);
        printf("���̵��� �����Ͻÿ�.\n");
        gotoxy(50, 10);
        printf("1. ���Ʊ�\n");
        gotoxy(50, 14);
        printf("2. û���\n");
        gotoxy(50, 18);
        printf("3. ����\n");
        gotoxy(50, 22);
        scanf("%d", &b);

        if (b == 1)
        {
            system("cls");
            //���Ʊ� ���� �Լ� ȣ��. ����� strcpy(nextStage, "û���"); �� stageEnding ȣ��
            //û��� ���� �Լ� ȣ��. ����� strcpy(nextStage, "����"); �� stageEnding ȣ��
            //���� ���� �Լ� ȣ��. ending ȣ��
        }
        if (b == 2)
        {
            system("cls");
            //û��� ���� �Լ� ȣ��. ����� strcpy(nextStage, "����"); �� stageEnding ȣ��
            //���� ���� �Լ� ȣ��. ending ȣ��

        }
        if (b == 3) {
            system("cls");
            //���� ���� �Լ� ȣ��. ending ȣ��
        }

    }
    else if (a == 2) {
        score = 500;
        ending(score);
    }
    else {
        stageEnding(nextStage);
    }
}
void Show_Box()
{
    int x = 9, y = 4, i;

    gotoxy(x, y);
    printf("��");
    for (i = 0; i < 106; i++)
        printf("��");
    printf("��");
    for (i = 0; i < 20; i++)
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
    y = 25;
    gotoxy(x, y);
    printf("��");
    for (i = 0; i < 106; i++)
        printf("��");
    printf("��");
}

void stageEnding(char* nextStage) {
    system("cls");
    Show_Box();
    gotoxy(CURSOR1, CURSOR2);
    printf("���� ! ���� ���������� ���۵˴ϴ�...");
    Sleep(1500); //1.5��
    system("cls");
    Show_Box();
    gotoxy(CURSOR3, CURSOR2);
    printf("%s", nextStage);
    Sleep(1500); //1.5��
    system("cls");
}

void ending(int score) {
    system("cls");
    Show_Box();
    gotoxy(CURSOR1, CURSOR2);
    printf("�� ���� ������... ");
    Sleep(2000);
    printf("%d �� �Դϴ�! �����մϴ�.", score);
    Sleep(1500);
    system("cls"); //�ٽ� �Ͻðڽ��ϱ�? ����� ���� ������ ������ ���� �ʿ�
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
void show_string(char* cnt)
{
    int x = 127 / 2 - strlen(word1[*cnt]) / 2;

    gotoxy(x, 10);
    printf("%s\n", word1[*cnt]);
    gotoxy(x, 19);
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
    printf("                    ");   // ������Ʈ
    gotoxy(WIDTH - 37, 5);
    SetColor(15, 4);   // ���� �Ͼ�, ��� ���� ����
    printf(" HP ");
    SetColor(15, 0);   // ���� �Ͼ�, ��� ����
    printf(" : ");
    SetColor(12, 0);      // ���� ����, ��� ����
    for (i = 0; i < health; i++)
        printf("\u2665");   // ��Ʈ ���
    SetColor(15, 0);   // ���� �Ͼ�, ��� ����
}
// �� ����
void SetColor(unsigned short text, unsigned short back)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}
// ���� ���
void ShowScore()
{
    gotoxy(10, 5);
    printf("                 ");   // ������Ʈ
    gotoxy(10, 5);
    SetColor(10, 0);
    printf("S C O R E : %d", score);
    SetColor(15, 0);   // ���� �Ͼ�, ��� ����
    gotoxy(0, 0);      // �ڽ� �������� ���� �ذ�
}


// ���¿�
// ���� �ð��� ���� ����
void time_score()
{
    timescore = 150 * ((double)remain_time / timeLimit);
    score += timescore;
}
// ���� ��� �� ���� ��, ����� �� ���� +1 ��
// ���Ʊ� ���� ���
void show_score_CHILD()
{
    score += 50 * update_correct() + 80 * update_difficult() + CHILD_CLEAR;
}
// û��� ���� ���
void show_score_ADOLESENT()
{
    score += 50 * update_correct() + 80 * update_difficult() + ADOLESENT_CLEAR;
}
// ���� ���� ���
void show_score_OLD()
{
    score += 50 * update_correct() + 80 * update_difficult() + OLD_CLEAR;
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

void LevelScore(int level)
{
    if (level == 1)
        show_score_CHILD();
    else if (level == 2)
        show_score_ADOLESENT();
    else
        show_score_OLD();
}

// ������
void timeprint(int timeLimit, int leveltime, int i, int j, int istyped) {
    // do-while�� ���� - main ������ ���ѷ���
    static int timecmp;
    static int init = 1;

    if (init)
    {
        timecmp = timeLimit;
        gotoxy(127 / 2 - 8 / 2, 15);
        printf("%2ds left", leveltime);
        gotoxy(127 / 2 - strlen(word1[i]) / 2 + j, 19);   // Ŀ�� �ڽ���
        init = 0;
    }
    if (timecmp > leveltime)
    {
        gotoxy(127 / 2 - 8 / 2, 15);
        printf("%2ds left", leveltime);
        gotoxy(127 / 2 - strlen(word1[i]) / 2 + j, 19);   // Ŀ�� �ڽ���
        timecmp = leveltime;
        if (timecmp <= 0)
        {
            timecmp = timeLimit;
            init = 1;
        }
    }
    if (istyped)
        init = 1;         // Ÿ���� ������ �� �ʱ�ȭ
}