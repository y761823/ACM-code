////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-07-20 19:48:08
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 2894
////Problem Title: 
////Run result: Accept
////Run time:31MS
////Run memory:344KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;

const int MAXM = 2048;

int s[MAXM];
bool vis[MAXM];

int m, k;

int trans(int now, int v) {
    return (now & ~(1 << (k - 1))) << 1 | v;
}

bool dfs(int i, int now) {
    if(i == m - 1 && now == m - 1) return true;
    if(vis[now]) return false;
    s[i] = now & 1;
    vis[now] = true;
    if(dfs(i + 1, trans(now, 0))) return true;
    if(dfs(i + 1, trans(now, 1))) return true;
    return vis[now] = false;
}

int main() {
    while(scanf("%d", &k) != EOF) {
        memset(vis, 0, sizeof(vis));
        m = 1 << k;
        dfs(0, m - 2);
        s[m - 1] = 1;
        printf("%d ", m);
        for(int i = 0; i < m; ++i) printf("%d", s[i]);
        puts("");
    }
}