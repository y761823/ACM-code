#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

typedef long long LL;

const int MAXN = 100 + 10;
const int MOD = 1e9 + 7;

int ll[MAXN], rr[MAXN];
int n, T;

int inv(int a) {
    if(a == 1) return 1;
    return (LL(MOD - MOD / a) * inv(MOD % a)) % MOD;
}

int atob(int a, int b, int h) {
    a = h - a + 1;
    b = max(1, h - b + 1);
    return (LL)(a + b) * (a - b + 1) / 2 % MOD;
}

int solve() {
    int maxl = *max_element(ll, ll + n);
    int maxr = *max_element(rr, rr + n);

    LL res = 0;
    for (int h = maxl; h <= maxr; ++h) {
        LL sum1 = 1;
        for (int i = 0; i < n; ++i) {
            sum1 = sum1 * atob(ll[i], rr[i], h) % MOD;
        }
        if (h > maxl) {
            LL sum2 = 1;
            for (int i = 0; i < n; ++i) {
                sum2 = sum2 * atob(min(h - 1, ll[i]), min(h - 1, rr[i]), h) % MOD;
            }
            //cout << "debug" << sum1 << " " << sum2 << endl;
            sum1 -= sum2;
            if (sum1 < 0)
                sum1 += MOD;
        } else {
            //cout << "debug" << sum1 << endl;
        }
        res += sum1;
    }
    res %= MOD;

    for (int i = 0; i < n; ++i)
        res = res * inv(rr[i] - ll[i] + 1) % MOD;

    return res;
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i)
            scanf("%d%d", &ll[i], &rr[i]);
        printf("%d\n", solve());
    }
}
