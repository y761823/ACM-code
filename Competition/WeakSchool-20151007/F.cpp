#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)

const int MAXN = 22;
const int MAXM = 510;
const int INF = 0x3f3f3f3f;

int mat[MAXN][MAXM];
int list[MAXN];
int T, n, m;

int calc(int cnt) {
    int maxdp[2] = {0}, res = -INF;
    for(int i = 0; i < m; ++i) {
        int b = 0, odd = (i & 1);
        for(int j = 0; j < cnt; ++j)
            b += mat[list[j]][i];
        b += maxdp[odd ^ 1];
        maxdp[odd] = max(b, maxdp[odd]);
        res = max(res, b);
    }
    return res;
}

int dfs(int cnt) {
    int res = calc(cnt);
    for(int &i = list[cnt] = list[cnt - 1] + 1; i < n; i += 2)
        res = max(res, dfs(cnt + 1));
    return res;
}

int solve() {
    int res = -INF;
    for(int &i = list[0] = 0; i < n; ++i)
        res = max(res, dfs(1));
    return res;
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                scanf("%d", &mat[i][j]);
            }
        }
        printf("Case #%d: %d\n", t, solve());
    }
}
