#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;

const int MAXN = 100010;
const int MAXT = 40 * MAXN;

struct Node {
    int ll, rr;
    int maxt;
} pool[MAXT];
int ncnt;

void init_tree() {
    ncnt = 1;
}

int insert(int x, int l, int r, int pos, int val) {
    int res = ncnt++;
    pool[res] = pool[x];
    pool[res].maxt = max(pool[res].maxt, val);
    if(l != r) {
        int mid = (l + r) >> 1;
        if(pos <= mid) pool[res].ll = insert(pool[res].ll, l, mid, pos, val);
        if(mid < pos) pool[res].rr = insert(pool[res].rr, mid + 1, r, pos, val);
    }
    return res;
}

int query(int x, int l, int r, int a, int b) {
    if(a <= l && r <= b) {
        return pool[x].maxt;
    } else {
        int mid = (l + r) >> 1, res = 0;
        if(a <= mid) res = max(res, query(pool[x].ll, l, mid, a, b));
        if(mid < b) res = max(res, query(pool[x].rr, mid + 1, r, a, b));
        return res;
    }
}

vector<int> table;
int yes[MAXN], no[MAXN];
int a[MAXN];
int n, l, T;

int query(int x, int a, int b) {
    if(a > b) return 0;
    return query(x, 1, table.size(), a, b);
}

int solve() {
    init_tree();
    yes[0] = no[0] = 0;

    for(int i = 1; i <= n; ++i) {
        int tn = query(no[i - 1], 1, a[i] - 1) + 1;
        no[i] = insert(no[i - 1], 1, table.size(), a[i], tn);

        int ty = query(yes[i - 1], 1, a[i] - 1);
        if(ty) ty++;
        if(i - l - 1 >= 0) ty = max(ty, query(no[i - l - 1], 1, a[i] - 1) + 1);
        yes[i] = insert(yes[i - 1], 1, table.size(), a[i], ty);
    }
    return max(pool[yes[n]].maxt, pool[no[n - l]].maxt);
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d", &n, &l);
        table.clear();
        for(int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
            table.push_back(a[i]);
        }
        sort(table.begin(), table.end());
        table.erase(unique(table.begin(), table.end()), table.end());
        for(int i = 1; i <= n; ++i)
            a[i] = lower_bound(table.begin(), table.end(), a[i]) - table.begin() + 1;
        printf("Case #%d: %d\n", t, solve());
    }
}
