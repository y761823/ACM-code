#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;

const int MAXN = 1010;
const int INF = 0x3f3f3f3f;

int fx[] = {0, 1, 0, -1};
int fy[] = {1, 0, -1, 0};

bool vis[MAXN][4];
int x[MAXN], y[MAXN];
int n;

int sgn(int x) {
    return (x > 0) - (x < 0);
}

int find_target(int nowx, int nowy, int f) {
    int res = -1, tmp = INF;
    for(int i = 0; i < n; ++i) {
        if(sgn(x[i] - nowx) == sgn(fx[f]) && sgn(y[i] - nowy) == sgn(fy[f])) {
            int d = abs(x[i] - nowx) + abs(y[i] - nowy);
            if(d < tmp) res = i, tmp = d;
        }
    }
    return res;
}

int solve() {
    memset(vis, 0, n * sizeof(vis[0]));
    int nowx = 0, nowy = 0, f = 1, step = 0;
    while(true) {
        int t = find_target(nowx, nowy, f);
        if(t == -1) return step;
        if(vis[t][f]) return -1;
        vis[t][f] = true;
        nowx = x[t] - fx[f]; nowy = y[t] - fy[f];
        f = (f + 1) & 3;
        step++;
    }
}

int main() {
    while(scanf("%d", &n) != EOF) {
        for(int i = 0; i < n; ++i)
            scanf("%d%d", &x[i], &y[i]);
        printf("%d\n", solve());
    }
}
