/*
ID: y7618231
PROG: nuggets
LANG: C++11
*/
#ifdef OYK_JUDGE
#define longformat "%I64d"
#else
#define longformat "%lld"
#endif // OYK_JUDGE

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXN = 100010;

bool dp[MAXN];
int a[MAXN], n, m;

void solve() {
    m = 100000;
    dp[0] = true;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j + a[i] <= m; ++j)
            if(dp[j]) dp[j + a[i]] = true;
    }
    while(m && dp[m]) --m;
    if(m <= 65536) printf("%d\n", m);
    else puts("0");
}

int main() {
#ifndef OYK_JUDGE
    freopen("nuggets.in", "r", stdin); freopen("nuggets.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) scanf("%d", &a[i]);
    solve();
}
