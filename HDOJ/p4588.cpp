////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-08-24 17:54:36
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4588
////Problem Title: 
////Run result: Accept
////Run time:1140MS
////Run memory:332KB
//////////////////System Comment End//////////////////
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;
typedef long long LL;

int a, b;
LL ans, carry, now;

inline LL get(LL x, int p) {
    ++x;
    LL v = 1LL << p, ret = 0;
    ret += x / v * v / 2;
    x %= v;
    if(x > v / 2) ret += x - v / 2;
    return ret;
}

int main() {
    //while(cin>>a>>b) cout<<get(a, b)<<endl;
    while(scanf("%d%d", &a, &b) != EOF) {
        carry = ans = 0;
        now = 1;
        while(1LL<<now <= b || carry > 0) {
            carry += get(b, now) - get(a - 1, now);
            ans += carry >> 1;
            carry >>= 1;
            ++now;
        }
        cout<<ans<<endl;
    }
}
