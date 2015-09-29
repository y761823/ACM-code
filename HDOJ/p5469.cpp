#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;

const int MAXN = 10010;
const LL SEED = 131;
const int MOD = 1000000007;

vector<int> adjs[MAXN];
char val[MAXN], str[MAXN];
int lhash[MAXN], rhash[MAXN], base[MAXN];
int n, m, T;

vector<int> vec;
int size[MAXN], maxsize[MAXN];
bool del[MAXN];

void dfs_size(int u, int f) {
    maxsize[u] = 0;
    size[u] = 1;
    for(int v : adjs[u]) if(v != f && !del[v]) {
        dfs_size(v, u);
        size[u] += size[v];
        maxsize[u] = max(maxsize[u], size[v]);
    }
    vec.push_back(u);
}

int getroot(int st) {
    vec.clear();
    dfs_size(st, 0);
    int res = st;
    for(int u : vec) {
        maxsize[u] = max(maxsize[u], size[st] - size[u]);
        if(maxsize[u] < maxsize[res]) res = u;
    }
    return res;
}

bool lvis[MAXN], rvis[MAXN];
int lstk[MAXN], ltop;
int rstk[MAXN], rtop;

bool dfs_check(int u, int f, int dep, int hashval) {
    hashval = (hashval + base[dep] * LL(val[u])) % MOD;
    if(hashval == lhash[dep + 1]) {
        if(rvis[dep + 1]) return true;
        lstk[ltop++] = dep + 1;
    }
    if(hashval == rhash[m - dep]) {
        if(lvis[m - dep]) return true;
        rstk[rtop++] = m - dep;
    }
    for(int v : adjs[u]) if(v != f && !del[v])
        if(dfs_check(v, u, dep + 1, hashval)) return true;
    return false;
}

int clstk[MAXN], cltop;
int crstk[MAXN], crtop;
bool dfs_ans(int st) {
    int rt = getroot(st);
    del[rt] = true;
    ltop = rtop = cltop = crtop = 0;
    for(int v : adjs[rt]) if(!del[v]) {
        if(dfs_check(v, rt, 1, val[rt])) return true;
        while(ltop) lvis[ clstk[cltop++] = lstk[--ltop] ] = true;
        while(rtop) rvis[ crstk[crtop++] = rstk[--rtop] ] = true;
    }
    if(lvis[m] || rvis[1]) return true;
    while(cltop) lvis[ clstk[--cltop] ] = false;
    while(crtop) rvis[ crstk[--crtop] ] = false;
    for(int v : adjs[rt]) if(!del[v])
        if(dfs_ans(v)) return true;
    return false;
}

void init() {
    lhash[1] = str[1];
    for(int i = 2; i <= m; ++i)
        lhash[i] = (lhash[i - 1] * SEED + str[i]) % MOD;
    rhash[m] = str[m];
    for(int i = m - 1; i > 0; --i)
        rhash[i] = (rhash[i + 1] * SEED + str[i]) % MOD;
    memset(del + 1, 0, n * sizeof(bool));
    memset(lvis + 1, 0, m * sizeof(bool));
    memset(rvis + 1, 0, m * sizeof(bool));
}

bool solve() {
    if(m == 1)
        return strchr(val + 1, str[1]) != NULL;

    init();
    return dfs_ans(1);
}

int main() {
    base[0] = 1;
    for(int i = 1; i < MAXN; ++i)
        base[i] = base[i - 1] * SEED % MOD;

    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i)
            adjs[i].clear();
        for(int i = 1, u, v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            adjs[u].push_back(v);
            adjs[v].push_back(u);
        }
        scanf("%s%s", val + 1, str + 1);
        m = strlen(str + 1);
        printf("Case #%d: %s\n", t, solve() ? "Find" : "Impossible");
    }
}
