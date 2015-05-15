/*
ID: y7618231
PROG: camelot
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
#include <numeric>
#include <queue>
#include <tuple>
using namespace std;
typedef long long LL;

const int MAXN = 33;
const int INF = 0x3f3f3f3f;

int fr[] = {-1, -2, -2, -1, 1, 2, 2, 1};
int fc[] = {-2, -1, 1, 2, 2, 1, -1, -2};

int disa[MAXN][MAXN][MAXN][MAXN], disb[MAXN][MAXN][MAXN][MAXN];
int mat[MAXN][MAXN];
int n, m, sr, sc;

bool check(int r, int c) {
    return 1 <= r && r <= n && 1 <= c && c <= m;
}

#define DISA disa[ar][ac]
#define DISB disb[ar][ac]
void get_disa(int ar, int ac) {
    queue<pair<int, int>> que; que.push(make_pair(ar, ac));
    DISA[ar][ac] = 0;
    while(!que.empty()) {
        int r = que.front().first, c = que.front().second; que.pop();
        for(int f = 0; f < 8; ++f) {
            int nr = r + fr[f], nc = c + fc[f];
            if(check(nr, nc) && DISA[nr][nc] == INF) {
                DISA[nr][nc] = DISA[r][c] + 1;
                que.push(make_pair(nr, nc));
            }
        }
    }
}

void get_disb(int ar, int ac) {
    priority_queue<tuple<int, int, int>> que;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j) {
            DISB[i][j] = DISA[i][j] + max(abs(i - sr), abs(j - sc));
            que.push(make_tuple(-DISB[i][j], i, j));
        }
    while(!que.empty()) {
        int d = -get<0>(que.top()), r = get<1>(que.top()), c = get<2>(que.top()); que.pop();
        if(d != DISB[r][c]) continue;
        for(int f = 0; f < 8; ++f) {
            int nr = r + fr[f], nc = c + fc[f];
            if(check(nr, nc) && d + 1 < DISB[nr][nc]) {
                DISB[nr][nc] = d + 1;
                que.push(make_tuple(-DISB[nr][nc], nr, nc));
            }
        }
    }
}

int solve() {
    memset(disa, 0x3f, sizeof disa);
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j) get_disa(i, j), get_disb(i, j);
    int res = INF;
    for(int tr = 1; tr <= n; ++tr) {
        for(int tc = 1; tc <= m; ++tc) {
            bool flag = true;
            int sum = 0;
            for(int r = 1; flag && r <= n; ++r)
                for(int c = 1; flag && c <= m; ++c) {
                    if(mat[r][c] && disa[tr][tc][r][c] == INF) flag = false;
                    sum += mat[r][c] * disa[tr][tc][r][c];
                }
            if(!flag) continue;
            res = min(res, sum + max(abs(sr - tr), abs(sc - tc)));
            for(int r = 1; r <= n; ++r)
                for(int c = 1; c <= m; ++c) if(mat[r][c])
                    res = min(res, sum - disa[tr][tc][r][c] + disb[r][c][tr][tc]);
        }
    }
    return res;
}

int main() {
#ifndef OYK_JUDGE
    freopen("camelot.in", "r", stdin); freopen("camelot.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%d%d", &n, &m);
    char r; int c;
    scanf(" %c%d", &r, &c);
    sr = c, sc = r - 'A' + 1;
    while(scanf(" %c%d", &r, &c) != EOF) {
        mat[c][r - 'A' + 1]++;
    }
    printf("%d\n", solve());
}
