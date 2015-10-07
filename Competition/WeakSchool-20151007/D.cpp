#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define foreach(it, vec) for(__typeof(vec.begin()) it = vec.begin(); it != vec.end(); ++it)

const int MAXN = 100010;

LL a[MAXN];
int res[MAXN];
int n, maxa, T;

void solve() {
    memset(res, 0, sizeof(res));
    LL now = 0, tmp = (1LL << 60) - 1;
    for(int i = maxa; i >= 0; --i) {
        now <<= 1;
        res[i + 60] = now >> 60;
        now &= tmp;
        if(now <= a[i]) {
            a[i] -= now;
            now = (a[i] & 1);
        } else {
            now -= a[i];
        }
    }
    for(int i = 0; i < 60; ++i)
        res[i] = (now >> i) & 1;
}

void print() {
    while(maxa && !res[maxa]) --maxa;
    for(int i = maxa; i >= 0; --i)
        putchar('0' + res[i]);
    puts("");
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        memset(a, 0, sizeof(a));
        scanf("%d", &n);
        maxa = 0;
        for(int i = 0, p, x; i < n; ++i) {
            scanf("%d%d", &p, &x);
            a[p] += x;
            maxa = max(maxa, p);
        }
        solve();
        printf("Case #%d: ", t);
        print();
    }
}
