#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)

const int MAXN = 500010;
const int MOD = 1e9 + 7;

LL cnt[MAXN], sum[MAXN];
int maxn = 500000;
int n, T;

void init() {
    cnt[1] = 1; cnt[2] = 3;
    sum[1] = 1; sum[2] = 11;
    for(int i = 3, pos = 2; i <= maxn; ++i) {
        if(i > cnt[pos]) pos++;
        cnt[i] = cnt[i - 1] + pos;
        sum[i] = sum[i - 1] + (cnt[i - 1] * 2 + 1 + pos) * pos / 2 % MOD * i % MOD;
    }
}

int find_last(int n) {
    int i = lower_bound(cnt + 1, cnt + maxn + 1, n) - cnt, pos = n - cnt[i - 1];
    return (sum[i - 1] + (cnt[i - 1] * 2 + 1 + pos) * pos / 2 % MOD * i % MOD) % MOD;
}

void debug(LL i) {
    printf("#debug:%I64d cnt:%I64d sum:%I64d\n", i, cnt[i], sum[i]);
}

int main() {
    init();
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        printf("%d\n", find_last(n));
    }
}
