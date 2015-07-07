////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-05-25 20:47:23
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4833
////Problem Title: 
////Run result: Accept
////Run time:265MS
////Run memory:588KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;
typedef long long LL;

const int MAXV = 10010;
const int MAXE = MAXV * 4;

int head[MAXV], ecnt;
int to[MAXE], next[MAXE], cost[MAXE];

void init(int n) {
    memset(head, -1, n * sizeof(int));
    ecnt = 0;
}

void add_edge(int u, int v, int c) {
    to[ecnt] = v; cost[ecnt] = c; next[ecnt] = head[u]; head[u] = ecnt++;
}

int dis[MAXV];

void solve(int n) {
    memset(dis, 0, n * sizeof(int));
    for(int u = n - 1; u >= 0; --u) {
        for(int p = head[u]; ~p; p = next[p]) {
            int &v = to[p];
            dis[u] = max(dis[u], dis[v] + cost[p]);
        }
    }
}

int dates[MAXV], earning[MAXV];
int start[MAXV], finish[MAXV], rates[MAXV];
int tmp[MAXV], tcnt;
int T, n, m;

int hash(int x) {
    return lower_bound(tmp, tmp + tcnt, x) - tmp;
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; ++i) scanf("%d%d", &dates[i], &earning[i]);
        for(int i = 0; i < m; ++i) scanf("%d%d%d", &start[i], &finish[i], &rates[i]);

        tcnt = 0;
        for(int i = 0; i < n; ++i) tmp[tcnt++] = dates[i];
        for(int i = 0; i < m; ++i)
            tmp[tcnt++] = start[i], tmp[tcnt++] = finish[i];
        sort(tmp, tmp + tcnt);
        tcnt = unique(tmp, tmp + tcnt) - tmp;

        init(tcnt);
        for(int i = 1; i < tcnt; ++i) add_edge(i - 1, i, 0);
        for(int i = 0; i < m; ++i) add_edge(hash(start[i]), hash(finish[i]), rates[i]);

        solve(tcnt);
        LL ans = 0;
        for(int i = 0; i < n; ++i) {
            ans += LL(earning[i]) * dis[hash(dates[i])];
        }

        printf("Case #%d:\n", t);
        printf("%I64d.%02I64d\n", ans / 100, ans % 100);
    }
}
