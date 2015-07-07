////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-10-09 16:44:03
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 5003
////Problem Title: 
////Run result: Accept
////Run time:0MS
////Run memory:300KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <functional>
using namespace std;
typedef long long LL;

const int MAXN = 55;

int T, n;
int a[MAXN];

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 0; i < n; ++i) scanf("%d", &a[i]);
        sort(a, a + n, greater<int>());
        double tmp = 1, res = 0;
        for(int i = 0; i < n; ++i) {
            res += tmp * a[i];
            tmp *= 0.95;
        }
        printf("%.10f\n", res);
    }
}
