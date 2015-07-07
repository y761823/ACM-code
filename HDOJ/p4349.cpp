////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-11-16 16:30:31
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4349
////Problem Title: 
////Run result: Accept
////Run time:78MS
////Run memory:296KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long LL;

int main() {
    int n;
    while(scanf("%d", &n) != EOF)
        printf("%d\n", 1 << __builtin_popcount(n));
}
