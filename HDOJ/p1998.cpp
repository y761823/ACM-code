////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-03-16 21:06:42
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 1998
////Problem Title: 
////Run result: Accept
////Run time:0MS
////Run memory:944KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long LL;

const int MAXN = 20 * 20;

int mat[MAXN][MAXN];
int n;

int youshang(int x, int y) {
    ++x, --y;
    if(x > n) x = 1;
    if(y < 1) y = n;
    return mat[y][x];
}

void turn_up(int &x, int &y) {
    ++y;
    if(y > n) y = n;
}

void turn_youshang(int &x, int &y) {
    ++x, --y;
    if(x > n) x = 1;
    if(y < 1) y = n;
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        memset(mat, 0, sizeof(mat));
        int x = n / 2 + 1, y = 1;
        for(int i = 1; i <= n * n; ++i) {
            mat[y][x] = i;
            if(i == n * n) break;
            if(youshang(x, y)) turn_up(x, y);
            else turn_youshang(x, y);
        }
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) printf("%4d", mat[i][j]);
            //rintf("%4d\n", mat[i][n]);
            puts("");
        }
    }
}