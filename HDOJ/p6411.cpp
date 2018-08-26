#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

typedef long long LL;

const int MAXN = 100010 + 10;
const int MOD = 1e9 + 7;

vector<vector<int>> block;
vector<int> edges[MAXN];
int value[MAXN], cnt[50];
bool vis[MAXN];
int n, m, T;

void dfs(int u) {
    if (vis[u])
        return ;
    vis[u] = true;
    block.back().push_back(u);

    for (auto v : edges[u])
        dfs(v);
}

int solve() {
    memset(vis + 1, 0, n * sizeof(bool));
    block.clear();
    for (int i = 1; i <= n; ++i) if (!vis[i]) {
        block.push_back({});
        dfs(i);
    }

    int res = 0;
    for (auto& vec : block) {
        sort(vec.begin(), vec.end(), [](int u, int v) {
            return value[u] < value[v];
        });
        memset(cnt, 0, sizeof(cnt));
        for (int u : vec) {
            int x = value[u];
            for (int i = 0; i < 31; ++i) if (x & (1 << i)) {
                LL sum = (LL)(1 << i) * cnt[i] % MOD;
                res = (res + x * sum) % MOD;
            }
            for (int i = 0; i < 31; ++i) if (x & (1 << i)) {
                cnt[i]++;
            }
        }
    }
    return res;
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i) {
            edges[i].clear();
            scanf("%d", &value[i]);
        }
        for (int i = 0, a, b; i < m; ++i) {
            scanf("%d%d", &a, &b);
            edges[a].push_back(b);
            edges[b].push_back(a);
        }
        printf("%d\n", solve());
    }
}
