/*
ID: y7618231
PROG: charrec
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
#include <numeric>
#include <set>
#include <deque>
#include <queue>
#include <cctype>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXN = 1210;
const int MAXC = 33;
const int INF = 0x3f3f3f3f;

const char Alpha[] = " abcdefghijklmnopqrstuvwxyz";

int get_bit() {
    char c = getchar();
    while(!isdigit(c)) c = getchar();
    int res = 0;
    while(isdigit(c)) res = res * 2 + c - '0', c = getchar();
    return res;
}

int bitcnt[1 << 20];
int font[MAXN], src[MAXN];
int go[MAXN][3], type[MAXN][3];
int n;

void init() {
    for(int i = 0; i < (1 << 20); ++i)
        bitcnt[i] = __builtin_popcount(i);
    memset(go, 0x3f, sizeof(go));
    for(int i = 0; i < n; ++i) {
        if(i + 19 - 1 < n) {
            for(int p = 0; p < 27; ++p) {
                for(int lost = 0; lost < 20; ++lost) {
                    int cnt = 0;
                    for(int j = 0; j < 20; ++j) if(j != lost)
                        cnt += bitcnt[src[i + j - (j > lost)] ^ font[p * 20 + j]];
                    if(cnt < go[i][0]) go[i][0] = cnt, type[i][0] = p;
                }
            }
        }

        if(i + 20 - 1 < n) {
            for(int p = 0; p < 27; ++p) {
                int cnt = 0;
                for(int j = 0; j < 20; ++j)
                    cnt += bitcnt[src[i + j] ^ font[p * 20 + j]];
                if(cnt < go[i][1]) go[i][1] = cnt, type[i][1] = p;
            }
        }

        if(i + 21 - 1 < n) {
            for(int p = 0; p < 27; ++p) {
                for(int more = 0; more < 20; ++more) {
                    int cnt = 0;
                    for(int j = 0; j < 20; ++j)
                        cnt += bitcnt[src[i + j + (j >= more)] ^ font[p * 20 + j]];
                    if(cnt < go[i][2]) go[i][2] = cnt, type[i][2] = p;
                }
            }
        }
    }
}

int dp[MAXN], pre[MAXN];

void print(int i) {
    if(i == 0) return ;
    print(i - 19 - pre[i]);
    putchar(Alpha[type[i - 19 - pre[i]][pre[i]]]);
}

void solve() {
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    for(int i = 0; i < n; ++i) {
        if(dp[i] == INF) continue;
        for(int j = 0; j < 3; ++j) if(i + 19 + j - 1 < n) {
            if(dp[i + 19 + j] > dp[i] + go[i][j]) {
                dp[i + 19 + j] = dp[i] + go[i][j];
                pre[i + 19 + j] = j;
            }
        }
    }
}

int main() {
#ifndef OYK_JUDGE
    freopen("charrec.in", "r", stdin); freopen("charrec.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) src[i] = get_bit();

    freopen("font.in", "r", stdin);
    scanf("%*d");
    for(int i = 0; i < 540; ++i) font[i] = get_bit();

    init();
    solve();
    print(n);
    puts("");
}
