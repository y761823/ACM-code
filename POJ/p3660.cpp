#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <cmath>
using namespace std;
typedef long long LL;

const int MAXN = 110;

bool mat[MAXN][MAXN];
int n, m;

void floyd() {
    for(int k = 1; k <= n; ++k)
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= n; ++j) mat[i][j] = (mat[i][j] || (mat[i][k] && mat[k][j]));
}

int solve() {
    floyd();
    int ret = 0;
    for(int i = 1; i <= n; ++i) {
        bool flag = true;
        for(int j = 1; j <= n; ++j)
            if(!mat[i][j] && !mat[j][i]) flag = false;
        ret += flag;
    }
    return ret;
}

int main() {
    scanf("%d%d", &n, &m);
    memset(mat, false, sizeof(mat));
    for(int i = 1; i <= n; ++i) mat[i][i] = true;
    while(m--) {
        int u, v;
        scanf("%d%d", &u, &v);
        mat[u][v] = true;
    }
    printf("%d\n", solve());
}
