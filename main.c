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
#define SIZE 16
#define TIME_LIMIT 10      //  통일 필요

// 김태영
#define CHILD_CLEAR 150         /*유아기 클리어 점수*/
#define ADOLESENT_CLEAR 300      /*청년기 클리어 점수*/
#define OLD_CLEAR 450         /*노년기 클리어 점수*/

#define CURSOR1 40
#define CURSOR2 12
#define CURSOR3 55


//========================== 함수 선언

void gotoxy(int, int);                     // 커서 이동   
void show_string(char*);                  // 문자열 출력
void ShowBox();                           // 박스 출력
void ShowHealth(int);                     // 체력 출력
void SetColor(unsigned short, unsigned short);   // 색 변경
void ShowScore();                        // 점수 출력


void time_score();            //남은 시간에 따른 점수
void show_score_CHILD();      //유아기 점수 계산하고 출력하는 함수
void show_score_ADOLESENT();   //청년기 점수 계산하고 출력하는 함수
void show_score_OLD();         //노년기 점수 계산하고 출력하는 함수
int update_correct();         //맞은 개수 +1하고 저장하는 함수
int update_difficult();         //틀린 개수 +1하고 저장하는 함수 <=== 틀린 개수가 아니라 어려운 거 맞은 개수??

void Level(int);


void timeprint(int, int, int, int); //남은시간 출력 함수

void Menu();
void Show_Box();
void stageEnding(char*); // 스테이지 중간 출력 함수
void ending(int); //게임 엔딩 출력 함수

//========================== 전역 변수

int timeLimit;


int score = 0;               //점수 저장 변수, 0으로 초기화
int correct = 0, difficult = 0;//correct: 맞은 기본단어 개수, difficult: 맞은 어려운 단어 개수
int timescore;               //남는 시간에 따른 추가 점수
int remain_time;            //타이핑 후 남은 시간




char* word1[SIZE] = { "arrive","bicycle","bring","button",
                        "monkey","nurse","patent","strawberry",
                        "supermarket","tomorrow","yellow","yesterday",
                        "pediatric asthma","autointoxication",
                        "battered child syndrome" };

int main() {
    char word[SIZE], ch, input[SIZE];
    int s_time, j = 0, i = 0;
    int health = 10;
    int level = 3;   // 1, 2, 3 순

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
            health -= 2;   // 시간 초과 체력 -2
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
                health--;   // 오타 체력 -1

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
    char nextStage[] = "유아기";
    system("cls");
    Show_Box();
    gotoxy(50, 8);
    printf("1.게임시작\n");
    gotoxy(50, 12);
    printf("2.게임종료\n");
    gotoxy(50, 16);
    scanf("%d", &a);
    if (a == 1)
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
        scanf("%d", &b);

        if (b == 1)
        {
            system("cls");
            //유아기 게임 함수 호출. 종료시 strcpy(nextStage, "청년기"); 후 stageEnding 호출
            //청년기 게임 함수 호출. 종료시 strcpy(nextStage, "노년기"); 후 stageEnding 호출
            //노년기 게임 함수 호출. ending 호출
        }
        if (b == 2)
        {
            system("cls");
            //청년기 게임 함수 호출. 종료시 strcpy(nextStage, "노년기"); 후 stageEnding 호출
            //노년기 게임 함수 호출. ending 호출

        }
        if (b == 3) {
            system("cls");
            //노년기 게임 함수 호출. ending 호출
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

void stageEnding(char* nextStage) {
    system("cls");
    Show_Box();
    gotoxy(CURSOR1, CURSOR2);
    printf("성공 ! 다음 스테이지가 시작됩니다...");
    Sleep(1500); //1.5초
    system("cls");
    Show_Box();
    gotoxy(CURSOR3, CURSOR2);
    printf("%s", nextStage);
    Sleep(1500); //1.5초
    system("cls");
}

void ending(int score) {
    system("cls");
    Show_Box();
    gotoxy(CURSOR1, CURSOR2);
    printf("총 얻은 점수는... ");
    Sleep(2000);
    printf("%d 점 입니다! 축하합니다.", score);
    Sleep(1500);
    system("cls"); //다시 하시겠습니까? 물어볼때 점수 남길지 지울지 결정 필요
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
void show_string(char* cnt)
{
    int x = 127 / 2 - strlen(word1[*cnt]) / 2;

    gotoxy(x, 10);
    printf("%s\n", word1[*cnt]);
    gotoxy(x, 19);
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
    printf("                    ");   // 업데이트
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


// 김태영
// 남은 시간에 따른 점수
void time_score()
{
    timescore = 150 * ((double)remain_time / timeLimit);
    score += timescore;
}
// 점수 출력 시 쉬운 거, 어려운 거 같이 +1 됨
// 유아기 점수 출력
void show_score_CHILD()
{
    score += 50 * update_correct() + 80 * update_difficult() + CHILD_CLEAR;
}
// 청년기 점수 출력
void show_score_ADOLESENT()
{
    score += 50 * update_correct() + 80 * update_difficult() + ADOLESENT_CLEAR;
}
// 노년기 점수 출력
void show_score_OLD()
{
    score += 50 * update_correct() + 80 * update_difficult() + OLD_CLEAR;
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

void LevelScore(int level)
{
    if (level == 1)
        show_score_CHILD();
    else if (level == 2)
        show_score_ADOLESENT();
    else
        show_score_OLD();
}

// 조현영
void timeprint(int timeLimit, int leveltime, int i, int j, int istyped) {
    // do-while문 삭제 - main 내에서 무한루프
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