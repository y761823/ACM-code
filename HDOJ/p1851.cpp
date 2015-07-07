////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-01-23 23:37:53
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 1851
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

int M, L;
int T, n;

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        int ans = 0;
        for(int i = 0; i < n; ++i) {
            scanf("%d%d", &M, &L);
            ans ^= (M % (L + 1));
        }
        puts(ans ? "No" : "Yes");
    }
}
