////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-03-16 21:59:10
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4465
////Problem Title: 
////Run result: Accept
////Run time:328MS
////Run memory:824KB
//////////////////System Comment End//////////////////
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAXN = 200010 * 2;

double a[MAXN], b[MAXN], p;
double c[MAXN];
int n;

void init() {
    c[0] = 0;
    for(int i = 1; i <= n; ++i) c[i] = c[i - 1] + log2(n + i) - log2(i);
    a[0] = 0;
    double tmp1 = log2(p);
    for(int i = 1; i <= n + 1; ++i) a[i] = a[i - 1] + tmp1;
    b[0] = 0;
    double tmp2 = log2(1 - p);
    for(int i = 1; i <= n + 1; ++i) b[i] = b[i - 1] + tmp2;
}

int main() {
    int t = 0;
    while(scanf("%d%lf", &n, &p) != EOF) {
        init();
        double ans = 0;
        for(int i = 0; i <= n; ++i) {
            double tmp1 = c[i] + a[n + 1] + b[i];
            double tmp2 = c[i] + a[i] + b[n + 1];
            ans += (exp2(tmp1) + exp2(tmp2)) * (n - i);
        }
        printf("Case %d: %.10f\n", ++t, ans);
    }
}