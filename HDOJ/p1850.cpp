////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-01-24 22:01:49
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 1850
////Problem Title: 
////Run result: Accept
////Run time:15MS
////Run memory:316KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 110;

int a[MAXN], n;

int main() {
    while(scanf("%d", &n) != EOF && n) {
        int ans = 0;
        for(int i = 0; i < n; ++i) scanf("%d", &a[i]), ans ^= a[i];
        int cnt = 0;
        for(int i = 0; i < n; ++i) cnt += (a[i] >= (a[i] ^ ans));
        printf("%d\n", ans ? cnt : 0);
    }
}
