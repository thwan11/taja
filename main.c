#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>

#define CHILD_CLEAR 1500
#define ADOLESENT_CLEAR 3000
#define OLD_CLEAR 4500

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
void modeSelect(); //모드 선택 함수
void levelSelect(); //난이도 선택 함수
void update_best_score(int);//최고점수 5개 저장하는 함수
void shuffle(int*, int);
void hard_shuffle(int*, int, int);
void printMent(int);

int best[5] = { 0,0,0,0,0 };
int score;
int mode = 1;
int menu;//메뉴호출
int* p_menu = &menu;
int timescore;               //남는 시간에 따른 추가 점수
int n = 0;                    //콤보
int level;                      //06.02김태영 level에 따라 단어배열 대입다르게 해야하므로 전역변수로 선언
int health;
int ment;
int er = 0;
int word[SIZE];
char* word1[SIZE] = { "arrive","bicycle","bring","button"
    ,"monkey","nurse","parent","strawberry","supermarket","tomorrow","yesterday","pediatric asthma","Autoi","Measles","Answer" };
//06.02김태영 난이도 따른 단어 배열 추가
char* word2[SIZE] = { "marriage","university","employment" ,"unemployment"
, "campus","certificate" ,"culture" ,"military","internet", "challenge", "start up","bitcoin", "Panic","Apartment","Dyspepsia" };
char* word3[SIZE] = { "nursing home","retire","funeral","denture","mature","wise",
"memory","gray hair","travel","sapient","hospital","experience","Senile dementia","Kodokushi","Glaucoma" };
char* word4[SIZE] = { "kindergarten","bicycle","picky eating","pediatrician"
    ,"report card","immature","patent","strawberry","supermarket","tomorrow","key harmonica","yesterday","Pediatric asthma","Measles vaccine","Answer" };
char* word5[SIZE] = { "congratulatory money","university","employment" ,"severance pay"
, "graduate school","certificate" ,"culture" ,"stock investment","internet", "challenge", "anaphylaxis","bitcoin", "Apartment","Dyspepsia" ,"Adolesent" }; //15
char* word6[SIZE] = { "nursing home","ventilation","funeral","elderly depression","mentally mature","hale and harty",
"homesickness","rheumatism","osteoporosis","sapient","hospital","experience","Senile dementia","Kodokushi","Glaucoma" }; //15

int main()
{
    char ch;                  //현재점수 보는 화면에서 원래화면으로 돌아가기
    int n;                  //콤보
    int start;      //start: 게임시작여부 입력 06.02김태영 level 전역변수로 선언
    int lvlList[6] = { 1,2,3,4,5,6 };
    system("mode con cols=128 lines=32");
    srand(time(0));
    while (1)
    {
        while (1)
        {
            /*콤보초기화 필요*/n = 0;
            update_best_score(score);
            score = 0;
            system("cls");
            Show_Box();
            gotoxy(50, 8);
            printf("1.게임시작\n");
            gotoxy(50, 12);
            printf("2.게임종료\n");
            gotoxy(50, 16);
            printf("3.점수순위보기\n");
            gotoxy(50, 20);
            printf("4.옵션");
            gotoxy(50, 23);
            scanf("%d", &start);    // 예외처리 됨
            while (getchar() != '\n');
            if (start >= 1 && start <= 4)
                break;
        }

        if (start == 1)
        {
            if (mode == 1) {
                levelSelect();
                ment = level;

                for (; level <= 3; level++, ment++)
                {
                    system("cls");
                    Show_Box();
                    gotoxy(50, 10);
                    ShowLevel(level);
                    Sleep(3000);
                    printMent(ment);
                    system("cls");
                    typing_game();
                    if ((*p_menu) == 2) {
                        score = 0;
                        break;
                    }
                    if ((*p_menu) == 3) {
                        break;
                    }
                    if (health <= 0)//06.03 김태영 체력이 다 닳아도 클리어되는것 수정
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
                if (health <= 0 || (*p_menu) == 2)
                {
                    (*p_menu) = 0;
                    continue;
                }
                ment = 4;
                printMent(ment);
            }
            else if (mode == 2) {
                levelSelect();
                ment = level;

                for (; level <= 3; level++, ment++)
                {
                    system("cls");
                    Show_Box();
                    gotoxy(50, 10);
                    ShowLevel(level);
                    Sleep(3000);
                    printMent(ment);
                    system("cls");
                    typing_game();
                    if ((*p_menu) == 2) {
                        score = 0;
                        break;
                    }
                    if ((*p_menu) == 3) {
                        break;
                    }
                    if (health <= 0)//06.03 김태영 체력이 다 닳아도 클리어되는것 수정
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
                if (health <= 0 || (*p_menu) == 2)
                {
                    (*p_menu) = 0;
                    continue;
                }
                ment = 4;
                printMent(ment);
            }
            else if (mode == 3) {
                system("cls");
                Show_Box();
                gotoxy(50, 12);
                printf("랜덤모드를 실행합니다.\n");
                Sleep(1000);
                shuffle(lvlList, 6);
                for (int k = 0; k < 3; k++)
                {
                    system("cls");
                    Show_Box();
                    gotoxy(50, 10);
                    printf("랜덤한 문자 선택중....");
                    Sleep(3000);
                    system("cls");
                    level = lvlList[k];

                    typing_game();
                    if ((*p_menu) == 2) {
                        score = 0;
                        break;
                    }
                    if ((*p_menu) == 3) {
                        break;
                    }
                    if (health <= 0)//06.03 김태영 체력이 다 닳아도 클리어되는것 수정
                    {
                        system("cls");
                        Show_Box();
                        gotoxy(50, 15);
                        printf("Game Over....");
                        Sleep(1500);
                        break;
                    }
                    if (k == 2)break;
                    Next_Stage();
                    score += ClearScore(level);
                }
                if (health <= 0 || (*p_menu) == 2)
                {
                    (*p_menu) = 0;
                    continue;
                }                if ((*p_menu) == 3) {
                    (*p_menu) = 0;
                    break;
                }
                system("cls");
                Show_Box();
                gotoxy(50, 12);
                printf("점수는 %d 점입니다.", score);
                Sleep(1500);
            }
        }
        if (start == 2)
        {
            // while ((ch = getchar()) != '\n');
            system("cls");
            Show_Box();
            gotoxy(50, 16);
            printf("게임을 종료합니다.\n\n\n\n\n\n\n\n\n");
            break;
        }
        if (start == 3)
        {

            while (1) {
                system("cls");
                Show_Box();
                for (int x = 0; x < 5; x++) {
                    gotoxy(50, 8 + 2 * x);
                    printf("%d. %d 점", x + 1, best[x]);
                }
                gotoxy(50, 18);
                printf("처음화면으로 돌아가려면 m을 누르시오.");
                gotoxy(50, 20);
                scanf("%c", &ch);   // 예외처리 됨
                if (ch == 'm')
                    break;
            }
        }
        if (start == 4) {
            modeSelect();
        }
        else
            continue;
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

void show_string(int* cnt)
{
    gotoxy(127 / 2 - strlen(word[*cnt]) / 2, 10);
    printf("%s\n", word[*cnt]);
    gotoxy(127 / 2 - strlen(word[*cnt]) / 2, 19);
}

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

void timeprint(int timeLimit, int leveltime, int i, int j, int istyped) {       // 수정 요함 word 1

    static int timecmp;
    static int init = 1;

    if (init)
    {
        timecmp = timeLimit;
        gotoxy(127 / 2 - 8 / 2, 15);
        printf("%2ds left", leveltime);
        gotoxy(127 / 2 - strlen(word[i]) / 2 + j, 19);   // 커서 박스로
        init = 0;
    }
    if (timecmp > leveltime)
    {
        gotoxy(127 / 2 - 8 / 2, 15);
        printf("%2ds left", leveltime);
        gotoxy(127 / 2 - strlen(word[i]) / 2 + j, 19);   // 커서 박스로
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
        scanf("%d", &menu); // 예외처리 됨
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
//게임함수
int typing_game() {
    char ch, input[ASIZE];
    int s_time, esc_time = 0, menu_time = 0, j = 0;
    int i = 0;  // 배열의 순서를 이거로 정할거라 매 게임마다 리셋해주어야함.
    int remain_time;
    int timeLimit;
    int w;//06.02 김태영 난이도에 따른 배열복사하는 for문에 필요


    if (mode == 3) {
        int idx = rand() % 6 + 1;
        level = idx;
    }
    if (mode == 2) level += 3;
    //06.02 김태영 health에 난이도에 따라 값 할당
    switch (level) {
    case 1: timeLimit = 15; health = 12; for (w = 0; w < SIZE; w++)word[w] = word1[w]; break;   // word[]에 문자열 포인터 저장
    case 2: timeLimit = 10; health = 8;  for (w = 0; w < SIZE; w++)word[w] = word2[w]; break;
    case 3: timeLimit = 10; health = 4;  for (w = 0; w < SIZE; w++)word[w] = word3[w]; break;
    case 4: timeLimit = 15; health = 12; for (w = 0; w < SIZE; w++)word[w] = word4[w]; break;   // word[]에 문자열 포인터 저장
    case 5: timeLimit = 10; health = 8;  for (w = 0; w < SIZE; w++)word[w] = word5[w]; break;
    case 6: timeLimit = 10; health = 4;  for (w = 0; w < SIZE; w++)word[w] = word6[w]; break;
    }

    int C_cnt = 12; //어려운 단어 5배수 위치에 배치
    shuffle(word, 12);
    hard_shuffle(word, 13, 3);
    for (int A = 4; A < 15; A += 5) {
        char* temp;
        temp = word[A];
        word[A] = word[C_cnt];
        word[C_cnt] = temp;
        C_cnt++;
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

        if (er == 1) {
            timeprint(timeLimit, remain_time, i, j, 1);
            er = 0;
        }
        else {
            timeprint(timeLimit, remain_time, i, j, 0);
        }

        if (_kbhit())
        {
            ch = _getch();
            if (ch == 27)
            {
                esc_time = time(0);
                Show_Menu();
                if (*p_menu == 2) {
                    er = 1;
                    esc_time = 0;
                    menu_time = 0;
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
                    show_string(&i);        // 글자 공백으로 커서만 가는 이유 show_string, print_time
                    for (int k = 0; k < i; k++)
                    {
                        printf("\b");
                    }
                    //printf("%s", input);  // 왜 안 되는지 모르겠음
                    for (int k = 0; k < j; k++)
                    {
                        printf("%c", input[k]);
                    }
                    *p_menu = 0;
                    continue;           // 공백 생기는 문제 생김
                    //goto loop;
                }
                continue;
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

        if (remain_time == 0)
        {
            system("cls");
            j = 0;
            n = 0;//콤보초기화
            health -= 2;   // 시간 초과 체력 -2
            i++;   //단어의 배열 중 다음 단어로 넘기게 됩니다
            if (i >= 15) break;   //단어의 배열이 끝나게 되면 게임을 끝낸다
            gotoxy(50, 23);
            printf("시간을 초과하였습니다!");
            Show_Box_Game();
            ShowScore();
            Show_Health(health);
            Sleep(1000);
            system("cls");
            Show_Box_Game();
            ShowScore();
            Show_Health(health);
            show_string(&i);
            s_time = time(0);
            esc_time = 0;
            menu_time = 0;
        }



        if (j >= strlen(word[i]))
        {
            input[strlen(word[i])] = 0;
            if (!strcmp(word[i], input))
            {
                if ((i == 4) || (i == 9) || (i == 14)) {
                    gotoxy(127 / 2 - 5 / 2, 22);
                    printf("축하합니다.\n");
                    Combo_score(remain_time, timeLimit);
                    time_score(remain_time, timeLimit);
                    update_difficult();
                    ShowScore();
                    gotoxy(127 / 2 - 5 / 2, 24);
                    printf("+80");
                    Sleep(1000);
                    s_time = time(0);
                    esc_time = 0;
                    menu_time = 0;
                }
                if ((i != 4) && (i != 9) && (i != 14)) {
                    gotoxy(127 / 2 - 5 / 2, 22);
                    printf("축하합니다.\n");
                    Combo_score(remain_time, timeLimit);
                    time_score(remain_time, timeLimit);
                    update_correct();
                    ShowScore();
                    gotoxy(127 / 2 - 5 / 2, 24);
                    printf("+50");
                    Sleep(1000);
                    s_time = time(0);
                    esc_time = 0;
                    menu_time = 0;
                }
                i++;   //단어의 배열 중 다음 단어로 넘기게 됩니다
                if (i >= 15) break;   //단어의 배열이 끝나게 되면 게임을 끝낸다
            }
            else {
                health--;   // 오타 체력 -1
                gotoxy(50, 23);
                printf("오타가 생겼습니다!");
                Sleep(1000);
                n = 0;//콤보초기화
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
    if (remain_time >= timeLimit - 3)   // -2 -> -3
    {
        n++;
        printf("%d combo!", n);
    }
    if (remain_time < timeLimit - 3) {
        n = 0;
        printf("%d combo!", n);
    }
    if (n == 5) {
        score += 280;
        gotoxy(50, 23);
        printf("콤보 점수 획득!");
        Sleep(1000);
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
    else if (level == 1)
        return CHILD_CLEAR * 2;
    else if (level == 2)
        return ADOLESENT_CLEAR * 2;
    else if (level == 3)
        return OLD_CLEAR * 2;
}
//모드 선택
void modeSelect() {
    while (1)
    {
        system("cls");
        Show_Box();
        gotoxy(50, 7);
        printf("인생 모드를 선택하시오.\n");
        gotoxy(50, 10);
        printf("1. 평범하게 산다\n");
        gotoxy(50, 14);
        printf("2. 도전적으로 산다\n");
        gotoxy(50, 18);
        printf("3. 운명에 맡긴다\n");
        gotoxy(50, 22);
        scanf("%d", &mode); // 예외처리 됨
        while (getchar() != '\n');
        if (mode >= 1 && mode <= 3)
            break;

    }
}

//난이도 선택
void levelSelect() {
    while (1)
    {
        system("cls");
        Show_Box();
        gotoxy(50, 7);
        if (mode == 1)
            printf("난이도를 선택하시오.\n");
        else
            printf("하드모드 난이도를 선택하시오.\n");
        gotoxy(50, 10);
        printf("1. 유아기\n");
        gotoxy(50, 14);
        printf("2. 청년기\n");
        gotoxy(50, 18);
        printf("3. 노년기\n");
        gotoxy(50, 22);
        scanf("%d", &level);    // 예외처리 됨
        while (getchar() != '\n');
        if (level >= 1 && level <= 3)
            break;
    }
}
//최고점수5개 저장하는 함수
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
void shuffle(int* arr, int num)
{
    srand(time(NULL));
    int temp;
    int rn1, rn2;
    for (int i = 0; i < num; i++) {
        rn1 = rand() % num;
        rn2 = rand() % num;
        temp = arr[rn1];
        arr[rn1] = arr[rn2];
        arr[rn2] = temp;
    }

}
void hard_shuffle(int* arr, int st, int num)
{
    srand(time(NULL));
    int temp;
    int rn1, rn2;
    for (int i = 0; i < 5; i++) {
        rn1 = rand() % num + st - 1;
        rn2 = rand() % num + st - 1;
        temp = arr[rn1];
        arr[rn1] = arr[rn2];
        arr[rn2] = temp;
    }
}

//앞, 뒤, 사이 멘트 출력 함수
void printMent(int ment) {
    system("cls");
    Show_Box();
    gotoxy(50, 8);
    switch (ment) {
    case 1:
        printf("내 나이 한 살, 인생을 시작해보자!\n"); //태영님이 작성해주실 부분.
        break;
    case 2:
        printf("열심히 공부해서 건국대학교에 입학했다!!\n");
        Sleep(1500);
        gotoxy(50, 10);
        printf("즐겁게 대학생활도 하고 공부도 열심히해야지!\n");
        Sleep(1500);
        gotoxy(50, 12);
        printf("코로나 빨리 끝났으면…\n");
        Sleep(1500);
        gotoxy(50, 14);
        printf("동기들 만나고 싶어요…");
        break;
    case 3:
        printf("그동안 열심히 공부하고 일해왔으니\n");
        Sleep(1500);
        gotoxy(50, 10);
        printf("이제 나의 시간을 보내야겠다!!");
        break;
    case 4:
        printf("지난인생을 돌이켜보니\n");
        Sleep(1500);
        gotoxy(50, 10);
        printf("좋은 인생이었다.");
        Sleep(2000);
        gotoxy(50, 14);
        printf("지금까지 %d 점 획득 !", score);
        break;
    }
    Sleep(3000);

}