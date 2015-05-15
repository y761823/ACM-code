#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;
typedef long long LL;

const int MAXN = 55;

LL mat[MAXN][MAXN];
int n, m, k;

LL det() {
    LL res = 1;
    for(int i = 1; i < n; ++i) {
        for(int j = i + 1; j < n; ++j) while(mat[j][i]) {
            LL t = mat[i][i] / mat[j][i];
            for(int k = i; k < n; ++k)
                mat[i][k] -= mat[j][k] * t, swap(mat[i][k], mat[j][k]);
            res = -res;
        }
        if(!mat[i][i]) return 0;
        res *= mat[i][i];
    }
    return res;
}

int main() {
    while(scanf("%d%d%d", &n, &m, &k) != EOF) {
        memset(mat, -1, sizeof(mat));
        for(int i = 0, u, v; i < m; ++i) {
            scanf("%d%d", &u, &v);
            mat[u - 1][v - 1] = mat[v - 1][u - 1] = 0;
        }
        for(int i = 0; i < n; ++i)
            mat[i][i] += count(mat[i], mat[i] + n, -1LL);
        cout<<det()<<endl;
    }
}
