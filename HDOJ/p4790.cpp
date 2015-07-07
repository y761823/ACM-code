////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-09-12 20:20:12
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4790
////Problem Title: 
////Run result: Accept
////Run time:46MS
////Run memory:320KB
//////////////////System Comment End//////////////////
#ifdef ONLINE_JUDGE
#define longformat "%lld"
#else
#define longformat "%I64d"
#endif // ONLINE_JUDGE

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long LL;
#define FOR(i, st, ed) for(int i = st; i <= ed; ++i)

LL a, b, c, d, p, m, tmp, f, cnt, ans;
int T;

void calc1() {
    LL r = (m + c) % p;
    f = m + (r ? p - r : 0);
    if(f <= b) {
        cnt = (b - f + 1 + p - 1) / p;
        ans += cnt * (d - c + 1);
    }
}

void calc2() {
    LL r = (a + c) % p;
    f = a + (r ? p - r : 0);
    if(f < m) {
        cnt = (m - 1 - f + 1 + p - 1) / p;
        ans += cnt * (cnt - 1) / 2 * p + (f - a + 1) * cnt;
    }
}

void calc3() {
    tmp = b - (d - c) + 1;
    LL r = (tmp + d) % p;
    f = tmp + (r ? p - r : 0);
    if(f <= b) {
        cnt = (b - f + 1 + p - 1) / p;
        ans += (b - f + 1) * cnt - cnt * (cnt - 1) / 2 * p;
    }
}

void solve() {
    m = a + (d - c);
    ans = 0;
    calc1();
    calc2();
    calc3();
    m = (b - a + 1) * (d - c + 1);
    LL gcd = __gcd(ans, m);
    //gcd = 1;
    printf("%I64d/%I64d\n", ans / gcd, m / gcd);
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%I64d%I64d%I64d%I64d%I64d%I64d", &a, &b, &c, &d, &p, &m);
        if(b - a < d - c)
            swap(a, c), swap(b, d);
        if(m > 0) {
            a += p - m;
            b += p - m;
        }
        printf("Case #%d: ", t);
        solve();
    }
}
