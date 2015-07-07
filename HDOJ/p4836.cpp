////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-05-31 20:39:21
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4836
////Problem Title: 
////Run result: Accept
////Run time:390MS
////Run memory:1468KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long LL;

const int MAXV = 10010;
const int MAXE = MAXV * 2;

int head[MAXV], weight[MAXV], sum[MAXV], ecnt;
int to[MAXE], next[MAXE];
int T, n, q;
char str[10];

void init() {
    memset(head, -1, (n + 1) * sizeof(int));
    ecnt = 0;
}

void add_edge(int u, int v) {
    to[ecnt] = v; next[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; next[ecnt] = head[v]; head[v] = ecnt++;
}

int tree[MAXV];

inline int lowbit(int x) {
    return x & -x;
}

int get_sum(int k) {
    int res = 0;
    while(k > 0) {
        res += tree[k];
        k -= lowbit(k);
    }
    return res;
}

void modify(int k, int val) {
    while(k <= n) {
        tree[k] += val;
        k += lowbit(k);
    }
}

int dep[MAXV], fa[20][MAXV];
int bid[MAXV], eid[MAXV], dfs_clock;

void dfs(int u, int f = -1, int deep = 0) {
    dep[u] = deep; fa[0][u] = f; bid[u] = ++dfs_clock;
    for(int p = head[u]; ~p; p = next[p]) {
        int &v = to[p];
        if(v == f) continue;
        dfs(v, u, deep + 1);
    }
    eid[u] = dfs_clock;
}

void initt() {
    dfs_clock = 0;
    dfs(1);
    for(int k = 0; k + 1 < 20; ++k) {
        for(int u = 1; u <= n; ++u) {
            if(fa[k][u] < 0) fa[k + 1][u] = -1;
            else fa[k + 1][u] = fa[k][fa[k][u]];
        }
    }
    memset(tree, 0, (n + 1) * sizeof(int));
    for(int i = 1; i <= n; ++i)
        modify(bid[i], weight[i]);
}

int get_kfa(int u, int k) {
    if(k < 0) return -1;
    int v = u;
    for(int i = 0; i < 20; ++i) {
        if((k >> i) & 1) v = fa[i][v];
        if(v < 0) return -1;
    }
    return v;
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d", &n);
        init();
        for(int i = 1, a, b; i < n; ++i) {
            scanf("%d%d", &a, &b);
            add_edge(a, b);
        }
        for(int i = 1; i <= n; ++i) scanf("%d", &weight[i]);
        initt();

        printf("Case #%d:\n", t);

        scanf("%d", &q);
        int root = 1;
        while(q--) {
            scanf("%s", str);
            if(*str == 'Q') {
                int ask;
                scanf("%d", &ask);
                int ans = 0, kfa = get_kfa(root, dep[root] - dep[ask] - 1);
                if(kfa > 0 && fa[0][kfa] == ask) ans = get_sum(n) - (get_sum(eid[kfa]) - get_sum(bid[kfa] - 1));
                else ans = get_sum(eid[ask]) - get_sum(bid[ask] - 1);
                if(ask == root) ans = get_sum(n);
                printf("%d\n", ans);
            } else if(*str == 'R') {
                scanf("%d", &root);
            } else {
                int a, b;
                scanf("%d%d", &a, &b);
                modify(bid[a], b - weight[a]);
                weight[a] = b;
            }
        }
    }
}
