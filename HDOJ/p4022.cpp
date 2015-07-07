////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-08-28 00:01:28
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4022
////Problem Title: 
////Run result: Accept
////Run time:812MS
////Run memory:14452KB
//////////////////System Comment End//////////////////
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>
using namespace std;
typedef long long LL;

const int MAXN = 100010;
const int MAXT = MAXN * 3;

int x[MAXN], y[MAXN];
int xtmp[MAXN], ytmp[MAXN];
int xcnt, ycnt;
int n, m;

int xhash(int x) {
    return lower_bound(xtmp, xtmp + xcnt, x) - xtmp;
}

int yhash(int y) {
    return lower_bound(ytmp, ytmp + ycnt, y) - ytmp;
}

multiset<int> xst[MAXN], yst[MAXN];

void init() {
    xcnt = ycnt = 0;
    for(int i = 0; i < n; ++i) {
        xtmp[xcnt++] = x[i];
        ytmp[ycnt++] = y[i];
    }
    sort(xtmp, xtmp + xcnt);
    sort(ytmp, ytmp + ycnt);
    xcnt = unique(xtmp, xtmp + xcnt) - xtmp;
    ycnt = unique(ytmp, ytmp + ycnt) - ytmp;
    for(int i = 0; i < n; ++i) {
        x[i] = xhash(x[i]);
        y[i] = yhash(y[i]);
    }
    for(int i = 0; i < xcnt; ++i) xst[i].clear();
    for(int i = 0; i < ycnt; ++i) yst[i].clear();
    for(int i = 0; i < n; ++i) {
        xst[x[i]].insert(y[i]);
        yst[y[i]].insert(x[i]);
    }
}

int op[MAXN], ask[MAXN];

void solve() {
    multiset<int>::iterator it;
    for(int i = 0; i < m; ++i) {
        if(op[i] == 0) {
            int t = xhash(ask[i]);
            if(xtmp[t] != ask[i]) {
                puts("0");
                continue;
            }
            printf("%d\n", xst[t].size());
            for(it = xst[t].begin(); it != xst[t].end(); ++it)
                yst[*it].erase(t);
            xst[t].clear();
        } else {
            int t = yhash(ask[i]);
            if(ytmp[t] != ask[i]) {
                puts("0");
                continue;
            }
            printf("%d\n", yst[t].size());
            for(it = yst[t].begin(); it != yst[t].end(); ++it)
                xst[*it].erase(t);
            yst[t].clear();
        }
    }
}

int main() {
    while(scanf("%d%d", &n, &m) != EOF) {
        if(n == 0 && m == 0) break;
        for(int i = 0; i < n; ++i) scanf("%d%d", &x[i], &y[i]);
        for(int i = 0; i < m; ++i) scanf("%d%d", &op[i], &ask[i]);
        init();
        solve();
        puts("");
    }
}