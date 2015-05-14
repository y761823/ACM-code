#ifdef OYK_JUDGE
#define longformat "%I64d"
#else
#define longformat "%lld"
#endif // OYK_JUDGE

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;

vector<vector<int> > mat;
int T, n, m, k;

char str[] = "RDLU";
int fr[] = {0, 1, 0, -1};
int fc[] = {1, 0, -1, 0};

void modify(int c, int r1, int r2, int val) {
    mat[r1][c] += val;
    mat[r2][c] -= val;
}

LL solve() {
    int step, r = 1, c = 1;
    char op;
    while(k--) {
        scanf(" %c%d", &op, &step);
        if(op == 'D') modify(c, r, r + step, 1);
        if(op == 'U') modify(c, r - step, r, -1);

        int f = strchr(str, op) - str;
        r += step * fr[f];
        c += step * fc[f];
    }

    LL res = 0;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j) {
            mat[i][j] = mat[i][j] + mat[i - 1][j] + mat[i][j - 1] - mat[i - 1][j - 1];
            res += mat[i][j] * mat[i][j];
        }
    return res;
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d%d", &n, &m, &k);
        mat = vector<vector<int> >(n + 2, vector<int>(m + 2, 0));
        LL res = solve();
        printf("Case #%d: " longformat "\n", t, res);
    }
}
