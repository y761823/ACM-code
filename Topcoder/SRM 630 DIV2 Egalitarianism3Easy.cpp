#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <queue>
using namespace std;
typedef long long LL;

const int MAXN = 13;
const int MAXE = 25;

int head[MAXN], ecnt, n;
int to[MAXE], nxt[MAXE], cost[MAXE];
int mat[MAXN][MAXN];

void init(int n) {
    ::n = n;
    memset(head + 1, -1, n * sizeof(int));
    ecnt = 0;
}

void add_edge(int u, int v, int c) {
    to[ecnt] = v; cost[ecnt] = c; nxt[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; cost[ecnt] = c; nxt[ecnt] = head[v]; head[v] = ecnt++;
}

void dfs(int st, int u, int f, int d) {
    mat[st][u] = d;
    for(int p = head[u]; ~p; p = nxt[p]) {
        int v = to[p];
        if(v != f) dfs(st, v, u, d + cost[p]);
    }
}

bool check(int state) {
    int d = -1;
    for(int i = 0; i < n; ++i) if((state >> i) & 1) {
        for(int j = i + 1; j < n; ++j) if((state >> j) & 1) {
            int tmp = mat[i + 1][j + 1];
            if(d == -1) d = tmp;
            if(d != tmp) return false;
        }
    }
    return true;
}

class Egalitarianism3Easy {
public:
    int maxCities(int n, vector <int> a, vector <int> b, vector <int> len) {
        init(n);
        for(int i = 0; i < n - 1; ++i)
            add_edge(a[i], b[i], len[i]);
        for(int i = 1; i <= n; ++i)
            dfs(i, i, -1, 0);
        int res = 0;
        for(int i = 1; i < (1 << n); ++i)
            if(check(i)) res = max(res, __builtin_popcount(i));
        return res;
    }
};
