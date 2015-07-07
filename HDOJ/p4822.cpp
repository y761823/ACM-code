////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-08-16 14:57:05
////Compiler: Visual C++
//////////////////////////////////////////////////////
////Problem ID: 4822
////Problem Title: 
////Run result: Accept
////Run time:2781MS
////Run memory:15788KB
//////////////////System Comment End//////////////////
#ifdef ONLINE_JUDGE
#pragma comment(linker, "/STACK:1024000000,1024000000")
#endif // ONLINE_JUDGE

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

const int MAXV = 100010;
const int MAXE = 200010;
const int MAX_LOG = 20;

int head[MAXV], ecnt;
int to[MAXE], next[MAXE];
int n, m, T;

void init() {
    memset(head + 1, -1, n * sizeof(int));
    ecnt = 0;
}

void add_edge(int u, int v) {
    to[ecnt] = v; next[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; next[ecnt] = head[v]; head[v] = ecnt++;
}

int fa[MAX_LOG][MAXV];
int size[MAXV], dep[MAXV];

void dfs(int u, int f, int depth) {
    fa[0][u] = f; size[u] = 1; dep[u] = depth;
    for(int p = head[u]; ~p; p = next[p]) {
        int v = to[p];
        if(v == f) continue;
        dfs(v, u, depth + 1);
        size[u] += size[v];
    }
}

void initfa() {
    dfs(1, -1, 0);
    for(int k = 0; k < MAX_LOG - 1; ++k) {
        for(int u = 1; u <= n; ++u) {
            if(fa[k][u] == -1) fa[k + 1][u] = 1;
            else fa[k + 1][u] = fa[k][fa[k][u]];
        }
    }
}

int upslope(int u, int p) {
    for(int k = 0; k < MAX_LOG; ++k) {
        if((p >> k) & 1) u = fa[k][u];
    }
    return u;
}

int lca(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    u = upslope(u, dep[u] - dep[v]);
    if(u == v) return u;
    for(int k = MAX_LOG - 1; k >= 0; --k) {
        if(fa[k][u] != fa[k][v])
            u = fa[k][u], v = fa[k][v];
    }
    return fa[0][u];
}

struct Node {
    int type, r;
    Node(int type, int r): type(type), r(r) {}
};

Node get_middle(int a, int b, int ab) {
    int len = dep[a] + dep[b] - 2 * dep[ab];
    if(dep[a] >= dep[b]) {
        return Node(1, upslope(a, (len - 1) / 2));
    } else {
        return Node(2, upslope(b, len / 2));
    }
}

int calc(int a, int b, int c, int ab, int ac) {
    Node bn = get_middle(a, b, ab), cn = get_middle(a, c, ac);
    if(bn.type == 1 && cn.type == 1) {
        if(dep[bn.r] < dep[cn.r]) swap(bn, cn);
        if(lca(bn.r, cn.r) == cn.r) return size[bn.r];
        else return 0;
    } else if(bn.type == 2 && cn.type == 2) {
        if(dep[bn.r] < dep[cn.r]) swap(bn, cn);
        if(lca(bn.r, cn.r) == cn.r) return n - size[cn.r];
        else return n - size[bn.r] - size[cn.r];
    } else {
        if(bn.type == 2) swap(bn, cn);
        int t = lca(bn.r, cn.r);
        if(t == cn.r) return n - size[cn.r];
        if(t == bn.r) return size[bn.r] - size[cn.r];
        return size[bn.r];
    }
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        init();
        for(int i = 1, u, v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            add_edge(u, v);
        }
        initfa();
        scanf("%d", &m);
        for(int i = 0, a, b, c; i < m; ++i) {
            scanf("%d%d%d", &a, &b, &c);
            int ab = lca(a, b), ac = lca(a, c), bc = lca(b, c);
            printf("%d %d %d\n", calc(a, b, c, ab, ac), calc(b, a, c, ab, bc), calc(c, a, b, ac, bc));
        }
    }
}
