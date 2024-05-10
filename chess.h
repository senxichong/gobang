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
#define KILLDEPTH 12 //ɱ�����
#define DEPTH 4 //���
#define WIDTH 45 //��ѡ�Ӹ���

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
    int more;//����
    int win5;//20000000
    int alive4;//��4
    int dalive4;//��4 10000
    int dead4;//��4 5000
    int alive3;//��3 10000
    int dalive3;//��3 1000
    int dead3;//��3 500
    int alive2; //��2 1000
    int dalive2; //��2 200
    int dead2; //��2 50
    int alive1; //��1 100
    int dalive1; //��1 10
    int dead1; //��1 5
}Info;
extern int AC_Board[ROW][COL];//�洢���ݵ�����
extern int id;//�Ⱥ���
extern int num;//��������
extern int bot_x, bot_y;//�����������
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