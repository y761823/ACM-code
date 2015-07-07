////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-09-25 21:11:58
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 5035
////Problem Title: 
////Run result: Accept
////Run time:796MS
////Run memory:300KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef pair<int, int> PII;

const int MAXV = 1010;

double k, s;
int T, n, c;

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d", &n);
        s = 0;
        for(int i = 0; i < n; ++i) scanf("%lf", &k), s += k;
        for(int i = 0; i < n; ++i) scanf("%d", &c);
        printf("Case #%d: %.6f\n", t, (n + 1) / s);
    }
}
