////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-03-16 21:12:18
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 3696
////Problem Title: 
////Run result: Accept
////Run time:203MS
////Run memory:880KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <stack>
using namespace std;

const int MAXN = 10010;
const int MAXE = 50010;

double p[MAXN], w[MAXN];
int head[MAXN], indeg[MAXN];
int to[MAXE], next[MAXE];
double b[MAXE];
int n, m, ecnt, k;

void init() {
    memset(head, 0, sizeof(head));
    memset(indeg, 0, sizeof(indeg));
    ecnt = 1;
}

void add_edge(int u, int v, double bi) {
    to[ecnt] = v; b[ecnt] = bi; next[ecnt] = head[u]; head[u] = ecnt++;
    ++indeg[v];
}

stack<int> stk;

double solve() {
    double ret = 0;
    for(int i = 1; i <= n; ++i)
        if(indeg[i] == 0) stk.push(i);
    while(!stk.empty()) {
        int u = stk.top(); stk.pop();
        ret += p[u] * w[u];
        for(int q = head[u]; q; q = next[q]) {
            int &v = to[q];
            p[v] = max(p[v], p[u] * b[q]);
            if(--indeg[v] == 0) stk.push(v);
        }
    }
    return ret;
}

int main() {
    while(scanf("%d", &n) != EOF && n) {
        init();
        for(int i = 1; i <= n; ++i) scanf("%lf%lf", &p[i], &w[i]);
        scanf("%d", &m);
        while(m--) {
            scanf("%d", &k);
            int tmpa, pre; double tmpb;
            scanf("%d", &pre);
            for(int i = 1; i < k; ++i) {
                scanf("%lf%d", &tmpb, &tmpa);
                add_edge(tmpa, pre, tmpb);
                pre = tmpa;
            }
        }
        printf("%.2f\n", solve());
    }
}