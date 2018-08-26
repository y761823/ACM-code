#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

typedef long long LL;

const int MAXN = 100010 + 10;

int fa[MAXN], weight[MAXN];
LL res1[MAXN], res2[MAXN];
int n, T;

void update_max(LL& maxa, LL& maxb, LL v) {
    if (v > maxb)
        swap(v, maxb);
    if (maxb > maxa)
        swap(maxb, maxa);
}

void update_min(LL& mina, LL& minb, LL v) {
    if (v < minb)
        swap(v, minb);
    if (minb < mina)
        swap(minb, mina);
}

void solve() {
    LL maxans = max(0, weight[1]);
    memset(res1 + 1, 0, n * sizeof(LL));
    memset(res2 + 1, 0, n * sizeof(LL));
    for (int i = 2; i <= n; ++i)
        update_max(res1[fa[i]], res2[fa[i]], weight[i]);
    maxans += accumulate(res1 + 1, res1 + n + 1, 0LL) + *max_element(res2 + 1, res2 + n + 1);

    LL minans = min(0, weight[1]);
    memset(res1 + 1, 0, n * sizeof(LL));
    memset(res2 + 1, 0, n * sizeof(LL));
    for (int i = 2; i <= n; ++i)
        update_min(res1[fa[i]], res2[fa[i]], weight[i]);
    minans += accumulate(res1 + 1, res1 + n + 1, 0LL) + *min_element(res2 + 1, res2 + n + 1);
    cout << maxans << " " << minans << endl;
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 2; i <= n; ++i)
            scanf("%d", &fa[i]);
        for (int i = 1; i <= n; ++i)
            scanf("%d", &weight[i]);
        solve();
    }
}
