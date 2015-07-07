////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-09-27 23:18:06
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 5053
////Problem Title: 
////Run result: Accept
////Run time:15MS
////Run memory:364KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <bitset>
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

const int MAXN = 10010;

LL sum[MAXN];
int a, b, T;

int main() {
    for(int i = 1; i <= 10000; ++i)
        sum[i] = sum[i - 1] + LL(i) * i * i;

    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d", &a, &b);
        printf("Case #%d: %I64d\n", t, sum[b] - sum[a - 1]);
    }
}