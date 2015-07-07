////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-08-12 14:54:09
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4572
////Problem Title: 
////Run result: Accept
////Run time:0MS
////Run memory:316KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;
typedef long long LL;

int n, m;

int main() {
    while(scanf("%d%d", &m, &n) != EOF) {
        printf("%d\n", n * m - (n >> 1) * (n >> 1));
    }
}
