#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <cmath>
using namespace std;
typedef long long LL;

const int MAXN = 110;
const int INF = 0x3f3f3f3f;

int mat[MAXN][MAXN];
int n, m, t;

void floyd() {
    for(int k = 1; k <= n; ++k)
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= n; ++j) mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
}

void solve() {
    floyd();
    int ans = 0, cnt = INF;
    for(int i = 1; i <= n; ++i) {
        int maxt = 0;
        for(int j = 1; j <= n; ++j) maxt = max(maxt, mat[i][j]);
        //if(maxt == cnt) {ans = 0; break;}
        if(maxt < cnt) ans = i, cnt = maxt;
    }
    if(ans == 0) puts("disjoint");
    else printf("%d %d\n", ans, cnt);
}

int main() {
    while(scanf("%d", &n) != EOF && n) {
        memset(mat, 0x3f, sizeof(mat));
        for(int i = 1; i <= n; ++i) mat[i][i] = 0;
        for(int i = 1; i <= n; ++i) {
            scanf("%d", &m);
            while(m--) {
                int a, b;
                scanf("%d%d", &a, &b);
                mat[i][a] = min(mat[i][a], b);
            }
        }
        solve();
    }
}
