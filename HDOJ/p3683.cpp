////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-03-24 18:28:44
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 3683
////Problem Title: 
////Run result: Accept
////Run time:31MS
////Run memory:336KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 17;

int mat[MAXN][MAXN];
int n = 15, m;
int win[2];

int fx[] = {-1, -1, -1, 0};
int fy[] = {-1, 0, 1, 1};

bool check(int x, int y) {
    for(int i = 0; i < 4; ++i) {
        int a = 1, b = 1;
        while(mat[x][y] == mat[x + a * fx[i]][y + a * fy[i]]) ++a;
        while(mat[x][y] == mat[x - b * fx[i]][y - b * fy[i]]) ++b;
        if(a + b >= 6) return true;
    }
    return false;
}

void checkWin() {
    win[0] = win[1] = 0;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            if(mat[i][j] == -1) {
                mat[i][j] = 1;
                win[1] += check(i, j);
                mat[i][j] = 0;
                win[0] += check(i, j);
                mat[i][j] = -1;
            }
        }
    }
}

void getWin(int &x, int &y, int player) {
    for(x = 1; x <= n; ++x)
        for(y = 1; y <= n; ++y) {
            if(mat[x][y] != -1) continue;
            mat[x][y] = player;
            if(check(x, y)) return ;
            mat[x][y] = -1;
        }
}

char name[2][10] = {"white", "black"};

void solve(int player) {
    checkWin();
    if(win[player] >= 1) {
        int x, y;
        getWin(x, y, player);
        printf("Place %s at (%d,%d) to win in 1 move.\n", name[player], x - 1, y - 1);
        return ;
    }
    if(win[player ^ 1] >= 2) {
        puts("Lose in 2 moves.");
        return ;
    }
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            if(mat[i][j] != -1) continue;
            mat[i][j] = player;
            checkWin();
            mat[i][j] = -1;
            if(win[player ^ 1] >= 1) continue;
            else if(win[player] >= 2) {
                printf("Place %s at (%d,%d) to win in 3 moves.\n", name[player], i - 1, j - 1);
                return ;
            }
        }
    }
    puts("Cannot win in 3 moves.");
}

int main() {
    while(scanf("%d", &m) != EOF && m) {
        memset(mat, -1, sizeof(mat));
        int black = 0, white = 0;
        for(int i = 0, x, y; i < m; ++i) {
            scanf("%d%d", &x, &y);
            ++x, ++y;
            scanf("%d", &mat[x][y]);
            black += (mat[x][y] == 1);
            white += (mat[x][y] == 0);
        }
        if(black == white) solve(1);
        else if(black == white + 1) solve(0);
        else puts("Invalid.");
    }
}
