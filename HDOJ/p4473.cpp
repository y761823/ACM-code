////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-03-16 22:02:01
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4473
////Problem Title: 
////Run result: Accept
////Run time:2609MS
////Run memory:364KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long LL;

int a, b, c;
LL n, ans;

LL sqrt2(LL x) {
    LL t = sqrt(x);
    while(t * t < x) ++t;
    while(t * t > x) --t;
    return t;
}

LL sqrt3(LL x) {
    LL t = pow(x, 1./3);
    while(t * t * t < x) ++t;
    while(t * t * t > x) --t;
    return t;
}

int main() {
    int t = 0;
    while(cin>>n) {
        LL sq3 = sqrt3(n);
        ans = sq3;
        for(a = 1; a <= sq3; ++a) {
            LL n_a = n / a, k = sqrt2(n_a);
            ans += (n_a / a + k - 2 * a) * 3;
            for(int b = a + 1; b <= k; ++b)
                ans += (n_a / b - b) * 6;
        }
        printf("Case %d: ", ++t);
        cout<<ans<<endl;
    }
}