#include <cstdio>
#include <algorithm>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define forall(i, v) for(__typeof(v.begin()) i = v.begin(); i != v.end(); ++i)

int fx[] = {0, 1, 0, -1};
int fy[] = {1, 0, -1, 0};

char mat[44][44];
int h, w, n, T;

vector<int> adj[418];
int link[418];
bool vis[418];

void init() {
    for(int i = 0; i < n; ++i) adj[i].clear();
}

bool dfs(int u) {
    if(vis[u]) return false;
    vis[u] = true;
    forall(v, adj[u]) {
        if(link[*v] == -1 || dfs(link[*v])) {
            link[*v] = u;
            return true;
        }
    }
    return false;
}

int hungry() {
    memset(link, -1, n * sizeof(int));
    int res = 0;
    for(int i = 0; i < n; ++i) {
        memset(vis, 0, n * sizeof(bool));
        res += dfs(i);
    }
    return res;
}

int mycount() {
    int res = 0;
    for(int i = 1; i <= h; ++i)
        for(int j = 1; j <= w; ++j) res += (mat[i][j] == '*');
    return res;
}

int solve() {
    init();
    for(int i = 1; i <= h; ++i) {
        for(int j = 1; j <= w; ++j) if(mat[i][j] == '*') if((i + j) & 1) {
            for(int f = 0; f < 4; ++f) {
                int ii = i + fx[f], jj = j + fy[f];
                if(mat[ii][jj] == '*') adj[(i - 1) * w + j - 1].push_back((ii - 1) * w + jj - 1);
            }
        }
    }
    return mycount() - hungry();
}

int main() {
    scanf("%d", &T);
    while(T--) {
        memset(mat, 0, sizeof(mat));
        scanf("%d%d", &h, &w);
        n = w * h;
        for(int i = 1; i <= h; ++i)
            scanf("%s", mat[i] + 1);
        printf("%d\n", solve());
    }
}
