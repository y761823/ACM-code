#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXN = 43;
const int MOD = 1e9 + 7;

int x1[MAXN], x2[MAXN], y1[MAXN], y2[MAXN], v[MAXN];
int mat[MAXN][MAXN], cnt[MAXN][MAXN], val[MAXN][MAXN][2];
int T, h, w, m, n;

LL power(LL x, int p) {
    LL res = 1;
    while(p) {
        if(p & 1) res = res * x % MOD;
        x = x * x % MOD;
        p >>= 1;
    }
    return res;
}

vector<int> xhashtable, yhashtable;

int gethash(vector<int>& hashtable, int val) {
    return lower_bound(hashtable.begin(), hashtable.end(), val) - hashtable.begin() + 1;
}
void unique(vector<int>& vec) {
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
}

void init() {
    xhashtable.clear(); xhashtable.push_back(1); xhashtable.push_back(h + 1);
    yhashtable.clear(); yhashtable.push_back(1); yhashtable.push_back(w + 1);
    for(int i = 0; i < n; ++i) {
        xhashtable.push_back(x1[i]);
        xhashtable.push_back(x2[i] + 1);
        yhashtable.push_back(y1[i]);
        yhashtable.push_back(y2[i] + 1);
    }
    unique(xhashtable);
    unique(yhashtable);

    for(int i = 0; i < n; ++i) {
        x1[i] = gethash(xhashtable, x1[i]);
        x2[i] = gethash(xhashtable, x2[i] + 1);
        y1[i] = gethash(yhashtable, y1[i]);
        y2[i] = gethash(yhashtable, y2[i] + 1);
    }

    FOR(i, 1, (int)xhashtable.size()) FOR(j, 1, (int)yhashtable.size())
        mat[i][j] = m;
    for(int i = 0; i < n; ++i) {
        FOR(x, x1[i], x2[i] - 1) FOR(y, y1[i], y2[i] - 1) {
            mat[x][y] = min(mat[x][y], v[i]);
        }
    }

    FOR(i, 1, (int)xhashtable.size() - 1) FOR(j, 1, (int)yhashtable.size() - 1) {
        int cnt = (xhashtable[i] - xhashtable[i - 1]) * (yhashtable[j] - yhashtable[j - 1]);
        val[i][j][0] = power(mat[i][j], cnt);
        val[i][j][1] = power(mat[i][j] - 1, cnt);
    }
}

int dfs(int p, int flag = 1) {
    if(p == n) {
        LL res = 1;
        FOR(i, 1, (int)xhashtable.size() - 1) FOR(j, 1, (int)yhashtable.size() - 1) {
            res = res * val[i][j][cnt[i][j] > 0] % MOD;
        }
        return (res * flag + MOD) % MOD;
    } else {
        int res = dfs(p + 1, flag);
        FOR(i, x1[p], x2[p] - 1) FOR(j, y1[p], y2[p] - 1) cnt[i][j] += (v[p] == mat[i][j]);
        res = (res + dfs(p + 1, -flag)) % MOD;
        FOR(i, x1[p], x2[p] - 1) FOR(j, y1[p], y2[p] - 1) cnt[i][j] -= (v[p] == mat[i][j]);
        return res;
    }
}

int main() {
    scanf("%d", &T);
    FOR(kase, 1, T) {
        scanf("%d%d%d%d", &h, &w, &m, &n);
        for(int i = 0; i < n; ++i) {
            scanf("%d%d%d%d%d", &x1[i], &y1[i], &x2[i], &y2[i], &v[i]);
        }
        init();
        printf("Case #%d: %d\n", kase, dfs(0));
    }
}
