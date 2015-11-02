#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long LL;

const int MAXN = 10010;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;

int p[MAXN], flag[MAXN], cnt;
int a[MAXN];
int T, n, m;

void get_factor() {
    cnt = 0;
    for(int i = 1; i * i <= m; ++i) {
        if(m % i == 0) {
            p[cnt++] = i;
            if(m / i != i) p[cnt++] = m / i;
        }
    }
    sort(p, p + cnt);
    memset(flag, 0, cnt * sizeof(int));
}

LL solve() {
    for(int i = 0; i < n; ++i)
        flag[lower_bound(p, p + cnt, __gcd(a[i], m)) - p] = INF;
    LL res = 0;
    for(int i = 0; i < cnt; ++i) {
        int c = 0;
        for(int j = 0; j < i; ++j)
            if(p[i] % p[j] == 0) c += flag[j], flag[i] |= flag[j];
        if(flag[i]) {
            res += LL(1 - c) * m * (m / p[i] - 1) / 2;
            flag[i] = 1 - c;
        }
    }
    return res;
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; ++i)
            scanf("%d", &a[i]);
        get_factor();
        printf("Case #%d: %I64d\n", t, solve());
    }
}
