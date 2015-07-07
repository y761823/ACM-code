////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-08-24 16:58:45
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4587
////Problem Title: 
////Run result: Accept
////Run time:5000MS
////Run memory:500KB
//////////////////System Comment End//////////////////
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;

const int MAXN = 5010;
const int MAXE = MAXN * 2;

int head[MAXN];
int to[MAXE], next[MAXE];
int pre[MAXN], cut[MAXN];
int n, m, dfs_clock, ecnt, stab;

void init() {
    memset(head, 0, sizeof(head));
    ecnt = 1;
}

void add_edge2(int u, int v) {
    to[ecnt] = v; next[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; next[ecnt] = head[v]; head[v] = ecnt++;
}

int del;

int dfs(int u, int fa) {
    int lowu = pre[u] = ++dfs_clock;
    for(int p = head[u]; p; p = next[p]) {
        int &v = to[p];
        if(v == del) continue;
        if(!pre[v]) {
            int lowv = dfs(v, u);
            lowu = min(lowu, lowv);
            if(lowv >= pre[u]) ++cut[u];
        } else if(pre[v] < pre[u] && v != fa) {
            lowu = min(lowu, pre[v]);
        }
    }
    if(fa < 0) --cut[u];
    return lowu;
}

int main() {
    while(scanf("%d%d", &n, &m) != EOF) {
        init();
        while(m--) {
            int a, b;
            scanf("%d%d", &a, &b);
            add_edge2(a, b);
        }
        stab = 0;
        for(int i = 0; i < n; ++i) {
            del = i;
            int sum = 0;
            memset(pre, 0, sizeof(pre));
            memset(cut, 0, sizeof(cut));
            dfs_clock = 0;
            for(int u = 0; u < n; ++u) {
                if(u == i || pre[u]) continue;
                ++sum;
                dfs(u, -1);
            }
            int maxcut = -1;
            for(int u = 0; u < n; ++u) if(u != i)
                maxcut = max(maxcut, cut[u]);
            stab = max(stab, sum + maxcut);
        }
        printf("%d\n", stab);
    }
}
