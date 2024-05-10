#include"chess.h"
int end = 0;
int id = 1;
Point lp;
int num = 0;
void menu()
{
    int m;
    printf("选择模式\n");
    printf("1 ( 人人对战)\n");
    printf("2 (玩家先手（执黑）)\n");
    printf("3 ( 玩家后手（执白）)\n\n");
    printf("输入请使用小写字母 数字\n");
    scanf("%d", &m);
    clear();
    switch (m)
    {
    case 1:
        display_Board();
        while (1) {
            Player();
            if (OutputExhibt()) {
                break;
            }
        }break;
    case 2:
        display_Board();
        while (1) {
            Player();
            if (OutputExhibt()) {
                break;
            }
            Computer();
            if (OutputExhibt()) {

            }
        }break;
    case 3:
        while (1) {
            Computer();
            if (OutputExhibt()) {

            }
            Player();
            if (OutputExhibt()) {
                break;
            }
        }break;
    default:
        printf("输入错误\n");
        break;
    }
}
void set(struct Point p, int player) {
    AC_Board[p.x][p.y] = player;
    num++;
}


void unSet(Point p) {
    AC_Board[p.x][p.y] = 0;
    num--;
}

int CheckWin(int x, int y)
{
    int i, j, k;
    const int direction[4][2] = { {1,0},{0,1},{1,1},{1,-1} };
    for (i = 0; i < 4; ++i)
    {
        const int d[2] = { -1,1 };
        int count = 1;
        for (j = 0; j < 2; ++j) {
            for (k = 1; k <= 4; ++k) {
                int row = x + k * d[j] * direction[i][0];
                int col = y + k * d[j] * direction[i][1];
                if (row >= 0 && row < SIZE && col >= 0 && col < SIZE &&
                    AC_Board[x][y] == AC_Board[row][col])
                    count++;
                else
                    break;
            }
        }
        if (count >= 5)
            return 1;
    }
    return 0;
}

void Player(void)
{
    char c = 0;
    int x = 0;
    Point p = { -1,-1 };

    printf("player%d:", id);
    while (1) {
        scanf("%c %d", &c, &x);
        clear();
        p.x = 15 - x;
        p.y = c - 'a';
    
        if (c == 'r') {
            Point aip = { bot_x,bot_y };
            unSet(lp);
            unSet(aip);
            inner_out();
            display_Board();
            printf("重新输入:");
            continue;
           
        }
        else if (AC_Board[p.x][p.y] != 0 || !inBoard(p)) {
            printf("重新输入:");
            continue;
           
        }
        else {
            set(p, id);
            lp = p;
            end = CheckWin(p.x, p.y) * id;
            if (forbiddenCheck(p, id))
                end = 3;

            inner_out();
            changeCurrent(p, id);
            display_Board();
            break;
        }
    }
}


void Computer(void)
{
    int kill = 0;
    if (num == 0) {
        bot_x = 7;
        bot_y = 7;
    }
    else {
#ifndef NKILL
        kill = Check_kill();
        if (!kill) {
            printf(":(\n");
            minmax(DEPTH, NINF, PINF, id);
        }
    }
#endif
#ifdef NKILL
    minmax(DEPTH, NINF, PINF, id);
}
#endif

Point p = { bot_x,bot_y };
set(p, id);
end = CheckWin(bot_x, bot_y) * id;
inner_out();
changeCurrent(p, id);
display_Board();
if (kill)

printf("bot下在:%c%d\n", bot_y + 'A', 15 - bot_x);

}


void clear(void) {
    int c;
    while ((c = getchar()) != EOF && c != '\n')
        ;
}




int inBoard(struct Point p) {
    if (p.x >= 0 && p.x < SIZE && p.y >= 0 && p.y < SIZE)
        return 1;
    else
        return 0;
}



int opp(int player) {
    return (player == 1) ? 2 : 1;
}




int OutputExhibt(void)
{
    id = opp(id);
    if (num == SIZE * SIZE)
    {
        display_Board();
        printf("平局\n");
        return 1;
    }
    if (end == 1)
    {
        display_Board();
        printf("黑棋获胜\n");
        return 1;
    }
    if (end == 2)
    {
        display_Board();
        printf(" 白棋获胜n");
        return 1;
    }
    if (end == 3)
    {
        display_Board();
        printf("禁手\n");
        getchar();
        return 0;
    }
    return 0;
}


