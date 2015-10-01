#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
typedef long long LL;
#define FOR(i, s, t) for(int i = s; i <= t; ++i)
#define foreach(it, vec) for(__typeof(vec.begin()) it = vec.begin(); it != vec.end(); ++it)

const int MAXN = 33;
const int INF = 0x3f3f3f3f;

vector<int> adjs[MAXN];
int last[510];

bool mat[MAXN][MAXN], vis[MAXN];
int n, m;
int res;

bool mustselect(int u) {
    for(int i = 0; i < u; ++i)
        if(!vis[i] && mat[i][u]) return true;
    return false;
}

void dfs(int u, int c) {
    if(c >= res) return ;
    if(u == n) {
        res = c;
    } else {
        vis[u] = true;
        dfs(u + 1, c + 1);
        vis[u] = false;

        if(!mustselect(u)) {
            int t = 0;
            foreach(it, adjs[u]) if(last[*it] == -1) {
                last[*it] = u;
                t++;
            }
            dfs(u + 1, c + t);
            foreach(it, adjs[u]) if(last[*it] == u)
                last[*it] = -1;
        }
    }
}

int solve() {
    memset(vis, 0, sizeof(vis));
    res = n;
    dfs(0, 0);
    return res;
}

int main() {
    while(scanf("%d%d", &n, &m) != EOF) {
        memset(mat, 0, sizeof(mat));
        memset(last, -1, sizeof(last));
        for(int i = 0; i < 30; ++i)
            adjs[i].clear();

        for(int i = 0, a, b; i < m; ++i) {
            scanf("%d%d", &a, &b);
            a--, b--;
            if(a > b) swap(a, b);
            if(b < 30) mat[a][b] = mat[b][a] = true;
            else adjs[a].push_back(b);
        }

        n = min(n, 30);
        printf("%d\n", solve());
    }
}
