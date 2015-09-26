#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long LL;

int c, k1, k2, b1;

LL power(LL x, int p) {
    LL res = 1;
    while(p) {
        if(p & 1) res = res * x % c;
        x = x * x % c;
        p >>= 1;
    }
    return res;
}

int check(int a) {
    int b = (-power(a, k1 + b1) + c) % c;
    if(power(a, k1) == power(b, k2))
        return b;
    return 0;
}

int main() {
    int kase = 0;
    while(scanf("%d%d%d%d", &c, &k1, &b1, &k2) != EOF) {
        printf("Case #%d:\n", ++kase);
        bool flag = false;
        for(int a = 1; a < c; ++a) {
            int b = check(a);
            if(b > 0) {
                flag = true;
                printf("%d %d\n", a, b);
            }
        }
        if(!flag) puts("-1");
    }
}
