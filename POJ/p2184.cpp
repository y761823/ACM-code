#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <numeric>
using namespace std;
typedef long long LL;

const int MAXN = 110;
const int MAXS = 200010;
const int INF = 0x3f3f3f3f;

int _dp[MAXS], *dp = _dp + MAXS / 2;
int a[MAXN], b[MAXN];
int n, psum, nsum;

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
        scanf("%d%d", &a[i], &b[i]);
        if(a[i] > 0) psum += a[i];
        if(a[i] < 0) nsum += a[i];
    }
    fill(dp + nsum, dp + psum + 1, -INF);
    dp[0] = 0;
    for(int i = 0; i < n; ++i) {
        if(a[i] >= 0) {
            for(int j = psum - a[i]; j >= nsum; --j)
                dp[j + a[i]] = max(dp[j + a[i]], dp[j] + b[i]);
        } else {
            for(int j = nsum - a[i]; j <= psum; ++j)
                dp[j + a[i]] = max(dp[j + a[i]], dp[j] + b[i]);
        }
        //for(int j = nsum; j <= psum; ++j) printf("%d ", dp[j]); puts("");
    }
    int res = 0;
    for(int i = 0; i <= psum; ++i)
        if(dp[i] >= 0) res = max(res, i + dp[i]);
    printf("%d\n", res);
}
