////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-03-16 21:59:59
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4467
////Problem Title: 
////Run result: Accept
////Run time:3125MS
////Run memory:7008KB
//////////////////System Comment End//////////////////
#pragma GCC optimize ("O2")

#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;

const int MAXN = 100010;
const int MAXE = 200010;

struct Edge {
    int from, to, del;
    LL w;
    void read() {
        scanf("%d%d%I64d", &from, &to, &w);
        del = 0;
        if(from > to) swap(from, to);
    }
    bool operator < (const Edge &rhs) const {
        if(from != rhs.from) return from < rhs.from;
        return to < rhs.to;
    }
    bool operator == (const Edge &rhs) const {
        return from == rhs.from && to == rhs.to;
    }
} edge[MAXE];

LL sum[3];
int n, m, q;
int head[MAXN], deg[MAXN], ecnt;
int col[MAXN];
LL state[MAXN][2];
int to[MAXE], next[MAXE];
LL weight[MAXE];

void init() {
    memset(head, 0, sizeof(head));
    memset(sum, 0, sizeof(sum));
    memset(deg, 0, sizeof(deg));
    memset(state, 0, sizeof(state));
    ecnt = 2;
}

void add_edge(int u, int v, LL w) {
    to[ecnt] = v; weight[ecnt] = w; next[ecnt] = head[u]; head[u] = ecnt++;
}

void change() {
    int x, c;
    scanf("%d", &x);
    c = col[x]; col[x] = !col[x];
    sum[c] -= state[x][0];
    sum[c + 1] -= state[x][1];
    sum[col[x]] += state[x][0];
    sum[col[x] + 1] += state[x][1];
    for(int p = head[x]; p; p = next[p]) {
        int &v = to[p];
        state[v][c] -= weight[p];
        state[v][col[x]] += weight[p];
        sum[c + col[v]] -= weight[p];
        sum[col[x] + col[v]] += weight[p];
    }
}

char s[10];

int main() {
    int t = 0;
    while(scanf("%d%d", &n, &m) != EOF) {
        init();
        for(int i = 1; i <= n; ++i) scanf("%d", &col[i]);
        for(int i = 1; i <= m; ++i) {
            edge[i].read();
            sum[col[edge[i].from] + col[edge[i].to]] += edge[i].w;
        }
        printf("Case %d:\n", ++t);
        sort(edge + 1, edge + m + 1);
        for(int i = 1; i < m; ++i) {
            if(edge[i] == edge[i + 1]) {
                edge[i].del = true;
                edge[i + 1].w += edge[i].w;
            } else {
                ++deg[edge[i].from], ++deg[edge[i].to];
            }
        }
        for(int i = 1; i <= m; ++i) {
            if(edge[i].del) continue;
            if(deg[edge[i].from] < deg[edge[i].to]) {
                add_edge(edge[i].from, edge[i].to, edge[i].w);
                state[edge[i].to][col[edge[i].from]] += edge[i].w;
            } else {
                add_edge(edge[i].to, edge[i].from, edge[i].w);
                state[edge[i].from][col[edge[i].to]] += edge[i].w;
            }
        }
        scanf("%d", &q);
        while(q--) {
            scanf("%s", s);
            if(*s == 'A') {
                int x, y;
                scanf("%d%d", &x, &y);
                printf("%I64d\n", sum[x + y]);
            } else change();
        }
    }
}