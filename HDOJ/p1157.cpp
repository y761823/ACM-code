////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-11-07 10:55:59
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 1157
////Problem Title: 
////Run result: Accept
////Run time:15MS
////Run memory:336KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

int a[10010];

int main() {
    int n;
    while(scanf("%d", &n) != EOF) {
        for(int i = 0; i < n; ++i) scanf("%d", &a[i]);
        sort(a, a + n);
        printf("%d\n", a[n/2]);
    }
}