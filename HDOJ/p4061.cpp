////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-08-30 18:53:53
////Compiler: Visual C++
//////////////////////////////////////////////////////
////Problem ID: 4061
////Problem Title: 
////Run result: Accept
////Run time:31MS
////Run memory:244KB
//////////////////System Comment End//////////////////
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <numeric>
using namespace std;
typedef long long LL;

const int MAXN = 110;

int a[MAXN];
int n, T;

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d", &n);
        for(int i = 0; i < n; ++i) scanf("%d", &a[i]);
        printf("Case %d: %.6f\n", t, double(a[0]) / accumulate(a, a + n, 0));
    }
}