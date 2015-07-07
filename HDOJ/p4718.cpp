////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-05-02 21:42:06
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4718
////Problem Title: 
////Run result: Accept
////Run time:2062MS
////Run memory:12376KB
//////////////////System Comment End//////////////////
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXV = 100010;
const int MAXE = MAXV;
const int MAXT = MAXV << 2;

int lmaxi[MAXT], rmaxi[MAXT], mmaxi[MAXT];
int lmaxd[MAXT], rmaxd[MAXT], mmaxd[MAXT];
int val[MAXV], n, m, T;

int inc_ord[MAXV], dec_ord[MAXV], inc_rev[MAXV], dec_rev[MAXV];

void init_inc_dec() {
    for(int i = 1, t = 1; i <= n; ++i) {
        if(t < i) t = i;
        while(t < n && val[t] < val[t + 1]) ++t;
        inc_ord[i] = t - i + 1;
    }
    for(int i = 1, t = 1; i <= n; ++i) {
        if(t < i) t = i;
        while(t < n && val[t] > val[t + 1]) ++t;
        dec_ord[i] = t - i + 1;
    }
    for(int i = n, t = n; i > 0; --i) {
        if(t > i) t = i;
        while(t > 0 && val[t] < val[t - 1]) --t;
        inc_rev[i] = i - t + 1;
    }
    for(int i = n, t = n; i > 0; --i) {
        if(t > i) t = i;
        while(t > 0 && val[t] > val[t - 1]) --t;
        dec_rev[i] = i - t + 1;
    }
}

int queryI(int x, int l, int r, int a, int b) {
    if(a <= l && r <= b) {
        return mmaxi[x];
    } else {
        int ll = x << 1, rr = ll | 1, mid = (l + r) >> 1;
        int ans = 0;
        if(a <= mid) ans = max(ans, queryI(ll, l, mid, a, b));
        if(mid < b) ans = max(ans, queryI(rr, mid + 1, r, a, b));
        if(val[mid] < val[mid + 1]) {
            ans = max(ans, min(rmaxi[ll], mid - a + 1) + min(lmaxi[rr], b - mid));
        }
        return ans;
    }
}

int queryD(int x, int l, int r, int a, int b) {
    if(a <= l && r <= b) {
        return mmaxd[x];
    } else {
        int ll = x << 1, rr = ll | 1, mid = (l + r) >> 1;
        int ans = 0;
        if(a <= mid) ans = max(ans, queryD(ll, l, mid, a, b));
        if(mid < b) ans = max(ans, queryD(rr, mid + 1, r, a, b));
        if(val[mid] > val[mid + 1]) {
            ans = max(ans, min(rmaxd[ll], mid - a + 1) + min(lmaxd[rr], b - mid));
        }
        return ans;
    }
}

void maintainI(int x, int l, int r) {
    int ll = x << 1, rr = ll | 1, mid = (l + r) >> 1;
    if(val[mid] < val[mid + 1]) {
        lmaxi[x] = lmaxi[ll] + (lmaxi[ll] == mid - l + 1) * lmaxi[rr];
        rmaxi[x] = rmaxi[rr] + (rmaxi[rr] == r - mid) * rmaxi[ll];
        mmaxi[x] = max(rmaxi[ll] + lmaxi[rr], max(mmaxi[ll], mmaxi[rr]));
    } else {
        lmaxi[x] = lmaxi[ll];
        rmaxi[x] = rmaxi[rr];
        mmaxi[x] = max(mmaxi[ll], mmaxi[rr]);
    }
}

void maintainD(int x, int l, int r) {
    int ll = x << 1, rr = ll | 1, mid = (l + r) >> 1;
    if(val[mid] > val[mid + 1]) {
        lmaxd[x] = lmaxd[ll] + (lmaxd[ll] == mid - l + 1) * lmaxd[rr];
        rmaxd[x] = rmaxd[rr] + (rmaxd[rr] == r - mid) * rmaxd[ll];
        mmaxd[x] = max(rmaxd[ll] + lmaxd[rr], max(mmaxd[ll], mmaxd[rr]));
    } else {
        lmaxd[x] = lmaxd[ll];
        rmaxd[x] = rmaxd[rr];
        mmaxd[x] = max(mmaxd[ll], mmaxd[rr]);
    }
}

void build(int x, int l, int r) {
    if(l == r) {
        lmaxi[x] = rmaxi[x] = mmaxi[x] = 1;
        lmaxd[x] = rmaxd[x] = mmaxd[x] = 1;
    } else {
        int ll = x << 1, rr = ll | 1, mid = (l + r) >> 1;
        build(ll, l, mid);
        build(rr, mid + 1, r);
        maintainI(x, l, r);
        maintainD(x, l, r);
    }
}

int v[MAXV];
int fa[MAXV], son[MAXV], size[MAXV], tid[MAXV], top[MAXV], dep[MAXV];
int head[MAXV], ecnt, dfs_clock;
int to[MAXE], next[MAXE];

void init(int n) {
    memset(head, -1, (n + 1) * sizeof(int));
    ecnt = dfs_clock = 0;
}

void add_edge(int u, int v) {
    to[ecnt] = v; next[ecnt] = head[u]; head[u] = ecnt++;
}

void dfs_size(int u, int depth) {
    size[u] = 1; son[u] = 0; dep[u] = depth;
    int maxsize = 0;
    for(int p = head[u]; ~p; p = next[p]) {
        int &v = to[p];
        dfs_size(v, depth + 1);
        size[u] += size[v];
        if(size[v] > maxsize) {
            son[u] = v;
            maxsize = size[v];
        }
    }
}

void dfs_heavy_edge(int u, int ancestor) {
    val[tid[u] = ++dfs_clock] = v[u];
    top[u] = ancestor;
    if(son[u]) dfs_heavy_edge(son[u], ancestor);
    for(int p = head[u]; ~p; p = next[p]) {
        int &v = to[p];
        if(v == son[u]) continue;
        dfs_heavy_edge(v, v);
    }
}

int query(int x, int y) {
    int res = 0, maxx = 0, prex = 0, maxy = 0, prey = 0;
    while(top[x] != top[y]) {
        if(dep[top[x]] > dep[top[y]]) {
            int sz = dep[x] - dep[top[x]] + 1;
            int up_ans = min(inc_rev[tid[x]], sz);
            int down_ans = min(dec_ord[tid[top[x]]], sz);
            res = max(res, queryD(1, 1, n, tid[top[x]], tid[x]));
            if(prex && v[prex] >= v[x]) maxx = 0;
            res = max(res, up_ans + maxx);
            maxx = down_ans + (sz == down_ans) * maxx;
            prex = top[x];
            x = fa[top[x]];
        } else {
            int sz = dep[y] - dep[top[y]] + 1;
            int up_ans = min(dec_rev[tid[y]], sz);
            int down_ans = min(inc_ord[tid[top[y]]], sz);
            res = max(res, queryI(1, 1, n, tid[top[y]], tid[y]));
            if(prey && v[prey] <= v[y]) maxy = 0;
            res = max(res, up_ans + maxy);
            maxy = down_ans + (sz == down_ans) * maxy;
            prey = top[y];
            y = fa[top[y]];
        }
    }
    if(dep[x] > dep[y]) {
        int sz = dep[x] - dep[y] + 1;
        int up_ans = min(inc_rev[tid[x]], sz);
        int down_ans = min(dec_ord[tid[y]], sz);
        res = max(res, queryD(1, 1, n, tid[y], tid[x]));
        if(prex && v[prex] >= v[x]) maxx = 0;
        if(prey && v[prey] <= v[y]) maxy = 0;
        res = max(res, up_ans + maxx);
        res = max(res, down_ans + maxy);
        if(up_ans == sz) res = max(res, maxx + up_ans + maxy);
    } else {
        int sz = dep[y] - dep[x] + 1;
        int up_ans = min(dec_rev[tid[y]], sz);
        int down_ans = min(inc_ord[tid[x]], sz);
        res = max(res, queryI(1, 1, n, tid[x], tid[y]));
        if(prex && v[prex] >= v[x]) maxx = 0;
        if(prey && v[prey] <= v[y]) maxy = 0;
        res = max(res, down_ans + maxx);
        res = max(res, up_ans + maxy);
        if(up_ans == sz) res = max(res, maxx + up_ans + maxy);
    }
    return res;
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d", &n);
        init(n);
        for(int i = 1; i <= n; ++i) scanf("%d", &v[i]);
        for(int i = 2; i <= n; ++i) {
            scanf("%d", &fa[i]);
            add_edge(fa[i], i);
        }
        dfs_size(1, 1);
        dfs_heavy_edge(1, 1);
        build(1, 1, n);
        init_inc_dec();
        printf("Case #%d:\n", t);
        scanf("%d", &m);
        while(m--) {
            int u, v;
            scanf("%d%d", &u, &v);
            printf("%d\n", query(u, v));
        }
        if(t != T) puts("");
    }
}
