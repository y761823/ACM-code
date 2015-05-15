/*
ID: y7618231
PROG: milk4
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
#include <numeric>
#include <set>
#include <deque>
#include <queue>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXN = 110;
const int seed = 313;
const int MOD = 1000000007;

int a[MAXN], ans[MAXN], cur[MAXN];
int q, n, maxdep;
bool flag;

void dfs(int i, int depth, int rest) {
    if(depth == maxdep) {
        if(rest == 0) {
            memcpy(ans, cur, n * sizeof(int));
            flag = true;
        }
    } else {
        if(i == n || ans[depth] < a[i]) return ;
        cur[depth] = a[i];
        for(int cnt = 1; cnt * a[i] <= rest; ++cnt)
            dfs(i + 1, depth + 1, rest - cnt * a[i]);
        dfs(i + 1, depth, rest);
    }
}

int main() {
#ifndef OYK_JUDGE
    freopen("milk4.in", "r", stdin); freopen("milk4.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%d%d", &q, &n);
    for(int i = 0; i < n; ++i) scanf("%d", &a[i]);
    sort(a, a + n);
    memset(ans, 0x3f, n * sizeof(int));
    for(maxdep = 1; maxdep <= n; ++maxdep) {
        dfs(0, 0, q);
        if(flag) break;
    }
    printf("%d", maxdep);
    for(int i = 0; i < maxdep; ++i) printf(" %d", ans[i]);
    puts("");
}
