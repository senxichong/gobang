#include"chess.h"

char EmptyBoard[SIZE+1][SIZE * CHARSIZE + 16] =
{
		"┏┯┯┯┯┯┯┯┯┯┯┯┯┯┓",
	   
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┗┷┷┷┷┷┷┷┷┷┷┷┷┷┛"
};

//此数组存储用于显示的棋盘 
char displayBoard[SIZE][SIZE * CHARSIZE + 1];

char player_1_set[] = "●";//黑棋子;
char palyer_1_cuset[] = "▲"; //黑棋子最后落子

char player_2_set[] = "◎";//白棋子;
char player_2_cuset[] = "△";//白棋子最后落子


int AC_Board[SIZE][SIZE];
void display_Board(void) {
	int i;
	
	for (i = 0; i < SIZE; i++) {
		printf("%3d %2s\n", SIZE - i, displayBoard[i]);
	}
	printf("    ");
	for (i = 0; i < SIZE; i++)
		printf("%2c", 'A' + i);
	printf("\n");
}
void changeCurrent(Point p, int player) {
	if (player == 1) {
		displayBoard[p.x][CHARSIZE * p.y] = palyer_1_cuset[0];
		displayBoard[p.x][CHARSIZE * p.y + 1] = palyer_1_cuset[1];
	}
	else if (player == 2) {
		displayBoard[p.x][CHARSIZE * p.y] = player_2_cuset[0];
		displayBoard[p.x][CHARSIZE * p.y + 1] = player_2_cuset[1];
	}
}
void init_Board(void) {
	int i, j;
	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++)
			AC_Board[i][j] = 0;
}


void inner_out(void) {

	int i, j;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j <= SIZE * CHARSIZE - 1; j++) {
			displayBoard[i][j] = EmptyBoard[i][j];
		}
	}

	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			if (AC_Board[i][j] == 1) {
				displayBoard[i][CHARSIZE * j] = player_1_set[0];
				displayBoard[i][CHARSIZE * j + 1] = player_1_set[1];
			}
			else if (AC_Board[i][j] == 2) {
				displayBoard[i][CHARSIZE * j] = player_2_set[0];
				displayBoard[i][CHARSIZE * j + 1] = player_2_set[1];
			}
		}
	}
}





