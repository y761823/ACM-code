/*
ID: y7618231
PROG: frameup
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
#include <string>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXN = 35;

char mat[MAXN][MAXN];
int L[MAXN], R[MAXN], U[MAXN], D[MAXN], cnt[MAXN];
vector<int> ele;
int n, m;

void update_max(int &a, int b) {
    if(a < b) a = b;
}

void update_min(int &a, int b) {
    if(a > b) a = b;
}

void init() {
    REP(i, n) REP(j, m)
        if(mat[i][j] != '.') cnt[mat[i][j] - 'A']++;
    REP(i, 26) if(cnt[i]) ele.push_back(i);
    reverse(ele.begin(), ele.end());
    REP(i, 26) L[i] = U[i] = 999;
    REP(i, n) REP(j, m) if(mat[i][j] != '.') {
        int c = mat[i][j] - 'A';
        update_min(L[c], j);
        update_max(R[c], j);
        update_min(U[c], i);
        update_max(D[c], i);
    }
}

bool cover[MAXN][MAXN];
int indeg[MAXN];
bool vis[MAXN];
vector<char> ans;
vector<string> res;

void print() {
    string s;
    for_each(ans.rbegin(), ans.rend(), [&s](char c) { s.push_back(c);});
    res.push_back(s);
}

void dfs(int u, int dep) {
    vis[u] = true;
    ans.push_back(u + 'A');
    for(int i : ele) indeg[i] -= cover[u][i];

    if(dep == (int)ele.size()) print();
    for(int i : ele)
        if(!vis[i] && indeg[i] == 0) dfs(i, dep + 1);

    for(int i : ele) indeg[i] += cover[u][i];
    ans.pop_back();
    vis[u] = false;
}

void solve() {
    for(int c : ele) {
        FOR(i, L[c], R[c]) {
            if(mat[U[c]][i] != c + 'A') cover[mat[U[c]][i] - 'A'][c] = true;
            if(mat[D[c]][i] != c + 'A') cover[mat[D[c]][i] - 'A'][c] = true;
        }
        FOR(i, U[c], D[c]) {
            if(mat[i][L[c]] != c + 'A') cover[mat[i][L[c]] - 'A'][c] = true;
            if(mat[i][R[c]] != c + 'A') cover[mat[i][R[c]] - 'A'][c] = true;
        }
    }
    for(int i : ele) for(int j : ele) indeg[j] += cover[i][j];
    for(int i : ele)
        if(indeg[i] == 0) dfs(i, 1);

    sort(begin(res), end(res));
    for(string &s : res)
        printf("%s\n", s.c_str());
}

int main() {
#ifndef OYK_JUDGE
    freopen("frameup.in", "r", stdin); freopen("frameup.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%d%d", &n, &m);
    REP(i, n) scanf("%s", mat[i]);
    init();
    solve();
}
