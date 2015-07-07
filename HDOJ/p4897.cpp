////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-08-02 15:30:20
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4897
////Problem Title: 
////Run result: Accept
////Run time:2515MS
////Run memory:10476KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;

const int MAXV = 100010;
const int MAXE = MAXV << 1;
const int MAXT = MAXV << 2;

int head[MAXV], ecnt;
int to[MAXE], next[MAXE];
int n, m, T;
//Graph
void initGraph() {
    memset(head + 1, -1, n * sizeof(int));
    ecnt = 0;
}

void add_edge(int u, int v) {
    to[ecnt] = v; next[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; next[ecnt] = head[v]; head[v] = ecnt++;
}
//Segment Tree
#define ll (x << 1)
#define rr (ll | 1)
#define mid ((l + r) >> 1)
int sum[MAXT], flip[MAXT];
int light[MAXT];//Çá±ßÊÇ·ñ·­×ª

void initSegmentTree() {
    memset(sum + 1, 0, 4 * n * sizeof(int));
    memset(flip + 1, 0, 4 * n * sizeof(int));
    memset(light + 1, 0, 4 * n * sizeof(int));
}

void pushdown(int x, int l, int r) {
    if(flip[x]) {
        flip[ll] ^= 1;
        sum[ll] = (mid - l + 1) - sum[ll];
        flip[rr] ^= 1;
        sum[rr] = (r - mid) - sum[rr];
        flip[x] = 0;
    }
    if(light[x]) {
        light[ll] ^= 1;
        light[rr] ^= 1;
        light[x] = 0;
    }
}

void maintain(int x) {
    sum[x] = sum[ll] + sum[rr];
}

void modifyFlip(int x, int l, int r, int a, int b) {
    if(a <= l && r <= b) {
        flip[x] ^= 1;
        sum[x] = (r - l + 1) - sum[x];
    } else {
        pushdown(x, l, r);
        if(a <= mid) modifyFlip(ll, l, mid, a, b);
        if(mid < b) modifyFlip(rr, mid + 1, r, a, b);
        maintain(x);
    }
}

void modifyLight(int x, int l, int r, int a, int b) {
    if(a <= l && r <= b) {
        light[x] ^= 1;
    } else {
        pushdown(x, l, r);
        if(a <= mid) modifyLight(ll, l, mid, a, b);
        if(mid < b) modifyLight(rr, mid + 1, r, a, b);
    }
}

int queryFlip(int x, int l, int r, int a, int b) {
    if(a <= l && r <= b) {
        return sum[x];
    } else {
        int res = 0;
        pushdown(x, l, r);
        if(a <= mid) res += queryFlip(ll, l, mid, a, b);
        if(mid < b) res += queryFlip(rr, mid + 1, r, a, b);
        return res;
    }
}

int queryLight(int x, int l, int r, int a, int b) {
    if(a <= l && r <= b) {
        return light[x];
    } else {
        int res = 0;
        pushdown(x, l, r);
        if(a <= mid) res += queryLight(ll, l, mid, a, b);
        if(mid < b) res += queryLight(rr, mid + 1, r, a, b);
        return res;
    }
}
//Ê÷Á´ÆÊ·Ö
int fa[MAXV], size[MAXV], son[MAXV], top[MAXV], tid[MAXV], dep[MAXV];
int dfs_clock;

void dfs_size(int u, int f, int depth) {
    fa[u] = f; dep[u] = depth;
    size[u] = 1; son[u] = 0;
    int maxsize = 0;
    for(int p = head[u]; ~p; p = next[p]) {
        int &v = to[p];
        if(v == f) continue;
        dfs_size(v, u, depth + 1);
        size[u] += size[v];
        if(size[v] > maxsize) {
            son[u] = v;
            maxsize = size[v];
        }
    }
}

void dfs_heavy_edge(int u, int ancestor) {
    tid[u] = ++dfs_clock; top[u] = ancestor;
    if(son[u]) dfs_heavy_edge(son[u], ancestor);
    for(int p = head[u]; ~p; p = next[p]) {
        int &v = to[p];
        if(v == fa[u] || v == son[u]) continue;
        dfs_heavy_edge(v, v);
    }
}

void modifyFlip(int a, int b) {
    while(top[a] != top[b]) {
        if(dep[top[a]] < dep[top[b]]) swap(a, b);
        modifyFlip(1, 1, n, tid[top[a]], tid[a]);
        a = fa[top[a]];
    }
    if(a != b) {
        if(dep[a] < dep[b]) swap(a, b);
        modifyFlip(1, 1, n, tid[son[b]], tid[a]);
    }
}

void modifyLight(int a, int b) {
    while(top[a] != top[b]) {
        if(dep[top[a]] < dep[top[b]]) swap(a, b);
        modifyLight(1, 1, n, tid[top[a]], tid[a]);
        if(son[a]) modifyFlip(1, 1, n, tid[son[a]], tid[son[a]]);
        modifyFlip(1, 1, n, tid[top[a]], tid[top[a]]);
        a = fa[top[a]];
    }
    if(dep[a] < dep[b]) swap(a, b);
    modifyLight(1, 1, n, tid[b], tid[a]);
    if(fa[b]) modifyFlip(1, 1, n, tid[b], tid[b]);
    if(son[a]) modifyFlip(1, 1, n, tid[son[a]], tid[son[a]]);
}

int query(int a, int b) {
    int res = 0;
    while(top[a] != top[b]) {
        if(dep[top[a]] < dep[top[b]]) swap(a, b);
        if(a != top[a]) res += queryFlip(1, 1, n, tid[son[top[a]]], tid[a]);
        res += queryFlip(1, 1, n, tid[top[a]], tid[top[a]]) ^ queryLight(1, 1, n, tid[fa[top[a]]], tid[fa[top[a]]]);
        a = fa[top[a]];
    }
    if(a != b) {
        if(dep[a] < dep[b]) swap(a, b);
        res += queryFlip(1, 1, n, tid[son[b]], tid[a]);
    }
    return res;
}

void ask() {
    int a, b;
    while(cin>>a>>b && a + b) {
        cout<<query(a, b)<<endl;
    }
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        initGraph();
        for(int i = 1, a, b; i < n; ++i) {
            scanf("%d%d", &a, &b);
            add_edge(a, b);
        }
        initSegmentTree();
        dfs_clock = 0;
        dfs_size(1, 0, 0);
        dfs_heavy_edge(1, 1);
        scanf("%d", &m);
        for(int i = 0, op, a, b; i < m; ++i) {
            scanf("%d%d%d", &op, &a, &b);
            if(op == 1) modifyFlip(a, b);
            if(op == 2) modifyLight(a, b);
            if(op == 3) printf("%d\n", query(a, b));
            //if(i == 1) ask();
        }
    }
}
