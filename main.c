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

void stageEnding(char*); // 스테이지 중간 출력 함수
int typing_game();
void gotoxy(int, int);
void Show_Box();    //게임 제외 박스
void Show_Box_Game();   //인게임 박스
void Show_Health(int);
void SetColor(unsigned short, unsigned short);   // 색 변경
void Show_Menu();//메뉴호출
void Combo_score(int);//콤보점수
void timeprint(int, int, int, int, int); //남은시간 출력 함수
void Next_Stage();//06.02 김태영 다음 스테이지로 넘어가는 함수
void show_string(int*); // 문자열 출력
void ShowLevel(int);    // 레벨 시작 안내문 출력
int ClearScore(int);    // 스테이지 클리어 점수

int score = 0;
int menu;//메뉴호출
int* p_menu = &menu;
int timescore;               //남는 시간에 따른 추가 점수
int n = 0;                    //콤보
int level;                      //06.02김태영 level에 따라 단어배열 대입다르게 해야하므로 전역변수로 선언
int health;
char* word1[SIZE] = { "arrive","bicycle","bring","button"
    ,"monkey","nurse","patent","strawberry","supermarket","tomorrow","yellow","yesterday","pediatric","autoi","measles","answer" };
//06.02김태영 난이도 따른 단어 배열 추가
char* word2[SIZE] = { "marrige","university","employment" ,"unemployment"
, "campus","certificate" ,"culture" ,"military","internet", "challenge", "start up","bitcoin", "panic","apartment","dyspepsia" ,"adolesent" };
char* word3[SIZE] = { "nursing home","retire","funeral","denture","mature","wise",
"memory","gray hair","travel","sapient","hospital","experience","senile dementia","kodokushi","glaucoma" };

int main()
{
    char ch;                  //현재점수 보는 화면에서 원래화면으로 돌아가기
    int n;                  //콤보
    int start;      //start: 게임시작여부 입력 06.02김태영 level 전역변수로 선언
    system("mode con cols=128 lines=32");
    srand(time(0));
    while (1)
    {
    mainstart:
        system("cls");
        Show_Box();
        gotoxy(50, 8);
        printf("1.게임시작\n");
        gotoxy(50, 12);
        printf("2.게임종료\n");
        gotoxy(50, 16);
        printf("3.현재점수\n");
        gotoxy(50, 20);
        scanf("%d", &start);
        if (start == 1)
        {
            system("cls");
            Show_Box();
            gotoxy(50, 7);
            printf("난이도를 선택하시오.\n");
            gotoxy(50, 10);
            printf("1. 유아기\n");
            gotoxy(50, 14);
            printf("2. 청년기\n");
            gotoxy(50, 18);
            printf("3. 노년기\n");
            gotoxy(50, 22);
            scanf("%d", &level);


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
                    break;
                }
                if ((*p_menu) == 3) {
                    break;
                }
                Next_Stage();
                score += ClearScore(level);
            }
            if ((*p_menu) == 3) {
                (*p_menu) = 0;
                break;
            }

            /*
            if (level == 1)
            {
                system("cls");
                Show_Box();
                gotoxy(50, 10);
                printf("유아기 난이도를 시작합니다.");//유아기 게임 함수로 대체
                Sleep(3000);
                typing_game();
                if ((*p_menu) == 2) {
                    (*p_menu) = 0;
                    continue;
                }
                if ((*p_menu) == 3) {
                    (*p_menu) = 0;
                    break;
                }
                Next_Stage();
                level++;
                score += CHILD_CLEAR;
                //goto adolesent;
            }
            if (level == 2)
            {
            //adolesent://06.02 김태영 goto문이용하여 스테이지 넘어가기
                system("cls");
                Show_Box();
                gotoxy(50, 10);
                printf("청년기게임을 시작합니다.");//청년기 게임 함수로 대체
                Sleep(3000);
                typing_game();//06.02 김태영 게임함수
                if ((*p_menu) == 2) {
                    (*p_menu) = 0;
                    continue;
                }
                if ((*p_menu) == 3) {
                    (*p_menu) = 0;
                    break;
                }
                Next_Stage();//06.02김태영 다음스테이지로 자동이동
                level++;
                score += ADOLESENT_CLEAR;
                //goto old;
            }
            if (level == 3)
            {
            //old://06.02 goto문이용하여 스테이지 넘어가기
                system("cls");
                Show_Box();
                gotoxy(50, 10);
                printf("노년기 게임을 시작합니다.");//노년기 게임 함수로 대체
                Sleep(3000);
                typing_game();//06.02김태영 게임함수
                if ((*p_menu) == 2) {
                    (*p_menu) = 0;
                    continue;
                }
                if ((*p_menu) == 3) {
                    (*p_menu) = 0;
                    break;
                }
                score += OLD_CLEAR;
                system("cls");
                Show_Box();
                gotoxy(50, 14);
                printf("축하합니다! 게임을 클리어했습니다!");
                gotoxy(50, 16);
                printf("점수는 %d점 입니다.", score);
                gotoxy(50, 18);
                printf("잠시후 처음화면으로 이동합니다.");
                Sleep(2000);
                continue;//06.02 김태영 처음화면으로 돌아가기
            }*/
        }
        if (start == 2)
        {
            system("cls");
            Show_Box();
            gotoxy(50, 16);
            printf("게임을 종료합니다.\n\n\n\n\n\n\n\n\n");
            break;
        }
        if (start == 3)
        {
            system("cls");
            Show_Box();
            while (1) {
                gotoxy(50, 10);
                printf("현재점수는 %d점입니다.", score);
                gotoxy(50, 14);
                printf("처음화면으로 돌아가려면 m을 누르시오.");
                gotoxy(50, 18);
                scanf("%s", &ch);
                if (ch == 'm')
                    break;
                else {
                    gotoxy(50, 18);
                    printf("\b\b    \b");
                    continue;
                }
            }
        }
        else
            continue;
    }
    if (health == 0) {                      // 수정 예정
        system("cls");
        Show_Box();
        gotoxy(50, 15);
        printf("Game Over....");
        Sleep(1500);
        goto mainstart;
    }
}

//커서이동
void gotoxy(int x, int y)
{
    COORD Pos;
    Pos.X = x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// 박스 출력
void Show_Box()
{
    int x = 9, y = 4, i;

    gotoxy(x, y);
    printf("┌");
    for (i = 0; i < 106; i++)
        printf("─");
    printf("┐");
    for (i = 0; i < 20; i++)
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
    y = 25;
    gotoxy(x, y);
    printf("└");
    for (i = 0; i < 106; i++)
        printf("─");
    printf("┘");
}
void Show_Box_Game()
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
void Show_Health(int health)
{
    int i;

    gotoxy(WIDTH - 30, 5);
    printf("                    ");   // 하트 삭제
    gotoxy(WIDTH - 37, 5);
    SetColor(15, 4);   // 글자 하양, 배경 진한 빨강
    printf(" HP ");
    SetColor(15, 0);   // 글자 하양, 배경 검정
    printf(" : ");
    SetColor(12, 0);      // 글자 빨강, 배경 검정
    for (i = 0; i < health; i++)
        printf("\u2665");   // 하트 출력
    SetColor(15, 0);   // 글자 하양, 배경 검정
}
// 색 변경
void SetColor(unsigned short text, unsigned short back)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}

void time_score(int remain_time, int timeLimit)
{
    timescore = 150 * ((double)remain_time / timeLimit);
    score += timescore;
}



// 문자열 출력
void show_string(int p, int* cnt)
{
    
    if ((p) == 1) 
    {
        gotoxy(127 / 2 - strlen(word1[*cnt]) / 2, 10);
        printf("%s\n", word1[*cnt]);
        gotoxy(127 / 2 - strlen(word1[*cnt]) / 2, 19);
    }
    if ((p) == 2) 
    {
        gotoxy(127 / 2 - strlen(word2[*cnt]) / 2, 10);
        printf("%s\n", word2[*cnt]);
        gotoxy(127 / 2 - strlen(word2[*cnt]) / 2, 19);
    }
    if ((p) == 3) 
    {
        gotoxy(127 / 2 - strlen(word3[*cnt]) / 2, 10);
        printf("%s\n", word3[*cnt]);
        gotoxy(127 / 2 - strlen(word3[*cnt]) / 2, 19);
    }
    
}
// 점수 출력
void ShowScore()
{
    gotoxy(10, 5);
    printf("                 ");   // 업데이트
    gotoxy(10, 5);
    SetColor(10, 0);
    printf("S C O R E : %d", score);
    SetColor(15, 0);   // 글자 하양, 배경 검정
    gotoxy(0, 0);      // 박스 지워지는 버그 해결
}
//남은시간 출력
void timeprint(int timeLimit, int leveltime, int i, int j, int istyped) {

    static int timecmp;
    static int init = 1;

    if (init)
    {
        timecmp = timeLimit;
        gotoxy(127 / 2 - 8 / 2, 15);
        printf("%2ds left", leveltime);
        gotoxy(127 / 2 - strlen(word1[i]) / 2 + j, 19);   // 커서 박스로
        init = 0;
    }
    if (timecmp > leveltime)
    {
        gotoxy(127 / 2 - 8 / 2, 15);
        printf("%2ds left", leveltime);
        gotoxy(127 / 2 - strlen(word1[i]) / 2 + j, 19);   // 커서 박스로
        timecmp = leveltime;
        if (timecmp <= 0)
        {
            timecmp = timeLimit;
            init = 1;
        }
    }
    if (istyped)
        init = 1;         // 타이핑 끝났을 때 초기화
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
        printf("1. 게임계속하기\n");
        gotoxy(50, 12);
        printf("2. 처음화면으로 돌아가기\n");
        gotoxy(50, 14);
        printf("3. 게임종료하기\n");
        gotoxy(50, 16);
        scanf("%d", &menu);
        if (*p_menu == 1) {
            system("cls");
            break;
        }
        if (*p_menu == 2)
            break;

        if (*p_menu == 3)
            break;

        else
            continue;
    }
}
//게임함수
int typing_game() {
    char ch, input[SIZE];
    int s_time, j = 0;
    int i = 0;  // 배열의 순서를 이거로 정할거라 매 게임마다 리셋해주어야함.
    int remain_time;
    int timeLimit;
    int w;//06.02 김태영 난이도에 따른 배열복사하는 for문에 필요
    int word[SIZE];
    //06.02 김태영 health에 난이도에 따라 값 할당
    switch (level) {
    case 1: timeLimit = 15; health = 12; for (w = 0; w < SIZE; w++)word[w] = word1[w]; break;   // word[]에 문자열 포인터 저장
    case 2: timeLimit = 10; health = 8;  for (w = 0; w < SIZE; w++)word[w] = word2[w]; break;
    case 3: timeLimit = 10; health = 4;  for (w = 0; w < SIZE; w++)word[w] = word3[w]; break;
    }


    

loop:
    Show_Box_Game();
    ShowScore();
    Show_Health(health);
    show_string(level, &i);

    s_time = time(0);
    while (1)
    {
        remain_time = s_time + timeLimit - time(0);
        timeprint(timeLimit, remain_time, i, j, 0);
        if (time(0) == s_time + timeLimit)
        {
            system("cls");
            i++;   //단어의 배열 중 다음 단어로 넘기게 됩니다
            if (i >= 15) break;   //단어의 배열이 끝나게 되면 게임을 끝낸다
            health -= 2;   // 시간 초과 체력 -2
            Show_Box_Game();
            ShowScore();
            Show_Health(health);
            show_string(level, &i);
            s_time = time(0);
            j = 0;
            n = 0;//콤보초기화
        }

        if (_kbhit())
        {
            ch = _getch();
            if (ch == 27)
            {
                Show_Menu();
                if (*p_menu == 2) {
                    break;
                }
                if (*p_menu == 3) {
                    break;
                }
                if (*p_menu == 1) {
                    goto loop;
                }
            }
            if (ch == 8)
            {
                if (j > 0)
                {
                    printf("\b \b");
                    input[j] = 0;   //6.2 변경 김재윤
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
                i++;   //단어의 배열 중 다음 단어로 넘기게 됩니다
                if (i >= 15) break;   //단어의 배열이 끝나게 되면 게임을 끝낸다
                gotoxy(127 / 2 - 5 / 2, 22);
                printf("축하합니다.\n");
                Combo_score(remain_time, timeLimit);
                time_score(remain_time, timeLimit);
                update_correct();
                ShowScore();
                Sleep(1000);
                s_time = time(0);
            }
            else {
                health--;   // 오타 체력 -1
                n = 0;//콤보초기화
            }
            system("cls");
            Show_Box_Game();
            ShowScore();
            Show_Health(health);
            show_string(level, &i);
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
    printf("성공 ! 다음 스테이지가 시작됩니다...");
    Sleep(1500);
}
void ShowLevel(int level)
{
    if (level == 1)
        printf("유아기 난이도를 시작합니다.");
    else if (level == 2)
        printf("청년기 난이도를 시작합니다.");
    else if (level == 3)
        printf("노년기 난이도를 시작합니다.");
}
int ClearScore(int level)
{
    if (level == 1)
        return CHILD_CLEAR;
    else if (level == 2)
        return ADOLESENT_CLEAR;
    else if (level == 3)
        return OLD_CLEAR;
}