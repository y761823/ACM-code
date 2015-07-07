////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-03-16 21:01:02
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 2487
////Problem Title: 
////Run result: Accept
////Run time:0MS
////Run memory:328KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAX = 110;

char mat[MAX][MAX];
int n, m;

bool top(char c) {
    int max_x = 0, min_x = MAX, max_y = 0, min_y = MAX;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            if(mat[i][j] != c) continue;
            max_x = max(max_x, j);
            min_x = min(min_x, j);
            max_y = max(max_y, i);
            min_y = min(min_y, i);
        }
    }
    if(max_x - min_x < 2 || max_y - min_y < 2) return false;
    for(int i = min_y; i <= max_y; ++i)
        if(mat[i][max_x] != c || mat[i][min_x] != c) return false;
    for(int i = min_x; i <= max_x; ++i)
        if(mat[max_y][i] != c || mat[min_y][i] != c) return false;
    for(int i = min_y + 1; i < max_y; ++i) {
        for(int j = min_x + 1; j < max_x; ++j)
            if(mat[i][j] != '.') return false;
    }
    return true;
}

int main() {
    while(scanf("%d%d", &n, &m) != EOF) {
        if(n == 0 && m == 0) break;
        for(int i = 1; i <= n; ++i) scanf("%s", &mat[i][1]);
        for(char c = 'A'; c <= 'Z'; ++c)
            if(top(c)) printf("%c", c);
        puts("");
    }
}