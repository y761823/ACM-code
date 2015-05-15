#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define FOR(i, n) for(int i = 0; i < n; ++i)

const int MAXV = 510;

vector<int> vec;
int mat[MAXV][MAXV];
int link[MAXV];
bool vis[MAXV];
int n;

bool dfs(int u, int max_val) {
    if(vis[u]) return false;
    vis[u] = true;
    for(int i = 1; i <= n; ++i) if(mat[u][i] <= max_val) {
        if(link[i] == -1 || dfs(link[i], max_val)) {
            link[i] = u;
            return true;
        }
    }
    return false;
}

bool hungry(int max_val) {
    memset(link + 1, -1, n * sizeof(int));
    for(int i = 1; i <= n; ++i) {
        memset(vis + 1, 0, n * sizeof(bool));
        if(!dfs(i, max_val)) return false;
    }
    return true;
}

int solve() {
    int l = 0, r = vec.size();
    while(l < r) {
        int mid = (l + r) >> 1;
        if(!hungry(vec[mid])) l = mid + 1;
        else r = mid;
    }
    hungry(vec[l]);
    return vec[l];
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j) scanf("%d", &mat[i][j]), vec.push_back(mat[i][j]);
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());

    printf("%d\n", solve());
    for(int i = 1; i <= n; ++i)
        printf("%d %d\n", link[i], i);
}
