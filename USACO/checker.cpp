/*
ID: y7618231
PROG: checker
LANG: C++11
*/
#ifdef OYK_JUDGE
#define longformat "%I64d"
#else
#define longformat "%lld"
#endif // OYK_JUDGE

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

int res[3][13], tmp[13];
int n, ans, uplimit;

void dfs(int row, int ld, int rd) {
    if(row == uplimit) {
        if(ans < 3) memcpy(res[ans], tmp, sizeof(tmp));
        ++ans;
        return ;
    } else {
        int pos = uplimit & ~(row | ld | rd);
        while(pos) {
            int low = pos & -pos;
            if(ans < 3) tmp[__builtin_popcount(row)] = low;
            dfs(row + low, (ld + low) << 1, (rd + low) >> 1);
            pos -= low;
        }
    }
}

int main() {
#ifndef OYK_JUDGE
    freopen("checker.in", "r", stdin); freopen("checker.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%d", &n);
    uplimit = (1 << n) - 1;
    dfs(0, 0, 0);
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < n; ++j) {
            printf("%d", 1 + __builtin_ctz(res[i][j]));
            putchar(j == n - 1 ? '\n' : ' ');
        }
    }
    printf("%d\n", ans);
}
