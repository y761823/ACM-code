////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-10-12 16:47:42
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 1021
////Problem Title: 
////Run result: Accept
////Run time:15MS
////Run memory:288KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long LL;
#define FOR(i, n) for(int i = 0; i < n; ++i)

int n;

int main() {
    while(scanf("%d", &n) != EOF) {
        puts((n & 3) == 2 ? "yes" : "no");
    }
}
