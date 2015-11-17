#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;

const int MAXN = 100010;
const int MOD = 1000000007;

int T, n;

LL power(LL x, int p) {
    LL res = 1;
    while(p) {
        if(p & 1) res = res * x % MOD;
        x = x * x % MOD;
        p >>= 1;
    }
    return res;
}

int solve() {
    LL res = 0, a = 1;
    if(n > 1) {
        for(int k = 1; k <= n; ++k) {
            if(k > 2) a = a * (n - k + 1) % MOD;
            res = (res + a * power(n - 1, min(n - k, n - 2))) % MOD;
        }
        res = res * (n - 1) % MOD;
    }
    res = (res + n * power(n - 1, n - 1)) % MOD;
    res = (power(n, n) - res + MOD) % MOD;
    return (res * n) % MOD;
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d", &n);
        printf("Case #%d: %d\n", t, solve());
    }
}
