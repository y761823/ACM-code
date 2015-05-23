#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <stack>
#include <numeric>
#include <vector>
using namespace std;
typedef long long LL;
#define foreach(u, vec) for(__typeof(vec.begin()) u = vec.begin(); u != vec.end(); ++u)

const int MAXN = 110;

vector<int> adj[MAXN];
int indeg[MAXN];
int n, m;

bool solve() {
    stack<int> stk;
    for(int i = 1; i <= n; ++i) if(!indeg[i])
        stk.push(i);
    while(!stk.empty()) {
        int u = stk.top(); stk.pop();
        foreach(v, adj[u])
            if(--indeg[*v] == 0) stk.push(*v);
    }
    return accumulate(indeg + 1, indeg + n + 1, 0) == 0;
}

int main() {
    while(scanf("%d%d", &n, &m) != EOF) {
        for(int i = 1; i <= n; ++i)
            adj[i].clear();
        memset(indeg + 1, 0, n * sizeof(int));
        for(int i = 0, u, v; i < m; ++i) {
            scanf("%d%d", &u, &v);
            adj[v].push_back(u);
            indeg[u]++;
        }
        puts(solve() ? "YES" : "NO");
    }
}
