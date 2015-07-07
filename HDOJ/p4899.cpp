////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-08-03 22:03:22
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4899
////Problem Title: 
////Run result: Accept
////Run time:1281MS
////Run memory:1060KB
//////////////////System Comment End//////////////////
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 20;
const int MOD = 1e9 + 7;

char dic[] = "ACTG";
int add[1 << 15][4];
int dp[2][1 << 15];
int pre[MAXN], lcs[MAXN], ans[MAXN];
char s[MAXN];
int T, n, m;

inline void update_add(int &a, int b) {
    a += b;
    if(a >= MOD) a -= MOD;
}

void init() {
    for(int state = 0; state < (1 << n); ++state) {
        pre[0] = 0;
        for(int i = 1; i <= n; ++i) pre[i] = pre[i - 1] + ((state >> (i - 1)) & 1);
        for(int k = 0; k < 4; ++k) {
            for(int i = 1; i <= n; ++i) {
                if(s[i] == dic[k]) lcs[i] = pre[i - 1] + 1;
                else lcs[i] = max(lcs[i - 1], pre[i]);
            }
            int &t = add[state][k] = 0;
            for(int i = 1; i <= n; ++i)
                t |= ((lcs[i] != lcs[i - 1]) << (i - 1));
        }
    }
}

void solve() {
    int *now = dp[0], *next = dp[1];
    memset(next, 0, (1 << n) * sizeof(int));
    next[0] = 1;
    for(int _ = 0; _ < m; ++_) {
        swap(now, next);
        memset(next, 0, (1 << n) * sizeof(int));
        for(int state = 0; state < (1 << n); ++state) if(now[state])
            for(int k = 0; k < 4; ++k)
                update_add(next[add[state][k]], now[state]);
    }
    memset(ans, 0, sizeof(ans));
    for(int state = 0; state < (1 << n); ++state) {
        update_add(ans[__builtin_popcount(state)], next[state]);
    }
    for(int i = 0; i <= n; ++i)
        printf("%d\n", ans[i]);
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%s%d", s + 1, &m);
        n = strlen(s + 1);
        init();
        solve();
    }
}
