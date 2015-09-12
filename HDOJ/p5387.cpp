#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)

const int MAX = 60 * 60 * 12;

void solve(int a, int b) {
    if(a > b) swap(a, b);
    int c = b - a;
    if(MAX - c < c) c = MAX - c;
    int gcd = __gcd(c, 120);
    if(gcd == 120) printf("%d ", c / gcd);
    else printf("%d/%d ", c / gcd, 120 / gcd);
}

int T, a, b, c;

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d:%d:%d", &a, &b, &c);
        if(a >= 12) a -= 12;
        a = a * 3600 + b * 60 + c;
        b = (b * 60 + c) * 12;
        c = c * 60 * 12;
        solve(a, b);
        solve(a, c);
        solve(b, c);
        puts("");
    }
}
