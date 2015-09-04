// http://arxiv.org/pdf/0906.2295v2.pdf
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cassert>
using namespace std;
typedef long long LL;

const int MAXN = 1000010;
const int MOD = 1000000007;

int prime[MAXN], total;
bool isprime[MAXN];

void make_prime(int n = MAXN) {
    memset(isprime, true, sizeof(isprime));
    for(int i = 2; i < n; ++i) {
        if(isprime[i]) prime[total++] = i;
        for(int j = 0; j < total && i * prime[j] < n; ++j) {
            isprime[i * prime[j]] = false;
            if(i % prime[j] == 0) break;
        }
    }
}

int f[MAXN], g[MAXN];

void build_f(int n = MAXN) {
    fill(g, g + n, 1);
    for(int i = 0; i < total; ++i) {
        for(LL j = prime[i]; j < n; j *= prime[i])
            g[j] = prime[i];
    }
    f[1] = 1;
    for(int i = 2; i < n; ++i)
        f[i] = (LL)f[i - 1] * g[i] % MOD;
}

int inv(int a) {
    if(a == 1) return 1;
    return LL(MOD - MOD / a) * inv(MOD % a) % MOD;
}

int T, n;

int main() {
    make_prime();
    build_f();
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        printf("%I64d\n", (LL)f[n + 1] * inv(n + 1) % MOD);
    }
}
