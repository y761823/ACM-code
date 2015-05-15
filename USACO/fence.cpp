/*
ID: y7618231
PROG: fence
LANG: C++
*/
#ifdef OYK_JUDGE
#define longformat "%I64d"
#else
#define longformat "%lld"
#endif // OYK_JUDGE

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
using namespace std;
typedef long long LL;

const int MAXV = 510;
const int MAXE = 1024;

vector<pair<int, int> > edge[MAXV];
bool vis[MAXE];
int n = 0, m, st = MAXV;

stack<int> stk;
void dfs(int u) {
    for(size_t i = 0; i < edge[u].size(); ++i) {
        int v = edge[u][i].first, id = edge[u][i].second;
        if(vis[id]) continue;
        vis[id] = true;
        dfs(v);
    }
    stk.push(u);
}

void print() {
    while(!stk.empty()) {
        printf("%d\n", stk.top()); stk.pop();
    }
}

int main() {
#ifndef OYK_JUDGE
    freopen("fence.in", "r", stdin); freopen("fence.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%d", &m);
    for(int i = 0, u, v; i < m; ++i) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(make_pair(v, i));
        edge[v].push_back(make_pair(u, i));
        st = min(st, min(u, v));
        n = max(n, max(u, v));
    }
    for(int i = 1; i <= n; ++i) {
        if(edge[i].size() & 1) {
            st = i;
            break;
        }
    }
    for(int i = 1; i <= n; ++i)
        sort(edge[i].begin(), edge[i].end());
    dfs(st);
    print();
}
