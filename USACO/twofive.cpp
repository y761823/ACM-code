/*
ID: y7618231
PROG: twofive
LANG: C++11
*/
#ifdef OYK_JUDGE
#define longformat "%I64d"
#else
#define longformat "%lld"
#endif // OYK_JUDGE

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXN = 8;
const int INF = 0x3f3f3f3f;

int dp[6][6][6][6][6];
char str[29], s[29], op;
int n = 5, cnt, m;

bool check(int pos, int dep) {
    return !s[pos] || s[pos] == dep + 'A';
}

int dfs(int a, int b, int c, int d, int e, int dep) {
    if(dep == 25) return 1;
    int &res = dp[a][b][c][d][e];
    if(res != -1) return res;
    res = 0;
    if(a < 5 && check(a, dep)) res += dfs(a + 1, b, c, d, e, dep + 1);
    if(b < a && check(b + 5, dep)) res += dfs(a, b + 1, c, d, e, dep + 1);
    if(c < b && check(c + 10, dep)) res += dfs(a, b, c + 1, d, e, dep + 1);
    if(d < c && check(d + 15, dep)) res += dfs(a, b, c, d + 1, e, dep + 1);
    if(e < d && check(e + 20, dep)) res += dfs(a, b, c, d, e + 1, dep + 1);
    return res;
}

int main() {
#ifndef OYK_JUDGE
    freopen("twofive.in", "r", stdin); freopen("twofive.out", "w", stdout);
#endif // OYK_JUDGE
    scanf(" %c", &op);
    if(op == 'N') {
        scanf("%d", &m);
        for(int i = 0; i < 25; ++i) {
            for(s[i] = 'A'; s[i] <= 'Z'; ++s[i]) {
                memset(dp, -1, sizeof(dp));
                int tmp = dfs(0, 0, 0, 0, 0, 0);
                if(m > tmp) m -= tmp;
                else break;
            }
        }
        puts(s);
    } else {
        scanf("%s", str);
        int res = 1;
        for(int i = 0; i < 25; ++i) {
            for(s[i] = 'A'; s[i] < str[i]; ++s[i]) {
                memset(dp, -1, sizeof(dp));
                res += dfs(0, 0, 0, 0, 0, 0);
            }
        }
        printf("%d\n", res);
    }
}
