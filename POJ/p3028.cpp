#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;

const int MAXN = 13;
const double EPS = 1e-8;

int T, n;
double dp[MAXN][(1 << MAXN) + 10][MAXN];
double p[MAXN];

inline int sgn(double x) {
    return (x > EPS) - (x < -EPS);
}

int Tnext[1 << MAXN][MAXN];

inline int next(int state, int x) {
    if(Tnext[state][x] != -1) return Tnext[state][x];
    int ret = x;
    while(true) {
        if(++ret == n) ret = 0;
        if(state & (1 << ret)) break;
    }
    return Tnext[state][x] = ret;
}

inline int count(int state) {
    int ret = 0;
    while(state) {
        ret += state & 1;
        state >>= 1;
    }
    return ret;
}

int c[MAXN][MAXN];
double b[MAXN][MAXN], maxb[MAXN];

void dfs(int state, int cur) {
    if(dp[cur][state][0] != -1) return ;
    if(count(state) == 1) {
        for(int i = 0; i < n; ++i) dp[cur][state][i] = (i == cur);
        return ;
    }

    for(int i = 0; i < n; ++i) {
        if((state & (1 << i)) == 0) continue;
        for(int tar = next(state, i); tar != i; tar = next(state, tar)) {
            int newState = state ^ (1 << tar), nx = next(newState, i);
            dfs(newState, nx);
        }
    }

    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j) b[i][j] = c[i][j] = 0;
    for(int i = 0; i < n; ++i) maxb[i] = 0;

    for(int i = 0; i < n; ++i) {
        if((state & (1 << i)) == 0) continue;
        for(int tar = next(state, i); tar != i; tar = next(state, tar)) {
            int newState = state ^ (1 << tar), nx = next(newState, i);
            maxb[i] = max(maxb[i], dp[nx][newState][i]);
        }
        for(int tar = next(state, i); tar != i; tar = next(state, tar)) {
            int newState = state ^ (1 << tar), nx = next(newState, i);
            if(sgn(maxb[i] - dp[nx][newState][i]) == 0) {
                for(int k = 0; k < n; ++k) {
                    ++c[i][k];
                    b[i][k] += dp[nx][newState][k];
                }
            }
        }
        for(int k = 0; k < n; ++k) b[i][k] /= c[i][k];
    }

    for(int k = 0; k < n; ++k) dp[cur][state][k] = p[cur] * b[cur][k];

    for(int k = 0; k < n; ++k) {
        if((state & (1 << k)) == 0) continue;
        int now = cur;
        double tmp = 1, sum = 0;
        do {
            now = next(state, now);
            sum += tmp * p[now] * b[now][k];
            tmp *= (1 - p[now]);
        } while(cur != now);
        dp[cur][state][k] += sum / (1 - tmp) * (1 - p[cur]);
    }
}

void solve() {
    dfs((1 << n) - 1, 0);
    for(int i = 0; i < n - 1; ++i) printf("%.2f ", 100 * dp[0][(1 << n) - 1][i]);
    printf("%.2f\n", 100 * dp[0][(1 << n) - 1][n - 1]);
}

int main() {
    memset(Tnext, -1, sizeof(Tnext));
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 0; i < n; ++i) scanf("%lf", &p[i]), p[i] /= 100;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < (1 << n); ++j) dp[i][j][0] = -1;
        solve();
    }
}

