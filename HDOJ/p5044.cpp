////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-09-27 23:32:30
////Compiler: Visual C++
//////////////////////////////////////////////////////
////Problem ID: 5044
////Problem Title: 
////Run result: Accept
////Run time:3890MS
////Run memory:17392KB
//////////////////System Comment End//////////////////
#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

const int MAXV = 100010;
const int MAXE = MAXV << 1;

int head[MAXV], ecnt;
int to[MAXE], next[MAXE];
int n, m, T;

void initGraph() {
    memset(head + 1, -1, n * sizeof(int));
    ecnt = 0;
}

void add_edge(int u, int v) {
    to[ecnt] = v; next[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; next[ecnt] = head[v]; head[v] = ecnt++;
}

LL pre[MAXV], nxt[MAXV];
int fid[MAXV];

void dfs_init(int u, int f) {
    for(int p = head[u]; ~p; p = next[p]) {
        int v = to[p];
        if(v == f) continue;
        fid[v] = p / 2;
        dfs_init(v, u);
    }
}

LL ans[MAXV], tmp[MAXV];

LL dfs_ans(int u, int f) {
    LL res = 0;
    for(int p = head[u]; ~p; p = next[p]) {
        int v = to[p];
        if(v == f) continue;
        res += dfs_ans(v, u);
    }
    res += pre[u];
    ans[u] = res;
    res += nxt[u];
    return res;
}

void modify0(int a, int b, int lca, int val) {
    pre[a] += val;
    pre[b] += val;
    pre[lca] -= val;
    nxt[lca] -= val;
}

void modify1(int a, int b, int lca, int val) {
    pre[a] += val;
    pre[b] += val;
    pre[lca] -= val;
    pre[lca] -= val;
}

int fa[MAXV];
bool vis[MAXV];
vector<PII> query[MAXV];

char s[10];
struct Operator {
    int op, u, v, val, lca;
    void read(int i) {
        scanf("%s%d%d%d", s, &u, &v, &val);
        query[u].push_back(make_pair(v, i));
        query[v].push_back(make_pair(u, i));
        op = (s[3] == '2');
    }
} op[MAXV];

int find_set(int x) {
    return fa[x] == x ? x : fa[x] = find_set(fa[x]);
}

void lca(int u, int f) {
    for(int p = head[u]; ~p; p = next[p]) {
        int &v = to[p];
        if(v == f || vis[v]) continue;
        lca(v, u);
        fa[v] = u;
    }
    vis[u] = true;
    for(vector<PII>::iterator it = query[u].begin(); it != query[u].end(); ++it) {
        if(vis[it->first]) {
            op[it->second].lca = find_set(it->first);
        }
    }
}

void solve() {
    memset(vis + 1, 0, n * sizeof(bool));
    for(int i = 1; i <= n; ++i) fa[i] = i;
    dfs_init(1, 0);
    lca(1, 0);

    memset(pre + 1, 0, n * sizeof(LL));
    memset(nxt + 1, 0, n * sizeof(LL));
    for(int i = 0; i < m; ++i)
        if(op[i].op == 0) modify0(op[i].u, op[i].v, op[i].lca, op[i].val);
    dfs_ans(1, 0);
    for(int i = 1; i <= n; ++i) {
        printf("%I64d", ans[i]);
        if(i < n) putchar(' ');
    }
    puts("");

    memset(pre + 1, 0, n * sizeof(LL));
    memset(nxt + 1, 0, n * sizeof(LL));
    for(int i = 0; i < m; ++i)
        if(op[i].op == 1) modify1(op[i].u, op[i].v, op[i].lca, op[i].val);
    dfs_ans(1, 0);
    for(int i = 2; i <= n; ++i) tmp[fid[i]] = ans[i];
    for(int i = 0; i < n - 1; ++i) {
        printf("%I64d", tmp[i]);
        if(i < n - 2) putchar(' ');
    }
    puts("");
}

int main() {/*
    #ifndef ONLINE_JUDGE
    freopen("F:/acmicpc/acm.txt", "r", stdin);
    freopen("F:/acmicpc/acmout.txt", "w", stdout);
    #endif // ONLINE_JUDGE
*/
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d", &n, &m);
        initGraph();
        for(int i = 1, a, b; i < n; ++i) {
            scanf("%d%d", &a, &b);
            add_edge(a, b);
        }
        for(int i = 1; i <= n; ++i)
            query[i].clear();
        for(int i = 0; i < m; ++i)
            op[i].read(i);

        printf("Case #%d:\n", t);
        solve();
    }
}