/*
ID: y7618231
LANG: C++
TASK: stamps
*/
#ifdef OYK_JUDGE
#define longformat "%I64d"
#else
#define longformat "%lld"
#endif // OYK_JUDGE

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <numeric>
using namespace std;

const int MAXN = 2000001;

int dp[MAXN];
int a[55], k, n;

int solve() {
    memset(dp, -1, sizeof(dp));
    int up = *max_element(a, a + n) * k;
    dp[0] = k;
    for(int i = 0; i < n; ++i) {
        int v = a[i];
        for(int j = v; j <= up; ++j)
            dp[j] = max(dp[j], dp[j - v] - 1);
    }
    int res = 0;
    while(res <= up && dp[res] >= 0) res++;
    return res - 1;
}

int main () {
#ifndef OYK_JUDGE
    freopen("stamps.in", "r", stdin); freopen("stamps.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%d%d", &k, &n);
    for(int i = 0; i < n; ++i) scanf("%d", &a[i]);
    printf("%d\n", solve());
}
