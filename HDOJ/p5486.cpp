#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <cctype>
using namespace std;
typedef long long LL;

const int MAXN = 1000010;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;

int T, n;

struct MySet {
    int head[MAXN], size[MAXN], ecnt;
    int to[MAXN], nxt[MAXN];

    int a[MAXN], tmp[MAXN], cnt;
    bool vis[MAXN];

    void add_edge(int u, int v) {
        size[u]++;
        to[ecnt] = v; nxt[ecnt] = head[u]; head[u] = ecnt++;
    }

    void init() {
        memcpy(tmp, a, n * sizeof(int));
        sort(tmp, tmp + n);
        cnt = unique(tmp, tmp + n) - tmp;
        for(int i = 0; i < n; ++i)
            a[i] = lower_bound(tmp, tmp + cnt, a[i]) - tmp;

        memset(head, -1, cnt * sizeof(int));
        memset(size, 0, cnt * sizeof(int));
        ecnt = 0;
        for(int i = 0; i < n; ++i)
            add_edge(a[i], i);
    }
} oldx, newx;

int getsplit(MySet &oldx, MySet &newx, int &oneone) {
    int res = oneone = 0;
    for(int i = 0; i < oldx.cnt; ++i) {
        int size = 0, cnt = 0;
        for(int p = oldx.head[i]; ~p; p = oldx.nxt[p]) {
            int j = newx.a[ oldx.to[p] ];
            if(!newx.vis[j]) {
                newx.vis[j] = true;
                cnt++;
                size += newx.size[j];
            }
        }
        if(size == oldx.size[i]) {
            if(cnt == 1) oneone++;
            else res++;
        }
        for(int p = oldx.head[i]; ~p; p = oldx.nxt[p]) {
            int j = newx.a[ oldx.to[p] ];
            newx.vis[j] = false;
        }
    }
    return res;
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d", &n);
        for(int i = 0; i < n; ++i)
            scanf("%d%d", &oldx.a[i], &newx.a[i]);
        oldx.init();
        newx.init();
        int cr;
        int br = getsplit(newx, oldx, cr);
        int ar = getsplit(oldx, newx, cr);
        printf("Case #%d: %d %d %d\n", t, ar, br, cr);
    }
}
