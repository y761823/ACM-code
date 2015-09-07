#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <numeric>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)

const int MAXN = 100010;

int a[MAXN], ll[MAXN], rr[MAXN];
int d1, d2, n;

LL solve1() {
    return accumulate(rr, rr + n, 0LL);
}

LL solve2() {
    LL res = 0;
    for(int i = 0; i < n; ++i)
        res += (LL)ll[i] * rr[i];
    return res;
}

int main() {
    while(scanf("%d%d%d", &n, &d1, &d2) != EOF) {
        for(int i = 0; i < n; ++i)
            scanf("%d", &a[i]);
        ll[0] = 1;
        for(int i = 1; i < n; ++i)
            ll[i] = (a[i] == a[i - 1] + d1 ? ll[i - 1] + 1 : 1);
        rr[n - 1] = 1;
        for(int i = n - 2; i >= 0; --i)
            rr[i] = (a[i + 1] == a[i] + d2 ? rr[i + 1] + 1 : 1);
        printf("%I64d\n", d1 == d2 ? solve1() : solve2());
    }
}
