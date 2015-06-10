#include <cstring>
#include <string>
#include <iostream>
#include <cstdio>
#include <map>
#include <algorithm>
using namespace std;

const int MAXN = 25;
const int INF = 0x7f7f7f7f;

struct Node {
    int u, v, c, use;
    Node() {}
    Node(int uu, int vv, int cc): u(uu), v(vv), c(cc), use(false) {}
    bool operator < (const Node &rhs) const {
        return c < rhs.c;
    }
};

map<string, int> mymap;
string s1, s2;
int n, m, k, ecnt, ans, cnt;
Node *p;
int fa[MAXN], head[MAXN], *next;
int mat[MAXN][MAXN];

void init() {
    ecnt = n = 0;
    p = new Node[2 * m + 5];
    next = new int[2 * m + 5];
    mymap.clear();
    mymap["Park"] = n++;
    memset(mat, 0, sizeof(mat));
}

int get_set(int x) {
    return fa[x] == x ? x : get_set(fa[x]);
}

void add_edge(int u, int v, int c) {
    p[ecnt++] = Node(u, v, c);
    p[ecnt++] = Node(v, u, c);
    if(mat[u][v] == 0 || c < mat[u][v])
        mat[u][v] = mat[v][u] = c;
}

void build_link() {
    memset(head, -1, sizeof(head));
    for(int i = ecnt - 1; i >= 0; --i) {
        next[i] = head[p[i].u];
        head[p[i].u] = i;
    }
}

void kruskal_del0() {
    ans = cnt = 0;
    for(int i = 0; i < ecnt; ++i) {
        if(p[i].u == 0 || p[i].v == 0) continue;
        int x = get_set(p[i].u), y = get_set(p[i].v);
        if(x == y) continue;
        fa[x] = y;
        p[i].use = p[i ^ 1].use = true;
        ans += p[i].c;
        ++cnt;
    }
    m = n - 1 - cnt;
    build_link();
    for(int i = head[0]; i != -1; i = next[i]) {
        if(p[i].u && p[i].v) continue;
        int x = get_set(p[i].u), y = get_set(p[i].v);
        if(x == y) continue;
        fa[x] = fa[y] = 0;
        p[i].use = p[i ^ 1].use = true;
        ans += p[i].c;
        if(++cnt == n - 1) break;
    }
}

void dfs(int x) {
    for(int i = head[x]; i != -1; i = next[i]) {
        if(p[i].use) {
            fa[p[i].v] = x;
            p[i].use = p[i ^ 1].use = false;
            dfs(p[i].v);
        }
    }
}

int best[MAXN];

int get_best(int x) {
    if(fa[x] == 0) return -1;
    if(best[x] != -1) return best[x];
    return best[x] = max(mat[x][fa[x]], get_best(fa[x]));
}

void exchange_edge() {
    while(m++ < k) {
        memset(best, -1, sizeof(best));
        for(int i = 0; i < n; ++i) get_best(i);
        int a = INF, y = 0;
        for(int i = head[0]; i != -1; i = next[i]) {
            if(best[p[i].v] != -1 && a > p[i].c - best[p[i].v]) {
                a = p[i].c - best[p[i].v];
                y = p[i].v;
            }
        }
        if(a >= 0) return ;
        ans += a; fa[y] = 0;
    }
}

int main() {
    int c;
    while(scanf("%d", &m) != EOF) {
        init();
        while(m--) {
            cin>>s1>>s2>>c;
            if(mymap.find(s1) == mymap.end()) mymap[s1] = n++;
            if(mymap.find(s2) == mymap.end()) mymap[s2] = n++;
            add_edge(mymap[s1], mymap[s2], c);
        }
        scanf("%d", &k);
        for(int i = 0; i <= n; ++i) fa[i] = i;
        sort(p, p + ecnt);
        kruskal_del0();
        dfs(0);
        exchange_edge();
        printf("Total miles driven: %d\n", ans);
        delete [] p;
        delete [] next;
    }
}
