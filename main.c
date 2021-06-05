#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>

#define CHILD_CLEAR 150
#define ADOLESENT_CLEAR 300
#define OLD_CLEAR 450

#define CURSOR1 40
#define CURSOR2 12
#define CURSOR3 55
#define WIDTH 128
#define HEIGHT 32
#define SIZE 16
#define TIME_LIMIT 10
#define ASIZE 51

void stageEnding(char*); // �������� �߰� ��� �Լ�
int typing_game();
void gotoxy(int, int);
void Show_Box();    //���� ���� �ڽ�
void Show_Box_Game();   //�ΰ��� �ڽ�
void Show_Health(int);
void SetColor(unsigned short, unsigned short);   // �� ����
void Show_Menu();//�޴�ȣ��
void Combo_score(int);//�޺�����
void timeprint(int, int, int, int, int); //�����ð� ��� �Լ�
void Next_Stage();//06.02 ���¿� ���� ���������� �Ѿ�� �Լ�
void show_string(int*); // ���ڿ� ���
void ShowLevel(int);    // ���� ���� �ȳ��� ���
int ClearScore(int);    // �������� Ŭ���� ����
void modeSelect(); //��� ���� �Լ�
void levelSelect(); //���̵� ���� �Լ�
void update_best_score(int);//�ְ����� 5�� �����ϴ� �Լ�

int best[5] = { 0,0,0,0,0 };
int score;
int mode;
int menu;//�޴�ȣ��
int* p_menu = &menu;
int timescore;               //���� �ð��� ���� �߰� ����
int n = 0;                    //�޺�
int level;                      //06.02���¿� level�� ���� �ܾ�迭 ���Դٸ��� �ؾ��ϹǷ� ���������� ����
int health;
int word[SIZE];
char* word1[SIZE] = { "arrive","bicycle","bring","button"
    ,"monkey","nurse","patent","strawberry","supermarket","tomorrow","yellow","yesterday","pediatric asthma","autoi","measles","answer" };
//06.02���¿� ���̵� ���� �ܾ� �迭 �߰�
char* word2[SIZE] = { "marriage","university","employment" ,"unemployment"
, "campus","certificate" ,"culture" ,"military","internet", "challenge", "start up","bitcoin", "panic","apartment","dyspepsia" ,"adolesent" };
char* word3[SIZE] = { "nursing home","retire","funeral","denture","mature","wise",
"memory","gray hair","travel","sapient","hospital","experience","senile dementia","kodokushi","glaucoma" };
char* word4[SIZE] = { "kindergarten","bicycle","picky eating","pediatrician"
    ,"report card","immature","patent","strawberry","supermarket","tomorrow","key harmonica","yesterday","pediatric asthma","autoi","measles vaccine","answer" };
char* word5[SIZE] = { "congratulatory money","university","employment" ,"severance pay"
, "graduate school","certificate" ,"culture" ,"stock investment","internet", "challenge", "anaphylaxis","bitcoin", "social networking service","apartment","dyspepsia" ,"career design" };
char* word6[SIZE] = { "nursing home","ventilation","funeral","elderly depression","mentally mature","hale and harty",
"homesickness","rheumatism","osteoporosis","sapient","hospital","experience","senile dementia","kodokushi","glaucoma" };

int main()
{
    char ch;                  //�������� ���� ȭ�鿡�� ����ȭ������ ���ư���
    int n;                  //�޺�
    int start;      //start: ���ӽ��ۿ��� �Է� 06.02���¿� level ���������� ����
    system("mode con cols=128 lines=32");
    srand(time(0));
    while (1)
    {
    mainstart:
        while (1)
        {
            update_best_score(score);
            score = 0;
            system("cls");
            Show_Box();
            gotoxy(50, 8);
            printf("1.���ӽ���\n");
            gotoxy(50, 12);
            printf("2.��������\n");
            gotoxy(50, 16);
            printf("3.������������\n");
            gotoxy(50, 20);
            scanf("%d", &start);    // ����ó�� ��
            while (getchar() != '\n');
            if (start >= 1 && start <= 3)
                break;
        }

        if (start == 1)
        {
            modeSelect();
            if (mode == 1) {
                levelSelect();


                for (; level <= 3; level++)
                {
                    system("cls");
                    Show_Box();
                    gotoxy(50, 10);
                    ShowLevel(level);
                    Sleep(3000);
                    system("cls");
                    typing_game();
                    if ((*p_menu) == 2) {
                        (*p_menu) = 0;
                        score = 0;
                        break;
                    }
                    if ((*p_menu) == 3) {
                        break;
                    }
                    if (health <= 0)//06.03 ���¿� ü���� �� ��Ƶ� Ŭ����Ǵ°� ����
                    {
                        system("cls");
                        Show_Box();
                        gotoxy(50, 15);
                        printf("Game Over....");
                        Sleep(1500);
                        break;
                    }
                    if (level != 3) {
                        Next_Stage();
                    }
                    score += ClearScore(level);
                }
                if ((*p_menu) == 3) {
                    (*p_menu) = 0;
                    break;
                }
            }
            else if (mode == 2) {
                levelSelect();


                for (; level <= 3; level++)
                {
                    system("cls");
                    Show_Box();
                    gotoxy(50, 10);
                    ShowLevel(level);
                    Sleep(3000);
                    system("cls");
                    typing_game();
                    if ((*p_menu) == 2) {
                        (*p_menu) = 0;
                        score = 0;
                        break;
                    }
                    if ((*p_menu) == 3) {
                        break;
                    }
                    if (health <= 0)//06.03 ���¿� ü���� �� ��Ƶ� Ŭ����Ǵ°� ����
                    {
                        system("cls");
                        Show_Box();
                        gotoxy(50, 15);
                        printf("Game Over....");
                        Sleep(1500);
                        break;
                    }
                    Next_Stage();
                    score += ClearScore(level);
                }
                if ((*p_menu) == 3) {
                    (*p_menu) = 0;
                    break;
                }
            }
            else if (mode == 3) {
                system("cls");
                Show_Box();
                gotoxy(50, 12);
                printf("������带 �����մϴ�.\n");
                Sleep(1000);
                // gotoxy(50, 10);
                for (int k = 0; k < 3; k++)
                {
                    system("cls");
                    Show_Box();
                    gotoxy(50, 10);
                    printf("������ ���� ������....");
                    Sleep(3000);
                    system("cls");
                    level = rand() % 6 + 1; // ���� ����

                    typing_game();
                    if ((*p_menu) == 2) {
                        (*p_menu) = 0;
                        score = 0;
                        break;
                    }
                    if ((*p_menu) == 3) {
                        break;
                    }
                    if (health <= 0)//06.03 ���¿� ü���� �� ��Ƶ� Ŭ����Ǵ°� ����
                    {
                        system("cls");
                        Show_Box();
                        gotoxy(50, 15);
                        printf("Game Over....");
                        Sleep(1500);
                        break;
                    }
                    Next_Stage();
                    score += ClearScore(level);
                }
                if ((*p_menu) == 3) {
                    (*p_menu) = 0;
                    break;
                }
            }
        }
        if (start == 2)
        {
            system("cls");
            Show_Box();
            gotoxy(50, 16);
            printf("������ �����մϴ�.\n\n\n\n\n\n\n\n\n");
            break;
        }
        if (start == 3)
        {

            while (1) {
                system("cls");
                Show_Box();
                for (int x = 0; x < 5; x++) {
                    gotoxy(50, 8 + 2 * x);
                    printf("%d. %d ��", x + 1, best[x]);
                }
                gotoxy(50, 18);
                printf("ó��ȭ������ ���ư����� m�� �����ÿ�.");
                gotoxy(50, 20);
                scanf("%s", &ch);   // ����ó�� ��
                if (ch == 'm')
                    break;
            }
        }
        else
            continue;
    }
    /*
    if (health <= 0) {                      // ���� ����
        system("cls");
        Show_Box();
        gotoxy(50, 15);
        printf("Game Over....");
        Sleep(1500);
        goto mainstart;
    }
    */
}

//Ŀ���̵�
void gotoxy(int x, int y)
{
    COORD Pos;
    Pos.X = x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// �ڽ� ���
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
void Show_Box_Game()
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
void Show_Health(int health)
{
    int i;

    gotoxy(WIDTH - 30, 5);
    printf("                    ");   // ��Ʈ ����
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

void time_score(int remain_time, int timeLimit)
{
    timescore = 150 * ((double)remain_time / timeLimit);
    score += timescore;
}



// ���ڿ� ���
void show_string(int* cnt)
{
    gotoxy(127 / 2 - strlen(word[*cnt]) / 2, 10);
    printf("%s\n", word[*cnt]);
    gotoxy(127 / 2 - strlen(word[*cnt]) / 2, 19);
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
//�����ð� ���
void timeprint(int timeLimit, int leveltime, int i, int j, int istyped) {       // ���� ���� word 1

    static int timecmp;
    static int init = 1;

    if (init)
    {
        timecmp = timeLimit;
        gotoxy(127 / 2 - 8 / 2, 15);
        printf("%2ds left", leveltime);
        gotoxy(127 / 2 - strlen(word[i]) / 2 + j, 19);   // Ŀ�� �ڽ���
        init = 0;
    }
    if (timecmp > leveltime)
    {
        gotoxy(127 / 2 - 8 / 2, 15);
        printf("%2ds left", leveltime);
        gotoxy(127 / 2 - strlen(word[i]) / 2 + j, 19);   // Ŀ�� �ڽ���
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

void update_correct()
{
    score += 50;
}
void update_difficult()
{
    score += 80;
}
void Show_Menu()
{
    while (1)
    {
        system("cls");
        Show_Box();
        gotoxy(50, 10);
        printf("1. ���Ӱ���ϱ�\n");
        gotoxy(50, 12);
        printf("2. ó��ȭ������ ���ư���\n");
        gotoxy(50, 14);
        printf("3. ���������ϱ�\n");
        gotoxy(50, 16);
        scanf("%d", &menu); // ����ó�� ��
        while (getchar() != '\n');
        if (*p_menu == 1) {
            system("cls");
            break;
        }
        else if (*p_menu == 2)
            break;

        else if (*p_menu == 3)
            break;

    }
}
//�����Լ�
int typing_game() {
    char ch, input[ASIZE];
    int s_time, esc_time = 0, menu_time = 0, j = 0;
    int i = 0;  // �迭�� ������ �̰ŷ� ���ҰŶ� �� ���Ӹ��� �������־����.
    int remain_time;
    int timeLimit;
    int w;//06.02 ���¿� ���̵��� ���� �迭�����ϴ� for���� �ʿ�


    if (mode == 3) {
        int idx = rand() % 6 + 1;
        level = idx;
    }
    if (mode == 2) level += 3;
    //06.02 ���¿� health�� ���̵��� ���� �� �Ҵ�
    switch (level) {
    case 1: timeLimit = 15; health = 12; for (w = 0; w < SIZE; w++)word[w] = word1[w]; break;   // word[]�� ���ڿ� ������ ����
    case 2: timeLimit = 10; health = 8;  for (w = 0; w < SIZE; w++)word[w] = word2[w]; break;
    case 3: timeLimit = 10; health = 4;  for (w = 0; w < SIZE; w++)word[w] = word3[w]; break;
    case 4: timeLimit = 15; health = 12; for (w = 0; w < SIZE; w++)word[w] = word4[w]; break;   // word[]�� ���ڿ� ������ ����
    case 5: timeLimit = 10; health = 8;  for (w = 0; w < SIZE; w++)word[w] = word5[w]; break;
    case 6: timeLimit = 10; health = 4;  for (w = 0; w < SIZE; w++)word[w] = word6[w]; break;
    }




loop:
    Show_Box_Game();
    ShowScore();
    Show_Health(health);
    show_string(&i);

    s_time = time(0);
    while (1)
    {
        remain_time = s_time + timeLimit + menu_time - esc_time - time(0);
        timeprint(timeLimit, remain_time, i, j, 0);
        if (remain_time == 0)
        {
            system("cls");
            i++;   //�ܾ��� �迭 �� ���� �ܾ�� �ѱ�� �˴ϴ�
            if (i >= 15) break;   //�ܾ��� �迭�� ������ �Ǹ� ������ ������
            health -= 2;   // �ð� �ʰ� ü�� -2
            Show_Box_Game();
            ShowScore();
            Show_Health(health);
            show_string(&i);
            s_time = time(0);
            esc_time = 0;
            menu_time = 0;
            j = 0;
            n = 0;//�޺��ʱ�ȭ
        }

        if (_kbhit())
        {
            ch = _getch();
            if (ch == 27)
            {
                esc_time = time(0);
                Show_Menu();
                if (*p_menu == 2) {
                    break;
                }
                if (*p_menu == 3) {
                    break;
                }
                if (*p_menu == 1) {
                    menu_time = time(0);
                    Show_Box_Game();
                    ShowScore();
                    Show_Health(health);
                    show_string(&i);        // ���� �������� Ŀ���� ���� ���� show_string, print_time
                    for (int k = 0; k < i; k++)
                    {
                        printf("\b");
                    }
                    //printf("%s", input);  // �� �� �Ǵ��� �𸣰���
                    for (int k = 0; k < j; k++)
                    {
                        printf("%c", input[k]);
                    }
                    *p_menu = 0;
                    continue;
                    //goto loop;
                }
            }
            if (ch == 8)
            {
                if (j > 0)
                {
                    printf("\b \b");
                    input[j] = 0;   //6.2 ���� ������
                    j--;
                }
            }
            if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch == 32))
            {
                printf("%c", ch);
                input[j] = ch;
                j++;
            }
        }

        if (j >= strlen(word[i]))
        {
            input[strlen(word[i])] = 0;
            if (!strcmp(word[i], input))
            {
                i++;   //�ܾ��� �迭 �� ���� �ܾ�� �ѱ�� �˴ϴ�
                if (i >= 15) break;   //�ܾ��� �迭�� ������ �Ǹ� ������ ������
                gotoxy(127 / 2 - 5 / 2, 22);
                printf("�����մϴ�.\n");
                Combo_score(remain_time, timeLimit);
                time_score(remain_time, timeLimit);
                update_correct();
                ShowScore();
                Sleep(1000);
                s_time = time(0);
            }
            else {
                health--;   // ��Ÿ ü�� -1
                n = 0;//�޺��ʱ�ȭ
            }
            system("cls");
            Show_Box_Game();
            ShowScore();
            Show_Health(health);
            show_string(&i);
            j = 0;
            timeprint(timeLimit, remain_time, i, j, 1);
        }

        if (health <= 0)
            break;
    }

    return 0;
}
void Combo_score(int remain_time, int timeLimit)
{
    gotoxy(50, 22);
    if (remain_time >= timeLimit - 2)
    {
        n++;
        printf("%d combo!", n);
    }
    if (remain_time < timeLimit - 2) {
        n = 0;
        printf("%d combo!", n);
    }
    if (n == 5) {
        score += 280;
        n = 0;
    }
}
void Next_Stage()
{
    system("cls");
    Show_Box();
    gotoxy(50, 10);
    printf("���� ! ���� ���������� ���۵˴ϴ�...");
    Sleep(1500);
}
void ShowLevel(int level)
{
    if (level == 1)
        printf("���Ʊ� ���̵��� �����մϴ�.");
    else if (level == 2)
        printf("û��� ���̵��� �����մϴ�.");
    else if (level == 3)
        printf("���� ���̵��� �����մϴ�.");
}
int ClearScore(int level)
{
    if (level == 1)
        return CHILD_CLEAR;
    else if (level == 2)
        return ADOLESENT_CLEAR;
    else if (level == 3)
        return OLD_CLEAR;
    else if (level == 1)
        return CHILD_CLEAR * 2;
    else if (level == 2)
        return ADOLESENT_CLEAR * 2;
    else if (level == 3)
        return OLD_CLEAR * 2;
}
//��� ����
void modeSelect() {
    while (1)
    {
        system("cls");
        Show_Box();
        gotoxy(50, 7);
        printf("��带 �����Ͻÿ�.\n");
        gotoxy(50, 10);
        printf("1. �⺻ ���\n");
        gotoxy(50, 14);
        printf("2. ����� �ܾ� ���\n");
        gotoxy(50, 18);
        printf("3. ���� ���\n");
        gotoxy(50, 22);
        scanf("%d", &mode); // ����ó�� ��
        while (getchar() != '\n');
        if (mode >= 1 && mode <= 3)
            break;

    }
}

//���̵� ����
void levelSelect() {
    while (1)
    {
        system("cls");
        Show_Box();
        gotoxy(50, 7);
        if (mode == 1)
            printf("���̵��� �����Ͻÿ�.\n");
        else
            printf("�ϵ��� ���̵��� �����Ͻÿ�.\n");
        gotoxy(50, 10);
        printf("1. ���Ʊ�\n");
        gotoxy(50, 14);
        printf("2. û���\n");
        gotoxy(50, 18);
        printf("3. ����\n");
        gotoxy(50, 22);
        scanf("%d", &level);    // ����ó�� ��
        while (getchar() != '\n');
        if (level >= 1 && level <= 3)
            break;
    }
}
//�ְ�����5�� �����ϴ� �Լ�
void update_best_score(int a)
{
    int x, w;
    if (a >= best[0]) {
        for (x = 4; x > 0; x--) {
            best[x] = best[(x - 1)];
        }
        best[0] = a;
    }
    for (w = 1; w < 5; w++) {
        if (a >= best[w] && a < best[w - 1]) {
            for (x = 4; x > w; x--) {
                best[x] = best[(x - 1)];
            }
            best[w] = a;
        }
    }
}