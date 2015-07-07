////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-08-07 18:28:59
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4813
////Problem Title: 
////Run result: Accept
////Run time:15MS
////Run memory:320KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long LL;

const int MAXN = 1010;

char s[MAXN];
int n, m, T;

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        scanf("%s", s);
        int c = 0;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) putchar(s[c++]);
            puts("");
        }
    }
}
