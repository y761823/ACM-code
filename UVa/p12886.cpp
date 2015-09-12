#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
typedef long long LL;

const int MAXN = 2010;
const LL seed1 = 131;
const LL seed2 = 10007;
const int MOD = 1000000007;

char mm[MAXN][MAXN], pp[MAXN][MAXN];
int code1[MAXN][MAXN], code2[MAXN][MAXN];
int hp, wp, hm, wm;
LL ss1, ss2;

LL power(LL x, int p) {
    LL res = 1;
    while(p) {
        if(p & 1) res = res * x % MOD;
        x = x * x % MOD;
        p >>= 1;
    }
    return res;
}

LL getf(LL x) {
    return (-x % MOD + MOD) % MOD;
}

void init(char mat[MAXN][MAXN], int h, int w) {
    for(int i = 0; i < h; ++i) {
        code1[i][0] = mat[i][0];
        for(int j = 1; j < w; ++j) {
            code1[i][j] = (code1[i][j - 1] * seed1 + mat[i][j]) % MOD;
            if(j >= wp) code1[i][j] = (code1[i][j] + getf(mat[i][j - wp] * ss1)) % MOD;
        }
    }
    for(int i = 0; i < h; ++i) {
        for(int j = 0; j < w; ++j) {
            if(i == 0) code2[i][j] = code1[i][j];
            else code2[i][j] = (code2[i - 1][j] * seed2 + code1[i][j]) % MOD;
            if(i >= hp) code2[i][j] = (code2[i][j] + getf(code1[i - hp][j] * ss2)) % MOD;
        }
    }
}

int solve() {
    ss1 = power(seed1, wp);
    ss2 = power(seed2, hp);
    init(pp, hp, wp);
    int target = code2[hp - 1][wp - 1];
    init(mm, hm, wm);

    int res = 0;
    for(int i = 0; i < hm; ++i)
        for(int j = 0; j < wm; ++j) if(i >= hp - 1 && j >= wp - 1)
            res += (code2[i][j] == target);
    return res;
}

int main() {
    while(scanf("%d%d%d%d", &hp, &wp, &hm, &wm) != EOF) {
        for(int i = 0; i < hp; ++i) scanf("%s", pp[i]);
        for(int i = 0; i < hm; ++i) scanf("%s", mm[i]);
        printf("%d\n", solve());
    }
}
