#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAXN = 110;
const int MAXE = MAXN * MAXN;

int head[MAXN], ecnt;
int to[MAXE], next[MAXE];
int pre[MAXN], lowlink[MAXN], dfs_clock;
bool iscut[MAXN];
int n, m, ans;

void init() {
    memset(head, 0, sizeof(head));
    memset(pre, 0, sizeof(pre));
    memset(iscut, 0, sizeof(iscut));
    ecnt = 1;
    ans = dfs_clock = 0;
}

void add_edge(int u, int v) {
    to[ecnt] = v; next[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; next[ecnt] = head[v]; head[v] = ecnt++;
}

void dfs(int fa, int u) {
    pre[u] = lowlink[u] = ++dfs_clock;
    int child = 0;
    for(int p = head[u]; p; p = next[p]) {
        int &v = to[p];
        if(v == fa) continue;
        if(!pre[v]) {
            ++child;
            dfs(u, v);
            lowlink[u] = min(lowlink[u], lowlink[v]);
            if(pre[u] <= lowlink[v]) iscut[u] = true;
        } else lowlink[u] = min(lowlink[u], pre[v]);
    }
    if(fa < 0 && child == 1) iscut[u] = false;
}

char s[5 * MAXN], *p, *prev;

int get_int(char *&src) {
    while(!isdigit(*src) && *src) ++src;
    int ret = 0;
    while(isdigit(*src)) ret = ret * 10 + *src++ - '0';
    return ret;
}

int main() {
    while(scanf("%d", &n) != EOF && n) {
        init();
        int u, v;
        while(gets(s) && *s != '0') {
            p = s;
            u = get_int(p);
            while((v = get_int(p)) > 0) add_edge(u, v);
        }
        dfs(-1, 1);
        for(int i = 1; i <= n; ++i) ans += iscut[i];
        printf("%d\n", ans);
    }
}
