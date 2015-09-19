#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;

const int MAXN = 201400;
const int INF = 0x3f3f3f3f;
const int MOD = 530600414;

int cnt[MAXN], len[MAXN], sum[MAXN], res[MAXN];
int n, T;

int getd(LL x) {
    return (-x % MOD + MOD) % MOD;
}

void init(int n = 201314) {
    cnt[1] = sum[1] = res[1] = 0; len[1] = 1;
    cnt[2] = sum[2] = res[2] = 0; len[2] = 2;
    cnt[3] = 1; sum[3] = 0; res[3] = 0; len[3] = 3;
    for(int i = 4; i <= n; ++i) {
        cnt[i] = (cnt[i - 2] + cnt[i - 1]) % MOD;
        len[i] = (len[i - 2] + len[i - 1]) % MOD;
        sum[i] = (sum[i - 2] + sum[i - 1] + (LL)cnt[i - 1] * len[i - 2]) % MOD;

        LL tmp = (LL)sum[i - 1] * cnt[i - 2] % MOD;
        tmp = (tmp + (LL)len[i - 2] * cnt[i - 1] % MOD * cnt[i - 2]) % MOD;
        tmp = (tmp + getd((LL)cnt[i - 1] * sum[i - 2])) % MOD;
        res[i] = (tmp + res[i - 1] + res[i - 2]) % MOD;
    }
}

int main() {
    init();
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d", &n);
        printf("Case #%d: %d\n", t, res[n]);
    }
}
