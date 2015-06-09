#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 100010;

double e[MAXN], dp[MAXN];
double p;
int T, n, x;

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%lf%d", &n, &p, &x);
        e[0] = 0;
        for(int i = 1; i <= 100; ++i)
            e[i] = (e[i - 1] + 1) / (1 - p);

        dp[0] = 0;
        for(int i = 1; i <= n; ++i) {
            dp[i] = 1e100;
            for(int j = 1; j <= i; ++j) {
                if(dp[i] <= e[j]) break;
                dp[i] = min(dp[i], dp[i - j] + e[j] + x);
            }
        }
        printf("Case #%d: %.6f\n", t, dp[n]);
    }
}
