////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-09-17 22:08:14
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4010
////Problem Title: 
////Run result: Accept
////Run time:734MS
////Run memory:5168KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 300010;
const int MAXE = MAXN * 2;
const int INF = 0x7fffffff;

int ch[MAXN][2], pre[MAXN], key[MAXN];
int add[MAXN], rev[MAXN], maxt[MAXN];
bool rt[MAXN];

int head[MAXN];
int to[MAXE], next[MAXE];
int ecnt, n, m, op;

inline void init() {
    ecnt = 2;
    for(int i = 0; i <= n; ++i) {
        head[i] = ch[i][0] = ch[i][1] = 0;
        pre[i] = add[i] = rev[i] = 0;
        rt[i] = true;
    }
    maxt[0] = -INF;
}

inline void add_edge(int u, int v) {
    to[ecnt] = v; next[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; next[ecnt] = head[v]; head[v] = ecnt++;
}

void dfs(int u) {
    for(int p = head[u]; p; p = next[p]) {
        int &v = to[p];
        if(pre[v]) continue;
        pre[v] = u;
        dfs(v);
    }
}

inline void update_max(int r) {
    maxt[r] = max(max(maxt[ch[r][0]], maxt[ch[r][1]]), key[r]);
}

inline void update_add(int r, int d) {
    if(!r) return ;
    key[r] += d;
    maxt[r] += d;
    add[r] += d;
}

inline void update_rev(int r) {
    if(!r) return ;
    swap(ch[r][0], ch[r][1]);
    rev[r] ^= 1;
}

inline void pushdown(int r) {
    if(add[r]) {
        update_add(ch[r][0], add[r]);
        update_add(ch[r][1], add[r]);
        add[r] = 0;
    }
    if(rev[r]) {
        update_rev(ch[r][0]);
        update_rev(ch[r][1]);
        rev[r] = 0;
    }
}

void rotate(int x) {
    int y = pre[x], t = ch[y][1] == x;
    ch[y][t] = ch[x][!t];
    pre[ch[y][t]] = y;
    pre[x] = pre[y];
    pre[y] = x;
    ch[x][!t] = y;
    if(rt[y]) rt[y] = false, rt[x] = true;
    else ch[pre[x]][ch[pre[x]][1] == y] = x;
    update_max(y);
}

void P(int r) {
    if(!rt[r]) P(pre[r]);
    pushdown(r);
}

inline void Splay(int r) {
    P(r);
    while(!rt[r]) {
        int f = pre[r], ff = pre[f];
        if(rt[f]) rotate(r);
        else if((ch[ff][1] == f) == (ch[f][1] == r)) rotate(f), rotate(r);
        else rotate(r), rotate(r);
    }
    update_max(r);
}

inline int access(int x) {
    int y = 0;
    while(x) {
        Splay(x);
        rt[ch[x][1]] = true, rt[ch[x][1] = y] = false;
        update_max(x);
        x = pre[y = x];
    }
    return y;
}

inline void be_root(int r) {
    access(r);
    Splay(r);
    update_rev(r);
}

inline void lca(int &u, int &v) {
    access(v), v = 0;
    while(u) {
        Splay(u);
        if(!pre[u]) return ;
        rt[ch[u][1]] = true;
        rt[ch[u][1] = v] = false;
        update_max(u);
        u = pre[v = u];
    }
}

inline int root(int u) {
    while(pre[u]) u = pre[u];
    return u;
}

inline void link(int u, int v) {
    if(u == v || root(u) == root(v)) puts("-1");
    else {
        be_root(u);
        pre[u] = v;
    }
}

inline void cut(int u, int v) {
    if(u == v || root(u) != root(v)) puts("-1");
    else {
        be_root(u);
        Splay(v);
        pre[ch[v][0]] = pre[v];
        pre[v] = 0;
        rt[ch[v][0]] = true;
        ch[v][0] = 0;
        update_max(v);
    }
}

inline void modity(int u, int v, int w) {
    if(root(u) != root(v)) puts("-1");
    else {
        lca(u, v);
        update_add(ch[u][1], w);
        update_add(v, w);
        key[u] += w;
        update_max(u);
    }
}

inline void query(int u, int v) {
    if(root(u) != root(v)) puts("-1");
    else {
        lca(u, v);
        printf("%d\n", max(max(maxt[v], maxt[ch[u][1]]), key[u]));
    }
}

int main() {
    while(scanf("%d", &n) != EOF) {
        init();
        for(int i = 1; i < n; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            add_edge(u, v);
        }
        for(int i = 1; i <= n; ++i) scanf("%d", &key[i]);
        pre[1] = -1; dfs(1); pre[1] = 0;
        scanf("%d", &m);
        while(m--) {
            scanf("%d", &op);
            if(op == 1) {
                int x, y;
                scanf("%d%d", &x, &y);
                link(x, y);
            }
            if(op == 2) {
                int x, y;
                scanf("%d%d", &x, &y);
                cut(x, y);
            }
            if(op == 3) {
                int x, y, w;
                scanf("%d%d%d", &w, &x, &y);
                modity(x, y, w);
            }
            if(op == 4) {
                int x, y;
                scanf("%d%d", &x, &y);
                query(x, y);
            }
        }
        puts("");
    }
}
