/*
ID: y7618231
PROG: starry
LANG: C++11
*/
#ifdef OYK_JUDGE
#define longformat "%I64d"
#else
#define longformat "%lld"
#endif // OYK_JUDGE

#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
#include <cstdio>
#include <cstring>
#include <unordered_map>
using namespace std;
typedef long long LL;

const int MAXN = 110;
const int seedA = 131;
const int seedB = 1234567;
const int MOD = 1000000007;

void update_max(int &a, int b) {
    if(a < b) a = b;
}

void update_min(int &a, int b) {
    if(b < a) a = b;
}

int get_hash(const vector<int>& vec) {
    LL res = 0;
    for(int x : vec) res = (res * seedA + x) % MOD;
    return res;
}

int get_hash(const vector<vector<int>>& mat) {
    LL res = 0;
    for(auto &vec : mat)
        res = (res * seedB + get_hash(vec)) % MOD;
    return res;
}

void rotate(vector<vector<int>> &mat) {
    vector<vector<int>> res(mat[0].size(), vector<int>(mat.size()));
    for(size_t i = 0; i < mat.size(); ++i) {
        for(size_t j = 0; j < mat[i].size(); ++j)
            res[mat[i].size() - j - 1][i] = mat[i][j];
    }
    mat = res;
}

void flip(vector<vector<int>> &mat) {
    for(auto &vec : mat)
        reverse(begin(vec), end(vec));
}

unordered_map<int, char> mymap;
char newchar;

void insert(vector<vector<int>> &mat, char c) {
    for(int _ = 0; _ < 2; ++_ ) {
        mymap[get_hash(mat)] = c;
        for(int i = 0; i < 3; ++i)
            rotate(mat), mymap[get_hash(mat)] = c;
        if(!_) flip(mat);
    }
}

char find(vector<vector<int>> &mat) {
    int key = get_hash(mat);
    auto it = mymap.find(key);
    if(it != mymap.end()) return it->second;
    insert(mat, newchar++);
    return newchar - 1;
}

char mat[MAXN][MAXN];
int vis[MAXN][MAXN], viscnt;
int n, m;

int fr[] = {-1, -1, -1, 0, 1, 1, 1, 0};
int fc[] = {-1, 0, 1, 1, 1, 0, -1, -1};

void fullfill(int sr, int sc) {
    int L, R, U, D;
    L = R = sc; U = D = sr;
    queue<pair<int, int>> que; que.push(make_pair(sr, sc));
    vis[sr][sc] = ++viscnt;
    while(!que.empty()) {
        int r = que.front().first, c = que.front().second; que.pop();
        update_min(U, r);
        update_max(D, r);
        update_min(L, c);
        update_max(R, c);
        for(int f = 0; f < 8; ++f) {
            int nr = r + fr[f], nc = c + fc[f];
            if(mat[nr][nc] == '1' && vis[nr][nc] < viscnt) {
                vis[nr][nc] = viscnt;
                que.push(make_pair(nr, nc));
            }
        }
    }

    vector<vector<int>> tmp(D - U + 1, vector<int>(R - L + 1));
    for(size_t i = 0; i < tmp.size(); ++i) {
        for(size_t j = 0; j < tmp[i].size(); ++j)
            tmp[i][j] = (vis[i + U][j + L] == viscnt);
    }

    char c = find(tmp);
    for(int i = U; i <= D; ++i)
        for(int j = L; j <= R; ++j) if(vis[i][j] == viscnt)
            mat[i][j] = c;
}

int main() {
#ifndef OYK_JUDGE
    freopen("starry.in", "r", stdin); freopen("starry.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%d%d", &m, &n);
    for(int i = 1; i <= n; ++i) scanf("%s", &mat[i][1]);
    newchar = 'a';
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j) if(mat[i][j] == '1')
            fullfill(i, j);
    for(int i = 1; i <= n; ++i)
        printf("%s\n", &mat[i][1]);
}
