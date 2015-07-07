////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-11-16 16:17:41
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 3037
////Problem Title: 
////Run result: Accept
////Run time:1234MS
////Run memory:680KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long LL;

const int MAXN = 100010;

int fac[MAXN];
int n, m, p, T;

int power(int x, int p, int mod) {
    int res = 1;
    while(p) {
        if(p & 1) res = (LL)res * x % mod;
        x = (LL)x * x % mod;
        p >>= 1;
    }
    return res;
}

void init_fac(int p) {
    fac[0] = 1;
    for(int i = 1; i <= p; ++i)
        fac[i] = (LL)fac[i - 1] * i % p;
}

int lucas(int n, int m, int p) {
    int res = 1;
    while(n && m) {
        int a = n % p, b = m % p;
        if(a < b) return 0;
        res = (LL)res * fac[a] * power((LL)fac[b] * fac[a - b] % p, p - 2, p) % p;//三次乘法注意
        n /= p;
        m /= p;
    }
    return res;
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d%d", &n, &m, &p);
        init_fac(p);
        printf("%d\n", lucas(n + m, m, p));
    }
}
