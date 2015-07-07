////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-09-14 18:09:33
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 5009
////Problem Title: 
////Run result: Accept
////Run time:1328MS
////Run memory:1292KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <set>
using namespace std;
typedef long long LL;

const int MAXN = 50010;
const int MAXT = MAXN << 1;
const int INF = 0x3f3f3f3f;

int tmp[MAXN], tcnt;

int hash(int x) {
    return lower_bound(tmp, tmp + tcnt, x) - tmp;
}

int a[MAXN], n;
int dp[MAXN];

int sqr(int x) {
    return x * x;
}

struct Node {
    int l, r;
    Node() {}
    Node(int l, int r): l(l), r(r) {}
} stk[256];
int top;

int pre[MAXN], last[MAXN];

int solve() {
    memset(last, 0, sizeof(last));
    for(int i = 1; i <= n; ++i) {
        pre[i] = last[a[i]];
        last[a[i]] = i;
    }

    top = 1;
    for(int i = 1; i <= top; ++i)
        stk[i] = Node(1, 1);
    dp[0] = 0; dp[1] = 1;

    for(int i = 2; i <= n; ++i) {
        bool flag = false;
        for(int j = top; j > 0; --j) {
            if(pre[i] < stk[j].l) {
                if(!flag) stk[j + 1].r = stk[j].r;
                else stk[j + 1] = stk[j];
                flag = true;
            }
        }
        if(top * top <= n && pre[i] < stk[top].l) stk[++top].l = 1;
        stk[1] = Node(i, i);

        dp[i] = i;
        for(int j = 1; j <= top; ++j)
            dp[i] = min(dp[i], dp[stk[j].l - 1] + sqr(j));
    }
    return dp[n];
}

int main() {
    while(scanf("%d", &n) != EOF) {
        for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        n = unique(a + 1, a + n + 1) - a - 1;
        tcnt = 0;
        for(int i = 1; i <= n; ++i) tmp[tcnt++] = a[i];
        sort(tmp, tmp + tcnt);
        tcnt = unique(tmp, tmp + tcnt) - tmp;
        for(int i = 1; i <= n; ++i) a[i] = hash(a[i]);
        printf("%d\n", solve());
    }
}
