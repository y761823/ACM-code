////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-11-07 10:54:14
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 1040
////Problem Title: 
////Run result: Accept
////Run time:0MS
////Run memory:300KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

int a[1010];

int main() {
    int T, n;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 0; i < n; ++i) scanf("%d", &a[i]);
        sort(a, a + n);
        for(int i = 0; i < n; ++i) {
            if(i) printf(" ");
            printf("%d", a[i]);
        }
        printf("\n");
    }
}