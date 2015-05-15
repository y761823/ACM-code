/*
ID: y7618231
PROG: shopping
LANG: C++11
*/
#ifdef OYK_JUDGE
#define longformat "%I64d"
#else
#define longformat "%lld"
#endif // OYK_JUDGE

#include <vector>
#include <iostream>
#include <tuple>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXS = 110;
const int MAXN = 1010;

int mat[MAXS][MAXN];
int need[MAXN], cost[MAXN];
int s, b;

vector<int> offer, list;
int dp[6][6][6][6][6];

inline void update_min(int &a, int b) {
    if(a > b) a = b;
}

void add(int id) {
    for(int i = 1; i <= 999; ++i)
        if(mat[id][i] > need[i]) return ;
    offer.push_back(id);
}

int get_id(size_t i) {
    if(i < list.size()) return list[i];
    return 1000;
}

#define FOR(i) for(k[i] = 0; k[i] <= need[get_id(i)]; ++k[i])
int solve() {
    for(int i = 0; i < s; ++i) add(i);
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0][0][0][0] = 0;
    int k[5], nk[5];
    FOR(0) FOR(1) FOR(2) FOR(3) FOR(4) {
        for(int off : offer) {
            bool flag = true;
            memcpy(nk, k, sizeof(k));
            for(int i = 0; i < 5; ++i) {
                nk[i] = k[i] + mat[off][get_id(i)];
                if(nk[i] > need[get_id(i)]) flag = false;
            }
            if(flag) update_min(dp[nk[0]][nk[1]][nk[2]][nk[3]][nk[4]], dp[k[0]][k[1]][k[2]][k[3]][k[4]] + mat[off][0]);
        }
    }
    return dp[need[get_id(0)]][need[get_id(1)]][need[get_id(2)]][need[get_id(3)]][need[get_id(4)]];
}

int main() {
#ifndef OYK_JUDGE
    freopen("shopping.in", "r", stdin); freopen("shopping.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%d", &s);
    for(int i = 0; i < s; ++i) {
        int n, c, k;
        scanf("%d", &n);
        for(int j = 0; j < n; ++j) {
            scanf("%d%d", &c, &k);
            mat[i][c] = k;
        }
        scanf("%d", &mat[i][0]);
    }
    scanf("%d", &b);
    int c, k, p;
    for(int i = 0; i < b; ++i) {
        scanf("%d%d%d", &c, &k, &p);
        need[c] = k;
        list.push_back(c);

        mat[s][c] = 1;
        mat[s++][0] = p;
    }
    printf("%d\n", solve());
}
