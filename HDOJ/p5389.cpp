#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <numeric>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)

const int MAXN = 100010;
const int MOD = 258280327;

int a[MAXN], dp[MAXN][9];
int x, y, n, T;

void update_add(int &a, int b) {
    a += b;
    if(a >= MOD) a -= MOD;
}

int solve() {
    int sum = accumulate(a + 1, a + n + 1, 0) % 9;
    if(sum != (x + y) % 9)
        return (sum == x % 9) + (sum == y % 9);

    memset(dp, 0, (n + 1) * sizeof(dp[0]));
    dp[0][0] = 1;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < 9; ++j) {
            update_add(dp[i + 1][j], dp[i][j]);
            update_add(dp[i + 1][(j + a[i + 1]) % 9], dp[i][j]);
        }
    }
    return dp[n][x % 9];
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d%d", &n, &x, &y);
        for(int i = 1; i <= n; ++i)
            scanf("%d", &a[i]);
        printf("%d\n", solve());
    }
}
