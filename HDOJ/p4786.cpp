////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-09-12 15:09:13
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4786
////Problem Title: 
////Run result: Accept
////Run time:734MS
////Run memory:1892KB
//////////////////System Comment End//////////////////
#ifdef ONLINE_JUDGE
#define longformat "%lld"
#else
#define longformat "%I64d"
#endif // ONLINE_JUDGE

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>
using namespace std;
typedef long long LL;

const int MAXN = 100010;

struct Edge {
    int u, v, c;
    void read() {
        scanf("%d%d%d", &u, &v, &c);
    }
    bool operator < (const Edge &rhs) const {
        return c < rhs.c;
    }
} edge[MAXN];

int fa[MAXN];
int n, m, T;

int get_set(int x) {
    return fa[x] == x ? x : fa[x] = get_set(fa[x]);
}

int kruskal() {
    for(int i = 1; i <= n; ++i) fa[i] = i;
    int res = 0;
    for(int i = 0; i < m; ++i) {
        int fu = get_set(edge[i].u), fv = get_set(edge[i].v);
        if(fu != fv) {
            res += edge[i].c;
            fa[fu] = fv;
        }
    }
    for(int i = 2; i <= n; ++i)
        if(get_set(1) != get_set(i)) return -1;
    return res;
}

int fib[33], fcnt = 30;
void get_fib() {
    fib[1] = fib[2] = 1;
    for(int i = 3; i <= fcnt; ++i)
        fib[i] = fib[i - 2] + fib[i - 1];
    //printf("%d\n", fib[fcnt]);
}

bool solve() {
    sort(edge, edge + m);
    int ans1 = kruskal();
    if(ans1 == -1) return false;

    reverse(edge, edge + m);
    int ans2 = kruskal();
    //printf("%d %d\n", ans1, ans2);

    for(int i = 1; i <= fcnt; ++i)
        if(ans1 <= fib[i] && fib[i] <= ans2) return true;
    return false;
}

int main() {
    get_fib();
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d", &n, &m);
        for(int i = 0; i < m; ++i) edge[i].read();
        printf("Case #%d: %s\n", t, solve() ? "Yes" : "No");
    }
}
