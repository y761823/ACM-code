/*
ID: y7618231
PROG: rectbarn
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
#include <vector>
using namespace std;

typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXP = 30010;
const int MAXN = 3010;
const int INF = 0x3f3f3f3f;

vector<int> dam[MAXN];
int up[2][MAXN], left[2][MAXN], right[2][MAXN];
int R, C, P;

int solve() {
    int res = 0, now = 0, pre = 1;
    for(int c = 1; c <= C; ++c) {
        up[now][c] = 0;
        left[now][c] = 1;
        right[now][c] = C;
    }
    for(int row = 1; row <= R; ++row) {
        swap(now, pre);
        for(size_t i = 0; i + 1 < dam[row].size(); ++i) {
            int l = dam[row][i], r = dam[row][i + 1];
            up[now][l] = 0;
            left[now][l] = 1;
            right[now][l] = C;
            for(int c = l + 1; c < r; ++c) {
                up[now][c] = up[pre][c] + 1;
                left[now][c] = max(l + 1, left[pre][c]);
                right[now][c] = min(r - 1, right[pre][c]);
                res = max(res, up[now][c] * (right[now][c] - left[now][c] + 1));
            }
        }
    }
    return res;
}

int main() {
#ifndef OYK_JUDGE
    freopen("rectbarn.in", "r", stdin); freopen("rectbarn.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%d%d%d", &R, &C, &P);
    for(int i = 0, r, c; i < P; ++i) {
        scanf("%d%d", &r, &c);
        dam[r].push_back(c);
    }
    for(int r = 1; r <= R; ++r) {
        dam[r].push_back(0), dam[r].push_back(C + 1);
        sort(dam[r].begin(), dam[r].end());
        dam[r].erase(unique(dam[r].begin(), dam[r].end()), dam[r].end());
    }
    printf("%d\n", solve());
}
