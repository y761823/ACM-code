////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-05-25 21:04:39
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4834
////Problem Title: 
////Run result: Accept
////Run time:2109MS
////Run memory:117820KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;
typedef long long LL;

const int MAXN = 1e7 + 10;

int cnt[MAXN];
LL ans[MAXN];

void initc() {
    int n = 1e7;
    for(int i = 1; i <= n; i += 2) {
        for(int j = i; j <= n; j += i) cnt[j]++;
    }
}

void init() {
    initc();
    int n = 1e7;
    ans[1] = 2;
    LL t = 0;
    for(int i = 2; i <= n; ++i) {
        t += cnt[i - 1];
        ans[i] = ans[i - 1] + t + 1;
    }
}

int main() {
    init();
    int T, n;
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d", &n);
        printf("Case #%d:\n", t);
        printf("%I64d\n", ans[n]);
    }
}