#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long LL;

const int MAXN = 100010;

LL res[15];
int fac[MAXN], p[15];
int k, T;
LL n, m;

int power(int x, int p, int mod) {
    int res = 1;
    while(p) {
        if(p & 1) res = (LL)res * x % mod;
        x = (LL)x * x % mod;
        p >>= 1;
    }
    return res;
}

void init_fac(int p) {
    fac[0] = 1;
    for(int i = 1; i <= p; ++i)
        fac[i] = (LL)fac[i - 1] * i % p;
}

LL lucas(LL n, LL m, int p) {
    LL res = 1;
    while(n && m) {
        LL a = n % p, b = m % p;
        if(a < b) return 0;
        res = (LL)res * fac[a] * power((LL)fac[b] * fac[a - b] % p, p - 2, p) % p;//èy′&#206;3&#203;·¨×￠òa
        n /= p;
        m /= p;
    }
    return res;
}

LL fastmul(LL x, LL p, LL mod) {
    LL res = 0;
    while(p) {
        if(p & 1) res = (res + x) % mod;
        x = (x + x) % mod;
        p >>= 1;
    }
    return res;
}

LL inv(LL x, LL mod) {
    if(x == 1) return 1;
    return fastmul((mod - mod / x), inv(mod % x, mod), mod);
}

void solve() {
    LL ans = 0, M = 1;
    for(int i = 0; i < k; ++i) M *= p[i];
    for(int i = 0; i < k; ++i) {
        LL Mi = M / p[i];
        LL tmp = fastmul(res[i], inv(Mi % p[i], p[i]), M);
        tmp = fastmul(tmp, Mi, M);
        ans = (ans + tmp) % M;
    }
    printf("%I64d\n", ans);
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%I64d%I64d%d", &n, &m, &k);
        for(int i = 0; i < k; ++i)
            scanf("%d", &p[i]);
        for(int i = 0; i < k; ++i) {
            init_fac(p[i]);
            res[i] = lucas(n, m, p[i]);
        }
        solve();
    }
}
