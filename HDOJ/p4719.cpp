////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-09-11 23:27:56
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4719
////Problem Title: 
////Run result: Accept
////Run time:781MS
////Run memory:8140KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;

const int MAXN = 100010;

LL dp[MAXN];
int n, L;
LL tree[MAXN << 2], maxt[MAXN << 2];

void pushdown(int x) {
    int ll = x << 1, rr = ll ^ 1;
    if(tree[x] != -1) {
        tree[ll] = max(tree[x], tree[ll]);
        tree[rr] = max(tree[x], tree[rr]);
        maxt[ll] = max(maxt[ll], tree[x]);
        maxt[rr] = max(maxt[rr], tree[x]);
        tree[x] = -1;
    }
}

void update(int x, int left, int right, int a, int b, LL val) {
    if(a <= left && right <= b) {
        tree[x] = max(tree[x], val);
        maxt[x] = max(maxt[x], val);
    }
    else {
        pushdown(x);
        int ll = x << 1, rr = ll ^ 1;
        int mid = (left + right) >> 1;
        if(a <= mid) update(ll, left, mid, a, b, val);
        if(mid < b) update(rr, mid + 1, right, a, b, val);
        maxt[x] = max(maxt[x], max(maxt[ll], maxt[rr]));
    }
}

LL query(int x, int left, int right, int a, int b) {
    if(a <= left && right <= b) return maxt[x];
    else {
        pushdown(x);
        int ll = x << 1, rr = ll ^ 1;
        int mid = (left + right) >> 1;
        LL ret = -1;
        if(a <= mid) ret = max(ret, query(ll, left, mid, a, b));
        if(mid < b) ret = max(ret, query(rr, mid + 1, right, a, b));
        return ret;
    }
}

struct Node {
    int h, pos;
    void read(int i) {
        pos = i;
        scanf("%d", &h);
    }
    bool operator < (const Node &rhs) const {
        if(h != rhs.h) return h < rhs.h;
        return pos > rhs.pos;
    }
} a[MAXN];

LL solve() {
    sort(a + 1, a + n + 1);
    dp[n] = -1;
    memset(tree, 255, sizeof(tree));
    memset(maxt, 255, sizeof(maxt));
    update(1, 0, n, 0, 0, 0);
    for(int i = 1; i <= n; ++i) {
        LL tmp = query(1, 0, n, max(0, a[i].pos - L), a[i].pos - 1);
        if(tmp == -1) {
            if(a[i].pos == n) break;
            else continue;
        }
        dp[a[i].pos] = tmp + LL(a[i].h) * a[i].h;
        if(a[i].pos == n) break;
        update(1, 0, n, a[i].pos, a[i].pos, dp[a[i].pos] - a[i].h);
    }
    //for(int i = 1; i <= n; ++i) printf("%I64d\n", dp[i]);
    return dp[n];
}

int main() {
    int T; scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d", &n, &L);
        for(int i = 1; i <= n; ++i) a[i].read(i);
        LL ans = solve();
        if(ans == -1) printf("Case #%d: No solution\n", t);
        else printf("Case #%d: %I64d\n", t, ans);
    }
}
