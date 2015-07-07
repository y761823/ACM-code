////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-11-07 11:00:27
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 2504
////Problem Title: 
////Run result: Accept
////Run time:0MS
////Run memory:292KB
//////////////////System Comment End//////////////////
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int solve(int a, int b) {
    for(int i = 2 * b; ; i += b)
        if(__gcd(a, i) == b) return i;
}

int main() {
    int a, b, n;
    while(scanf("%d", &n) != EOF) {
        while(n--) {
            scanf("%d%d", &a, &b);
            printf("%d\n", solve(a, b));
        }
    }
}