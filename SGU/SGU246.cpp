#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define FOR(i, n) for(int i = 0; i < n; ++i)

LL x;

int main() {
    scanf("%I64d", &x);
    LL n = (x + 1) / 2;
    LL gcd = __gcd(x, n + 1);
    printf("%I64d\n", gcd * (x / gcd / 2) + 1);
}
