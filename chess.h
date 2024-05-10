#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<windows.h>

#define ROW 15
#define COL 15
#define SIZE 15
#define NINF -100000000
#define PINF 100000000
#define KILLDEPTH 12 //杀棋深度
#define DEPTH 4 //深度
#define WIDTH 45 //备选子个数

#define longlong  long long
#define CHARSIZE 2
typedef struct Point{
	int x;
	int y;

}Point;
typedef struct Move{
	int score;
	Point p;
}Move;
typedef struct Info {
    int more;//长连
    int win5;//20000000
    int alive4;//活4
    int dalive4;//冲4 10000
    int dead4;//死4 5000
    int alive3;//活3 10000
    int dalive3;//眠3 1000
    int dead3;//死3 500
    int alive2; //活2 1000
    int dalive2; //眠2 200
    int dead2; //死2 50
    int alive1; //活1 100
    int dalive1; //眠1 10
    int dead1; //死1 5
}Info;
extern int AC_Board[ROW][COL];//存储数据的棋盘
extern int id;//先后手
extern int num;//总棋子数
extern int bot_x, bot_y;//电脑最后落子
//main.c

void init_Board(void);
void inner_out(void);
void display_Board(void);
void changeCurrent(Point p, int player);
void menu(void);
//maxmin.c
longlong minmax(int depth, longlong alpha, longlong beta, int player);
longlong alphaBeta(int depth, longlong alpha, longlong beta, int player, Point p);
int inspire_Find(Move* s, int player);
void shellSort(Move* s, int len);
int Check_kill(void);
int maxKill(int depth, Point p);
int minKill(int depth, Point p);
int Search_BotKill(Move* move);
int Search_HumKill(Move* move);
//score.c
Point nextPoint(Point p, int d, int di);
int inBoard(Point p);
void search_around(Point p, int d, int* s, int way, int player);
int search_inf(Point p, int d, int* left, int* right, int player);
int singleScore(Point p, int player);
longlong Check_Score(int player);
Info typeAnalysis(int length, int* left, int* right, int player);
Info getInfo(Point p, int player);
int forbiddenCheck(Point p, int player);
//choice.c
void clear(void);
void set(Point p, int player);
void unSet(Point p);
int opp(int player);
void Player(void);
void Computer(void);
int CheckWin(int x, int y);
int OutputExhibt(void);