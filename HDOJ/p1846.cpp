////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-01-23 23:27:42
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 1846
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

int main() {
    int T, n, m;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        puts((n % (m + 1)) ? "first" : "second");
    }
}
