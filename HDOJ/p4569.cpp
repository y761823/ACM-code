////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-08-22 14:03:55
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4569
////Problem Title: 
////Run result: Accept
////Run time:62MS
////Run memory:328KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
typedef long long LL;

const int MAXN = 8;

int T, deg;
LL phi;
LL a[MAXN];

LL f(LL x, LL m) {
    LL ret = 0, xx = 1;
    for(int i = 0; i <= deg; ++i) {
        ret = (ret + a[i] * xx) % m;
        xx = (xx * x) % m;
    }
    return ret;
}

LL ans, ret;
int t;

void solve() {
    for(ans = 0; ans < phi; ++ans) {
        if(f(ans, phi) == 0) {
            for(ret = ans; ret <= phi * phi; ret += phi)
                if(f(ret, phi * phi) == 0) {
                    printf("Case #%d: %d\n", t, (int)ret);
                    return ;
                }
        }
    }
    printf("Case #%d: No solution!\n", t);
}

int main() {
    cin>>T;
    for(t = 1; t <= T; ++t) {
        cin>>deg;
        for(int i = deg; i >= 0; --i) cin>>a[i];
        cin>>phi;
        solve();
    }
}
