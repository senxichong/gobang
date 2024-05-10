#include"chess.h"

int bot_x, bot_y;
int Search_BotKill(Move* move) {
    int length = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (AC_Board[i][j] == 0) {
                Point p = { i, j };
                if (Check_Around(p) && !forbiddenCheck(p, id)) {
                    int score = singleScore(p, id);
                    if (score > 5000) {
                        move[length].score = score;
                        move[length++].p = p;
                    }
                }
            }
        }
    }
    shellSort(move, length);
    return length;
}


int Search_HumKill(Move* move) {
    int length = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (AC_Board[i][j] == 0) {
                Point p = { i, j };
                if (Check_Around(p) && !forbiddenCheck(p, opp(id))) {
                    int score = singleScore(p, opp(id));
                    if (!forbiddenCheck(p, id)) {
                        score += singleScore(p, id);
                    }
                    if (score > 5000) {
                        move[length].score = score;
                        move[length++].p = p;
                    }
                }
            }
        }
    }
    shellSort(move, length);
    return length;
}

int Check_Around(Point p) {
    if (num == 1 || num == 2) {
        for (int i = 0; i < 4; i++) {
            for (int j = -1; j <= 1; j++) {
                if (j != 0) {
                    Point np = nextPoint(p, i, j);
                    if (inBoard(np) && AC_Board[np.x][np.y] == 1)
                        return 1;
                }
            }
        }
    }
    else {
        for (int i = 0; i < 4; i++) {
            for (int j = -2; j <= 2; j++) {
                if (j != 0) {
                    Point np = nextPoint(p, i, j);
                    if (inBoard(np) && AC_Board[np.x][np.y] != 0)
                        return 1;
                }
            }
        }
    }
    return 0;
}

longlong minmax(int depth, longlong alpha, longlong beta, int player) {
    Move moves[224];
    int length = inspire_Find(moves, player);
    if (length > WIDTH)
        length = WIDTH - rand() % 3;

    for (int i = 0; i < length; i++) {
        set(moves[i].p, player);
        longlong temp = -alphaBeta(depth - 1, -beta, -alpha, opp(player), moves[i].p);//ตÝน้
        unSet(moves[i].p);
        if (temp >= beta) {
            return beta;
        }
        if (temp > alpha) {
            alpha = temp;
            bot_x = moves[i].p.x;
            bot_y = moves[i].p.y;
        }
    }
    return alpha;
}

longlong alphaBeta(int depth, longlong alpha, longlong beta, int player, Point p) {
    if (CheckWin(p.x, p.y))
        return Check_Score(player);
    if (depth == 0 || num == SIZE * SIZE) {
        return Check_Score(player);
    }

    Move moves[224];
    int length = inspire_Find(moves, player);
    if (length > WIDTH)
        length = WIDTH - rand() % 3;

    for (int i = 0; i < length; i++) {
        set(moves[i].p, player);
        longlong temp = -alphaBeta(depth - 1, -beta, -alpha, opp(player), moves[i].p);
        unSet(moves[i].p);
        if (temp >= beta) {
            return beta;
        }
        if (temp > alpha) {
            alpha = temp;
        }
    }
    return alpha;
}

int inspire_Find(Move* scoreBoard, int player) {
    int length = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (AC_Board[i][j] == 0) {
                Point p = { i, j };

                if (Check_Around(p) && !forbiddenCheck(p, player)) {
                    scoreBoard[length].score = singleScore(p, player);
                    if (!forbiddenCheck(p, opp(player))) {
                        scoreBoard[length].score += singleScore(p, opp(player));
                    }
                    scoreBoard[length++].p = p;
                }
            }
        }
    }
    shellSort(scoreBoard, length);
    return length;
}


void shellSort(Move* s, int len) {
    int i, j, gap;
    Move temp;
    for (gap = len / 2; gap > 0; gap /= 2) {
        for (i = gap; i < len; i += 1) {
            for (j = i - gap; j >= 0 && s[j].score < s[j + gap].score; j -= gap) {
                temp = s[j + gap];
                s[j + gap] = s[j];
                s[j] = temp;
            }
        }
    }
}


int Check_kill(void) {
    int depth = KILLDEPTH;
    Move kill[100];
    int length = Search_BotKill(kill);
    if (length == 0)
        return 0;
    if (length > 9)
        depth = 8;
    for (int i = 0; i < length; i++) {
        set(kill[i].p, id);
        int killed = minKill(depth - 1, kill[i].p);
        unSet(kill[i].p);
        if (killed) {
            bot_x = kill[i].p.x;
            bot_y = kill[i].p.y;
            return 1;
        }
    }
    return 0;
}


int maxKill(int depth, Point p) {
    if (CheckWin(p.x, p.y))
        return 0;
    if (depth == 0)
        return 0;

    Move kill[100];
    int length = Search_BotKill(kill);
    if (length == 0)
        return 0;
    for (int i = 0; i < length; i++) {
        set(kill[i].p, id);
        int killed = minKill(depth - 1, kill[i].p);
        unSet(kill[i].p);
        if (killed) {
            return 1;
        }
    }
    return 0;
}


int minKill(int depth, Point p) {
    if (CheckWin(p.x, p.y))
        return 1;
    if (depth == 0)
        return 0;

    Move kill[100];
    int length = Search_HumKill(kill);
    if (length == 0)
        return 0;
    for (int i = 0; i < length; i++) {
        set(kill[i].p, opp(id));
        int killed = maxKill(depth - 1, kill[i].p);
        unSet(kill[i].p);
        if (!killed) {
            return 0;
        }
    }
    return 1;
}



