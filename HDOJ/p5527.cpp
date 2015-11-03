#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <numeric>
using namespace std;
typedef long long LL;

const int MAXN = 12;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;

int cost[] = {1, 5, 10, 20, 50, 100, 200, 500, 1000, 2000};
int c[MAXN];
int T, p, n = 10;

LL solve(int i, LL rest) {
    if(rest == 0) return 0;
    if(i < 0) return INF;
    LL v = min((LL)c[i], rest / cost[i]);
    LL res = v + solve(i - 1, rest - v * cost[i]);
    if(v > 0) res = min(res, v - 1 + solve(i - 1, rest - (v - 1) * cost[i]));
    return res;
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &p);
        for(int i = 0; i < n; ++i) scanf("%d", &c[i]);

        LL summoney = 0;
        for(int i = 0; i < n; ++i)
            summoney += (LL)cost[i] * c[i];

        int res = summoney >= p ? solve(n - 1, summoney - p) : INF;
        if(res >= INF) puts("-1");
        else printf("%d\n", accumulate(c, c + n, 0) - res);
    }
}
