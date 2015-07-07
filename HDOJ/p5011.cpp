////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-10-12 15:57:07
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 5011
////Problem Title: 
////Run result: Accept
////Run time:484MS
////Run memory:288KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;
typedef long long LL;
#define FOR(i, n) for(int i = 0; i < n; ++i)

int main() {
    int res, n;
    while(scanf("%d", &n) != EOF) {
        res = 0;
        for(int i = 0, x; i < n; ++i)
            scanf("%d", &x), res ^= x;
        puts(res ? "Win" : "Lose");
    }
}
