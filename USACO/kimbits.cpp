/*
ID: y7618231
LANG: C++
TASK: kimbits
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
#include <numeric>
using namespace std;
typedef long long LL;

int dp[33][33];
int n, l;
LL k;

void init() {
    dp[0][0] = 1;
    for(int i = 1; i <= n; ++i) {
        for(int j = 0; j <= i; ++j) {
            dp[i][j] = dp[i - 1][j];
            if(j) dp[i][j] += dp[i - 1][j - 1];
        }
    }
}

void print() {
    LL one = l;
    for(int i = n; i > 0; --i) {
        int sum = 0;
        for(int j = 0; j <= one; ++j)
            sum += dp[i - 1][j];
        if(sum >= k) putchar('0');
        else putchar('1'), one--, k -= sum;
    }
    puts("");
}

int main () {
#ifndef OYK_JUDGE
    freopen("kimbits.in", "r", stdin); freopen("kimbits.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%d%d" longformat, &n, &l, &k);
    init();
    print();
}
