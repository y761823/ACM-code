////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-11-07 10:57:55
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 2560
////Problem Title: 
////Run result: Accept
////Run time:46MS
////Run memory:288KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    int n, m, T, x, ans;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        ans = 0;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                scanf("%d", &x);
                ans += x;
            }
        }
        printf("%d\n", ans);
    }
}