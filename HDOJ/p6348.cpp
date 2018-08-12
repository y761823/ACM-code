#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

const int MAXN = 10010;
const int MOD = 1000000007;

inline int mod_add(int x, int y) {
    int sum = x + y;
    return sum < MOD ? sum : sum - MOD;
}

inline int lowbit(int x) {
    return x & -x;
}

int cnt[2][MAXN];
int p[MAXN], sum[MAXN], res[MAXN];
int T, n;

void modify(int k, int val) {
    while (k <= n) {
        sum[k] = mod_add(sum[k], val);
        k += lowbit(k);
    }
}

int get_sum(int k) {
    int res = 0;
    while (k) {
        res = mod_add(res, sum[k]);
        k -= lowbit(k);
    }
    return res;
}

void solve() {
    memset(res + 1, 0, sizeof(int) * n);
    for (int i = 1; i <= n; ++i)
        cnt[0][i] = 1;
    res[1] = n;

    int* pre = cnt[0];
    int* cur = cnt[1];
    for (int k = 2; k <= n; ++k) {
        bool flag = false;
        for (int i = 1; i <= n; ++i)
            if (pre[i]) flag = true;
        if (!flag)
            break;

        memset(sum + 1, 0, n * sizeof(int));
        for (int i = 1; i <= n; ++i) {
            cur[i] = get_sum(p[i]);
            modify(p[i], pre[i]);
            res[k] = mod_add(res[k], cur[i]);
        }
        swap(pre, cur);
    }
}

int main() {
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
            scanf("%d", &p[i]);

        solve();
        printf("Case #%d:", t);
        for (int i = 1; i <= n; ++i)
            printf(" %d", res[i]);
        puts("");
    }
}
