#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)

const int MAXN = 1010;

vector<int> htmp;

struct Node {
    int h, d;
    bool operator < (const Node &rhs) const {
        if(h != rhs.h) return h < rhs.h;
        return d < rhs.d;
    }
} a[MAXN];
int n, T;

int atree[MAXN][MAXN], btree[MAXN][MAXN];
int dp[MAXN][MAXN];

int lowbit(int x) {
    return x & -x;
}

void modify(int tree[], int x, int val) {
    while(x <= n) {
        tree[x] = max(tree[x], val);
        x += lowbit(x);
    }
}

int get_max(int tree[], int x) {
    int res = 0;
    while(x) {
        res = max(res, tree[x]);
        x -= lowbit(x);
    }
    return res;
}

int solve() {
    for(int i = 0; i <= n; ++i) {
        memset(atree[i] + 1, 0, n * sizeof(int));
        memset(btree[i] + 1, 0, n * sizeof(int));
    }
    int res = 0;
    for(int a = 0; a <= n; ++a) {
        for(int b = 0; b <= n; ++b) if(a != b) {
            int d = ::a[max(a, b)].d;
            dp[a][b] = (a > b ? get_max(btree[b], d) : get_max(atree[a], d)) + 1;
            modify(atree[a], ::a[b].d, dp[a][b]);
            modify(btree[b], ::a[a].d, dp[a][b]);
            res = max(res, dp[a][b]);
        }
    }
    return res;
}

int main() {
    a[0].d = 1;

    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        htmp.clear();
        for(int i = 1; i <= n; ++i) {
            scanf("%d%d", &a[i].h, &a[i].d);
            a[i].h = -a[i].h;
            htmp.push_back(a[i].d);
        }
        sort(a + 1, a + n + 1);

        sort(htmp.begin(), htmp.end());
        htmp.erase(unique(htmp.begin(), htmp.end()), htmp.end());
        for(int i = 1; i <= n; ++i)
            a[i].d = lower_bound(htmp.begin(), htmp.end(), a[i].d) - htmp.begin() + 1;

        printf("%d\n", solve());
    }
}
