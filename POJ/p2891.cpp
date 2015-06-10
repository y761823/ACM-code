#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;

void exgcd(LL a, LL b, LL &d, LL &x, LL &y) {
    if(!b) d = a, x = 1, y = 0;
    else {
        exgcd(b, a % b, d, y, x);
        y -= x * (a / b);
    }
}

int main() {
    LL k, a1, a2, r1, r2;
    while(scanf("%I64d", &k) != EOF) {
        bool flag = true;
        scanf("%I64d%I64d", &a1, &r1);
        for(int i = 1; i < k; ++i) {
            scanf("%I64d%I64d", &a2, &r2);
            if(!flag) continue;
            LL r = r2 - r1, d, k1, k2;
            exgcd(a1, a2, d, k1, k2);
            if(r % d) flag = false;
            LL t = a2 / d;
            k1 = (r / d * k1 % t + t) % t;
            r1 = r1 + a1 * k1;
            a1 = a1 / d * a2;
        }
        printf("%I64d\n", flag ? r1 : -1);
    }
}
