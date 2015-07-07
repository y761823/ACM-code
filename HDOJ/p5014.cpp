////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-10-14 16:32:28
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 5014
////Problem Title: 
////Run result: Accept
////Run time:703MS
////Run memory:684KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef unsigned long long ULL;
typedef long long LL;

const int MAXN = 100010;

int link[MAXN];
int n;

LL solve() {
    LL res = 0;
    int t = n;
    while(t >= 0) {
        int p = t;
        while(p && p != (1 << (__builtin_ffs(p) - 1))) --p;
        if(p == 0) {
            link[0] = 0;
            break;
        }
        for(int i = 0; p + i <= t; ++i) {
            link[p + i] = p - i - 1;
            link[p - i - 1] = p + i;
            res += ((p + i) ^ (p - i - 1)) << 1;
        }
        t -= 2 * (t - p + 1);
    }
    return res;
}

int main() {
    while(scanf("%d", &n) != EOF) {
        printf("%I64d\n", solve());
        for(int i = 0, a; i <= n; ++i) {
            if(i) putchar(' ');
            scanf("%d", &a);
            printf("%d", link[a]);
        }
        puts("");
    }
}
