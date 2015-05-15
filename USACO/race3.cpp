/*
ID: y7618231
PROG: race3
LANG: C++11
*/
#ifdef OYK_JUDGE
#define longformat "%I64d"
#else
#define longformat "%lld"
#endif // OYK_JUDGE

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXN = 110;
const int MAXM = 33;

vector<int> edge[MAXN], ans1, ans2;
vector<bool> vis, tmp;
int n;

bool bfs(int st, int ban, int ed) {
    queue<int> que; que.push(st);
    vis = vector<bool>(n); vis[st] = true;
    while(!que.empty()) {
        int u = que.front(); que.pop();
        for(int v : edge[u]) if(v != ban && !vis[v]) {
            vis[v] = true;
            que.push(v);
        }
    }
    return vis[ed];
}

bool check(int ban) {
    for(int v : edge[ban])
        if(vis[v]) return false;
    for(int u = 0; u < n; ++u) if(u != ban) {
        for(int v : edge[u]) if(v != ban) {
            if(vis[u] != vis[v]) return false;
        }
    }
    return true;
}

void solve() {
    for(int i = 1; i < n - 1; ++i)
        if(!bfs(0, i, n - 1)) ans1.push_back(i);
    printf("%d", ans1.size());
    for(int x : ans1) printf(" %d", x);
    puts("");

    for(int ban : ans1) {
        bfs(0, ban, ban);
        bool flag = check(ban);
        tmp = vis;
        for(int i = 1; flag && i < n - 1; ++i) if(i != ban)
            if(tmp[i] && !bfs(i, -1, ban)) flag = false;
        if(flag) ans2.push_back(ban);
    }
    printf("%d", ans2.size());
    for(int x : ans2) printf(" %d", x);
    puts("");
}

int main() {
#ifndef OYK_JUDGE
    freopen("race3.in", "r", stdin); freopen("race3.out", "w", stdout);
#endif // OYK_JUDGE
    int x;
    while(scanf("%d", &x) != EOF && x != -1) {
        while(x != -2) {
            edge[n].push_back(x);
            scanf("%d", &x);
        }
        n++;
    }
    solve();
}
