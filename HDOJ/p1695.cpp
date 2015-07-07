////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2015-02-14 00:20:20
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 1695
////Problem Title: 
////Run result: Accept
////Run time:46MS
////Run memory:1684KB
//////////////////System Comment End//////////////////
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
typedef long long LL;

#define foreach(iter, v) for(__typeof(v.begin()) iter = v.begin(); iter != v.end(); ++iter)

const int MAXN = 100010;

bool isprime[MAXN];
int mobius[MAXN], prime[MAXN];
int total;

void init(int n = 100000) {
    memset(isprime, true, sizeof(isprime));
    mobius[1] = 1;
    for(int i = 2; i <= n; ++i) {
        if(isprime[i]) {
            prime[total++] = i;
            mobius[i] = -1;
        }
        for(int j = 0; j < total && i * prime[j] <= n; ++j) {
            isprime[i * prime[j]] = false;
            if(i % prime[j]) mobius[i * prime[j]] = -mobius[i];
            else {
                mobius[i * prime[j]] = 0;
                break;
            }
        }
    }
}

LL solve(int n, int m) {
    if(n > m) swap(n, m);

    LL res = 0, tmp = 0;
    for(int i = 1; i <= n; ++i)
        res += (LL)mobius[i] * (n / i) * (m / i),
        tmp += (LL)mobius[i] * (n / i) * (n / i);
    return res - tmp / 2;
}

int T, a, b, c, d, k;

int main() {
    init();
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
        LL ans = (k ? solve(b / k, d / k) : 0);
        printf("Case %d: %I64d\n", t, ans);
    }
}
