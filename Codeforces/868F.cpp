#include <cstdio>
#include <limits>
#include <algorithm>
#include <memory>
#include <cstring>

typedef long long LL;

constexpr int MAXN = 100005;
constexpr int MAXK = 25;

int a[MAXN];
LL dp[MAXK][MAXN];
int n, k;

int count[MAXN];
int cur_l, cur_r;
LL sum;

LL calc(int target_l, int target_r) {
    while (target_l < cur_l) sum += count[a[--cur_l]]++;
    while (cur_l < target_l) sum -= --count[a[cur_l++]];

    while (target_r < cur_r) sum -= --count[a[cur_r--]];
    while (cur_r < target_r) sum += count[a[++cur_r]]++;

    return sum;
}

void solve(int step, int l, int r, int low, int high) {
    int mid = (l + r) / 2, bast_pos = 0;
    LL res = 0x7f7f7f7f7f7f7f7f;
    for (int i = low; i < std::min(high, mid + 1); ++i) {
        LL v = i > 0 ? dp[step - 1][i - 1] : 0;
        v += calc(i, mid);
        if (res > v) {
            res = v;
            bast_pos = i;
        }
    }
    dp[step][mid] = res;
    if (l < mid)
        solve(step, l, mid, low, bast_pos + 1);
    if (mid + 1 < r)
        solve(step, mid + 1, r, bast_pos, high);
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    memset(dp[0], 0x7f, sizeof(dp[0][0]) * n);

    cur_l = cur_r = 0;
    count[a[0]] = 1;

    for (int i = 1; i <= k; ++i) {
        solve(i, 0, n, 0, n);
    }

    printf("%lld\n", dp[k][n - 1]);
}
